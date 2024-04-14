#include "MotionSensor.h"
#include <iostream>
#include <pigpio.h>

#define MPU_INT_PIN 17

#define wrap_180(x) (x < -180 ? x+360 : (x > 180 ? x - 360: x))
#define delay_ms(a)    usleep(a*1000)

MotionSensor::MotionSensor()
{
	if (gpioInitialise() < 0) {
		std::cerr << "pigpio initialization failed." << std::endl;
	}
}
// MotionSensor destructor
MotionSensor::~MotionSensor() {
	gpioTerminate();
}

int MotionSensor::ms_open() 
{
	dmpReady=1;
	initialized = 0;
	for (int i=0;i<DIM;i++)
  {
		lastval[i]=10;
	}

	// initialize device
	printf("Initializing the MPU... Please wait.\n");
	if (mpu_init(NULL) != 0) {
		printf("MPU initialization failure.\n");
		return -1;
	}
	printf("MPU initialization is successful..");

	printf("Setting up the MPU sensor... Please wait.\n");
    dump_init();
	if (mpu_set_sensors(INV_XYZ_GYRO|INV_XYZ_ACCEL)!=0) {
		printf("MPU sensor setting failure.\n");
		return -1;
	}
	printf("MPU Sensor Setting Successful.\n");

	printf("Setting gyro sensitivity... Please wait.\n");
	if (mpu_set_gyro_fsr(2000)!=0) {
		printf("Failed to set gyro accuracy.\n");
		return -1;
	}
	printf("Gyroscope accuracy set successfully.\n");

	printf("Setting accelerometer sensitivity... Please wait.\n");
	if (mpu_set_accel_fsr(2)!=0) {
		printf("Accelerometer sensitivity setting failed.\n");
		return -1;
	}
	printf("Accelerometer sensitivity set successfully.\n");

	// verify connection
	printf("Execute the MPU boot command... Please wait.\n");
	mpu_get_power_state(&devStatus);
	printf(devStatus ? "MPU6050 Connection Successful.\n" : "MPU6050 Connection Failure. %u\n",devStatus);

	//fifo config
	printf("Setting the MPU FIFO... Please wait\n");
	if (mpu_configure_fifo(INV_XYZ_GYRO|INV_XYZ_ACCEL)!=0) {
		printf("MPU fifo 设置失败.\n");
		return -1;
	}
	printf("MPU fifo set successfully.\n");


	// load and configure the DMP
	printf("Reading DMP firmware... Please wait.\n");
	if (dmp_load_motion_driver_firmware()!=0) {
		printf("DMP firmware open failure.\n");
		return -1;
	}
	printf("DMP firmware opened successfully.\n");


	printf("Activating DMP... Please wait.\n");
	if (mpu_set_dmp_state(1)!=0) {
		printf("DMP激活失败.\n");
		return -1;
	}
	printf("DMP activation successful.\n");

	//dmp_set_orientation()
	//if (dmp_enable_feature(DMP_FEATURE_LP_QUAT|DMP_FEATURE_SEND_RAW_GYRO)!=0) {
	printf("Setting the DMP... Please wait.\n");
	if (dmp_enable_feature(DMP_FEATURE_6X_LP_QUAT|DMP_FEATURE_SEND_RAW_ACCEL|DMP_FEATURE_SEND_CAL_GYRO|DMP_FEATURE_GYRO_CAL)!=0) {
		printf("DMP feature extraction failed.\n");
		return -1;
	}
	printf("DMP feature extraction successful.\n");

	printf("Setting the DMP FIFO sample rate... Please wait\n");
	if (dmp_set_fifo_rate(rate)!=0) {
		printf("DMP FIFO Sample Rate Setting Failure.\n");
		return -1;
	}
	printf("DMP FIFO Sample Rate Setting Successful.\n");


	printf("Reset FIFO message queue... Please wait\n");
	if (mpu_reset_fifo()!=0) {
		printf("FIFO message queue reset failure.\n");
		return -1;
	}
	printf("FIFO message queue reset successful.\n");

	printf("under test... ");
	do {
		delay_ms(1000/rate);  //dmp will habve 4 (5-1) packets based on the fifo_rate
		r=dmp_read_fifo(g,a,_q,&sensors,&fifoCount);
	} while (r!=0 || fifoCount<5); //packtets!!!
	printf("fulfillment.\n");

	initialized = 1;
	// Set GPIO mode and interrupts
	gpioSetMode(MPU_INT_PIN, PI_INPUT);// Set GPIOs as inputs
	gpioSetPullUpDown(MPU_INT_PIN, PI_PUD_DOWN);// Setting up internal dropdowns
	gpioSetISRFuncEx(MPU_INT_PIN, RISING_EDGE, 0, interruptHandler, this);// Register the interrupt handler
	return 0;
}

void interruptHandler(int gpio, int level, uint32_t tick, void* user) {
	MotionSensor* sensor = reinterpret_cast<MotionSensor*>(user);
	sensor->ms_update();
}

int MotionSensor::ms_update() 
{
	if (!dmpReady) {
		printf("Error: DMP not ready.\n");
		return -1;
	}

	if (dmp_read_fifo(g, a, _q, &sensors, &fifoCount) == 0) {
		q = _q;
		GetGravity(&gravity, &q);
		GetYawPitchRoll(ypr, &q, &gravity);

		mpu_get_temperature(&t);
		temp = (float)t / 65536L;

		mpu_get_compass_reg(c);

		//scaling for degrees output
		for (int i = 0; i < DIM; i++) {
			ypr[i] *= 180 / M_PI;
		}

		//unwrap yaw when it reaches 180
		ypr[0] = wrap_180(ypr[0]);

		//change sign of Pitch, MPU is attached upside down
		ypr[1] *= -1.0;

		//0=gyroX, 1=gyroY, 2=gyroZ
		//swapped to match Yaw,Pitch,Roll
		//Scaled from deg/s to get tr/s
		for (int i = 0; i < DIM; i++) {
			gyro[i] = (float)(g[DIM - i - 1]) / 131.0 / 360.0;
			accel[i] = (float)(a[DIM - i - 1]);
			compass[i] = (float)(c[DIM - i - 1]);
		}
	}else {
		// Log or handle error
		std::cerr << "Failed to read FIFO data." << std::endl;
	}
	
	return 0;
}

int MotionSensor::ms_close() 
{
	return 0;
}

uint8_t MotionSensor::GetGravity(VectorFloat *v, Quaternion *q) 
{
	v -> x = 2 * (q -> x*q -> z - q -> w*q -> y);
	v -> y = 2 * (q -> w*q -> x + q -> y*q -> z);
	v -> z = q -> w*q -> w - q -> x*q -> x - q -> y*q -> y + q -> z*q -> z;
	return 0;
}

uint8_t MotionSensor::GetYawPitchRoll(float *data, Quaternion *q, VectorFloat *gravity) 
{
	// yaw: (about Z axis)
	data[0] = atan2(2*q -> x*q -> y - 2*q -> w*q -> z, 2*q -> w*q -> w + 2*q -> x*q -> x - 1);
	// pitch: (nose up/down, about Y axis)
	data[1] = atan(gravity -> x / sqrt(gravity -> y*gravity -> y + gravity -> z*gravity -> z));
	// roll: (tilt left/right, about X axis)
	data[2] = atan(gravity -> y / sqrt(gravity -> x*gravity -> x + gravity -> z*gravity -> z));
	return 0;
}

