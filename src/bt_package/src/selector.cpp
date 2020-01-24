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

#include "../include/selector.h"
#include <iostream>
#include <string>

tree::SelectorNode::SelectorNode(std::string key, unsigned int num)
{
    this->key = key;
    set_type(SELECTOR);
    set_num_children(num);
}

tree::ReturnStatus tree::SelectorNode::Tick()
{
    std::cout << "Selector Node ticked" << std::endl;

    for (unsigned int i = 0; i < get_num_children(); i++)
    {
        child_i_status_ = child[i]->Tick();

        if (child_i_status_ != tree::FAILURE)
        {
            if (child_i_status_ == tree::SUCCESS)
            {
                child[i]->set_status(tree::IDLE);
                std::cout << i + 1 << "'th child of SELECTOR node returned SUCCESS. Returning back to the parent" << std::endl;
                return child_i_status_; //success 
            }
            else //this is the case of running
            {
                std::cout << i + 1 << "'th child of SELECTOR node returned RUNNNING. Returning back to the parent" << std::endl;
            }
        }
        else
        {
            if (i == (get_num_children() - 1))
            {
                child[i]->set_status(tree::IDLE);
                std::cout << "Last child of SELECTOR node returned FAILURE. The sequence failed and it's returning failure" << std::endl;
                return tree::FAILURE;   // If the  child status is failure, and it is the last child to be ticked,
                                        // then the sequence has failed.
            }
            else
            {
                std::cout << i + 1 << "'th child of SELECTOR node returned FAILURE. Going for other child" << std::endl;
            }
        }
    }
    return child_i_status_;
}