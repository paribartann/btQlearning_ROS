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


#ifndef SEQUENCE_STAR_NODE_H
#define SEQUENCE_STAR_NODE_H

#include "node.h"
#include <string>

namespace tree{

    class SequenceStarNode : public Node
    {
        private:
            unsigned int current_child_index_;
        public:
            SequenceStarNode(std::string key, unsigned int); 
            ReturnStatus Tick();
    };
}

#endif