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

#include "../include/condition.h"
#include "../include/env.h"
#include <iostream>
#include <string>


namespace tree
{

    ConditionNode::ConditionNode(std::string key, EnvClass& envObject_)
    {   
    this->key = key; 
    envObject = &envObject_;
    set_type(CONDITION);
    }

    ReturnStatus ConditionNode::Tick()
    {
        std::cout<<"Condition Node Ticked"<<std::endl;
            
        return envObject->call_condition(this->key);
            
    }


}
