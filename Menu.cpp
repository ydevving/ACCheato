#include "pch.h"
#include "Menu.h"
#include "Features.h"

namespace Colors
{
	const char* red = "\x1B[31m";
	const char* green = "\x1B[32m";

	const char* end = "\x1B[0m";
};

void Menu::WriteMenu()
{
	//system("cls");
	std::cout << Menu::ascii << "\n\n";

	for (size_t i = 0; i < Menu::TOTAL_OPTIONS; ++i)
	{
		unsigned int pad = Menu::padding - options[i].length();
		if (Menu::toggled[i] == true)
		{
			std::cout << options[i] << std::setw(pad+2) << " [ " << Colors::green << "ON" << Colors::end << " ]" << std::endl;
		}
		else if (Menu::toggled[i] == false)
		{
			std::cout << options[i] << std::setw(pad+2) << " [ " << Colors::red << "OFF" << Colors::end << " ]" << std::endl;
		}
	}

	std::cout << "\n\nOption -> ";
}

void Menu::Select(const int numberChoice)
{
	bool on_off = false;
	if (!Menu::IsSelected(numberChoice))
		on_off = true;

	Menu::toggled[numberChoice - 1] = on_off;

	if (on_off == true)
	{
		std::cout << "On!\n";
		switch (numberChoice)
		{
		case 1:
			Menu::threads[numberChoice - 1] = std::thread(Features::RandomiseHP, 101, 999);
			break;
		case 2:
			Menu::threads[numberChoice - 1] = std::thread(Features::UnlimitedAmmo);
			break;
		default:
			break;
		}
	}
	else
	{
		std::cout << "Off [ Doesnt work ]\n";
	}
}

char Menu::IsSelected(const int numberChoice)
{
	if (Menu::TOTAL_OPTIONS < numberChoice)
		return -1;

	return true ? Menu::toggled[numberChoice - 1] == true : false;
}

const char* Menu::ascii = R"(
	   _____               .__   __     ____  __.    ___.           
	  /  _  \   __________ |  |_/  |_  |    |/ _|__ _\_ |__   ____  
	 /  /_\  \ /  ___/  _ \|  |\   __\ |      < |  |  \ __ \_/ __ \ 
	/    |    \\___ (  <_> )  |_|  |   |    |  \|  |  / \_\ \  ___/ 
	\____|__  /____  >____/|____/__|   |____|__ \____/|___  /\___  >
			\/     \/                          \/         \/     
)";

std::string Menu::options[Menu::TOTAL_OPTIONS] = {
	"1 | Randomise Health (101-999)",
	"2 | Unlimited Ammo",
};

bool Menu::toggled[Menu::TOTAL_OPTIONS] = {};

std::thread Menu::threads[Menu::TOTAL_OPTIONS] = {};

unsigned int Menu::padding = 25;

unsigned int Menu::largestString = 0;
