cmake_minimum_required(VERSION 3.5)
project(udbot_odom2tf)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(tf2_msgs REQUIRED)
find_package(tf2_ros REQUIRED)

add_executable(udbot_odom2tf src/udbot_odom2tf.cpp)
ament_target_dependencies(udbot_odom2tf rclcpp std_msgs nav_msgs tf2_msgs tf2_ros)

install(TARGETS
  udbot_odom2tf
  DESTINATION lib/${PROJECT_NAME})

ament_package()
