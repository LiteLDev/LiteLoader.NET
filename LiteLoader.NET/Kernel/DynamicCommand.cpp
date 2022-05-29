#include "../Header/DynamicCommand/DynamicCommand.h"
#include <memory>

namespace LLNET::DynamicCommand
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
			return gcnew MC::BlockPos(NativePtr->get<BlockPos>());
		}
		case ::DynamicCommand::ParameterType::Vec3:
		{
			return gcnew MC::Vec3(NativePtr->get<Vec3>());
		}
		case ::DynamicCommand::ParameterType::Message:
			return marshalString(NativePtr->getRaw<::CommandMessage>().getMessage(*NativePtr->origin));
		case ::DynamicCommand::ParameterType::RawText:
			return marshalString(NativePtr->getRaw<std::string>());
		case ::DynamicCommand::ParameterType::JsonValue:
			return marshalString(JsonHelpers::serialize(NativePtr->getRaw<Json::Value>()));
		case ::DynamicCommand::ParameterType::Item:
			return gcnew MC::ItemInstance(NativePtr->getRaw<CommandItem>().createInstance(1, 1, nullptr, true).value_or(ItemInstance::EMPTY_ITEM));
		case ::DynamicCommand::ParameterType::Block:
			return gcnew MC::Block(const_cast<Block*>(NativePtr->getRaw<Block const*>()));
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
		if (NativePtr->isSet || NativePtr->type != ::DynamicCommand::ParameterType::Bool)
			throw gcnew DynamicCommandInvalidCastException;
		return NativePtr->getRaw<bool>();
	}
	inline int DynamicCommand::Result::AsInt() {
		if (NativePtr->isSet || NativePtr->type != ::DynamicCommand::ParameterType::Int)
			throw gcnew DynamicCommandInvalidCastException;
		return NativePtr->getRaw<int>();
	}
	inline float DynamicCommand::Result::AsFloat() {
		if (NativePtr->isSet || NativePtr->type != ::DynamicCommand::ParameterType::Float)
			throw gcnew DynamicCommandInvalidCastException;
		return NativePtr->getRaw<float>();
	}
	inline String^ DynamicCommand::Result::AsString() {
		if (NativePtr->isSet || NativePtr->type != ::DynamicCommand::ParameterType::Float)
			throw gcnew DynamicCommandInvalidCastException;
		return marshalString<Encoding::E_UTF8>(NativePtr->getRaw<std::string>());
	}
	inline List<MC::Actor^>^ DynamicCommand::Result::AsActorList() {
		if (NativePtr->isSet || NativePtr->type != ::DynamicCommand::ParameterType::Actor)
			throw gcnew DynamicCommandInvalidCastException;
		auto arr = gcnew List<MC::Actor^>;
		for (auto i : NativePtr->get<std::vector<::Actor*>>())
		{
			arr->Add(gcnew MC::Actor(i));
		}
		return arr;
	}
	inline List<MC::Player^>^ DynamicCommand::Result::AsPlayerList() {
		if (NativePtr->isSet || NativePtr->type != ::DynamicCommand::ParameterType::Player)
			throw gcnew DynamicCommandInvalidCastException;
		auto arr = gcnew List<MC::Player^>;
		for (auto i : NativePtr->get<std::vector<::Player*>>())
		{
			arr->Add(gcnew MC::Player(i));
		}
		return arr;
	}
	inline MC::BlockPos^ DynamicCommand::Result::AsBlockPos() {
		if (NativePtr->isSet || NativePtr->type != ::DynamicCommand::ParameterType::BlockPos)
			throw gcnew DynamicCommandInvalidCastException;
		return gcnew MC::BlockPos(NativePtr->get<::BlockPos>());
	}
	inline MC::Vec3^ DynamicCommand::Result::AsVec3() {
		if (NativePtr->isSet || NativePtr->type != ::DynamicCommand::ParameterType::Vec3)
			throw gcnew DynamicCommandInvalidCastException;
		return gcnew MC::Vec3(NativePtr->get<::Vec3>());
	}
	inline MC::CommandMessage^ DynamicCommand::Result::AsCommandMessage() {
		if (NativePtr->isSet || NativePtr->type != ::DynamicCommand::ParameterType::Message)
			throw gcnew DynamicCommandInvalidCastException;
		return gcnew MC::CommandMessage(const_cast<::CommandMessage*>(&NativePtr->getRaw<::CommandMessage>()));
	}
	inline String^ DynamicCommand::Result::AsRawText() {
		if (NativePtr->isSet || NativePtr->type != ::DynamicCommand::ParameterType::Enum)
			throw gcnew DynamicCommandInvalidCastException;
		return marshalString(NativePtr->getRaw<std::string>());
	}
	inline String^ DynamicCommand::Result::AsJsonValue() {
		if (NativePtr->isSet || NativePtr->type != ::DynamicCommand::ParameterType::Enum)
			throw gcnew DynamicCommandInvalidCastException;
		return marshalString(NativePtr->getRaw<std::string>());
	}
	inline MC::CommandItem^ DynamicCommand::Result::AsCommandItem() {
		if (NativePtr->isSet || NativePtr->type != ::DynamicCommand::ParameterType::Item)
			throw gcnew DynamicCommandInvalidCastException;
		return gcnew MC::CommandItem(NativePtr->getRaw<CommandItem>());
	}
	inline MC::Block^ DynamicCommand::Result::AsBlock() {
		if (NativePtr->isSet || NativePtr->type != ::DynamicCommand::ParameterType::Block)
			throw gcnew DynamicCommandInvalidCastException;
		return gcnew MC::Block(const_cast<Block*>(NativePtr->getRaw<Block const*>()));
	}
	inline MC::MobEffect^ DynamicCommand::Result::AsMobEffect() {
		if (NativePtr->isSet || NativePtr->type != ::DynamicCommand::ParameterType::Effect)
			throw gcnew DynamicCommandInvalidCastException;
		return gcnew MC::MobEffect(const_cast<::MobEffect*>(NativePtr->getRaw<::MobEffect const*>()));
	}
	inline String^ DynamicCommand::Result::AsEnum() {
		if (NativePtr->isSet || NativePtr->type != ::DynamicCommand::ParameterType::Enum)
			throw gcnew DynamicCommandInvalidCastException;
		return marshalString(NativePtr->getRaw<std::string>());
	}
	inline String^ DynamicCommand::Result::AsSoftEnum() {
		if (NativePtr->isSet || NativePtr->type != ::DynamicCommand::ParameterType::SoftEnum)
			throw gcnew DynamicCommandInvalidCastException;
		return marshalString(NativePtr->getRaw<std::string>());
	}
	inline MC::Command^ DynamicCommand::Result::AsCommand() {
		if (NativePtr->isSet || NativePtr->type != ::DynamicCommand::ParameterType::Command)
			throw gcnew DynamicCommandInvalidCastException;
		return gcnew MC::Command((::__Command*)NativePtr->getRaw<std::unique_ptr<::Command>>().get(), true);
	}
	inline MC::ActorDefinitionIdentifier^ DynamicCommand::Result::AsActorType() {
		if (NativePtr->isSet || NativePtr->type != ::DynamicCommand::ParameterType::ActorType)
			throw gcnew DynamicCommandInvalidCastException;
		return gcnew MC::ActorDefinitionIdentifier((ActorDefinitionIdentifier*)NativePtr->getRaw<ActorDefinitionIdentifier const*>());
	}
	LLNET::DynamicCommand::DynamicCommand::Result::Result(ParameterPtr^ ptr, DynamicCommand^ command, MC::CommandOrigin^ origin, DynamicCommandInstance^ instance)
		:ClassTemplate(::DynamicCommand::Result(ptr->NativePtr, command->NativePtr, origin->NativePtr, instance->NativePtr))
	{
	}
	LLNET::DynamicCommand::DynamicCommand::Result::Result(ParameterPtr^ ptr, DynamicCommand^ command, MC::CommandOrigin^ origin)
		:ClassTemplate(::DynamicCommand::Result(ptr->NativePtr, command->NativePtr, origin->NativePtr))
	{
	}
	LLNET::DynamicCommand::DynamicCommand::Result::Result()
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
	inline DynamicCommandInstance^ DynamicCommand::CreateCommand(String^ name, String^ description, Dictionary<String^, List<String^>^>^ enums, List<ParameterData^>^ params, List<List<String^>^>^ overloads, CallBackFn^ callback, MC::CommandPermissionLevel permission, MC::CommandFlag^ flag1, MC::CommandFlag^ flag2, IntPtr handler)
	{

		if (handler == IntPtr::Zero)
			handler = IntPtr(MODULE);


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
			(HMODULE)(void*)handler)
			.release(),
			true);
	}
	inline DynamicCommandInstance^ DynamicCommand::Setup(DynamicCommandInstance^ commandInstance)
	{
		return gcnew DynamicCommandInstance(
			(::DynamicCommandInstance*)::DynamicCommand::setup(std::unique_ptr<::DynamicCommandInstance>(commandInstance->Release())));
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
		return gcnew ParameterData(name, type, optional, enumOptions, "");
	}
	inline DynamicCommand::ParameterData^ DynamicCommand::ParameterData::Create(String^ name, ParameterType type, bool optional)
	{
		return gcnew ParameterData(name, type, optional, "");
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
		return gcnew ParameterData(name, type, enumOptions, "");
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

	inline DynamicCommand::DynamicCommand(System::IntPtr p)
		: MC::Command(p)
	{
	}
	inline DynamicCommand::DynamicCommand(System::IntPtr p, bool ownsNativeInstance)
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

	inline DynamicCommandInstance^ DynamicCommand::CreateCommand(String^ name, String^ description, MC::CommandPermissionLevel permission, MC::CommandFlag^ flag1, MC::CommandFlag^ flag2, IntPtr handler)
	{
		return gcnew DynamicCommandInstance(::DynamicCommand::createCommand(marshalString(name), marshalString(description), ::CommandPermissionLevel(permission), flag1, flag2, (HMODULE)(void*)handler).release(), true);
	}
	inline DynamicCommandInstance^ DynamicCommand::CreateCommand(String^ name, String^ description, MC::CommandPermissionLevel permission, MC::CommandFlag^ flag1, MC::CommandFlag^ flag2)
	{
		auto& a = ::DynamicCommand::createCommand(marshalString(name), marshalString(description), ::CommandPermissionLevel(permission), (::CommandFlag)flag1, (::CommandFlag)flag2, MODULE);
		return gcnew DynamicCommandInstance(a.release(), true);
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

		pNativeCallBackFn pFn = static_cast<pNativeCallBackFn>((void*)Marshal::GetFunctionPointerForDelegate(nativecallback));
		return pFn;
	}
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
	DynamicCommandInstance::DynamicCommandInstance(String^ name, String^ description, MC::CommandPermissionLevel permission, MC::CommandFlag^ flag, IntPtr handler)
		:ClassTemplate(::DynamicCommandInstance::create(
			marshalString(name),
			marshalString(description),
			::CommandPermissionLevel(permission),
			::CommandFlag{ (::CommandFlagValue(flag->value)) },
			(HMODULE)(void*)handler)
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
			MODULE).release(),
			true)
	{
	}
	inline DynamicCommandInstance^ DynamicCommandInstance::Create(String^ name, String^ description, MC::CommandPermissionLevel permission, MC::CommandFlag^ flag, IntPtr handler)
	{
		return gcnew DynamicCommandInstance(name, description, permission, flag, handler);
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
	//	std::vector<::DynamicCommandInstance::ParameterIndex> stdvector;
	//	for each (auto var in overload)
	//		stdvector.emplace_back(var->DeReference());
	//	auto& _ret = (*NativePtr).buildOverload(stdvector);
	//	stdvector.~vector();
	//	auto ret = gcnew List<MC::CommandParameterData^>((int)_ret.size());
	//	for (auto iter = _ret.begin(); iter != _ret.end(); ++iter)
	//		ret->Add(gcnew MC::CommandParameterData(std::move(*iter)));
	//	return ret;
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
		return (*NativePtr).addSoftEnumValues(marshalString(name), stdvector);
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

	List<LLNET::Core::Std::string^>^ DynamicCommandInstance::EnumNames::get() {
		auto& vec = NativePtr->enumNames;
		auto ret = gcnew List<LLNET::Core::Std::string^>((int)vec.size());
		for (auto& v : vec) {
			ret->Add(gcnew LLNET::Core::Std::string(v.release(), true));
		}
		return ret;
	}

	//void DynamicCommandInstance::EnumNames::set(List<LLNET::Core::Std::string^>^ value) {
	//	std::vector<std::unique_ptr<std::string>> vec;
	//	for each (auto var in value)
	//	{
	//		vec.emplace_back(std::make_unique<std::string>(var->Release()));
	//	}
	//	NativePtr->enumNames = vec;
	//}

} // namespace LLNET::DynamicCommand

