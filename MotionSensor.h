#ifndef _MOTION_SENSOR_H_
#define _MOTION_SENSOR_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#include "helper_3dmath.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"

#define YAW 0
#define PITCH 1
#define ROLL 2
#define DIM 3

class MotionSensor
{

 public:
    MotionSensor();
    int ms_open();
    int ms_update();
    int ms_close();
    
    float ypr[3]; //yaw, pitch, roll
    float accel[3];
    float gyro[3];
    float temp;
    float compass[3];
    
    
 private:
    uint8_t GetGravity(VectorFloat *v, Quaternion *q);
    uint8_t GetYawPitchRoll(float *data, Quaternion *q, VectorFloat *gravity); 
    uint8_t GetGyro(int32_t *data, const uint8_t* packet);
     // MPU control/status vars
    uint8_t devStatus;      // return status after each device operation
    //(0 = success, !0 = error)
    uint8_t fifoCount;     // count of all bytes currently in FIFO
    uint8_t fifoBuffer[64]; // FIFO storage buffer
    
    int16_t a[3];              // [x, y, z]            accel vector
    int16_t g[3];              // [x, y, z]            gyro vector
    int32_t _q[4];
    int32_t t;
    int16_t c[3];
    
    VectorFloat gravity;    // [x, y, z]            gravity vector
    
    int r;
    int initialized = 0;
    int dmpReady = 0;
    float lastval[3];
    int16_t sensors;
    Quaternion q; 
    uint8_t rate = 100;
};
#endif
