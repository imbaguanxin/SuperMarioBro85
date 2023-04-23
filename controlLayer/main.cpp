#include "controller.hpp"
#include <chrono>

int main()
{
    FsOpenWindow(32, 32, 960, 960, 1);
    Controller c;
    auto now = std::chrono::system_clock::now();
    double time_interval = 0;
    while (true != c.IsTerminated())
    {
        auto next_now = std::chrono::system_clock::now();
        time_interval = double(std::chrono::duration_cast<std::chrono::milliseconds>(next_now - now).count()) / 1000;
        now = next_now;
        printf("time interval: %f\n", time_interval / 10);

        c.RunOneStep(time_interval);
        c.Draw();
        FsSleep(100);
    }
}