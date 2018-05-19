#ifndef WINDOWSACTIONMANAGER_H
#define WINDOWSACTIONMANAGER_H

#include <QtGlobal>

#ifdef Q_OS_WIN
#include "iactionmanager.h"

class WindowsActionManager : public IActionManager
{
public:
    WindowsActionManager();

    void executeAction(MediaManager::MediaMode mode, MediaManager::MediaAction action) override;

private:
    int actionToWindowsKey(MediaManager::MediaMode mode, MediaManager::MediaAction action);
    void executeKey_Windows(int virtualKeyCode);
};

#endif //Q_OS_WIN
#endif // WINDOWSACTIONMANAGER_H
