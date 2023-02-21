#include "pch.h"
#include "Features.h"
#include "Memory.h"

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> distr(101, 999);

void Features::RandomiseHP(bool state)
{
	std::cout << "RandomiseHP" << std::endl;
	int oldHP;
	int r = distr(gen);

	uintptr_t Health = Memory::FindDMAAddy(Memory::pHandle, Memory::BaseAddress + 0x10F4F4, { 0xF8 });
	Memory::PatchEx(Memory::pHandle, (void*)Health, &r, sizeof(int));

	while (state == true) {}

	
}

void Features::UnlimitedAmmo()
{
	unsigned int ammoTotal = INT_MAX;

	uintptr_t Ammo = Memory::FindDMAAddy(Memory::pHandle, Memory::BaseAddress + 0x10F4F4, { 0x150 });
	Memory::PatchEx(Memory::pHandle, (BYTE*)Ammo, &ammoTotal, sizeof(ammoTotal));
}