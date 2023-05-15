cmake_minimum_required(VERSION 3.0.2)
project(rotate_map)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)

find_package(catkin REQUIRED COMPONENTS
  pcl_ros
  roscpp
)
find_package(PCL 1.8 REQUIRED )
find_package(yaml-cpp REQUIRED)
find_package(Boost REQUIRED COMPONENTS system)

catkin_package(
 INCLUDE_DIRS include
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${PCL_INCLUDE_DIRS}
)

add_executable(${PROJECT_NAME} 
  src/pcd_io_handler.cpp
  src/map_transformator.cpp
  src/main.cpp
)

target_link_libraries(${PROJECT_NAME}
  ${catkin_LIBRARIES}
  ${PCL_LIBRARIES}
  ${Boost_LIBRARIES}
  yaml-cpp
  stdc++fs
)
