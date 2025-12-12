#include "TitleProtector.h"
#include "../Dependencies/ForbiddenList.h"
#include "../dependencies/ProcessUtils.h"
#include <iostream>
#include <sstream>
#include <Windows.h>

#define CLR_WHITE  "\x1b[38;2;255;255;255m"
#define CLR_GREEN  "\x1b[38;2;4;141;106m"
#define CLR_RED    "\x1b[38;2;222;49;121m"
#define CLR_RESET  "\x1b[0m"

#define DBG(tag, msg) \
    std::cout << CLR_WHITE "[" \
              << CLR_GREEN "DBG" \
              << CLR_WHITE "] " \
              << CLR_RED << tag \
              << CLR_WHITE ": " \
              << CLR_GREEN << msg \
              << CLR_RESET \
              << "\n";

TitleProtector::TitleProtector() : running(false) {}
TitleProtector::~TitleProtector() { Stop(); }

void PrintAscii() {
    std::cout << CLR_GREEN
        "              ,\n"
        "     __  _.-` `'-.\n"
        "    /||\\'._ __{}_(\n"
        "    ||||  |'--.__\\\n"
        "    |  L.(   ^_\\^\n"
        "    \\ .-' |   _ |\n"
        "    | |   )\\___/\n"
        "    |  \\-'`:._]\n"
        "    \\__/;      '-.\n\n"
        << CLR_RESET;
}

void TitleProtector::Start() {
    if (running.load()) return;

    PrintAscii();
    DBG("Dev", "SilvaTweaks");
    DBG("Initialization", "Starting Protection Engine");
    DBG("Configuration", "Loading Forbidden List");

    running = true;
    worker = std::thread(&TitleProtector::ThreadLoop, this);
    SetThreadPriority(worker.native_handle(), THREAD_PRIORITY_LOWEST);

    DBG("Status", "Protection Active");
}

void TitleProtector::Stop() {
    if (!running.load()) return;

    DBG("Shutdown", "Stopping Protection");

    running = false;
    if (worker.joinable())
        worker.join();

    DBG("Status", "Protection Disabled");
}

void TitleProtector::ThreadLoop() {
    DBG("Monitor", "Scan Started");

    bool firstScan = true;
    static DWORD lastKilledPID = 0;

    while (running.load()) {
        auto windows = ProcessUtils::GetAllWindowTitles();

        if (firstScan) {
            std::stringstream ss;
            ss << windows.size() << " Windows Detected";
            DBG("Scan", ss.str());
            firstScan = false;
        }

        for (const auto& window : windows) {

            if (window.pid == lastKilledPID)
                continue;

            for (const auto& forbidden : ForbiddenList::Titles) {

                bool matchTitle = (window.title.find(forbidden) != std::wstring::npos);
                bool matchProc = (_wcsicmp(window.processName.c_str(), forbidden.c_str()) == 0);

                if (matchTitle || matchProc) {
                    DBG("Detection", "Forbidden target detected");
                    DBG("ProcessID", std::to_string(window.pid).c_str());
                    DBG("Action", "Terminating Process");

                    HANDLE h = OpenProcess(PROCESS_TERMINATE, FALSE, window.pid);
                    if (h) {
                        TerminateProcess(h, 0x2A1);
                        CloseHandle(h);
                        lastKilledPID = window.pid;
                    }
                    break;
                }
            }
        }

        Sleep(1000);
    }

    DBG("Monitor", "Scan Stopped");
}
