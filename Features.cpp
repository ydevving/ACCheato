#include "pch.h"
#include "Features.h"
#include "Memory.h"
#include "Menu.h"

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> distr(101, 999);

void Features::RandomiseHP(unsigned int idx)
{
	void* Health = (void*)Memory::FindDMAAddy(Memory::pHandle, Memory::BaseAddress + 0x10F4F4, { 0xF8 });
	int oldHealth = 100, r = distr(gen);

	Memory::PatchEx(Memory::pHandle, Health, &r, sizeof(int));

	while (Menu::toggled[idx] == true)
	{
		Memory::PatchEx(Memory::pHandle, Health, &r, sizeof(int));
	}

	Memory::PatchEx(Memory::pHandle, (void*)Health, &oldHealth, sizeof(int));
}

void Features::UnlimitedAmmo(unsigned int idx)
{
	unsigned int ammoTotal = INT_MAX;

	uintptr_t Ammo = Memory::FindDMAAddy(Memory::pHandle, Memory::BaseAddress + 0x10F4F4, { 0x150 });
	Memory::PatchEx(Memory::pHandle, (BYTE*)Ammo, &ammoTotal, sizeof(ammoTotal));

	while (Menu::toggled[idx] == true) {}

	unsigned int mag = 20;

	Memory::PatchEx(Memory::pHandle, (BYTE*)Ammo, &mag, sizeof(unsigned int));
}