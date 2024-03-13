#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <wiringPi.h>
#include "MotionSensor.h"
#include "bluetoothsender.h"
#include <iostream>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/bind.hpp>


#define delay_ms(a) usleep(a*1000)
#define LEFT_BTN_PIN 7
#define RIGHT_BTN_PIN 4
#define DEATH 10

MotionSensor mpu6050;
BluetoothSender bt("/dev/ttyUSB0", 115200);

void timer_handle(const boost::system::error_code &error_code,
	              boost::asio::deadline_timer *timer, int *count)
{
    unsigned char mouse_msg[11]={0x57,0xab,0x00,0x05,0x05,0x01,0x00,0x00,0x00,0x00,0x00};
		mpu6050.ms_update();
    if(mpu6050.ypr[YAW]< -1*DEATH)
    {
      mouse_msg[7]=0x00+std::abs(mpu6050.ypr[YAW]-DEATH);
    }
    else if(mpu6050.ypr[YAW] > DEATH)
    {
      mouse_msg[7]=0xff-std::abs(mpu6050.ypr[YAW]-DEATH); 
    }
    if(mpu6050.ypr[ROLL] < -1*DEATH)
    {
      mouse_msg[8]=0xff-std::abs(mpu6050.ypr[ROLL]-DEATH);
    }
    else if(mpu6050.ypr[ROLL] > DEATH)
    {
      mouse_msg[8]=0x00+std::abs(mpu6050.ypr[ROLL]-DEATH); 
    }
    mouse_msg[6]=mouse_msg[6] | digitalRead(LEFT_BTN_PIN);
    mouse_msg[6]=mouse_msg[6] | (digitalRead(RIGHT_BTN_PIN)<<1);
    bt.sendMouseMsg(mouse_msg);
        
		timer->expires_at(timer->expires_at() + boost::posix_time::milliseconds(10));
		timer->async_wait(boost::bind(timer_handle, boost::asio::placeholders::error, timer, count));
}

void initMouseBtn()
{
    pinMode(0,OUTPUT);
    pinMode(2,OUTPUT);
    pinMode(5,OUTPUT);
    digitalWrite(0,0);
    digitalWrite(2,1);
    digitalWrite(5,1);
    pinMode(LEFT_BTN_PIN,INPUT);
    pinMode(RIGHT_BTN_PIN,INPUT);
}

int main(int argc,char** argv) 
{ 
    int i=0;
    int count=0;
    boost::asio::io_service ioService;
    boost::asio::deadline_timer timer(ioService, boost::posix_time::milliseconds(10));
    // 注册定时器回调函数
	  timer.async_wait(boost::bind(timer_handle, boost::asio::placeholders::error, &timer, &count));
    wiringPiSetup();
    initMouseBtn();
    //初始化mpu6050的dmp
	  mpu6050.ms_open();
    if(!bt.open())
    {
       return 1;
    }
 	  while(i<1000)
    {
    		mpu6050.ms_update();
        printf("初始校准中 yaw = %2.1f\tpitch = %2.1f\troll = %2.1f\t\r",mpu6050.ypr[YAW], mpu6050.ypr[PITCH], mpu6050.ypr[ROLL]);
        i++;
    }
    printf("\n初始化完成,任意输入退出\n");
    // 运行IO服务，处理事件
    ioService.run();
    system("pause");
	  return 0;
}
