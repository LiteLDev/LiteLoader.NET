/* 8/15/2022 - LazuliKao 
* it might not be the best solution but currently, I only have done this.
*
* without this fix, as long as any function called in managed code will lose
* native "try catch", and all fatal exceptions will be handled by "coreclr"
* instead of already written C++ "try catch", which causes a fatal error
* and terminate the program.
* the solution is to hook "coreclr.dll" and redirect the `LogInfoForFatalError` function
* ```
* PublicSymbol    ?LogInfoForFatalError@@YAXIPEB_W00@Z
* RelativeVirtualAddress  2480668
* ```
* (This method will be called by "coreclr" during a fatal error, after 
*  which the program will be terminated)
* By throwing a C++ exception directly in this method, you can catch
* the exception outside, instead of terminating the program.
*/

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
    return 0u;
}
#pragma unmanaged
typedef void (*LogInfoForFatalErrorType)(UINT exitCode, LPCWSTR pszMessage, LPCWSTR errorSource, LPCWSTR argExceptionString);
#pragma unmanaged
static void* oldLogInfoForFatalError;
#pragma unmanaged
typedef void (*EEPolicy_LogFatalErrorType)(UINT exitCode, UINT_PTR address, LPCWSTR pszMessage, PEXCEPTION_POINTERS pExceptionInfo, LPCWSTR errorSource, LPCWSTR argExceptionString);
#pragma unmanaged
static void* oldEEPolicy_LogFatalError = nullptr;
#pragma unmanaged
void LogInfoForFatalError(UINT exitCode, LPCWSTR pszMessage, LPCWSTR errorSource, LPCWSTR argExceptionString)
{
    // call old function to print info
    ((LogInfoForFatalErrorType)oldLogInfoForFatalError)(exitCode, pszMessage, errorSource, argExceptionString);
    // unmanaged is necessary,otherwise it will cause stack overflow
    // do not use other functions outside of this function
    if (oldEEPolicy_LogFatalError == nullptr)
    {
        std::cout << "[FixCLRFatalError] CLR Fatal Error." << std::endl;
        std::cout << "[FixCLRFatalError] ExitCode : " << exitCode << std::endl;
        if (pszMessage != nullptr) {
            std::cout << "[FixCLRFatalError] pszMessage : ";
            wprintf_s(pszMessage);
            std::cout << std::endl;
        }
        if (errorSource != nullptr)
        {
            std::cout << "[FixCLRFatalError] errorSource : ";
            wprintf_s(errorSource);
            std::cout << std::endl;
        }
        if (argExceptionString != nullptr) {
            std::cout << "[FixCLRFatalError] argExceptionString : ";
            wprintf_s(argExceptionString);
            std::cout << std::endl;
        }
    }
    // throw an exception which could be caught outside ,otherwise the program will be terminated by clr
    throw;
}
#pragma unmanaged
void EEPolicy_LogFatalError(UINT exitCode, UINT_PTR address, LPCWSTR pszMessage, PEXCEPTION_POINTERS pExceptionInfo, LPCWSTR errorSource, LPCWSTR argExceptionString)
{
    // unmanaged is necessary,otherwise it will cause stack overflow
    // do not use other functions outside of this function
    // call original
    std::cout << "[FixCLRFatalError] CLR Fatal Error." << std::endl;
    std::cout << "[FixCLRFatalError] Address : " << address << std::endl;
    std::cout << "[FixCLRFatalError] ExitCode : " << exitCode << std::endl;
    if (pszMessage != nullptr) {
        std::cout << "[FixCLRFatalError] pszMessage : ";
        wprintf_s(pszMessage);
        std::cout << std::endl;
    }
    if (errorSource != nullptr)
    {
        std::cout << "[FixCLRFatalError] errorSource : ";
        wprintf_s(errorSource);
        std::cout << std::endl;
    }
    if (argExceptionString != nullptr) {
        std::cout << "[FixCLRFatalError] argExceptionString : ";
        wprintf_s(argExceptionString);
        std::cout << std::endl;
    }
    if (pExceptionInfo != nullptr) {
        std::cout << "[FixCLRFatalError] ExceptionAddress : " << pExceptionInfo->ExceptionRecord->ExceptionAddress << std::endl;
        // https://github.com/dotnet/runtime/blob/43c9f6bf1c1a4c6e118bbee68a8aa213a8ba644e/src/coreclr/vm/eepolicy.cpp#L426
        std::cout << "[FixCLRFatalError] ExceptionCode : " << ((pExceptionInfo && pExceptionInfo->ExceptionRecord) ? pExceptionInfo->ExceptionRecord->ExceptionCode : 0) << std::endl;
        std::cout << "[FixCLRFatalError] ExceptionFlags : " << pExceptionInfo->ExceptionRecord->ExceptionFlags << std::endl;
        if (pExceptionInfo->ExceptionRecord->ExceptionInformation != nullptr)
        {
            std::cout << "[FixCLRFatalError] ExceptionInformation : " << *(pExceptionInfo->ExceptionRecord->ExceptionInformation) << std::endl;
        }
    }
    ((EEPolicy_LogFatalErrorType)oldEEPolicy_LogFatalError)(exitCode, address, pszMessage, pExceptionInfo, errorSource, argExceptionString);
}
#pragma managed
inline void FixCLRFatalError(Logger& logger)
{
    auto cp = System::Diagnostics::Process::GetCurrentProcess();
    for each (System::Diagnostics::ProcessModule ^ mod in cp->Modules)
    {
        if (mod->ModuleName->ToLower() == "coreclr.dll")
        {
            void* baseAddress = mod->BaseAddress.ToPointer();
            int size = mod->ModuleMemorySize;
            // To update signature please use this : https://github.com/LazuliKao/CoreClrPatch/blob/main/build.fsx
            
            // ?LogInfoForFatalError@@YAXIPEB_W00@Z
            // https://github.com/dotnet/runtime/blob/43c9f6bf1c1a4c6e118bbee68a8aa213a8ba644e/src/coreclr/vm/eepolicy.cpp#L324
            uintptr_t result = FindSignature((uintptr_t)baseAddress, ((uintptr_t)(baseAddress)+size),
                "48 89 5C 24 08 48 89 74 24 10 48 89 7C 24 18 41 ? 41 56 41 57 48 81 EC ? 00 00 00 4D 8B ? ? 8B ? 48 8B DA 8B ? ? ?");
            if (result != 0)
            {
                HookFunction((void*)result, &oldLogInfoForFatalError, (void*)(LogInfoForFatalError));
                logger.info("The fatal error of CoreCLR has been redirected. {}", result);
                // ?LogFatalError@EEPolicy@@CAXI_KPEB_WPEAU_EXCEPTION_POINTERS@@11@Z
                // https://github.com/dotnet/runtime/blob/9d6396deb02161f5ee47af72ccac52c2e1bae458/src/coreclr/vm/eepolicy.cpp#L410
                uintptr_t eepolicylog = FindSignature((uintptr_t)baseAddress, ((uintptr_t)(baseAddress)+size),
                    "40 53 56 57 41 ? 41 ? 41 57 48 81 EC ? 0C 00 00 48 8B 05 ? ? ? 00 48 33 C4 48 89 84 24 ? 0C 00 00 49 8B D9 48 89 9C");
                if (eepolicylog != 0)
                {
                    HookFunction((void*)eepolicylog, &oldEEPolicy_LogFatalError, (void*)(EEPolicy_LogFatalError));
                }
            }
            else
            {
                logger.info("Unable to find signature.");
                logger.info("Please open an issue on LiteLoader.NET repo and upload your coreclr version({}) and dll file.", marshalString(System::Environment::Version->ToString()));
                logger.info("{}", marshalString(mod->FileVersionInfo->FileName));
            }
        }
    }
}
