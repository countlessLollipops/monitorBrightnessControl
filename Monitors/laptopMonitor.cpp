
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

//#include "laptopMonitor.h"

#define IOCTL_VIDEO_QUERY_SUPPORTED_BRIGHTNESS	CTL_CODE(FILE_DEVICE_VIDEO, 0x125, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_VIDEO_QUERY_DISPLAY_BRIGHTNESS CTL_CODE(FILE_DEVICE_VIDEO, 0x126, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_VIDEO_SET_DISPLAY_BRIGHTNESS CTL_CODE(FILE_DEVICE_VIDEO, 0x127, METHOD_BUFFERED, FILE_ANY_ACCESS)

typedef struct _DISPLAY_BRIGHTNESS {
    UCHAR ucDisplayPolicy;
    UCHAR ucACBrightness;
    UCHAR ucDCBrightness;
} DISPLAY_BRIGHTNESS, * PDISPLAY_BRIGHTNESS;

void set_LCD_Brightness(int level)
{
    HANDLE hDevice;
    DWORD nOutBufferSize = 256;
    BYTE SupportedBrightness[256];
    DWORD g_supportedLevelCount;
    DISPLAY_BRIGHTNESS displayBrightness;

    memset(SupportedBrightness, 0, sizeof(SupportedBrightness));

    LPCSTR lpFileName = "\\\\.\\LCD";
    hDevice = CreateFileA(lpFileName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, 0);
    if (hDevice == INVALID_HANDLE_VALUE)
    {
        printf("open \\\\.\\LCD error");
        exit(1);
    }

    if (!DeviceIoControl(hDevice, IOCTL_VIDEO_QUERY_SUPPORTED_BRIGHTNESS, NULL, 0, SupportedBrightness, nOutBufferSize, &g_supportedLevelCount, NULL))
    {
        printf("IOCTL_VIDEO_QUERY_SUPPORTED_BRIGHTNESS error - %d, -buffer:%d", g_supportedLevelCount, nOutBufferSize);
        exit(1);
    }

    if (g_supportedLevelCount == 0)
    {
        printf("\nLCD not support LEVEL COUNT", g_supportedLevelCount);
        exit(1);
    }

    displayBrightness.ucDisplayPolicy = 0;
    displayBrightness.ucACBrightness = level;
    displayBrightness.ucDCBrightness = level;

    nOutBufferSize = sizeof(displayBrightness);
    if (!DeviceIoControl(hDevice, IOCTL_VIDEO_SET_DISPLAY_BRIGHTNESS, (DISPLAY_BRIGHTNESS*)&displayBrightness, nOutBufferSize, NULL, 0, &nOutBufferSize, NULL))
    {
        printf("IOCTL_VIDEO_SET_SUPPORTED_BRIGHTNESS error - %d, - buffer: %d ", g_supportedLevelCount, nOutBufferSize);
        exit(1);
    }

    Sleep(500); /* delay for some time while wmi event changed */
    nOutBufferSize = sizeof(displayBrightness);
    if (!DeviceIoControl(hDevice, IOCTL_VIDEO_QUERY_DISPLAY_BRIGHTNESS, NULL, 0, (DISPLAY_BRIGHTNESS*)&displayBrightness, nOutBufferSize, &nOutBufferSize, NULL))
    {
        printf("IOCTL_VIDEO_QUERY_SUPPORTED_BRIGHTNESS error - %d, - buffer: %d ", g_supportedLevelCount, nOutBufferSize);
        exit(1);
    }
    printf("\nBrightness_AC: %d\nBrightness_DC: %d", displayBrightness.ucACBrightness, displayBrightness.ucDCBrightness);
}
