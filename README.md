# Gyro_micro_ros Tutorial 


### In this tutorial, we are trying to track the oreantation of MPU5050 sensor and visulize in Rbiz2.

requirements : 

## First Step : Clone the repo and build 
1. Go to your workspace and clone the repo.
```git clone git@github.com:Htet-Wai-Yan-HWY/Gyro_micro_ros.git```

2. build the project.

```colcon build --symlink-install```

## Second Step : Upload program to your Esp32.

1. Go to src/fimware and upload the code.

If you are using ArduinoIDE go to Arduino Code directory and just upload the code.(don't forget to change the SSID,PASSOWRD AND TARGET IP)

### warning 
    make sure that installing micro_ros_arduino library.
    
    library link : https://github.com/micro-ROS/micro_ros_arduino/releases

## Third Step : Run micro ros agent 

    If it not installed, 
    ''' https://www.google.com/url?sa=t&rct=j&q=&esrc=s&source=web&cd=&ved=2ahUKEwiM_7TW-KmBAxX_zjgGHT3RAvkQFnoECBEQAQ&url=https%3A%2F%2Fmicro.ros.org%2Fdocs%2Ftutorials%2Fcore%2Ffirst_application_linux%2F&usg=AOvVaw2JYKgRAihkJH-UZgYwhdhV&opi=89978449 '''

in that link you can use to upload firmware with that packages but there is a little probem with my machine, so I used above methods. And build and source declear that project in your ros2 workspace.


In this project, I use wifi udp4 to get the data from micro_controller.
### warning : Don't use 24,25 pins for joystick module in esp32 (That used by wifi).


    If it already installed,
    run micro ros agent 
    
    ```ros2 run micro_ros_agent micro_ros_agent udp4 --port 8888```


## Need to continute read me: