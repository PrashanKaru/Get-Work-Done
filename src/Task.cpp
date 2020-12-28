// standard include files
#include <iostream>
#include <string>

// own include files
#include "Task.h"

using namespace std;

// contructor

// Empty contructor - should be called only when creating a new task from menu
Task::Task():
topic(""), description(""), time_allocated(0.0), time_taken(0.0)
{

}

// All fields contructor - should be called when reading from saved data
Task::Task(string topic, string description, float time_allocated, float time_taken, Date due_date):
topic(topic), description(description), time_allocated(time_allocated), time_taken(time_taken), due_date(due_date)
{

}

// accessors

// set all fields in Task from stdin
void Task::set_task_stdin(void)
{
    string s_data;

    // set topic
    cout << "Enter topic: ";
    cin >> s_data;

    this->topic = s_data;

    // set description
    cout << "Enter description: ";
    cin >> s_data;

    this->description = s_data;

    float f_data;

    // set time_allocated
    cout << "Enter time allocated: ";
    cin >> f_data;

    // check to see if the time is only positive and not negative
    while(f_data < 0)
    {
        cout << "Please enter a positive time\n";
        cout << "Enter time allocated: ";
        cin >> f_data;
    }

    this->time_allocated = f_data;

    // set time_taken
    cout << "Enter time taken: ";
    cin >> f_data;

    // check to see if the time is only positive and not negative
    while(f_data < 0)
    {
        cout << "Please enter a positive time\n";
        cout << "Enter time taken: ";
        cin >> f_data;
    }

    this->time_taken = f_data;

    // set due_date
    due_date.set_date_stdin();
}

// get topic
string get_topic(void);

// get description
string get_description(void);

// get time_allocated
float get_time_allocated(void);

// get time_taken
float get_time_taken(void);

// get due_date
Date get_due_date(void);