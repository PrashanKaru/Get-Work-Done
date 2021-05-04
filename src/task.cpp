// standard C++ include files
#include <iostream>
#include <string>

// project provided include files
#include "input.cpp"
#include "task.h"

using namespace std;

// contructor

// Empty contructor - should be called only when creating a new task from menu
task::task(): task("", "", 0.0, 0.0, nullptr)
{
    try
    {
        // create an instance of Date for due_date which will be used later
        this->due_date = new date();
    }
    catch(const bad_alloc& exp)
    {
        throw runtime_error("Cannot create due date, out of memory");
    }
}

// All fields contructor - should be called when reading from saved data
task::task(string topic, string description, float time_allocated, float time_taken, date* due_date):
    topic(topic),
    description(description),
    time_allocated(time_allocated),
    time_taken(time_taken),
    due_date(due_date)
{
}

// Copy constructor
task::task(const task& src): task(src.topic, src.description, src.time_allocated, src.time_taken, nullptr)
{
    cout << "Calling copy constructor\n";
    try
    {
        this->due_date = new date(*(src.due_date));
    }
    catch(const bad_alloc& exp)
    {
        throw runtime_error("Cannot create due date, out of memory");
    }
}

// accessors

// set all fields in Task from stdin
void task::set_task_stdin(void)
{
    string s_data;

    // to ignore the \n that is present due to cin so that getline won't fail
    // cin.ignore();
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
        while(get_from_stdin<float>("Enter time allocated: ", f_data) == false)
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
void task::set_topic(string& topic)
{
    this->topic = topic;
}

// get topic
string task::get_topic(void)
{
    return this->topic;
}

// set description
void task::set_description(string& description)
{
    this->description = description;
}

// get description
string task::get_description(void)
{
    return this->description;
}

// set time_allocated
bool task::set_time_allocated(float& time_allocated)
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
float task::get_time_allocated(void)
{
    return this->time_allocated;
}

// set time_taken
bool task::set_time_taken(float& time_taken)
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
float task::get_time_taken(void)
{
    return this->time_taken;
}

// set due_date
void task::set_due_date(string& due_date)
{
    // call method to set due date
    this->due_date->set_date(due_date);
}

// get due_date
date* task::get_due_date(void)
{
    return this->due_date;
}

task::~task()
{
    delete due_date;
    due_date = nullptr;
}
