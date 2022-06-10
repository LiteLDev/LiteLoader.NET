#pragma once
#include <MC/BlockInstance.hpp>
#include "Types.hpp"
#include "Block.hpp"
#include "BlockActor.hpp"
#include "Container.hpp"

namespace MC
{
	ref class BlockSource;
	ref class BlockPos;
	value class Vec3;
	ref class ItemStack;
	ref class Container;
	ref class BlockActor;
	ref class Block;
}

namespace MC
{
	public
	ref class BlockInstance : ClassTemplate<BlockInstance, ::BlockInstance>
	{
	public:
		__ctor_all(BlockInstance, ::BlockInstance);

		inline static BlockInstance^ CreateBlockinstance(Block^ block, BlockPos^ pos, int dimId);


		/// <summary>
		/// Create a instance of the MC.BlockInstance class from block, position, and dimension id.
		/// </summary>
		/// <param name="block">£­Block</param>
		/// <param name="pos">£­Position</param>
		/// <param name="dimid">
		/// £­Dimension id
		/// <para>¡¡</para>
		/// <para>dimid:</para>
		/// <para>¡¡¡¡0 : OverWorld</para>
		/// <para>¡¡¡¡1 : The Nether</para>
		/// <para>¡¡¡¡2 : The End</para>
		/// </param>
		/// <returns>A instance of the MC.BlockInstance</returns>
		static BlockInstance^ Create(MC::Block^ block, MC::BlockPos^ pos, int dimid);


		/// <summary>
		/// Create a instance of the MC.BlockInstance class from block and block position with default dimension id.
		/// </summary>
		/// <param name="block">£­Block</param>
		/// <param name="pos">£­Block Position</param>
		/// <returns>A instance of the MC.BlockInstance</returns>
		static BlockInstance^ Create(MC::Block^ block, MC::BlockPos^ pos);


		/// <summary>
		/// Create a instance of the MC.BlockInstance class that is empty
		/// </summary>
		/// <returns>A instance of the MC.BlockInstance</returns>
		static BlockInstance^ Create();


		/// <summary>
		/// Break this block naturally.
		/// </summary>
		inline bool BreakNaturally(bool isCreativeMode);


		/// <summary>
		/// Break this block naturally.
		/// </summary>
		inline bool BreakNaturally();


		/// <summary>
		/// Break this block naturally with tool.
		/// </summary>
		/// <param name="tool">£­The item of tool</param>
		inline bool BreakNaturally(ItemStack^ tool, bool isCreativeMode);


		/// <summary>
		/// Break this block naturally with tool.
		/// </summary>
		/// <param name="tool">£­The item of tool</param>
		inline bool BreakNaturally(ItemStack^ tool);


		/// <summary>
		/// Get the block in the current MC.BlockInstance object.
		/// </summary>
		property Block^ Block { MC::Block^ get(); };


		/// <summary>
		/// Get the position in the current MC.BlockInstance object.
		/// </summary>
		property BlockPos^ Position { BlockPos^ get(); };


		/// <summary>
		/// Get the block source in the current MC.BlockInstance object.
		/// </summary>
		property BlockSource^ BlockSource { MC::BlockSource^ get(); };


		/// <summary>
		/// Get the block entity owned by the current MC.BlockInstance object.
		/// </summary>
		property BlockActor^ BlockEntity { BlockActor^ get(); };


		/// <summary>
		/// Get the container owned by the current MC.BlockInstance object.
		/// </summary>
		property Container^ Container { MC::Container^ get(); };


		/// <summary>
		/// Get the drop item in the current MC.BlockInstance object.
		/// </summary>
		property ItemStack^ BlockDrops { ItemStack^ get(); };


		/// <summary>
		/// Get the dimension id in the current MC.BlockInstance object.
		/// </summary>
		property int DimensionId
		{
			int get();
		}


		/// <summary>
		///	Determine if this block instance has a block entity.
		/// </summary>
		property bool HasBlockEntity
		{
			bool get();
		}


		/// <summary>
		/// Determine if this block instance is null.
		/// </summary>
		property bool IsNull
		{
			bool get();
		}


		/// <summary>
		/// Determine if this block instance has a container.
		/// </summary>
		property bool HasContainer
		{
			bool get();
		}


		/// <summary>
		/// Get the block id in the current MC.BlockInstance object.
		/// </summary>
		property short BlockId
		{
			short get();
		}

		static bool operator==(BlockInstance^ a, BlockInstance^ b);

	};
} // namespace MC