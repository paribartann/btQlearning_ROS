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


#ifndef TREE_H
#define TREE_H

#include <string>
#include <vector>
#include "node.h"

#include "env.h"

namespace tree{
    class BT
     {
        public:
            
            BT(std::string str, int*);   // constructor
            ~BT() { delete envObject; }  // destructor   
 
            Node* buildBT(const char*);   // builds a Behavior Tree (BT) from a given file and returns the pointer to its root node
            void execute(Node*, int);     // logically executes a given BT 

            //***Utility Functions for buildTree function***//
            std::string getBehavior(int);
            unsigned int getNumberOfChildren(int);
            int getDepth(int);
            //**********************************************//

            //recursive function to build a tree
            void buildTree(int, int, Node*, int);

            EnvClass* envObject;
 
        private:

            Node* root;  //root node of a tree
            //*********** Helper variables for building a tree ************//
            Node* rootC; 
            std::vector<std::string> result; 
            std::vector < std::vector<std::string> > splittedBySpace;
            std::vector<std::string> splitWord;
            std::vector<int> alreadyParsed;
            //*************************************************************// 
    };

}
#endif
