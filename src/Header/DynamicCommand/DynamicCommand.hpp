#pragma once
#include <DynamicCommandAPI.h>
#include <src/Main/DotNETGlobal.hpp>
#include <src/Tools/PropertryHelper.hpp>
#include <src/Header/Command/Command.hpp>
#include <src/Header/Command/CommandOrigin.hpp>
#include <src/Header/Command/CommandParameterData.hpp>
#include <src/Header/Command/CommandOutput.hpp>
#include <src/Header/Command/CommandMessage.hpp>
#include <src/Header/Command/CommandItem.hpp>
#include <src/Header/MC/Player.hpp>
#include <src/Header/MC/BlockPos.hpp>
#include <src/Header/MC/Vec3.hpp>
#include <src/Header/MC/ItemStack.hpp>
#include <src/Header/MC/Block.hpp>
#include <mc/Command.hpp>
#include <src/Header/MC/ActorDefinitionIdentifier.hpp>
#include <src/Header/Core/STLHelper/string.hpp>
#include <mc/JsonHelpers.hpp>

//struct __ParameterData : public ::DynamicCommand::ParameterData
//{
//public:
//    using Base = ParameterData;
//    inline ::DynamicCommand::ParameterType GetType();
//    inline void SetType(::DynamicCommand::ParameterType t);
//    inline size_t GetOffset();
//    inline void SetOffest(size_t o);
//    inline std::string GetName();
//    inline void SetName(std::string& s);
//    inline std::string GetDescription();
//    inline void SetDescription(std::string& s);
//    inline std::string GetIdentifier();
//    inline void SetIdentifier(std::string& s);
//    //inline bool GetOptional();
//    inline void SetOptional(bool b);
//    inline CommandParameterOption GetOption();
//    inline void SetOption(CommandParameterOption o);
//    __ParameterData() = delete;
//    __ParameterData(__ParameterData const& p);
//    __ParameterData(std::string const& name, ::DynamicCommand::ParameterType type, bool optional = false, std::string const& enumOptions = "", std::string const& identifier = "", CommandParameterOption parameterOption = (CommandParameterOption)0);
//    __ParameterData(std::string const& name, ::DynamicCommand::ParameterType type, std::string const& enumOptions = "", std::string const& identifier = "", CommandParameterOption parameterOption = (CommandParameterOption)0);
//};

namespace LiteLoader::DynamicCommand {
    interface class ICommand;
    interface class ICommandEvent;
    interface class ICommandData;
}

namespace LiteLoader::DynamicCommand
{
    using namespace LiteLoader::NET;

    ref class DynamicCommandInstance;
    public ref class DynamicCommand : public MC::Command
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
            MC::BlockPos AsBlockPos();
            MC::Vec3 AsVec3();
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
            __ctor_default(ParameterPtr, ::DynamicCommand::ParameterPtr);

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
            __ctor_default(ParameterData, ::DynamicCommand::ParameterData);

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
        static DynamicCommandInstance^ CreateCommand(String^ name, String^ description, MC::CommandPermissionLevel permission, MC::CommandFlag^ flag1, MC::CommandFlag^ flag2, IntPtr handle);
        static DynamicCommandInstance^ CreateCommand(String^ name, String^ description, MC::CommandPermissionLevel permission, MC::CommandFlag^ flag1, MC::CommandFlag^ flag2);
        static DynamicCommandInstance^ CreateCommand(String^ name, String^ description, MC::CommandPermissionLevel permission, MC::CommandFlag^ flag1);
        static DynamicCommandInstance^ CreateCommand(String^ name, String^ description, MC::CommandPermissionLevel permission);
        static DynamicCommandInstance^ CreateCommand(String^ name, String^ description);

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
            IntPtr handle);

        static DynamicCommandInstance^ Setup(DynamicCommandInstance^ commandInstance);
        inline static bool UnregisterCommand(String^ name);
        inline static bool UpdateAvailableCommands();
        inline DynamicCommandInstance^ GetInstance();
        inline static DynamicCommandInstance^ GetInstance(String^ commandName);

        generic<typename TCommand>
        where TCommand:ICommand, gcnew()
            static bool RegisterCommand();
        internal:
            static bool _registerCommandInternal(System::Type^ cmdType);
    };

} // namespace LiteLoader::DynamicCommand