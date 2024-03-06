cmake_minimum_required(VERSION 3.5)

project(piMouse LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall")

add_definitions(-DMPU6050)
add_definitions(-DMPU_DEBUGOFF)

add_executable(piMouse main.cpp I2Cdev.cpp inv_mpu.cpp inv_mpu_dmp_motion_driver.cpp MotionSensor.cpp bluetoothsender.cpp)
target_link_libraries(piMouse PRIVATE -lwiringPi -lpthread)
