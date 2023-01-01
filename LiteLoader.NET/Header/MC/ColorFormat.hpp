#pragma once
#include "Types.hpp"
#include "MC/ColorFormat.hpp"

namespace MC
{
public
ref class ColorFormat __static
{
public:
    static initonly String^ Aqua = marshalString(::ColorFormat::AQUA);
    static initonly String^ Black = marshalString(::ColorFormat::BLACK);
    static initonly String^ Blue = marshalString(::ColorFormat::BLUE);
    static initonly String^ Bold = marshalString(::ColorFormat::BOLD);
    static initonly String^ DarkAqua = marshalString(::ColorFormat::DARK_AQUA);
    static initonly String^ DarkBlue = marshalString(::ColorFormat::DARK_BLUE);
    static initonly String^ DarkGray = marshalString(::ColorFormat::DARK_GRAY);
    static initonly String^ DarkGreen = marshalString(::ColorFormat::DARK_GREEN);
    static initonly String^ DarkPurple = marshalString(::ColorFormat::DARK_PURPLE);
    static initonly String^ DarkRed = marshalString(::ColorFormat::DARK_RED);
    static initonly String^ Escape = marshalString(::ColorFormat::ESCAPE);
    static initonly String^ Gold = marshalString(::ColorFormat::GOLD);
    static initonly String^ Gray = marshalString(::ColorFormat::GRAY);
    static initonly String^ Green = marshalString(::ColorFormat::GREEN);
    static initonly String^ Italic = marshalString(::ColorFormat::ITALIC);
    static initonly String^ LightPurple = marshalString(::ColorFormat::LIGHT_PURPLE);
    static initonly String^ MinecoinGold = marshalString(::ColorFormat::MINECOIN_GOLD);
    static initonly String^ Obfuscated = marshalString(::ColorFormat::OBFUSCATED);
    static initonly String^ Red = marshalString(::ColorFormat::RED);
    static initonly String^ Reset = marshalString(::ColorFormat::RESET);
    static initonly String^ White = marshalString(::ColorFormat::WHITE);
    static initonly String^ Yellow = marshalString(::ColorFormat::YELLOW);

    static String^ ConsoleCodeFromColorCode(String^ mcCode);
    static String^ NearestColorCodeFromConsoleCode(String^ consoleCode);
    static String^ ConvertToMc(String^ str);
    static String^ ConvertToConsole(String^ str, bool keepColor);
    static String^ ConvertToConsole(String^ str);
    static String^ RemoveColorCode(String^ str);
};
}
