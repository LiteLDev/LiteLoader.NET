#pragma once
#include <LiteLoader.NET/Main/DotNETGlobal.hpp>
#include <LiteLoader.NET/Main/ClassTemplate.hpp>
#include <LiteLoader.NET/Header/Core/STLHelper/string.hpp>
#include <LiteLoader.NET/Header/DynamicCommand/DynamicCommand.hpp>
#include <DynamicCommandAPI.h>

namespace LiteLoader::DynamicCommand {
	interface class ICommand;
	interface class ICommandEvent;
	interface class ICommandData;
}

namespace LiteLoader::DynamicCommand
{
	public ref class DynamicCommandInstance : ClassTemplate<DynamicCommandInstance, ::DynamicCommandInstance>
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
		property List<LiteLoader::NET::Std::string^>^ EnumNames { List<LiteLoader::NET::Std::string^>^ get(); /*void set(List<LiteLoader::NET::Std::string^>^ val);*/ };

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
		DynamicCommandInstance(String^ name, String^ description, MC::CommandPermissionLevel permission, MC::CommandFlag^ flag, IntPtr handle);
		DynamicCommandInstance(String^ name, String^ description, MC::CommandPermissionLevel permission, MC::CommandFlag^ flag);

		inline static DynamicCommandInstance^ Create(String^ name, String^ description, MC::CommandPermissionLevel permission, MC::CommandFlag^ flag, IntPtr handle);
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
}