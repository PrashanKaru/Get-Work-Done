#ifndef _TASK_H_
#define _TASK_H_

// own include files
#include "date.h"

class task
{
  public:
    // contructor

    // Empty contructor - should be called only when creating a new task from menu
    task();

    // All fields contructor - should be called when reading from saved data
    task(string topic, string description, float time_allocated, float time_taken, date* due_date);

    // Copy constructor
    task(const task& src);

    // accessors

    // set all fields in Task from stdin
    void set_task_stdin(void);

    // set topic
    void set_topic(string& topic);

    // get topic
    string get_topic(void);

    // set description
    void set_description(string& description);

    // get description
    string get_description(void);

    // set time_allocated
    bool set_time_allocated(float& time_allocated);

    // get time_allocated
    float get_time_allocated(void);

    // set time_taken
    bool set_time_taken(float& time_taken);

    // get time_taken
    float get_time_taken(void);

    // set due_date
    void set_due_date(string& due_date);

    // get due_date
    date* get_due_date(void);

    // Destructor
    ~task();

  private:
    string topic;
    string description;
    float time_allocated; // this will be in hours
    float time_taken;     // this will be in hours
    date* due_date;
};

#endif
