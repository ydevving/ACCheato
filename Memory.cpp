#include "pch.h"
#include "Memory.h"

DWORD Memory::GetPID(const wchar_t* processName)
{
    DWORD pid = 0;
    HANDLE pSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (pSnap == INVALID_HANDLE_VALUE) return pid;

    PROCESSENTRY32 pEntry;
    pEntry.dwSize = sizeof(pEntry);

    unsigned int counter = 0;

    if (Process32First(pSnap, &pEntry))
    {
        do
        {
            if (!_wcsicmp(pEntry.szExeFile, processName))
            {
                pid = pEntry.th32ProcessID;
                break;
            }
        } while (Process32Next(pSnap, &pEntry));
    }

    CloseHandle(pSnap);
    return pid;
}

uintptr_t Memory::GetModuleBaseAddress(DWORD procId, const wchar_t* modName)
{
    uintptr_t modBaseAddr = 0;
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);
    if (hSnap == INVALID_HANDLE_VALUE) return modBaseAddr;

    MODULEENTRY32 modEntry;

    modEntry.dwSize = sizeof(modEntry);

    if (Module32First(hSnap, &modEntry))
    {
        do
        {
            if (!_wcsicmp(modEntry.szModule, modName))
            {
                modBaseAddr = (uintptr_t)modEntry.modBaseAddr;
                break;
            }

        } while (Module32Next(hSnap, &modEntry));
    }

    CloseHandle(hSnap);
    return modBaseAddr;
}

uintptr_t Memory::FindDMAAddy(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int>offsets)
{
    for (unsigned int i = 0; i < offsets.size(); i++)
    {
        ReadProcessMemory(hProc, (BYTE*)ptr, &ptr, sizeof(ptr), 0);
        ptr += offsets[i];
    }

    return ptr;
}
