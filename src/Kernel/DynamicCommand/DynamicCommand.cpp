#include <src/Header/DynamicCommand/DynamicCommand.hpp>
#include <src/Header/DynamicCommand/DynamicCommandInstance.hpp>
#include <src/Main/PluginOwnData.hpp>
#include <memory>

namespace LiteLoader::DynamicCommand
{
    DynamicCommand^ DynamicCommand::Result::Command::get()
    {
        return gcnew DynamicCommand((::DynamicCommand*)NativePtr->command);
    }
    DynamicCommandInstance^ DynamicCommand::Result::Instance::get()
    {
        return gcnew DynamicCommandInstance((::DynamicCommandInstance*)NativePtr->instance);
    }
    MC::CommandOrigin^ DynamicCommand::Result::Origin::get()
    {
        return gcnew MC::CommandOrigin((::CommandOrigin*)NativePtr->origin);
    }
    inline System::Object^ DynamicCommand::Result::Get() {
        if (!NativePtr->isSet)
            return nullptr; // null
        switch (NativePtr->type)
        {
        case ::DynamicCommand::ParameterType::Bool:
            return NativePtr->getRaw<bool>();
        case ::DynamicCommand::ParameterType::Int:
            return NativePtr->getRaw<int>();
        case ::DynamicCommand::ParameterType::Float:
            return NativePtr->getRaw<float>();
        case ::DynamicCommand::ParameterType::String:
            return marshalString(NativePtr->getRaw<std::string>());
        case ::DynamicCommand::ParameterType::Actor:
        {
            auto arr = gcnew List<MC::Actor^>;
            for (auto i : NativePtr->get<std::vector<Actor*>>())
            {
                arr->Add(gcnew MC::Actor(i));
            }
            return arr;
        }
        case ::DynamicCommand::ParameterType::Player:
        {
            auto arr = gcnew List<MC::Player^>;
            for (auto i : NativePtr->get<std::vector<Player*>>())
            {
                arr->Add(gcnew MC::Player(i));
            }
            return arr;
        }
        case ::DynamicCommand::ParameterType::BlockPos:
        {
            return MC::BlockPos(NativePtr->get<BlockPos>());
        }
        case ::DynamicCommand::ParameterType::Vec3:
        {
            return MC::Vec3(NativePtr->get<Vec3>());
        }
        case ::DynamicCommand::ParameterType::Message:
            return gcnew MC::CommandMessage(const_cast<::CommandMessage*>(&NativePtr->getRaw<::CommandMessage>()));
        case ::DynamicCommand::ParameterType::RawText:
            return marshalString(NativePtr->getRaw<std::string>());
        case ::DynamicCommand::ParameterType::JsonValue:
            return marshalString(JsonHelpers::serialize(NativePtr->getRaw<Json::Value>()));
        case ::DynamicCommand::ParameterType::Item:
            return gcnew MC::CommandItem(NativePtr->getRaw<CommandItem>());
		//case ::DynamicCommand::ParameterType::Block:
			//return gcnew MC::Block(const_cast<Block*>(NativePtr->getRaw<Block const*>()));
        case ::DynamicCommand::ParameterType::Effect:
            return gcnew MC::MobEffect((MobEffect*)NativePtr->getRaw<MobEffect const*>());
        case ::DynamicCommand::ParameterType::Enum:
            return marshalString(NativePtr->getRaw<std::string>());
        case ::DynamicCommand::ParameterType::SoftEnum:
            return marshalString(NativePtr->getRaw<std::string>());
        case ::DynamicCommand::ParameterType::Command:
            return gcnew MC::Command((::__Command*)NativePtr->getRaw<std::unique_ptr<::Command>>().get());
        case ::DynamicCommand::ParameterType::ActorType:
            return gcnew MC::ActorDefinitionIdentifier((ActorDefinitionIdentifier*)NativePtr->getRaw<ActorDefinitionIdentifier const*>());
        default:
            return nullptr; // null
            break;
        }
    }
    inline bool DynamicCommand::Result::AsBool() {
        if (!NativePtr->isSet || NativePtr->type != ::DynamicCommand::ParameterType::Bool)
            throw gcnew DynamicCommandInvalidCastException;
        return NativePtr->getRaw<bool>();
    }
    inline int DynamicCommand::Result::AsInt() {
        if (!NativePtr->isSet || NativePtr->type != ::DynamicCommand::ParameterType::Int)
            throw gcnew DynamicCommandInvalidCastException;
        return NativePtr->getRaw<int>();
    }
    inline float DynamicCommand::Result::AsFloat() {
        if (!NativePtr->isSet || NativePtr->type != ::DynamicCommand::ParameterType::Float)
            throw gcnew DynamicCommandInvalidCastException;
        return NativePtr->getRaw<float>();
    }
    inline String^ DynamicCommand::Result::AsString() {
        if (!NativePtr->isSet || NativePtr->type != ::DynamicCommand::ParameterType::Float)
            throw gcnew DynamicCommandInvalidCastException;
        return marshalString(NativePtr->getRaw<std::string>());
    }
    inline List<MC::Actor^>^ DynamicCommand::Result::AsActorList() {
        if (!NativePtr->isSet || NativePtr->type != ::DynamicCommand::ParameterType::Actor)
            throw gcnew DynamicCommandInvalidCastException;
        auto arr = gcnew List<MC::Actor^>;
        for (auto i : NativePtr->get<std::vector<::Actor*>>())
        {
            arr->Add(gcnew MC::Actor(i));
        }
        return arr;
    }
    inline List<MC::Player^>^ DynamicCommand::Result::AsPlayerList() {
        if (!NativePtr->isSet || NativePtr->type != ::DynamicCommand::ParameterType::Player)
            throw gcnew DynamicCommandInvalidCastException;
        auto arr = gcnew List<MC::Player^>;
        for (auto i : NativePtr->get<std::vector<::Player*>>())
        {
            arr->Add(gcnew MC::Player(i));
        }
        return arr;
    }
    inline MC::BlockPos DynamicCommand::Result::AsBlockPos() {
        if (!NativePtr->isSet || NativePtr->type != ::DynamicCommand::ParameterType::BlockPos)
            throw gcnew DynamicCommandInvalidCastException;
        return MC::BlockPos(NativePtr->get<::BlockPos>());
    }
    inline MC::Vec3 DynamicCommand::Result::AsVec3() {
        if (!NativePtr->isSet || NativePtr->type != ::DynamicCommand::ParameterType::Vec3)
            throw gcnew DynamicCommandInvalidCastException;
        return MC::Vec3(NativePtr->get<::Vec3>());
    }
    inline MC::CommandMessage^ DynamicCommand::Result::AsCommandMessage() {
        if (!NativePtr->isSet || NativePtr->type != ::DynamicCommand::ParameterType::Message)
            throw gcnew DynamicCommandInvalidCastException;
        return gcnew MC::CommandMessage(const_cast<::CommandMessage*>(&NativePtr->getRaw<::CommandMessage>()));
    }
    inline String^ DynamicCommand::Result::AsRawText() {
        if (!NativePtr->isSet || NativePtr->type != ::DynamicCommand::ParameterType::RawText)
            throw gcnew DynamicCommandInvalidCastException;
        return marshalString(NativePtr->getRaw<std::string>());
    }
    inline String^ DynamicCommand::Result::AsJsonValue() {
        if (!NativePtr->isSet || NativePtr->type != ::DynamicCommand::ParameterType::JsonValue)
            throw gcnew DynamicCommandInvalidCastException;
        return marshalString(NativePtr->getRaw<std::string>());
    }
    inline MC::CommandItem^ DynamicCommand::Result::AsCommandItem() {
        if (!NativePtr->isSet || NativePtr->type != ::DynamicCommand::ParameterType::Item)
            throw gcnew DynamicCommandInvalidCastException;
        return gcnew MC::CommandItem(NativePtr->getRaw<CommandItem>());
    }
	//inline MC::Block^ DynamicCommand::Result::AsBlock() {
	//	if (!NativePtr->isSet || NativePtr->type != ::DynamicCommand::ParameterType::Block)
	//		throw gcnew DynamicCommandInvalidCastException;
	//	return gcnew MC::Block(const_cast<Block*>(NativePtr->getRaw<Block const*>()));
	//}
    inline MC::MobEffect^ DynamicCommand::Result::AsMobEffect() {
        if (!NativePtr->isSet || NativePtr->type != ::DynamicCommand::ParameterType::Effect)
            throw gcnew DynamicCommandInvalidCastException;
        return gcnew MC::MobEffect(const_cast<::MobEffect*>(NativePtr->getRaw<::MobEffect const*>()));
    }
    inline String^ DynamicCommand::Result::AsEnum() {
        if (!NativePtr->isSet || NativePtr->type != ::DynamicCommand::ParameterType::Enum)
            throw gcnew DynamicCommandInvalidCastException;
        return marshalString(NativePtr->getRaw<std::string>());
    }
    inline String^ DynamicCommand::Result::AsSoftEnum() {
        if (!NativePtr->isSet || NativePtr->type != ::DynamicCommand::ParameterType::SoftEnum)
            throw gcnew DynamicCommandInvalidCastException;
        return marshalString(NativePtr->getRaw<std::string>());
    }
    inline MC::Command^ DynamicCommand::Result::AsCommand() {
        if (!NativePtr->isSet || NativePtr->type != ::DynamicCommand::ParameterType::Command)
            throw gcnew DynamicCommandInvalidCastException;
        return gcnew MC::Command((::__Command*)NativePtr->getRaw<std::unique_ptr<::Command>>().get(), true);
    }
    inline MC::ActorDefinitionIdentifier^ DynamicCommand::Result::AsActorType() {
        if (!NativePtr->isSet || NativePtr->type != ::DynamicCommand::ParameterType::ActorType)
            throw gcnew DynamicCommandInvalidCastException;
        return gcnew MC::ActorDefinitionIdentifier((ActorDefinitionIdentifier*)NativePtr->getRaw<ActorDefinitionIdentifier const*>());
    }
    LiteLoader::DynamicCommand::DynamicCommand::Result::Result(ParameterPtr^ ptr, DynamicCommand^ command, MC::CommandOrigin^ origin, DynamicCommandInstance^ instance)
        :ClassTemplate(::DynamicCommand::Result(ptr->NativePtr, command->NativePtr, origin->NativePtr, instance->NativePtr))
    {
    }
    LiteLoader::DynamicCommand::DynamicCommand::Result::Result(ParameterPtr^ ptr, DynamicCommand^ command, MC::CommandOrigin^ origin)
        :ClassTemplate(::DynamicCommand::Result(ptr->NativePtr, command->NativePtr, origin->NativePtr))
    {
    }
    LiteLoader::DynamicCommand::DynamicCommand::Result::Result()
        :ClassTemplate(::DynamicCommand::Result())
    {
    }
    inline DynamicCommand::Result^ DynamicCommand::Result::Create(ParameterPtr^ ptr, DynamicCommand^ command, MC::CommandOrigin^ origin, DynamicCommandInstance^ instance)
    {
        return gcnew Result(ptr, command, origin, instance);
    }

