#include <iostream>
#include <Windows.h>
#include "./Features/TitleProtector.h"

int main() {
    TitleProtector protector;
    protector.Start();

    while (true) {
        Sleep(1000);
    }

    return 0;
}
