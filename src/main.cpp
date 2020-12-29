// standard include files
#include <iostream>

// own include files
#include "Date.h"
#include "Task.h"

using namespace std;

int main(void)
{
    // Date * date_obj = new Date(29, 12, 20);
    // date_obj.set_date_stdin();
    // cout << date_obj.get_date() << endl;
    
    // Task * task_obj = new Task("Math", "Prime Number", 1.5, 0, date_obj);
    Task * task_obj = new Task();
    // task_obj->set_task_stdin();
    
    cout << task_obj->get_topic() << endl;
    cout << task_obj->get_description() << endl;
    cout << task_obj->get_time_allocated() << endl;
    cout << task_obj->get_due_date()->get_date() << endl;
    
    delete task_obj;
    return 0;
}