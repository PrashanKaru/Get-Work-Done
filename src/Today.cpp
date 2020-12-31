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
        cout << "**********Today Menu**********" << endl;
        cout << "1) Modify tasks" << endl;
        cout << "2) Remove Task" << endl;
        cout << "3) Print stats" << endl; 
        cout << "4) Print" << endl;
        cout << "5) Go back" << endl;
        cout << "******************************\n" << endl;

        // get input from stdin 
        get_from_stdin<int> ("Enter choice: ", choice);

        // placed for visual purpose
        cout << endl;

        // hold data for max ongoing time
        float new_max_ongoing_time {0.0};
    
        switch(choice)
        {
        case 1:
            modify_task();
            break;
        case 2:
            remove_task();
            break;
        case 3:
            cout << endl;
            cout << "*******************************" << endl;
            cout << "Maximum Allocated Time: " << get_max_allocated_time() << endl;
            cout << "Current Allocated Time: " << get_current_allocated_time() << endl;
            cout << "*******************************" << endl;
            cout << endl;
            break;
        case 4:
            print();
            break;
        case 5:
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