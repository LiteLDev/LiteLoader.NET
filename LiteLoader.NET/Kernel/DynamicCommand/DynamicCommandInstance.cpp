#include <LiteLoader.NET/Header/DynamicCommand/DynamicCommandInstance.hpp>
#include <LiteLoader.NET/Main/PluginOwnData.hpp>

namespace LiteLoader::DynamicCommand
{
    DynamicCommandInstance^ DynamicCommandInstance::ParameterIndex::Instance::get() {
        return gcnew DynamicCommandInstance(NativePtr->instance);
    }
    void DynamicCommandInstance::ParameterIndex::Instance::set(DynamicCommandInstance^ value) {
        NativePtr->instance = value->NativePtr;
    }
    size_t DynamicCommandInstance::ParameterIndex::Index::get() {
        return NativePtr->index;
    }
    void DynamicCommandInstance::ParameterIndex::Index::set(size_t value) {
        NativePtr->index = value;
    }
    inline DynamicCommandInstance::ParameterIndex^ DynamicCommandInstance::ParameterIndex::Create(DynamicCommandInstance^ instance, size_t index)
    {
        return gcnew ParameterIndex(::DynamicCommandInstance::ParameterIndex(instance, index));
    }
    inline DynamicCommandInstance::ParameterIndex::operator size_t()
    {
        return NativePtr->operator size_t();
    }
    inline DynamicCommand::ParameterData^ DynamicCommandInstance::ParameterIndex::GetParameterData()
    {
        return gcnew DynamicCommand::ParameterData(NativePtr->operator->());
    }
    inline bool DynamicCommandInstance::ParameterIndex::IsValid()
    {
        return NativePtr->isValid();
    }
    inline size_t DynamicCommandInstance::CommandSize::get() {
        return NativePtr->commandSize;
    }
    inline void DynamicCommandInstance::CommandSize::set(size_t value) {
        NativePtr->commandSize = value;
    }
    Dictionary<String^, DynamicCommand::ParameterPtr^>^ DynamicCommandInstance::ParameterPtrs::get()
    {
        auto& ptrs = (*NativePtr).parameterPtrs;
        auto ret = gcnew Dictionary<String^, DynamicCommand::ParameterPtr^>((int)ptrs.size());
        for (auto& kv : ptrs)
            ret->Add(marshalString(kv.first), gcnew DynamicCommand::ParameterPtr(std::move(kv.second)));
        return ret;
    }
    void DynamicCommandInstance::ParameterPtrs::set(Dictionary<String^, DynamicCommand::ParameterPtr^>^ val)
    {
        std::unordered_map<std::string, ::DynamicCommand::ParameterPtr> map;
        for each (auto var in val)
            map.emplace(marshalString(var.Key), *var.Value->NativePtr);
        (*NativePtr).parameterPtrs = std::move(map);
    }
    DynamicCommandInstance::DynamicCommandInstance(String^ name, String^ description, MC::CommandPermissionLevel permission, MC::CommandFlag^ flag, IntPtr handle)
        :ClassTemplate(::DynamicCommandInstance::create(
            marshalString(name),
            marshalString(description),
            ::CommandPermissionLevel(permission),
            ::CommandFlag{ (::CommandFlagValue(flag->value)) },
            (HMODULE)(void*)handle)
            .release(),
            true)
    {
    }
    DynamicCommandInstance::DynamicCommandInstance(String^ name, String^ description, MC::CommandPermissionLevel permission, MC::CommandFlag^ flag)
        :ClassTemplate(::DynamicCommandInstance::create(
            marshalString(name),
            marshalString(description),
            ::CommandPermissionLevel(permission),
            ::CommandFlag{ (::CommandFlagValue(flag->value)) },
            CALLING_MODULE).release(),
            true)
    {
    }
    inline DynamicCommandInstance^ DynamicCommandInstance::Create(String^ name, String^ description, MC::CommandPermissionLevel permission, MC::CommandFlag^ flag, IntPtr handle)
    {
        return gcnew DynamicCommandInstance(name, description, permission, flag, handle);
    }
    inline DynamicCommandInstance^ DynamicCommandInstance::Create(String^ name, String^ description, MC::CommandPermissionLevel permission, MC::CommandFlag^ flag)
    {
        return gcnew DynamicCommandInstance(name, description, permission, flag);
    }
    inline String^ DynamicCommandInstance::SetEnum(String^ description, List<String^>^ values)
    {
        std::vector<std::string> stringvector;
        for each (auto var in values)
            stringvector.emplace_back(marshalString(var));
        return marshalString((*NativePtr).setEnum(marshalString(description), stringvector));
    }
    inline String^ DynamicCommandInstance::GetEnumValue(int index)
    {
        return marshalString((*NativePtr).getEnumValue(index));
    }
    inline DynamicCommandInstance::ParameterIndex^ DynamicCommandInstance::NewParameter(DynamicCommand::ParameterData^ data)
    {
        auto ret = gcnew DynamicCommandInstance::ParameterIndex((*NativePtr).newParameter(std::move(*data->NativePtr)));
        return ret;
    }
    inline DynamicCommandInstance::ParameterIndex^ DynamicCommandInstance::NewParameter(String^ name, DynamicCommand::ParameterType type, bool optional, String^ description, String^ identifier, MC::CommandParameterOption parameterOption)
    {
        return gcnew DynamicCommandInstance::ParameterIndex((*NativePtr).newParameter(marshalString(name),
            ::DynamicCommand::ParameterType(type),
            optional,
            marshalString(description),
            marshalString(identifier),
            ::CommandParameterOption(parameterOption)));
    }
    inline DynamicCommandInstance::ParameterIndex^ DynamicCommandInstance::NewParameter(String^ name, DynamicCommand::ParameterType type, bool optional, String^ description, String^ identifier)
    {
        return gcnew DynamicCommandInstance::ParameterIndex((*NativePtr).newParameter(marshalString(name),
            ::DynamicCommand::ParameterType(type),
            optional,
            marshalString(description),
            marshalString(identifier)));
    }
    inline DynamicCommandInstance::ParameterIndex^ DynamicCommandInstance::NewParameter(String^ name, DynamicCommand::ParameterType type, bool optional, String^ description)
    {
        return gcnew DynamicCommandInstance::ParameterIndex((*NativePtr).newParameter(marshalString(name),
            ::DynamicCommand::ParameterType(type),
            optional,
            marshalString(description)));
    }
    inline DynamicCommandInstance::ParameterIndex^ DynamicCommandInstance::NewParameter(String^ name, DynamicCommand::ParameterType type, bool optional)
    {
        return gcnew DynamicCommandInstance::ParameterIndex((*NativePtr).newParameter(marshalString(name),
            ::DynamicCommand::ParameterType(type),
            optional));
    }
    inline DynamicCommandInstance::ParameterIndex^ DynamicCommandInstance::NewParameter(String^ name, DynamicCommand::ParameterType type)
    {
        return gcnew DynamicCommandInstance::ParameterIndex((*NativePtr).newParameter(marshalString(name),
            ::DynamicCommand::ParameterType(type)));
    }
    inline DynamicCommandInstance::ParameterIndex^ DynamicCommandInstance::FindParameterIndex(String^ param)
    {
        return gcnew DynamicCommandInstance::ParameterIndex((*NativePtr).findParameterIndex(marshalString(param)));
    }
    inline DynamicCommandInstance::ParameterIndex^ DynamicCommandInstance::Mandatory(String^ name, DynamicCommand::ParameterType type, String^ description, String^ identifier, MC::CommandParameterOption parameterOption)
    {
        return gcnew DynamicCommandInstance::ParameterIndex((*NativePtr).mandatory(
            marshalString(name),
            ::DynamicCommand::ParameterType(type),
            marshalString(description),
            marshalString(identifier),
            ::CommandParameterOption(parameterOption)));
    }
    inline DynamicCommandInstance::ParameterIndex^ DynamicCommandInstance::Mandatory(String^ name, DynamicCommand::ParameterType type, String^ description, String^ identifier)
    {
        return gcnew DynamicCommandInstance::ParameterIndex((*NativePtr).mandatory(
            marshalString(name),
            ::DynamicCommand::ParameterType(type),
            marshalString(description),
            marshalString(identifier)));
    }
    inline DynamicCommandInstance::ParameterIndex^ DynamicCommandInstance::Mandatory(String^ name, DynamicCommand::ParameterType type, String^ description, MC::CommandParameterOption parameterOption)
    {
        return gcnew DynamicCommandInstance::ParameterIndex((*NativePtr).mandatory(
            marshalString(name),
            ::DynamicCommand::ParameterType(type),
            marshalString(description)));
    }
    inline DynamicCommandInstance::ParameterIndex^ DynamicCommandInstance::Mandatory(String^ name, DynamicCommand::ParameterType type, String^ description)
    {
        return gcnew DynamicCommandInstance::ParameterIndex((*NativePtr).mandatory(
            marshalString(name),
            ::DynamicCommand::ParameterType(type),
            marshalString(description)));
    }
    inline DynamicCommandInstance::ParameterIndex^ DynamicCommandInstance::Mandatory(String^ name, DynamicCommand::ParameterType type, MC::CommandParameterOption parameterOption)
    {
        return gcnew DynamicCommandInstance::ParameterIndex((*NativePtr).mandatory(
            marshalString(name),
            ::DynamicCommand::ParameterType(type),
            ::CommandParameterOption(parameterOption)));
    }
    inline DynamicCommandInstance::ParameterIndex^ DynamicCommandInstance::Mandatory(String^ name, DynamicCommand::ParameterType type)
    {
        return gcnew DynamicCommandInstance::ParameterIndex((*NativePtr).mandatory(
            marshalString(name),
            ::DynamicCommand::ParameterType(type)));
    }
    inline DynamicCommandInstance::ParameterIndex^ DynamicCommandInstance::Optional(String^ name, DynamicCommand::ParameterType type, String^ description, String^ identifier, MC::CommandParameterOption parameterOption)
    {
        return gcnew DynamicCommandInstance::ParameterIndex((*NativePtr).optional(
            marshalString(name),
            ::DynamicCommand::ParameterType(type),
            marshalString(description),
            marshalString(identifier),
            ::CommandParameterOption(parameterOption)));
    }
    inline DynamicCommandInstance::ParameterIndex^ DynamicCommandInstance::Optional(String^ name, DynamicCommand::ParameterType type, String^ description, String^ identifier)
    {
        return gcnew DynamicCommandInstance::ParameterIndex((*NativePtr).optional(
            marshalString(name),
            ::DynamicCommand::ParameterType(type),
            marshalString(description),
            marshalString(identifier)));
    }
    inline DynamicCommandInstance::ParameterIndex^ DynamicCommandInstance::Optional(String^ name, DynamicCommand::ParameterType type, String^ description, MC::CommandParameterOption parameterOption)
    {
        return gcnew DynamicCommandInstance::ParameterIndex((*NativePtr).optional(
            marshalString(name),
            ::DynamicCommand::ParameterType(type),
            marshalString(description),
            ::CommandParameterOption(parameterOption)));
    }
    inline DynamicCommandInstance::ParameterIndex^ DynamicCommandInstance::Optional(String^ name, DynamicCommand::ParameterType type, String^ description)
    {
        return gcnew DynamicCommandInstance::ParameterIndex((*NativePtr).optional(
            marshalString(name),
            ::DynamicCommand::ParameterType(type),
            marshalString(description)));
    }
    inline DynamicCommandInstance::ParameterIndex^ DynamicCommandInstance::Optional(String^ name, DynamicCommand::ParameterType type, MC::CommandParameterOption parameterOption)
    {
        return gcnew DynamicCommandInstance::ParameterIndex((*NativePtr).optional(
            marshalString(name),
            ::DynamicCommand::ParameterType(type),
            ::CommandParameterOption(parameterOption)));
    }
    inline DynamicCommandInstance::ParameterIndex^ DynamicCommandInstance::Optional(String^ name, DynamicCommand::ParameterType type)
    {
        return gcnew DynamicCommandInstance::ParameterIndex((*NativePtr).optional(
            marshalString(name),
            ::DynamicCommand::ParameterType(type)));
    }
    inline bool DynamicCommandInstance::AddOverload(List<ParameterIndex^>^ params)
    {
        std::vector<::DynamicCommandInstance::ParameterIndex> stdvector;
        for each (auto var in params)
            stdvector.emplace_back(*var->NativePtr);
        return (*NativePtr).addOverload(std::move(stdvector));
    }
    inline bool DynamicCommandInstance::AddOverload(List<String^>^ params)
    {
        std::vector<std::string> stdvector;
        for each (auto var in params)
            stdvector.emplace_back(marshalString(var));
        return (*NativePtr).addOverload(std::move(stdvector));
    }
    inline bool DynamicCommandInstance::AddOverload(List<DynamicCommand::ParameterData^>^ params)
    {
        std::vector<::DynamicCommand::ParameterData> stdvector;
        for each (auto var in params)
            stdvector.emplace_back(*var->NativePtr);
        return (*NativePtr).addOverload(std::move(stdvector));
    }

