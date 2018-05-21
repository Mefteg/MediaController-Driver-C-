#ifndef IPERFORMANCEMONITOR_H
#define IPERFORMANCEMONITOR_H

class IPerformanceMonitor
{
public:
    virtual ~IPerformanceMonitor() {}
    virtual float getCPULoad() = 0;
};

#endif // IPERFORMANCEMONITOR_H
