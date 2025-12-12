#pragma once
#include <string>
#include <vector>
#include <Windows.h>

namespace ProcessUtils {

    struct WindowInfo {
        std::wstring title;
        std::wstring processName;
        HWND hwnd = nullptr;
        DWORD pid = 0;
    };

    std::vector<WindowInfo> GetAllWindowTitles();
    DWORD GetPIDFromHWND(HWND hwnd);
    std::wstring GetProcessNameFromPID(DWORD pid);

    std::vector<WindowInfo> GetForbiddenWindows();
}