    inline bool DynamicCommandInstance::SetAlias(String^ alias)
    {
        return (*NativePtr).setAlias(marshalString(alias));
    }

    // inline List<MC::CommandParameterData^>^ DynamicCommandInstance::buildOverload(List<ParameterIndex^>^ overload)
    //{
    //    std::vector<::DynamicCommandInstance::ParameterIndex> stdvector;
    //    for each (auto var in overload)
    //        stdvector.emplace_back(var->DeReference());
    //    auto& _ret = (*NativePtr).buildOverload(stdvector);
    //    stdvector.~vector();
    //    auto ret = gcnew List<MC::CommandParameterData^>((int)_ret.size());
    //    for (auto iter = _ret.begin(); iter != _ret.end(); ++iter)
    //        ret->Add(gcnew MC::CommandParameterData(std::move(*iter)));
    //    return ret;
    // }

    inline void DynamicCommandInstance::SetCallback(DynamicCommand::CallBackFn^ callback)
    {
        (*NativePtr).setCallback(DynamicCommand::CallBackFnManager::Create(callback));
    }

    inline void DynamicCommandInstance::RemoveCallback()
    {
        (*NativePtr).removeCallback();
    }

    inline String^ DynamicCommandInstance::SetSoftEnum(String^ name, List<String^>^ values)
    {
        std::vector<std::string> stdvector;
        for each (auto var in values)
            stdvector.emplace_back(marshalString(var));
        return marshalString((*NativePtr).setSoftEnum(marshalString(name), stdvector));
    }

