
#include "desktopmonitor.h"

desktopMonitor::desktopMonitor()
{
    hWnd = GetDesktopWindow();

    //获取显示器句柄
    hMonitor = MonitorFromWindow(hWnd, MONITOR_DEFAULTTOPRIMARY);

    //获取显示器数量
    BOOL bSuccess = GetNumberOfPhysicalMonitorsFromHMONITOR(hMonitor, &cPhysicalMonitors);
    //std::cout << bSuccess << std::endl;

    if (bSuccess)
    {
        //分配PHYSICAL_MONITOR结构数组
        pPhysicalMonitors = (LPPHYSICAL_MONITOR)malloc(cPhysicalMonitors * sizeof(PHYSICAL_MONITOR));

        if (pPhysicalMonitors != NULL)
        {
            //获取数组
            bSuccess = GetPhysicalMonitorsFromHMONITOR(hMonitor, cPhysicalMonitors, pPhysicalMonitors);
        }
    }
}

desktopMonitor::~desktopMonitor()
{
    //关闭显示器句柄
    bSuccess = DestroyPhysicalMonitors(cPhysicalMonitors, pPhysicalMonitors);

    //释放数组
    free(pPhysicalMonitors);
}

LPPHYSICAL_MONITOR desktopMonitor::getPhyxMonitor()
{
    return pPhysicalMonitors;
}