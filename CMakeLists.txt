cmake_minimum_required(VERSION 3.17)
project(monitorBrightnessControl)

set(CMAKE_CXX_STANDARD 14)

add_executable(monitorBrightnessControl main.cpp Monitors/laptopMonitor.h Monitors/laptopMonitor.cpp Monitors/desktopMonitor.h Monitors/desktopMonitor.cpp Monitors/DDCCI.h Monitors/DDCCI.cpp)