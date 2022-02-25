#include <string.h>
#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <tf/transform_datatypes.h>
#include <sound_play/sound_play.h>


using std::string;
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

string phrases[] = {
    "01_Intro.wav",
    "02_Stop_Arrival.wav",
    "03_Package_Delivered.wav",
    "04_Trouble_Navigating.wav",
    "05_Finish.wav"
};

string base_sound_path = "/home/jr2/Phrases/";

void sleepok(int t, ros::NodeHandle &nh)
{
    if (nh.ok())
        sleep(t);
}

struct place_t {
    float x;
    float y;
    float yaw;
    string name;
    place_t(float xi, float yi, float yawi, string namei) :
        x(xi), y(yi), yaw(yawi), name(namei)
    {}
};

int main(int argc, char** argv)
{
    ros::init(argc, argv, "simple_navigation_goals");
    ros::NodeHandle nh;
    // tell action client spin a thread by default
    // MoveBaseClient ac("move_base", true);
    sound_play::SoundClient sc;
    // wait for action server to come up
    // while(!ac.waitForServer(ros::Duration(5.0))) {
    //     ROS_INFO("Waiting for the move_base action server to come up");
    // }
    
    sleepok(1, nh);
    // Initialize move_base goal message
    move_base_msgs::MoveBaseGoal goal;
    goal.target_pose.header.frame_id = "map";
    int i = 0;
    // std::vector<place_t> waypoints;
    // TODO use a vector for waypoint navigation
    // map hallway goal posts
    // (47.392, 66.779, 1.566)  E-door 
    // (47.923, 56.401, -1.577) Student door
    // (36.469 53.735 -0.016)   Hallway 
    // (53.455, 51.290, -0.106) P3 door
    // (25.321, 56.717, 1.627)  Assistance desk
    // (37.307, 38.004, -3.097) Front of other help desk
    /** int num_goals = 3;
    // float x[num_goals] = {36.469, 47.323, 47.392};
    // float y[num_goals] = {53.735, 56.401, 66.779};
    // float yaw[num_goals] = {-0.016, 1.577, 1.566};
    string places[num_goals] = {
        "Hallway",
        "Student Worker room",
        "Emergency Exit door"
    }; */

    int num_goals = 5;
    float x[num_goals] = {37.307, 25.321, 53.455, 47.323, 47.392};
    float y[num_goals] = {38.004, 56.717, 52.290, 56.401, 66.779};
    float yaw[num_goals] = {-3.097, 1.627, -0.106, 1.577, 1.566};
    string places[num_goals] = {
        "Front help desk",
        "Assistance Desk",
        "P3 Door",
        "Student Worker room",
        "Emergency Exit door"
    };

    while(nh.ok()) {
        goal.target_pose.header.stamp = ros::Time::now();
        goal.target_pose.pose.position.x = x[i];
        goal.target_pose.pose.position.y = y[i];
        goal.target_pose.pose.orientation = tf::createQuaternionMsgFromYaw(yaw[i]);

        string wav = base_sound_path + phrases[i];
        sc.playWave(wav);
        ROS_INFO("Playing [%d] %s", i, wav.c_str());
        sleepok(4, nh);
        sc.stopWave(wav);

        // ROS_INFO("Sending goal to '%s'", places[i].c_str());
        // ac.sendGoal(goal);

        // ac.waitForResult();

        // if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED) {
            
        // }
        // else {
        //     ROS_WARN("Could not reach goal.");
        // }
        i = (++i) % num_goals;  // increment to next goal.
    }
    

    return 0;
}
