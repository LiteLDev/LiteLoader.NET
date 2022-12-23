#include <LiteLoader.NET/Header/MC/Player.hpp>

#include <LiteLoader.NET/Header/MC/CompoundTag.hpp>
#include <LiteLoader.NET/Header/MC/NetworkIdentifier.hpp>
#include <LiteLoader.NET/Header/MC/Certificate.hpp>
#include <LiteLoader.NET/Header/MC/Container.hpp>
#include <LiteLoader.NET/Header/MC/ScorePacketInfo.hpp>
#include <LiteLoader.NET/Header/MC/BlockPos.hpp>
#include <LiteLoader.NET/Header/MC/ItemStack.hpp>
#include <LiteLoader.NET/Header/MC/Vec3.hpp>
#include <LiteLoader.NET/Header/MC/Vec2.hpp>
#include <LiteLoader.NET/Header/MC/Attribute.hpp>
#include <LiteLoader.NET/Header/MC/AABB.hpp>
#include <LiteLoader.NET/Header/MC/Tick.hpp>

#include "LiteLoader.NET/Header/MC/Packet.hpp"
#include "LiteLoader.NET/Header/MC/SerializedSkin.hpp"

#include <LiteLoader.NET/Header/Logger/Logger.hpp>


enum class GameType;

namespace MC
{
    inline String^ Player::Name::get()
    {
        return marshalString(NativePtr->getName());
    }

    inline String^ Player::RealName::get()
    {
        return marshalString(NativePtr->getRealName());
    }

    inline String^ Player::Uuid::get()
    {
        return marshalString(NativePtr->getUuid());
    }

    inline String^ Player::Xuid::get()
    {
        return marshalString(NativePtr->getXuid());
    }

    inline unsigned char Player::ClientSubId::get()
    {
        return NativePtr->getClientSubId();
    }

    inline String^ Player::DeviceTypeName::get()
    {
        return marshalString(NativePtr->getDeviceTypeName());
    }

    inline int Player::AvgPing::get()
    {
        return NativePtr->getAvgPing();
    }

    inline int Player::LastPing::get()
    {
        return NativePtr->getLastPing();
    }

    inline String^ Player::IP::get()
    {
        return marshalString(NativePtr->getIP());
    }

    inline String^ Player::LanguageCode::get()
    {
        return marshalString(NativePtr->getLanguageCode());
    }

    inline String^ Player::ServerAddress::get()
    {
        return marshalString(NativePtr->getServerAddress());
    }

    inline NetworkIdentifier^ Player::NetworkIdentifier::get()
    {
        return gcnew MC::NetworkIdentifier(NativePtr->getNetworkIdentifier());
    }

    inline Certificate^ Player::Certificate::get()
    {
        return gcnew MC::Certificate(NativePtr->getCertificate());
    }

    inline Container^ Player::EnderChestContainer::get()
    {
        return gcnew Container(NativePtr->getEnderChestContainer());
    }

    inline SerializedSkin^ Player::Skin::get()
    {
        return gcnew SerializedSkin(&NativePtr->getSkin());
    }

    inline VALUE_TUPLE<BlockPos, int> Player::RespawnPosition::get()
    {
        auto& p = NativePtr->getRespawnPosition();
        return VALUE_TUPLE<MC::BlockPos, int>(
            MC::BlockPos(p.first), p.second);
    }

    inline float Player::AvgPacketLoss::get()
    {
        return NativePtr->getAvgPacketLoss();
    }

    inline String^ Player::ClientId::get()
    {
        return marshalString(NativePtr->getClientId());
    }

    inline int Player::DeviceType::get()
    {
        return NativePtr->getDeviceType();
    }

    inline bool Player::IsOP::get()
    {
        return NativePtr->isOP();
    }

    inline int Player::CurrentExperience::get()
    {
        return NativePtr->getCurrentExperience();
    }

    inline void Player::CurrentExperience::set(int value)
    {
        if (NativePtr->setTotalExperience(value))
            throw gcnew LiteLoader::NET::MCException("Failed to set current experience.");
    }

    inline size_t Player::TotalExperience::get()
    {
        return NativePtr->getCurrentExperience();
    }

    inline void Player::TotalExperience::set(size_t value)
    {
        if (NativePtr->setTotalExperience(value))
            throw gcnew LiteLoader::NET::MCException("Failed to set total experience.");
    }

    inline bool Player::ReduceExperience(size_t exp) { return NativePtr->reduceExperience(exp); }

    /// <summary>
    /// Experience required to upgrade to level from (level-1)
    /// </summary>

    inline int Player::GetXpNeededForLevel(int level) { return ::Player::getXpNeededForLevel(level); }

    /// <summary>
    /// Experience required to upgrade to level from level 0
    /// </summary>

    inline size_t Player::GetTotalXpNeededForLevel(int level) { return ::Player::getTotalXpNeededForLevel(level); }

    inline bool Player::Kick(String^ msg)
    {
        return NativePtr->kick(marshalString(msg));
    }

    inline bool Player::CrashClient()
    {
        return NativePtr->crashClient();
    }

    /// <param name="type">:default = TextType::RAW</param>
    inline bool Player::SendText(String^ text, TextType type)
    {
        return NativePtr->sendText(marshalString(text), static_cast<::TextType>(type));
    }

    inline bool Player::SendText(String^ text) { return SendText(text, TextType::RAW); }

    inline bool Player::TalkAs(String^ msg)
    {
        return NativePtr->talkAs(marshalString(msg));
    }

    inline bool Player::GiveItem(ItemStack^ item)
    {
        return NativePtr->giveItem(item->NativePtr);
    }

    inline int Player::ClearItem(String^ typeName)
    {
        return NativePtr->clearItem(marshalString(typeName));
    }

    inline bool Player::Runcmd(String^ cmd)
    {
        return NativePtr->runcmd(marshalString(cmd));
    }

    inline bool Player::TransferServer(String^ address, unsigned short port)
    {
        return NativePtr->transferServer(marshalString(address), port);
    }

    inline bool Player::SetSidebar(String^ title,
                                   List<System::Tuple<String^, int>^>^ data,
                                   ObjectiveSortOrder sortOrder)
    {
        auto len = data->Count;
        std::vector<std::pair<std::string, int>> stdvector(len);
        for (int i = 0; i < len; ++i)
            stdvector.emplace_back(std::move(std::pair<std::string, int>(
                marshalString(data[i]->Item1), data[i]->Item2)));
        return NativePtr->setSidebar(
            marshalString(title), stdvector, static_cast<::ObjectiveSortOrder>(sortOrder));
    }

    inline bool Player::RemoveSidebar()
    {
        return NativePtr->removeSidebar();
    }

