#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include "../libMR9270S/libmr9270s.h"

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

#define g_C2Q(str) QString::fromLocal8Bit(str)
#define g_Q2C(qs)  (const char*)(qs).toLocal8Bit()

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
    void on_btn_connect_clicked();

    void on_btn_disconnect_clicked();

    void on_btn_read_clicked();

    void on_btn_write_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_btn_write_2_clicked();


private:
    Ui::MainWindow *ui;
    LibMR9270S *dev_MR9270S;
    int outputtype ;

    void comm_int();
};

#endif // MAINWINDOW_H
