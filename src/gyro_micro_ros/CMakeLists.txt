cmake_minimum_required(VERSION 3.8)
project(gyro_micro_ros)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(rclcpp REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(turtlesim REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(tf2_geometry_msgs REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(rviz2 REQUIRED)


if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()



# add_executable(tf_pub src/tf_pub.cpp)
# ament_target_dependencies(tf_pub rclcpp tf2 tf2_ros sensor_msgs)

# add_executable(sub src/sub.cpp)
# ament_target_dependencies(sub rclcpp tf2 tf2_ros sensor_msgs)

# add_executable(tur src/sub.cpp)
# ament_target_dependencies(tur turtlesim rclcpp tf2 tf2_ros sensor_msgs)

# add_executable(not_sub src/not_sub.cpp)
# ament_target_dependencies(not_sub rclcpp tf2 tf2_ros sensor_msgs)

add_executable(raw src/raw.cpp)
ament_target_dependencies(raw rclcpp tf2 tf2_ros sensor_msgs geometry_msgs tf2_geometry_msgs)

add_executable(time_bridge src/time_bridge.cpp)
ament_target_dependencies(time_bridge rclcpp tf2 tf2_ros sensor_msgs)


install(DIRECTORY
  launch
  rviz
  DESTINATION share/${PROJECT_NAME}/
)

install(TARGETS
  time_bridge
  #raw
  # not_sub
  # tur
  # tf_pub
  #sub
  DESTINATION lib/${PROJECT_NAME})

# rosidl_generate_interfaces(${PROJECT_NAME}
#   "msg/Customimu.msg"
#   DEPENDENCIES geometry_msgs std_msgs # Add packages that above messages depend on, in this case geometry_msgs for Sphere.msg
# )




ament_package()
