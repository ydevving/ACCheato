#pragma once

class Menu
{
public:
	static void WriteMenu();
	static void Select(const unsigned int numberChoice);
	static char IsSelected(const unsigned int numberChoice);
public:
	static const int TOTAL_OPTIONS = 3;
	static unsigned int largestString;
	static unsigned int padding;
	static const char* ascii;
	static std::string options[TOTAL_OPTIONS];
	static bool toggled[TOTAL_OPTIONS];
	static std::thread threads[TOTAL_OPTIONS];
};
