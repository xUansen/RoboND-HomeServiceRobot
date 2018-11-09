#!/bin/sh
catkin_dir=/home/nvidia/workspace/RoboND-HomeServiceRobot/catkin_ws
catkin_src_dir=$catkin_dir/src

# launch turtlebot in the custom world
xterm -e "roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$catkin_src_dir/Worlds/simple.world"
sleep 2
