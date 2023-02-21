#include "pch.h"
#include "Memory.h"
#include "Menu.h"
#include "Features.h"

void Exit(HANDLE handle)
{
    CloseHandle(handle);
    std::cin.get();
    exit(0);
}

int main()
{
    for (unsigned int i = 0; i < Menu::TOTAL_OPTIONS; ++i)
    {
        Menu::toggled[i] = false;
        
        if (Menu::options[i].length() > Menu::largestString)
            Menu::largestString = Menu::options[i].length();
    }

    if (Menu::largestString >= Menu::padding)
    {
        Menu::padding = Menu::largestString + 2;
    }

    const wchar_t* processName = L"ac_client.exe";
    Memory::pid = Memory::GetPID(processName);
    std::string option;

    if (Memory::pid)
    {
        std::wcout << "Found process " << processName << " with ID (" << Memory::pid << ")\n";
    }
    else
    {
        std::wcout << "Couldn\'t find " << processName << "!\n";

        return 0;
    }

    Memory::pHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, Memory::pid);
    if (Memory::pHandle != NULL)
    {
        std::wcout << "Process " << processName << " succesfully opened!\n";
    }
    else
    {
        std::wcout << "Error opening " << processName << "!\n";
        Exit(Memory::pHandle);
    }

    Memory::BaseAddress = Memory::GetModuleBaseAddress(Memory::pid, processName);
    if (Memory::BaseAddress)
    {
        std::cout << "Found Module Base Address: " << "0x" << std::hex << Memory::BaseAddress << std::dec << std::endl;
    }
    else
    {
        std::cout << "Couldn\'t find module base address!\n";
        Exit(Memory::pHandle);
    }

    while (true)
    {
        Menu::WriteMenu();
        std::getline(std::cin, option);

        int n;
        try
        {
            n = std::stoi(option);
        } 
        catch (std::invalid_argument)
        {
            continue;
        } 
        catch (std::out_of_range)
        {
            continue;
        }

        if (n == 1)
        {
            Menu::Select(n);
        }
        else if (n == 2)
        {
            Menu::Select(n);
        }
        else
        {
            std::cerr << "\nWrong Input!\n";
        }
    }
    
    Exit(Memory::pHandle);
}
