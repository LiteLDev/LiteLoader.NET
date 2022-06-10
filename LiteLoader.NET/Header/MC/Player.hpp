#pragma once
#include <MC/Player.hpp>
#include "Mob.hpp"

namespace MC
{
	ref class NetworkIdentifier;
	ref class Certificate;
	ref struct ScorePacketInfo;
	ref class BlockPos;
	value class Vec3;
	ref class Mob;
	ref class Container;
	ref class ItemStack;
	ref class CompoundTag;
	ref class Attribute;

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

		property String^ Name { String^ get(); };
		property String^ RealName { String^ get(); };
		property String^ Uuid { String^ get(); };
		property String^ Xuid { String^ get(); };
		property String^ IP { String^ get(); };
		property String^ LanguageCode { String^ get(); };
		property String^ ServerAddress { String^ get(); };
		property NetworkIdentifier^ NetworkIdentifier { MC::NetworkIdentifier^ get(); };
		property Certificate^ Certificate { MC::Certificate^ get(); };
		property Container^ EnderChestContainer { Container^ get(); };

		property unsigned char ClientSubId
		{
			unsigned char get();
		};
		property String^ DeviceTypeName { String^ get(); };
		property int AvgPing
		{
			int get();
		}
		property int LastPing
		{
			int get();
		}
		property Pair<MC::BlockPos^, int> RespawnPosition
		{
			Pair<MC::BlockPos^, int> get();
		};
		property float AvgPacketLoss
		{
			float get();
		}
		property String^ ClientId { String^ get(); };
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
		inline bool GiveItem(ItemStack^ item);
		inline int ClearItem(String^ typeName);
		inline bool Runcmd(String^ cmd);
		inline bool TransferServer(String^ address, unsigned short port);
		inline bool SetSidebar(String^ title, List<System::Tuple<String^, int>^>^ data, ObjectiveSortOrder sortOrder);
		inline bool RemoveSidebar();
		inline CompoundTag^ GetNbt();
		inline bool SetNbt(CompoundTag^ nbt);
		inline bool RefreshAttribute(Attribute^ attribute);
		inline bool RefreshAttributes(List<Attribute^>^ attributes);

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
		inline bool SendSpawnParticleEffectPacket(Vec3 spawnPos, int dimid, String^ ParticleName, int64_t EntityUniqueID);
		/*bad*/ inline bool SendPlaySoundPacket(String^ SoundName, Vec3 Position, float Volume, float Pitch);


		inline bool SendTransferPacket(String^ address, short port);
		inline bool SendSetDisplayObjectivePacket(String^ title, String^ name, char sortOrder);
		inline bool SendSetScorePacket(char type, List<ScorePacketInfo^>^ data);
		/// <param name="overlay">:default = 0</param>
		inline bool SendBossEventPacket(BossEvent type, String^ name, float percent, BossEventColour colour, int overlay);
		inline bool SendCommandRequestPacket(String^ cmd);
		inline bool SendTextTalkPacket(String^ msg);

		inline bool SendRawFormPacket(unsigned formId, String^ data);
		delegate void callBackFunc_int(int);
		inline bool SendSimpleFormPacket(String^ title, String^ content, List<String^>^ buttons, List<String^>^ images, callBackFunc_int^ callback);
		delegate void callBackFunc_bool(bool);
		inline bool SendModalFormPacket(String^ title, String^ content, String^ button1, String^ button2, callBackFunc_bool^ callback);
		delegate void callBackFunc_String(std::string);
		inline bool SendCustomFormPacket(
			String^ data,
			callBackFunc_String^ callback);

		inline static bool IsValid(Player^ player);
		delegate void ModalForm_callback(bool);
		delegate void SimpleForm_callback(int);
		delegate void CustomForm_callback(String^);


	private:
	public:
		bool SendModalForm(String^ title,
			String^ content,
			String^ button1,
			String^ button2,
			ModalForm_callback^ callback);

		bool SendSimpleForm(String^ title,
			String^ content,
			List<String^>^ buttons,
			List<String^>^ images,
			SimpleForm_callback^ callback);

	private:
		inline void NATIVECALLBACK CustomForm_Func(std::string str);
		delegate void dgCustomForm_Func(std::string);
		CustomForm_callback^ __func;

	public:
		bool SendCustomForm(String^ json, CustomForm_callback^ callback);


#ifdef MANUAL_MAINTENANCE

		property ::System::String^ DeviceName
		{
			::System::String^ get();
		}

		property bool Sleeping
		{
			bool get();
		}

		property float Speed
		{
			float get();
		}

		property int SleepTimer
		{
			int get();
		}

		property int PreviousTickSleepTimer
		{
			int get();
		}

		property bool IsHostingPlayer
		{
			bool get();
		}

