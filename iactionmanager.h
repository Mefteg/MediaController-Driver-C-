#ifndef IACTIONMANAGER_H
#define IACTIONMANAGER_H

#include "mediamanager.h"

class IActionManager
{
public:
    virtual ~IActionManager() {}
    virtual void executeAction(MediaManager::MediaMode mode, MediaManager::MediaAction action) = 0;
};

#endif // IACTIONMANAGER_H
