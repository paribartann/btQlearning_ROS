/*
#Copyright (C) <September, 2019>  <Paribartan Dhakal>

#This program is free software: you can redistribute it and/or modify
#it under the terms of the GNU Affero General Public License as
#published by the Free Software Foundation, either version 3 of the
#License, or (at your option) any later version.

#This program is distributed in the hope that it will be useful,
#but WITHOUT ANY WARRANTY; without even the implied warranty of
#MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#GNU Affero General Public License for more details.
*/

#ifndef ENV_H
#define ENV_H

#include <tuple>
#include <map>
#include <string>
#include <utility>
#include <vector>
#include "node.h"

namespace tree {

struct Index {
  Index() {}
  Index(int i, int j) : i(i), j(j) {}
  int i;
  int j;

  bool operator<(const Index &right) const {
    return i < right.i || (i == right.i && j < right.j);
  }
};

class EnvClass {
 private:
  char env[10][10];                                          //environment array

  std::map<int, std::string> actionNameMap;                  //mapping the index with action name for output
                                                             // purpose only


  int count;                                                 // this is needed to maintain the intersection 
                                                             // of the visible blocks

  bool targetVisible;                                        //sets true if we can see the target  

  std::string self_id_;                                      //id associated with each drone (for generalment)

 public:
  enum direction { EAST, SOUTH, WEST, NORTH };               //orientation of the drone
  int height;                                                //height of the drone
  EnvClass(std::string self_id, int*);                             // constructor

  direction orientation;                                     //variable of direction enum

  std::map<int, Index> wayPointMap;                          //maps waypoint index with its corresponding co-efficient

  std::map<Index, int> q_wayPointMap;                        //previously need for learningSequenceStar.cpp
  std::pair<int, direction> heightDirection;                 //this is required for q_wayPointHeightDirectionMap
  std::pair<Index, std::pair<int, direction>> wayPointHeightDirection;
  std::map<std::pair<Index, std::pair<int, direction>>, int> // maps the pair of coordinates, orientaion
      q_wayPointHeightDirectionMap;                          // and height with the q-table index




  std::map<std::tuple<Index, int, direction>, double*> dictQTable;
  
  void qDictTableUpdate(Index, unsigned int, int, Index, int, direction, int, direction);



  std::vector<Index> visibleBlockFunction(Index, direction,
                                          int);             // a lookup table that returns
                                                            // all the visible blocks from
                                                            // a certain orientation,
                                                            // height, and a location

  Index initialWayPoint;
  Index currentWayPoint;

  bool getTargetVisible() { return targetVisible; }
  std::string getDirection(direction);
  int getIntDirection(direction);

  const int NUMBER_OF_WAYPOINTS = 5;
  const int NUMBER_OF_ACTIONS = 5;

  int rotate_counter;
  ReturnStatus rotate_status;

  unsigned int current_action;
  unsigned int previous_action;

  bool reset;

  int index;                                                 // for random index
  /****************   action   **********************/
  ReturnStatus rotate();
  ReturnStatus elevate();
  ReturnStatus de_elevate();
  ReturnStatus waypoint_translation();
  ReturnStatus end_episode();
  /**************** endOfAction *********************/

  Index prevWaypoint;

                                                            // condition
  ReturnStatus is_target_visible();

  // utility function for mapping a function with its string value(gotten from a
  // BT file)
  ReturnStatus call_function(std::string);
  ReturnStatus call_condition(std::string);

  bool isTargetThere();                                     // calls a visibleBlock function and checks if target
                                                            // is present in the returned indexes.

 
  double findMaxQValueDict(Index, int, direction);
  void settingEnvironment(int* wayp);
  void printEnvironment();
  void printQTableDict();
};

}  // namespace tree

#endif