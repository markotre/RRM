#ifndef PROJECT_TURTLECONTROL_H
#define PROJECT_TURTLECONTROL_H

// Include ros base
#include <ros/ros.h>
#include <ros/service.h>

//Include ros msgs
#include <geometry_msgs/Twist.h>
#include <turtlesim/Pose.h>
#include <turtlesim/TeleportAbsolute.h>
#include <turtlesim/SetPen.h>
#include <rrm_cv1_trebula/Draw.h>
#include <rrm_cv1_trebula/StartStop.h>


//main class for turtle control
class TurtleControl {

public:
    //Constructor
    TurtleControl();

    //Callbacks
    bool drawCallback(rrm_cv1_trebula::Draw::Request &req, rrm_cv1_trebula::Draw::Response &res);
    bool runCallback(rrm_cv1_trebula::StartStop::Request &req, rrm_cv1_trebula::StartStop::Response &res);
    void poseCallback(const turtlesim::Pose::ConstPtr& msg);

    // Other public methods
    void setupDrawing();
    void publish();
    double getRate();
    bool getDrawingStatus();
    bool run_state = false;
    int radius = 0;
    int speed = 0;


private:

    // Consts
    const double PUB_RATE = 100.0;
    const double  WINDOW_CENTER = 5.544444561;
    const double WINDOW_EDGE = 11.088889122;

    // member variables
    geometry_msgs::Twist velocity_msg_;
    bool drawing_status_;
    turtlesim::Pose pose_msg_;

    //ROS communication tools
    ros::Publisher velocity_pub_;
    ros::Subscriber pose_sub_;
    ros::ServiceServer square_service_;
    ros::ServiceServer startstop_service_;
    ros::ServiceClient teleport_client_;
};


#endif //PROJECT_TURTLECONTROL_H