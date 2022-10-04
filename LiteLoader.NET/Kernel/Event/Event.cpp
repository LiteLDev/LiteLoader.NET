#include <LiteLoader.NET/Header/Event/Event.hpp>

extern void InitPlayerEvents();
extern void InitBlockEvents();
extern void InitEntityEvents();
extern void InitOtherEvents();

void InitEvents()
{
	InitPlayerEvents();
	InitBlockEvents();
	InitEntityEvents();
	InitOtherEvents();
}
