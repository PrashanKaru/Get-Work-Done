// standard include files
#include <fstream>
#include <iostream>

// personal include files
#include "../include/ongoing.h"
#include "input.cpp"

// constructor

// no parameter constructor
ongoing::ongoing(): ongoing("ongoing")
{
}

// constructor with parameter that allows setting the stage field from stage Class
ongoing::ongoing(string src): stage(src), max_allocated_time(0.0), current_allocated_time(0.0)
{
}

// methods

// this will be used to load the tasks from disk
void ongoing::load_tasks(void)
{
    // create string which holds file name
    string file_name = "." + this->get_stage() + ".data";

    // open in reading mode
    ifstream stage_file(file_name, ios_base::in);

    // if the file did not open then exit method and give appropriate message
    if(stage_file.is_open() == false)
    {
        string error_message = "No saved data for ";
        cout << "***" << error_message << get_stage() << "***" << endl;
        return;
    }

    // holds the data read from the file
    string s_data;

    // holds the converted string as a float type which was read from file
    float f_data {0.0};

    // file structure
    // 1st line holds max_allocated_time, extract and then get all other tasks

    // get max_ongoing_time
    getline(stage_file, s_data);

    // convert string to float
    f_data = stof(s_data);

    // set max_allocated_time
    this->max_allocated_time = f_data;

    task* new_task = nullptr;

    try
    {
        while(true)
        {
            // create a new instance of task
            new_task = new task();

            // get topic from file
            getline(stage_file, s_data);

            // check to see if eof has reached
            if(stage_file.eof() == true)
            {
                // delete object since eof has reached and exit
                delete new_task;
                break;
            }

            // set topic
            new_task->set_topic(s_data);

            // get description from file
            getline(stage_file, s_data);

            // set description
            new_task->set_description(s_data);

            // get time_allocated
            getline(stage_file, s_data);

            // convert string to float
            f_data = stof(s_data);

            // set time_allocated
            new_task->set_time_allocated(f_data);

            // increment current_ongoing
            this->current_allocated_time += f_data;

            // get time_taken
            getline(stage_file, s_data);

            // convert string to float
            f_data = stof(s_data);

            // set time_taken
            new_task->set_time_taken(f_data);

            // get due_date
            getline(stage_file, s_data);

            // set due_date
            new_task->set_due_date(s_data);

            // insert task
            insert_task(hash<string> {}(new_task->get_description()), new_task);
        }
    }
    catch(bad_alloc& exp) // this will take place if the task object cannot be created
    {
        cout << exp.what() << endl;
        cout << "*********************************" << endl;
        cout << "Cannot create task, out of memory" << endl;
        cout << "Cannot create anymore tasks" << endl;
        cout << "*********************************" << endl;
    }
    catch(runtime_error& exp) // this will take place if date object cannot be created
    {
        cout << exp.what() << endl;
        cout << "***************************" << endl;
        cout << "Cannot create anymore tasks" << endl;
        cout << "***************************" << endl;
        delete new_task;
    }

    // close file
    stage_file.close();
}

// this will be used to save the tasks to disk
void ongoing::save_tasks(void)
{
    // create string which holds file name
    string file_name = "." + this->get_stage() + ".data";

    // open in writing mode
    ofstream stage_file(file_name, ios_base::out);

    // if the file did not open then exit method and give appropriate message
    if(stage_file.is_open() == false)
    {
        cerr << "Error in opening file to save" << endl;
        return;
    }

    // first line will be max_allocated_time
    stage_file << this->max_allocated_time << endl;

    // iterate through the tasks and save each task
    // format to save
    /*
        topic
        description
        time_allocated
        time_taken
        due_date - value not pointer
    */
    // get pointer to ongoing tasks
    unordered_map<size_t, task*>* ongoing_tasks = get_tasks();

    for(unordered_map<size_t, task*>::const_iterator it = ongoing_tasks->begin(); it != ongoing_tasks->end(); it++)
    {
        stage_file << it->second->get_topic() << endl;
        stage_file << it->second->get_description() << endl;
        stage_file << it->second->get_time_allocated() << endl;
        stage_file << it->second->get_time_taken() << endl;
        stage_file << it->second->get_due_date()->get_date() << endl;
    }

    // close stage_file
    stage_file.close();
}

// print menu for current menu and perform action per user request
void ongoing::menu(void)
{
    // check if stage is empty, if so print message and return
    if(get_tasks()->empty() == true)
    {
        cout << "No tasks in " << get_stage() << endl;
        cout << endl;
        return;
    }

    bool exit = false;
    while(exit == false)
    {
        // holds the choice from the menu
        int choice {0};
        cout << "**********Ongoing Menu**********" << endl;
        cout << "1) Modify tasks" << endl;
        cout << "2) Remove Task" << endl;
        cout << "3) Print stats" << endl;
        cout << "4) Print" << endl;
        cout << "5) Go back" << endl;
        cout << "********************************\n" << endl;

        // get input from stdin
        get_from_stdin<int>("Enter choice: ", choice);

        // placed for visual purpose
        cout << endl;

        switch(choice)
        {
            case 1:
                modify_task();
                break;
            case 2:
                remove_task();
                break;
            case 3:
                cout << endl;
                cout << "*******************************" << endl;
                cout << "Maximum Allocated Time: " << get_max_allocated_time() << endl;
                cout << "Current Allocated Time: " << get_current_allocated_time() << endl;
                cout << "*******************************" << endl;
                cout << endl;
                break;
            case 4:
                print();
                break;
            case 5:
                // turn true to exit
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

// increase the current_allocated_time with the value provided as a parameter to the method
void ongoing::increase_current_allocated_time(float time_allocated)
{
    // increase current_allocated_time by the value time_allocated
    this->current_allocated_time += time_allocated;
}

// decrease the current_allocated_time with the value provided as a parameter to the method
void ongoing::decrease_current_allocated_time(float time_allocated)
{
    // decrease current_allocated_time by the value time_allocated
    this->current_allocated_time -= time_allocated;
}

// accessors

// setter max_allocated_time
bool ongoing::set_max_allocated_time(float& max_allocated_time)
{
    if(max_allocated_time < 0)
    {
        return false;
    }
    this->max_allocated_time = max_allocated_time;
    return true;
}

// getter max_allocated_time
float ongoing::get_max_allocated_time(void)
{
    return this->max_allocated_time;
}

// getter current_allocated_time
float ongoing::get_current_allocated_time(void)
{
    return this->current_allocated_time;
}

// destructor
ongoing::~ongoing()
{
}
