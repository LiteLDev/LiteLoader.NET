#pragma once
#include <DynamicCommandAPI.h>
#include "../Main/.NETGlobal.hpp"
#include "../Tools/PropertryHelper.h"
#include "../Header/Command/Command.hpp"
#include "../Header/Command/CommandOrigin.hpp"
#include "../Header/Command/CommandParameterData.hpp"
#include "../Header/Command/CommandOutput.hpp"
#include "../Header/Command/CommandMessage.hpp"
#include "../Header/Command/CommandItem.hpp"
#include "../Header/MC/Player.hpp"
#include "../Header/MC/BlockPos.hpp"
#include "../Header/MC/Vec3.hpp"
#include "../Header/MC/ItemStack.hpp"
#include "../Header/MC/Block.hpp"
#include "../Header/MC/Command.hpp"
#include "../Header/MC/ActorDefinitionIdentifier.hpp"
#include "../Core/STLHelper/string.hpp"
#include <MC/JsonHelpers.hpp>

struct __ParameterData : public ::DynamicCommand::ParameterData
{
public:
	using Base = ParameterData;
	inline ::DynamicCommand::ParameterType GetType();
	inline void SetType(::DynamicCommand::ParameterType t);
	inline size_t GetOffset();
	inline void SetOffest(size_t o);
	inline std::string GetName();
	inline void SetName(std::string& s);
	inline std::string GetDescription();
	inline void SetDescription(std::string& s);
	inline std::string GetIdentifier();
	inline void SetIdentifier(std::string& s);
	inline bool GetOptional();
	inline void SetOptional(bool b);
	inline CommandParameterOption GetOption();
	inline void SetOption(CommandParameterOption o);
	__ParameterData() = delete;
	__ParameterData(__ParameterData const& p);
	__ParameterData(std::string const& name, ::DynamicCommand::ParameterType type, bool optional = false, std::string const& enumOptions = "", std::string const& identifier = "", CommandParameterOption parameterOption = (CommandParameterOption)0);
	__ParameterData(std::string const& name, ::DynamicCommand::ParameterType type, std::string const& enumOptions = "", std::string const& identifier = "", CommandParameterOption parameterOption = (CommandParameterOption)0);
};

namespace LLNET::DynamicCommand {
	interface class ICommand;
	interface class ICommandEvent;
	interface class ICommandData;
}

namespace LLNET::DynamicCommand
{
	using namespace LLNET::Core;

