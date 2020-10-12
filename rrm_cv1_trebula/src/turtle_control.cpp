#include "rrm_cv1_trebula/turtle_control.h"
#include <ros/service.h>
#include <std_srvs/Empty.h>



ros::ServiceClient clearClient;

TurtleControl::TurtleControl(){

    // NodeHandler
    ros::NodeHandle n;

    // Publisher
    velocity_pub_ = n.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 1);

    // Subscriber
    pose_sub_ = n.subscribe("turtle1/pose", 1, &TurtleControl::poseCallback, this);

    // Service server
    square_service_ = n.advertiseService("/turtle_control/draw", &TurtleControl::drawCallback, this);

    startstop_service_ = n.advertiseService("/turtle_control/startstop", &TurtleControl::runCallback, this);


    // Service client
    teleport_client_ = n.serviceClient<turtlesim::TeleportAbsolute>("/turtle1/teleport_absolute");
    ros::ServiceClient setpen_client = n.serviceClient<turtlesim::SetPen>("/turtle1/set_pen");
    ros::service::waitForService("clear");
    clearClient = n.serviceClient<std_srvs::Empty>("/clear");


    //init variables
    velocity_msg_ = geometry_msgs::Twist();

    //set default pen width
    int width = 1;
    int r = 0;
    int g = 0;
    int b = 0;


    // get parameters from server
    n.getParam("/turtle_control/line/width", width);
    n.getParam("/turtle_control/line/color/r", r);
    n.getParam("/turtle_control/line/color/g", g);
    n.getParam("/turtle_control/line/color/b", b);

    ROS_WARN("Farba bola nacitana R= %d G= %d B= %d",r,g,b);

    // Create service message
    turtlesim::SetPen setpen_srv;
    setpen_srv.request.width = width;
    //setup pen colors
    setpen_srv.request.r = r;
    setpen_srv.request.g = g;
    setpen_srv.request.b = b;
    setpen_srv.request.off = false;

    ros::service::waitForService("/turtle1/set_pen");
    // Call service
    if (setpen_client.call(setpen_srv)){
        ROS_WARN("Ciara bola uspesne nastavena");
    }

    //variable init
    this->drawing_status_ = false;
    this->pose_msg_ = turtlesim::Pose();
}

// service server callback for start/stop the drawing
bool TurtleControl::runCallback(rrm_cv1_trebula::StartStop::Request &req, rrm_cv1_trebula::StartStop::Response &res) {

    this->run_state = req.run;
    if(this->run_state){
        velocity_msg_.linear.x = this->speed;
        velocity_msg_.angular.z= (float)(this->speed)/(float)(this->radius);
    }else {
        velocity_msg_.linear.x = 0;
        velocity_msg_.angular.z= 0;
    }
    res.success = true;
    return true;
}

// service server callback for starting the drawing and drawing speed/radius configuration
bool TurtleControl::drawCallback(rrm_cv1_trebula::Draw::Request &req, rrm_cv1_trebula::Draw::Response &res)
{
    // osetrenie delenia nulou
    if(req.radius != 0){
        this->speed = req.speed;
        this->radius= req.radius;
        if(this->run_state){
            velocity_msg_.linear.x = this->speed;
            velocity_msg_.angular.z= (float)(this->speed)/(float)(this->radius);
        }
        this->drawing_status_ = true;
        res.success = true;
    }else{
        res.success = false;

    }



    return true;
}

// topic callback a for listening to the pose message from the turtle
void TurtleControl::poseCallback(const turtlesim::Pose::ConstPtr& msg)
{
    if ((msg->x >= WINDOW_EDGE)||(msg->y >= WINDOW_EDGE)||(msg->x <= 0)||(msg->y <= 0))
    {
        turtlesim::TeleportAbsolute teleport_srv;
        teleport_srv.request.theta = 0;
        teleport_srv.request.x = WINDOW_CENTER;
        teleport_srv.request.y = WINDOW_CENTER;
        teleport_client_.call(teleport_srv);
        velocity_msg_.linear.y = 0;
        velocity_msg_.linear.z = 0;
        velocity_msg_.linear.x = 0;
        velocity_msg_.angular.y = 0;
        velocity_msg_.angular.z = 0;
        velocity_msg_.angular.x = 0;
        this->run_state = false;
        std_srvs::Empty srv;
        clearClient.call(srv);

    }
    this->pose_msg_ = *msg;


}

// publishing the configured velocity
void TurtleControl::publish()
{
    velocity_pub_.publish(velocity_msg_);
}

//frequency setup
double TurtleControl::getRate()
{
    return PUB_RATE;
}

//getter if drawing is enabled or not
bool TurtleControl::getDrawingStatus()
{
    return this->drawing_status_;
}


