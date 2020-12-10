# nastavenie kompilátora (pre kinetic a melodic 11)
cmake_minimum_required(VERSION 2.8.3)
project(abb_scanner_pkg)
add_compile_options(-std=c++14)
find_package(catkin REQUIRED COMPONENTS
        roscpp
        rospy
        std_msgs
        message_generation
        tf
        laser_geometry
        pcl_ros
        )
find_package(PCL REQUIRED QUIET COMPONENTS common sample_consensus io
        segmentation filters)
pkg_search_module(Eigen3 REQUIRED eigen3)
generate_messages(
        DEPENDENCIES
        std_msgs
)
include_directories(
        include
        ${catkin_INCLUDE_DIRS}
        ${EIGEN3_INCLUDE_DIRS}
        ${PCL_INCLUDE_DIRS}
)
add_executable(scanner src/scanner_node.cpp src/LaserScanToPointCloud.cpp)
target_link_libraries(scanner ${catkin_LIBRARIES})
add_dependencies(scanner ${catkin_EXPORTED_TARGETS})