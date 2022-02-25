#include <ros/ros.h>
#include <visualization_msgs/Marker.h>

#include <people_msgs/PositionMeasurementArray.h>
#include <people_msgs/PositionMeasurement.h>

void leg_vis_cb(const people_msgs::PositionMeasurementArrayConstPtr& msg)
{
    uint32_t shape = visualization_msgs::Marker::CYLINDER;
    visualization_msgs::Marker marker;
    marker.header.frame_id = "/odom";
    marker.header.stamp = msg->header.stamp;
    marker.pose.position.x = msg->people[0].pos.x;
    marker.pose.position.y = msg->people[0].pos.x;
    marker.pose.position.z = 0;
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = 1.0;

    ROS_INFO("Recived leg tracker message at frame \"%s\" [%lf, %lf]", 
            marker.header.frame_id.c_str(), 
            marker.pose.position.x,
            marker.pose.position.y);
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "leg_visualization");
    ros::NodeHandle nh;
    ros::Rate(2);
    ros::Publisher marker_pub = nh.advertise<visualization_msgs::Marker>("visualization_marker", 10);
    ros::Subscriber leg_sub = nh.subscribe("leg_tracker_measurements", 1000, leg_vis_cb);
    

    ros::spin();
    return 0;
}