    inline CompoundTag^ Player::GetNbt()
    {
        return gcnew CompoundTag(NativePtr->getNbt().release(), true);
    }

    inline bool Player::SetNbt(CompoundTag^ nbt)
    {
        return NativePtr->setNbt(nbt->NativePtr);
    }

    inline bool Player::RefreshAttribute(Attribute^ attribute)
    {
        return NativePtr->refreshAttribute(attribute);
    }

    inline bool Player::RefreshAttributes(List<Attribute^>^ attributes)
    {
        auto len = attributes->Count;
        std::vector<const ::Attribute*> stdvector(len);
        for (int i = 0; i < len; ++i)
            stdvector[i] = attributes[i];
        return NativePtr->refreshAttributes(stdvector);
    }

    inline int Player::GetScore(String^ key)
    {
        return NativePtr->getScore(marshalString(key));
    }

    inline bool Player::SetScore(String^ key, int value)
    {
        return NativePtr->setScore(marshalString(key), value);
    }

    inline bool Player::AddScore(String^ key, int value)
    {
        return NativePtr->addScore(marshalString(key), value);
    }

    inline bool Player::ReduceScore(String^ key, int value)
    {
        return NativePtr->reduceScore(marshalString(key), value);
    }

    inline bool Player::DeleteScore(String^ key)
    {
        return NativePtr->deleteScore(marshalString(key));
    }

    // PacketEX

    void Player::SendNetworkPacket(Packet^ packet)
    {
        NativePtr->sendNetworkPacket(packet);
    }

    /// <param name="Type">:default = TextType::RAW</param>
    inline bool Player::SendTextPacket(String^ text, TextType Type)
    {
        return NativePtr->sendText(marshalString(text), static_cast<::TextType>(Type));
    }

    inline bool Player::SendTitlePacket(String^ text, TitleType Type, int FadeInDuration, int RemainDuration,
                                        int FadeOutDuration)
    {
        return NativePtr->sendTitlePacket(marshalString(text), static_cast<::TitleType>(Type), FadeInDuration,
                                          RemainDuration, FadeOutDuration);
    }

    inline bool Player::SendNotePacket(unsigned int tone)
    {
        return NativePtr->sendNotePacket(tone);
    }

    /// <param name="EntityUniqueID">:default = -1</param>
    inline bool Player::SendSpawnParticleEffectPacket(Vec3 spawnPos, int dimid, String^ ParticleName,
                                                      int64_t EntityUniqueID)
    {
        return NativePtr->sendSpawnParticleEffectPacket(spawnPos, dimid, marshalString(ParticleName), EntityUniqueID);
    }

    /*bad*/
    inline bool Player::SendPlaySoundPacket(String^ SoundName, Vec3 Position, float Volume, float Pitch)
    {
        return NativePtr->sendPlaySoundPacket(marshalString(SoundName), Position, Volume, Pitch);
    }

    ///// <param name="DataItem">:default = {} (using null to substitute it.)</param>
    // inline bool Player::sendAddItemEntityPacket(unsigned long long runtimeID, int itemID, int stackSize, short aux, Vec3 pos, List<csFakeDataItem^>^ DataItem) {
    //    if (DataItem == nullptr) {
    //        return NativePtr->sendAddItemEntityPacket(runtimeID, itemID, stackSize, aux, *pos->Translate());
    //    }
    //    auto len = DataItem->Count;
    //    vector<FakeDataItem> stdvector = {};
    //    for (int i = 0; i < len; i++)
    //        stdvector.emplace_back(*DataItem[i]->Translate());
    //    return NativePtr->sendAddItemEntityPacket(runtimeID, itemID, stackSize, aux, *pos->Translate(), stdvector);
    // }
    ///// <param name="DataItem">:default = {} (using null to substitute it.)</param>
    // inline bool Player::sendAddEntityPacket(unsigned long long runtimeID, System::String^ entityType, Vec3 pos, Vec3 rotation, List<csFakeDataItem^>^ DataItem) {
    //    if (DataItem == nullptr) {
    //        return NativePtr->sendAddEntityPacket(runtimeID, marshalString(entityType), *pos->Translate(), *rotation->Translate());
    //    }
    //    auto len = DataItem->Count;
    //    vector<FakeDataItem> stdvector = {};
    //    for (int i = 0; i < len; i++)
    //        stdvector.emplace_back(*DataItem[i]->Translate());
    //    return NativePtr->sendAddEntityPacket(runtimeID, marshalString(entityType), *pos->Translate(), *rotation->Translate(), stdvector);
    // }

    inline bool Player::SendTransferPacket(String^ address, short port)
    {
        return NativePtr->sendTransferPacket(marshalString(address), port);
    }

    inline bool Player::SendSetDisplayObjectivePacket(String^ title, String^ name, char sortOrder)
    {
        return NativePtr->sendSetDisplayObjectivePacket(marshalString(title), marshalString(name), sortOrder);
    }

    inline bool Player::SendSetScorePacket(char type, List<ScorePacketInfo^>^ data)
    {
        auto len = data->Count;
        vector<::ScorePacketInfo> stdvector = {};
        for (int i = 0; i < len; i++)
            stdvector.emplace_back(*data[i]->NativePtr);
        return NativePtr->sendSetScorePacket(type, stdvector);
    }

    /// <param name="overlay">:default = 0</param>
    inline bool Player::SendBossEventPacket(BossEvent type, String^ name, float percent, BossEventColour colour,
                                            int overlay)
    {
        return NativePtr->sendBossEventPacket(static_cast<::BossEvent>(type), marshalString(name), percent,
                                              static_cast<::BossEventColour>(colour), overlay);
    }

    inline bool Player::SendCommandRequestPacket(String^ cmd)
    {
        return NativePtr->sendCommandRequestPacket(marshalString(cmd));
    }

    inline bool Player::SendTextTalkPacket(String^ msg)
    {
        return NativePtr->sendTextTalkPacket(marshalString(msg));
    }

    inline bool Player::SendRawFormPacket(unsigned formId, String^ data)
    {
        return NativePtr->sendRawFormPacket(formId, marshalString(data));
    }

    inline bool Player::SendToastPacket(String^ title, String^ msg)
    {
        return NativePtr->sendToastPacket(marshalString(title), marshalString(msg));
    }

