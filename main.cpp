#include "pch.h"
#include "Memory.h"
#include "Menu.h"

void Exit(HANDLE handle)
{
    CloseHandle(handle);
    std::cin.get();
    exit(0);
}

int main()
{
    Menu::options.resize(10);
    for (unsigned int i = 1; i <= Menu::options.size(); ++i)
    {
        Menu::toggled.push_back(false);
    }

    const wchar_t* processName = L"ac_client.exe";
    DWORD pid = Memory::GetPID(processName);
    std::string option;

    if (pid)
    {
        std::wcout << "Found process " << processName << " with ID (" << pid << ")\n";
    }
    else
    {
        std::wcout << "Couldn\'t find " << processName << "!\n";

        return 0;
    }

    HANDLE pHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    if (pHandle != NULL)
    {
        std::wcout << "Process " << processName << " succesfully opened!\n";
    }
    else
    {
        std::wcout << "Error opening " << processName << "!\n";
        Exit(pHandle);
    }

    uintptr_t baseAddr = Memory::GetModuleBaseAddress(pid, processName);
    if (baseAddr)
    {
        std::cout << "Found Module Base Address: " << "0x" << std::hex << baseAddr << std::dec << std::endl;
    }
    else
    {
        std::cout << "Couldn\'t find module base address!\n";
        Exit(pHandle);
    }

    Menu::WriteMenu();
    while (true)
    {
        std::getline(std::cin, option);
        if (option == "1")
        {

        }
        else if (option == "2")
        {

        }
    }
    
    Exit(pHandle);
}
