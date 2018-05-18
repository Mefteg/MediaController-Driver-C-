#ifndef IPERFORMANCEMONITOR_H
#define IPERFORMANCEMONITOR_H

class IPerformanceMonitor
{
public:
    virtual float getCPULoad() const = 0;
};

#endif // IPERFORMANCEMONITOR_H
