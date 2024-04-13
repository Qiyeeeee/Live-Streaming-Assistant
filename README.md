# Live-Streaming-Assistant

### Project Introduction:
With the growth of the internet industry, the live broadcasting sector has expanded rapidly. Traditional mice, which require a desktop environment, are no longer sufficient for all scenarios in the life of a live streamer. For example, outdoor broadcasters or performing artists often face the challenge of not being able to rely on a fixed desktop surface while performing. To address this issue, we have developed a gesture-controlled mouse that allows broadcasters to freely control their live stream in any setting without being limited by a desktop surface.

### Project Members
| Name | Email | Contribution | GitHub |
|----------|----------|----------|----------|
| Jianhua Dong |2938631D@student.gla.ac.uk | Row1Col3 | Row1Col4 |
| Ao Liu | 2858676L@student.gla.ac.uk | Row2Col3 | [trashcanbomb](https://github.com/trashcanbomb) |
| Lixun Ma | 2929238M@student.gla.ac.uk | Row3Col3 | Row3Col4 |
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
### Installation Tutorial
-
-
### Project Overview


### bluetoothsender.cpp
BluetoothSender, which sends data through the serial port, can be used to communicate with any device connected through the serial port, including but not limited to Bluetooth modules.

### MotionSensor.cpp
MotionSensor implements the interaction with the MPU sensors, including initialisation, data reading, and basic data processing.

### CMakeLists.txt
Used to configure the CMake project, where some of the source files that make up the executable have not been uploaded (3.6.2024)
