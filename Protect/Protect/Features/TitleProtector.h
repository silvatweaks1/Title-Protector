#pragma once
#include <thread>
#include <atomic>

class TitleProtector {
public:
    TitleProtector();
    ~TitleProtector();

    void Start();
    void Stop();

private:
    void ThreadLoop();

    std::thread worker;
    std::atomic<bool> running;
};
