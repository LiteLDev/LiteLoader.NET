
inline uintptr_t FindSignature(uintptr_t rangeStart, uintptr_t rangeEnd, const char* szSignature)
{
    const char* pattern = szSignature;
    uintptr_t firstMatch = 0;
#define INRANGE(x, a, b) (x >= a && x <= b)
#define GET_BYTE(x) (GET_BITS(x[0]) << 4 | GET_BITS(x[1]))
#define GET_BITS(x) (INRANGE((x & (~0x20)), 'A', 'F') ? ((x & (~0x20)) - 'A' + 0xa) : (INRANGE(x, '0', '9') ? x - '0' : 0))

    BYTE patByte = GET_BYTE(pattern);
    const char* oldPat = pattern;

    for (uintptr_t pCur = rangeStart; pCur < rangeEnd; pCur++)
    {
        if (!*pattern)
            return firstMatch;

        while (*(PBYTE)pattern == ' ')
            pattern++;

        if (!*pattern)
            return firstMatch;

        if (oldPat != pattern)
        {
            oldPat = pattern;
            if (*(PBYTE)pattern != '\?')
                patByte = GET_BYTE(pattern);
        }

        if (*(PBYTE)pattern == '\?' || *(BYTE*)pCur == patByte)
        {
            if (!firstMatch)
                firstMatch = pCur;

            if (!pattern[2] || !pattern[1])
                return firstMatch;

            // if (*(PWORD)pattern == '\?\?' || *(PBYTE)pattern != '\?')
            // pattern += 3;

            // else
            pattern += 2;
        }
        else
        {
            pattern = szSignature;
            firstMatch = 0;
        }
    }
#ifdef _DEBUG
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-variable"
#endif
    const char* sig = szSignature; // Put sig in here to access it in debugger
    // This will not get optimized away because we are in debug
    // Leave this in here to quickly find bad signatures in case of updates
    logF("Signature dead: %s", szSignature);
    if (false)
    {
        const char* msgToTheOverwhelmedDebugger = "SIGNATURE NOT FOUND";
        __debugbreak();
    }

#ifdef __clang__
#pragma clang diagnostic pop
#endif
#endif
    return 0u;
}
// typedef void (*HookFunctionType)(void* a1, void* a2);
static void HookFunctionInstance(UINT exitCode, LPCWSTR pszMessage, LPCWSTR errorSource, LPCWSTR argExceptionString)
{
    throw new std::exception();
}
inline void FixCLRFatalError()
{ 
    auto cp = System::Diagnostics::Process::GetCurrentProcess();
    auto enumerator = cp->Modules->GetEnumerator();
    do
    {
        auto mod = (System::Diagnostics::ProcessModule ^)(enumerator->Current);
        if (mod->ModuleName->ToLower() == "coreclr.dll")
        {
            void* baseAddress = mod->BaseAddress.ToPointer();
            int size = mod->ModuleMemorySize;
            uintptr_t result = FindSignature((uintptr_t)baseAddress, ((uintptr_t)(baseAddress) + size),
                                             "48 89 5C 24 08 48 89 74 24 10 48 89 7C 24 18 41 54 41 56 41 57 48 81 EC B0 00 00 00 4D 8B E1 4D 8B F0 48 8B DA 8B F9 44 8B 15 ? ? 23 00 65 48 8B 04 25 58 00 00 00 B9 30 01 00 00 4E 8B 3C D0 49 8B 34 0F 48 89 74 24 60 33 C0 F0 48 0F B1 35 ? ? 24 00 48 3B C6 75 11 48 8D 0D ? ? 18 00 E8 9F 1C FE FF E9 85 01 00 00 48 85 C0 74 23 BB 01 00 00 00 EB 0B 33 D2 8D 4A 32 FF 15 ? ? 16");
            if (result != 0)
            {
                void* pold;
                std::cout << "[fixClrFatalError] fix coreclr.dll on " << result << std::endl;
                HookFunction((void*)result, &pold, (void*)(HookFunctionInstance));
            }
            else
            {
                std::cout << "[fixClrFatalError] unable to find signature." << std::endl;
                std::cout << "[fixClrFatalError] please upload your coreclr.dll to LLNet." << std::endl;
                std::cout << "[fixClrFatalError] " << marshalString(mod->FileVersionInfo->FileName) << std::endl;
            }
        }
    } while (enumerator->MoveNext());
}