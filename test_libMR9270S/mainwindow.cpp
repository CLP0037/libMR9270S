#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->btn_read->setEnabled(false);
    ui->btn_write->setEnabled(false);
    dev_MR9270S = new LibMR9270S();
    outputtype = 0;
    ui->lineEdit_readout->setEnabled(false);
    ui->lineEdit_writein->setEnabled(false);


    //ui->label_linkstate1->setText("好的");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_connect_clicked()
{
    ui->label_linkstate1->setText("");
    ui->label_outputtype->setText("");
    ui->label_outputstate->setText("");
    bool rtn = dev_MR9270S->dev_connect("COM3", 19200, 'N', 8, 1,2);
    if(rtn)
    {
        ui->label_linkstate1->setText("设备连接成功");//"dev link success"g_C2Q("设备连接成功")
    }
    else
        ui->label_linkstate1->setText("设备连接失败");//"dev link failed"g_C2Q("设备连接失败")
}

void MainWindow::on_btn_disconnect_clicked()
{
    dev_MR9270S->dev_disconnect();
    ui->label_linkstate1->setText("");
    ui->label_outputtype->setText("");
    ui->label_outputstate->setText("");
}

void MainWindow::on_btn_read_clicked()
{
    ui->label_outputstate->setText("");
    float data_value = 0.0f;
    switch(outputtype)
    {
        case 1://mA
        {
             data_value = dev_MR9270S->dev_get_I_output();
        }break;
        case 2://V
        {
            data_value = dev_MR9270S->dev_get_U_output();
        }break;
        case 5://mV
        {
            data_value = dev_MR9270S->dev_get_mV_output();
        }break;
        default:
        {
            return;
        }
    }
    ui->lineEdit_readout->setText(QString::number(data_value,'g',4));
}

void MainWindow::on_btn_write_clicked()
{
    ui->label_outputstate->setText("");
    bool bRTN;
    float data_value = ui->lineEdit_writein->text().trimmed().toFloat();
    if(data_value<=0)
    {
       return;
    }
    switch(outputtype)
    {
        case 1://mA
        {
             bRTN = dev_MR9270S->dev_set_I_output(data_value,1);
        }break;
        case 2://V
        {
            bRTN = dev_MR9270S->dev_set_U_output(data_value,1);
        }break;
        case 5://mV
        {
            bRTN = dev_MR9270S->dev_set_mV_output(data_value,1);
        }break;
        default:
        {
            return;
        }
    }
    if(bRTN)
        ui->label_outputstate->setText("启动输出成功");//g_C2Q("启动输出成功")
    else
        ui->label_outputstate->setText("启动输出失败");//g_C2Q("启动输出失败")
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    outputtype = index;
    switch(index)
    {
    //    case 0:
    //    {

    //    }break;
        case 1://mA
        {
            ui->label_outputtype->setText("电流(mA)输出");//g_C2Q("电流(mA)输出")
            ui->btn_read->setEnabled(true);
            ui->btn_write->setEnabled(true);
            ui->lineEdit_writein->setEnabled(true);
        }break;
        case 2://V
        {
            ui->label_outputtype->setText("电压(V)输出");//g_C2Q("电压(V)输出")
            ui->btn_read->setEnabled(true);
            ui->btn_write->setEnabled(true);
            ui->lineEdit_writein->setEnabled(true);
        }break;
    //    case 3:
    //    {

    //    }break;
    //    case 4:
    //    {

    //    }break;
        case 5://mV
        {
            ui->label_outputtype->setText("毫伏(mV)输出");//g_C2Q("毫伏(mV)输出")
            ui->btn_read->setEnabled(true);
            ui->btn_write->setEnabled(true);
            ui->lineEdit_writein->setEnabled(true);
        }break;
    //    case 6:
    //    {

    //    }break;
    //    case 7:
    //    {

    //    }break;
    //    case 8:
    //    {

    //    }break;
    //    case 9:
    //    {

    //    }break;
        default:
        {
            //暂不支持的输出信号类型
            ui->label_outputtype->setText("暂不支持");//"暂不支持的输出信号类型"
            //ui->label_outputtype->setText(g_C2Q("暂不支持的输出信号类型"));
            ui->btn_read->setEnabled(false);
            ui->btn_write->setEnabled(false);
            ui->lineEdit_writein->setEnabled(false);
            outputtype = 0;
        }break;
    }
}

void MainWindow::on_btn_write_2_clicked()
{
    ui->label_outputstate->setText("");
    bool bRTN;
    float data_value = ui->lineEdit_writein->text().trimmed().toFloat();
    if(data_value<=0)
    {
       return;
    }
    switch(outputtype)
    {
        case 1://mA
        {
             bRTN = dev_MR9270S->dev_set_I_output(data_value,0);
        }break;
        case 2://V
        {
            bRTN = dev_MR9270S->dev_set_U_output(data_value,0);
        }break;
        case 5://mV
        {
            bRTN = dev_MR9270S->dev_set_mV_output(data_value,0);
        }break;
        default:
        {
            return;
        }
    }
    if(bRTN)
        ui->label_outputstate->setText("停止输出成功");//g_C2Q("停止输出成功")
    else
        ui->label_outputstate->setText("停止输出失败");//g_C2Q("停止输出失败")
}

