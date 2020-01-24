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


#include "../include/selectorstar.h"
#include <iostream>
#include <string>



tree::SelectorStarNode::SelectorStarNode(std::string key, unsigned int num, EnvClass& envObject_)
{
    this->key = key; 
    current_child_index_ = 0;
    set_type(SELECTORSTAR);
    set_num_children(num);
    envObject = &envObject_;
    current_child = 0;
    previous_child = 0;
}


tree::ReturnStatus tree::SelectorStarNode::Tick()
{
    std::cout<<"SelectorStar Node ticked"<<std::endl;

    while (current_child_index_ < get_num_children())
    {
        envObject->previous_action = current_child;
        envObject->current_action = current_child_index_;

        child_i_status_ = child[current_child_index_]->Tick();
        
        //now checking the returned status of the children nodes
        if (child_i_status_ == tree::FAILURE)
        {
            set_status(child_i_status_);
            
            if (current_child_index_ != (get_num_children() - 1))
            {
                std::cout<<current_child_index_+1<<"'th child of SELECTORSTAR returned FAILURE. Going for other one"<<std::endl;
                current_child_index_++;
            }
            else
            {
                std::cout<<"Last child of SELECTORSTAR returned FAILURE. Returning FAILURE to the Parent"<<std::endl;
                current_child_index_ = 0;
                return tree::FAILURE;
            }
        }
        else
        {
            if (child_i_status_ == tree::SUCCESS)
            {
                if (current_child_index_ == (get_num_children() - 1))
                {
                    std::cout<<"Last child of SELECTORSTAR returned SUCCESS. Going for other one"<<std::endl;
                    current_child_index_ = 0;
                }
                else
                {
                    std::cout<<current_child_index_+1<<"'th child of SELECTORSTAR returned SUCCESS. Going for other one"<<std::endl;
                    current_child_index_++;
                }
            }
            else
            {
                std::cout<<current_child_index_+1<<"'th child of SELECTORSTAR returned RUNNING."<<std::endl;
            }
            
            return child_i_status_; 
        }
        //return child_i_status_;   
    }
    return child_i_status_; 
}



