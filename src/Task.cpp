// standard include files
#include <iostream>
#include <string>

// own include files
#include "Task.h"
#include "input.cpp"

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
        throw runtime_error("Cannot create due date, out of memory");
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
        throw runtime_error("Cannot create due date, out of memory");
    }
}

// accessors

// set all fields in Task from stdin
void Task::set_task_stdin(void)
{
    string s_data;

    // to ignore the \n that is present due to cin so that getline won't fail
    cin.ignore();
    // set topic
    cout << "Enter topic: ";
    getline(cin, s_data);

    this->topic = s_data;

    cout << endl;

    // set description
    cout << "Enter description: ";
    getline(cin, s_data);

    this->description = s_data;

    cout << endl;
    
    float f_data;

    bool got_it = false;

    while(got_it == false)
    {
        // get input from stdin and if true returned then valid input given
        while(get_from_stdin<float> ("Enter time allocated: ", f_data) == false)
        {
            cout << endl;
            cout << "Invalid input given" << endl;
            cout << "Try again" << endl;
            cout << endl;
        }

        // check to see if the time is only positive and not negative
        if(f_data < 0)
        {
            cout << endl;
            cout << "Entered time was negative" << endl;
            cout << "Try again" << endl;
            cout << endl;
        }
        else
        {
            got_it = true;
        }
    }

    this->time_allocated = f_data;

    cout << endl;

    cout << "Time to set due date" << endl;

    cout << endl;

    // set all fields in due_date
    due_date->set_date_stdin();

    cout << endl;
}

// set topic
void Task::set_topic(string & topic)
{
    this->topic = topic;
}

// get topic
string Task::get_topic(void)
{
    return this->topic;
}

// set description
void Task::set_description(string & description)
{
    this->description = description;
}

// get description
string Task::get_description(void)
{
    return this->description;
}

// set time_allocated
bool Task::set_time_allocated(float & time_allocated)
{
    // if the given value is less than zero then return false since negative is not possible
    if(time_allocated < 0)
    {
        return false;
    }
    else
    {
        this->time_allocated = time_allocated;
        return true;
    }
}

// get time_allocated
float Task::get_time_allocated(void)
{
    return this->time_allocated;
}

// set time_taken
bool Task::set_time_taken(float & time_taken)
{
    // if the given value is less than zero then return false since negative is not possible
    if(time_taken < 0)
    {
        return false;
    }
    else
    {
        this->time_taken = time_taken;
        return true;    
    }
}

// get time_taken
float Task::get_time_taken(void)
{
    return this->time_taken;
}

// set due_date
void Task::set_due_date(string & due_date)
{
    // call method to set due date
    this->due_date->set_date(due_date);
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