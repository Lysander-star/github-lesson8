cmake_minimum_required(VERSION 3.8)
project(lengths_ros CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(example_interfaces REQUIRED)

add_library(lengths STATIC src/lengths.cpp)
target_include_directories(lengths PUBLIC include)

add_executable(length_pub src/length_pub.cpp)
target_link_libraries(length_pub lengths)
ament_target_dependencies(length_pub rclcpp example_interfaces)

add_executable(mean_node src/mean_node.cpp)
target_link_libraries(mean_node lengths)
ament_target_dependencies(mean_node rclcpp example_interfaces)

install(TARGETS length_pub mean_node
  DESTINATION lib/${PROJECT_NAME})

ament_package()
