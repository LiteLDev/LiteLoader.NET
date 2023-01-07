#include <src/Header/MC/ColorFormat.hpp>

namespace MC
{
    String^ ColorFormat::ConsoleCodeFromColorCode(String^ mcCode)
    {
        return marshalString(::ColorFormat::consoleCodeFromColorCode(marshalString(mcCode)));
    }

    String^ ColorFormat::NearestColorCodeFromConsoleCode(String^ consoleCode)
    {
        return marshalString(::ColorFormat::nearestColorCodeFromConsoleCode(marshalString(consoleCode)));
    }

    String^ ColorFormat::ConvertToMc(String^ str)
    {
        return marshalString(::ColorFormat::convertToMc(marshalString(str)));
    }

    String^ ColorFormat::ConvertToConsole(String^ str, bool keepColor)
    {
        return marshalString(::ColorFormat::convertToConsole(marshalString(str), keepColor));
    }

    String^ ColorFormat::ConvertToConsole(String^ str)
    {
        return marshalString(::ColorFormat::convertToConsole(marshalString(str)));
    }

    String^ ColorFormat::RemoveColorCode(String^ str)
    {
        return marshalString(::ColorFormat::removeColorCode(marshalString(str)));
    }
}
