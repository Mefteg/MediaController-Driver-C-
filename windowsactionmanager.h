#include <QtGlobal>

#ifdef Q_OS_WIN
#ifndef WINDOWSACTIONMANAGER_H
#define WINDOWSACTIONMANAGER_H

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

#endif // WINDOWSACTIONMANAGER_H
#endif //Q_OS_WIN
