// standard C++ include files
#include <fstream>
#include <iostream>

// project provided include files
#include "input.cpp"
#include "stage.h"

using namespace std;

// constructor

// no parameter constructor used for arrays
stage::stage()
{
}

// single paramter constructor
stage::stage(string stage_name): stage_name(stage_name)
{
    try
    {
        tasks = new unordered_map<size_t, task*>();
    }
    catch(const bad_alloc& exp)
    {
        cerr << "Not enough memory to create " + this->stage_name << endl;
    }
}

// methods
// insert new task by providing the information
void stage::insert_task(size_t id, task* task_to_insert)
{
    this->tasks->insert(make_pair(id, task_to_insert));
}

// remove task
void stage::remove_task()
{
    // holds id to remove
    size_t id {0};

    // get input from stdin and if true returned then valid input given
    if(get_from_stdin<size_t>("ID of task to remove: ", id) == false)
    {
        cout << endl;
        cout << "Invalid input given" << endl;
        cout << endl;
        return;
    }

    cout << endl;

    cout << "Checking if ID exists" << endl;
    cout << endl;
    // check to see if the key exists in the map
    unordered_map<size_t, task*>::const_iterator item_to_remove = tasks->find(id);
    if(item_to_remove == tasks->end())
    {
        cout << "Entered ID does not match any task" << endl;
        cout << endl;
    }
    else
    {
        // delete the memory allocated for the task
        delete item_to_remove->second;

        // erase using key
        tasks->erase(id);
        cout << "Task with ID removed sucessfully" << endl;
        cout << endl;
    }
}

// modify task
void stage::modify_task(void)
{
    // holds id to remove
    size_t id {0};

    // get input from stdin and if true returned then valid input given
    if(get_from_stdin<size_t>("Enter ID of task to modify: ", id) == false)
    {
        cout << "Invalid input given" << endl;
        cout << endl;
        return;
    }

    cout << endl;

    cout << "Checking if ID exists" << endl;

    cout << endl;
    // check to see if the item exists
    unordered_map<size_t, task*>::const_iterator item_to_modify = tasks->find(id);

    // check if the item does not exist and print message and exit
    if(item_to_modify == tasks->end())
    {
        cout << "ID does not exist" << endl;
        cout << endl;
        return;
    }

    bool exit = false;

    while(exit == false)
    {
        int choice {0};
        // present options
        cout << "*******Choose option to modify*******" << endl;
        cout << "1) Topic" << endl;
        cout << "2) Description" << endl;
        cout << "3) Time Allocated" << endl;
        cout << "4) Due Date" << endl;
        cout << "5) Go Back" << endl;
        cout << "*************************************\n" << endl;

        get_from_stdin<int>("Enter choice: ", choice);

        // placed for visual purpose
        cout << endl;

        string s_data;
        float f_data;

        switch(choice)
        {
            case 1:
                // rename topic
                cout << "Rename topic: ";
                getline(cin, s_data);
                // modify topic to new topic
                item_to_modify->second->set_topic(s_data);
                cout << endl;
                cout << "Topic renamed" << endl;
                cout << endl;
                break;
            case 2: {
                // rename description
                cout << "Rename description: ";
                getline(cin, s_data);

                // rename with new description
                item_to_modify->second->set_description(s_data);

                // get the current task *, this is because description determines the key and hence needs to be
                // recomputed and inserted into the unordered_map and item_to_modify needs to be removed
                task* new_task = item_to_modify->second;

                tasks->insert(make_pair(hash<string> {}(new_task->get_description()), new_task));

                // erase the previous version of the task
                tasks->erase(item_to_modify);
                cout << endl;
                cout << "Description renamed" << endl;
                cout << endl;
            }
            break;
            case 3:
                // get input from stdin and if true returned then valid input given
                if(get_from_stdin<float>("Reset time allocated: ", f_data) == false)
                {
                    cout << endl;
                    cout << "Invalid input given" << endl;
                    cout << endl;
                }
                else
                {
                    // modify time allocated to new time allocated
                    bool success = item_to_modify->second->set_time_allocated(f_data);
                    // check to see if the time_allocated was successful or not
                    if(success == true)
                    {
                        cout << endl;
                        cout << "Time allocated reset" << endl;
                        cout << endl;
                    }
                    else
                    {
                        cout << endl;
                        cout << "Time cannot be negative, therefore not set" << endl;
                        cout << endl;
                    }
                }
                break;
            case 4:
                // reset due_date
                cout << "Reset due date: ";
                getline(cin, s_data);
                // modifiy due date to new due date
                item_to_modify->second->get_due_date()->set_date(s_data);
                cout << endl;
                cout << "Due date reset" << endl;
                cout << endl;
                break;
            case 5:
                exit = true;
                cout << "Going back ..." << endl;
                cout << endl;
                break;
            default:
                cout << "Option does not exist" << endl;
                cout << endl;
                break;
        }
    }
}

