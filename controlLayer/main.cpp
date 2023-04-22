#include "controller.hpp"

int main()
{
    FsOpenWindow(32, 32, 960, 960, 1);
    Controller c;
    while (true != app.MustTerminate())
    {
        app.RunOneStep();
        app.Draw();
        FsSleep(10);
    }
}