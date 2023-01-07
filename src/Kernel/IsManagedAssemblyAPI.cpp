#pragma once
#include <src/Header/IsManagedAssemblyAPI.hpp>

#pragma managed
_declspec(noinline) bool __isManagedAssembly(const char* _path)
{
    using namespace System;
    using namespace System::IO;
    using namespace System::Reflection::PortableExecutable;
    try
    {
        String^ path = gcnew String(_path);
        FileStream fs(path, FileMode::Open, FileAccess::Read, FileShare::ReadWrite);
        PEReader peReader(% fs);

        if (!peReader.HasMetadata)
        {
            return false;
        }

        auto metadata = peReader.GetMetadata();

        if (metadata.Pointer == nullptr)
            return false;

        return true;
    }
    catch (...)
    {
        return false;
    }

}

#pragma unmanaged
bool isManagedAssembly(const char* path)
{
    return __isManagedAssembly(path);
}