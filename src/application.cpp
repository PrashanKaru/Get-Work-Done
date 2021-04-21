// standard include files
#include <cstdlib>
#include <iostream>

// personal include files
#include "Backlog.h"
#include "Done.h"
#include "Ongoing.h"
#include "Today.h"
#include "application.h"
#include "input.cpp"

// constructor
application::application():
    num_of_stages(4) // set the number of stages to be 4 since there are 4 stages, today, ongoing, backlog & done
{
    // created a array of pointers on the heap and store address in stages
    try
    {
        stages = new Stage*[num_of_stages];
    }
    catch(const bad_alloc& exp)
    {
        cerr << "Cannot allocate memory for stages, out of memory" << endl;
        // exit program since not enough memory
        exit(EXIT_FAILURE);
    }

    try
    {
        stages[0] = new Today();
    }
    catch(const bad_alloc& exp)
    {
        cerr << "Cannot allocate memory for Today stage, out of memory" << endl;
        // delete previously allocated memory
        delete stages;
        // exit program since not enough memory
        exit(EXIT_FAILURE);
    }

    try
    {
        stages[1] = new Ongoing();
    }
    catch(const bad_alloc& exp)
    {
        cerr << "Cannot allocate memory for Ongoing stage, out of memory" << endl;
        // delete previously allocated memory
        delete stages[0];
        delete stages;
        // exit program since not enough memory
        exit(EXIT_FAILURE);
    }

    try
    {
        stages[2] = new Backlog();
    }
    catch(const bad_alloc& exp)
    {
        cerr << "Cannot allocate memory for Backlog stage, out of memory" << endl;
        // delete previously allocated memory
        delete stages[0];
        delete stages[1];
        delete stages;
        // exit program since not enough memory
        exit(EXIT_FAILURE);
    }

    try
    {
        stages[3] = new Done();
    }
    catch(const bad_alloc& exp)
    {
        cerr << "Cannot allocate memory for Done stage, out of memory" << endl;
        // delete previously allocated memory
        delete stages[0];
        delete stages[1];
        delete stages[2];
        delete stages;
        // exit program since not enough memory
        exit(EXIT_FAILURE);
    }

    // add all the stages if all the memory was allocated successfully
    stages_in_app.push_back("Today");
    stages_in_app.push_back("Ongoing");
    stages_in_app.push_back("Backlog");
    stages_in_app.push_back("Done");
}

// method

