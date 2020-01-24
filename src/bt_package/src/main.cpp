/* 
#Copyright (C) <June, 2019>  <Paribartan Dhakal>

#This program is free software: you can redistribute it and/or modify
#it under the terms of the GNU Affero General Public License as
#published by the Free Software Foundation, either version 3 of the
#License, or (at your option) any later version.

#This program is distributed in the hope that it will be useful,
#but WITHOUT ANY WARRANTY; without even the implied warranty of
#MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#GNU Affero General Public License for more details.
*/

#include <ros/ros.h>
#include "../include/tree.h"
#include <iostream>
#include <fstream>
#include <string>


using namespace std;

int main(int argc, char* argv[])
{

    string name_space, file_location, waypoints;
    ros::init(argc, argv, "tree_node");
    ros::NodeHandle nh("~");
    nh.getParam("name_space", name_space);
    nh.getParam("file_location", file_location);
    nh.getParam("waypoints", waypoints);
      
    ROS_INFO("Got Parameter: %s", name_space.c_str());
    ROS_INFO("Got Parameter: %s", file_location.c_str());
    ROS_INFO("Got Parameter: %s", waypoints.c_str());
    
    const char* fileName = file_location.c_str();
    
      
    ifstream infile(waypoints);
    int num = 0;
    infile >> num;  //number of elements
    int wayp_array[num];
    for (int i = 0; i < num; i++)
    {
        wayp_array[i] = 0;
    }
    
    for (int i = 0; i < num; i++)
    {
        infile>>wayp_array[i];
    }
    
    tree::BT bt1(name_space, wayp_array);

  
    tree::Node* root = bt1.buildBT(fileName);
    
    bt1.execute(root, 10000);

    return 0;
}