    inline DynamicCommand::Result^ DynamicCommand::Result::Create(ParameterPtr^ ptr, DynamicCommand^ command, MC::CommandOrigin^ origin)
    {
        return gcnew Result(ptr, command, origin);
    }

    inline DynamicCommand::Result^ DynamicCommand::Result::Create()
    {
        return gcnew Result();
    }
    String^ DynamicCommand::Result::EnumValue::get()
    {
        return marshalString(NativePtr->getEnumValue());
    }
    DynamicCommand::ParameterType DynamicCommand::Result::GetParameterType()
    {
        return ParameterType(NativePtr->getType());
    }
    String^ DynamicCommand::Result::Name::get()
    {
        return marshalString(NativePtr->getName());
    }
    String^ DynamicCommand::Result::ToDebugString()
    {
        return marshalString(NativePtr->toDebugString());
    }
    DynamicCommandInstance^ DynamicCommand::Result::GetInstance()
    {
        return gcnew DynamicCommandInstance((::DynamicCommandInstance*)NativePtr->getInstance());
    }
    String^ DynamicCommand::Result::ToString()
    {
        return ToDebugString();
    }

    inline DynamicCommandInstance^ DynamicCommand::CreateCommand(String^ name, String^ description, Dictionary<String^, List<String^>^>^ enums, List<ParameterData^>^ params, List<List<String^>^>^ overloads, CallBackFn^ callback, MC::CommandPermissionLevel permission, MC::CommandFlag^ flag1, MC::CommandFlag^ flag2, nint_t handle)
    {

        if (handle == nint_t::Zero)
            handle = nint_t(CALLING_MODULE);


        std::unordered_map<std::string, std::vector<std::string>> enumsMap;

        std::vector<::DynamicCommand::ParameterData> paramsData;

        std::vector<std::vector<std::string>> overLoads;

        auto callbackfn = CallBackFnManager::Create(callback);

        for each (auto % map in enums)
        {
            std::vector<std::string> vector;
            for each (auto vec in map.Value)
            {
                vector.emplace_back(marshalString(vec));
            }
            enumsMap[marshalString(map.Key)] = std::move(vector);
        }

        for each (auto var in params)
        {
            paramsData.emplace_back(*(var->NativePtr));
        }

        for each (auto var in overloads)
        {
            std::vector<std::string> vector;
            for each (auto vec in var)
            {
                vector.emplace_back(marshalString(vec));
            }
            overLoads.emplace_back(std::move(vector));
        }

        return gcnew DynamicCommandInstance(::DynamicCommand::createCommand(
            marshalString(name),
            marshalString(description),
            std::move(enumsMap),
            std::move(paramsData),
            std::move(overLoads),
            callbackfn,
            ::CommandPermissionLevel(permission),
            flag1,
            flag2,
            (HMODULE)handle.ToPointer())
            .release(),
            true);

        PluginOwnData::AddRegisteredCommand(handle, name);
    }
    inline DynamicCommandInstance^ DynamicCommand::Setup(DynamicCommandInstance^ commandInstance)
    {
        return gcnew DynamicCommandInstance(
            (::DynamicCommandInstance*)::DynamicCommand::setup(std::unique_ptr<::DynamicCommandInstance>(commandInstance->ReleasePointer())));
    }
    inline bool DynamicCommand::UnregisterCommand(String^ name)
    {
        return ::DynamicCommand::unregisterCommand(marshalString(name));
    }
    inline bool DynamicCommand::UpdateAvailableCommands()
    {
        return ::DynamicCommand::updateAvailableCommands();
    }
    inline DynamicCommandInstance^ DynamicCommand::GetInstance()
    {
        return gcnew DynamicCommandInstance((::DynamicCommandInstance*)NativePtr->getInstance());
    }
    inline DynamicCommandInstance^ DynamicCommand::GetInstance(String^ commandName)
    {
        return gcnew DynamicCommandInstance((::DynamicCommandInstance*)::DynamicCommand::getInstance(marshalString(commandName)));
    }
    inline DynamicCommand::ParameterPtr::ParameterPtr(ParameterType type, size_t offset)
        :ClassTemplate(::DynamicCommand::ParameterPtr(::DynamicCommand::ParameterType(type), offset))
    {
    }
    inline DynamicCommand::ParameterPtr^ DynamicCommand::ParameterPtr::Create(ParameterType type, size_t offset)
    {
        return gcnew ParameterPtr(::DynamicCommand::ParameterPtr(::DynamicCommand::ParameterType(type), offset));
    }
    bool DynamicCommand::ParameterPtr::IsValueSet(DynamicCommand^ command)
    {
        return NativePtr->isValueSet(command->NativePtr);
    }
    DynamicCommand::Result^ DynamicCommand::ParameterPtr::GetResult(DynamicCommand^ command, MC::CommandOrigin^ origin)
    {
        return gcnew Result(NativePtr->getResult(command->NativePtr, origin));
    }
    inline size_t DynamicCommand::ParameterPtr::GetOffset()
    {
        return size_t(NativePtr->getOffset());
    }
    inline DynamicCommand::ParameterData::ParameterData(ParameterData^ data)
        :ClassTemplate(::DynamicCommand::ParameterData(*data->NativePtr))
    {
    }
    inline DynamicCommand::ParameterData::ParameterData(String^ name, ParameterType type, bool optional, String^ enumOptions, String^ identifier, MC::CommandParameterOption parameterOption)
        : ClassTemplate(::DynamicCommand::ParameterData(
            marshalString(name),
            ::DynamicCommand::ParameterType(type),
            optional,
            marshalString(enumOptions),
            marshalString(identifier),
            ::CommandParameterOption(parameterOption)))
    {
    }
    inline DynamicCommand::ParameterData::ParameterData(String^ name, ParameterType type, bool optional, String^ enumOptions, String^ identifier)
        : ClassTemplate(::DynamicCommand::ParameterData(
            marshalString(name),
            ::DynamicCommand::ParameterType(type),
            optional,
            marshalString(enumOptions),
            marshalString(identifier)))
    {
    }
    inline DynamicCommand::ParameterData::ParameterData(String^ name, ParameterType type, bool optional, String^ enumOptions)
        : ClassTemplate(::DynamicCommand::ParameterData(
            marshalString(name),
            ::DynamicCommand::ParameterType(type),
            optional,
            marshalString(enumOptions)))
    {
    }
    inline DynamicCommand::ParameterData::ParameterData(String^ name, ParameterType type, bool optional)
        : ClassTemplate(::DynamicCommand::ParameterData(
            marshalString(name),
            ::DynamicCommand::ParameterType(type),
            optional))
    {
    }
    inline DynamicCommand::ParameterData::ParameterData(String^ name, ParameterType type)
        : ClassTemplate(::DynamicCommand::ParameterData(
            marshalString(name),
            ::DynamicCommand::ParameterType(type), false))
    {
    }
    inline DynamicCommand::ParameterData::ParameterData(String^ name, ParameterType type, String^ enumOptions, String^ identifier, MC::CommandParameterOption parameterOption)
        : ClassTemplate(::DynamicCommand::ParameterData(
            marshalString(name),
            ::DynamicCommand::ParameterType(type),
            marshalString(enumOptions),
            marshalString(identifier),
            ::CommandParameterOption(parameterOption)))
    {
    }
    inline DynamicCommand::ParameterData::ParameterData(String^ name, ParameterType type, String^ enumOptions, String^ identifier)
        :ClassTemplate(::DynamicCommand::ParameterData(
            marshalString(name),
            ::DynamicCommand::ParameterType(type),
            marshalString(enumOptions),
            marshalString(identifier)))
    {
    }
    inline DynamicCommand::ParameterData::ParameterData(String^ name, ParameterType type, String^ enumOptions)
        :ClassTemplate(::DynamicCommand::ParameterData(
            marshalString(name),
            ::DynamicCommand::ParameterType(type),
            marshalString(enumOptions)))
    {
    }
    inline DynamicCommand::ParameterData^ DynamicCommand::ParameterData::Create(ParameterData^ data)
    {
        return gcnew ParameterData(::DynamicCommand::ParameterData(data));
    }
    inline DynamicCommand::ParameterData^ DynamicCommand::ParameterData::Create(String^ name, ParameterType type, bool optional, String^ enumOptions, String^ identifier, MC::CommandParameterOption parameterOption)
    {
        return gcnew ParameterData(name, type, optional, enumOptions, identifier, parameterOption);
    }
    inline DynamicCommand::ParameterData^ DynamicCommand::ParameterData::Create(String^ name, ParameterType type, bool optional, String^ enumOptions, String^ identifier)
    {
        return gcnew ParameterData(name, type, optional, enumOptions, identifier, MC::CommandParameterOption::None);
    }
    inline DynamicCommand::ParameterData^ DynamicCommand::ParameterData::Create(String^ name, ParameterType type, bool optional, String^ enumOptions)
    {
        return gcnew ParameterData(name, type, optional, enumOptions, String::Empty);
    }
    inline DynamicCommand::ParameterData^ DynamicCommand::ParameterData::Create(String^ name, ParameterType type, bool optional)
    {
        return gcnew ParameterData(name, type, optional, String::Empty);
    }
    inline DynamicCommand::ParameterData^ DynamicCommand::ParameterData::Create(String^ name, ParameterType type)
    {
        return gcnew ParameterData(name, type, false);
    }
    inline DynamicCommand::ParameterData^ DynamicCommand::ParameterData::Create(String^ name, ParameterType type, String^ enumOptions, String^ identifier, MC::CommandParameterOption parameterOption)
    {
        return gcnew ParameterData(name, type, enumOptions, identifier, parameterOption);
    }
    inline DynamicCommand::ParameterData^ DynamicCommand::ParameterData::Create(String^ name, ParameterType type, String^ enumOptions, String^ identifier)
    {
        return gcnew ParameterData(name, type, enumOptions, identifier, MC::CommandParameterOption::None);
    }
    inline DynamicCommand::ParameterData^ DynamicCommand::ParameterData::Create(String^ name, ParameterType type, String^ enumOptions)
    {
        return gcnew ParameterData(name, type, enumOptions, String::Empty);
    }
    MC::CommandParameterData^ DynamicCommand::ParameterData::MakeParameterData()
    {
        return gcnew MC::CommandParameterData(NativePtr->makeParameterData());
    }
    inline void DynamicCommand::ParameterData::SetOptional(bool optional)
    {
        return NativePtr->setOptional(optional);
    }
    inline bool DynamicCommand::ParameterData::SetEnumOptions(String^ enumOptions)
    {
        return NativePtr->setEnumOptions(marshalString(enumOptions));
    }