	ref class DynamicCommandInstance;
	public
	ref class DynamicCommand : public MC::Command
	{
	public:
		//__ctor_base(DynamicCommand, ::DynamicCommand, MC::Command);
		DynamicCommand(System::IntPtr p);
		DynamicCommand(System::IntPtr p, bool ownsNativeInstance);
		DynamicCommand(::DynamicCommand* p);
		DynamicCommand(::DynamicCommand* p, bool ownsNativeInstance);
	property ::DynamicCommand* NativePtr { public: ::DynamicCommand* get(); protected: void set(::DynamicCommand* value); };

	public:
		ref struct ParameterPtr;
		enum class ParameterType
		{
			Bool,             /// bool
			Int,              /// int
			Float,            /// float
			String,           /// std::string
			Actor,            /// CommandSelector<Actor>
			Player,           /// CommandSelector<Player>
			BlockPos,         /// CommandPosition
			Vec3,             /// CommandPositionFloat
			RawText,          /// CommandRawText
			Message,          /// CommandMessage
			JsonValue,        /// Json::Value
			Item,             /// CommandItem
			Block,            /// Block const*
			Effect,           /// MobEffect const*
			Enum,             /// ENUM
			SoftEnum,         /// SOFT_ENUM
			ActorType,        /// ActorDefinitionIdentifier const*
			Command,          /// std::unique_ptr<Command>
			WildcardSelector, /// WildcardCommandSelector<Actor>
		};
		ref struct Result : ClassTemplate<Result, ::DynamicCommand::Result>
		{
		public:
			__ctor_all(Result, ::DynamicCommand::Result);

			property DynamicCommand^ Command { DynamicCommand^ get(); };
			property DynamicCommandInstance^ Instance { DynamicCommandInstance^ get(); };
			property MC::CommandOrigin^ Origin { MC::CommandOrigin^ get(); };
			property ParameterType Type { ParameterType get(); };
			property size_t Offset { size_t get(); };
			property bool IsSet { bool get(); };

			Object^ Get();

			bool AsBool();
			int AsInt();
			float AsFloat();
			String^ AsString();
			List<MC::Actor^>^ AsActorList();
			List<MC::Player^>^ AsPlayerList();
			MC::BlockPos^ AsBlockPos();
			MC::Vec3^ AsVec3();
			MC::CommandMessage^ AsCommandMessage();
			String^ AsRawText();
			String^ AsJsonValue();
			MC::CommandItem^ AsCommandItem();
			MC::Block^ AsBlock();
			MC::MobEffect^ AsMobEffect();
			String^ AsEnum();
			String^ AsSoftEnum();
			MC::Command^ AsCommand();
			MC::ActorDefinitionIdentifier^ AsActorType();


			Result(ParameterPtr^ NativePtr, DynamicCommand^ command, MC::CommandOrigin^ origin, DynamicCommandInstance^ instance);
			Result(ParameterPtr^ NativePtr, DynamicCommand^ command, MC::CommandOrigin^ origin);
			Result();

			inline static Result^ Create(ParameterPtr^ ptr, DynamicCommand^ command, MC::CommandOrigin^ origin, DynamicCommandInstance^ instance);
			inline static Result^ Create(ParameterPtr^ ptr, DynamicCommand^ command, MC::CommandOrigin^ origin);
			inline static Result^ Create();
			property String^ EnumValue { String^ get(); };
			property String^ Name { String^ get(); };
			ParameterType GetParameterType();
			String^ ToDebugString();
			DynamicCommandInstance^ GetInstance();
			String^ ToString() override;
		};

	public:
		ref struct ParameterPtr : ClassTemplate<ParameterPtr, ::DynamicCommand::ParameterPtr>
		{
		public:
			__ctor_all(ParameterPtr, ::DynamicCommand::ParameterPtr);

			ParameterPtr(ParameterType type, size_t offset);

			inline static ParameterPtr^ Create(ParameterType type, size_t offset);
			bool IsValueSet(DynamicCommand^ command);
			Result^ GetResult(DynamicCommand^ command, MC::CommandOrigin^ origin);
			inline size_t GetOffset();
		};

	public:
		ref struct ParameterData : ClassTemplate<ParameterData, ::DynamicCommand::ParameterData>
		{
		public:
			__ctor_all(ParameterData, ::DynamicCommand::ParameterData);

			inline ParameterData(ParameterData^ data);
			inline ParameterData(String^ name, ParameterType type, bool optional, String^ enumOptions, String^ identifier, MC::CommandParameterOption parameterOption);
			inline ParameterData(String^ name, ParameterType type, bool optional, String^ enumOptions, String^ identifier);
			inline ParameterData(String^ name, ParameterType type, bool optional, String^ enumOptions);
			inline ParameterData(String^ name, ParameterType type, bool optional);
			inline ParameterData(String^ name, ParameterType type);
			inline ParameterData(String^ name, ParameterType type, String^ enumOptions, String^ identifier, MC::CommandParameterOption parameterOption);
			inline ParameterData(String^ name, ParameterType type, String^ enumOptions, String^ identifier);
			inline ParameterData(String^ name, ParameterType type, String^ enumOptions);

			inline static ParameterData^ Create(ParameterData^ data);
			inline static ParameterData^ Create(String^ name, ParameterType type, bool optional, String^ enumOptions, String^ identifier, MC::CommandParameterOption parameterOption);
			inline static ParameterData^ Create(String^ name, ParameterType type, bool optional, String^ enumOptions, String^ identifier);
			inline static ParameterData^ Create(String^ name, ParameterType type, bool optional, String^ enumOptions);
			inline static ParameterData^ Create(String^ name, ParameterType type, bool optional);
			inline static ParameterData^ Create(String^ name, ParameterType type);
			inline static ParameterData^ Create(String^ name, ParameterType type, String^ enumOptions, String^ identifier, MC::CommandParameterOption parameterOption);
			inline static ParameterData^ Create(String^ name, ParameterType type, String^ enumOptions, String^ identifier);
			inline static ParameterData^ Create(String^ name, ParameterType type, String^ enumOptions);
			MC::CommandParameterData^ MakeParameterData();
			inline void SetOptional(bool optional);
			inline bool SetEnumOptions(String^ enumOptions);
		};
		/*virtual void execute(class CommandOrigin const& origin, class CommandOutput& output);*/
		inline static DynamicCommandInstance^ CreateCommand(String^ name, String^ description, MC::CommandPermissionLevel permission, MC::CommandFlag^ flag1, MC::CommandFlag^ flag2, IntPtr handler);
		inline static DynamicCommandInstance^ CreateCommand(String^ name, String^ description, MC::CommandPermissionLevel permission, MC::CommandFlag^ flag1, MC::CommandFlag^ flag2);
		inline static DynamicCommandInstance^ CreateCommand(String^ name, String^ description, MC::CommandPermissionLevel permission, MC::CommandFlag^ flag1);
		inline static DynamicCommandInstance^ CreateCommand(String^ name, String^ description, MC::CommandPermissionLevel permission);
		inline static DynamicCommandInstance^ CreateCommand(String^ name, String^ description);

		delegate void CallBackFn(DynamicCommand^ cmd, MC::CommandOrigin^ origin, MC::CommandOutput^ output, Dictionary<String^, Result^>^ results);

	public:
		ref class CallBackFnManager
		{
		private:
			delegate void NativeCallBackFn(::DynamicCommand const&, ::CommandOrigin const&, ::CommandOutput&, std::unordered_map<std::string, ::DynamicCommand::Result>&);
			using pNativeCallBackFn = void (*)(::DynamicCommand const&, CommandOrigin const&, CommandOutput&, std::unordered_map<std::string, ::DynamicCommand::Result>&);
			static List<GCHandle>^ gchList = gcnew List<GCHandle>;
		private:
			CallBackFnManager(CallBackFn^ callback);

			void NATIVECALLBACK NativeCallbackFunc(::DynamicCommand const& cmd,
				::CommandOrigin const& origin,
				::CommandOutput& output,
				std::unordered_map<std::string, ::DynamicCommand::Result>& results);

			CallBackFn^ callback = nullptr;

		public:
			static pNativeCallBackFn Create(CallBackFn^ callback);
		};

	public:
		inline static DynamicCommandInstance^ CreateCommand(
			String^ name,
			String^ description,
			Dictionary<String^, List<String^>^>^ enums,
			List<ParameterData^>^ params,
			List<List<String^>^>^ overloads,
			CallBackFn^ callback,
			MC::CommandPermissionLevel permission,
			MC::CommandFlag^ flag1,
			MC::CommandFlag^ flag2,
			IntPtr handler);

		inline static DynamicCommandInstance^ Setup(DynamicCommandInstance^ commandInstance);
		inline static bool UnregisterCommand(String^ name);
		inline static bool UpdateAvailableCommands();
		inline DynamicCommandInstance^ GetInstance();
		inline static DynamicCommandInstance^ GetInstance(String^ commandName);

		generic<typename TCommand>
		where TCommand:ICommand, gcnew()
			static bool RegisterCommand();
	};
	public
	ref class DynamicCommandInstance : ClassTemplate<DynamicCommandInstance, ::DynamicCommandInstance>
	{
	public:
		__ctor(DynamicCommandInstance, ::DynamicCommandInstance);

	public:
		ref struct ParameterIndex : ClassTemplate<ParameterIndex, ::DynamicCommandInstance::ParameterIndex>
		{
		public:
			__ctor_all(ParameterIndex, ::DynamicCommandInstance::ParameterIndex);

			property DynamicCommandInstance^ Instance { DynamicCommandInstance^ get(); void set(DynamicCommandInstance^ val); };
			property size_t Index { size_t get(); void set(size_t value); };
			inline static ParameterIndex^ Create(DynamicCommandInstance^ instance, size_t index);
			inline operator size_t();
			inline DynamicCommand::ParameterData^ GetParameterData();
			inline bool IsValid();
		};

	public:
		property size_t CommandSize { size_t get(); void set(size_t val); };
		property Dictionary<String^, DynamicCommand::ParameterPtr^>^ ParameterPtrs {Dictionary<String^, DynamicCommand::ParameterPtr^>^ get(); void set(Dictionary<String^, DynamicCommand::ParameterPtr^>^ val); };

		/// <summary>
		/// unique_ptr&lt;std::string&gt;
		/// </summary>
		property List<LLNET::Core::Std::string^>^ EnumNames { List<LLNET::Core::Std::string^>^ get(); /*void set(List<LLNET::Core::Std::string^>^ val);*/ };

		//property List<String^>^ EnumValues {
		//	List<String^>^ get();
		//	void set(List<String^>^ val);
		//};
		//property Dictionary<String^, System::Tuple<size_t, size_t>^>^ EnumRanges {
		//	Dictionary<String^, System::Tuple<size_t, size_t>^>^ get();
		//	void set(Dictionary<String^, System::Tuple<size_t, size_t>^>^ val);
		//};
		//property List<DynamicCommand::ParameterData^>^ ParameterDatas {
		//	List<DynamicCommand::ParameterData^>^ get();
		//	void set(List<DynamicCommand::ParameterData^>^ val);
		//};
		DynamicCommandInstance(String^ name, String^ description, MC::CommandPermissionLevel permission, MC::CommandFlag^ flag, IntPtr handler);
		DynamicCommandInstance(String^ name, String^ description, MC::CommandPermissionLevel permission, MC::CommandFlag^ flag);

		inline static DynamicCommandInstance^ Create(String^ name, String^ description, MC::CommandPermissionLevel permission, MC::CommandFlag^ flag, IntPtr handler);
		inline static DynamicCommandInstance^ Create(String^ name, String^ description, MC::CommandPermissionLevel permission, MC::CommandFlag^ flag);
		inline String^ SetEnum(String^ description, List<String^>^ values);
		inline String^ GetEnumValue(int index);
		inline ParameterIndex^ NewParameter(DynamicCommand::ParameterData^ data);
		inline ParameterIndex^ NewParameter(String^ name, DynamicCommand::ParameterType type, bool optional, String^ description, String^ identifier, MC::CommandParameterOption parameterOption);
		inline ParameterIndex^ NewParameter(String^ name, DynamicCommand::ParameterType type, bool optional, String^ description, String^ identifier);
		inline ParameterIndex^ NewParameter(String^ name, DynamicCommand::ParameterType type, bool optional, String^ description);
		inline ParameterIndex^ NewParameter(String^ name, DynamicCommand::ParameterType type, bool optional);
		inline ParameterIndex^ NewParameter(String^ name, DynamicCommand::ParameterType type);
		inline ParameterIndex^ FindParameterIndex(String^ param);
		inline ParameterIndex^ Mandatory(String^ name, DynamicCommand::ParameterType type, String^ description, String^ identifier, MC::CommandParameterOption parameterOption);
		inline ParameterIndex^ Mandatory(String^ name, DynamicCommand::ParameterType type, String^ description, String^ identifier);
		inline ParameterIndex^ Mandatory(String^ name, DynamicCommand::ParameterType type, String^ description, MC::CommandParameterOption parameterOption);
		inline ParameterIndex^ Mandatory(String^ name, DynamicCommand::ParameterType type, String^ description);
		inline ParameterIndex^ Mandatory(String^ name, DynamicCommand::ParameterType type, MC::CommandParameterOption parameterOption);
		inline ParameterIndex^ Mandatory(String^ name, DynamicCommand::ParameterType type);
		inline ParameterIndex^ Optional(String^ name, DynamicCommand::ParameterType type, String^ description, String^ identifier, MC::CommandParameterOption parameterOption);
		inline ParameterIndex^ Optional(String^ name, DynamicCommand::ParameterType type, String^ description, String^ identifier);
		inline ParameterIndex^ Optional(String^ name, DynamicCommand::ParameterType type, String^ description, MC::CommandParameterOption parameterOption);
		inline ParameterIndex^ Optional(String^ name, DynamicCommand::ParameterType type, String^ description);
		inline ParameterIndex^ Optional(String^ name, DynamicCommand::ParameterType type, MC::CommandParameterOption parameterOption);
		inline ParameterIndex^ Optional(String^ name, DynamicCommand::ParameterType type);

		inline bool AddOverload(List<ParameterIndex^>^ params);
		inline bool AddOverload(List<String^>^ params);
		inline bool AddOverload(List<DynamicCommand::ParameterData^>^ params);
		inline bool SetAlias(String^ alias);
		// inline List<MC::CommandParameterData^>^ buildOverload(List<ParameterIndex^>^ overload);
		inline void SetCallback(DynamicCommand::CallBackFn^ callback);
		inline void RemoveCallback();
		inline String^ SetSoftEnum(String^ name, List<String^>^ values);
		inline bool AddSoftEnumValues(String^ name, List<String^>^ values);
		inline bool RemoveSoftEnumValues(String^ name, List<String^>^ values);
		inline static List<String^>^ GetSoftEnumValues(String^ name);
		inline static List<String^>^ GetSoftEnumNames();

		inline String^ GetCommandName();
		inline bool HasRegistered();
	};
} // namespace LLNET::DynamicCommand