    inline bool Player::SendSimpleFormPacket(
        String^ title,
        String^ content,
        List<String^>^ buttons,
        List<String^>^ images,
        callBackFunc_int^ callback)
    {
        auto len1 = buttons->Count;
        vector<string> stdvector1(len1);
        for (int i = 0; i < len1; i++)
            stdvector1.emplace_back(marshalString(buttons[i]));
        auto len2 = images->Count;
        vector<string> stdvector2(len2);
        for (int j = 0; j < len2; j++)
            stdvector2.emplace_back(marshalString(images[j]));
        GCHandle gch = GCHandle::Alloc(callback);
        auto __ptr = Marshal::GetFunctionPointerForDelegate(callback);
        auto __funcptr = static_cast<void (*)(int)>(__ptr.ToPointer());
        return NativePtr->sendSimpleFormPacket(
            marshalString(title),
            marshalString(content),
            stdvector1,
            stdvector2,
            __funcptr);
    }

    inline bool Player::SendModalFormPacket(
        String^ title,
        String^ content,
        String^ button1,
        String^ button2,
        callBackFunc_bool^ callback)
    {
        GCHandle gch = GCHandle::Alloc(callback);
        auto __ptr = Marshal::GetFunctionPointerForDelegate(callback);
        auto __funcptr = static_cast<void (*)(bool)>(__ptr.ToPointer());
        return NativePtr->sendModalFormPacket(
            marshalString(title),
            marshalString(content),
            marshalString(button1),
            marshalString(button2),
            __funcptr);
    }

    delegate void callBackFunc_String(std::string);
    /// <summary>
    /// QAQ
    /// </summary>
    /// <param name="data"></param>
    /// <param name="callback"></param>
    /// <returns></returns>
    inline bool Player::SendCustomFormPacket(
        String^ data,
        callBackFunc_String^ callback)
    {
        GCHandle gch = GCHandle::Alloc(callback);
        auto __ptr = Marshal::GetFunctionPointerForDelegate(callback);
        auto __funcptr = static_cast<void (*)(std::string)>(__ptr.ToPointer());
        return NativePtr->sendCustomFormPacket(marshalString(data), __funcptr);
    }

    inline bool Player::IsValid(Player^ player)
    {
        return ::Player::isValid(player->NativePtr);
    }

    bool Player::SendModalForm(String^ title,
                               String^ content,
                               String^ button1,
                               String^ button2,
                               ModalForm_callback^ func)
    {
        GCHandle gch = GCHandle::Alloc(func);
        auto pfunc = static_cast<void (*)(bool)>(Marshal::GetFunctionPointerForDelegate(func).ToPointer());
        return NativePtr->sendModalFormPacket(
            marshalString(title),
            marshalString(content),
            marshalString(button1),
            marshalString(button2),
            pfunc);
    }

    bool Player::SendSimpleForm(String^ title,
                                String^ content,
                                List<String^>^ buttons,
                                List<String^>^ images,
                                SimpleForm_callback^ callback)
    {
        GCHandle gch = GCHandle::Alloc(callback);
        auto pfunc = static_cast<void (*)(int)>(Marshal::GetFunctionPointerForDelegate(callback).ToPointer());
        auto len = buttons->Count;
        std::vector<std::string> buttonsvector(len);
        for (int i = 0; i < len; ++i)
            buttonsvector.emplace_back(marshalString(buttons[i]));
        len = images->Count;
        std::vector<std::string> imagesvector(len);
        for (int i = 0; i < len; ++i)
            imagesvector.emplace_back(marshalString(images[i]));
        return NativePtr->sendSimpleFormPacket(
            marshalString(title),
            marshalString(content),
            buttonsvector,
            imagesvector,
            pfunc);
    }

    inline void NATIVECALLBACK Player::CustomForm_Func(std::string str)
    {
        try
        {
            __func(marshalString(str));
        }
        CATCH
    }

    bool Player::SendCustomForm(String^ json,
                                CustomForm_callback^ callback)
    {
        __func = callback;
        auto dgfunc = gcnew dgCustomForm_Func(this, &Player::CustomForm_Func);
        GCHandle gch = GCHandle::Alloc(dgfunc);
        auto pfunc = static_cast<void (*)(std::string)>(
            Marshal::GetFunctionPointerForDelegate(dgfunc).ToPointer());
        return NativePtr->sendCustomFormPacket(
            marshalString(json),
            pfunc);
    }


    Player::GameType Player::GameMode::get()
    {
        return static_cast<GameType>(NativePtr->getPlayerGameType());
    }

    void Player::GameMode::set(GameType value)
    {
        NativePtr->setPlayerGameType(static_cast<::GameType>(value));
    }

#ifdef MANUAL_MAINTENANCE


    String^ Player::DeviceName::get()
    {
        auto __ret = NativePtr->getDeviceName();
        return clix::marshalString<E_UTF8>(__ret);
    }

    bool Player::Sleeping::get()
    {
        return NativePtr->isSleeping();
    }

    float Player::Speed::get()
    {
        return NativePtr->getSpeed();
    }

    int Player::SleepTimer::get()
    {
        return NativePtr->getSleepTimer();
    }

    int Player::PreviousTickSleepTimer::get()
    {
        auto __ret = NativePtr->getPreviousTickSleepTimer();
        return __ret;
    }

    bool Player::IsHostingPlayer::get()
    {
        return NativePtr->isHostingPlayer();
    }

    bool Player::IsLoading::get()
    {
        return NativePtr->isLoading();
    }

    bool Player::IsPlayerInitialized::get()
    {
        return NativePtr->isPlayerInitialized();
    }

    bool Player::IsTeacher::get()
    {
        return NativePtr->isTeacher();
    }

    int Player::MaxItemCooldownLeft::get()
    {
        return NativePtr->getMaxItemCooldownLeft();
    }

    bool Player::ForceAllowEating::get()
    {
        return NativePtr->forceAllowEating();
    }

    ActorUniqueID Player::AgentID::get()
    {
        return NativePtr->getAgentID();
    }

    BlockPos Player::BedPosition::get()
    {
        return NativePtr->getBedPosition();
    }

    long long Player::BlockedUsingDamagedShieldTimeStamp::get()
    {
        auto __ret = NativePtr->getBlockedUsingDamagedShieldTimeStamp();
        return __ret;
    }

    long long Player::BlockedUsingShieldTimeStamp::get()
    {
        auto __ret = NativePtr->getBlockedUsingShieldTimeStamp();
        return __ret;
    }

    long long Player::BlockingStartTimeStamp::get()
    {
        auto __ret = NativePtr->getBlockingStartTimeStamp();
        return __ret;
    }

    int Player::Direction::get()
    {
        auto __ret = NativePtr->getDirection();
        return __ret;
    }

    int Player::EnchantmentSeed::get()
    {
        auto __ret = NativePtr->getEnchantmentSeed();
        return __ret;
    }

    void Player::EnchantmentSeed::set(int _0)
    {
        NativePtr->setEnchantmentSeed(_0);
    }

