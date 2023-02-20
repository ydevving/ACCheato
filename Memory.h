#pragma once

class Memory
{
public:
	static DWORD GetPID(const wchar_t* processName);
	static uintptr_t GetModuleBaseAddress(DWORD procId, const wchar_t* modName);
	static uintptr_t FindDMAAddy(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int>offsets);
};