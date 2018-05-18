#include "windowsperformancemonitor.h"

#ifdef Q_OS_WIN

WindowsPerformanceMonitor::WindowsPerformanceMonitor()
    : _previousTotalTicks(0)
    , _previousIdleTicks(0)
{

}

float WindowsPerformanceMonitor::getCPULoad()
{
    FILETIME idleTime, kernelTime, userTime;
    return GetSystemTimes(&idleTime, &kernelTime, &userTime) ? CalculateCPULoad(FileTimeToInt64(idleTime), FileTimeToInt64(kernelTime)+FileTimeToInt64(userTime)) : -1.0f;
}

float WindowsPerformanceMonitor::CalculateCPULoad(quint64 idleTicks, quint64 totalTicks)
{
   quint64 totalTicksSinceLastTime = totalTicks - _previousTotalTicks;
   quint64 idleTicksSinceLastTime  = idleTicks - _previousIdleTicks;

   float ret = 1.0f - ((totalTicksSinceLastTime > 0) ? ((float)idleTicksSinceLastTime) / totalTicksSinceLastTime : 0);

   _previousTotalTicks = totalTicks;
   _previousIdleTicks  = idleTicks;

   return ret;
}

quint64 WindowsPerformanceMonitor::FileTimeToInt64(const FILETIME & ft)
{
    return (((quint64)(ft.dwHighDateTime))<<32)|((quint64)ft.dwLowDateTime);
}

#endif //Q_OS_WIN
