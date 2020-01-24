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

#include "../include/learningSelectorStar.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <random>
#include <cstdlib>
#include <ctime>

#define EPS 0.05

using namespace std;

void swap(int *a, int *b);

tree::LearningSelectorStarNode::LearningSelectorStarNode(string key, unsigned int num, EnvClass &envObject_)
{
    this->key = key;
    current_child_index_ = 0;
    set_type(LEARNINGSELECTORSTAR);
    set_num_children(num);
    envObject = &envObject_;
    current_child = 0;
    previous_child = 0;
}

tree::ReturnStatus tree::LearningSelectorStarNode::Tick()
{

    cout << "LearningSelectorStar Node ticked" << endl;

    if (envObject->reset)
    {
        current_child_index_ = 0;
        /****************** GENERATING RANDOM NUMBER ***************************/
        random_device rd;
        srand(rd());
        double random_number;
        random_number = (double)rand() / (double)RAND_MAX; //float in range 0 to 1
        //random_number = (double)rand() / (double)((unsigned) RAND_MAX + 1) //1 excluded
        cout << "RANDOM NUMBER = " << random_number << endl;
        int ActionIndexes[] = {0, 1, 2, 3, 4};
        int n = sizeof(ActionIndexes) / sizeof(ActionIndexes[0]);
        /***********************************************************************/
        
        //this is for the wayP and current action/////////
        std::pair<int, EnvClass::direction> heightDirection;
        heightDirection.first = envObject->height;
        heightDirection.second = envObject->orientation;
       

        int *returnedActionArray = getActionsArray(ActionIndexes, random_number, n); //get the action based on the random number generated
        for (unsigned int i = 0; i < get_num_children(); i++)
        {
            returnedArray[i] = returnedActionArray[i];
        }
        envObject->reset = false;
    }

    for (unsigned int i = 0; i < get_num_children(); i++)
    {
        cout << returnedArray[i] << " " << endl;
    }

    while (current_child_index_ < get_num_children())
    {

        envObject->previous_action = current_child;
        envObject->current_action = returnedArray[current_child_index_];
        current_child = returnedArray[current_child_index_];
        
        cout<<"PREV ACTION = "<< envObject->previous_action <<endl;
        cout<<"CURR ACTION = "<< envObject->current_action <<endl;
       

        cout << returnedArray[current_child_index_] << " number child is being ticked" << endl;

        //TICK
        child_i_status_ = child[returnedArray[current_child_index_]]->Tick();

        if (child_i_status_ == tree::FAILURE)
        {
            child[returnedArray[current_child_index_]]->set_status(tree::IDLE); //just to say that it's been completed

            if (current_child_index_ != (get_num_children() - 1)) //if not the last child
            {
                std::cout << current_child_index_ + 1 << "'th child of LearningSelectorStar returned FAILURE. Going for other one" << std::endl;
                current_child_index_++;
            }
            else //if it;s the last child
            {
                current_child_index_ = 0;
                std::cout << "Last child of LearningSelectorStar returned FAILURE. Going for other one" << std::endl;
                return child_i_status_;
            }
        }
        else
        {
            if (child_i_status_ == tree::SUCCESS) //success
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
            else //RUNNING
            {
                child[returnedArray[current_child_index_]]->set_status(child_i_status_);
                std::cout << current_child_index_ + 1 << "'th child of LearningSelectorStar returned RUNNING." << std::endl;
            }
            return child_i_status_;
        }
    }
    return child_i_status_;
}

int *tree::LearningSelectorStarNode::SortingArray(map<std::tuple<Index, int, EnvClass::direction>, double*> myMap, int actionArray[])
{
    auto current_state_tuple = make_tuple(envObject->currentWayPoint, envObject->height, envObject->orientation);
    unsigned int n = get_num_children();
    for (unsigned int i = 0; i < n-1; i++)
    {
        for (unsigned int j = 0; j < n-1-i; j++)
        {
            
            if (myMap[current_state_tuple][actionArray[j+1]] > myMap[current_state_tuple][actionArray[j]])
            {
                swap(&actionArray[j], &actionArray[j+1]);
            }
        }
        
        
    }
    return actionArray;
}

int *tree::LearningSelectorStarNode::getActionsArray(int *arr, double random_number, int n)
{
    
    if (random_number < EPS)
    {
        cout << "RANDOM" << endl;
        return randomize(arr, n);
    }
    else
    {
        cout << "SORTED" << endl;
        return SortingArray(envObject->dictQTable, arr);
    }
}

int *tree::LearningSelectorStarNode::randomize(int arr[], int n)
{

    random_device rd;
    srand(rd());
    for (int i = n - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        swap(&arr[i], &arr[j]);
    }

    return arr;
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
