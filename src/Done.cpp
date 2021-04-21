// standard include files
#include <iostream>

// personal include files
#include "Done.h"

Done::Done(): Stage("done")
{
}

// methods

// remove task - override
// this overrided method should have no functionality
void Done::remove_task(void)
{
    cout << "cannot remove from this stage" << endl;
}

// modify task
// this overrided method should have no functionality
void Done::modify_task(void)
{
    cout << "cannot modify from this stage" << endl;
}

// print menu for current menu and perform action per user request
void Done::menu(void)
{
    if(get_tasks()->empty() == true)
    {
        cout << "No tasks in " << get_stage() << endl;
        cout << endl;
        return;
    }

    cout << "Only can print contentes within Done Stage" << endl;
    cout << endl;
    print();
}

// destructor
Done::~Done()
{
}
