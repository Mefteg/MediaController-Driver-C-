#include "mediamanager.h"

#ifdef Q_OS_WIN
#include "windowsactionmanager.h"
#endif //Q_OS_WIN

#ifdef Q_OS_MACOS
#include "macosactionmanager.h"
#endif //Q_OS_MACOS

MediaManager::MediaManager()
    : m_mode(MediaMode::PLAYER)
    , m_actionManager(nullptr)
{
#ifdef Q_OS_WIN
    m_actionManager = new WindowsActionManager();
#endif //Q_OS_WIN
#ifdef Q_OS_MACOS
    m_actionManager = new MacOsActionManager();
#endif //Q_OS_MACOS
#ifdef Q_OS_LINUX
    qDebug("No action manager for Linux. Inexpected behaviours could occur.");
#endif //Q_OS_LINUX
}

MediaManager::~MediaManager()
{
    delete m_actionManager;
}

void MediaManager::handleData(const QByteArray& data)
{
    std::string message = data.toStdString();

    if (message.compare("MODE\r\n") == 0)
    {
        m_mode = getNextMode(m_mode);
    }
    else
    {
        MediaAction action = MediaAction::PLAY;
        if (message.compare("PREVIOUS\r\n") == 0)
        {
            action = MediaAction::PREVIOUS;
        }
        else if (message.compare("PLAY\r\n") == 0)
        {
            action = MediaAction::PLAY;
        }
        else if (message.compare("NEXT\r\n") == 0)
        {
            action = MediaAction::NEXT;
        }

        m_actionManager->executeAction(m_mode, action);
    }
}

MediaManager::MediaMode MediaManager::getNextMode(MediaMode mode)
{
    return (MediaMode)((mode + 1) % MediaMode::MediaMode_COUNT);
}