// this will be used to load the tasks from disk
void stage::load_tasks(void)
{
    // create string which holds file name
    string file_name = "." + this->stage_name + ".data";

    // open in reading mode
    ifstream stage_file(file_name, ios_base::in);

    // if the file did not open then exit method and give appropriate message
    if(stage_file.is_open() == false)
    {
        string error_message = "No saved data for ";
        cout << "***" << error_message << this->stage_name << "***" << endl;
        return;
    }

    task* new_task = nullptr;

    try
    {
        while(true)
        {
            // create a new instance of task
            new_task = new task();

            // holds the data read from the file
            string s_data;

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

            // holds the converted string read from file
            float f_data {0.0};

            // get time_allocated
            getline(stage_file, s_data);

            // convert string to float
            f_data = stof(s_data);

            // set time_allocated
            new_task->set_time_allocated(f_data);

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

            tasks->insert(make_pair(hash<string> {}(new_task->get_description()), new_task));
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
void stage::save_tasks(void)
{
    // create string which holds file name
    string file_name = "." + this->stage_name + ".data";

    // open in writing mode
    ofstream stage_file(file_name, ios_base::out);

    // if the file did not open then exit method and give appropriate message
    if(stage_file.is_open() == false)
    {
        cerr << "Error in opening file to save" << endl;
        return;
    }

    // iterate through the tasks and save each task
    // format to save
    /*
        topic
        description
        time_allocated
        time_taken
        due_date - value not pointer
    */

    for(unordered_map<size_t, task*>::const_iterator it = tasks->begin(); it != tasks->end(); it++)
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

// print a table edge with a specific character
void stage::print_table_edge(const char character, const unsigned short horizontal_line_length)
{
    for(unsigned short i = 0; i < horizontal_line_length; i++)
    {
        cout << character;
    }
    // print a new line
    cout << endl;
}

// print a single task
void stage::print_task(unordered_map<size_t, task*>::const_iterator current_task)
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

    // print time_taken
    cout << "Time Taken: " << current_task->second->get_time_taken() << endl;

    // print -------------
    print_table_edge('-', horizontal_line_length);

    // print due_date
    cout << "Due Date: " << current_task->second->get_due_date()->get_date() << endl;

    // horizontal =================== for ammount specficed by horizontal line
    print_table_edge('=', horizontal_line_length);
}

// print all tasks
void stage::print_all_tasks(void)
{
    // print border
    print_table_edge('*', 50);

    // print stage in upper case
    for(auto& c: this->stage_name)
    {
        cout << char(c ^ ' ');
    }
    cout << endl;

    // print another border
    print_table_edge('*', 50);

    for(unordered_map<size_t, task*>::const_iterator it = tasks->begin(); it != tasks->end(); it++)
    {
        cout << endl;
        print_task(it);
    }
    cout << endl;
    cout << endl;
    cout << endl;
}
// print based on topic
void stage::print_specific_topic(void)
{
    string topic;

    // cin.ignore();
    cout << "Enter the topic: ";
    getline(cin, topic);

    cout << endl;

    // print border
    print_table_edge('*', 50);

    // print stage in upper case
    for(auto& c: this->stage_name)
    {
        cout << char(c ^ ' ');
    }
    cout << endl;

    // print another border
    print_table_edge('*', 50);

    // hold flag
    bool exists = false;

    for(unordered_map<size_t, task*>::const_iterator it = tasks->begin(); it != tasks->end(); it++)
    {
        // if the topic matches print
        if(it->second->get_topic() == topic)
        {
            cout << endl;
            print_task(it);
            exists = true;
        }
    }

    // there were no tasks with specified topic
    if(exists == false)
    {
        cout << "No tasks found with specified topic" << endl;
        print_table_edge('=', 50);
        cout << endl;
        cout << endl;
        cout << endl;
    }
    else
    {
        cout << endl;
        cout << endl;
        cout << endl;
    }
}

// print based on due date
void stage::print_specific_due_date(void)
{
    string due_date;

    // cin.ignore();
    cout << "Enter due date: ";
    getline(cin, due_date);

    cout << endl;

    // print border
    print_table_edge('*', 50);

    // print stage in upper case
    for(auto& c: this->stage_name)
    {
        cout << char(c ^ ' ');
    }
    cout << endl;

    // print another border
    print_table_edge('*', 50);

    // hold flag
    bool exists = false;

    for(unordered_map<size_t, task*>::const_iterator it = tasks->begin(); it != tasks->end(); it++)
    {
        // if the due date matches print
        if(it->second->get_due_date()->get_date() == due_date)
        {
            cout << endl;
            print_task(it);
            exists = true;
        }
    }

    // there were no tasks with specified topic
    if(exists == false)
    {
        cout << "No tasks found with specified due date" << endl;
        print_table_edge('=', 50);
        cout << endl;
        cout << endl;
        cout << endl;
    }
    else
    {
        cout << endl;
        cout << endl;
        cout << endl;
    }
}

// print based on time allocted
void stage::print_specific_time_allocated(void)
{
    float time_allocated {0.0};

    // get input from stdin and if true returned then valid input given
    if(get_from_stdin<float>("Enter time allocated: ", time_allocated) == false)
    {
        cout << "Invalid input given" << endl;
        cout << endl;
        return;
    }

    cout << endl;

    // print border
    print_table_edge('*', 50);

    // print stage in upper case
    for(auto& c: this->stage_name)
    {
        cout << char(c ^ ' ');
    }
    cout << endl;

    // print another border
    print_table_edge('*', 50);

    // hold flag
    bool exists = false;

    for(unordered_map<size_t, task*>::const_iterator it = tasks->begin(); it != tasks->end(); it++)
    {
        // if the topic matches print
        if(it->second->get_time_allocated() == time_allocated)
        {
            cout << endl;
            print_task(it);
            exists = true;
        }
    }

    // there were no tasks with specified topic
    if(exists == false)
    {
        cout << "No tasks found with specified time allocated" << endl;
        print_table_edge('=', 50);
        cout << endl;
        cout << endl;
        cout << endl;
    }
    else
    {
        cout << endl;
        cout << endl;
        cout << endl;
    }
}

// print based on ID
void stage::print_id(void)
{
    size_t id {0};

    // get input from stdin and if true returned then valid input given
    if(get_from_stdin<size_t>("Enter ID: ", id) == false)
    {
        cout << "Invalid input given" << endl;
        cout << endl;
        return;
    }

    cout << endl;

    // print border
    print_table_edge('*', 50);

    // print stage in upper case
    for(auto& c: this->stage_name)
    {
        cout << char(c ^ ' ');
    }
    cout << endl;

    // print another border
    print_table_edge('*', 50);

    // hold flag
    bool exists = false;

    for(unordered_map<size_t, task*>::const_iterator it = tasks->begin(); it != tasks->end(); it++)
    {
        // if the topic matches print
        if(it->first == id)
        {
            cout << endl;
            print_task(it);
            exists = true;
        }
    }

    // there were no tasks with specified topic
    if(exists == false)
    {
        cout << "No tasks found with specified ID" << endl;
        print_table_edge('=', 50);
        cout << endl;
        cout << endl;
        cout << endl;
    }
    else
    {
        cout << endl;
        cout << endl;
        cout << endl;
    }
}

// method for printing all print options available and printing
void stage::print(void)
{
    bool exit = false;

    while(exit == false)
    {
        int choice {0};
        cout << "**********Print Menu**********" << endl;
        cout << "1) Print All" << endl;
        cout << "2) Print topic" << endl;
        cout << "3) Print due date" << endl;
        cout << "4) Print time allocated" << endl;
        cout << "5) Print ID" << endl;
        cout << "6) Go Back" << endl;
        cout << "******************************\n" << endl;

        // get input from stdin and if true returned then valid input given
        get_from_stdin<int>("Enter choice: ", choice);

        cout << endl;

        switch(choice)
        {
            case 1:
                print_all_tasks();
                break;
            case 2:
                print_specific_topic();
                break;
            case 3:
                print_specific_due_date();
                break;
            case 4:
                print_specific_time_allocated();
                break;
            case 5:
                print_id();
                break;
            case 6:
                exit = true;
                cout << "Going back ..." << endl;
                cout << endl;
                break;
            default:
                cout << "Choice does not exist" << endl;
                cout << endl;
                break;
        }
    }
}

// check to see if the passed id exist in the tasks or not
unordered_map<size_t, task*>::const_iterator stage::find_id(size_t id)
{
    return tasks->find(id);
}

// accessors

// get stage
string stage::get_stage(void)
{
    return this->stage_name;
}

// get tasks pointer
unordered_map<size_t, task*>* stage::get_tasks(void)
{
    return this->tasks;
}

// destructor
stage::~stage()
{
    for(auto it = tasks->begin(); it != tasks->end(); it++)
    {
        delete it->second;
    }

    delete tasks;
}
