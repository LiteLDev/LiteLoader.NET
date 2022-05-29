#pragma once
#include <MC/CommandSelectorBase.hpp>
#include "../MC/Types.hpp"

namespace MC
{
	ref class Actor;
	ref class ActorDefinitionIdentifier;
	ref class BlockPos;
	ref class CommandIntegerRange;
	ref class CommandPosition;
	ref class CommandSelectorBase;
	ref class Player;
}

namespace MC
{
	public ref class CommandSelectorBase :
		ClassTemplate<CommandSelectorBase, ::CommandSelectorBase>
	{
	public:

		property ::System::String^ Name
		{
			::System::String^ get();
		}

		property bool HasName
		{
			bool get();
		}

		property bool IsExplicitIdSelector
		{
			bool get();
		}

		void SetBox(MC::BlockPos^ _0);

		void SetExcludeAgents(bool _0);

		void SetExplicitIdSelector(::System::String^ _0);

		void SetIncludeDeadPlayers(bool _0);

		void SetPosition(MC::CommandPosition^ _0);

		void SetRadiusMax(float _0);

		void SetRadiusMin(float _0);

		void SetResultCount(unsigned long long _0, bool _1);

		void SetVersion(int _0);

	protected:

		bool __ownsNativeInstance;
	};
}