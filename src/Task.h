#ifndef _TASK_H_
#define _TASK_H_

// own include files
#include "Date.h"

class Task
{
    public:
        // contructor
        
        // Empty contructor - should be called only when creating a new task from menu
        Task();
        
        // All fields contructor - should be called when reading from saved data
        Task(string topic, string description, float time_allocated, float time_taken, Date * due_date);

        // Copy constructor
        Task(const Task & src);

        // accessors

        // set all fields in Task from stdin
        void set_task_stdin(void);

        // get topic
        string get_topic(void);
        
        // get description
        string get_description(void);

        // get time_allocated
        float get_time_allocated(void);

        // get time_taken
        float get_time_taken(void);

        // get due_date
        Date * get_due_date(void);

        // Destructor
        ~Task();

    private:
        string topic;
        string description;
        float time_allocated; // this will be in hours
        float time_taken; // this will be in hours
        Date * due_date;
};

#endif