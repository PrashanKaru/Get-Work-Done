// standard include files
#include <iostream>
#include <string>

// own include files
#include "Task.h"

using namespace std;

// contructor

// Empty contructor - should be called only when creating a new task from menu
Task::Task():
Task("", "", 0.0, 0.0, nullptr)
{
    try
    {
        // create an instance of Date for due_date which will be used later
        this->due_date = new Date();
    }
    catch(const bad_alloc & exp)
    {
        throw bad_alloc(exp);
    }
    
}

// All fields contructor - should be called when reading from saved data
Task::Task(string topic, string description, float time_allocated, float time_taken, Date * due_date):
topic(topic), description(description), time_allocated(time_allocated), time_taken(time_taken), due_date(due_date)
{

}

// Copy constructor
Task::Task(const Task & src):
Task(src.topic, src.description, src.time_allocated, src.time_taken, nullptr)
{
    cout << "Calling copy constructor\n";
    try
    {
        this->due_date = new Date(*(src.due_date));
    }
    catch(const bad_alloc & exp)
    {
        throw bad_alloc(exp);
    }
}

// accessors

// set all fields in Task from stdin
void Task::set_task_stdin(void)
{
    string s_data;

    // set topic
    cout << "Enter topic: ";
    getline(cin, s_data);

    this->topic = s_data;

    // set description
    cout << "Enter description: ";
    getline(cin, s_data);

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

    cout << "Set due date" << endl;

    // set all fields in due_date
    due_date->set_date_stdin();
}

// get topic
string Task::get_topic(void)
{
    return this->topic;
}

// get description
string Task::get_description(void)
{
    return this->description;
}

// get time_allocated
float Task::get_time_allocated(void)
{
    return this->time_allocated;
}

// get time_taken
float Task::get_time_taken(void)
{
    return this->time_taken;
}

// get due_date
Date * Task::get_due_date(void)
{
    return this->due_date;
}

Task::~Task()
{
    delete due_date;
    due_date = nullptr;
}