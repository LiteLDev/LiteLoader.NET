#include "../../Header/MC/Level.hpp"

#include "../../Header/MC/Player.hpp"
#include "../../Header/MC/Vec3.hpp"
#include "../../Header/MC/ItemStack.hpp"
#include "../../Header/MC/MapItemSavedData.hpp"
#include "../../Header/MC/Block.hpp"
#include "../../Header/MC/BlockPos.hpp"
#include "../../Header/MC/BlockSource.hpp"
#include "../../Header/MC/BlockInstance.hpp"
#include "../../Header/MC/BlockActor.hpp"
#include "../../Header/MC/Dimension.hpp"
#include "../../Header/MC/Container.hpp"
#include "../../Header/MC/BlockPalette.hpp"
#include "../../Header/MC/ActorDamageSource.hpp"
#include "../../Header/MC/Packet.hpp"

namespace MC
{
inline bool NATIVECALLBACK Level::CallbackFn(::Player& p)
{
    return _callback(gcnew Player(&p));
}
inline void Level::ForEachPlayer(Callback ^ callback)
{
    if (callback == nullptr)
        throw gcnew System::ArgumentNullException;
    if (gchList == nullptr)
        gchList = gcnew List<GCHandle>;

    _callback = callback;

    auto deFn = gcnew NativeCallback(&Level::CallbackFn);

    gchList->Add(GCHandle::Alloc(deFn));

    auto pFn = static_cast<pNativeCallback>(
        Marshal::GetFunctionPointerForDelegate(_callback).ToPointer());

    NativePtr->forEachPlayer(pFn);
}
inline List<Player ^> ^ Level::GetAllPlayers()
{
    auto& stdvector = ::Level::getAllPlayers();
    auto ret = gcnew List<Player ^>(int(stdvector.size()));
    for each (auto var in stdvector)
        ret->Add(gcnew Player(var));
    return ret;
}
inline Player ^ Level::GetPlayer(String^ info)
{
    return gcnew Player(NativePtr->getPlayer(marshalString(info)));
}
inline Player ^ Level::GetPlayer(ActorUniqueID ^ id)
{
    const auto player = NativePtr->getPlayer(*id);
    return player != nullptr ? gcnew Player(player) : nullptr;
}
inline Actor ^ Level::GetEntity(ActorUniqueID ^ id)
{
    const auto entity = ::Level::getEntity(*id);
    return entity != nullptr ? gcnew Actor(entity) : nullptr;
}
inline Actor^ Level::GetRuntimeEntity(ActorRuntimeID^ id, bool _)
{
    const auto entity = NativePtr->getRuntimeEntity(*id, _);
    return entity != nullptr ? gcnew Actor(entity) : nullptr;
}
inline Player^ Level::GetRuntimePlayer(ActorRuntimeID^ id)
{
    const auto player = NativePtr->getRuntimePlayer(*id);
    return player != nullptr ? gcnew Player(player) : nullptr;
}
inline List<Actor ^> ^ Level::GetAllEntities(int dimId)
{
    auto& stdvector = ::Level::getAllEntities(dimId);
    auto ret = gcnew List<Actor ^>(int(stdvector.size()));
    for each (auto& var in stdvector)
        ret->Add(gcnew Actor(var));
    return ret;
}
inline List<Actor ^> ^ Level::GetAllEntities()
{
    auto& stdvector = ::Level::getAllEntities();
    auto ret = gcnew List<Actor ^>(int(stdvector.size()));
    for each (auto& var in stdvector)
        ret->Add(gcnew Actor(var));
    return ret;
}
inline Actor ^ Level::SpawnMob(Vec3 pos, int dimId, String^ typeName)
{
    return gcnew Actor(::Level::spawnMob(
        pos, dimId, marshalString(typeName)));
}
inline Actor ^ Level::SpawnItem(Vec3 pos, int dimId, ItemStack ^ item)
{
    return gcnew Actor(::Level::spawnItem(
        pos, dimId, item->NativePtr));
}
inline bool Level::CreateExplosion(Vec3 pos, int dimId, Actor ^ source, float radius, bool createFire, bool canBreak, float maxResistance)
{
    return ::Level::createExplosion(::Vec3(pos), dimId, source, radius, createFire, canBreak, maxResistance);
}
inline bool Level::CreateExplosion(Vec3 pos, int dimId, Actor ^ source, float radius, bool createFire, bool canBreak)
{
    return ::Level::createExplosion(::Vec3(pos), dimId, source, radius, createFire, canBreak);
}
inline MapItemSavedData ^ Level::GetMapSavedData(ActorUniqueID ^ id)
{
    const auto data = NativePtr->getMapSavedData(*id);
    return data != nullptr ? gcnew MapItemSavedData(data) : nullptr;
}
inline Actor^ Level::CloneMob(Vec3 pos, int dimid, Actor^ ac)
{
    return gcnew Actor(::Level::cloneMob(pos, dimid, ac->NativePtr));
}
inline Block ^ Level::GetBlock(BlockPos pos, int dimId)
{
    return gcnew Block(::Level::getBlock(pos, dimId));
}
inline Block ^ Level::GetBlock(BlockPos pos, BlockSource ^ blockSource)
{
    return gcnew Block(::Level::getBlock(pos, blockSource));
}
inline Block ^ Level::GetBlockEx(BlockPos pos, int dimId)
{
    return gcnew Block(::Level::getBlockEx(pos, dimId));
}
inline BlockInstance ^ Level::GetBlockInstance(BlockPos pos, int dimId)
{
    return gcnew BlockInstance(::Level::getBlockInstance(pos, dimId));
}
inline BlockInstance ^ Level::GetBlockInstance(BlockPos pos, BlockSource ^ blockSource)
{
    return gcnew BlockInstance(::Level::getBlockInstance(pos, blockSource));
}
inline BlockActor ^ Level::GetBlockEntity(BlockPos pos, int dimId)
{
    return gcnew BlockActor(::Level::getBlockEntity(pos, dimId));
}
inline BlockActor ^ Level::GetBlockEntity(BlockPos pos, BlockSource ^ blockSource)
{
    return gcnew BlockActor(::Level::getBlockEntity(pos, blockSource));
}
inline bool Level::SetBlock(BlockPos pos, int dim, Block ^ block)
{
    return ::Level::setBlock(pos, dim, block);
}
inline bool Level::SetBlock(BlockPos pos, int dim, String^ name, unsigned short tileData)
{
    return ::Level::setBlock(pos, dim, marshalString(name), tileData);
}
inline bool Level::SetBlock(BlockPos pos, int dim, CompoundTag ^ nbt)
{
    return ::Level::setBlock((::BlockPos&)pos, dim, nbt->NativePtr);
}
inline bool Level::BreakBlockNaturally(BlockSource ^ bs, BlockPos pos)
{
    return ::Level::breakBlockNaturally(bs, pos);
}
inline bool Level::BreakBlockNaturally(BlockSource ^ bs, BlockPos pos, ItemStack ^ tool)
{
    return ::Level::breakBlockNaturally(bs->NativePtr, pos, tool->NativePtr);
}
inline bool Level::DestroyBlock(BlockSource ^ bs, BlockPos pos, bool a2)
{
    return NativePtr->destroyBlock(bs, pos, a2);
}
inline void Level::SpawnParticleEffect(String^ type, Vec3 pos, Dimension ^ a2)
{
    NativePtr->spawnParticleEffect(marshalString(type), pos, a2->NativePtr);
}
//inline void Level::SpawnParticleEffect(String^ type, Actor ^ a1, Vec3 a2)
//{
//    ::Level::spawnParticleEffect(marshalString(type), *a1->NativePtr, a2);
//}
inline bool Level::HasContainer(Vec3 pos, int dim)
{
    return ::Level::hasContainer((::Vec3&)pos, dim);
}
inline Container ^ Level::GetContainer(Vec3 pos, int dim)
{
    return gcnew Container(::Level::getContainer((::Vec3&)pos, dim));
}
inline ItemStack ^ Level::GetItemStackFromId(short itemId, int aux)
{
    return gcnew ItemStack(::Level::getItemStackFromId(itemId, aux));
}
inline ItemStack ^ Level::GetItemStackFromId(short itemId)
{
    return gcnew ItemStack(::Level::getItemStackFromId(itemId));
}
inline BlockSource ^ Level::GetBlockSource(int dimid)
{
    return gcnew BlockSource(::Level::getBlockSource(dimid));
}
inline BlockSource ^ Level::GetBlockSource(Actor ^ actor)
{
    return gcnew BlockSource(::Level::getBlockSource(actor));
}
inline BlockPalette ^ Level::GetBlockPalette()
{
    return gcnew BlockPalette(&NativePtr->getBlockPalette());
}
inline Dimension ^ Level::GetDimension(AutomaticID<Dimension ^, int> ^ a0)
{
    return gcnew Dimension(NativePtr->getDimension((int)a0));
}
inline Actor ^ Level::GetDamageSourceEntity(ActorDamageSource ^ ads)
{
    return gcnew Actor(::Level::getDamageSourceEntity(ads));
}
inline void Level::BroadcastText(String^ text, TextType type)
{
    ::Level::broadcastText(marshalString(text), ::TextType(type));
}
inline void Level::BroadcastTitle(String^ text, TitleType Type, int FadeInDuration, int RemainDuration, int FadeOutDuration)
{
    ::Level::broadcastTitle(marshalString(text), ::TitleType(Type), FadeInDuration, RemainDuration, FadeOutDuration);
}
inline void Level::SendPacketForAllPlayers(Packet ^ pkt)
{
    ::Level::sendPacketForAllPlayers(pkt);
}
inline bool Level::RuncmdAs(Player ^ pl, String^ cmd)
{
    return ::Level::runcmdAs(pl->NativePtr, marshalString(cmd));
}
inline Pair<bool, String^> Level::RuncmdEx(String^ cmd)
{
    auto& kvpair = ::Level::runcmdEx(marshalString(cmd));
    return Pair<bool, String^>(kvpair.first, marshalString(kvpair.second));
}
inline bool Level::Runcmd(String^ cmd)
{
    return ::Level::runcmd(marshalString(cmd));
}
} // namespace MC