    BlockPos Player::ExpectedSpawnPosition::get()
    {
        return NativePtr->getExpectedSpawnPosition();
    }

    String^ Player::InteractText::get()
    {
        auto __ret = NativePtr->getInteractText();
        return clix::marshalString<E_UTF8>(__ret);
    }

    float Player::Luck::get()
    {
        auto __ret = NativePtr->getLuck();
        return __ret;
    }

    int Player::MapIndex::get()
    {
        auto __ret = NativePtr->getMapIndex();
        return __ret;
    }

    void Player::MapIndex::set(int _0)
    {
        NativePtr->setMapIndex(_0);
    }

    AABB Player::PickupArea::get()
    {
        return NativePtr->getPickupArea();
    }

    String^ Player::PlatformOnlineId::get()
    {
        auto& __ret = NativePtr->getPlatformOnlineId();
        return clix::marshalString<E_UTF8>(__ret);
    }

    void Player::PlatformOnlineId::set(String^ _0)
    {
        auto __arg0 = clix::marshalString<E_UTF8>(_0);
        NativePtr->setPlatformOnlineId(__arg0);
    }

    int Player::PlayerIndex::get()
    {
        auto __ret = NativePtr->getPlayerIndex();
        return __ret;
    }

    void Player::PlayerIndex::set(int _0)
    {
        NativePtr->setPlayerIndex(_0);
    }

    int Player::PlayerLevel::get()
    {
        auto __ret = NativePtr->getPlayerLevel();
        return __ret;
    }

    String^ Player::PlayerSessionId::get()
    {
        auto& __ret = NativePtr->getPlayerSessionId();
        return clix::marshalString<E_UTF8>(__ret);
    }

    BlockPos Player::RespawnAnchorPosition::get()
    {
        return NativePtr->getRespawnAnchorPosition();
    }

    int Player::SelectedItemSlot::get()
    {
        auto __ret = NativePtr->getSelectedItemSlot();
        return __ret;
    }

    float Player::SleepRotation::get()
    {
        auto __ret = NativePtr->getSleepRotation();
        return __ret;
    }

    BlockPos Player::SpawnPosition::get()
    {
        return NativePtr->getSpawnPosition();
    }

    List<ActorUniqueID>^ Player::TrackedBosses::get()
    {
        auto& vec = NativePtr->getTrackedBosses();
        auto ret = gcnew List<ActorUniqueID>(static_cast<int>(vec.size()));
        for (auto& item : vec)
        {
            ret->Add(item);
        }
        return ret;
    }

    bool Player::UsedPotion::get()
    {
        auto __ret = NativePtr->getUsedPotion();
        return __ret;
    }

    void Player::UsedPotion::set(bool _0)
    {
        NativePtr->setUsedPotion(_0);
    }

    int Player::XpNeededForNextLevel::get()
    {
        auto __ret = NativePtr->getXpNeededForNextLevel();
        return __ret;
    }

    bool Player::HasBedPosition::get()
    {
        auto __ret = NativePtr->hasBedPosition();
        return __ret;
    }

    bool Player::HasOpenContainer::get()
    {
        auto __ret = NativePtr->hasOpenContainer();
        return __ret;
    }

    bool Player::HasOwnedChunkSource::get()
    {
        auto __ret = NativePtr->hasOwnedChunkSource();
        return __ret;
    }

    bool Player::HasRespawnAnchorPosition::get()
    {
        auto __ret = NativePtr->hasRespawnAnchorPosition();
        return __ret;
    }

    bool Player::HasRespawnPosition::get()
    {
        auto __ret = NativePtr->hasRespawnPosition();
        return __ret;
    }

    //bool MC::Player::IsBouncing::get()
    //{
    //    auto __ret = NativePtr->isBouncing();
    //    return __ret;
    //}

    bool Player::IsForcedRespawn::get()
    {
        auto __ret = NativePtr->isForcedRespawn();
        return __ret;
    }

    bool Player::IsHungry::get()
    {
        auto __ret = NativePtr->isHungry();
        return __ret;
    }

    bool Player::IsHurt::get()
    {
        auto __ret = NativePtr->isHurt();
        return __ret;
    }

    bool Player::IsInCreativeMode::get()
    {
        auto __ret = NativePtr->isInCreativeMode();
        return __ret;
    }

    bool Player::IsInRaid::get()
    {
        auto __ret = NativePtr->isInRaid();
        return __ret;
    }

    bool Player::IsRespawningFromTheEnd::get()
    {
        auto __ret = NativePtr->isRespawningFromTheEnd();
        return __ret;
    }

    bool Player::IsSleepingLongEnough::get()
    {
        auto __ret = NativePtr->isSleepingLongEnough();
        return __ret;
    }

    bool Player::IsSpawned::get()
    {
        auto __ret = NativePtr->isSpawned();
        return __ret;
    }

    bool Player::IsUsingItem::get()
    {
        auto __ret = NativePtr->isUsingItem();
        return __ret;
    }


    void Player::ServerInitItemStackIds()
    {
        NativePtr->_serverInitItemStackIds();
    }

    void Player::ResetUserPos(bool _0)
    {
        NativePtr->resetUserPos(_0);
    }

    void Player::Remove()
    {
        NativePtr->remove();
    }

    bool Player::isRuntimePredictedMovementEnabled()
    {
        auto __ret = NativePtr->isRuntimePredictedMovementEnabled();
        return __ret;
    }

    void Player::Move(Vec3 _0)
    {
        NativePtr->move(_0);
    }

    //void MC::Player::UnkVfn40()
    //{
    //    ((class ::Player*)NativePtr)->__unk_vfn_40();
    //}

    void Player::TeleportTo(Vec3 _0, bool _1, int _2, int _3, bool _4)
    {
        NativePtr->teleportTo(_0, _1, _2, _3, _4);
    }

    void Player::NormalTick()
    {
        NativePtr->normalTick();
    }

    //void MC::Player::VehicleTick()
    //{
    //    ((class ::Player*)NativePtr)->vehicleTick();
    //}

    //float MC::Player::GetRidingHeight()
    //{
    //    auto __ret = ((class ::Player*)NativePtr)->getRidingHeight();
    //    return __ret;
    //}

    //void MC::Player::UnkVfn61()
    //{
    //    ((class ::Player*)NativePtr)->__unk_vfn_61();
    //}

    String^ Player::GetFormattedNameTag()
    {
        auto __ret = NativePtr->getFormattedNameTag();
        return clix::marshalString<E_UTF8>(__ret);
    }

    //void MC::Player::UnkVfn68()
    //{
    //    ((class ::Player*)NativePtr)->__unk_vfn_68();
    //}

