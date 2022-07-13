#include "../../Header/MC/Player.hpp"

#include "../../Header/MC/CompoundTag.hpp"
#include "../../Header/MC/NetworkIdentifier.hpp"
#include "../../Header/MC/Certificate.hpp"
#include "../../Header/MC/Container.hpp"
#include "../../Header/MC/ScorePacketInfo.hpp"
#include "../../Header/MC/BlockPos.hpp"
#include "../../Header/MC/ItemStack.hpp"
#include "../../Header/MC/Vec3.hpp"
#include "../../Header/MC/Vec2.hpp"
#include "../../Header/MC/Attribute.hpp"
#include "../../Header/MC/AABB.hpp"
#include "../../Header/MC/Tick.hpp"

#include "../../Header/Logger.hpp"

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
	inline Pair<BlockPos, int> Player::RespawnPosition::get()
	{
		auto& p = NativePtr->getRespawnPosition();
		return Pair<MC::BlockPos, int>(
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
			throw gcnew LLNET::Core::MCException("Failed to set current experience.");
	}
	inline size_t Player::TotalExperience::get()
	{
		return NativePtr->getCurrentExperience();
	}
	inline void Player::TotalExperience::set(size_t value)
	{
		if (NativePtr->setTotalExperience(value))
			throw gcnew LLNET::Core::MCException("Failed to set total experience.");
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
		return NativePtr->sendText(marshalString(text), ::TextType(type));
	}
	inline bool Player::SendText(String^ text) { return SendText(text, MC::TextType::RAW); }
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
			marshalString(title), stdvector, ::ObjectiveSortOrder(sortOrder));
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
	inline bool Player::RefreshAttribute(MC::Attribute^ attribute)
	{
		return NativePtr->refreshAttribute(attribute);
	}
	inline bool Player::RefreshAttributes(List<MC::Attribute^>^ attributes)
	{
		auto len = attributes->Count;
		std::vector<::Attribute const*> stdvector(len);
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
	/// <param name="Type">:default = TextType::RAW</param>
	inline bool Player::SendTextPacket(String^ text, TextType Type)
	{
		return NativePtr->sendText(marshalString(text), ::TextType(Type));
	}
	inline bool Player::SendTitlePacket(String^ text, TitleType Type, int FadeInDuration, int RemainDuration, int FadeOutDuration)
	{
		return NativePtr->sendTitlePacket(marshalString(text), ::TitleType(Type), FadeInDuration, RemainDuration, FadeOutDuration);
	}
	inline bool Player::SendNotePacket(unsigned int tone)
	{
		return NativePtr->sendNotePacket(tone);
	}
	/// <param name="EntityUniqueID">:default = -1</param>
	inline bool Player::SendSpawnParticleEffectPacket(Vec3 spawnPos, int dimid, String^ ParticleName, int64_t EntityUniqueID)
	{
		return NativePtr->sendSpawnParticleEffectPacket(spawnPos, dimid, marshalString(ParticleName), EntityUniqueID);
	}
	/*bad*/ inline bool Player::SendPlaySoundPacket(String^ SoundName, Vec3 Position, float Volume, float Pitch)
	{
		return NativePtr->sendPlaySoundPacket(marshalString(SoundName), Position, Volume, Pitch);
	}

	///// <param name="DataItem">:default = {} (using null to substitute it.)</param>
	// inline bool Player::sendAddItemEntityPacket(unsigned long long runtimeID, int itemID, int stackSize, short aux, Vec3 pos, List<csFakeDataItem^>^ DataItem) {
	//	if (DataItem == nullptr) {
	//		return NativePtr->sendAddItemEntityPacket(runtimeID, itemID, stackSize, aux, *pos->Translate());
	//	}
	//	auto len = DataItem->Count;
	//	vector<FakeDataItem> stdvector = {};
	//	for (int i = 0; i < len; i++)
	//		stdvector.emplace_back(*DataItem[i]->Translate());
	//	return NativePtr->sendAddItemEntityPacket(runtimeID, itemID, stackSize, aux, *pos->Translate(), stdvector);
	// }
	///// <param name="DataItem">:default = {} (using null to substitute it.)</param>
	// inline bool Player::sendAddEntityPacket(unsigned long long runtimeID, System::String^ entityType, Vec3 pos, Vec3 rotation, List<csFakeDataItem^>^ DataItem) {
	//	if (DataItem == nullptr) {
	//		return NativePtr->sendAddEntityPacket(runtimeID, marshalString(entityType), *pos->Translate(), *rotation->Translate());
	//	}
	//	auto len = DataItem->Count;
	//	vector<FakeDataItem> stdvector = {};
	//	for (int i = 0; i < len; i++)
	//		stdvector.emplace_back(*DataItem[i]->Translate());
	//	return NativePtr->sendAddEntityPacket(runtimeID, marshalString(entityType), *pos->Translate(), *rotation->Translate(), stdvector);
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
	inline bool Player::SendBossEventPacket(BossEvent type, String^ name, float percent, BossEventColour colour, int overlay)
	{
		return NativePtr->sendBossEventPacket(::BossEvent(type), marshalString(name), percent, ::BossEventColour(colour), overlay);
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
	inline bool Player::SendToastPacket(String^ title, String^ msg) { return NativePtr->sendToastPacket(marshalString(title), marshalString(msg)); }
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

#ifdef MANUAL_MAINTENANCE


	::System::String^ MC::Player::DeviceName::get()
	{
		auto __ret = NativePtr->getDeviceName();
		return clix::marshalString<clix::E_UTF8>(__ret);
	}

	bool MC::Player::Sleeping::get()
	{
		return NativePtr->isSleeping();
	}

	float MC::Player::Speed::get()
	{
		return NativePtr->getSpeed();
	}

	int MC::Player::SleepTimer::get()
	{
		return NativePtr->getSleepTimer();
	}

	int MC::Player::PreviousTickSleepTimer::get()
	{
		auto __ret = NativePtr->getPreviousTickSleepTimer();
		return __ret;
	}

	bool MC::Player::IsHostingPlayer::get()
	{
		return NativePtr->isHostingPlayer();
	}

	bool MC::Player::IsLoading::get()
	{
		return NativePtr->isLoading();
	}

	bool MC::Player::IsPlayerInitialized::get()
	{
		return NativePtr->isPlayerInitialized();
	}

	bool MC::Player::IsTeacher::get()
	{
		return NativePtr->isTeacher();
	}

	int MC::Player::MaxItemCooldownLeft::get()
	{
		return NativePtr->getMaxItemCooldownLeft();
	}

	bool MC::Player::ForceAllowEating::get()
	{
		return NativePtr->forceAllowEating();
	}

	MC::ActorUniqueID MC::Player::AgentID::get()
	{
		return NativePtr->getAgentID();
	}

	MC::BlockPos MC::Player::BedPosition::get()
	{
		return NativePtr->getBedPosition();
	}

	long long MC::Player::BlockedUsingDamagedShieldTimeStamp::get()
	{
		auto __ret = NativePtr->getBlockedUsingDamagedShieldTimeStamp();
		return __ret;
	}

	long long MC::Player::BlockedUsingShieldTimeStamp::get()
	{
		auto __ret = NativePtr->getBlockedUsingShieldTimeStamp();
		return __ret;
	}

	long long MC::Player::BlockingStartTimeStamp::get()
	{
		auto __ret = NativePtr->getBlockingStartTimeStamp();
		return __ret;
	}

	int MC::Player::Direction::get()
	{
		auto __ret = NativePtr->getDirection();
		return __ret;
	}

	int MC::Player::EnchantmentSeed::get()
	{
		auto __ret = NativePtr->getEnchantmentSeed();
		return __ret;
	}

	void MC::Player::EnchantmentSeed::set(int _0)
	{
		NativePtr->setEnchantmentSeed(_0);
	}

	MC::BlockPos MC::Player::ExpectedSpawnPosition::get()
	{
		return NativePtr->getExpectedSpawnPosition();
	}

	::System::String^ MC::Player::InteractText::get()
	{
		auto __ret = NativePtr->getInteractText();
		return clix::marshalString<clix::E_UTF8>(__ret);
	}

	float MC::Player::Luck::get()
	{
		auto __ret = NativePtr->getLuck();
		return __ret;
	}

	int MC::Player::MapIndex::get()
	{
		auto __ret = NativePtr->getMapIndex();
		return __ret;
	}

	void MC::Player::MapIndex::set(int _0)
	{
		NativePtr->setMapIndex(_0);
	}

	MC::AABB MC::Player::PickupArea::get()
	{
		return NativePtr->getPickupArea();
	}

	::System::String^ MC::Player::PlatformOnlineId::get()
	{
		auto& __ret = NativePtr->getPlatformOnlineId();
		return (::System::String^)(clix::marshalString<clix::E_UTF8>(__ret));
	}

	void MC::Player::PlatformOnlineId::set(::System::String^ _0)
	{
		auto __arg0 = clix::marshalString<clix::E_UTF8>(_0);
		NativePtr->setPlatformOnlineId(__arg0);
	}

	int MC::Player::PlayerIndex::get()
	{
		auto __ret = NativePtr->getPlayerIndex();
		return __ret;
	}

	void MC::Player::PlayerIndex::set(int _0)
	{
		NativePtr->setPlayerIndex(_0);
	}

	int MC::Player::PlayerLevel::get()
	{
		auto __ret = NativePtr->getPlayerLevel();
		return __ret;
	}

	::System::String^ MC::Player::PlayerSessionId::get()
	{
		auto& __ret = NativePtr->getPlayerSessionId();
		return (::System::String^)(clix::marshalString<clix::E_UTF8>(__ret));
	}

	MC::BlockPos MC::Player::RespawnAnchorPosition::get()
	{
		return NativePtr->getRespawnAnchorPosition();
	}

	int MC::Player::SelectedItemSlot::get()
	{
		auto __ret = NativePtr->getSelectedItemSlot();
		return __ret;
	}

	float MC::Player::SleepRotation::get()
	{
		auto __ret = NativePtr->getSleepRotation();
		return __ret;
	}

	MC::BlockPos MC::Player::SpawnPosition::get()
	{
		return NativePtr->getSpawnPosition();
	}

	List<MC::ActorUniqueID>^ MC::Player::TrackedBosses::get()
	{
		auto& vec = NativePtr->getTrackedBosses();
		auto ret = gcnew List<MC::ActorUniqueID>((int)vec.size());
		for (auto& item : vec)
		{
			ret->Add(item);
		}
		return ret;
	}

	bool MC::Player::UsedPotion::get()
	{
		auto __ret = NativePtr->getUsedPotion();
		return __ret;
	}

	void MC::Player::UsedPotion::set(bool _0)
	{
		NativePtr->setUsedPotion(_0);
	}

	int MC::Player::XpNeededForNextLevel::get()
	{
		auto __ret = NativePtr->getXpNeededForNextLevel();
		return __ret;
	}

	bool MC::Player::HasBedPosition::get()
	{
		auto __ret = NativePtr->hasBedPosition();
		return __ret;
	}

	bool MC::Player::HasOpenContainer::get()
	{
		auto __ret = NativePtr->hasOpenContainer();
		return __ret;
	}

	bool MC::Player::HasOwnedChunkSource::get()
	{
		auto __ret = NativePtr->hasOwnedChunkSource();
		return __ret;
	}

	bool MC::Player::HasRespawnAnchorPosition::get()
	{
		auto __ret = NativePtr->hasRespawnAnchorPosition();
		return __ret;
	}

	bool MC::Player::HasRespawnPosition::get()
	{
		auto __ret = NativePtr->hasRespawnPosition();
		return __ret;
	}

	//bool MC::Player::IsBouncing::get()
	//{
	//	auto __ret = NativePtr->isBouncing();
	//	return __ret;
	//}

	bool MC::Player::IsForcedRespawn::get()
	{
		auto __ret = NativePtr->isForcedRespawn();
		return __ret;
	}

	bool MC::Player::IsHungry::get()
	{
		auto __ret = NativePtr->isHungry();
		return __ret;
	}

	bool MC::Player::IsHurt::get()
	{
		auto __ret = NativePtr->isHurt();
		return __ret;
	}

	bool MC::Player::IsInCreativeMode::get()
	{
		auto __ret = NativePtr->isInCreativeMode();
		return __ret;
	}

	bool MC::Player::IsInRaid::get()
	{
		auto __ret = NativePtr->isInRaid();
		return __ret;
	}

	bool MC::Player::IsRespawningFromTheEnd::get()
	{
		auto __ret = NativePtr->isRespawningFromTheEnd();
		return __ret;
	}

	bool MC::Player::IsSleepingLongEnough::get()
	{
		auto __ret = NativePtr->isSleepingLongEnough();
		return __ret;
	}

	bool MC::Player::IsSpawned::get()
	{
		auto __ret = NativePtr->isSpawned();
		return __ret;
	}

	bool MC::Player::IsUsingItem::get()
	{
		auto __ret = NativePtr->isUsingItem();
		return __ret;
	}


	void MC::Player::ServerInitItemStackIds()
	{
		((class ::Player*)NativePtr)->_serverInitItemStackIds();
	}

	void MC::Player::ResetUserPos(bool _0)
	{
		((class ::Player*)NativePtr)->resetUserPos(_0);
	}

	void MC::Player::Remove()
	{
		((class ::Player*)NativePtr)->remove();
	}

	bool MC::Player::isRuntimePredictedMovementEnabled()
	{
		auto __ret = ((class ::Player*)NativePtr)->isRuntimePredictedMovementEnabled();
		return __ret;
	}

	void MC::Player::Move(MC::Vec3 _0)
	{
		((class ::Player*)NativePtr)->move(_0);
	}

	//void MC::Player::UnkVfn40()
	//{
	//	((class ::Player*)NativePtr)->__unk_vfn_40();
	//}

	void MC::Player::TeleportTo(MC::Vec3 _0, bool _1, int _2, int _3, bool _4)
	{
		((class ::Player*)NativePtr)->teleportTo(_0, _1, _2, _3, _4);
	}

	void MC::Player::NormalTick()
	{
		((class ::Player*)NativePtr)->normalTick();
	}

	//void MC::Player::VehicleTick()
	//{
	//	((class ::Player*)NativePtr)->vehicleTick();
	//}

	//float MC::Player::GetRidingHeight()
	//{
	//	auto __ret = ((class ::Player*)NativePtr)->getRidingHeight();
	//	return __ret;
	//}

	//void MC::Player::UnkVfn61()
	//{
	//	((class ::Player*)NativePtr)->__unk_vfn_61();
	//}

	::System::String^ MC::Player::GetFormattedNameTag()
	{
		auto __ret = ((class ::Player*)NativePtr)->getFormattedNameTag();
		return clix::marshalString<clix::E_UTF8>(__ret);
	}

	//void MC::Player::UnkVfn68()
	//{
	//	((class ::Player*)NativePtr)->__unk_vfn_68();
	//}

	float MC::Player::GetCameraOffset()
	{
		auto __ret = ((class ::Player*)NativePtr)->getCameraOffset();
		return __ret;
	}

	//void MC::Player::UnkVfn82()
	//{
	//	((class ::Player*)NativePtr)->__unk_vfn_82();
	//}

	bool MC::Player::CanInteractWithOtherEntitiesInGame()
	{
		auto __ret = ((class ::Player*)NativePtr)->canInteractWithOtherEntitiesInGame();
		return __ret;
	}

	//void MC::Player::UnkVfn88()
	//{
	//	((class ::Player*)NativePtr)->__unk_vfn_88();
	//}

	void MC::Player::PlayerTouch(MC::Player^ _0)
	{
		if (ReferenceEquals(_0, nullptr))
			throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
		auto& __arg0 = *(class ::Player*)_0->NativePtr;
		((class ::Player*)NativePtr)->playerTouch(__arg0);
	}

	bool MC::Player::isImmobile()
	{
		auto __ret = ((class ::Player*)NativePtr)->isImmobile();
		return __ret;
	}

	//void MC::Player::UnkVfn95()
	//{
	//	((class ::Player*)NativePtr)->__unk_vfn_95();
	//}

	void MC::Player::SetSleeping(bool _0)
	{
		((class ::Player*)NativePtr)->setSleeping(_0);
	}

	//void MC::Player::UnkVfn98()
	//{
	//	((class ::Player*)NativePtr)->__unk_vfn_98();
	//}

	bool MC::Player::isBlocking()
	{
		auto __ret = ((class ::Player*)NativePtr)->isBlocking();
		return __ret;
	}

	//void MC::Player::UnkVfn105()
	//{
	//	((class ::Player*)NativePtr)->__unk_vfn_105();
	//}

	//void MC::Player::UnkVfn107()
	//{
	//	((class ::Player*)NativePtr)->__unk_vfn_107();
	//}

	//void MC::Player::UnkVfn108()
	//{
	//	((class ::Player*)NativePtr)->__unk_vfn_108();
	//}

	//void MC::Player::UnkVfn109()
	//{
	//	((class ::Player*)NativePtr)->__unk_vfn_109();
	//}

	//MC::Actor^ MC::Player::findAttackTarget()
	//{
	//	auto __ret = ((class ::Player*)NativePtr)->findAttackTarget();
	//	if (__ret == nullptr) return nullptr;
	//	return (__ret == nullptr) ? nullptr : gcnew ::MC::Actor((class ::Actor*)__ret);
	//}

	bool MC::Player::IsValidTarget(MC::Actor^ _0)
	{
		auto __arg0 = (class ::Actor*)_0->NativePtr;
		auto __ret = ((class ::Player*)NativePtr)->isValidTarget(__arg0);
		return __ret;
	}

	bool MC::Player::Attack(MC::Actor^ _0, MC::ActorDamageCause _1)
	{
		if (ReferenceEquals(_0, nullptr))
			throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
		auto& __arg0 = *(class ::Actor*)_0->NativePtr;
		auto __arg1 = (::ActorDamageCause)_1;
		auto __ret = ((class ::Player*)NativePtr)->attack(__arg0, __arg1);
		return __ret;
	}

	void MC::Player::OnTame()
	{
		((class ::Player*)NativePtr)->onTame();
	}

	void MC::Player::OnFailedTame()
	{
		((class ::Player*)NativePtr)->onFailedTame();
	}

	bool MC::Player::isJumping()
	{
		auto __ret = ((class ::Player*)NativePtr)->isJumping();
		return __ret;
	}

	void MC::Player::VehicleLanded(MC::Vec3 _0, MC::Vec3 _1)
	{
		((class ::Player*)NativePtr)->vehicleLanded(_0, _0);
	}

	void MC::Player::Feed(int _0)
	{
		((class ::Player*)NativePtr)->feed(_0);
	}

	void MC::Player::AwardKillScore(MC::Actor^ _0, int _1)
	{
		if (ReferenceEquals(_0, nullptr))
			throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
		auto& __arg0 = *(class ::Actor*)_0->NativePtr;
		((class ::Player*)NativePtr)->awardKillScore(__arg0, _1);
	}

	bool MC::Player::ConsumeTotem()
	{
		auto __ret = ((class ::Player*)NativePtr)->consumeTotem();
		return __ret;
	}

	MC::ActorUniqueID MC::Player::GetSourceUniqueID()
	{
		return ((class ::Player*)NativePtr)->getSourceUniqueID();
	}

	bool MC::Player::CanFreeze()
	{
		auto __ret = ((class ::Player*)NativePtr)->canFreeze();
		return __ret;
	}

	int MC::Player::GetPortalCooldown()
	{
		auto __ret = ((class ::Player*)NativePtr)->getPortalCooldown();
		return __ret;
	}

	int MC::Player::GetPortalWaitTime()
	{
		auto __ret = ((class ::Player*)NativePtr)->getPortalWaitTime();
		return __ret;
	}

	bool MC::Player::CanChangeDimensions()
	{
		auto __ret = ((class ::Player*)NativePtr)->canChangeDimensions();
		return __ret;
	}

	//void MC::Player::UnkVfn181()
	//{
	//	((class ::Player*)NativePtr)->__unk_vfn_181();
	//}

	MC::ActorUniqueID MC::Player::GetControllingPlayer()
	{
		return ((class ::Player*)NativePtr)->getControllingPlayer();
	}

	void MC::Player::OnSynchedDataUpdate(int _0)
	{
		((class ::Player*)NativePtr)->onSynchedDataUpdate(_0);
	}

	bool MC::Player::CanAddPassenger(MC::Actor^ _0)
	{
		if (ReferenceEquals(_0, nullptr))
			throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
		auto& __arg0 = *(class ::Actor*)_0->NativePtr;
		auto __ret = ((class ::Player*)NativePtr)->canAddPassenger(__arg0);
		return __ret;
	}

	bool MC::Player::CanBePulledIntoVehicle()
	{
		auto __ret = ((class ::Player*)NativePtr)->canBePulledIntoVehicle();
		return __ret;
	}

	//void MC::Player::UnkVfn195()
	//{
	//	((class ::Player*)NativePtr)->__unk_vfn_195();
	//}

	void MC::Player::SendMotionPacketIfNeeded()
	{
		((class ::Player*)NativePtr)->sendMotionPacketIfNeeded();
	}

	bool MC::Player::CanSynchronizeNewEntity()
	{
		auto __ret = ((class ::Player*)NativePtr)->canSynchronizeNewEntity();
		return __ret;
	}

	void MC::Player::StartSwimming()
	{
		((class ::Player*)NativePtr)->startSwimming();
	}

	void MC::Player::StopSwimming()
	{
		((class ::Player*)NativePtr)->stopSwimming();
	}

	//void MC::Player::UnkVfn220()
	//{
	//	((class ::Player*)NativePtr)->__unk_vfn_220();
	//}

	//void MC::Player::UnkVfn221()
	//{
	//	((class ::Player*)NativePtr)->__unk_vfn_221();
	//}

	float MC::Player::GetMapDecorationRotation()
	{
		auto __ret = ((class ::Player*)NativePtr)->getMapDecorationRotation();
		return __ret;
	}

	bool MC::Player::isWorldBuilder()
	{
		auto __ret = ((class ::Player*)NativePtr)->isWorldBuilder();
		return __ret;
	}

	bool MC::Player::isCreative()
	{
		auto __ret = ((class ::Player*)NativePtr)->isCreative();
		return __ret;
	}

	bool MC::Player::isAdventure()
	{
		auto __ret = ((class ::Player*)NativePtr)->isAdventure();
		return __ret;
	}

	bool MC::Player::isSurvival()
	{
		auto __ret = ((class ::Player*)NativePtr)->isSurvival();
		return __ret;
	}

	bool MC::Player::isSpectator()
	{
		auto __ret = ((class ::Player*)NativePtr)->isSpectator();
		return __ret;
	}

	void MC::Player::SetAuxValue(int _0)
	{
		((class ::Player*)NativePtr)->setAuxValue(_0);
	}

	void MC::Player::SetSize(float _0, float _1)
	{
		((class ::Player*)NativePtr)->setSize(_0, _1);
	}

	void MC::Player::StartSpinAttack()
	{
		((class ::Player*)NativePtr)->startSpinAttack();
	}

	void MC::Player::StopSpinAttack()
	{
		((class ::Player*)NativePtr)->stopSpinAttack();
	}

	//void MC::Player::UnkVfn246()
	//{
	//	((class ::Player*)NativePtr)->__unk_vfn_246();
	//}

	//void MC::Player::UnkVfn249()
	//{
	//	((class ::Player*)NativePtr)->__unk_vfn_249();
	//}

	bool MC::Player::ShouldDropDeathLoot()
	{
		auto __ret = ((class ::Player*)NativePtr)->shouldDropDeathLoot();
		return __ret;
	}

	//void MC::Player::UnkVfn261()
	//{
	//	((class ::Player*)NativePtr)->__unk_vfn_261();
	//}

	//void MC::Player::UnkVfn269()
	//{
	//	((class ::Player*)NativePtr)->__unk_vfn_269();
	//}

	void MC::Player::OnSizeUpdated()
	{
		((class ::Player*)NativePtr)->_onSizeUpdated();
	}

	//void MC::Player::UnkVfn278()
	//{
	//	((class ::Player*)NativePtr)->__unk_vfn_278();
	//}

	void MC::Player::SpawnAnim()
	{
		((class ::Player*)NativePtr)->spawnAnim();
	}

	void MC::Player::SetSpeed(float _0)
	{
		((class ::Player*)NativePtr)->setSpeed(_0);
	}

	void MC::Player::Travel(float _0, float _1, float _2)
	{
		((class ::Player*)NativePtr)->travel(_0, _1, _2);
	}

	void MC::Player::AiStep()
	{
		((class ::Player*)NativePtr)->aiStep();
	}

	int MC::Player::GetItemUseDuration()
	{
		auto __ret = ((class ::Player*)NativePtr)->getItemUseDuration();
		return __ret;
	}

	float MC::Player::GetItemUseStartupProgress()
	{
		auto __ret = ((class ::Player*)NativePtr)->getItemUseStartupProgress();
		return __ret;
	}

	float MC::Player::GetItemUseIntervalProgress()
	{
		auto __ret = ((class ::Player*)NativePtr)->getItemUseIntervalProgress();
		return __ret;
	}

	//void MC::Player::UnkVfn307()
	//{
	//	((class ::Player*)NativePtr)->__unk_vfn_307();
	//}

	bool MC::Player::IsAlliedTo(MC::Mob^ _0)
	{
		auto __arg0 = (class ::Mob*)_0->NativePtr;
		auto __ret = ((class ::Player*)NativePtr)->isAlliedTo(__arg0);
		return __ret;
	}

	//void MC::Player::UnkVfn311()
	//{
	//	((class ::Player*)NativePtr)->__unk_vfn_311();
	//}

	void MC::Player::DropEquipmentOnDeath()
	{
		((class ::Player*)NativePtr)->dropEquipmentOnDeath();
	}

	void MC::Player::ClearVanishEnchantedItemsOnDeath()
	{
		((class ::Player*)NativePtr)->clearVanishEnchantedItemsOnDeath();
	}

	void MC::Player::SendInventory(bool _0)
	{
		((class ::Player*)NativePtr)->sendInventory(_0);
	}

	void MC::Player::OnBorn(MC::Actor^ _0, MC::Actor^ _1)
	{
		if (ReferenceEquals(_0, nullptr))
			throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
		auto& __arg0 = *(class ::Actor*)_0->NativePtr;
		if (ReferenceEquals(_1, nullptr))
			throw gcnew ::System::ArgumentNullException("_1", "Cannot be null because it is a C++ reference (&).");
		auto& __arg1 = *(class ::Actor*)_1->NativePtr;
		((class ::Player*)NativePtr)->onBorn(__arg0, __arg1);
	}

	float MC::Player::GetWalkTargetValue(MC::BlockPos _0)
	{
		return ((class ::Player*)NativePtr)->_getWalkTargetValue(_0);
	}

	bool MC::Player::CanExistWhenDisallowMob()
	{
		auto __ret = ((class ::Player*)NativePtr)->canExistWhenDisallowMob();
		return __ret;
	}

	//void MC::Player::UnkVfn345()
	//{
	//	((class ::Player*)NativePtr)->__unk_vfn_345();
	//}

	void MC::Player::JumpFromGround()
	{
		((class ::Player*)NativePtr)->jumpFromGround();
	}

	void MC::Player::UpdateAi()
	{
		((class ::Player*)NativePtr)->updateAi();
	}

	void MC::Player::ServerAiMobStep()
	{
		((class ::Player*)NativePtr)->_serverAiMobStep();
	}

	void MC::Player::UpdateGliding()
	{
		((class ::Player*)NativePtr)->updateGliding();
	}

	//void MC::Player::UnkVfn359()
	//{
	//	((class ::Player*)NativePtr)->__unk_vfn_359();
	//}

	void MC::Player::DestroyRegion()
	{
		((class ::Player*)NativePtr)->destroyRegion();
	}

	void MC::Player::SuspendRegion()
	{
		((class ::Player*)NativePtr)->suspendRegion();
	}

	void MC::Player::ResendAllChunks()
	{
		((class ::Player*)NativePtr)->resendAllChunks();
	}

	void MC::Player::FireWillChangeDimension()
	{
		((class ::Player*)NativePtr)->_fireWillChangeDimension();
	}

	void MC::Player::FireDimensionChanged()
	{
		((class ::Player*)NativePtr)->_fireDimensionChanged();
	}

	void MC::Player::TickWorld(MC::Tick^ _0)
	{
		if (ReferenceEquals(_0, nullptr))
			throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
		auto& __arg0 = *(struct ::Tick*)_0->NativePtr;
		((class ::Player*)NativePtr)->tickWorld(__arg0);
	}

	//void MC::Player::UnkVfn369()
	//{
	//	((class ::Player*)NativePtr)->__unk_vfn_369();
	//}

	void MC::Player::MoveView()
	{
		((class ::Player*)NativePtr)->moveView();
	}

	void MC::Player::CheckMovementStats(MC::Vec3 _0)
	{
		((class ::Player*)NativePtr)->checkMovementStats(_0);
	}

	//void MC::Player::UnkVfn374()
	//{
	//	((class ::Player*)NativePtr)->__unk_vfn_374();
	//}

	//void MC::Player::UnkVfn375()
	//{
	//	((class ::Player*)NativePtr)->__unk_vfn_375();
	//}

	void MC::Player::Respawn()
	{
		((class ::Player*)NativePtr)->respawn();
	}

	//void MC::Player::UnkVfn377()
	//{
	//	((class ::Player*)NativePtr)->__unk_vfn_377();
	//}

	//void MC::Player::UnkVfn378()
	//{
	//	((class ::Player*)NativePtr)->__unk_vfn_378();
	//}

	bool MC::Player::HasResource(int _0)
	{
		auto __ret = ((class ::Player*)NativePtr)->hasResource(_0);
		return __ret;
	}

	void MC::Player::CompleteUsingItem()
	{
		((class ::Player*)NativePtr)->completeUsingItem();
	}

	void MC::Player::StartDestroying()
	{
		((class ::Player*)NativePtr)->startDestroying();
	}

	void MC::Player::StopDestroying()
	{
		((class ::Player*)NativePtr)->stopDestroying();
	}

	//void MC::Player::UnkVfn384()
	//{
	//	((class ::Player*)NativePtr)->__unk_vfn_384();
	//}

	//void MC::Player::UnkVfn385()
	//{
	//	((class ::Player*)NativePtr)->__unk_vfn_385();
	//}

	void MC::Player::OpenTrading(MC::ActorUniqueID _0, bool _1)
	{
		((class ::Player*)NativePtr)->openTrading(_0, _1);
	}

	bool MC::Player::CanOpenContainerScreen()
	{
		auto __ret = ((class ::Player*)NativePtr)->canOpenContainerScreen();
		return __ret;
	}

	//void MC::Player::UnkVfn388()
	//{
	//	((class ::Player*)NativePtr)->__unk_vfn_388();
	//}

	//void MC::Player::UnkVfn389()
	//{
	//	((class ::Player*)NativePtr)->__unk_vfn_389();
	//}

	void MC::Player::OpenInventory()
	{
		((class ::Player*)NativePtr)->openInventory();
	}

	//void MC::Player::UnkVfn391()
	//{
	//	((class ::Player*)NativePtr)->__unk_vfn_391();
	//}

	//void MC::Player::UnkVfn392()
	//{
	//	((class ::Player*)NativePtr)->__unk_vfn_392();
	//}

	void MC::Player::DisplayWhisperMessage(::System::String^ _0, ::System::String^ _1, ::System::String^ _2, ::System::String^ _3)
	{
		auto __arg0 = clix::marshalString<clix::E_UTF8>(_0);
		auto __arg1 = clix::marshalString<clix::E_UTF8>(_1);
		auto __arg2 = clix::marshalString<clix::E_UTF8>(_2);
		auto __arg3 = clix::marshalString<clix::E_UTF8>(_3);
		((class ::Player*)NativePtr)->displayWhisperMessage(__arg0, __arg1, __arg2, __arg3);
	}

	void MC::Player::StopSleepInBed(bool _0, bool _1)
	{
		((class ::Player*)NativePtr)->stopSleepInBed(_0, _1);
	}

	bool MC::Player::CanStartSleepInBed()
	{
		auto __ret = ((class ::Player*)NativePtr)->canStartSleepInBed();
		return __ret;
	}

	//void MC::Player::UnkVfn401()
	//{
	//	((class ::Player*)NativePtr)->__unk_vfn_401();
	//}

	//void MC::Player::UnkVfn402()
	//{
	//	((class ::Player*)NativePtr)->__unk_vfn_402();
	//}

	//void MC::Player::UnkVfn406()
	//{
	//	((class ::Player*)NativePtr)->__unk_vfn_406();
	//}

	void MC::Player::RegisterTrackedBoss(MC::ActorUniqueID _0)
	{
		((class ::Player*)NativePtr)->registerTrackedBoss(_0);
	}

	void MC::Player::UnRegisterTrackedBoss(MC::ActorUniqueID _0)
	{
		((class ::Player*)NativePtr)->unRegisterTrackedBoss(_0);
	}

	void MC::Player::InitHUDContainerManager()
	{
		((class ::Player*)NativePtr)->initHUDContainerManager();
	}

	void MC::Player::Crit(MC::Actor^ _0)
	{
		if (ReferenceEquals(_0, nullptr))
			throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
		auto& __arg0 = *(class ::Actor*)_0->NativePtr;
		((class ::Player*)NativePtr)->_crit(__arg0);
	}

	//void MC::Player::UnkVfn413()
	//{
	//	((class ::Player*)NativePtr)->__unk_vfn_413();
	//}

	void MC::Player::AddExperience(int _0)
	{
		((class ::Player*)NativePtr)->addExperience(_0);
	}

	void MC::Player::AddLevels(int _0)
	{
		((class ::Player*)NativePtr)->addLevels(_0);
	}

	void MC::Player::DeleteContainerManager()
	{
		((class ::Player*)NativePtr)->deleteContainerManager();
	}

	void MC::Player::SetFieldOfViewModifier(float _0)
	{
		((class ::Player*)NativePtr)->setFieldOfViewModifier(_0);
	}

	bool MC::Player::IsActorRelevant(MC::Actor^ _0)
	{
		if (ReferenceEquals(_0, nullptr))
			throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
		auto& __arg0 = *(class ::Actor*)_0->NativePtr;
		auto __ret = ((class ::Player*)NativePtr)->isActorRelevant(__arg0);
		return __ret;
	}

	void MC::Player::OnSuspension()
	{
		((class ::Player*)NativePtr)->onSuspension();
	}

	void MC::Player::OnLinkedSlotsChanged()
	{
		((class ::Player*)NativePtr)->onLinkedSlotsChanged();
	}

	int MC::Player::GetItemCooldownLeft(unsigned long long _0)
	{
		auto __ret = ((class ::Player*)NativePtr)->getItemCooldownLeft(_0);
		return __ret;
	}

	//void MC::Player::UnkVfn441()
	//{
	//	((class ::Player*)NativePtr)->__unk_vfn_441();
	//}

	void MC::Player::OnMovePlayerPacketNormal(MC::Vec3 _0, MC::Vec2 _1, float _2)
	{
		((class ::Player*)NativePtr)->onMovePlayerPacketNormal(_0, _1, _2);
	}

	void MC::Player::ApplyExhaustion(MC::Vec3 _0)
	{
		((class ::Player*)NativePtr)->applyExhaustion(_0);
	}

	bool MC::Player::CanBeSeenOnMap()
	{
		auto __ret = ((class ::Player*)NativePtr)->canBeSeenOnMap();
		return __ret;
	}

	bool MC::Player::CanUseOperatorBlocks()
	{
		auto __ret = ((class ::Player*)NativePtr)->canUseOperatorBlocks();
		return __ret;
	}

	void MC::Player::CauseFoodExhaustion(float _0)
	{
		((class ::Player*)NativePtr)->causeFoodExhaustion(_0);
	}

	void MC::Player::ClearRespawnPosition()
	{
		((class ::Player*)NativePtr)->clearRespawnPosition();
	}

	void MC::Player::Eat(int _0, float _1)
	{
		((class ::Player*)NativePtr)->eat(_0, _1);
	}

	MC::Vec3 MC::Player::GetCapePos(float _0)
	{
		return ((class ::Player*)NativePtr)->getCapePos(_0);
	}

	void MC::Player::GetNewEnchantmentSeed()
	{
		((class ::Player*)NativePtr)->getNewEnchantmentSeed();
	}

	bool MC::Player::HasOpenContainerOfContainerType(MC::ContainerType _0)
	{
		auto __arg0 = (::ContainerType)_0;
		auto __ret = ((class ::Player*)NativePtr)->hasOpenContainerOfContainerType(__arg0);
		return __ret;
	}

	bool MC::Player::Interact(MC::Actor^ _0, MC::Vec3 _1)
	{
		if (ReferenceEquals(_0, nullptr))
			throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
		auto& __arg0 = *(class ::Actor*)_0->NativePtr;
		auto __ret = ((class ::Player*)NativePtr)->interact(__arg0, _1);
		return __ret;
	}

	bool MC::Player::IsHiddenFrom(MC::Mob^ _0)
	{
		if (ReferenceEquals(_0, nullptr))
			throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
		auto& __arg0 = *(class ::Mob*)_0->NativePtr;
		auto __ret = ((class ::Player*)NativePtr)->isHiddenFrom(__arg0);
		return __ret;
	}

	void MC::Player::RecheckSpawnPosition()
	{
		((class ::Player*)NativePtr)->recheckSpawnPosition();
	}

	void MC::Player::ReleaseUsingItem()
	{
		((class ::Player*)NativePtr)->releaseUsingItem();
	}

	void MC::Player::ResetPlayerLevel()
	{
		((class ::Player*)NativePtr)->resetPlayerLevel();
	}

	void MC::Player::ResetToDefaultGameMode()
	{
		((class ::Player*)NativePtr)->resetToDefaultGameMode();
	}

	void MC::Player::SetAllPlayersSleeping()
	{
		((class ::Player*)NativePtr)->setAllPlayersSleeping();
	}

	void MC::Player::SetBedRespawnPosition(MC::BlockPos _0)
	{
		((class ::Player*)NativePtr)->setBedRespawnPosition(_0);
	}

	void MC::Player::SetBlockRespawnUntilClientMessage(bool _0)
	{
		((class ::Player*)NativePtr)->setBlockRespawnUntilClientMessage(_0);
	}

	void MC::Player::SetChunkRadius(unsigned int _0)
	{
		((class ::Player*)NativePtr)->setChunkRadius(_0);
	}

	void MC::Player::SetHasSeenCredits(bool _0)
	{
		((class ::Player*)NativePtr)->setHasSeenCredits(_0);
	}

	void MC::Player::SetRespawnPositionCandidate()
	{
		((class ::Player*)NativePtr)->setRespawnPositionCandidate();
	}

	void MC::Player::SetRespawnReady(MC::Vec3 _0)
	{
		((class ::Player*)NativePtr)->setRespawnReady(_0);
	}

	bool MC::Player::ShouldShowCredits()
	{
		auto __ret = ((class ::Player*)NativePtr)->shouldShowCredits();
		return __ret;
	}

	void MC::Player::SpawnExperienceOrb(MC::Vec3 _0, int _1)
	{
		((class ::Player*)NativePtr)->spawnExperienceOrb(_0, _1);
	}

	void MC::Player::StartGliding()
	{
		((class ::Player*)NativePtr)->startGliding();
	}

	void MC::Player::StopGliding()
	{
		((class ::Player*)NativePtr)->stopGliding();
	}

	void MC::Player::StopUsingItem()
	{
		((class ::Player*)NativePtr)->stopUsingItem();
	}

	bool MC::Player::Take(MC::Actor^ _0, int _1, int _2)
	{
		if (ReferenceEquals(_0, nullptr))
			throw gcnew ::System::ArgumentNullException("_0", "Cannot be null because it is a C++ reference (&).");
		auto& __arg0 = *(class ::Actor*)_0->NativePtr;
		auto __ret = ((class ::Player*)NativePtr)->take(__arg0, _1, _2);
		return __ret;
	}

	void MC::Player::UpdateInventoryTransactions()
	{
		((class ::Player*)NativePtr)->updateInventoryTransactions();
	}

	void MC::Player::UpdateSpawnChunkView()
	{
		((class ::Player*)NativePtr)->updateSpawnChunkView();
	}

	void MC::Player::UpdateTrackedBosses()
	{
		((class ::Player*)NativePtr)->updateTrackedBosses();
	}


	float MC::Player::DEFAULT_BB_HEIGHT::get()
	{
		return ::Player::DEFAULT_BB_HEIGHT;
	}

	float MC::Player::DEFAULT_BB_WIDTH::get()
	{
		return ::Player::DEFAULT_BB_WIDTH;
	}

	float MC::Player::DEFAULT_FLY_SPEED::get()
	{
		return ::Player::DEFAULT_FLY_SPEED;
	}

	float MC::Player::DEFAULT_PLAYER_HEIGHT_OFFSET::get()
	{
		return ::Player::DEFAULT_PLAYER_HEIGHT_OFFSET;
	}

	float MC::Player::DEFAULT_WALK_SPEED::get()
	{
		return ::Player::DEFAULT_WALK_SPEED;
	}

	float MC::Player::DISTANCE_TO_TRANSFORM_EVENT::get()
	{
		return ::Player::DISTANCE_TO_TRANSFORM_EVENT;
	}

	float MC::Player::DISTANCE_TO_TRAVELLED_EVENT::get()
	{
		return ::Player::DISTANCE_TO_TRAVELLED_EVENT;
	}

	int MC::Player::GLIDE_STOP_DELAY::get()
	{
		return ::Player::GLIDE_STOP_DELAY;
	}

	int MC::Player::ITEM_USE_INTERVAL_DURATION::get()
	{
		return ::Player::ITEM_USE_INTERVAL_DURATION;
	}

	int MC::Player::MAX_ITEM_USE_DURATION::get()
	{
		return ::Player::MAX_ITEM_USE_DURATION;
	}

	float MC::Player::PLAYER_ALIVE_HEIGHT::get()
	{
		return ::Player::PLAYER_ALIVE_HEIGHT;
	}

	float MC::Player::PLAYER_ALIVE_WIDTH::get()
	{
		return ::Player::PLAYER_ALIVE_WIDTH;
	}

	float MC::Player::PLAYER_DEAD_HEIGHT::get()
	{
		return ::Player::PLAYER_DEAD_HEIGHT;
	}

	float MC::Player::PLAYER_DEAD_WIDTH::get()
	{
		return ::Player::PLAYER_DEAD_WIDTH;
	}

	float MC::Player::PLAYER_DOWN_SWIM_SPEED::get()
	{
		return ::Player::PLAYER_DOWN_SWIM_SPEED;
	}

	float MC::Player::PLAYER_GLIDING_CAMERA_OFFSET::get()
	{
		return ::Player::PLAYER_GLIDING_CAMERA_OFFSET;
	}

	float MC::Player::PLAYER_SLEEPING_CAMERA_OFFSET::get()
	{
		return ::Player::PLAYER_SLEEPING_CAMERA_OFFSET;
	}

	float MC::Player::PLAYER_SLEEPING_HEIGHT::get()
	{
		return ::Player::PLAYER_SLEEPING_HEIGHT;
	}

	float MC::Player::PLAYER_SLEEPING_WIDTH::get()
	{
		return ::Player::PLAYER_SLEEPING_WIDTH;
	}

	float MC::Player::PLAYER_SNEAK_OFFSET::get()
	{
		return ::Player::PLAYER_SNEAK_OFFSET;
	}

	float MC::Player::PLAYER_SWIMMING_CAMERA_OFFSET::get()
	{
		return ::Player::PLAYER_SWIMMING_CAMERA_OFFSET;
	}

	float MC::Player::PLAYER_SWIM_BREACH_ANGLE::get()
	{
		return ::Player::PLAYER_SWIM_BREACH_ANGLE;
	}

	float MC::Player::PLAYER_SWIM_ENTER_THRESHOLD::get()
	{
		return ::Player::PLAYER_SWIM_ENTER_THRESHOLD;
	}

	float MC::Player::PLAYER_SWIM_FLY_MULTI::get()
	{
		return ::Player::PLAYER_SWIM_FLY_MULTI;
	}

	float MC::Player::PLAYER_UP_SWIM_SPEED::get()
	{
		return ::Player::PLAYER_UP_SWIM_SPEED;
	}

	unsigned int MC::Player::SPAWN_CHUNK_LARGE_JUMP::get()
	{
		return ::Player::SPAWN_CHUNK_LARGE_JUMP;
	}

	unsigned int MC::Player::SPAWN_CHUNK_RADIUS::get()
	{
		return ::Player::SPAWN_CHUNK_RADIUS;
	}

#endif // MANUAL_MAINTENANCE


} // namespace MC