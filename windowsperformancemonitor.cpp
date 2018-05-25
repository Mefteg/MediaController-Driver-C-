#include "windowsperformancemonitor.h"

#ifdef Q_OS_WIN

#include <Psapi.h>
#include <QString>

WindowsPerformanceMonitor::WindowsPerformanceMonitor()
    : _previousTotalTicks(0)
    , _previousIdleTicks(0)
{

}

WindowsPerformanceMonitor::~WindowsPerformanceMonitor()
{

}

float WindowsPerformanceMonitor::getCPULoad()
{
    DWORD aProcesses[1024], cbNeeded, cProcesses;
    unsigned int i;

    if (EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded) == false)
    {
        return -1.0f;
    }


    // Calculate how many process identifiers were returned.
    cProcesses = cbNeeded / sizeof(DWORD);

    // Print the name and process identifier for each process.
    for (i = 0; i < cProcesses; i++)
    {
        if(aProcesses[i] != 0)
        {
            PrintProcessNameAndID(aProcesses[i]);
        }
    }

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


void WindowsPerformanceMonitor::PrintProcessNameAndID( DWORD processID )
{
    TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");

    // Get a handle to the process.

    HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION |
                                   PROCESS_VM_READ,
                                   FALSE, processID );

    // Get the process name.

    if (NULL != hProcess )
    {
        HMODULE hMod;
        DWORD cbNeeded;

        if ( EnumProcessModules( hProcess, &hMod, sizeof(hMod),
                                 &cbNeeded) )
        {
            GetModuleBaseName( hProcess, hMod, szProcessName,
                               sizeof(szProcessName)/sizeof(TCHAR) );
        }
    }

    char processName[MAX_PATH];
    wcstombs(processName, szProcessName, MAX_PATH);

    // Print the process name and identifier.
    qDebug("%s  (PID: %u)\n", processName, processID);

    // Release the handle to the process.

    CloseHandle( hProcess );
}

#endif //Q_OS_WIN