		property bool IsLoading
		{
			bool get();
		}

		property bool IsPlayerInitialized
		{
			bool get();
		}

		property bool IsTeacher
		{
			bool get();
		}

		property int MaxItemCooldownLeft
		{
			int get();
		}

		property bool ForceAllowEating
		{
			bool get();
		}

		property MC::ActorUniqueID^ AgentID
		{
			MC::ActorUniqueID^ get();
		}

		property MC::BlockPos^ BedPosition
		{
			MC::BlockPos^ get();
		}

		property long long BlockedUsingDamagedShieldTimeStamp
		{
			long long get();
		}

		property long long BlockedUsingShieldTimeStamp
		{
			long long get();
		}

		property long long BlockingStartTimeStamp
		{
			long long get();
		}

		property int Direction
		{
			int get();
		}

		property int EnchantmentSeed
		{
			int get();
			void set(int);
		}

		property MC::BlockPos^ ExpectedSpawnPosition
		{
			MC::BlockPos^ get();
		}

		property ::System::String^ InteractText
		{
			::System::String^ get();
		}

		property float Luck
		{
			float get();
		}

		property int MapIndex
		{
			int get();
			void set(int);
		}

		property MC::AABB^ PickupArea
		{
			MC::AABB^ get();
		}

		property ::System::String^ PlatformOnlineId
		{
			::System::String^ get();
			void set(::System::String^);
		}

		property int PlayerIndex
		{
			int get();
			void set(int);
		}

		property int PlayerLevel
		{
			int get();
		}

		property ::System::String^ PlayerSessionId
		{
			::System::String^ get();
		}

		property MC::BlockPos^ RespawnAnchorPosition
		{
			MC::BlockPos^ get();
		}

		property int SelectedItemSlot
		{
			int get();
		}

		property float SleepRotation
		{
			float get();
		}

		property MC::BlockPos^ SpawnPosition
		{
			MC::BlockPos^ get();
		}

		property ::System::Collections::Generic::List<MC::ActorUniqueID^>^ TrackedBosses
		{
			::System::Collections::Generic::List<MC::ActorUniqueID^>^ get();
		}

		property bool UsedPotion
		{
			bool get();
			void set(bool);
		}

		property int XpNeededForNextLevel
		{
			int get();
		}

		property bool HasBedPosition
		{
			bool get();
		}

		property bool HasOpenContainer
		{
			bool get();
		}

		property bool HasOwnedChunkSource
		{
			bool get();
		}

		property bool HasRespawnAnchorPosition
		{
			bool get();
		}

		property bool HasRespawnPosition
		{
			bool get();
		}

		property bool IsBouncing
		{
			bool get();
		}

		property bool IsForcedRespawn
		{
			bool get();
		}

		property bool IsHungry
		{
			bool get();
		}

		property bool IsHurt
		{
			bool get();
		}

		property bool IsInCreativeMode
		{
			bool get();
		}

		property bool IsInRaid
		{
			bool get();
		}

		property bool IsRespawningFromTheEnd
		{
			bool get();
		}

		property bool IsSleepingLongEnough
		{
			bool get();
		}

		property bool IsSpawned
		{
			bool get();
		}

		property bool IsUsingItem
		{
			bool get();
		}

		virtual void ServerInitItemStackIds() override;

		virtual void ResetUserPos(bool _0) override;

		virtual void Remove() override;

		virtual bool isRuntimePredictedMovementEnabled();

		virtual void Move(MC::Vec3 _0) override;

		//virtual void UnkVfn40() override;

		virtual void TeleportTo(MC::Vec3 _0, bool _1, int _2, int _3) override;

		virtual void NormalTick() override;

		virtual void VehicleTick() override;

		virtual float GetRidingHeight();

		//virtual void UnkVfn61() override;

		virtual ::System::String^ GetFormattedNameTag();

		//virtual void UnkVfn68() override;

		virtual float GetCameraOffset();

		//virtual void UnkVfn82() override;

		virtual bool CanInteractWithOtherEntitiesInGame() override;

		//virtual void UnkVfn88() override;

		virtual void PlayerTouch(MC::Player^ _0) override;

		virtual bool isImmobile();

		//virtual void UnkVfn95() override;

		virtual void SetSleeping(bool _0);

		//virtual void UnkVfn98() override;

		virtual bool isBlocking();

		//virtual void UnkVfn105() override;

		//virtual void UnkVfn107() override;

		//virtual void UnkVfn108() override;

		//virtual void UnkVfn109() override;

		virtual MC::Actor^ findAttackTarget();

		virtual bool IsValidTarget(MC::Actor^ _0) override;

		virtual bool Attack(MC::Actor^ _0, MC::ActorDamageCause _1) override;

		virtual void OnTame() override;

		virtual void OnFailedTame() override;

