
#ifndef MONITORBRIGHTNESSCONTROL_DESKTOPMONITOR_H
#define MONITORBRIGHTNESSCONTROL_DESKTOPMONITOR_H

#include <physicalmonitorenumerationapi.h>
#include <highlevelmonitorconfigurationapi.h>
#include <Windows.h>

class desktopMonitor
{
private:
    HMONITOR hMonitor = NULL;
    DWORD cPhysicalMonitors = 0;
    LPPHYSICAL_MONITOR pPhysicalMonitors = NULL;
    HWND hWnd;
    BOOL bSuccess = false;

public:
    desktopMonitor();
    ~desktopMonitor();

    LPPHYSICAL_MONITOR getPhyxMonitor();
};

#endif //MONITORBRIGHTNESSCONTROL_DESKTOPMONITOR_H