// run the application
void application::run(void)
{
    // load all data from disk to memory
    for(int i = 0; i < num_of_stages; i++)
    {
        stages[i]->load_tasks();
    }

    // used as flag that will indicate when to exit the program
    bool exit {false};
    // used to hold the choice from the user via stdin
    int choice {0};

    // use to clear variable
    // char in {0};

    // placed for visual purpose
    cout << endl;

    // main program loop
    while(exit == false)
    {
        cout << "*********Menu*********" << endl;
        cout << "1) Stage" << endl;
        cout << "2) Transfer task" << endl;
        cout << "3) Set Maximum Allocated Time" << endl;
        cout << "4) Print all stages" << endl;
        cout << "5) Exit" << endl;
        cout << "**********************\n" << endl;

        get_from_stdin<int>("Enter choice: ", choice);

        // placed for visual purpose
        cout << endl;

        switch(choice)
        {
            case 1:
                while(true)
                {
                    cout << "*****Choose Stage*****" << endl;
                    cout << "1) Today" << endl;
                    cout << "2) Ongoing" << endl;
                    cout << "3) Backlog" << endl;
                    cout << "4) Done" << endl;
                    cout << "5) Go back" << endl;
                    cout << "**********************\n" << endl;

                    get_from_stdin<int>("Enter choice: ", choice);

                    // placed for visual purpose
                    cout << endl;

                    // check if choice is between and including 1 and 4
                    if(choice >= 1 && choice <= 4)
                    {
                        stages[choice - 1]->menu();
                    }
                    else if(choice == 5)
                    {
                        cout << "Going back ..." << endl;
                        // placed for visual purpose
                        cout << endl;
                        break;
                    }
                    else
                    {
                        cout << "Choice does not exist" << endl;
                        // placed for visual purpose
                        cout << endl;
                    }
                }
                break;
            case 2:
                transfer_task();
                break;
            case 3:
                cout << "*******Choose Stage*******" << endl;
                cout << "1) Today" << endl;
                cout << "2) Ongoing" << endl;
                cout << "**************************\n" << endl;

                get_from_stdin<int>("Enter choice: ", choice);

                // placed for visual purpose
                cout << endl;

                // check if choice is between and including 1 and 4
                if(choice == 1 || choice == 2)
                {
                    // perform static cast since it is an Ongoing object
                    Ongoing* an_ongoing_stage = static_cast<Ongoing*>(stages[choice - 1]);

                    // print current stats
                    cout << "*********************************************" << endl;
                    cout << "Currently set maximum allocated time is " << an_ongoing_stage->get_max_allocated_time()
                         << endl;
                    cout << "Current allocated time is " << an_ongoing_stage->get_current_allocated_time() << endl;
                    cout << "*********************************************" << endl;
                    cout << endl;

                    // hold data for max ongoing time
                    float new_max_ongoing_time {0.0};

                    // get input from stdin and if true returned then valid input given
                    if(get_from_stdin<float>("Enter new maximum allocated time: ", new_max_ongoing_time) == true)
                    {
                        cout << endl;

                        // check to see if the new_max_ongoing_time is less than current_allocated_time
                        if(new_max_ongoing_time < an_ongoing_stage->get_current_allocated_time())
                        {
                            cout << "Cannot set the maximum allocated time to be less than the current allocated time"
                                 << endl;
                            cout << endl;
                        }
                        else
                        {
                            // since input was valid, try setting the value
                            // if the result of max_allocated_time is less than zero a false is returned as time cannot
                            // be negative
                            if(an_ongoing_stage->set_max_allocated_time(new_max_ongoing_time) == false)
                            {
                                cout << "Maximum allocated time cannot be less than 0" << endl;
                                cout << endl;
                            }
                            else
                            {
                                cout << "Maximum allocated time has successfully been set" << endl;
                                cout << endl;
                            }
                        }
                    }
                    else // else tell user invalid value given. This is for input like "absd"
                    {
                        cout << "Invalid input given" << endl;
                        cout << endl;
                    }
                }
                else
                {
                    cout << "Choice does not exist" << endl;
                    // placed for visual purpose
                    cout << endl;
                }
                break;
            case 4:
                // print all tasks in each stage
                for(int i = 0; i < num_of_stages; i++)
                {
                    // check if there are any tasks in stage and if not print message and move onto next stage
                    if(stages[i]->get_tasks()->empty() == true)
                    {
                        // print border
                        stages[i]->print_table_edge('*', 50);

                        // print stage in upper case
                        for(auto& c: stages[i]->get_stage())
                        {
                            cout << char(c ^ ' ');
                        }
                        cout << endl;

                        // print another border
                        stages[i]->print_table_edge('*', 50);
                        cout << "No tasks in " << stages[i]->get_stage() << endl;
                        stages[i]->print_table_edge('=', 50);
                        cout << endl;
                        cout << endl;
                        cout << endl;
                    }
                    else
                    {
                        // if there are tasks in stage then print all tasks in that stage
                        stages[i]->print_all_tasks();
                    }
                }
                break;
            case 5:
                exit = true;
                cout << "Exiting ..." << endl;
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

    // save all data in memory to disk
    for(int i = 0; i < num_of_stages; i++)
    {
        stages[i]->save_tasks();
    }
}

// transfer_task
void application::transfer_task(void)
{
    // print menu to ask user where to transfer new task to
    cout << "*******Stages*******" << endl;
    int choice {1};
    for(auto& i: stages_in_app)
    {
        // print number
        cout << choice;
        // print bracket and the name of stage
        cout << ") " + i << endl;
        choice++;
    }
    cout << "********************\n" << endl;

    int stage_limit {1};
    int from_stage {0};
    int to_stage {0};

    // get input from stdin and if true returned then valid input given
    if(get_from_stdin<int>("Enter stage to transfer from: ", from_stage) == false)
    {
        cout << endl;
        cout << "Invalid input given, exiting transfer task" << endl;
        cout << endl;
        return;
    }

    // get input from stdin and if true returned then valid input given
    if(get_from_stdin<int>("Enter stage to transfer to: ", to_stage) == false)
    {
        cout << endl;
        cout << "Invalid input given, exiting transfer task" << endl;
        cout << endl;
        return;
    }

    cout << endl;

    // subtract to later compare with index
    from_stage--;
    to_stage--;

    // compare to see if the stages are the same, if so print error message and return
    if(from_stage == to_stage)
    {
        cout << "Cannot transfer to same stage" << endl;
        cout << endl;
        return;
    }
    else if(from_stage == num_of_stages - 1) // if the Stage is Done then cannot transfer from it
    {
        cout << "Cannot transfer from Done" << endl;
        cout << endl;
        return;
    }

    // get ID of task to remove
    size_t id {0};

    // get input from stdin and if true returned then valid input given
    if(get_from_stdin<size_t>("Enter ID of task to transfer from " + stages_in_app[from_stage] + " to " +
                                  stages_in_app[to_stage] + ": ",
                              id) == false)
    {
        cout << endl;
        cout << "Invalid input given, exitting transfer task" << endl;
        cout << endl;
        return;
    }

    cout << endl;

    // check to see if the key exists in the map
    unordered_map<size_t, Task*>::const_iterator item_to_remove = stages[from_stage]->find_id(id);

    if(item_to_remove == stages[from_stage]->get_tasks()->end())
    {
        cout << "Task does not exist" << endl;
        cout << endl;
        return;
    }

    // get the time allocated for current task
    float time_allocated = item_to_remove->second->get_time_allocated();

    // check if to_stage is today or ongoing and if so first check to see if the new addition of task will be greater
    // than max limit for both stages and if so exit else add task

    // check to see if to_stage is less than or equal to stage_limit
    // if so, indicates that the stage is either Today or Ongoing
    if(to_stage <= stage_limit)
    {
        // create a static cast Ongoing*
        Ongoing* a_ongoing_stage = static_cast<Ongoing*>(stages[to_stage]);

        // check to see if the time_allocated and current_allocated time summed together is greater than the
        // max_allocated_time, if so max_allocated_time does not add this task and exit
        if(time_allocated + a_ongoing_stage->get_current_allocated_time() > a_ongoing_stage->get_max_allocated_time())
        {
            cout << "Current task will exceed maximum allocated time" << endl;
            cout << endl;
            return;
        }
    }

    // transfer the task from this Stage to dest Stage

    // therefore insert task in dest Stage and erase from this stage
    stages[to_stage]->insert_task(item_to_remove->first, item_to_remove->second);

    // erase using const_iterator from earlier
    stages[from_stage]->get_tasks()->erase(item_to_remove);

    // check if from_stage is today or ongoing
    if(from_stage <= stage_limit) // Today or Ongoing
    {
        // perform static cast
        Ongoing* a_ongoing_stage = static_cast<Ongoing*>(stages[from_stage]);
        // update the current_allocated_time
        // since the task was transfered from Today or Ongoing, the current_allocated_time needs to be decreased
        a_ongoing_stage->decrease_current_allocated_time(time_allocated);
    }

    // check if to_stage is today or ongoing
    if(to_stage <= stage_limit) // today
    {
        // perform static cast
        Ongoing* a_ongoing_stage = static_cast<Ongoing*>(stages[to_stage]);
        // update the current_allocated_time
        // since the task was transfered to Today or Ongoing, the current_allocated_time needs to be increased
        a_ongoing_stage->increase_current_allocated_time(time_allocated);
    }

    cout << "Successfully transfered task from " << stages_in_app[from_stage] << " to " << stages_in_app[to_stage]
         << endl;
    cout << endl;
}

// destructor
application::~application()
{
    // delete each stage
    delete stages[0];
    delete stages[1];
    delete stages[2];
    delete stages[3];
    // delete stages
    delete[] stages;
}
