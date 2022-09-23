#include <LiteLoader.NET/Header/Command/CommandOrigin.hpp>

#include <LiteLoader.NET/Header/MC/ServerPlayer.hpp>
#include <LiteLoader.NET/Header/MC/Level.hpp>
#include <LiteLoader.NET/Header/MC/BlockPos.hpp>
#include <LiteLoader.NET/Header/MC/Vec3.hpp>
#include <LiteLoader.NET/Header/MC/Vec2.hpp>
#include <LiteLoader.NET/Header/MC/Dimension.hpp>
#include <LiteLoader.NET/Header/MC/NetworkIdentifier.hpp>
#include <LiteLoader.NET/Header/Command/CommandOriginIdentity.hpp>
#include <LiteLoader.NET/Header/Command/CommandOriginData.hpp>
#include <LiteLoader.NET/Header/Command/CommandPositionFloat.hpp>
#include <LiteLoader.NET/Header/MC/CompoundTag.hpp>
#include <LiteLoader.NET/Header/Command/CommandArea.hpp>
#include <LiteLoader.NET/Header/Command/Command.hpp>

enum class AbilitiesIndex;
enum class CommandOriginType : char;

namespace MC
{
    inline ServerPlayer^ CommandOrigin::Player::get()
    {
        return gcnew ServerPlayer(NativePtr->getPlayer());
    }

    String^ CommandOrigin::RequestId::get()
    {
        return marshalString(NativePtr->getRequestId());
    }

    String^ CommandOrigin::Name::get()
    {
        return marshalString(NativePtr->getName());
    }

    BlockPos CommandOrigin::BlockPosition::get()
    {
        return BlockPos(NativePtr->getBlockPosition());
    }

    Vec3 CommandOrigin::WorldPosition::get()
    {
        return NativePtr->getWorldPosition();
    }

    Vec2 CommandOrigin::Rotation::get()
    {
        return NativePtr->getRotation().value_or(::Vec2::ZERO);
    }

    Level^ CommandOrigin::Level::get()
    {
        return gcnew MC::Level(NativePtr->getLevel());
    }

    Dimension^ CommandOrigin::Dimension::get()
    {
        return gcnew MC::Dimension(NativePtr->getDimension());
    }

    Actor^ CommandOrigin::Entity::get()
    {
        return gcnew Actor(NativePtr->getEntity());
    }

    CommandPermissionLevel CommandOrigin::PermissionsLevel::get()
    {
         return static_cast<CommandPermissionLevel>(NativePtr->getPermissionsLevel());
    }

    CommandOrigin^ CommandOrigin::Clone()
    {
        return gcnew CommandOrigin(NativePtr->clone().release(), true);
    }

    BlockPos CommandOrigin::CursorHitBlockPos::get()
    {
        return NativePtr->getCursorHitBlockPos().value_or(::BlockPos::ZERO);
    }

    Vec3 CommandOrigin::CursorHitPos::get()
    {
        return NativePtr->getCursorHitPos().value_or(::Vec3::ZERO);
    }

    bool CommandOrigin::HasChatPerms::get()
    {
        return NativePtr->hasChatPerms();
    }

    bool CommandOrigin::HasTellPerms::get()
    {
        return NativePtr->hasTellPerms();
    }

    bool CommandOrigin::CanUseAbility(int _EnumAbilitiesIndex)
    {
        return NativePtr->canUseAbility(static_cast<AbilitiesIndex>(_EnumAbilitiesIndex));
    }

    bool CommandOrigin::IsWorldBuilder::get()
    {
        return NativePtr->isWorldBuilder();
    }

    bool CommandOrigin::CanUseCommandsWithoutCheatsEnabled::get()
    {
        return NativePtr->canUseCommandsWithoutCheatsEnabled();
    }

    bool CommandOrigin::IsSelectorExpansionAllowed::get()
    {
        return NativePtr->isSelectorExpansionAllowed();
    }

    NetworkIdentifier^ CommandOrigin::SourceId::get()
    {
        return gcnew NetworkIdentifier(const_cast<::NetworkIdentifier*>(&NativePtr->getSourceId()));
    }

    unsigned char CommandOrigin::SourceSubId::get()
    {
        return NativePtr->getSourceSubId();
    }

    CommandOrigin^ CommandOrigin::OutputReceiver::get()
    {
        return gcnew CommandOrigin(&const_cast<::CommandOrigin&>(NativePtr->getOutputReceiver()));
    }

    CommandOriginIdentity^ CommandOrigin::Identity::get()
    {
        return gcnew CommandOriginIdentity(&NativePtr->getIdentity());
    }

    CommandOriginType CommandOrigin::OriginType::get()
    {
        return static_cast<CommandOriginType>(NativePtr->getOriginType());
    }

    CommandOriginData^ CommandOrigin::ToCommandOriginData()
    {
        return gcnew CommandOriginData(NativePtr->toCommandOriginData());
    }

    Mce::UUID CommandOrigin::UUID::get()
    {
        return const_cast<mce::UUID&>(NativePtr->getUUID());
    }

    void CommandOrigin::UpdateValues()
    {
        NativePtr->updateValues();
    }

    Vec3 CommandOrigin::GetExecutePosition(int a0, CommandPositionFloat^ a1)
    {
        return static_cast<::Vec3>(NativePtr->getExecutePosition(a0, *(a1->NativePtr)));
    }

    CompoundTag^ CommandOrigin::Serialize()
    {
        return gcnew CompoundTag(&NativePtr->serialize());
    }

    bool CommandOrigin::IsValid::get()
    {
        return NativePtr->isValid();
    }

    void CommandOrigin::UUID::set(Mce::UUID value)
    {
        NativePtr->_setUUID(value);
    }

    CommandArea^ CommandOrigin::GetAreaAt(BlockPos bp0, BlockPos bp1, int a0, bool a1)
    {
        return gcnew CommandArea(NativePtr->getAreaAt(bp0, bp1, a0, a1).release(), true);
    }

    CommandArea^ CommandOrigin::GetAreaAt(BlockPos bp0, int a0)
    {
        return gcnew CommandArea(NativePtr->getAreaAt(bp0, a0).release(), true);
    }

    CommandArea^ CommandOrigin::GetAreaAtWithBuffer(BlockPos bp0, BlockPos bp1, int a0, bool a1)
    {
        return gcnew CommandArea(NativePtr->getAreaAtWithBuffer(bp0, bp1, a0, a1).release(), true);
    }

    CommandArea^ CommandOrigin::GetAreaAtWithBuffer(BlockPos bp0, int a0)
    {
        return gcnew CommandArea(NativePtr->getAreaAtWithBuffer(bp0, a0).release(), true);
    }
} // namespace MC
