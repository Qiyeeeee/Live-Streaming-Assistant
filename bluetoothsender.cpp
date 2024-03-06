#include "bluetoothsender.h"

BluetoothSender::BluetoothSender(const char * port,int baudrate)
{
   _portname=port;
   _baudrate=baudrate;
}

void BluetoothSender::sendMouseMsg(unsigned char *data,int len)
{
  unsigned char sum=0x00;
  for(int i=0;i<len;i++)
  {
    sum+=data[i];
    if(i<len-1)
      serialPutchar(fd,data[i]);
    else
      serialPutchar(fd,sum);
  }
}

bool BluetoothSender::open()
{
    if ((fd = serialOpen(_portname, _baudrate)) < 0) //初始化串口并获取文件描述符保存到fd变量里
    {
       std::cout<<"Unable to open serial device"<<std::endl;
       return false;
    }
    return true;
}