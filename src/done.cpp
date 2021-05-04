// standard C++ include files
#include <iostream>

// project provided include files
#include "done.h"

done::done(): stage("done")
{
}

// methods

// remove task - override
// this overrided method should have no functionality
void done::remove_task(void)
{
    cout << "cannot remove from this stage" << endl;
}

// modify task
// this overrided method should have no functionality
void done::modify_task(void)
{
    cout << "cannot modify from this stage" << endl;
}

// print menu for current menu and perform action per user request
void done::menu(void)
{
    if(get_tasks()->empty() == true)
    {
        cout << "No tasks in " << get_stage() << endl;
        cout << endl;
        return;
    }

    cout << "Only can print contentes within Done stage" << endl;
    cout << endl;
    print();
}

// destructor
done::~done()
{
}