    float Player::GetCameraOffset()
    {
        auto __ret = NativePtr->getCameraOffset();
        return __ret;
    }

    //void MC::Player::UnkVfn82()
    //{
    //    ((class ::Player*)NativePtr)->__unk_vfn_82();
    //}

    /*bool Player::CanInteractWithOtherEntitiesInGame()
    {
        auto __ret = NativePtr->canInteractWithOtherEntitiesInGame();
        return __ret;
    }*/

    //void MC::Player::UnkVfn88()
    //{
    //    ((class ::Player*)NativePtr)->__unk_vfn_88();
    //}

    void Player::PlayerTouch(Player^ _0)
    {
        if (ReferenceEquals(_0, nullptr))
            throw gcnew System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
        auto& __arg0 = *_0->NativePtr;
        NativePtr->playerTouch(__arg0);
    }

    bool Player::isImmobile()
    {
        auto __ret = NativePtr->isImmobile();
        return __ret;
    }

    //void MC::Player::UnkVfn95()
    //{
    //    ((class ::Player*)NativePtr)->__unk_vfn_95();
    //}

    void Player::SetSleeping(bool _0)
    {
        NativePtr->setSleeping(_0);
    }

    //void MC::Player::UnkVfn98()
    //{
    //    ((class ::Player*)NativePtr)->__unk_vfn_98();
    //}

    bool Player::isBlocking()
    {
        auto __ret = NativePtr->isBlocking();
        return __ret;
    }

    //void MC::Player::UnkVfn105()
    //{
    //    ((class ::Player*)NativePtr)->__unk_vfn_105();
    //}

    //void MC::Player::UnkVfn107()
    //{
    //    ((class ::Player*)NativePtr)->__unk_vfn_107();
    //}

    //void MC::Player::UnkVfn108()
    //{
    //    ((class ::Player*)NativePtr)->__unk_vfn_108();
    //}

    //void MC::Player::UnkVfn109()
    //{
    //    ((class ::Player*)NativePtr)->__unk_vfn_109();
    //}

    //MC::Actor^ MC::Player::findAttackTarget()
    //{
    //    auto __ret = ((class ::Player*)NativePtr)->findAttackTarget();
    //    if (__ret == nullptr) return nullptr;
    //    return (__ret == nullptr) ? nullptr : gcnew ::MC::Actor((class ::Actor*)__ret);
    //}

    bool Player::IsValidTarget(Actor^ _0)
    {
        auto __arg0 = _0->NativePtr;
        auto __ret = NativePtr->isValidTarget(__arg0);
        return __ret;
    }

    bool Player::Attack(Actor^ _0, ActorDamageCause _1)
    {
        if (ReferenceEquals(_0, nullptr))
            throw gcnew System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
        auto& __arg0 = *_0->NativePtr;
        auto __arg1 = static_cast<::ActorDamageCause>(_1);
        auto __ret = NativePtr->attack(__arg0, __arg1);
        return __ret;
    }

    void Player::OnTame()
    {
        NativePtr->onTame();
    }

    void Player::OnFailedTame()
    {
        NativePtr->onFailedTame();
    }

    bool Player::isJumping()
    {
        auto __ret = NativePtr->isJumping();
        return __ret;
    }

    void Player::VehicleLanded(Vec3 _0, Vec3 _1)
    {
        NativePtr->vehicleLanded(_0, _0);
    }

    void Player::Feed(int _0)
    {
        NativePtr->feed(_0);
    }

    void Player::AwardKillScore(Actor^ _0, int _1)
    {
        if (ReferenceEquals(_0, nullptr))
            throw gcnew System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
        auto& __arg0 = *_0->NativePtr;
        NativePtr->awardKillScore(__arg0, _1);
    }

    bool Player::ConsumeTotem()
    {
        auto __ret = NativePtr->consumeTotem();
        return __ret;
    }

    ActorUniqueID Player::GetSourceUniqueID()
    {
        return NativePtr->getSourceUniqueID();
    }

    bool Player::CanFreeze()
    {
        auto __ret = NativePtr->canFreeze();
        return __ret;
    }

    int Player::GetPortalCooldown()
    {
        auto __ret = NativePtr->getPortalCooldown();
        return __ret;
    }

    int Player::GetPortalWaitTime()
    {
        auto __ret = NativePtr->getPortalWaitTime();
        return __ret;
    }

    /*bool Player::CanChangeDimensions()
    {
        auto __ret = NativePtr->canChangeDimensions();
        return __ret;
    }*/

    //void MC::Player::UnkVfn181()
    //{
    //    ((class ::Player*)NativePtr)->__unk_vfn_181();
    //}

    ActorUniqueID Player::GetControllingPlayer()
    {
        return NativePtr->getControllingPlayer();
    }

    void Player::OnSynchedDataUpdate(int _0)
    {
        NativePtr->onSynchedDataUpdate(_0);
    }

    bool Player::CanAddPassenger(Actor^ _0)
    {
        if (ReferenceEquals(_0, nullptr))
            throw gcnew System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
        auto& __arg0 = *_0->NativePtr;
        auto __ret = NativePtr->canAddPassenger(__arg0);
        return __ret;
    }

    bool Player::CanBePulledIntoVehicle()
    {
        auto __ret = NativePtr->canBePulledIntoVehicle();
        return __ret;
    }

    //void MC::Player::UnkVfn195()
    //{
    //    ((class ::Player*)NativePtr)->__unk_vfn_195();
    //}

    void Player::SendMotionPacketIfNeeded()
    {
        NativePtr->sendMotionPacketIfNeeded();
    }

    bool Player::CanSynchronizeNewEntity()
    {
        auto __ret = NativePtr->canSynchronizeNewEntity();
        return __ret;
    }

    void Player::StartSwimming()
    {
        NativePtr->startSwimming();
    }

    void Player::StopSwimming()
    {
        NativePtr->stopSwimming();
    }

    //void MC::Player::UnkVfn220()
    //{
    //    ((class ::Player*)NativePtr)->__unk_vfn_220();
    //}

    //void MC::Player::UnkVfn221()
    //{
    //    ((class ::Player*)NativePtr)->__unk_vfn_221();
    //}

    float Player::GetMapDecorationRotation()
    {
        auto __ret = NativePtr->getMapDecorationRotation();
        return __ret;
    }

    bool Player::isWorldBuilder()
    {
        auto __ret = NativePtr->isWorldBuilder();
        return __ret;
    }

    bool Player::isCreative()
    {
        auto __ret = NativePtr->isCreative();
        return __ret;
    }

    bool Player::isAdventure()
    {
        auto __ret = NativePtr->isAdventure();
        return __ret;
    }

