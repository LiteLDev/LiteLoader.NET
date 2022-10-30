#pragma once
#include <mc/Level.hpp>
#include "Types.hpp"

namespace MC
{
ref class MapItemSavedData;
ref class BlockPalette;
ref class ActorDamageSource;
ref class Packet;
ref class ItemStack;
value class Vec3;
ref class Block;
ref class BlockSource;
ref class BlockInstance;
ref class BlockActor;
ref class CompoundTag;
ref class Container;
ref class Dimension;
ref class Player;
ref class Actor;
} // namespace MC

namespace MC
{
public
ref class Level : ClassTemplate<Level, ::Level>
{
public:
    __ctor(Level, ::Level);

public:
    delegate bool Callback(Player ^);

private:
    // inline static void forEachPlayer(Callback^ callback);
    delegate bool NativeCallback(::Player&);
    typedef bool (*pNativeCallback)(::Player&);
    static Callback ^ _callback = nullptr;
    inline static bool NATIVECALLBACK CallbackFn(::Player& p);
    static List<GCHandle> ^ gchList = nullptr;

public:
    inline /*static*/ void ForEachPlayer(Callback ^ callback);
    inline static List<Player ^> ^ GetAllPlayers();
    /// name or xuid
    inline /*static*/ Player ^ GetPlayer(String ^ info);
    /// UniqueID
    inline /*static*/ Player ^ GetPlayer(ActorUniqueID ^ id);
    inline static Actor ^ GetEntity(ActorUniqueID ^ id);
    inline Actor^ GetRuntimeEntity(ActorRuntimeID^ id, bool _);
    inline Player^ GetRuntimePlayer(ActorRuntimeID^ id);
    inline static List<Actor ^> ^ GetAllEntities(int dimId);
    inline static List<Actor ^> ^ GetAllEntities();
    inline static Actor ^ SpawnMob(Vec3 pos, int dimId, String ^ typeName);
    inline static Actor ^ SpawnItem(Vec3 pos, int dimId, ItemStack ^ item);
    inline static bool CreateExplosion(Vec3 pos, int dimId, Actor ^ source, float radius, bool createFire, bool canBreak, float maxResistance);
    inline static bool CreateExplosion(Vec3 pos, int dimId, Actor ^ source, float radius, bool createFire, bool canBreak);
    inline /*static*/ MapItemSavedData ^ GetMapSavedData(ActorUniqueID ^ a0);
    inline static Actor^ CloneMob(Vec3 pos, int dimid, Actor^ ac);

    // Block
    inline static Block ^ GetBlock(BlockPos pos, int dimId);
    inline static Block ^ GetBlock(BlockPos pos, BlockSource ^ blockSource);
    inline static Block ^ GetBlockEx(BlockPos pos, int dimId);
    inline static BlockInstance ^ GetBlockInstance(BlockPos pos, int dimId);
    inline static BlockInstance ^ GetBlockInstance(BlockPos pos, BlockSource ^ blockSource);
    inline static BlockActor ^ GetBlockEntity(BlockPos pos, int dimId);
    inline static BlockActor ^ GetBlockEntity(BlockPos pos, BlockSource ^ blockSource);
    inline static bool SetBlock(BlockPos pos, int dim, Block ^ block);
    inline static bool SetBlock(BlockPos pos, int dim, String ^ name, unsigned short tileData);
    inline static bool SetBlock(BlockPos pos, int dim, CompoundTag ^ nbt);
    inline static bool BreakBlockNaturally(BlockSource ^ bs, BlockPos pos);
    inline static bool BreakBlockNaturally(BlockSource ^ bs, BlockPos pos, ItemStack ^ tool);
    inline /*static*/ bool DestroyBlock(BlockSource ^ bs, BlockPos pos, bool a2);
    inline /*static*/ void SpawnParticleEffect(String ^ type, Vec3 pos, Dimension ^ a2);
    //inline static void SpawnParticleEffect(String ^ type, Actor ^ a1, Vec3 a2);
    inline static bool HasContainer(Vec3 pos, int dim);
    inline static Container ^ GetContainer(Vec3 pos, int dim);

    // Item
    inline static ItemStack ^ GetItemStackFromId(short itemId, int aux);
    inline static ItemStack ^ GetItemStackFromId(short a2);

    // Helper
    inline static BlockSource ^ GetBlockSource(int dimid);
    inline static BlockSource ^ GetBlockSource(Actor ^ actor);
    inline /*static*/ BlockPalette ^ GetBlockPalette();
    inline /*static*/ Dimension ^ GetDimension(AutomaticID<Dimension ^, int> ^ a0);
    inline static Actor ^ GetDamageSourceEntity(ActorDamageSource ^ ads);
    inline static void BroadcastText(String ^ text, TextType type);
    inline static void BroadcastTitle(String ^ text, TitleType Type, int FadeInDuration, int RemainDuration, int FadeOutDuration);
    inline static void SendPacketForAllPlayers(Packet ^ pkt);


    ref class ServerCommandOrigin : ClassTemplate<ServerCommandOrigin, ::Level::ServerCommandOrigin>
    {
    public:
        property IntPtr MyVTBL
        {
            IntPtr get()
            {
                return IntPtr(NativePtr->myVTBL);
            };
            void set(IntPtr value)
            {
                NULL_ARG_CHECK(value);
                NativePtr->myVTBL = (void*)value;
            };
        };
        property array<IntPtr> ^ UUID {
            array<IntPtr> ^ get() {
                auto ret = gcnew array<IntPtr>(2);
                ret[0] = IntPtr(NativePtr->UUID[0]);
                ret[1] = IntPtr(NativePtr->UUID[1]);
                return ret;
            };
            void set(array<IntPtr> ^ value)
            {
                NULL_ARG_CHECK(value);
                if (value->Length != 2)
                    throw gcnew System::Exception;
                NativePtr->UUID[0] = (void*)value[0];
                NativePtr->UUID[1] = (void*)value[1];
            }
        };
        property IntPtr ServerLevel
        {
            IntPtr get()
            {
                return IntPtr(NativePtr->lvl);
            };
            void set(IntPtr value)
            {
                NativePtr->lvl = (::ServerLevel*)(void*)value;
            };
        };
        property String ^ Name {
            String ^ get() {
                return marshalString(NativePtr->Name);
            };
            void set(String ^ value)
            {
                NativePtr->Name = marshalString(value);
            };
        };
        property unsigned char Perm
        {
            unsigned char get()
            {
                return NativePtr->Perm;
            }
            void set(unsigned char value)
            {
                NativePtr->Perm = value;
            }
        }
        //property array<IntPtr> ^ Fake_vtbl {
        //    array<IntPtr> ^ get() {
        //        auto ret = gcnew array<IntPtr>(26);
        //        for (int i = 0; i < 26; i++)
        //        {
        //            ret[i] = IntPtr(NativePtr->fake_vtbl[i]);
        //        }
        //        return ret;
        //    };
        //    void set(array<IntPtr> ^ value)
        //    {
        //        NULL_ARG_CHEEK(value);
        //        if (value->Length != 26)
        //            throw gcnew System::Exception;
        //        for (int i = 0; i < 26; i++)
        //        {
        //            NativePtr->fake_vtbl[i] = (void*)value[i];
        //        }
        //    }
        //};
        //ServerCommandOrigin()
        //{
        //    NativePtr = new ::Level::ServerCommandOrigin;
        //    OwnsNativeInstance = true;
        //}
    };


    // For compatibility
    inline static bool RuncmdAs(Player ^ pl, String ^ cmd);
    inline static Pair<bool, String ^> RuncmdEx(String ^ cmd);
    inline static bool Runcmd(String ^ cmd);


#ifdef MANUAL_MAINTENANCE

    property double TickDeltaTime
    {
        double get();
    }

    property bool Use3DBiomeMaps
    {
        bool get();
    }

    static unsigned int CreateRandomSeed();

    //static property float AVERAGE_GAME_TICKS_PER_RANDOM_TICK_PER_BLOCK
    //{
    //    float get();
    //}

    //static property float AVERAGE_RANDOM_TICKS_PER_BLOCK_PER_GAME_DAY
    //{
    //    float get();
    //}

    //static property float AVERAGE_RANDOM_TICKS_PER_BLOCK_PER_MINUTE
    //{
    //    float get();
    //}

    //static property float RANDOM_TICKS_PER_TICK_PER_SUBCHUNK
    //{
    //    float get();
    //}

#endif // MANUAL_MAINTENANCE


#ifdef INCLUDE_MCAPI
    // property MC::PlayerCapabilities::ISharedController ^ Capabilities {
    //     MC::PlayerCapabilities::ISharedController ^ get();
    // }
#endif // INCLUDE_MCAPI
};
} // namespace MC