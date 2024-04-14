# Project Version Update
## Version 2.0
Replaced WiringPi with Pigpio, and now the mouse has sensitivity adjustment.

## Version 1.0
Performance and responsiveness have been further improved and optimised by changing the way sensor data is processed (event interrupt).

## Version 0.9
Initial version, basic mouse functionality is already available.

****

# Live-Streaming-Assistant

## Project Introduction:
With the growth of the internet industry, the live broadcasting sector has expanded rapidly. Traditional mice, which require a desktop environment, are no longer sufficient for all scenarios in the life of a live streamer. For example, outdoor broadcasters or performing artists often face the challenge of not being able to rely on a fixed desktop surface while performing. To address this issue, we have developed a gesture-controlled mouse that allows broadcasters to freely control their live stream in any setting without being limited by a desktop surface.

### Project Members
| Name | Email | Contribution | GitHub |
|----------|----------|----------|----------|
| Jianhua Dong |2938631D@student.gla.ac.uk | Row1Col3 |[ yokinoh](https://github.com/yokinoh) |
| Ao Liu | 2858676L@student.gla.ac.uk | Row2Col3 | [trashcanbomb](https://github.com/trashcanbomb) |
| Lixun Ma | 2929238M@student.gla.ac.uk | Row3Col3 | [Matteo](https://github.com/Matteolx98) |
| Lincheng Li | 2510846L@student.gla.ac.uk | Row4Col3 | Row4Col4 |
| Zixiang Chang | 2808158C@student.gla.ac.uk | Row5Col3 | [Qiyeeeee](https://github.com/Qiyeeeee) |


### Key Features
1. No Desktop Constraints: This mouse utilizes advanced sensor technology to operate on any surface or even in mid-air, greatly enhancing flexibility in use, particularly suited for outdoor broadcasters and performing artists who operate without a fixed work surface.
2. High Portability and Wireless Connectivity: Designed to be lightweight and easy to carry, it supports wireless connectivity and a built-in Bluetooth module, offering greater freedom of movement. This allows the broadcaster to maintain smooth live streaming operations on the go without the limitations of traditional wired connections.
3. Compatibility and Customizability: This mouse is not only compatible with various operating systems and live streaming software but also allows users to make extensive settings adjustments based on personal habits and specific needs. This flexibility ensures that the mouse can adapt to various live broadcasting scenarios and the particular demands of users. The mouse is plug-and-play.

### Technical Architecture:
1. Core Control Unit - Raspberry Pi
Function: The Raspberry Pi serves as the central processing unit, integrating inputs from various hardware components, processing data, and transmitting instructions and data via the Bluetooth module.
Role: It runs operating systems and software applications, provides a graphical interface (if required), and networking capabilities, supporting interfaces for various peripherals.
2. Motion Tracking - MPU-6050 Module
Function: The MPU-6050 module combines a three-axis gyroscope and a three-axis accelerometer to monitor and report the device's angular velocity and acceleration. This integration provides comprehensive motion tracking data.
Role: By accurately measuring the device's movements and tilt angles in space, the MPU-6050 provides essential data for high-precision control and positioning of the device. This is crucial for ensuring the accuracy and responsiveness of the wireless mouse during operation, especially when performing complex or rapid movements. Its data are critical for the algorithm to adjust the cursor's position and movement in real-time to achieve a virtual response consistent with the physical movement.
3. Signal Transmission Module - HC-05 Master-Slave Integrated Bluetooth Module
Function: The HC-05 Bluetooth module is a master-slave integrated wireless serial communication module that transmits processed signals from the Raspberry Pi wirelessly to the connected computer or other receiving devices.
Role: Provides a stable wireless connection, allowing the device to move freely within a certain range without the need for physical connection cables. This module is particularly suitable for applications requiring remote control or data transmission, such as wireless remote control devices or data monitoring systems.
4. Signal Processing Module - CH341T USB-to-I2C/IIC/UART/TTL Serial Converter
Function: The CH341T converter is responsible for converting USB signals into I2C/IIC/UART/TTL signals that can be processed by the Raspberry Pi for effective data communication.
Role: Extends the Raspberry Pi's connectivity capabilities, enabling communication with other devices via USB. This enhances the system's interoperability and flexibility, especially when interfacing with a variety of hardware device types.
5. Power Module - Waveshare Raspberry Pi Expansion Board Lithium Battery Mobile Power Supply
Function: This expansion board has a built-in lithium battery that provides a stable 5V power supply to the Raspberry Pi and the connected Bluetooth module. This power design supports wireless operation, ensuring that the device can continue to work without an external power supply.
Role: As the mouse uses wireless Bluetooth technology for connectivity, it requires a reliable internal power system to ensure continuity and efficiency during mobile use. The use of a mobile power supply greatly increases the device's freedom and flexibility, particularly suitable for use in outdoor broadcasting or remote operations, without worrying about connection interruptions due to power issues.

### Project Video Demonstration

https://github.com/Qiyeeeee/Live-Streaming-Assistant/assets/43346136/ff3dcaa1-c6c2-445a-a0d8-bb16e29dfb49



### Installation Tutorial
On Windows or Linux platforms, after plugging the device receiver into the USB port. Wait for about 2 minutes and it is ready to use.

## Project Overview

### Project Hardware Overview
The live broadcast assistant has been meticulously designed to ensure seamless integration and communication between its components. At the heart of the system is the Raspberry Pi, which acts as the central processing unit, coordinating commands and data flow.
![1](https://github.com/Qiyeeeee/Live-Streaming-Assistant/assets/43346136/93156c6f-14b7-43c1-a2cd-0ebcdb054852)

**Raspberry Pi 3b+：** As a small and powerful single-board computer, the Raspberry PI acts as a central processing unit (CPU) that coordinates and controls the various parts of the entire system. This includes processing input and output data, executing software instructions, and managing communication with other devices or system components.

**HC-05 Bluetooth module：** The HC-05 Bluetooth module plays a crucial role by converting traditional serial communication into wireless Bluetooth communication, enabling the device to achieve remote data transmission without physical connection. This capability greatly improves the flexibility and mobility of the system for a variety of applications, including remote monitoring, control systems, and data collection, making the implementation and operation of projects more convenient and efficient.

**CH341T USB-I2C/IIC UART TTL：** CH341T USB-I2C/IIC UART TTL microcontroller serial downloader is a multifunctional interface converter, it provides the ability to convert from USB to I2C, UART and TTL, making the data transmission and program download between the microcontroller and the computer simple and efficient. The existence of this converter greatly enhances the compatibility and scalability of the project, supports a variety of different communication protocols, makes it possible to connect with a variety of devices and systems, which brings great convenience for development and debugging.

**MPU 6050：** The MPU-6050 sensor module plays a crucial role as a six-axis motion tracking device with an integrated gyroscope and accelerometer that provides real-time, three-dimensional motion information. This enables the project to capture and process precise position, speed, and acceleration data, which is particularly important for applications requiring motion control, attitude determination, or behavior analysis. These features of the MPU-6050 add advanced motion monitoring and analysis capabilities to the project, greatly expanding its application range and performance.


### Project Code Introduction
**main.cpp**: Responsible for processing the received sensor data and editing it as Msg waiting for the Bluetooth module to send it.

**bluetoothsender.cpp**: BluetoothSender, which sends data through the serial port, can be used to communicate with any device connected through the serial port, including but not limited to Bluetooth modules.

**MotionSensor.cpp**: MotionSensor implements the interaction with the MPU sensors, including initialisation, data reading, and basic data processing.

**CMakeLists.txt**: Used to configure the CMake project.
