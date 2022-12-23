#pragma once
#include <mc/Player.hpp>
#include "BlockPos.hpp"
#include "Mob.hpp"
#include <mc/MobEffect.hpp>

namespace MC
{
    ref class Attribute;
    ref class NetworkIdentifier;
    ref class Certificate;
    ref struct ScorePacketInfo;
    value class BlockPos;
    value class Vec3;
    ref class Mob;
    ref class Container;
    ref class ItemStack;
    ref class CompoundTag;
    ref class Packet;
    ref class SerializedSkin;
} // namespace MC

namespace MC
{
    public ref class Player : Mob
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
        property SerializedSkin^ Skin { SerializedSkin^ get(); }

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
        property VALUE_TUPLE<MC::BlockPos, int> RespawnPosition
        {
            VALUE_TUPLE<MC::BlockPos, int> get();
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

        /// <summary> 
        /// <exception cref="LiteLoader::NET::MCException"></exception>
        /// </summary>
        property int CurrentExperience
        {
            int get();
            void set(int value);
        }

        /// <summary>
        /// <exception cref="LiteLoader::NET::MCException"></exception>
        /// </summary>
        property size_t TotalExperience
        {
            size_t get();
            void set(size_t value);
        }

        bool ReduceExperience(size_t exp);

        /// <summary>
        /// Experience required to upgrade to level from (level-1)
        /// </summary>
        static int GetXpNeededForLevel(int level);

        /// <summary>
        /// Experience required to upgrade to level from level 0
        /// </summary>
        static size_t GetTotalXpNeededForLevel(int level);

        inline bool Kick(String^ msg);
        inline bool CrashClient();
        /// <param name="type">:default = TextType::RAW</param>
        inline bool SendText(String^ text, TextType type);
        inline bool SendText(String^ text);

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
        // PacketEX
        inline void SendNetworkPacket(Packet^ packet);
        /// <param name="Type">:default = TextType::RAW</param>
        inline bool SendTextPacket(String^ text, TextType Type);
        inline bool SendTitlePacket(String^ text, TitleType Type, int FadeInDuration, int RemainDuration,
                                    int FadeOutDuration);
        inline bool SendNotePacket(unsigned int tone);
        /// <param name="EntityUniqueID">:default = -1</param>
        inline bool SendSpawnParticleEffectPacket(Vec3 spawnPos, int dimid, String^ ParticleName,
                                                  int64_t EntityUniqueID);
        /*bad*/
        inline bool SendPlaySoundPacket(String^ SoundName, Vec3 Position, float Volume, float Pitch);


        inline bool SendTransferPacket(String^ address, short port);
        inline bool SendSetDisplayObjectivePacket(String^ title, String^ name, char sortOrder);
        inline bool SendSetScorePacket(char type, List<ScorePacketInfo^>^ data);
        /// <param name="overlay">:default = 0</param>
        inline bool SendBossEventPacket(BossEvent type, String^ name, float percent, BossEventColour colour,
                                        int overlay);
        inline bool SendCommandRequestPacket(String^ cmd);
        inline bool SendTextTalkPacket(String^ msg);

        inline bool SendRawFormPacket(unsigned formId, String^ data);
        inline bool SendToastPacket(String^ title, String^ msg);
        delegate void callBackFunc_int(int);
        inline bool SendSimpleFormPacket(String^ title, String^ content, List<String^>^ buttons, List<String^>^ images,
                                         callBackFunc_int^ callback);
        delegate void callBackFunc_bool(bool);
        inline bool SendModalFormPacket(String^ title, String^ content, String^ button1, String^ button2,
                                        callBackFunc_bool^ callback);
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

        enum class GameType
        {
            Survival = 0,
            Creative = 1,
            Adventure = 2,
        };

        virtual property GameType GameMode
        {
            GameType get();
            void set(GameType);
        }


#ifdef MANUAL_MAINTENANCE

        property String^ DeviceName
        {
            String^ get();
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

        property ActorUniqueID AgentID
        {
            ActorUniqueID get();
        }

        property MC::BlockPos BedPosition
        {
            MC::BlockPos get();
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

        property MC::BlockPos ExpectedSpawnPosition
        {
            MC::BlockPos get();
        }

        property String^ InteractText
        {
            String^ get();
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

        property MC::AABB PickupArea
        {
            MC::AABB get();
        }

        property String^ PlatformOnlineId
        {
            String^ get();
            void set(String^);
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

        property String^ PlayerSessionId
        {
            String^ get();
        }

        property MC::BlockPos RespawnAnchorPosition
        {
            MC::BlockPos get();
        }

        property int SelectedItemSlot
        {
            int get();
        }

        property float SleepRotation
        {
            float get();
        }

        property MC::BlockPos SpawnPosition
        {
            MC::BlockPos get();
        }

        property List<ActorUniqueID>^ TrackedBosses
        {
            List<ActorUniqueID>^ get();
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

        //property bool IsBouncing
        //{
        //    bool get();
        //}

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

        void ServerInitItemStackIds() override;

        void ResetUserPos(bool _0) override;

        void Remove() override;

        virtual bool isRuntimePredictedMovementEnabled();

        void Move(Vec3 _0) override;

        //virtual void UnkVfn40() override;

        void TeleportTo(Vec3 _0, bool _1, int _2, int _3, bool _4) override;

        void NormalTick() override;

        //virtual void VehicleTick() override;

        //virtual float GetRidingHeight();

        //virtual void UnkVfn61() override;

        virtual String^ GetFormattedNameTag();

        //virtual void UnkVfn68() override;

        virtual float GetCameraOffset();

        //virtual void UnkVfn82() override;

        //bool CanInteractWithOtherEntitiesInGame() override;

        //virtual void UnkVfn88() override;

        void PlayerTouch(Player^ _0) override;

        virtual bool isImmobile();

        //virtual void UnkVfn95() override;

        virtual void SetSleeping(bool _0);

        //virtual void UnkVfn98() override;

        virtual bool isBlocking();

        //virtual void UnkVfn105() override;

        //virtual void UnkVfn107() override;

        //virtual void UnkVfn108() override;

        //virtual void UnkVfn109() override;

        //virtual MC::Actor^ findAttackTarget();

        bool IsValidTarget(Actor^ _0) override;

        bool Attack(Actor^ _0, ActorDamageCause _1) override;

        void OnTame() override;

        void OnFailedTame() override;

        virtual bool isJumping();

        void VehicleLanded(Vec3 _0, Vec3 _1) override;

        void Feed(int _0) override;

        void AwardKillScore(Actor^ _0, int _1) override;

        bool ConsumeTotem() override;

        virtual ActorUniqueID GetSourceUniqueID();

        bool CanFreeze() override;

        virtual int GetPortalCooldown();

        virtual int GetPortalWaitTime();

        //bool CanChangeDimensions() override;

        //virtual void UnkVfn181() override;

        virtual ActorUniqueID GetControllingPlayer();

        void OnSynchedDataUpdate(int _0) override;

        bool CanAddPassenger(Actor^ _0) override;

        bool CanBePulledIntoVehicle() override;

        //virtual void UnkVfn195() override;

        void SendMotionPacketIfNeeded() override;

        bool CanSynchronizeNewEntity() override;

        void StartSwimming() override;

        void StopSwimming() override;

        //virtual void UnkVfn220() override;

        //virtual void UnkVfn221() override;

        virtual float GetMapDecorationRotation();

        virtual bool isWorldBuilder();

        virtual bool isCreative();

        virtual bool isAdventure();

        virtual bool isSurvival();

        virtual bool isSpectator();

        void SetAuxValue(int _0) override;

        void SetSize(float _0, float _1) override;

        void StartSpinAttack() override;

        void StopSpinAttack() override;

        //virtual void UnkVfn246() override;

        //virtual void UnkVfn249() override;

        bool ShouldDropDeathLoot() override;

        //virtual void UnkVfn261() override;

        /// <summary>
        /// <para>*265*/ virtual void readAdditionalSaveData(class CompoundTag const&amp;, class DataLoadHelper&amp;);</para>
        /// <para>*266*/ virtual void addAdditionalSaveData(class CompoundTag&amp;);</para>
        /// </summary>
        //virtual void UnkVfn269() override;

        void OnSizeUpdated() override;

        //virtual void UnkVfn278() override;

        void SpawnAnim() override;

        virtual void SetSpeed(float _0);

        void Travel(float _0, float _1, float _2) override;

        void AiStep() override;

        virtual int GetItemUseDuration();

        virtual float GetItemUseStartupProgress();

        virtual float GetItemUseIntervalProgress();

        //virtual void UnkVfn307() override;

        bool IsAlliedTo(Mob^ _0) override;

        //virtual void UnkVfn311() override;

        void DropEquipmentOnDeath() override;

        void ClearVanishEnchantedItemsOnDeath() override;

        void SendInventory(bool _0) override;

        void OnBorn(Actor^ _0, Actor^ _1) override;

        float GetWalkTargetValue(MC::BlockPos _0) override;

        bool CanExistWhenDisallowMob() override;

        //virtual void UnkVfn345() override;

        void JumpFromGround() override;

        void UpdateAi() override;

        void ServerAiMobStep() override;

        void UpdateGliding() override;

        //virtual void UnkVfn359() override;

        virtual void DestroyRegion();

        virtual void SuspendRegion();

        virtual void ResendAllChunks();

        virtual void FireWillChangeDimension();

        virtual void FireDimensionChanged();

        virtual void TickWorld(Tick^ _0);

        //virtual void UnkVfn369();

        virtual void MoveView();

        virtual void CheckMovementStats(Vec3 _0);

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

        virtual void OpenTrading(ActorUniqueID _0, bool _1);

        virtual bool CanOpenContainerScreen();

        //virtual void UnkVfn388();

        //virtual void UnkVfn389();

        virtual void OpenInventory();

        //virtual void UnkVfn391();

        //virtual void UnkVfn392();

        virtual void DisplayWhisperMessage(String^ _0, String^ _1, String^ _2, String^ _3);

        virtual void StopSleepInBed(bool _0, bool _1);

        virtual bool CanStartSleepInBed();

        //virtual void UnkVfn401();

        //virtual void UnkVfn402();

        //virtual void UnkVfn406();

        virtual void RegisterTrackedBoss(ActorUniqueID _0);

        virtual void UnRegisterTrackedBoss(ActorUniqueID _0);

        virtual void InitHUDContainerManager();

        virtual void Crit(Actor^ _0);

        //virtual void UnkVfn413();

        virtual void AddExperience(int _0);

        virtual void AddLevels(int _0);

        virtual void DeleteContainerManager();

        virtual void SetFieldOfViewModifier(float _0);

        virtual bool IsActorRelevant(Actor^ _0);

        virtual void OnSuspension();

        virtual void OnLinkedSlotsChanged();

        virtual int GetItemCooldownLeft(unsigned long long _0);

        //virtual void UnkVfn441();

        virtual void OnMovePlayerPacketNormal(Vec3 _0, Vec2 _1, float _2);

        void ApplyExhaustion(Vec3 _0);

        bool CanBeSeenOnMap();

        bool CanUseOperatorBlocks();

        void CauseFoodExhaustion(float _0);

        void ClearRespawnPosition();

        void Eat(int _0, float _1);

        Vec3 GetCapePos(float _0);

        void GetNewEnchantmentSeed();

        bool HasOpenContainerOfContainerType(ContainerType _0);

        bool Interact(Actor^ _0, Vec3 _1);

        bool IsHiddenFrom(Mob^ _0);

        void RecheckSpawnPosition();

        void ReleaseUsingItem();

        void ResetPlayerLevel();

        void ResetToDefaultGameMode();

        void SetAllPlayersSleeping();

        void SetBedRespawnPosition(MC::BlockPos _0);

        void SetBlockRespawnUntilClientMessage(bool _0);

        void SetChunkRadius(unsigned int _0);

        void SetHasSeenCredits(bool _0);

        void SetRespawnPositionCandidate();

        void SetRespawnReady(Vec3 _0);

        bool ShouldShowCredits();

        void SpawnExperienceOrb(Vec3 _0, int _1);

        void StartGliding();

        void StopGliding();

        void StopUsingItem();

        bool Take(Actor^ _0, int _1, int _2);

        void UpdateInventoryTransactions();

        void UpdateSkin(SerializedSkin^ skin, int skinId);

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