    //__ctor_base(DynamicCommand, ::DynamicCommand, MC::Command);

    inline DynamicCommand::DynamicCommand(nint_t p)
        : MC::Command(p)
    {
    }
    inline DynamicCommand::DynamicCommand(nint_t p, bool ownsNativeInstance)
        : MC::Command(p, ownsNativeInstance)
    {
    }
    inline DynamicCommand::DynamicCommand(::DynamicCommand* p)
        : MC::Command((::__Command*)p)
    {
    }
    inline DynamicCommand::DynamicCommand(::DynamicCommand* p, bool ownsNativeInstance)
        : MC::Command((::__Command*)p, ownsNativeInstance)
    {
    }
    inline ::DynamicCommand* DynamicCommand::NativePtr::get() {
        return (::DynamicCommand*)(MC::Command::NativePtr);
    }
    inline void DynamicCommand::NativePtr::set(::DynamicCommand* value) {
        MC::Command::NativePtr = (__Command*)value;
    }
    inline DynamicCommand::ParameterType DynamicCommand::Result::Type::get()
    {
        return ParameterType(NativePtr->type);
    }
    inline size_t DynamicCommand::Result::Offset::get()
    {
        return NativePtr->offset;
    }
    inline bool DynamicCommand::Result::IsSet::get()
    {
        return NativePtr->isSet;
    }

