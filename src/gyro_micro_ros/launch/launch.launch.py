from launch_ros.actions import Node

import os 
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, ExecuteProcess, IncludeLaunchDescription
from launch.actions import DeclareLaunchArgument, ExecuteProcess, TimerAction
from launch.conditions import IfCondition
from launch.substitutions import LaunchConfiguration, PythonExpression
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration, PathJoinSubstitution
from launch_ros.substitutions import FindPackageShare


def generate_launch_description():
	
	use_rviz = LaunchConfiguration('use_rviz')

	madgwick_filter = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([os.path.join(get_package_share_directory('imu_filter_madgwick'), 'launch', 'imu_filter.launch.py')])
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
	rviz_config_file = PathJoinSubstitution(
        [FindPackageShare("gyro_micro_ros"), "rviz", "gyro.rviz"]
    )
	rviz_node = Node(
        package="rviz2",
        executable="rviz2",
        condition=IfCondition(LaunchConfiguration('use_rviz')),
        name="rviz2",
        output="log",
        arguments=["-d", rviz_config_file],
    )


	return LaunchDescription(
		[
            DeclareLaunchArgument('use_rviz', default_value='true', description='Use rviz.'),
			madgwick_filter,
			micro_ros_agent,
			time_fill,
			rviz_node,
		]
	)