#include "Memory.h"
#include <psapi.h>
#include "../Globals/Globals.h"

bool Memory::Init()
{
    g.GameHwnd = FindWindowA(TargetClass, nullptr);

    if (!g.GameHwnd)
    {
        MessageBoxA(nullptr, "Please Open FiveM", "Info", MB_TOPMOST | MB_OK);

        while (!g.GameHwnd)
        {
            g.GameHwnd = FindWindowA(TargetClass, nullptr);

            Sleep(500);
        }
    }

    GetWindowThreadProcessId(g.GameHwnd, &PID);
    pHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID);

    if (!pHandle)
    {
        MessageBoxA(nullptr, "Failed to get process handle", "ERROR", MB_TOPMOST | MB_ICONERROR | MB_OK);
        return false;
    }

    char pModule[128]{};
    GetModuleBaseNameA(pHandle, nullptr, pModule, sizeof(pModule)); // like "FiveM_b2944_GTAProcess.exe"
    g.ProcName = pModule;
    BaseAddress = GetModuleBase(pModule);

    return true;
}

uintptr_t Memory::GetModuleBase(const std::string module)
{
    MODULEENTRY32 entry{};
    entry.dwSize = sizeof(MODULEENTRY32);

    uintptr_t result = 0;
    const auto snapShot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, PID);

    while (Module32Next(snapShot, &entry))
    {
        if (!module.compare(entry.szModule))
        {
            result = reinterpret_cast<uintptr_t>(entry.modBaseAddr);
            break;
        }
    }

    if (snapShot)
        CloseHandle(snapShot);

    return result;
}

Memory m;