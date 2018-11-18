#!/bin/sh
catkin_dir=/home/nvidia/workspace/RoboND-HomeServiceRobot/catkin_ws
catkin_src_dir=$catkin_dir/src

#Launch turtlebot in the custom world
xterm  -e  " roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$catkin_src_dir/World/simple.world" &
sleep 5

#Launch gmapping demo
xterm -e " roslaunch turtlebot_gazebo amcl_demo.launch map_file:=$catkin_src_dir/World/myMap.yaml" &
sleep 2

#Launch rviz
xterm -e " roslaunch turtlebot_rviz_launchers view_navigation.launch"
