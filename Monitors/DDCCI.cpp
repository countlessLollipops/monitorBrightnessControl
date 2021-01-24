#pragma comment(lib, "dxva2.lib")
#include <iostream>

#include <highlevelmonitorconfigurationapi.h>
#include <strsafe.h>

#include "DDCCI.h"

void ddcciBrightness(int brightness, HANDLE &hPhysicalMonitor)
{
    BOOL bSuccess = false;
    DWORD dwMinimumBrightness = 0;
    DWORD dwCurrentBrightness = 0;
    DWORD dwMaximumBrightness = 0;
    bSuccess = GetMonitorBrightness(hPhysicalMonitor, &dwMinimumBrightness, &dwCurrentBrightness, &dwMaximumBrightness);
    std::cout << dwMinimumBrightness << "\t" << dwCurrentBrightness << "\t" << dwMaximumBrightness << std::endl;

    DWORD  dwNewBrightness = brightness;
    bSuccess = SetMonitorBrightness(hPhysicalMonitor, dwNewBrightness);

    DestroyPhysicalMonitor(hPhysicalMonitor);
}