#pragma once
#include "DynamicCommand.h"

namespace LLNET::DynamicCommand::Internal {
	public ref class CommandManager {
	public:
		value struct EnumInfo {
			String^ Name;
			Dictionary<String^, long>^ enums;
			System::Type^ Type;
		};

		value struct ParamInfo {
			String^ Name;
			DynamicCommand::ParameterType ParamType;
			bool IsMandatory;
			String^ EnumName;
			String^ Identifier;
			MC::CommandParameterOption Option;
			System::Type^ Type;
		};

		ref struct CommandData
		{
			ICommand^ cmd;
			::DynamicCommandInstance const* instance = nullptr;
			List<EnumInfo>^ Enums = gcnew List<EnumInfo>;
			List<ParamInfo>^ Parameters = gcnew List<ParamInfo>;
			List<String^>^ Alias = gcnew List<String^>;
			System::Type^ CmdType;
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
		};

		static List<NativeDynamicCommandCallback^>^ callbackInstance = gcnew List<NativeDynamicCommandCallback^>;
	};
}

void LLNET::DynamicCommand::Internal::CommandManager::NativeDynamicCommandCallback::NativeCallback(::DynamicCommand const& cmd, ::CommandOrigin const& origin, ::CommandOutput& output, std::unordered_map<std::string, ::DynamicCommand::Result>& results)
{
}
