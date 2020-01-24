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

#include "../include/sequencestar.h"
#include <iostream>
#include <string>


tree::SequenceStarNode::SequenceStarNode(std::string key, unsigned int num)
{
    this->key = key; 
    current_child_index_ = 0;
    set_type(SEQUENCESTAR);
    set_num_children(num);
}

tree::ReturnStatus tree::SequenceStarNode::Tick()
{
    std::cout<<"SequenceStar Node ticked"<<std::endl;
    
    while (current_child_index_ < get_num_children())
    {

        //tick the children and get its status
        child_i_status_ = child[current_child_index_]->Tick();
        child[current_child_index_]->set_status(child_i_status_);

        //now checking the returned status of the children nodes
        //if the child returns success
        
        if (child_i_status_ == tree::SUCCESS)
        {
            child[current_child_index_]->set_status(tree::IDLE);    //just to say that it's been completed

            if (current_child_index_ != (get_num_children() - 1))           //if not the last child
            {
                std::cout<<current_child_index_+1<<"'th child of SEQUENCESTAR returned SUCCESS. Going for other one"<<std::endl;
                current_child_index_++;
            }
            else        //if it;s the last child
            {
                current_child_index_ = 0;
                std::cout<<"Last child of SEQUENCESTAR returned SUCCESS. Going for other one"<<std::endl;
                return child_i_status_;
            }
        }
        else
        {
            if (child_i_status_ == tree::FAILURE)           //failure
            {
                child[current_child_index_]->set_status(tree::IDLE);    //just to say that it's been completed
                std::cout<<current_child_index_+1<<"'th child of SEQUENCESTAR returned FALIURE. Going for other one"<<std::endl;
                current_child_index_ = 0;
            }
            else  //RUNNING
            {
                child[current_child_index_]->set_status(child_i_status_);
                std::cout<<current_child_index_+1<<"'th child of SEQUENCESTAR returned RUNNING."<<std::endl;
                
            }
           return child_i_status_; 
        }
    }
    return child_i_status_; 
}