    inline bool DynamicCommandInstance::AddSoftEnumValues(String^ name, List<String^>^ values)
    {
        std::vector<std::string> stdvector;
        for each (auto var in values)
            stdvector.emplace_back(marshalString(var));
        return (*NativePtr).addSoftEnumValues(marshalString(name), stdvector);
    }

    inline bool DynamicCommandInstance::RemoveSoftEnumValues(String^ name, List<String^>^ values)
    {
        std::vector<std::string> stdvector;
        for each (auto var in values)
            stdvector.emplace_back(marshalString(var));
        return (*NativePtr).removeSoftEnumValues(marshalString(name), stdvector);
    }

    inline List<String^>^ DynamicCommandInstance::GetSoftEnumValues(String^ name)
    {
        auto& stdvector = ::DynamicCommandInstance::getSoftEnumValues(marshalString(name));
        auto ret = gcnew List<String^>((int)stdvector.size());
        for (auto iter = stdvector.begin(); iter != stdvector.end(); ++iter)
            ret->Add(marshalString(*iter));
        return ret;
    }

    inline List<String^>^ DynamicCommandInstance::GetSoftEnumNames()
    {
        auto& stdvector = ::DynamicCommandInstance::getSoftEnumNames();
        auto ret = gcnew List<String^>((int)stdvector.size());
        for (auto iter = stdvector.begin(); iter != stdvector.end(); ++iter)
            ret->Add(marshalString(*iter));
        return ret;
    }

    inline String^ DynamicCommandInstance::GetCommandName()
    {
        return marshalString((*NativePtr).getCommandName());
    }

    inline bool DynamicCommandInstance::HasRegistered()
    {
        return (*NativePtr).hasRegistered();
    }

    List<LiteLoader::NET::Std::string^>^ DynamicCommandInstance::EnumNames::get() {
        auto& vec = NativePtr->enumNames;
        auto ret = gcnew List<LiteLoader::NET::Std::string^>((int)vec.size());
        for (auto& v : vec) {
            ret->Add(gcnew LiteLoader::NET::Std::string(v.release(), true));
        }
        return ret;
    }

    //void DynamicCommandInstance::EnumNames::set(List<LiteLoader::NET::Std::string^>^ value) {
    //    std::vector<std::unique_ptr<std::string>> vec;
    //    for each (auto var in value)
    //    {
    //        vec.emplace_back(std::make_unique<std::string>(var->Release()));
    //    }
    //    NativePtr->enumNames = vec;
    //}
}