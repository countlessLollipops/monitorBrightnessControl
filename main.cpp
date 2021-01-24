#include <iostream>

#include "Monitors/desktopMonitor.h"
#include "Monitors/laptopMonitor.h"
#include "Monitors/DDCCI.h"

void help() {
    std::cout << "(c) Cocoa, 2021" << std::endl;
    std::cout << "Usage: BrightnessCtl.exe -[type] <level>" << std::endl;
    std::cout << "\tOption:" << std::endl;
    std::cout << "\t-[type]\t{laptopDisplay, monitorDisplay}" << std::endl;
    std::cout << "\t<level>\t brightness level need to be specified" << std::endl;
    std::cout << "\n  Error code:\n" << std::endl;
    std::cout << "\tPass: 0;  Fail: 1" << std::endl;
    exit(0);
}

int main(int argc, char *argv[]) {

    std::cout << 1 << std::endl;
    if (argc == 3) {
        std::cout << "两个参数 屏幕 亮度" << std::endl;
        if (atoi(argv[2]) >= 0 && atoi(argv[2]) <= 100) {
            if (strcmp("-desktopDisplay", argv[1]) == 0) {
                desktopMonitor *allMonitor = new desktopMonitor();

                LPPHYSICAL_MONITOR pPhysicalMonitors = allMonitor->getPhyxMonitor();
                HANDLE hPhysicalMonitor = pPhysicalMonitors[0].hPhysicalMonitor;

                ddcciBrightness(atoi(argv[2]), hPhysicalMonitor);

                delete allMonitor;
            } else if (strcmp("-laptopDisplay", argv[1]) == 0) {
                set_LCD_Brightness(atoi(argv[2]));
            }
        }
    } else if (argc == 4) {
        std::cout << "三个参数 桌面屏幕 屏幕编号 亮度" << std::endl;
        if (atoi(argv[3]) >= 0 && atoi(argv[3]) <= 100 && atoi(argv[2]) >= 0) {
            if (strcmp("-desktopDisplay", argv[1]) == 0) {
                desktopMonitor *allMonitor = new desktopMonitor();
                LPPHYSICAL_MONITOR  pPhysicalMonitor=allMonitor->getPhyxMonitor();
                HANDLE hPhysicalMonitor = pPhysicalMonitor[atoi(argv[2])].hPhysicalMonitor;
                ddcciBrightness(atoi(argv[3]),hPhysicalMonitor);
                delete allMonitor;
            }
            else{
                help();
            }
        }
    } else {
        help();
    }
    return 0;
}
