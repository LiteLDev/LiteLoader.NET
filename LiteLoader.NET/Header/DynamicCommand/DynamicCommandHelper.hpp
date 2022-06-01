#pragma once
#include "DynamicCommand.h"

namespace LLNET::DynamicCommand::Internal {
	public ref class CommandManager {
	public:
		value struct EnumInfo {
			String^ Name;
			Dictionary<String^, Object^>^ enums;
			System::Type^ Type;
		};

		value struct ParamInfo {
			String^ Name;
			DynamicCommand::ParameterType ParamType;
			bool IsMandatory;
			List<int>^ OverloadIds;
			String^ EnumName;
			String^ Identifier;
			MC::CommandParameterOption Option;
			System::Reflection::FieldInfo^ Fieldinfo;
			System::Reflection::PropertyInfo^ PropertyInfo;
			bool IsField;
		};

		ref struct CommandData
		{
			ICommand^ cmd;
			::DynamicCommandInstance const* instance = nullptr;
			List<EnumInfo>^ Enums = gcnew List<EnumInfo>;
			List<ParamInfo>^ Parameters = gcnew List<ParamInfo>;
			List<String^>^ Alias = gcnew List<String^>;
			System::Type^ CmdType;
			bool autoReset;
		};

	internal:
		ref struct NativeDynamicCommandCallback
		{
			CommandData^ data;
			GCHandle gch;

			delegate void delCallback(::DynamicCommand const& cmd, ::CommandOrigin const& origin, ::CommandOutput& output, std::unordered_map<std::string, ::DynamicCommand::Result>& results);
			typedef void (*pCallback)(::DynamicCommand const& cmd, ::CommandOrigin const& origin, ::CommandOutput& output, std::unordered_map<std::string, ::DynamicCommand::Result>& results);

			void NativeCallback(::DynamicCommand const& cmd, ::CommandOrigin const& origin, ::CommandOutput& output, std::unordered_map<std::string, ::DynamicCommand::Result>& results);

			~NativeDynamicCommandCallback() {
				if (gch.IsAllocated)
					gch.Free();
				delete data;
			}

			System::Object^ _parseResult(::DynamicCommand::Result& result, ParamInfo% paramInfo);
		};

		static List<NativeDynamicCommandCallback^>^ callbackInstance = gcnew List<NativeDynamicCommandCallback^>;
	};
}
