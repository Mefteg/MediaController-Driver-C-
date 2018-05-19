#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>
#include <QListView>
#include <QPushButton>

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
    void handleConnectButton();

    void openSerialPort();
    void closeSerialPort();
    void readData();

private:
    void writeData(const QByteArray &data);

private:

    Ui::MainWindow *m_ui;
    QStringListModel *m_model;
    QListView *m_serialPortList;
    QPushButton *m_connectButton;

    QSerialPort *m_serial;

    MediaManager m_mediaManager;
};

#endif // MAINWINDOW_H