    bool Player::isSurvival()
    {
        auto __ret = NativePtr->isSurvival();
        return __ret;
    }

    bool Player::isSpectator()
    {
        auto __ret = NativePtr->isSpectator();
        return __ret;
    }

    void Player::SetAuxValue(int _0)
    {
        NativePtr->setAuxValue(_0);
    }

    void Player::SetSize(float _0, float _1)
    {
        NativePtr->setSize(_0, _1);
    }

    void Player::StartSpinAttack()
    {
        NativePtr->startSpinAttack();
    }

    void Player::StopSpinAttack()
    {
        NativePtr->stopSpinAttack();
    }

    //void MC::Player::UnkVfn246()
    //{
    //    ((class ::Player*)NativePtr)->__unk_vfn_246();
    //}

    //void MC::Player::UnkVfn249()
    //{
    //    ((class ::Player*)NativePtr)->__unk_vfn_249();
    //}

    bool Player::ShouldDropDeathLoot()
    {
        auto __ret = NativePtr->shouldDropDeathLoot();
        return __ret;
    }

    //void MC::Player::UnkVfn261()
    //{
    //    ((class ::Player*)NativePtr)->__unk_vfn_261();
    //}

    //void MC::Player::UnkVfn269()
    //{
    //    ((class ::Player*)NativePtr)->__unk_vfn_269();
    //}

    void Player::OnSizeUpdated()
    {
        NativePtr->_onSizeUpdated();
    }

    //void MC::Player::UnkVfn278()
    //{
    //    ((class ::Player*)NativePtr)->__unk_vfn_278();
    //}

    void Player::SpawnAnim()
    {
        NativePtr->spawnAnim();
    }

    void Player::SetSpeed(float _0)
    {
        NativePtr->setSpeed(_0);
    }

    void Player::Travel(float _0, float _1, float _2)
    {
        NativePtr->travel(_0, _1, _2);
    }

    void Player::AiStep()
    {
        NativePtr->aiStep();
    }

    int Player::GetItemUseDuration()
    {
        auto __ret = NativePtr->getItemUseDuration();
        return __ret;
    }

    float Player::GetItemUseStartupProgress()
    {
        auto __ret = NativePtr->getItemUseStartupProgress();
        return __ret;
    }

    float Player::GetItemUseIntervalProgress()
    {
        auto __ret = NativePtr->getItemUseIntervalProgress();
        return __ret;
    }

    //void MC::Player::UnkVfn307()
    //{
    //    ((class ::Player*)NativePtr)->__unk_vfn_307();
    //}

    bool Player::IsAlliedTo(Mob^ _0)
    {
        auto __arg0 = _0->NativePtr;
        auto __ret = NativePtr->isAlliedTo(__arg0);
        return __ret;
    }

    //void MC::Player::UnkVfn311()
    //{
    //    ((class ::Player*)NativePtr)->__unk_vfn_311();
    //}

    void Player::DropEquipmentOnDeath()
    {
        NativePtr->dropEquipmentOnDeath();
    }

    void Player::ClearVanishEnchantedItemsOnDeath()
    {
        NativePtr->clearVanishEnchantedItemsOnDeath();
    }

    void Player::SendInventory(bool _0)
    {
        NativePtr->sendInventory(_0);
    }

    void Player::OnBorn(Actor^ _0, Actor^ _1)
    {
        if (ReferenceEquals(_0, nullptr))
            throw gcnew System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
        auto& __arg0 = *_0->NativePtr;
        if (ReferenceEquals(_1, nullptr))
            throw gcnew System::ArgumentNullException("_1", "Cannot be null because it is a C++ reference (&).");
        auto& __arg1 = *_1->NativePtr;
        NativePtr->onBorn(__arg0, __arg1);
    }

    float Player::GetWalkTargetValue(MC::BlockPos _0)
    {
        return NativePtr->_getWalkTargetValue(_0);
    }

    bool Player::CanExistWhenDisallowMob()
    {
        auto __ret = NativePtr->canExistWhenDisallowMob();
        return __ret;
    }

    //void MC::Player::UnkVfn345()
    //{
    //    ((class ::Player*)NativePtr)->__unk_vfn_345();
    //}

    void Player::JumpFromGround()
    {
        NativePtr->jumpFromGround();
    }

    void Player::UpdateAi()
    {
        NativePtr->updateAi();
    }

    void Player::ServerAiMobStep()
    {
        NativePtr->_serverAiMobStep();
    }

    void Player::UpdateGliding()
    {
        NativePtr->updateGliding();
    }

    //void MC::Player::UnkVfn359()
    //{
    //    ((class ::Player*)NativePtr)->__unk_vfn_359();
    //}

    void Player::DestroyRegion()
    {
        NativePtr->destroyRegion();
    }

    void Player::SuspendRegion()
    {
        NativePtr->suspendRegion();
    }

    void Player::ResendAllChunks()
    {
        NativePtr->resendAllChunks();
    }

    void Player::FireWillChangeDimension()
    {
        NativePtr->_fireWillChangeDimension();
    }

    void Player::FireDimensionChanged()
    {
        NativePtr->_fireDimensionChanged();
    }

    void Player::TickWorld(Tick^ _0)
    {
        if (ReferenceEquals(_0, nullptr))
            throw gcnew System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
        auto& __arg0 = *_0->NativePtr;
        NativePtr->tickWorld(__arg0);
    }

    //void MC::Player::UnkVfn369()
    //{
    //    ((class ::Player*)NativePtr)->__unk_vfn_369();
    //}

    void Player::MoveView()
    {
        NativePtr->moveView();
    }

    void Player::CheckMovementStats(Vec3 _0)
    {
        NativePtr->checkMovementStats(_0);
    }

    //void MC::Player::UnkVfn374()
    //{
    //    ((class ::Player*)NativePtr)->__unk_vfn_374();
    //}

    //void MC::Player::UnkVfn375()
    //{
    //    ((class ::Player*)NativePtr)->__unk_vfn_375();
    //}

    void Player::Respawn()
    {
        NativePtr->respawn();
    }

    //void MC::Player::UnkVfn377()
    //{
    //    ((class ::Player*)NativePtr)->__unk_vfn_377();
    //}

    //void MC::Player::UnkVfn378()
    //{
    //    ((class ::Player*)NativePtr)->__unk_vfn_378();
    //}

    bool Player::HasResource(int _0)
    {
        auto __ret = NativePtr->hasResource(_0);
        return __ret;
    }

    void Player::CompleteUsingItem()
    {
        NativePtr->completeUsingItem();
    }

    void Player::StartDestroying()
    {
        NativePtr->startDestroying();
    }

