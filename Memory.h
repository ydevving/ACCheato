#pragma once


class Memory
{
public:
	static DWORD GetPID(const wchar_t* processName);
	static uintptr_t GetModuleBaseAddress(DWORD procId, const wchar_t* modName);
	static uintptr_t FindDMAAddy(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int>offsets);
	static void PatchEx(HANDLE hProcess, void* dst, void* buffer, size_t size);
	static void NopEx(HANDLE hProcess, void* dst, size_t size);
public:
	static HANDLE pHandle;
	static uintptr_t BaseAddress;
	static DWORD pid;
};