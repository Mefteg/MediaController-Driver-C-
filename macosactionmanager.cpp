#include "macosactionmanager.h"

#ifdef Q_OS_MACOS

MacOsActionManager::MacOsActionManager()
{

}

MacOsActionManager::~MacOsActionManager()
{

}


void MacOsActionManager::executeAction(MediaManager::MediaMode mode, MediaManager::MediaAction action)
{
    qDebug("ACTION !");
}

#endif // Q_OS_MACOS
