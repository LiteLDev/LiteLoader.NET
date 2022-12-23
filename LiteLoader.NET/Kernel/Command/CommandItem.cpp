#include <LiteLoader.NET/Header/Command/CommandItem.hpp>
#include <LiteLoader.NET/Header/Command/CommandOutput.hpp>
#include <LiteLoader.NET/Header/MC/ItemInstance.hpp>

namespace MC {
    inline CommandItem::CommandItem(unsigned __int64 uint64)
        :ClassTemplate(new ::CommandItem(uint64), true)
    {
    }
    inline CommandItem::CommandItem(int a1, short a2, bool a3)
        : ClassTemplate(new ::CommandItem(a1, a2, a3), true)
    {
    }
    inline CommandItem::CommandItem()
        : ClassTemplate(new ::CommandItem(), true)
    {
    }
    inline ItemInstance^ CommandItem::CreateInstance(int a1, int a2, MC::CommandOutput^ output, bool a4) {
        return gcnew ItemInstance(NativePtr->createInstance(a1, a2, output->NativePtr, a4).value_or(::ItemInstance::EMPTY_ITEM));
    }

    inline int CommandItem::Id::get() {
        return NativePtr->getId();
    }

    inline CommandItem::operator bool(CommandItem^ obj) {
        return obj->NativePtr->operator bool();
    }

    inline CommandItem::operator unsigned __int64(CommandItem^ obj) {
        return obj->NativePtr->operator unsigned __int64();
    }
}