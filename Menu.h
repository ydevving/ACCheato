#pragma once

#include "pch.h"

class Menu
{
public:
	static void WriteMenu();
	static bool Select(int numberChoice, bool on_off);
	static char IsSelected(const int numberChoice);
public:
	static const wchar_t* ascii;
	static std::vector<std::string> options;
	static std::vector<bool> toggled;
};
