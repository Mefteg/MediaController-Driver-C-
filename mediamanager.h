#ifndef MEDIAMANAGER_H
#define MEDIAMANAGER_H

#include <QByteArray>

class IActionManager;

class MediaManager
{
public:
    enum MediaMode
    {
        PLAYER, VOLUME, MediaMode_COUNT
    };

    enum MediaAction
    {
        PREVIOUS, PLAY, NEXT
    };

    MediaManager();
    virtual ~MediaManager();

    void handleData(const QByteArray& data);

private:
    MediaMode getNextMode(MediaMode mode);

private:
    MediaMode m_mode;
    IActionManager* m_actionManager;
};

#endif // MEDIAMANAGER_H
