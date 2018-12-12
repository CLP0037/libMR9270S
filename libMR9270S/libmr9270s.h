#ifndef LIBMR9270S_H
#define LIBMR9270S_H

#include "libmr9270s_global.h"

#include <QDebug>
#include "modbus.h"

#define REGISTER_NUM 35

class Q_DECL_EXPORT LibMR9270S : public QObject
//class LIBMR9270SSHARED_EXPORT LibMR9270S
{
    Q_OBJECT
public:
    LibMR9270S();
    ~LibMR9270S();

    /**
     * @brief dev_connect 连接设备===modbus_new_rtu - 生成RTU的连接
     * @param comm 指定OS处理的串行端口的名称，比如 /dev/ttyS0 or /dev/ttyUSB0，
     * 在windows系统上，如果COM编号大于9，必须要在COM前加上\\.\ ，比如 \\\\.\\COM10 http://msdn.microsoft.com/en-us/library/aa365247(v=vs.85).aspx
     * @param baud 连接的波特率
     * @param parity 奇偶检验位  N 无奇偶校验    E 偶数校验    O 奇数校验
     * @param data_bit 数据的位数，允许值有： 5, 6, 7 ,8
     * @param stop_bit 停止位位数，允许值有1和2
     * @param addr modbus从机地址
     * @return
     */
    bool dev_connect(QString comm, int baud, char parity, int data_bit, int stop_bit,int addr);

    void dev_disconnect();

    /**
     * @brief dev_operate_registers  读写寄存器操作
     * @param position  寄存器地址 基准按40001偏移,即position=0对应地址40001
     * @param type 寄存器操作类型：1=读/2=写
     * @param num 读取寄存器个数
     * @param to_sec  延时时间：秒
     * @param to_usec  延时时间：毫秒
     * @return
     */
    bool dev_operate_registers(int position,int type,int num, unsigned int to_sec, unsigned int to_usec);


//    * 输出信号选择
//    * =0电流输出，
//    * =1电压输出，
//    * =2无源输出，
//    * =3频率输出，
//    * =4毫伏输出，
//    * =5电热阻输出，
//    * =6为24V输出

    //设置电流输出(mA)
    /**
     * @brief dev_set_I_output
     * @param value  输出值设置
     * @param type  输出类型：1-启动输出，0-停止输出
     * @return
     */
    bool dev_set_I_output(float value,int type);

    //设置电压输出(V)
    bool dev_set_U_output(float value,int type);

    //设置毫伏输出(mV)
    bool dev_set_mV_output(float value,int type);

    //获取电流输出(mA)
    float dev_get_I_output();

    //获取电压输出(V)
    float dev_get_U_output();

    //获取毫伏输出(mV)
    float dev_get_mV_output();

    //bool dev_outputsignal_select(int position,int type,unsigned int to_sec, unsigned int to_usec);

    char* str2charx(QString temp_str);

    //
    modbus_t *mb_MR9270S;

    unsigned short sMR9270S_Data[REGISTER_NUM];
//    typedef struct{
//        unsigned short
//    }_sMR9270S;

};

#endif // LIBMR9270S_H
