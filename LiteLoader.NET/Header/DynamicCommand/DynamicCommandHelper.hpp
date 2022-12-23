#pragma once
#include <LiteLoader.NET/Main/DotNETGlobal.hpp>
#include "DynamicCommand.hpp"
#include <EventAPI.h>

namespace LiteLoader::DynamicCommand::Internal {
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

            bool isKeyValuePair_with_bool;
            System::Type^ KVPairType;
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
            ~NativeDynamicCommandCallback();
            System::Object^ _parseResult(::DynamicCommand::Result& result, ParamInfo% paramInfo);
        };

        static List<NativeDynamicCommandCallback^>^ callbackInstance = gcnew List<NativeDynamicCommandCallback^>;
        static List<System::Type^>^ unregisteredCmdList = gcnew List<System::Type^>;
        static bool isRegCmdEventRaised = false;

        static bool OnRegCmdEvent(::Event::RegCmdEvent ev);

        CommandManager::CommandManager()
        {
            ::Event::RegCmdEvent::subscribe(OnRegCmdEvent);
        }
    };
}
