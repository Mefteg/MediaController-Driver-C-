#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSerialPortInfo>
#include <QKeyEvent>

#include "windowsactionmanager.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_ui(new Ui::MainWindow)
    , m_serial(nullptr)
{
    m_ui->setupUi(this);
    m_serial = new QSerialPort();

    // Connect serial events.
    connect(m_serial, &QSerialPort::readyRead, this, &MainWindow::readData);

    // List serial port.
    QList<QSerialPortInfo> serialPorts = QSerialPortInfo::availablePorts();
    foreach (QSerialPortInfo serialPort, serialPorts) {
        qDebug("---");
        qDebug(serialPort.description().toStdString().c_str());
        qDebug(serialPort.portName().toStdString().c_str());
        qDebug(serialPort.serialNumber().toStdString().c_str());
    }

    // TODO : Add UI to do that.
    // Open serial port COM4 (hardcoded)
    openSerialPort();
}

MainWindow::~MainWindow()
{
    if (m_serial != nullptr)
    {
        closeSerialPort();
        delete m_serial;
    }

    delete m_ui;
}

void MainWindow::openSerialPort()
{
    m_serial->setPortName("COM4");
    m_serial->setBaudRate(QSerialPort::Baud9600);
    if (m_serial->open(QIODevice::ReadWrite))
    {
        qDebug("Connection opened successfully !");
    }
    else
    {
        qDebug("Error while trying to open a connection...");
    }
}

void MainWindow::closeSerialPort()
{
    if (m_serial->isOpen())
    {
        m_serial->close();
        qDebug("Connection closed.");
    }
}

void MainWindow::readData()
{
    const QByteArray data = m_serial->readAll();
    qDebug(data.toStdString().c_str());

    m_mediaManager.handleData(data);
}

void MainWindow::writeData(const QByteArray &data)
{
    if (m_serial != nullptr && m_serial->isOpen() == true)
    {
        m_serial->write(data);
    }
}
