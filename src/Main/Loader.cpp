#include <LoggerAPI.h>
#include "DotNETGlobal.hpp"
#include "PluginAttribute.hpp"
#include "PluginManager.hpp"
#include "IPluginInitializer.hpp"
#include "FixCLRFatalError.hpp"
#include "PluginOwnData.hpp"

#include <src/Tools/CallbackConverter.hpp>


#pragma managed

//managed
Assembly^ OnAssemblyResolve(System::Object^ sender, System::ResolveEventArgs^ args);

//managed
void Init();

//inline void InitializePluginHandler(std::filesystem::path const& path, Assembly^ Asm);

//managed
bool LoadByDefaultEntry(Logger& logger, Assembly^ Asm);

//managed
bool LoadByCustomEntry(Logger& logger, Assembly^ Asm);

//managed
void LoadPlugins(std::vector<std::filesystem::path> const& assemblyPaths, Logger& logger);

//managed
List<String^>^ ParsePluginLibraryPath(Assembly^ Asm);

namespace LiteLoader::NET {
    public ref class __Entry
    {
    public:
        delegate void EntryPropotype(void*, void*);

        static void InitAndLoadPlugins(void* pLogger, void* std_vector_assemblies)
        {
            auto& logger = *reinterpret_cast<::Logger*>(pLogger);

            FixCLRFatalError(logger);

            Init();

            logger.info("Loading .NET plugins...");

            LoadPlugins(
                *reinterpret_cast<std::vector<std::filesystem::path>*>(std_vector_assemblies),
                logger);
        }
    };
}

void __entry(void* pLogger, void* std_vector_assemblies) { LiteLoader::NET::__Entry::InitAndLoadPlugins(pLogger, std_vector_assemblies); }

#pragma unmanaged
#include "Global.hpp"
#include <Utils/Hash.h>
#include <sstream>

#pragma unmanaged

std::vector<std::filesystem::path> GetAllAssemblies();

void LoadMain()
{
    Logger logger(LLNET_INFO_LOADER_NAME);

    logger.consoleLevel = 5;

    __entry(&logger, &GetAllAssemblies());
}

std::vector<std::filesystem::path> GetAllAssemblies()
{
    std::filesystem::directory_iterator files(LLNET_PLUGINS_LOAD_DIR);
    std::vector<std::filesystem::path> assemblies;
    for (auto& file : files)
    {
        auto& filePath = file.path();
        if (filePath.extension() == ".dll")
        {
            assemblies.emplace_back(filePath);
        }
    }
    return assemblies;
}

#pragma managed
extern void InitEvents();

void Init()
{
    InitEvents();
    System::AppDomain::CurrentDomain->AssemblyResolve += gcnew System::ResolveEventHandler(&OnAssemblyResolve);
    auto LLNET_Asm = Assembly::GetExecutingAssembly();
    LiteLoader::NET::PluginOwnData::ManagedAssemblyHandle->TryAdd(LLNET_Asm, nint_t(::ll::getPlugin(LLNET_INFO_LOADER_NAME)->handle));
}


Assembly^ ResolveAssembly(Assembly^ requestingAssembly, AssemblyName% assemblyName)
{
    using System::IO::Path;
    using System::IO::File;

    if (assemblyName.Name == LLNET_INFO_LOADER_NAME)
        return Assembly::GetExecutingAssembly();

    auto llLibPath = Path::Combine(LITELOADER_LIBRARY_DIR, assemblyName.Name + ".dll");
    if (File::Exists(llLibPath))
    {
        return Assembly::LoadFrom(llLibPath);
    }

    auto llLibPathManaged = Path::Combine(LLNET_LIBRARY_DIR_DOTNETONLY, assemblyName.Name + ".dll");
    if (File::Exists(llLibPathManaged))
    {
        return Assembly::LoadFrom(llLibPathManaged);
    }

    if (GlobalClass::RUNTIME_SHARED_LIB_DIR != nullptr)
    {
        auto runtimeSharedLibPath = Path::Combine(const_cast<String^>(GlobalClass::RUNTIME_SHARED_LIB_DIR), assemblyName.Name + ".dll");
        if (File::Exists(runtimeSharedLibPath))
        {
            return Assembly::LoadFrom(runtimeSharedLibPath);
        }
    }

    List<String^>^ customPaths = nullptr;
    if (LiteLoader::NET::PluginOwnData::CustomLibPath->TryGetValue(requestingAssembly, customPaths))
    {
        for each (auto customPath in customPaths)
        {
            auto libPath = System::IO::Path::Combine(customPath, assemblyName.Name + ".dll");
            if (File::Exists(libPath))
            {

                auto Asm = System::Reflection::Assembly::LoadFrom(libPath);
                auto handle = GetModuleHandle(std::filesystem::path(marshalString(Asm->Location)).wstring().c_str());
                LiteLoader::NET::PluginOwnData::ManagedAssemblyHandle->Add(Asm, nint_t(handle));
                return Asm;
            }

            auto libPathWithPlugin = Path::Combine("plugins", customPath, assemblyName.Name + ".dll");
            if (File::Exists(libPathWithPlugin))
            {
                auto Asm = Assembly::LoadFrom(libPathWithPlugin);
                auto handle = GetModuleHandle(std::filesystem::path(marshalString(Asm->Location)).wstring().c_str());
                LiteLoader::NET::PluginOwnData::ManagedAssemblyHandle->Add(Asm, nint_t(handle));
                return Asm;
            }
        }
    }

    return nullptr;
}