		virtual bool isJumping();

		virtual void VehicleLanded(MC::Vec3 _0, MC::Vec3 _1) override;

		virtual void Feed(int _0) override;

		virtual void AwardKillScore(MC::Actor^ _0, int _1) override;

		virtual bool ConsumeTotem() override;

		virtual MC::ActorUniqueID^ GetSourceUniqueID();

		virtual bool CanFreeze() override;

		virtual int GetPortalCooldown();

		virtual int GetPortalWaitTime();

		virtual bool CanChangeDimensions() override;

		//virtual void UnkVfn181() override;

		virtual MC::ActorUniqueID^ GetControllingPlayer();

		virtual void OnSynchedDataUpdate(int _0) override;

		virtual bool CanAddPassenger(MC::Actor^ _0) override;

		virtual bool CanBePulledIntoVehicle() override;

		//virtual void UnkVfn195() override;

		virtual void SendMotionPacketIfNeeded() override;

		virtual bool CanSynchronizeNewEntity() override;

		virtual void StartSwimming() override;

		virtual void StopSwimming() override;

		//virtual void UnkVfn220() override;

		//virtual void UnkVfn221() override;

		virtual float GetMapDecorationRotation();

		virtual bool isWorldBuilder();

		virtual bool isCreative();

		virtual bool isAdventure();

		virtual bool isSurvival();

		virtual bool isSpectator();

		virtual void SetAuxValue(int _0) override;

		virtual void SetSize(float _0, float _1) override;

		virtual void StartSpinAttack() override;

		virtual void StopSpinAttack() override;

		//virtual void UnkVfn246() override;

		//virtual void UnkVfn249() override;

		virtual bool ShouldDropDeathLoot() override;

		//virtual void UnkVfn261() override;

		/// <summary>
		/// <para>*265*/ virtual void readAdditionalSaveData(class CompoundTag const&amp;, class DataLoadHelper&amp;);</para>
		/// <para>*266*/ virtual void addAdditionalSaveData(class CompoundTag&amp;);</para>
		/// </summary>
		//virtual void UnkVfn269() override;

		virtual void OnSizeUpdated() override;

		//virtual void UnkVfn278() override;

		virtual void SpawnAnim() override;

		virtual void SetSpeed(float _0);

		virtual void Travel(float _0, float _1, float _2) override;

		virtual void AiStep() override;

		virtual int GetItemUseDuration();

		virtual float GetItemUseStartupProgress();

		virtual float GetItemUseIntervalProgress();

		//virtual void UnkVfn307() override;

		virtual bool IsAlliedTo(MC::Mob^ _0) override;

		//virtual void UnkVfn311() override;

		virtual void DropEquipmentOnDeath() override;

		virtual void ClearVanishEnchantedItemsOnDeath() override;

		virtual void SendInventory(bool _0) override;

		virtual void OnBorn(MC::Actor^ _0, MC::Actor^ _1) override;

		virtual float GetWalkTargetValue(MC::BlockPos^ _0) override;

		virtual bool CanExistWhenDisallowMob() override;

		//virtual void UnkVfn345() override;

		virtual void JumpFromGround() override;

		virtual void UpdateAi() override;

		virtual void ServerAiMobStep() override;

		virtual void UpdateGliding() override;

		//virtual void UnkVfn359() override;

		virtual void DestroyRegion();

		virtual void SuspendRegion();

		virtual void ResendAllChunks();

		virtual void FireWillChangeDimension();

		virtual void FireDimensionChanged();

		virtual void TickWorld(MC::Tick^ _0);

		//virtual void UnkVfn369();

		virtual void MoveView();

		virtual void CheckMovementStats(MC::Vec3 _0);

		//virtual void UnkVfn374();

		//virtual void UnkVfn375();

		virtual void Respawn();

		//virtual void UnkVfn377();

		//virtual void UnkVfn378();

		virtual bool HasResource(int _0);

		virtual void CompleteUsingItem();

		virtual void StartDestroying();

		virtual void StopDestroying();

		//virtual void UnkVfn384();

		//virtual void UnkVfn385();

		virtual void OpenTrading(MC::ActorUniqueID^ _0, bool _1);

		virtual bool CanOpenContainerScreen();

		//virtual void UnkVfn388();

		//virtual void UnkVfn389();

		virtual void OpenInventory();

		//virtual void UnkVfn391();

		//virtual void UnkVfn392();

		virtual void DisplayWhisperMessage(::System::String^ _0, ::System::String^ _1, ::System::String^ _2, ::System::String^ _3);

		virtual void StopSleepInBed(bool _0, bool _1);

		virtual bool CanStartSleepInBed();

		//virtual void UnkVfn401();

		//virtual void UnkVfn402();

		//virtual void UnkVfn406();

