// standard include files
#include <iostream>

// own include files
#include "Date.h"
#include "Task.h"

using namespace std;

void print(Task task_obj)
{
    cout << "Due date addr: " << task_obj.get_due_date() << endl;
    cout << task_obj.get_topic() << endl;
    cout << task_obj.get_description() << endl;
    cout << task_obj.get_time_allocated() << endl;
    cout << task_obj.get_due_date()->get_date() << endl;
}

int main(void)
{
    Date * date_obj = new Date(29, 12, 20);
    // date_obj.set_date_stdin();
    // cout << date_obj.get_date() << endl;
    
    Task * task_obj_1 = new Task("Math", "Prime Number", 1.5, 0, date_obj);
    // Task * task_obj_1 = new Task();
    // Task task_obj(*task_obj_1);
    // task_obj->set_task_stdin();
    cout << "Due date addr: " << task_obj_1->get_due_date() << endl;
    cout << task_obj_1->get_due_date()->get_date() << endl;
    print(*task_obj_1);
    cout << "Due date addr: " << task_obj_1->get_due_date() << endl;
    cout << task_obj_1->get_due_date()->get_date() << endl;
    delete task_obj_1;
    return 0;
}