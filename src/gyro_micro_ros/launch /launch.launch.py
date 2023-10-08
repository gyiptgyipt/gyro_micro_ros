from launch_ros.actions import Node

import os 
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, ExecuteProcess, IncludeLaunchDescription
from launch.actions import DeclareLaunchArgument, ExecuteProcess, TimerAction
from launch.conditions import IfCondition
from launch.substitutions import LaunchConfiguration, PythonExpression
from launch.launch_description_sources import PythonLaunchDescriptionSource


def generate_launch_description():

	madgwick_filter = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([os.path.join(get_package_share_directory('rom2109_controller'), 'launch', 'rom2109.launch.py')])
    )
	
	micro_ros_agent=ExecuteProcess(
		cmd=[[
			'ros2 run micro_ros_agent micro_ros_agent udp4 --port 8888'
		]],
		shell=True,
		output='screen'
	)
	
	time_fill =Node(
    	package='gyro_micro_ros',
    	# namespace='turtlesim1',
    	executable='time_bridge',
		)


	return LaunchDescription(
		[
			madgwick_filter,
			micro_ros_agent,
			time_fill,
		]
	)