		virtual void RegisterTrackedBoss(MC::ActorUniqueID^ _0);

		virtual void UnRegisterTrackedBoss(MC::ActorUniqueID^ _0);

		virtual void InitHUDContainerManager();

		virtual void Crit(MC::Actor^ _0);

		//virtual void UnkVfn413();

		virtual void AddExperience(int _0);

		virtual void AddLevels(int _0);

		virtual void DeleteContainerManager();

		virtual void SetFieldOfViewModifier(float _0);

		virtual bool IsActorRelevant(MC::Actor^ _0);

		virtual void OnSuspension();

		virtual void OnLinkedSlotsChanged();

		virtual int GetItemCooldownLeft(unsigned long long _0);

		//virtual void UnkVfn441();

		virtual void OnMovePlayerPacketNormal(MC::Vec3 _0, MC::Vec2 _1, float _2);

		void ApplyExhaustion(MC::Vec3 _0);

		bool CanBeSeenOnMap();

		bool CanUseOperatorBlocks();

		void CauseFoodExhaustion(float _0);

		void ClearRespawnPosition();

		void Eat(int _0, float _1);

		MC::Vec3 GetCapePos(float _0);

		void GetNewEnchantmentSeed();

		bool HasOpenContainerOfContainerType(MC::ContainerType _0);

		bool Interact(MC::Actor^ _0, MC::Vec3 _1);

		bool IsHiddenFrom(MC::Mob^ _0);

		void RecheckSpawnPosition();

		void ReleaseUsingItem();

		void ResetPlayerLevel();

		void ResetToDefaultGameMode();

		void SetAllPlayersSleeping();

		void SetBedRespawnPosition(MC::BlockPos^ _0);

		void SetBlockRespawnUntilClientMessage(bool _0);

		void SetChunkRadius(unsigned int _0);

		void SetHasSeenCredits(bool _0);

		void SetRespawnPositionCandidate();

		void SetRespawnReady(MC::Vec3 _0);

		bool ShouldShowCredits();

		void SpawnExperienceOrb(MC::Vec3 _0, int _1);

		void StartGliding();

		void StopGliding();

		void StopUsingItem();

		bool Take(MC::Actor^ _0, int _1, int _2);

		void UpdateInventoryTransactions();

		void UpdateSpawnChunkView();

		void UpdateTrackedBosses();

		static property float DEFAULT_BB_HEIGHT
		{
			float get();
		}

		static property float DEFAULT_BB_WIDTH
		{
			float get();
		}

		static property float DEFAULT_FLY_SPEED
		{
			float get();
		}

		static property float DEFAULT_PLAYER_HEIGHT_OFFSET
		{
			float get();
		}

		static property float DEFAULT_WALK_SPEED
		{
			float get();
		}

		static property float DISTANCE_TO_TRANSFORM_EVENT
		{
			float get();
		}

		static property float DISTANCE_TO_TRAVELLED_EVENT
		{
			float get();
		}

		static property int GLIDE_STOP_DELAY
		{
			int get();
		}

		static property int ITEM_USE_INTERVAL_DURATION
		{
			int get();
		}

		static property int MAX_ITEM_USE_DURATION
		{
			int get();
		}

		static property float PLAYER_ALIVE_HEIGHT
		{
			float get();
		}

		static property float PLAYER_ALIVE_WIDTH
		{
			float get();
		}

		static property float PLAYER_DEAD_HEIGHT
		{
			float get();
		}

		static property float PLAYER_DEAD_WIDTH
		{
			float get();
		}

		static property float PLAYER_DOWN_SWIM_SPEED
		{
			float get();
		}

		static property float PLAYER_GLIDING_CAMERA_OFFSET
		{
			float get();
		}

		static property float PLAYER_SLEEPING_CAMERA_OFFSET
		{
			float get();
		}

		static property float PLAYER_SLEEPING_HEIGHT
		{
			float get();
		}

		static property float PLAYER_SLEEPING_WIDTH
		{
			float get();
		}

		static property float PLAYER_SNEAK_OFFSET
		{
			float get();
		}

		static property float PLAYER_SWIMMING_CAMERA_OFFSET
		{
			float get();
		}

		static property float PLAYER_SWIM_BREACH_ANGLE
		{
			float get();
		}

		static property float PLAYER_SWIM_ENTER_THRESHOLD
		{
			float get();
		}

		static property float PLAYER_SWIM_FLY_MULTI
		{
			float get();
		}

		static property float PLAYER_UP_SWIM_SPEED
		{
			float get();
		}

		static property unsigned int SPAWN_CHUNK_LARGE_JUMP
		{
			unsigned int get();
		}

		static property unsigned int SPAWN_CHUNK_RADIUS
		{
			unsigned int get();
		}
#endif
	};


} // namespace MC