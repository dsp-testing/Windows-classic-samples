#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <iostream>
#include <cstring>

// Unsafe buffer overflow function for demonstration/testing only!
void vulnerableFunction(const wchar_t* input) {
    wchar_t buffer[8];
    // Unsafe: No bounds checking!
    wcscpy(buffer, input);
    std::wcout << L"Buffer: " << buffer << std::endl;
}

// DllMain entry point
BOOL APIENTRY DllMain(HMODULE hModule,
                      DWORD  ul_reason_for_call,
                      LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        // Simulate: treat lpReserved as a string pointer for this POC
        if (lpReserved) {
            // For demo, assume lpReserved is a wchar_t* (not normally the case, but for POC)
            const wchar_t* input = reinterpret_cast<const wchar_t*>(lpReserved);
            std::wcout << L"Input received in DllMain: " << input << std::endl;
            vulnerableFunction(input);
        }
        else {
            std::wcout << L"No input provided to DllMain (lpReserved is NULL)" << std::endl;
        }
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