    void Player::StopDestroying()
    {
        NativePtr->stopDestroying();
    }

    //void MC::Player::UnkVfn384()
    //{
    //    ((class ::Player*)NativePtr)->__unk_vfn_384();
    //}

    //void MC::Player::UnkVfn385()
    //{
    //    ((class ::Player*)NativePtr)->__unk_vfn_385();
    //}

    void Player::OpenTrading(ActorUniqueID _0, bool _1)
    {
        NativePtr->openTrading(_0, _1);
    }

    bool Player::CanOpenContainerScreen()
    {
        auto __ret = NativePtr->canOpenContainerScreen();
        return __ret;
    }

    //void MC::Player::UnkVfn388()
    //{
    //    ((class ::Player*)NativePtr)->__unk_vfn_388();
    //}

    //void MC::Player::UnkVfn389()
    //{
    //    ((class ::Player*)NativePtr)->__unk_vfn_389();
    //}

    void Player::OpenInventory()
    {
        NativePtr->openInventory();
    }

    //void MC::Player::UnkVfn391()
    //{
    //    ((class ::Player*)NativePtr)->__unk_vfn_391();
    //}

    //void MC::Player::UnkVfn392()
    //{
    //    ((class ::Player*)NativePtr)->__unk_vfn_392();
    //}

    void Player::DisplayWhisperMessage(String^ _0, String^ _1, String^ _2, String^ _3)
    {
        auto __arg0 = clix::marshalString<E_UTF8>(_0);
        auto __arg1 = clix::marshalString<E_UTF8>(_1);
        auto __arg2 = clix::marshalString<E_UTF8>(_2);
        auto __arg3 = clix::marshalString<E_UTF8>(_3);
        NativePtr->displayWhisperMessage(__arg0, __arg1, __arg2, __arg3);
    }

    void Player::StopSleepInBed(bool _0, bool _1)
    {
        NativePtr->stopSleepInBed(_0, _1);
    }

    bool Player::CanStartSleepInBed()
    {
        auto __ret = NativePtr->canStartSleepInBed();
        return __ret;
    }

    //void MC::Player::UnkVfn401()
    //{
    //    ((class ::Player*)NativePtr)->__unk_vfn_401();
    //}

    //void MC::Player::UnkVfn402()
    //{
    //    ((class ::Player*)NativePtr)->__unk_vfn_402();
    //}

    //void MC::Player::UnkVfn406()
    //{
    //    ((class ::Player*)NativePtr)->__unk_vfn_406();
    //}

    void Player::RegisterTrackedBoss(ActorUniqueID _0)
    {
        NativePtr->registerTrackedBoss(_0);
    }

    void Player::UnRegisterTrackedBoss(ActorUniqueID _0)
    {
        NativePtr->unRegisterTrackedBoss(_0);
    }

    void Player::InitHUDContainerManager()
    {
        NativePtr->initHUDContainerManager();
    }

    void Player::Crit(Actor^ _0)
    {
        if (ReferenceEquals(_0, nullptr))
            throw gcnew System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
        auto& __arg0 = *_0->NativePtr;
        NativePtr->_crit(__arg0);
    }

    //void MC::Player::UnkVfn413()
    //{
    //    ((class ::Player*)NativePtr)->__unk_vfn_413();
    //}

    void Player::AddExperience(int _0)
    {
        NativePtr->addExperience(_0);
    }

    void Player::AddLevels(int _0)
    {
        NativePtr->addLevels(_0);
    }

    void Player::DeleteContainerManager()
    {
        NativePtr->deleteContainerManager();
    }

    void Player::SetFieldOfViewModifier(float _0)
    {
        NativePtr->setFieldOfViewModifier(_0);
    }

    bool Player::IsActorRelevant(Actor^ _0)
    {
        if (ReferenceEquals(_0, nullptr))
            throw gcnew System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
        auto& __arg0 = *_0->NativePtr;
        auto __ret = NativePtr->isActorRelevant(__arg0);
        return __ret;
    }

    void Player::OnSuspension()
    {
        NativePtr->onSuspension();
    }

    void Player::OnLinkedSlotsChanged()
    {
        NativePtr->onLinkedSlotsChanged();
    }

    int Player::GetItemCooldownLeft(unsigned long long _0)
    {
        auto __ret = NativePtr->getItemCooldownLeft(_0);
        return __ret;
    }

    //void MC::Player::UnkVfn441()
    //{
    //    ((class ::Player*)NativePtr)->__unk_vfn_441();
    //}

    void Player::OnMovePlayerPacketNormal(Vec3 _0, Vec2 _1, float _2)
    {
        NativePtr->onMovePlayerPacketNormal(_0, _1, _2);
    }

    void Player::ApplyExhaustion(Vec3 _0)
    {
        NativePtr->applyExhaustion(_0);
    }

    bool Player::CanBeSeenOnMap()
    {
        auto __ret = NativePtr->canBeSeenOnMap();
        return __ret;
    }

    bool Player::CanUseOperatorBlocks()
    {
        auto __ret = NativePtr->canUseOperatorBlocks();
        return __ret;
    }

    void Player::CauseFoodExhaustion(float _0)
    {
        NativePtr->causeFoodExhaustion(_0);
    }

    void Player::ClearRespawnPosition()
    {
        NativePtr->clearRespawnPosition();
    }

    void Player::Eat(int _0, float _1)
    {
        NativePtr->eat(_0, _1);
    }

    Vec3 Player::GetCapePos(float _0)
    {
        return NativePtr->getCapePos(_0);
    }

    void Player::GetNewEnchantmentSeed()
    {
        NativePtr->getNewEnchantmentSeed();
    }

    bool Player::HasOpenContainerOfContainerType(ContainerType _0)
    {
        auto __arg0 = static_cast<::ContainerType>(_0);
        auto __ret = NativePtr->hasOpenContainerOfContainerType(__arg0);
        return __ret;
    }

    bool Player::Interact(Actor^ _0, Vec3 _1)
    {
        if (ReferenceEquals(_0, nullptr))
            throw gcnew System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
        auto& __arg0 = *_0->NativePtr;
        auto __ret = NativePtr->interact(__arg0, _1);
        return __ret;
    }

    bool Player::IsHiddenFrom(Mob^ _0)
    {
        if (ReferenceEquals(_0, nullptr))
            throw gcnew System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
        auto& __arg0 = *_0->NativePtr;
        auto __ret = NativePtr->isHiddenFrom(__arg0);
        return __ret;
    }

    void Player::RecheckSpawnPosition()
    {
        NativePtr->recheckSpawnPosition();
    }

    void Player::ReleaseUsingItem()
    {
        NativePtr->releaseUsingItem();
    }

