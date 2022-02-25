#!/usr/bin/env python
import rospy
from sys import argv
from geometry_msgs.msg import PoseWithCovarianceStamped
from tf.transformations import quaternion_from_euler


def publisher(x_pos=47.2, y_pos=55.2, yaw_rad=-1.534):
    pub = rospy.Publisher("/initialpose", PoseWithCovarianceStamped, queue_size=1)
    rospy.init_node('update_pose', anonymous=True)
    rate = rospy.Rate(2)  # Hz
    rospy.sleep(3)
    # Set
    p = PoseWithCovarianceStamped()
    p.header.frame_id = "map"
    p.header.stamp = rospy.Time.now()
    p.pose.pose.position.x = x_pos
    p.pose.pose.position.y = y_pos
    [x, y, z, w] = quaternion_from_euler(0, 0, yaw_rad)
    p.pose.pose.orientation.x = x
    p.pose.pose.orientation.y = y
    p.pose.pose.orientation.z = z
    p.pose.pose.orientation.w = w

    pub.publish(p)
    rospy.loginfo("Set 2D pose [%f, %f, %f]", x_pos, y_pos, yaw_rad)


if __name__ == "__main__":
    try:
        if len(argv) == 1:
            publisher()
        elif len(argv) == 4:
            publisher(float(argv[1]), float(argv[2]), float(argv[3]))
        else:
            rospy.logerr("Argument ysage is [x_pos, y_pos, yaw_rad] in map coordinates.")
    except rospy:
        pass
