#include "windowsactionmanager.h"

#ifdef Q_OS_WIN

#include <Windows.h>

WindowsActionManager::WindowsActionManager()
{

}

void WindowsActionManager::executeAction(MediaManager::MediaMode mode, MediaManager::MediaAction action)
{
    executeKey_Windows(actionToWindowsKey(mode, action));
}

int WindowsActionManager::actionToWindowsKey(MediaManager::MediaMode mode, MediaManager::MediaAction action)
{
    switch (action) {
    case MediaManager::MediaAction::PREVIOUS:
        return mode == MediaManager::MediaMode::PLAYER ? VK_MEDIA_PREV_TRACK : VK_VOLUME_DOWN;
    case MediaManager::MediaAction::PLAY:
        return mode == MediaManager::MediaMode::PLAYER ? VK_MEDIA_PLAY_PAUSE : VK_VOLUME_MUTE;
    case MediaManager::MediaAction::NEXT:
        return mode == MediaManager::MediaMode::PLAYER ? VK_MEDIA_NEXT_TRACK : VK_VOLUME_UP;
    default:
        return mode == MediaManager::MediaMode::PLAYER ? VK_MEDIA_PLAY_PAUSE : VK_VOLUME_MUTE;
    }
}

void WindowsActionManager::executeKey_Windows(int virtualKeyCode)
{
    // This structure will be used to create the keyboard
    // input event.
    INPUT ip;

    // Set up a generic keyboard event.
    ip.type = INPUT_KEYBOARD;
    ip.ki.wScan = 0; // hardware scan code for key
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;

    ip.ki.wVk = virtualKeyCode;
    ip.ki.dwFlags = 0; // 0 for key press
    SendInput(1, &ip, sizeof(INPUT));

    // Release the "A" key
    ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
    SendInput(1, &ip, sizeof(INPUT));
}
#endif //Q_OS_WIN
