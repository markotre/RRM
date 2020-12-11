#include "abb_scanner_pkg/LaserScanToPointCloud.h"

int main(int argc, char** argv){


    ros::init(argc, argv, "listener");
    ros::NodeHandle n;

    LaserScanToPointCloud laserScanToPointCloud;
    ros::Rate rate(400);
    ROS_INFO("Initializing scanner_node");

    while(ros::ok()){
        ros::getGlobalCallbackQueue()->callAvailable(ros::WallDuration(0.1));
        ros::spin();
        rate.sleep();
    }

    return 0;
}
