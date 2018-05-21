#include <QtGlobal>

#ifndef WINDOWSPERFORMANCEMONITOR_H
#define WINDOWSPERFORMANCEMONITOR_H

#include "iperformancemonitor.h"

#include <Windows.h>

class WindowsPerformanceMonitor : public IPerformanceMonitor
{
public:
    WindowsPerformanceMonitor();
    virtual ~WindowsPerformanceMonitor() override;

    float getCPULoad() override;

private:
    float CalculateCPULoad(quint64 idleTicks, quint64 totalTicks);
    quint64 FileTimeToInt64(const FILETIME & ft);

    quint64 _previousTotalTicks;
    quint64 _previousIdleTicks;
};

#endif // WINDOWSPERFORMANCEMONITOR_H
