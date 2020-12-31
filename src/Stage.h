#ifndef _STAGE_H_
#define _STAGE_H_

// standard include files
#include <unordered_map>
#include <string>

// personal include files
#include "Task.h"

using namespace std;

class Stage
{
    public:
        // constructor

        // no parameter constructor used for arrays
        Stage();

        // single paramter constructor
        Stage(string stage);

        // methods

        // insert new task by providing the information
        void insert_task(size_t id, Task * task_to_insert);
        
        // remove task
        virtual void remove_task(void);

        // modify task
        virtual void modify_task(void);
        
        // this will be used to load the tasks from disk
        virtual void load_tasks(void);
        
        // this will be used to save the tasks to disk
        virtual void save_tasks(void);
        
        // print a table edge with a specific character
        void print_table_edge(const char character, const unsigned short horizontal_line_length);
        
        // print a single task
        virtual void print_task(unordered_map<size_t, Task *>::const_iterator current_task);
        
        // print all tasks
        void print_all_tasks(void);
        
        // print based on topic
        void print_specific_topic(void);
        
        // print based on due date
        void print_specific_due_date(void);
        
        // print based on time allocated
        void print_specific_time_allocated(void);
        
        // print based on ID
        void print_id(void);

        // print menu for current menu and perform action per user request
        virtual void menu(void) = 0;

        // method for printing all print options available and printing
        void print(void);

        // check to see if the passed id exist in the tasks or not
        unordered_map<size_t, Task *>::const_iterator find_id(size_t id);

        // accessors

        // get stage
        string get_stage(void);
        
        // get tasks pointer
        unordered_map<size_t, Task *> * get_tasks(void);

        // destructor
        virtual ~Stage();
    private:
        unordered_map<size_t, Task *> * tasks;
        string stage;
};

#endif