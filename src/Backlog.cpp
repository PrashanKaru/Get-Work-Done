// standard include files
#include <iostream>

// personal include files
#include "Backlog.h"
#include "input.cpp"

// constructor
Backlog::Backlog(): Stage("backlog")
{
}

// methods

// insert new task from stdin - overloaded insert_task(size_t, Task *)
void Backlog::insert_task(void)
{
    Task* new_task = nullptr;
    try
    {
        // create default Task
        new_task = new Task();

        // get info about task from stdin
        cout << "Set details of new task" << endl;
        cout << endl;
        new_task->set_task_stdin();

        // add task to unordered_map
        // key - hashed task->description
        // value - new_task
        // calls other overloaded method
        insert_task(hash<string> {}(new_task->get_description()), new_task);
    }
    catch(bad_alloc& exp) // this will take place if the task object cannot be created
    {
        cerr << exp.what() << endl;
        cerr << "Cannot create task, out of memory" << endl;
        cerr << "Cannot create anymore tasks" << endl;
    }
    catch(runtime_error& exp) // this will take place if date object cannot be created
    {
        cerr << exp.what() << endl;
        cerr << "Cannot create anymore tasks" << endl;
        delete new_task;
    }
}

// print a single task
// should print without time taken as ongoing should not have this info
void Backlog::print_task(unordered_map<size_t, Task*>::const_iterator current_task)
{
    const unsigned short horizontal_line_length = 50;

    // horizontal =================== for ammount specficed by horizontal line
    print_table_edge('=', horizontal_line_length);

    // print ID
    cout << "ID: " << current_task->first << endl;

    // print -------------
    print_table_edge('-', horizontal_line_length);

    // print topic
    cout << "Topic: " << current_task->second->get_topic() << endl;

    // print -------------
    print_table_edge('-', horizontal_line_length);

    // print description
    cout << "Description: " << current_task->second->get_description() << endl;

    // print -------------
    print_table_edge('-', horizontal_line_length);

    // print time_allocated
    cout << "Time Allocated: " << current_task->second->get_time_allocated() << endl;

    // print -------------
    print_table_edge('-', horizontal_line_length);

    // print due_date
    cout << "Due Date: " << current_task->second->get_due_date()->get_date() << endl;

    // horizontal =================== for ammount specficed by horizontal line
    print_table_edge('=', horizontal_line_length);
}

// print menu for current menu and perform action per user request - no implmentation in base class
void Backlog::menu(void)
{
    bool exit = false;

    while(exit == false)
    {
        // holds the choice from the menu
        int choice {0};
        cout << "**********Backlog Menu**********" << endl;
        cout << "1) Insert task" << endl;
        cout << "2) Modify task" << endl;
        cout << "3) Remove task" << endl;
        cout << "4) Print" << endl;
        cout << "5) Go back" << endl;
        cout << "********************************\n" << endl;

        // get input from stdin
        get_from_stdin<int>("Enter choice: ", choice);

        cout << endl;

        switch(choice)
        {
            case 1:
                // call insert method with no arguements
                insert_task();
                break;
            case 2:
                modify_task();
                break;
            case 3:
                remove_task();
                break;
            case 4:
                print();
                break;
            case 5:
                exit = true;
                cout << "Going back ..." << endl;
                // placed for visual purpose
                cout << endl;
                break;
            default:
                cout << "Choice does not exist" << endl;
                // placed for visual purpose
                cout << endl;
                break;
        }
    }
}

// destructor
Backlog::~Backlog()
{
}
