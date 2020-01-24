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


/* taken help from geek for geeks */

#include "../include/node.h"
#include <string>
#include <iostream>
#include <queue>  
using namespace std;

namespace tree
{

    Node::Node() {}

    Node::~Node() {}
  
    // Prints the n-ary tree level wise 
    void LevelOrderTraversal(Node* root) 
    { 
        if (root == NULL) 
            return; 
    
        // Standard level order traversal code 
        // using queue 
        queue<Node *> q;  // Create a queue 
        q.push(root); // Enqueue root  
        while (!q.empty()) 
        { 
            int n = q.size(); 
    
            // If this node has children 
            while (n > 0) 
            { 
                // Dequeue an item from queue and print it 
                Node * p = q.front(); 
                q.pop(); 
                cout << p->key << " "; 
    
                // Enqueue all children of the dequeued item 
                for (unsigned long i=0; i < p->child.size(); i++) 
                    q.push(p->child[i]); 
                n--; 
            } 
    
            cout << endl; // Print new line between two levels 
        } 
    } 
} 
