#include "rrm_cv3_trebula/forward_kinematics.h"

using namespace matrix;

ForwardKinematics::ForwardKinematics() : position_(0, 0, L1 + L2 + L3 +L4){

    // ROS node handler
    ros::NodeHandle n;

    // Creating subscriber, publisher and service server
    joint_sub_ = n.subscribe("joint_states", 5, &ForwardKinematics::jointCallback, this);

    // Resize joint_state array and initialize with value 0
    joint_state_.position.resize(3, 0);
}

void ForwardKinematics::broadcastTf(){

    //Create transformation, set origin and rotation and finally send
    tf::Transform transform;

    transform.setOrigin( tf::Vector3(0, 0, 0.0));
    tf::Quaternion q;
    q.setRPY(0,0,joint_state_.position[0]);
    transform.setRotation(q);
    broadcaster_.sendTransform(tf::StampedTransform(transform, ros::Time::now(),"base_link", "joint_1"));


    transform.setOrigin( tf::Vector3(0, 0, 0.203));
    q.setRPY(0,joint_state_.position[1],0);
    transform.setRotation(q);
    broadcaster_.sendTransform(tf::StampedTransform(transform, ros::Time::now(),"joint_1", "joint_2"));

    transform.setOrigin( tf::Vector3(0, 0, 0.178));
    q.setRPY(0,0,0);
    transform.setRotation(q);
    broadcaster_.sendTransform(tf::StampedTransform(transform, ros::Time::now(),"joint_2", "joint_3a"));

    transform.setOrigin( tf::Vector3(0, 0, joint_state_.position[2]));
    q.setRPY(0,0,0);
    transform.setRotation(q);
    broadcaster_.sendTransform(tf::StampedTransform(transform, ros::Time::now(),"joint_3a", "joint_3b"));

    transform.setOrigin( tf::Vector3(0, 0, 0.170));
    q.setRPY(0,joint_state_.position[3],0);
    transform.setRotation(q);
    broadcaster_.sendTransform(tf::StampedTransform(transform, ros::Time::now(),"joint_3b", "joint_4"));




    // Calculated forward kinematic tool0 -> base_link
    transform.setOrigin( position_ );
    transform.setRotation(orientation_);
    broadcaster_.sendTransform(tf::StampedTransform(transform, ros::Time::now(),"base_link", "tool0"));

    // Links
    transform.setOrigin( tf::Vector3(0, 0, 0.1015));
    q.setRPY(0,0,0);
    transform.setRotation(q);
    broadcaster_.sendTransform(tf::StampedTransform(transform, ros::Time::now(),"joint_1", "link1"));

    transform.setOrigin( tf::Vector3(0, 0, 0.089));
    q.setRPY(0,0,0);
    transform.setRotation(q);
    broadcaster_.sendTransform(tf::StampedTransform(transform, ros::Time::now(),"joint_2", "link2"));

    transform.setOrigin( tf::Vector3(0, 0, 0.089));
    q.setRPY(0,0,0);
    transform.setRotation(q);
    broadcaster_.sendTransform(tf::StampedTransform(transform, ros::Time::now(),"link2", "joint_3a"));

    transform.setOrigin( tf::Vector3(0, 0, 0.081));
    q.setRPY(0,0,0);
    transform.setRotation(q);
    broadcaster_.sendTransform(tf::StampedTransform(transform, ros::Time::now(),"joint_3b", "link3"));

    transform.setOrigin( tf::Vector3(0, 0, 0.04));
    q.setRPY(0,0,0);
    transform.setRotation(q);
    broadcaster_.sendTransform(tf::StampedTransform(transform, ros::Time::now(),"joint_4", "link4"));


}


void ForwardKinematics::jointCallback(const sensor_msgs::JointState::ConstPtr& msg)
{
    joint_state_ = *msg;

    Eigen::MatrixXd T0 = createRz(joint_state_.position[0]) * createTz(L1) * createRy(joint_state_.position[1]) * createTz(L2 + joint_state_.position[2] + L3 +0.05) * createRy(joint_state_.position[3]);

    // convert rotation matrix to tf matrix
    tf::Matrix3x3 tf3d;
    tf3d.setValue(static_cast<double>(T0(0,0)), static_cast<double>(T0(0,1)), static_cast<double>(T0(0,2)),
                  static_cast<double>(T0(1,0)), static_cast<double>(T0(1,1)), static_cast<double>(T0(1,2)),
                  static_cast<double>(T0(2,0)), static_cast<double>(T0(2,1)), static_cast<double>(T0(2,2)));

    // Convert to quternion
    tf3d.getRotation(orientation_);

    // Calculate position
    Eigen::MatrixXd p(4,1);
    p(0,0) = 0;
    p(1,0) = 0;
    p(2,0) = L4;
    p(3,0) = 1;
    Eigen::MatrixXd result = T0 * p;
    position_.setX(result(0,0));
    position_.setY(result(1,0));
    position_.setZ(result(2,0));
}