    void Player::ResetPlayerLevel()
    {
        NativePtr->resetPlayerLevel();
    }

    void Player::ResetToDefaultGameMode()
    {
        NativePtr->resetToDefaultGameMode();
    }

    void Player::SetAllPlayersSleeping()
    {
        NativePtr->setAllPlayersSleeping();
    }

    void Player::SetBedRespawnPosition(MC::BlockPos _0)
    {
        NativePtr->setBedRespawnPosition(_0);
    }

    void Player::SetBlockRespawnUntilClientMessage(bool _0)
    {
        NativePtr->setBlockRespawnUntilClientMessage(_0);
    }

    void Player::SetChunkRadius(unsigned int _0)
    {
        NativePtr->setChunkRadius(_0);
    }

    void Player::SetHasSeenCredits(bool _0)
    {
        NativePtr->setHasSeenCredits(_0);
    }

    void Player::SetRespawnPositionCandidate()
    {
        NativePtr->setRespawnPositionCandidate();
    }

    void Player::SetRespawnReady(Vec3 _0)
    {
        NativePtr->setRespawnReady(_0);
    }

    bool Player::ShouldShowCredits()
    {
        auto __ret = NativePtr->shouldShowCredits();
        return __ret;
    }

    void Player::SpawnExperienceOrb(Vec3 _0, int _1)
    {
        NativePtr->spawnExperienceOrb(_0, _1);
    }

    void Player::StartGliding()
    {
        NativePtr->startGliding();
    }

    void Player::StopGliding()
    {
        NativePtr->stopGliding();
    }

    void Player::StopUsingItem()
    {
        NativePtr->stopUsingItem();
    }

    bool Player::Take(Actor^ _0, int _1, int _2)
    {
        if (ReferenceEquals(_0, nullptr))
            throw gcnew System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
        auto& __arg0 = *_0->NativePtr;
        auto __ret = NativePtr->take(__arg0, _1, _2);
        return __ret;
    }

    void Player::UpdateInventoryTransactions()
    {
        NativePtr->updateInventoryTransactions();
    }

    void Player::UpdateSkin(SerializedSkin^ skin, int skinId)
    {
        NativePtr->updateSkin(*skin->NativePtr, skinId);
    }

    void Player::UpdateSpawnChunkView()
    {
        NativePtr->updateSpawnChunkView();
    }

    void Player::UpdateTrackedBosses()
    {
        NativePtr->updateTrackedBosses();
    }


    float Player::DEFAULT_BB_HEIGHT::get()
    {
        return ::Player::DEFAULT_BB_HEIGHT;
    }

    float Player::DEFAULT_BB_WIDTH::get()
    {
        return ::Player::DEFAULT_BB_WIDTH;
    }

    float Player::DEFAULT_FLY_SPEED::get()
    {
        return ::Player::DEFAULT_FLY_SPEED;
    }

    float Player::DEFAULT_PLAYER_HEIGHT_OFFSET::get()
    {
        return ::Player::DEFAULT_PLAYER_HEIGHT_OFFSET;
    }

    float Player::DEFAULT_WALK_SPEED::get()
    {
        return ::Player::DEFAULT_WALK_SPEED;
    }

    float Player::DISTANCE_TO_TRANSFORM_EVENT::get()
    {
        return ::Player::DISTANCE_TO_TRANSFORM_EVENT;
    }

    float Player::DISTANCE_TO_TRAVELLED_EVENT::get()
    {
        return ::Player::DISTANCE_TO_TRAVELLED_EVENT;
    }

    int Player::GLIDE_STOP_DELAY::get()
    {
        return ::Player::GLIDE_STOP_DELAY;
    }

    int Player::ITEM_USE_INTERVAL_DURATION::get()
    {
        return ::Player::ITEM_USE_INTERVAL_DURATION;
    }

    int Player::MAX_ITEM_USE_DURATION::get()
    {
        return ::Player::MAX_ITEM_USE_DURATION;
    }

    float Player::PLAYER_ALIVE_HEIGHT::get()
    {
        return ::Player::PLAYER_ALIVE_HEIGHT;
    }

    float Player::PLAYER_ALIVE_WIDTH::get()
    {
        return ::Player::PLAYER_ALIVE_WIDTH;
    }

    float Player::PLAYER_DEAD_HEIGHT::get()
    {
        return ::Player::PLAYER_DEAD_HEIGHT;
    }

    float Player::PLAYER_DEAD_WIDTH::get()
    {
        return ::Player::PLAYER_DEAD_WIDTH;
    }

    float Player::PLAYER_DOWN_SWIM_SPEED::get()
    {
        return ::Player::PLAYER_DOWN_SWIM_SPEED;
    }

    float Player::PLAYER_GLIDING_CAMERA_OFFSET::get()
    {
        return ::Player::PLAYER_GLIDING_CAMERA_OFFSET;
    }

    float Player::PLAYER_SLEEPING_CAMERA_OFFSET::get()
    {
        return ::Player::PLAYER_SLEEPING_CAMERA_OFFSET;
    }

    float Player::PLAYER_SLEEPING_HEIGHT::get()
    {
        return ::Player::PLAYER_SLEEPING_HEIGHT;
    }

    float Player::PLAYER_SLEEPING_WIDTH::get()
    {
        return ::Player::PLAYER_SLEEPING_WIDTH;
    }

    float Player::PLAYER_SNEAK_OFFSET::get()
    {
        return ::Player::PLAYER_SNEAK_OFFSET;
    }

    float Player::PLAYER_SWIMMING_CAMERA_OFFSET::get()
    {
        return ::Player::PLAYER_SWIMMING_CAMERA_OFFSET;
    }

    float Player::PLAYER_SWIM_BREACH_ANGLE::get()
    {
        return ::Player::PLAYER_SWIM_BREACH_ANGLE;
    }

    float Player::PLAYER_SWIM_ENTER_THRESHOLD::get()
    {
        return ::Player::PLAYER_SWIM_ENTER_THRESHOLD;
    }

    float Player::PLAYER_SWIM_FLY_MULTI::get()
    {
        return ::Player::PLAYER_SWIM_FLY_MULTI;
    }

    float Player::PLAYER_UP_SWIM_SPEED::get()
    {
        return ::Player::PLAYER_UP_SWIM_SPEED;
    }

    unsigned int Player::SPAWN_CHUNK_LARGE_JUMP::get()
    {
        return ::Player::SPAWN_CHUNK_LARGE_JUMP;
    }

    unsigned int Player::SPAWN_CHUNK_RADIUS::get()
    {
        return ::Player::SPAWN_CHUNK_RADIUS;
    }

#endif // MANUAL_MAINTENANCE
} // namespace MC
