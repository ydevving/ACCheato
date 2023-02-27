#include "pch.h"
#include "Features.h"
#include "Memory.h"
#include "Menu.h"

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> distr(101, 999);

unsigned int INTMAX = INT_MAX;
int oldHealth = 100;

void Features::UnlimitedHP(unsigned int idx)
{
	void* Health = (void*)Memory::FindDMAAddy(Memory::pHandle, Memory::BaseAddress + 0x10F4F4, { 0xF8 });

	Memory::PatchEx(Memory::pHandle, Health, &INTMAX, sizeof(INTMAX));

	while (Menu::toggled[idx] == true)
	{
		Memory::PatchEx(Memory::pHandle, Health, &INTMAX, sizeof(INTMAX));
		Sleep(10);
	}

	Memory::PatchEx(Memory::pHandle, (void*)Health, &oldHealth, sizeof(oldHealth));
}

void Features::UnlimitedAmmo(unsigned int idx)
{
	Memory::PatchEx(Memory::pHandle, (BYTE*)(Memory::BaseAddress + 0x637e9), (BYTE*)"\xFF\x06", 2);

	while (Menu::toggled[idx] == true) {}

	unsigned int mag = 20;

	Memory::PatchEx(Memory::pHandle, (BYTE*)(Memory::BaseAddress + 0x637e9), (BYTE*)"\xFF\x0E", 2);
}

void Features::NoRecoil(unsigned int idx)
{
	Memory::NopEx(Memory::pHandle, (BYTE*)(Memory::BaseAddress + 0x63786), 10);

	while (Menu::toggled[idx] == true) {}

	Memory::PatchEx(Memory::pHandle, (BYTE*)(Memory::BaseAddress + 0x63786), (BYTE*)"\x50\x8D\x4C\x24\x1c\x51\x8B\xCE\xFF\xD2", 10);
}
