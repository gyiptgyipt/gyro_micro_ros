# Gyro_micro_ros Tutorial 


### In this tutorial, we will try to track the oreantation of MPU6050 sensor and visulize in Rviz2.

### requirements :
install imu tools from CCNY Robotics Lab to use filters.

```
sudo apt-get install ros-<YOUR_ROSDISTRO>-imu-tools
``` 

## First Step : Clone the repo and build 
1. Go to your workspace and clone the repo.

```
git clone git@github.com:gyiptgyipt/gyro_micro_ros.git
```

2. build the project.

```
colcon build --symlink-install
```

## Second Step : Upload program to your Esp32.

1. Go to src/firmware and upload the code.

If you are using ArduinoIDE go to [Arduino Code](https://github.com/Htet-Wai-Yan-HWY/gyro_micro_ros/blob/main/src/firmware/Arduino%20Code/gyro_pub/gyro_pub.ino) directory and just upload the code.(don't forget to change the SSID,PASSOWRD AND TARGET IP)

### warning 
    
make sure that installing micro_ros_arduino library.
    
library link : [micro_ros_arduino](https://github.com/micro-ROS/micro_ros_arduino/releases)

## Third Step : Run micro ros agent 

If it not installed, [micro_ros.org](https://micro.ros.org/docs/tutorials/core/first_application_linux/) and follow the tutorial.

-In that link you can use to upload firmware with that packages but there is a little probem with my machine, so I used above methods. And build and source declear that project in your ros2 workspace.

-I just use the micro_ros_agent from that tutorial.(Because we uploaded our firmware with arduino IDE)


In this project, I use wifi udp4 to get the data from micro_controller.
### warning : Don't use 24,25 pins for joystick module in esp32 (That used by wifi).


If it already installed,  run micro ros agent 
    
```
ros2 run micro_ros_agent micro_ros_agent udp4 --port 8888
```

## Fourth step : 

-Run time_bridge and imu_filter (time_bridge.cpp in nothing, It just sync time with ros2 system because I am not familiar with "rclc" micro_ros_arduino library's time stamp.)
-And don't forget to set value of use_magnetometer: false in imu_tools package's configuration because Mpu6050 don't have magnetometer.

```
ros2 run gyro_micro_ros time_bridge
```
    
after subscribing and republishing imu data,we add filter. 

```
ros2 launch imu_filter_madgwick imu_filter.launch.py
```


# Open rviz2 and enjoy the imu visulization 

## youtube video link : [YOUTUBE](https://www.youtube.com/watch?v=9Fiira7s9Rk)

### After that tutorial you can follow these tutorial.

-Mapping using Ultrasonic Sensor ([sonic_to_laser](https://github.com/Htet-Wai-Yan-HWY/sonic_to_laser))


### Free to ask me anytime if something was wrong, I love to help you guys <3
    
