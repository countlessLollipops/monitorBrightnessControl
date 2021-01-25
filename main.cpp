#include <iostream>

#include "Monitors/desktopMonitor.h"
#include "Monitors/laptopMonitor.h"
#include "Monitors/DDCCI.h"

void help() {
    std::cout << "(c) Cocoa, 2021" << std::endl;
    std::cout << "with 2 args:" << std::endl;
    std::cout << "Usage: BrightnessCtl.exe -[type] <level>" << std::endl;
    std::cout << "\tOption:" << std::endl;
    std::cout << "\t-[type]\t{laptopDisplay, monitorDisplay}" << std::endl;
    std::cout << "\t<level>\t brightness level need to be specified" << std::endl;
    std::cout << std::endl;
    std::cout << "with 3 args:" << std::endl;
    std::cout << "only for desktopDisplay" << std::endl;
    std::cout << "Usage: BrightnessCtl.exe -desktopDisplay <num> <level>" << std::endl;
    std::cout << std::endl;

    exit(0);
}

int main(int argc, char *argv[]) {

    std::cout << 1 << std::endl;
    if (argc == 3) {
        std::cout << "�������� ��Ļ ����" << std::endl;
        if (atoi(argv[2]) >= 0 && atoi(argv[2]) <= 100) {
            if (strcmp("-desktopDisplay", argv[1]) == 0) {
                std::cout << "����������Ļ����" << std::endl;
                desktopMonitor *allMonitor = new desktopMonitor();

                LPPHYSICAL_MONITOR pPhysicalMonitors = allMonitor->getPhyxMonitor();
                HANDLE hPhysicalMonitor = pPhysicalMonitors[0].hPhysicalMonitor;

                ddcciBrightness(atoi(argv[2]), hPhysicalMonitor);

                delete allMonitor;
            } else if (strcmp("-laptopDisplay", argv[1]) == 0) {
                std::cout << "���ڱʼǱ���Ļ����" << std::endl;
                set_LCD_Brightness(atoi(argv[2]));
            } else {
                help();
            }
        }
    } else if (argc == 4) {
        std::cout << "�������� ������Ļ ��Ļ��� ����" << std::endl;
        if (atoi(argv[3]) >= 0 && atoi(argv[3]) <= 100 && atoi(argv[2]) >= 0) {
            if (strcmp("-desktopDisplay", argv[1]) == 0) {
                desktopMonitor *allMonitor = new desktopMonitor();
                LPPHYSICAL_MONITOR pPhysicalMonitor = allMonitor->getPhyxMonitor();
                HANDLE hPhysicalMonitor = pPhysicalMonitor[atoi(argv[2])].hPhysicalMonitor;
                ddcciBrightness(atoi(argv[3]), hPhysicalMonitor);
                delete allMonitor;
            } else {
                help();
            }
        }
    } else {
        help();
    }
    return 0;
}
