#include "pch.h"
#include "Features.h"
#include "Memory.h"

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> distr(100, 999);

void Features::RandomiseHP(int startRange, int endRange)
{
	std::cout << "RandomiseHP" << std::endl;
	int r = distr(gen);

	uintptr_t Health = Memory::FindDMAAddy(Memory::pHandle, Memory::BaseAddress + 0x10F4F4, { 0xF8 });

	//Memory::PatchEx(Memory::pHandle, (void*)Health, &r, sizeof(int));
	WriteProcessMemory(Memory::pHandle, (void*)Health, &r, sizeof(int), NULL);
}

void Features::UnlimitedAmmo()
{
	unsigned int* ammoTotal = new unsigned int(4);

	uintptr_t Ammo = Memory::FindDMAAddy(Memory::pHandle, Memory::BaseAddress + 0x10F4F4, { 0x150 });
	WriteProcessMemory(Memory::pHandle, (BYTE*)Ammo, ammoTotal, sizeof(unsigned int), NULL);

	delete ammoTotal;
}