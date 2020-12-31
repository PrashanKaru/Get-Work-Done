#ifndef _ONGOING_H_
#define _ONGOING_H_

// standard include files

// personal include files
#include "Stage.h"

class Ongoing : public Stage
{
    public:
        // constructor
        
        // no parameter constructor
        Ongoing();
        
        // constructor with parameter that allows setting the stage field from Stage Class
        Ongoing(string src);

        // methods

        // print a single task
        // should print without time taken as ongoing should not have this info
        virtual void print_task(unordered_map<size_t, Task *>::const_iterator current_task);
        
        // this will be used to load the tasks from disk
        virtual void load_tasks(void) override;
        
        // this will be used to save the tasks to disk
        virtual void save_tasks(void) override;

        // print menu for current menu and perform action per user request
        virtual void menu(void) override;

        // increase the current_allocated_time with the value provided as a parameter to the method
        void increase_current_allocated_time(float time_allocated);
        
        // decrease the current_allocated_time with the value provided as a parameter to the method
        void decrease_current_allocated_time(float time_allocated);

        // accessors

        // setter max_allocated_time
        bool set_max_allocated_time(float & max_allocated_time);

        // getter max_allocated_time
        float get_max_allocated_time(void);
        
        // getter current_allocated_time
        float get_current_allocated_time(void);
        
        //destructor
        ~Ongoing();

    private:
        // this will hold the maximum allocated time that all the task's time allocated can add up to
        float max_allocated_time;
        // this will hold the current allocated time that all the task's time allocated add up to
        float current_allocated_time;
};

#endif