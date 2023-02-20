#include "pch.h"
#include "Menu.h"

namespace Colors
{
	const char* red = "\x1B[31m";
	const char* green = "\x1B[32m";

	const char* end = "\x1B[0m";
};

void Menu::WriteMenu()
{
	std::cout << Menu::ascii << "\n\n";

	for (size_t i = 0; i < Menu::options.size(); ++i)
	{
		if (Menu::toggled[i] == true)
		{
			std::cout << options[i] << " [ " << Colors::green << "ON" << Colors::end << " ]\n";
		}
		else if (Menu::toggled[i] == false)
		{
			std::cout << options[i] << " [ " << Colors::red << "OFF" << Colors::end << " ]\n";
		}
	}

	std::cout << "\n\nOption -> ";
}

bool Menu::Select(const int numberChoice, bool on_off)
{
	if (options.size() < numberChoice)
		return false;

	options[numberChoice - 1] = on_off;

	return true;
}

char Menu::IsSelected(const int numberChoice)
{
	if (options.size() < numberChoice)
		return -1;

	return true ? toggled[numberChoice] == true : false;
}

const wchar_t* Menu::ascii = LR"(
	   _____               .__   __     ____  __.    ___.           
	  /  _  \   __________ |  |_/  |_  |    |/ _|__ _\_ |__   ____  
	 /  /_\  \ /  ___/  _ \|  |\   __\ |      < |  |  \ __ \_/ __ \ 
	/    |    \\___ (  <_> )  |_|  |   |    |  \|  |  / \_\ \  ___/ 
	\____|__  /____  >____/|____/__|   |____|__ \____/|___  /\___  >
			\/     \/                          \/         \/     
)";

std::vector<std::string> Menu::options = {
	"1 | Randomise Health (100-999)",
	"2 | Unlimited Ammo",
};

std::vector<bool> Menu::toggled = {};
