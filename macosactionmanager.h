#include <QtGlobal>

#ifdef Q_OS_MACOS

#ifndef MACOSACTIONMANAGER_H
#define MACOSACTIONMANAGER_H

#include "iactionmanager.h"

class MacOsActionManager : public IActionManager
{
public:
    MacOsActionManager();
    ~MacOsActionManager() override;

    void executeAction(MediaManager::MediaMode mode, MediaManager::MediaAction action) override;
};

#endif // MACOSACTIONMANAGER_H

#endif // Q_OS_MACOS