inline ::DynamicCommand::ParameterType __ParameterData::GetType()
{
	return type;
}

inline void __ParameterData::SetType(::DynamicCommand::ParameterType t)
{
	type = t;
}

inline size_t __ParameterData::GetOffset()
{
	return offset;
}

inline void __ParameterData::SetOffest(size_t o)
{
	offset = o;
}

inline std::string __ParameterData::GetName()
{
	return name;
}

inline void __ParameterData::SetName(std::string& s)
{
	name = s;
}

inline std::string __ParameterData::GetDescription()
{
	return description;
}

inline void __ParameterData::SetDescription(std::string& s)
{
	description = s;
}

inline std::string __ParameterData::GetIdentifier()
{
	return identifier;
}

inline void __ParameterData::SetIdentifier(std::string& s)
{
	identifier = s;
}

inline bool __ParameterData::GetOptional()
{
	return option;
}

inline void __ParameterData::SetOptional(bool b)
{
	optional = b;
}

inline CommandParameterOption __ParameterData::GetOption()
{
	return option;
}

inline void __ParameterData::SetOption(CommandParameterOption o)
{
	option = o;
}

inline __ParameterData::__ParameterData(__ParameterData const& p)
	: ParameterData(p)
{
}

inline __ParameterData::__ParameterData(std::string const& name, ::DynamicCommand::ParameterType type, bool optional, std::string const& enumOptions, std::string const& identifier, CommandParameterOption parameterOption)
	: Base(name, type, optional, enumOptions, identifier, parameterOption)
{
}

inline __ParameterData::__ParameterData(std::string const& name, ::DynamicCommand::ParameterType type, std::string const& enumOptions, std::string const& identifier, CommandParameterOption parameterOption)
	: Base(name, type, enumOptions, identifier, parameterOption)
{
}
