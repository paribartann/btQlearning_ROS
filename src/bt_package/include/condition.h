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

#ifndef CONDITION_NODE_H
#define CONDITION_NODE_H

#include "node.h"
#include "../include/env.h"


namespace tree{

    class ConditionNode : public Node
    {
        public:
             ConditionNode(std::string key, EnvClass&);
            ReturnStatus Tick(); 
            EnvClass* envObject;
    };
}



#endif