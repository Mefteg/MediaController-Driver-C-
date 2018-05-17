#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>

#include "mediamanager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void openSerialPort();
    void closeSerialPort();
    void readData();

private:
    void writeData(const QByteArray &data);

private:
    MediaManager m_mediaManager;

    Ui::MainWindow *m_ui;
    QSerialPort *m_serial;
};

#endif // MAINWINDOW_H
