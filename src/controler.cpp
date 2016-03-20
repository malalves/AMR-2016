#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <geometry_msgs/Twist.h>
#include <iostream>

#define b 0.35
#define r 0.1

ros::Publisher pubR;
ros::Publisher pubL;

//comentario inutil
void c_callback(const geometry_msgs::TwistConstPtr &tws){
	std_msgs::Float64 vr, vl;

	ROS_INFO("received twist %f %f",tws->angular.z,tws->linear.x);

    vr.data = tws->linear.x - ((b/2)*(tws->angular.z));
    vl.data = tws->linear.x + ((b/2)*(tws->angular.z));

	pubR.publish(vr);
	pubL.publish(vl);
}
    
int main(int argc, char **argv){
    
    ros::init(argc,argv,"control");
    
    ros::NodeHandle control;

	ros::Subscriber twistSub = control.subscribe("/vehicle/Twist",1,c_callback);
    
    pubR = control.advertise<std_msgs::Float64>("/vrep/vehicle/motorRightSpeed", 1);
    pubL = control.advertise<std_msgs::Float64>("/vrep/vehicle/motorLeftSpeed", 1);
    
    ros::spin();
}
