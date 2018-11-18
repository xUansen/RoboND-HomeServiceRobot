#!/bin/sh
catkin_dir=/home/nvidia/workspace/RoboND-HomeServiceRobot/catkin_ws
catkin_src_dir=$catkin_dir/src

# launch turtlebot in the custom world
xterm -e "roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$catkin_src_dir/World/simple.world" &
sleep 5

# launch amcl demo
xterm -e " roslaunch turtlebot_gazebo gmapping_demo.launch custome_gmapping_launch_file:=$catkin_src_dir/turtlrbot_simulatior/turtlebot_gazebo/launch/gmapping.launch.xml" &
sleep 2

# launch rviz
xterm -e " roslaunch turtlebot_teleop keyboard_teleop.launch" &
sleep 10

# launch markers in rviz
xterm -e "roslaunch turtlebot_rviz_launchers view_navigation.launch"