Assembly^ OnAssemblyResolve(System::Object^ sender, System::ResolveEventArgs^ args)
{
    return ResolveAssembly(args->RequestingAssembly, AssemblyName(args->Name));
}


void LoadPlugins(std::vector<std::filesystem::path> const& assemblyPaths, Logger& logger)
{
    using System::Reflection::PortableExecutable::PEReader;
    using System::IO::File;
    using System::IO::FileStream;
    using System::IO::FileMode;
    using System::IO::FileAccess;
    using System::IO::FileShare;

    size_t count = 0;
    for (auto iter = assemblyPaths.begin(); iter != assemblyPaths.end(); ++iter)
    {
        if (iter->filename() == LLNET_INFO_LOADER_NAME)
            continue;

        auto path = marshalString(iter->string());

        bool isManagedAssembly = false;
        auto file = gcnew FileStream(path, FileMode::Open, FileAccess::Read, FileShare::ReadWrite);
        auto reader = gcnew PEReader(file);

        if (reader->HasMetadata)
            isManagedAssembly = true;

        file->Close();

        if (!isManagedAssembly)
        {
            continue;
        }


        auto Asm = Assembly::LoadFrom(path);

        LiteLoader::NET::PluginManager::registerPlugin(Asm->GetName()->Name, String::Empty, gcnew LiteLoader::Version(1, 0, 0), nullptr, Asm);

        LiteLoader::NET::PluginOwnData::CustomLibPath->Add(Asm, ParsePluginLibraryPath(Asm));

        auto succeed = LoadByDefaultEntry(logger, Asm);
        if (!succeed)
            succeed = LoadByCustomEntry(logger, Asm);


        if (succeed)
        {
            logger.info(".NET plugin <{}> loaded", marshalString(Asm->GetName()->Name));
            ++count;
        }
    }
    logger.info("{} .NET plugin(s) loaded", count);
}

// For forward compatibility
bool LoadByDefaultEntry(Logger& logger, Assembly^ Asm)
{
    auto plugin = Asm->GetType("PluginMain.Plugin");
    if (plugin == nullptr)
        return false;
    auto method = plugin->GetMethod("OnPostInit");
    if (method == nullptr)
        return false;
    if (method->ReturnType != void::typeid)
        return false;
    if (method->GetParameters()->Length > 0)
        return false;
    try
    {
        reinterpret_cast<void(*)()>(method->MethodHandle.GetFunctionPointer().ToPointer())();
    }
    catch (System::Exception^ ex)
    {
        logger.error(".NET plugin <{}> failed to load: Uncaught {} Detected!", marshalString(Asm->GetName()->Name), marshalString(ex->GetType()->ToString()));
        logger.error(marshalString(ex->ToString()));
        return false;
    }
    return true;
}


List<String^>^ ParsePluginLibraryPath(Assembly^ Asm)
{
    using LiteLoader::NET::LibPathAttribute;

    auto libAttrType = LibPathAttribute::typeid;
    auto ret = gcnew List<String^>;

    auto asmLibPathAttrArr = Asm->GetCustomAttributes(libAttrType, false);

    if (asmLibPathAttrArr == nullptr)
        return ret;

    for each (auto attr in asmLibPathAttrArr)
    {
        ret->Add(static_cast<LibPathAttribute^>(attr)->Path);
    }

    return ret;
}

bool LoadByCustomEntry(Logger& logger, Assembly^ Asm)
{
    using IPluginInitializer = LiteLoader::NET::IPluginInitializer;
    using PluginMainAttribute = LiteLoader::NET::PluginMainAttribute;
    using LibPathAttribute = LiteLoader::NET::LibPathAttribute;

    auto types = Asm->GetExportedTypes();
    auto name = Asm->GetName();
    System::String^ pluginName = name->Name;
    IPluginInitializer^ initializer = nullptr;
    for each (auto type in types)
    {
        if (type->Equals(IPluginInitializer::typeid))
            continue;

        auto pluginMainAttr = System::Attribute::GetCustomAttribute(type, PluginMainAttribute::typeid);
        auto customLibPathAttribute = System::Attribute::GetCustomAttribute(type, LibPathAttribute::typeid);

        if (pluginMainAttr != nullptr)
        {
            pluginName = static_cast<PluginMainAttribute^>(pluginMainAttr)->Name;
            auto ctor = type->GetConstructor(System::Type::EmptyTypes);
            if (ctor != nullptr)
            {
                pluginName = static_cast<PluginMainAttribute^>(pluginMainAttr)->Name;
                initializer = static_cast<IPluginInitializer^>(ctor->Invoke(nullptr));
                break;
            }
        }
    }

    try
    {
        if (initializer == nullptr)
        {
            throw gcnew System::EntryPointNotFoundException();
        }
        initializer->OnInitialize();
    }
    catch (System::Exception^ ex)
    {
        logger.error(".NET plugin <{}> failed to load: Uncaught {} Detected!", marshalString(pluginName), marshalString(ex->GetType()->ToString()));
        logger.error(marshalString(ex->ToString()));
        return false;
    }
    String^ introduction = initializer->Introduction;
    auto version = gcnew LiteLoader::Version(
        name->Version->Major,
        name->Version->Minor,
        name->Version->Build
    );
    auto others = initializer->MetaData;
    LiteLoader::NET::PluginManager::registerPlugin(pluginName, introduction, version, others, Asm);
    return true;
}
