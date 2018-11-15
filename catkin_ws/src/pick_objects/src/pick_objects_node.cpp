#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

#include <string>

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

move_base_msgs::MoveBaseGoal setGoal(double x, double y, double z, double w) {

	move_base_msgs::MoveBaseGoal goal;

	// set up the frame parameters
	goal.target_pose.header.frame_id = "map";
	goal.target_pose.header.stamp = ros::Time::now();

  	// Define a position and orientation for the robot to reach
  	goal.target_pose.pose.position.x = x;
  	goal.target_pose.pose.position.y = y;

  	goal.target_pose.pose.orientation.w = w;
  	goal.target_pose.pose.orientation.z = z;

	return goal;
}

bool checkGoalStatus(MoveBaseClient& ac, std::string success_msg, std::string fail_msg){
	bool reached_goal = false;

  	if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
    		ROS_INFO("%s", success_msg.c_str());
		reached_goal = true;
	}
  	else
    		ROS_INFO("%s", fail_msg.c_str());

	return reached_goal;
}

int main(int argc, char** argv){

  // Initialize the simple_navigation_goals node
  ros::init(argc, argv, "pick_objects");

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal pickup_goal  = setGoal(3.53071165085, 7.02457809448, 0.679776960744, 0.733418900521);
  move_base_msgs::MoveBaseGoal dropoff_goal = setGoal(-4.454413414, 6.56948661804, 0.703485544441, 0.710709567096);

  // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending pickup goal");
  ac.sendGoal(pickup_goal);
  // Wait an infinite time for the results
  ac.waitForResult();
  // Check if the robot reached its goal
  bool checkPickupGoal = checkGoalStatus(ac, "Pickup zone reached", "Unable to reach pickup zone");

  ROS_INFO("Picking up...");
  // Sleep for 5 seconds
  ros::Duration(5.0).sleep();

  // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending dropoff goal");
  ac.sendGoal(dropoff_goal);

  // Wait an infinite time for the results
  ac.waitForResult();
  // Check if the robot reached its goal
  bool checkDropoffGoal = checkGoalStatus(ac, "Dropoff zone reached", "Unable to reach dropoff zone");

  // Infom user if both goals were accomplished or not
  if (checkPickupGoal && checkDropoffGoal)
	ROS_INFO("Robot successfully reached both zones!");
  else 
	ROS_INFO("Robot did not reach both zones");

  // Sleep for 5 seconds
  ros::Duration(5.0).sleep();

  return 0;
}

