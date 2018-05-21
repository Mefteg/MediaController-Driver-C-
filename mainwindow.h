#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>
#include <QListView>
#include <QPushButton>

#include <QSerialPort>

#include <QTimer>

#include "mediamanager.h"
#include "iperformancemonitor.h"

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
    void performanceMonitorTimeOut();

private:
    void writeData(const QByteArray &data);

private:

    Ui::MainWindow *m_ui;
    QStringListModel *m_model;
    QListView *m_serialPortList;
    QPushButton *m_connectButton;

    QSerialPort *m_serial;

    QTimer performanceMonitorTimer;

    MediaManager m_mediaManager;
    IPerformanceMonitor *m_performanceMonitor;
};

#endif // MAINWINDOW_H
