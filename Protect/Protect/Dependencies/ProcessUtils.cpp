#include "ProcessUtils.h"
#include "../Dependencies/ForbiddenList.h"

#include <Windows.h>
#include <Psapi.h>
#include <vector>
#include <string>

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
    int length = GetWindowTextLengthW(hwnd);
    if (length == 0)
        return TRUE;

    std::wstring buffer(length, L'\0');
    GetWindowTextW(hwnd, &buffer[0], length + 1);

    auto windows = reinterpret_cast<std::vector<ProcessUtils::WindowInfo>*>(lParam);

    ProcessUtils::WindowInfo info;
    info.title = buffer;
    info.hwnd = hwnd;
    info.pid = ProcessUtils::GetPIDFromHWND(hwnd);
    info.processName = ProcessUtils::GetProcessNameFromPID(info.pid);

    windows->push_back(info);

    return TRUE;
}

std::vector<ProcessUtils::WindowInfo> ProcessUtils::GetAllWindowTitles()
{
    std::vector<WindowInfo> windows;
    EnumWindows(EnumWindowsProc, reinterpret_cast<LPARAM>(&windows));
    return windows;
}

DWORD ProcessUtils::GetPIDFromHWND(HWND hwnd)
{
    DWORD pid = 0;
    GetWindowThreadProcessId(hwnd, &pid);
    return pid;
}

std::wstring ProcessUtils::GetProcessNameFromPID(DWORD pid)
{
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);
    if (!hProcess)
        return L"";

    wchar_t name[MAX_PATH] = { 0 };
    GetModuleBaseNameW(hProcess, nullptr, name, MAX_PATH);
    CloseHandle(hProcess);

    return name;
}

std::vector<ProcessUtils::WindowInfo> ProcessUtils::GetForbiddenWindows()
{
    std::vector<WindowInfo> all = GetAllWindowTitles();
    std::vector<WindowInfo> forbidden;

    for (auto& w : all)
    {
        for (const auto& blockedTitle : ForbiddenList::Titles)
        {
            if (w.title.find(blockedTitle) != std::wstring::npos)
            {
                forbidden.push_back(w);
                break;
            }
        }
    }

    return forbidden;
}
