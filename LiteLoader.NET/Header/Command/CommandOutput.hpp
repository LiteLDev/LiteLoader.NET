#pragma once
#include <mc/CommandOutput.hpp>
#include <LiteLoader.NET/Header/MC/Types.hpp>

enum CommandOutputType;

namespace MC
{
ref class CommandOutputParameter;
ref class CommandPropertyBag;
ref class CommandOutputMessage;
ref class Actor;
}

namespace MC
{
public
ref class CommandOutput : ClassTemplate<CommandOutput, ::CommandOutput>
{
public:
    __ctor(CommandOutput, ::CommandOutput);
    __ctor_move(CommandOutput, ::CommandOutput);

    inline static CommandOutput ^ Create(CommandOutput ^ co);

    inline void AddMessage(String^ str);
    inline void Success(String^ str);
    inline void Error(String^ str);
    inline void AddToResultList(String^ str0, String^ str1);
    inline void AddToResultList(String^ str, Actor ^ ac);
    inline void Error(String^ str, List<CommandOutputParameter ^> ^ coplist);
    inline void ForceOutput(String^ str, List<CommandOutputParameter ^> ^ coplist);
    inline void Load(int _EnumCommandOutputType, int a0, List<CommandOutputMessage ^> ^ comlist, CommandPropertyBag ^ cpb);
    inline void SetHasPlayerText();
    inline void Success(String^ str, List<CommandOutputParameter ^> ^ coplist);
    inline void Success();
    inline bool WantsData();

    property CommandPropertyBag ^ Data { CommandPropertyBag ^ get(); };
    property List<CommandOutputMessage ^> ^ Messages { List<CommandOutputMessage ^> ^ get(); };

    property int SuccessCount
    {
        int get();
    }
    property bool IsEmpty
    {
        bool get();
    }
    property int OutPutType
    {
        int get();
    }
};
} // namespace MC
