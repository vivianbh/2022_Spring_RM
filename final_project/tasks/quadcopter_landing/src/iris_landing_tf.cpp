#include <iostream>
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <std_srvs/Empty.h>
#include <apriltag_ros/AprilTagDetectionArray.h>
#include <mav_msgs/conversions.h>
#include <mav_msgs/default_topics.h>
#include <trajectory_msgs/MultiDOFJointTrajectory.h>
#include <geometry_msgs/PointStamped.h>
#include <math.h>
#include <cmath>
#include <Eigen/Core>


ros::Publisher trajectory_pub;
geometry_msgs::PointStamped current_position;  // UAV 

float linear_smoothing_navigation_step = 2;
bool flag_gps_initialized_OK = false;
bool tag_gps_initialized_OK = false;
Eigen::Vector3d home;
Eigen::Vector3d apriltag_err;  // ref. to camera frame
Eigen::Vector3d position_err;  // ref. to world frame

void updateUavPosition(const geometry_msgs::PointStamped& msg)
{
    if (!flag_gps_initialized_OK) {flag_gps_initialized_OK= true;}
    current_position = msg;
}
  
void updateTagPosition(const apriltag_ros::AprilTagDetectionArray& msg){
    tag_gps_initialized_OK = true;

    // ref.to camera frame(= drone frame)
    apriltag_err[0] = msg.detections[0].pose.pose.pose.position.x;
    apriltag_err[1] = msg.detections[0].pose.pose.pose.position.y;
    apriltag_err[2] = msg.detections[0].pose.pose.pose.position.z;

    /***** convert to world frame *****/
    Eigen::Matrix3d R1, R2;
    // initial: x +180 degree -> z -90 degree
    float rx = 180*M_PI/180;
    float ry = 0;
    float rz = 90*M_PI/180;

    // ++ToDo++ need consider if the orientation of quadcopter change
    
    R1 <<       1,         0,        0,
	            0,   cos(rx),  sin(rx),
	            0,  -sin(rx),  cos(rx);
	R2 << cos(rz),  sin(rz),         0,
	     -sin(rz),  cos(rz),         0,
			    0,	      0,         1;                             cos(ry)*sin(rx),                            cos(ry)*cos(rx);
    position_err = R2*R1*apriltag_err;

    ROS_INFO("position error relate to camera: [%f, %f, %f].",
	    position_err[0],
	    position_err[1],
	    position_err[2]);
}

double getDistanceToTarget(const Eigen::Vector3d& position_err)
{
    double distance = 0;
    distance = position_err[0]*position_err[0] + position_err[1]*position_err[1] + position_err[2]*position_err[2];
    distance = sqrt(distance);
    return distance;
}

int main(int argc, char **argv){
	ros::init(argc, argv, "iris_landing_tf");
	ros::NodeHandle nh;
    // Create a private node handle for accessing node parameters.
    ros::NodeHandle nh_private("~");

    std::string uav_name = "iris_leader";  
    ros::param::get("~mav_name",uav_name);

    //Subscribe topic
	ros::Subscriber sub = nh.subscribe("/tag_detections",1000,updateTagPosition);
    ros::Subscriber position_sub = nh.subscribe(std::string("/"+uav_name+"/odometry_sensor1/position").c_str(), 10, &updateUavPosition);
    
    //Publish topic
    trajectory_pub = nh.advertise<trajectory_msgs::MultiDOFJointTrajectory>("/"+uav_name+"/command/trajectory", 10);


    trajectory_msgs::MultiDOFJointTrajectory trajectory_msg;
	trajectory_msg.header.stamp = ros::Time::now();

    
    while (ros::ok())
    { 
        
        if(flag_gps_initialized_OK && tag_gps_initialized_OK)
        {   
            ros::Duration(2).sleep();

            /***** get desire position *****/
            Eigen::Vector3d desired_position;
            double z_offset = 1.5;
            desired_position[0] = current_position.point.x + (position_err[0]);
            desired_position[1] = current_position.point.y + (position_err[1]);
            desired_position[2] = current_position.point.z + (position_err[2]) + z_offset;
            double desired_yaw = 0.0;

            ROS_INFO("UAV current position is: [%f, %f, %f].", current_position.point.x, current_position.point.y, current_position.point.z);
            ROS_INFO("Desire_position is: [%f, %f, %f].", desired_position[0], desired_position[1], desired_position[2]);
            ROS_INFO("The error distance to target is: %f", getDistanceToTarget(position_err));
            
            if(getDistanceToTarget(position_err)>0.1){
                mav_msgs::msgMultiDofJointTrajectoryFromPositionYaw(desired_position, desired_yaw, &trajectory_msg);
	            trajectory_pub.publish(trajectory_msg);
                ROS_INFO("Publish desire position: [%f, %f, %f].", desired_position[0], desired_position[1], desired_position[2]);
            }
            
        }

        ros::spinOnce();
    }

	ros::shutdown();
	return 0;
}