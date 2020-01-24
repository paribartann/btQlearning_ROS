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

/* taken help from geek for geeks for Node structure */


#ifndef NODE_H
#define NODE_H

#include <string> 
#include <vector>

// Represents a node of an n-ary tree 
namespace tree{

    enum NodeType{ SELECTOR, SEQUENCE, SELECTORSTAR, SEQUENCESTAR, ACTION, CONDITION, LEARNINGSELECTORSTAR, LEARNINGSEQUENCESTAR };
    enum ReturnStatus{RUNNING, SUCCESS, FAILURE, IDLE};

    class Node 
    { 
        private: 
            ReturnStatus status_;
            NodeType type_; 
            unsigned int N_of_children_;    

        public:
            Node();
            ~Node();
            
            unsigned int current_child;
            unsigned int previous_child;

            std::vector<Node*>child; 
            std::string key; 
            
            NodeType get_type() { return type_; }
            void set_type(NodeType _type) {type_ = _type;}

            ReturnStatus get_status() { return status_; }
            void set_status(ReturnStatus _status) {status_ = _status; }

            unsigned int get_num_children() { return N_of_children_; }
            void set_num_children(unsigned int num) {N_of_children_ = num; }

            virtual ReturnStatus Tick() = 0;    //pure virtual function 
         
            // child i status. Used to rout the ticks
            ReturnStatus child_i_status_;
            // ******************************** //

            
            
    }; 

    
    void LevelOrderTraversal(Node* root);
}   


#endif
   
