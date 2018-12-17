#include "libmr9270s.h"


LibMR9270S::LibMR9270S()
{
    //mb_MR9270S = new modbus_t();
    mb_MR9270S = NULL;
}

LibMR9270S::~LibMR9270S()
{
    delete mb_MR9270S;
}

bool LibMR9270S::dev_connect(QString comm, int baud, char parity, int data_bit, int stop_bit,int addr)
{
    int rtn;
    char* portname;
    QByteArray temp_ba = comm.trimmed().toLatin1();
    portname = temp_ba.data();
    //portname = str2charx(comm);
    mb_MR9270S = modbus_new_rtu(portname,baud,parity,data_bit,stop_bit);//portname   parity
    //mb_MR9270S = modbus_new_rtu("COM3", 19200, 'N', 8, 1);
    if (mb_MR9270S == NULL)
    {
        //fprintf(stderr, "Unable to allocate libmodbus context\n");
        return false;
    }

    rtn = modbus_set_slave(mb_MR9270S, addr);  //设置modbus从机地址
     if(rtn == -1)
     {
         qDebug()<<QString("modbus_set_slave errno : %1;error info : %2").arg(errno).arg(modbus_strerror(errno));
         mb_MR9270S = NULL;
         return false;
     }

    rtn = modbus_connect(mb_MR9270S);
     if(rtn == -1)
     {
         qDebug()<<QString("modbus_connect errno : %1;error info : %2").arg(errno).arg(modbus_strerror(errno));
         mb_MR9270S = NULL;
         return false;
     }

    return true;
}

void LibMR9270S::dev_disconnect()
{
    if(mb_MR9270S == NULL)
    {
        return;
    }
    modbus_close(mb_MR9270S);
    modbus_free(mb_MR9270S);
}

bool LibMR9270S::dev_operate_registers(int position,int type,int num, unsigned int to_sec, unsigned int to_usec)
{
    uint16_t tab_reg[100]={0};
    int rtn;
    int regs;//读写寄存器个数

    //设置modbus超时时间

//    #ifdef Q_OS_WIN32 //Windows操作系统
//    {
//        struct timeval t;
//          t.tv_sec=to_sec;
//          t.tv_usec=to_usec;        //set modbus time
//          modbus_set_response_timeout(mb_MR9270S,&t);

//    }
//    #else
//    {
//        rtn = modbus_set_response_timeout(mb_MR9270S, to_sec,to_usec);
//        if(rtn == -1)
//        {
//           qDebug()<<QString("modbus_set_response_timeout errno : %1;error info : %2").arg(errno).arg(modbus_strerror(errno));
//           return false;
//        }
//    }
//    #endif

    rtn = modbus_set_response_timeout(mb_MR9270S, to_sec,to_usec);
    if(rtn == -1)
    {
       qDebug()<<QString("modbus_set_response_timeout errno : %1;error info : %2").arg(errno).arg(modbus_strerror(errno));
       return false;
    }

    switch(type)
    {
        case 1://读
        {
            //int modbus_read_registers(modbus_t *ctx, int addr, int nb, uint16_t *dest);
            regs = modbus_read_registers(mb_MR9270S, position, num, tab_reg);
            if(regs < 0)
            {
                qDebug()<<QString("modbus_read_registers errno : %1;error info : %2").arg(errno).arg(modbus_strerror(errno));
                return false;
            }
            int i;
            for (i=0; i < regs; i++) {
                qDebug()<<QString("reg[%1]=%2 (0x%3)").arg(i).arg(tab_reg[i]).arg(QString::number(tab_reg[i],16));
                sMR9270S_Data[i] = tab_reg[i];
            }
        }break;
        case 2://写
        {
            //int modbus_write_register(modbus_t *ctx, int reg_addr, int value)
            //输出信号选择
            regs = modbus_write_register(mb_MR9270S,8,sMR9270S_Data[8]);
            if(regs < 0)
            {
                qDebug()<<QString("modbus_write_register_8 errno : %1;error info : %2").arg(errno).arg(modbus_strerror(errno));
                return false;
            }
            //输出信号设定值
            regs = modbus_write_register(mb_MR9270S,17,sMR9270S_Data[17]);
            if(regs < 0)
            {
                qDebug()<<QString("modbus_write_register_17 errno : %1;error info : %2").arg(errno).arg(modbus_strerror(errno));
                return false;
            }
            //输出信号开关
            regs = modbus_write_register(mb_MR9270S,11,sMR9270S_Data[11]);
            if(regs < 0)
            {
                qDebug()<<QString("modbus_write_register_11 errno : %1;error info : %2").arg(errno).arg(modbus_strerror(errno));
                return false;
            }

            //int modbus_write_registers(modbus_t *ctx, int addr, int nb, const uint16_t *data);
            //regs = modbus_write_registers(mb_MR9270S, position, num, (uint16_t *)sMR9270S_Data);
            //if(regs < 0)
            //{
            //    qDebug()<<QString("modbus_write_registers errno : %1;error info : %2").arg(errno).arg(modbus_strerror(errno));
            //    return false;
            //}

        }break;
    }




    return true;
}

//设置电流输出(mA)
bool LibMR9270S::dev_set_I_output(float value,int type)
{
    int data_set = (int)(value * 1000);

    sMR9270S_Data[8] = 0;
    sMR9270S_Data[11] = type;
    sMR9270S_Data[17] = data_set;
    return dev_operate_registers(0,2,35, 2, 0);
}

//设置电压输出(V)
bool LibMR9270S::dev_set_U_output(float value,int type)
{
    int data_set = (int)(value * 1000);

    sMR9270S_Data[8] = 1;
    sMR9270S_Data[11] = type;
    sMR9270S_Data[17] = data_set;
    return dev_operate_registers(0,2,35, 2, 0);
}

//设置毫伏输出(mV)
bool LibMR9270S::dev_set_mV_output(float value,int type)
{
    int data_set = (int)(value * 100);

    sMR9270S_Data[8] = 4;
    sMR9270S_Data[11] = type;
    sMR9270S_Data[17] = data_set;
    return dev_operate_registers(0,2,35, 2, 0);
}

//获取电流输出(mA)
float LibMR9270S::dev_get_I_output()
{
    float value = 0.0f;
    if(dev_operate_registers(0,1,35, 2, 0))
    {
        value = sMR9270S_Data[17] * 0.001f;
    }
    return value;
}

//获取电压输出(V)
float LibMR9270S::dev_get_U_output()
{
    float value = 0.0f;
    if(dev_operate_registers(0,1,35, 2, 0))
    {
        value = sMR9270S_Data[17] * 0.001f;
    }
    return value;
}

//获取毫伏输出(mV)
float LibMR9270S::dev_get_mV_output()
{
    float value = 0.0f;
    if(dev_operate_registers(0,1,35, 2, 0))
    {
        value = sMR9270S_Data[17] * 0.01f;
    }
    return value;
}


char* LibMR9270S::str2charx(QString temp_str)
{
    QByteArray temp_ba = temp_str.trimmed().toLatin1();
    char* temp_charx = temp_ba.data();
    return temp_charx;
}



