// standard include files
#include <iostream>
#include <cstdlib>

// personal include files
#include "application.h"
#include "Today.h"
#include "Ongoing.h"
#include "Backlog.h"
#include "Done.h"

// constructor 
application::application():
num_of_stages(4)
{
    // created a array of pointers on the heap and store address in stages
    try
    {
        stages = new Stage * [num_of_stages];
    }
    catch(const bad_alloc & exp)
    {
        cerr << "Cannot allocate memory for stages, out of memory" << endl;
        // exit program since not enough memory
        exit(EXIT_FAILURE);
    }
    
    try
    {
        stages[0] = new Today();
    }
    catch(const bad_alloc & exp)
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
    catch(const bad_alloc & exp)
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
    catch(const bad_alloc & exp)
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
    catch(const bad_alloc & exp)
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

    // main program loop
    while(exit == false)
    {
        cout << "Menu" << endl;
        cout << "1) Stage" << endl;
        cout << "2) Transfer task" << endl;
        cout << "3) Print all stages" << endl;
        cout << "4) Exit" << endl;
        cin >> choice;

        switch(choice)
        {
            case 1:
                cout << "Choose Stage" << endl;
                cout << "1) Today" << endl;
                cout << "2) Ongoing" << endl;
                cout << "3) Backlog" << endl;
                cout << "4) Done" << endl;
                cout << "5) Go back" << endl;
                cout << "Stage: ";
                cin >> choice;

                // check if choice is between and including 1 and 4
                if(choice >= 1 && choice <= 4)
                {
                    stages[choice - 1]->menu();
                }
                else if(choice == 5)
                {
                    cout << "Go back ..." << endl;
                }
                else
                {
                    cout << "Choice does not exist" << endl;
                }            
                break;
            case 2:
                transfer_task();
                break;
            case 3:
                // print all tasks in each stage
                for(int i = 0; i < num_of_stages; i++)
                {
                    cout << stages[i]->get_stage() << endl;
                    stages[i]->print_all_tasks();
                }
                break;
            case 4:
                exit = true;
                break;
            default:
                cout << "Invalid choice" << endl;
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
    cout << "Stages" << endl;
    int choice {1};
    for(auto & i:stages_in_app)
    {
        // print number
        cout << choice;
        // print bracket and the name of stage
        cout << ") " + i << endl;
        choice++;
    }

    int stage_limit {1};
    int from_stage {0};
    int to_stage {0};
    
    cout << "Enter stage to transfer from: ";
    cin >> from_stage;
    cout << "Enter stage to transfer to: ";
    cin >> to_stage;

    // subtract to later compare with index
    from_stage--;
    to_stage--;
    
    // compare to see if the stages are the same, if so print error message and return
    if(from_stage == to_stage)
    {
        cout << "Cannot transfer to same stage" << endl;
        return;
    }
    else if(from_stage == num_of_stages - 1)    // if the Stage is Done then cannot transfer from it
    {
        cout << "Cannot transfer from Done" << endl;
        return;
    }

    // get ID of task to remove
    size_t id {0};
    cout << "Enter ID of task to transfer from " + stages_in_app[from_stage] + " to " + stages_in_app[to_stage] << endl;
    cin >> id;

    // check to see if the key exists in the map
    unordered_map<size_t, Task*>::const_iterator item_to_remove = stages[from_stage]->find_id(id);

    if(item_to_remove == stages[from_stage]->get_tasks()->end())
    {
        cerr << "Task does not exist" << endl;
        return;
    }

    // get the time allocated for current task
    float time_allocated = item_to_remove->second->get_time_allocated();

    // check if to_stage is today or ongoing and if so first check to see if the new addition of task will be greater than max limit for both stages and if so exit else add task

    // check to see if to_stage is less than or equal to stage_limit
    // if so, indicates that the stage is either Today or Ongoing
    if(to_stage <= stage_limit)
    {
        // create a static cast Ongoing*
        Ongoing * a_ongoing_stage = static_cast<Ongoing *> (stages[to_stage]);

        // check to see if the time_allocated and current_allocated time summed together is greater than the max_allocated_time, if so max_allocated_time does not add this task and exit
        if(time_allocated + a_ongoing_stage->get_current_allocated_time() > a_ongoing_stage->get_max_allocated_time())
        {
            cout << "Current task will exceed maximum allocated time" << endl;
            return;
        }
    }

    // transfer the task from this Stage to dest Stage

    // therefore insert task in dest Stage and erase from this stage
    stages[to_stage]->insert_task(item_to_remove->first, item_to_remove->second);

    // erase using const_iterator from earlier
    stages[from_stage]->get_tasks()->erase(item_to_remove);

    // check if from_stage is today or ongoing
    if(from_stage <= stage_limit)   // Today or Ongoing
    {
        // perform static cast
        Ongoing * a_ongoing_stage = static_cast<Ongoing *> (stages[from_stage]);
        // update the current_allocated_time 
        // since the task was transfered from Today or Ongoing, the current_allocated_time needs to be decreased
        a_ongoing_stage->decrease_current_allocated_time(time_allocated);
    }
    
    // check if to_stage is today or ongoing
    if(to_stage <= stage_limit)   // today
    {
        // perform static cast
        Ongoing * a_ongoing_stage = static_cast<Ongoing *> (stages[to_stage]);
        // update the current_allocated_time 
        // since the task was transfered to Today or Ongoing, the current_allocated_time needs to be increased
        a_ongoing_stage->increase_current_allocated_time(time_allocated);
    }
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
    delete [] stages;
}