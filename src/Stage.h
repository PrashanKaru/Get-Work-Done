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
        Stage(string stage);

        // methods
        // insert new task
        void insert_task(void);
        // remove task
        void remove_task(size_t id);
        // this will be used to load the tasks from disk
        void load_tasks(void);
        // this will be used to save the tasks to disk
        void save_tasks(void);
        // print a table edge with a specific character
        void print_table_edge(const char character, const unsigned short horizontal_line_length);
        // print a single task
        void print_task(unordered_map<size_t, Task *>::const_iterator current_task);
        // print all tasks
        void print_all_tasks(void);

        // destructor
        ~Stage();
    private:
        unordered_map<size_t, Task *> * tasks;
        string stage;
};

#endif