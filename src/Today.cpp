// standard include files
#include <iostream>

// personal include files
#include "Today.h"
#include "input.cpp"

// constructor
Today::Today():
Ongoing("today")
{

}

// methods

// this method will increase the time spent for a specfic ID
void Today::increase_time_spent(void)
{
    // hold data for max ongoing time
    float increase_time_by {0.0};
    
    // hold id
    size_t id {0};
    
    // check if ID exist
    get_from_stdin<size_t> ("Enter ID of task to increase time spent on: ", id);

    unordered_map<size_t, Task *>::const_iterator item_to_increase = find_id(id);

    cout << endl;

    cout << "Checking ID ..." << endl;

    cout << endl;
    
    // check if the id does not exist and if so print message and exist
    if(item_to_increase == get_tasks()->end())
    {
        cout << "ID does not exist" << endl;
        cout << endl;
    }
    else
    {
        get_from_stdin<float> ("Enter the time to increase this task by: ", increase_time_by);

        cout << endl;

        // if given time is less than 0 then exit
        if(increase_time_by < 0)
        {
            cout << "Cannot enter a negative value" << endl;
            cout << endl;
        }
        else
        {
            // increase time_allocated
            // get the current time taken
            float current_time_taken = item_to_increase->second->get_time_taken();

            // increase time and set time taken
            increase_time_by += current_time_taken;
            item_to_increase->second->set_time_taken(increase_time_by);
            increase_time_by -= current_time_taken;

            cout << "Successfully increased time by " << increase_time_by << " for task with ID " << id << endl;
            cout << endl;
        }
    }
}

// print menu for current menu and perform action per user request
void Today::menu(void)
{
    // check if stage is empty, if so print message and return
    if(get_tasks()->empty() == true)
    {
        cout << "No tasks in " << get_stage() << endl;
        cout << endl;
        return;
    }

    bool exit = false;
    while(exit == false)
    {
        // holds the choice from the menu
        int choice {0};
        cout << "*************Today Menu*************" << endl;
        cout << "1) Modify tasks" << endl;
        cout << "2) Increase time spent on task" << endl;
        cout << "3) Remove Task" << endl;
        cout << "4) Print stats" << endl; 
        cout << "5) Print" << endl;
        cout << "6) Go back" << endl;
        cout << "************************************\n" << endl;

        // get input from stdin 
        get_from_stdin<int> ("Enter choice: ", choice);

        // placed for visual purpose
        cout << endl;

    
        switch(choice)
        {
        case 1:
            modify_task();
            break;
        case 2:
            increase_time_spent();
            break;
        case 3:
            remove_task();
            break;
        case 4:
            cout << endl;
            cout << "*******************************" << endl;
            cout << "Maximum Allocated Time: " << get_max_allocated_time() << endl;
            cout << "Current Allocated Time: " << get_current_allocated_time() << endl;
            cout << "*******************************" << endl;
            cout << endl;
            break;
        case 5:
            print();
            break;
        case 6:
            // turn true to exit
            exit = true;
            cout << "Going back ..." << endl;
            // placed for visual purpose
            cout << endl;
            break;
        default:
            cout << "Choice does not exist" << endl;
            // placed for visual purpose
            cout << endl;
            break;
        }
    }
}

// destructor
Today::~Today()
{

}