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

#include "../include/learningSequenceStar.h"

#include <iostream>
#include <string>
#include <algorithm>
#include <random>
#include <cstdlib>
#include <ctime>

#define EPS 0.05

using namespace std;

tree::LearningSequenceStarNode::LearningSequenceStarNode(string key, unsigned int num, EnvClass &envObject_)
{
    this->key = key;
    current_child_index_ = 0;
    set_type(LEARNINGSEQUENCESTAR);
    set_num_children(num);
    envObject = &envObject_;
    current_child = 0;
    previous_child = 0;
}

tree::ReturnStatus tree::LearningSequenceStarNode::Tick()
{
    std::cout << "LearningSequenceStar Node ticked" << std::endl;

    // if (envObject->reset)
    // {
    //     current_child_index_ = 0;
    //     /****************** GENERATING RANDOM NUMBER ***************************/
    //     random_device rd;
    //     srand(rd());
    //     double random_number;
    //     random_number = (double)rand() / (double)RAND_MAX; //float in range 0 to 1
    //     //random_number = (double)rand() / (double)((unsigned) RAND_MAX + 1) //1 excluded
    //     cout << "RANDOM NUMBER = " << random_number << endl;
    //     int ActionIndexes[] = {0, 1, 2, 3, 4};
    //     int n = sizeof(ActionIndexes) / sizeof(ActionIndexes[0]);
    //     /***********************************************************************/

    //     current_state = envObject->currentWayPoint; //observing the current state

    //     //cout<<"X: "<<current_state.i<<" Y: "<s<current_state.j<<endl;

    //     int *returnedActionArray = getActionsArray(ActionIndexes, random_number, n); //get the action based on the random number generated
    //     for (unsigned int i = 0; i < get_num_children(); i++)
    //     {
    //         returnedArray[i] = returnedActionArray[i];
    //     }
    //     envObject->reset = false;
    // }

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
        cout<<"CURR CHILD = "<< current_child <<endl;

        cout << "\n"
             << returnedArray[current_child_index_] + 1<< " number child is being ticked" << endl;

        //tick the children and get its status
        child_i_status_ = child[returnedArray[current_child_index_]]->Tick();
        child[returnedArray[current_child_index_]]->set_status(child_i_status_);

        //now checking the returned status of the children nodes
        //if the child returns sucess

        if (child_i_status_ == tree::SUCCESS)
        {
            child[returnedArray[current_child_index_]]->set_status(tree::IDLE); //just to say that it's been completed

            if (current_child_index_ != (get_num_children() - 1)) //if not the last child
            {
                std::cout << current_child_index_ + 1 << "'th child of LEARNINGSEQUENCESTAR returned SUCCESS. Going for other one" << std::endl;
                std::cout << "=================NEW ACTION STARTING==============" << std::endl;
                current_child_index_++;
            }
            else //if it;s the last child AND SUCCESS
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

                //because always the reset is happening after waypoint translation, getting the indexes of next 
                //waypoint and sorting it's (action array);
                current_state = envObject->currentWayPoint; //observing the current state 
                
                
                //cout<<"X: "<<current_state.i<<" Y: "<s<current_state.j<<endl;

                int *returnedActionArray = getActionsArray(ActionIndexes, random_number, n); //get the action based on the random number generated
                for (unsigned int i = 0; i < get_num_children(); i++)
                {
                    returnedArray[i] = returnedActionArray[i];
                }
                std::cout << "Last child of LEARNINGSEQUENCESTAR returned SUCCESS. Going for other one" << std::endl;

                return child_i_status_;
            }
        }
        else
        {
            if (child_i_status_ == tree::FAILURE) //failure
            {
                child[returnedArray[current_child_index_]]->set_status(tree::IDLE); //just to say that it's been completed
                std::cout << returnedArray[current_child_index_] + 1 << "'th child of LEARNINGSEQUENCESTAR returned FALIURE. Going for other one" << std::endl;
                current_child_index_ = 0;
            }
            else //RUNNING
            {
                child[returnedArray[current_child_index_]]->set_status(child_i_status_);
                std::cout << returnedArray[current_child_index_] + 1 << "'th child of LEARNINGSEQUENCESTAR returned RUNNING." << std::endl;
            }
            return child_i_status_; //RETURN EITHER FAILURE OR RUNNING
        }
    }
    return child_i_status_;
}

//int *tree::LearningSequenceStarNode::SortingArray(double array[][5], int actionArray[])
int *tree::LearningSequenceStarNode::SortingArray(map<std::tuple<Index, int, EnvClass::direction>, double*> myMap, int actionArray[])
{

    int max_index;
    double index_val;
    auto current_state_tuple = make_tuple(envObject->currentWayPoint, envObject->height, envObject->orientation);

    for (unsigned int i = 0; i < get_num_children() - 1; i++)
    {
        max_index = i;
        for (unsigned int j = i + 1; j < get_num_children(); j++)
        {
            // if (array[envObject->q_wayPointHeightDirectionMap[current_state]][j] > array[envObject->q_wayPointHeightDirectionMap[current_state]][max_index])
            if (myMap[current_state_tuple][j] > myMap[current_state_tuple][max_index])
            {
                max_index = j;
            }
        }
        index_val = actionArray[max_index];
        actionArray[max_index] = actionArray[i];
        actionArray[i] = index_val;
    }
    return actionArray;
}


int *tree::LearningSequenceStarNode::getActionsArray(int *arr, double random_number, int n)
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

int *tree::LearningSequenceStarNode::randomize(int arr[], int n)
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

void tree::LearningSequenceStarNode::swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
