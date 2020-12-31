// standard include files
#include <iostream>

// personal include files
#include "Today.h"

// constructor
Today::Today():
Ongoing("today")
{

}

// methods

// print menu for current menu and perform action per user request
void Today::menu(void)
{
    // holds the choice from the menu
    int choice {0};
    cout << "Today Menu" << endl;
    cout << "1) Modify tasks" << endl;
    cout << "2) Set Maximum Allocated Time" << endl;
    cout << "3) Remove Task" << endl;
    cout << "4) Print stats" << endl; 
    cout << "5) Print" << endl;
    cout << "6) Go back" << endl;
    cout << "Enter choice: ";
    cin >> choice;

    // holds the id of the task to modify
    size_t id {0};

    // hold data for max ongoing time
    float new_max_ongoing_time {0.0};
  
    switch(choice)
    {
    case 1:
        cout << "Enter ID of task to modify: ";
        cin >> id;
        modify_task(id);
        break;
    case 2:
    {
        cout << "Enter Maximum Allocated Time: ";
        cin >> new_max_ongoing_time;
        bool success = set_max_allocated_time(new_max_ongoing_time);
        // if the result of max_allocated_time is less than zero a false is returned as time cannot be negative
        if(success == false)
        {
            cout << "Value cannot be less than 0" << endl;
        }
    }
        break;
    case 3:
        cout << "ID of task to remove: ";
        cin >> id;
        remove_task(id);
        break;
    case 4:
        cout << "Maximum Allocated Time: " << get_max_allocated_time() << endl;
        cout << "Current Allocated Time: " << get_current_allocated_time() << endl;
        break;
    case 5:
        print();
        break;
    case 6:
        cout << "Going back ..." << endl;
        break;
    default:
        cout << "Choice does not exist" << endl;
        break;
    }
}

// destructor
Today::~Today()
{

}