#ifdef MANUAL_MAINTENANCE

unsigned int MC::Level::CreateRandomSeed()
{
    return ::Level::createRandomSeed();
}

double MC::Level::TickDeltaTime::get()
{
    return NativePtr->getTickDeltaTime();
}

bool MC::Level::Use3DBiomeMaps::get()
{
    return NativePtr->use3DBiomeMaps();
}

//float MC::Level::AVERAGE_GAME_TICKS_PER_RANDOM_TICK_PER_BLOCK::get()
//{
//    return ::Level::AVERAGE_GAME_TICKS_PER_RANDOM_TICK_PER_BLOCK;
//}
//
//float MC::Level::AVERAGE_RANDOM_TICKS_PER_BLOCK_PER_GAME_DAY::get()
//{
//    return ::Level::AVERAGE_RANDOM_TICKS_PER_BLOCK_PER_GAME_DAY;
//}
//
//float MC::Level::AVERAGE_RANDOM_TICKS_PER_BLOCK_PER_MINUTE::get()
//{
//    return ::Level::AVERAGE_RANDOM_TICKS_PER_BLOCK_PER_MINUTE;
//}
//
//float MC::Level::RANDOM_TICKS_PER_TICK_PER_SUBCHUNK::get()
//{
//    return ::Level::RANDOM_TICKS_PER_TICK_PER_SUBCHUNK;
//}

#endif // MANUAL_MAINTENANCE




#ifdef INCLUDE_MCAPI
// MC::PlayerCapabilities::ISharedController ^ MC::Level::Capabilities::get()
//{
//     auto& __ret = ((class ::Level*)NativePtr)->getCapabilities();
//     return (MC::PlayerCapabilities::ISharedController ^)((&__ret == nullptr) ? nullptr : gcnew ::MC::PlayerCapabilities::ISharedController((struct ::PlayerCapabilities::ISharedController*)&__ret));
// }
#endif // INCLUDE_MCAPI
