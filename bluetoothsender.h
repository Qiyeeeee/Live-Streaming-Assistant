#ifndef _BLUETOOTHSENDER_H_
#define _BLUETOOTHSENDER_H_
#include <wiringPi.h>
#include <wiringSerial.h>
#include <iostream>

class BluetoothSender{

public:
  BluetoothSender(const char * port,int baudrate);
  void sendMouseMsg(unsigned char *data,int len=11);
  bool open();
  
private:
  int fd;
  const char *_portname;
  int _baudrate;
};
#endif