    inline DynamicCommandInstance^ DynamicCommand::CreateCommand(String^ name, String^ description, MC::CommandPermissionLevel permission, MC::CommandFlag^ flag1, MC::CommandFlag^ flag2, nint_t handle)
    {
        auto ret = gcnew DynamicCommandInstance(::DynamicCommand::createCommand(marshalString(name), marshalString(description), ::CommandPermissionLevel(permission), flag1, flag2, (HMODULE)handle.ToPointer()).release(), true);

        PluginOwnData::AddRegisteredCommand(handle, name);

        return ret;
    }
    inline DynamicCommandInstance^ DynamicCommand::CreateCommand(String^ name, String^ description, MC::CommandPermissionLevel permission, MC::CommandFlag^ flag1, MC::CommandFlag^ flag2)
    {
        auto handle = CALLING_MODULE;
        auto ret = gcnew DynamicCommandInstance(::DynamicCommand::createCommand(marshalString(name), marshalString(description), ::CommandPermissionLevel(permission), (::CommandFlag)flag1, (::CommandFlag)flag2, handle).release(), true);

        PluginOwnData::AddRegisteredCommand(static_cast<nint_t>(handle), name);

        return ret;
    }
    inline DynamicCommandInstance^ DynamicCommand::CreateCommand(String^ name, String^ description, MC::CommandPermissionLevel permission, MC::CommandFlag^ flag1)
    {
        MC::CommandFlag^ flag = gcnew MC::CommandFlag;
        flag->value = MC::CommandFlagValue(0);
        return CreateCommand(name, description, permission, flag1, flag);
    }
    inline DynamicCommandInstance^ DynamicCommand::CreateCommand(String^ name, String^ description, MC::CommandPermissionLevel permission)
    {
        MC::CommandFlag^ flag = gcnew MC::CommandFlag;
        flag->value = MC::CommandFlagValue(128);
        return CreateCommand(name, description, permission, flag);
    }
    inline DynamicCommandInstance^ DynamicCommand::CreateCommand(String^ name, String^ description)
    {
        return CreateCommand(name, description, MC::CommandPermissionLevel::GameMasters);
    }
    DynamicCommand::CallBackFnManager::CallBackFnManager(CallBackFn^ callback)
    {
        this->callback = callback;
    }
    void NATIVECALLBACK DynamicCommand::CallBackFnManager::NativeCallbackFunc(
        ::DynamicCommand const& cmd,
        ::CommandOrigin const& origin,
        ::CommandOutput& output,
        std::unordered_map<std::string, ::DynamicCommand::Result>& results)
    {
        auto dictionary = gcnew Dictionary<String^, DynamicCommand::Result^>((int)results.size());
        for (auto iter = results.begin(); iter != results.end(); ++iter)
            dictionary->Add(
                marshalString(iter->first),
                gcnew DynamicCommand::Result(std::move(iter->second)));

        callback(gcnew DynamicCommand((::DynamicCommand*)&cmd),
            gcnew MC::CommandOrigin((::CommandOrigin*)&origin),
            gcnew MC::CommandOutput((::CommandOutput*)&output),
            dictionary);
    }
    DynamicCommand::CallBackFnManager::pNativeCallBackFn DynamicCommand::CallBackFnManager::Create(CallBackFn^ callback)
    {
        auto manager = gcnew CallBackFnManager(callback);

        NativeCallBackFn^ nativecallback = gcnew NativeCallBackFn(manager, &DynamicCommand::CallBackFnManager::NativeCallbackFunc);
        gchList->Add(GCHandle::Alloc(nativecallback));

        pNativeCallBackFn pFn = static_cast<pNativeCallBackFn>(Marshal::GetFunctionPointerForDelegate(nativecallback).ToPointer());
        return pFn;
    }
} // namespace LiteLoader::DynamicCommand
