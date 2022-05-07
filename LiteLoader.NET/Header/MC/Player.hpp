#pragma once
#include <MC/Player.hpp>
#include "Mob.hpp"

namespace MC
{
ref class Attribute;
ref class NetworkIdentifier;
ref class Certificate;
ref struct ScorePacketInfo;
ref class BlockPos;
ref class Vec3;
ref class Mob;
ref class Container;
ref class ItemStack;
ref class CompoundTag;
} // namespace MC

namespace MC
{
public
ref class Player : Mob
{
public:
    __ctor_base(Player, ::Player, Mob);

    enum class PositionMode : char
    {
        NORMAL,
        RESPAWN,
        TELEPORT,
        HEAD_ROTATION,
    };

    property String ^ Name { String ^ get(); };
    property String ^ RealName { String ^ get(); };
    property String^ Uuid { String ^ get(); };
    property String ^ IP { String ^ get(); };
    property String ^ LanguageCode { String ^ get(); };
    property String ^ ServerAddress { String ^ get(); };
    property NetworkIdentifier ^ NetworkIdentifier { MC::NetworkIdentifier ^ get(); };
    property Certificate ^ Certificate { MC::Certificate ^ get(); };
    property Container ^ EnderChestContainer { Container ^ get(); };

    property unsigned char ClientSubId
    {
        unsigned char get();
    };
    property String^ DeviceTypeName { String ^ get(); };
    property int AvgPing
    {
        int get();
    }
    property int LastPing
    {
        int get();
    }
    property Pair<MC::BlockPos ^, int> RespawnPosition
    {
        Pair<MC::BlockPos ^, int> get();
    };
    property float AvgPacketLoss
    {
        float get();
    }
    property String^ ClientId { String ^ get(); };
    property int DeviceType
    {
        int get();
    }
    property bool IsOP
    {
        bool get();
    }

    inline bool Kick(String^ msg);
    inline bool CrashClient();
    /// <param name="type">:default = TextType::RAW</param>
    inline bool SendText(String^ text, TextType type);

    inline bool TalkAs(String^ msg);
    inline bool GiveItem(ItemStack ^ item);
    inline int ClearItem(String^ typeName);
    inline bool Runcmd(String^ cmd);
    inline bool TransferServer(String^ address, unsigned short port);
    inline bool SetSidebar(String^ title, List<System::Tuple<String^, int> ^> ^ data, ObjectiveSortOrder sortOrder);
    inline bool RemoveSidebar();
    inline CompoundTag ^ GetNbt();
    inline bool SetNbt(CompoundTag ^ nbt);
    inline bool RefreshAttribute(Attribute ^ attribute);
    inline bool RefreshAttributes(List<Attribute ^> ^ attributes);

    inline int GetScore(String^ key);
    inline bool SetScore(String^ key, int value);
    inline bool AddScore(String^ key, int value);
    inline bool ReduceScore(String^ key, int value);
    inline bool DeleteScore(String^ key);
    // Packet
    /// <param name="Type">:default = TextType::RAW</param>
    inline bool SendTextPacket(String^ text, TextType Type);
    inline bool SendTitlePacket(String^ text, TitleType Type, int FadeInDuration, int RemainDuration, int FadeOutDuration);
    inline bool SendNotePacket(unsigned int tone);
    /// <param name="EntityUniqueID">:default = -1</param>
    inline bool SendSpawnParticleEffectPacket(Vec3 ^ spawnPos, int dimid, String^ ParticleName, int64_t EntityUniqueID);
    /*bad*/ inline bool SendPlaySoundPacket(String^ SoundName, Vec3 ^ Position, float Volume, float Pitch);


    inline bool SendTransferPacket(String^ address, short port);
    inline bool SendSetDisplayObjectivePacket(String^ title, String^ name, char sortOrder);
    inline bool SendSetScorePacket(char type, List<ScorePacketInfo ^> ^ data);
    /// <param name="overlay">:default = 0</param>
    inline bool SendBossEventPacket(BossEvent type, String^ name, float percent, BossEventColour colour, int overlay);
    inline bool SendCommandRequestPacket(String^ cmd);
    inline bool SendTextTalkPacket(String^ msg);

    inline bool SendRawFormPacket(unsigned formId, String^ data);
    delegate void callBackFunc_int(int);
    inline bool SendSimpleFormPacket(String^ title, String^ content, List<String^> ^ buttons, List<String^> ^ images, callBackFunc_int ^ callback);
    delegate void callBackFunc_bool(bool);
    inline bool SendModalFormPacket(String^ title, String^ content, String^ button1, String^ button2, callBackFunc_bool ^ callback);
    delegate void callBackFunc_String(std::string);
    inline bool SendCustomFormPacket(
        String^ data,
        callBackFunc_String ^ callback);

    inline static bool IsValid(Player ^ player);
    delegate void ModalForm_callback(bool);
    delegate void SimpleForm_callback(int);
    delegate void CustomForm_callback(String^);


private:
public:
    bool SendModalForm(String^ title,
                       String^ content,
                       String^ button1,
                       String^ button2,
                       ModalForm_callback ^ callback);

    bool SendSimpleForm(String^ title,
                        String^ content,
                        List<String^> ^ buttons,
                        List<String^> ^ images,
                        SimpleForm_callback ^ callback);

private:
    inline void NATIVECALLBACK CustomForm_Func(std::string str);
    delegate void dgCustomForm_Func(std::string);
    CustomForm_callback ^ __func;

public:
    bool SendCustomForm(String^ json, CustomForm_callback ^ callback);
};

} // namespace MC