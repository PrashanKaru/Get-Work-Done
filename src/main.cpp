// standard include files
#include <iostream>
#include <vector>

// own include files
#include "Stage.h"
#include "Ongoing.h"
#include "Backlog.h"
#include "Done.h"

using namespace std;

// transfer task
void transfer_task(Stage ** src, vector<string> & list_stages, int stage_limit)
{
    // print menu to ask user where to transfer new task to
    cout << "Stages" << endl;
    int choice {1};
    for(auto & i:list_stages)
    {
        // print number
        cout << choice;
        // print bracket and the name of stage
        cout << ") " + i << endl;
        choice++;
    }

    int from_stage {0};
    int to_stage {0};
    
    cout << "Enter stage to transfer from: ";
    cin >> from_stage;
    cout << "Enter stage to transfer to: ";
    cin >> to_stage;
    
    // compare to see if the stages are the same, if so print error message and return
    if(from_stage == to_stage)
    {
        cout << "Cannot transfer to same stage" << endl;
        return;
    }

    // get ID of task to remove
    size_t id {0};
    cout << "Enter ID of task to transfer from " + list_stages[from_stage - 1] + " to " + list_stages[to_stage - 1] << endl;
    cin >> id;

    // check to see if the key exists in the map
    unordered_map<size_t, Task*>::const_iterator item_to_remove = src[from_stage - 1]->find_id(id);

    if(item_to_remove == src[from_stage - 1]->get_tasks()->end())
    {
        cerr << "Task does not exist" << endl;
        return;
    }

    // get the time allocated for current task
    float time_allocated = item_to_remove->second->get_time_allocated();

    // check if to_stage is today or ongoing and if so first check to see if the new addition of task will be greater than max limit for both stages and if so exit else add task

    // check to see if to_stage is less than or equal to stage_limit
    // if so, indicates that the stage is either Today or Ongoing
    if(to_stage -  1 <= stage_limit)
    {
        // create a static cast Ongoing*
        Ongoing * a_ongoing_stage = static_cast<Ongoing *> (src[to_stage - 1]);

        // check to see if the time_allocated and current_allocated time summed together is greater than the max_allocated_time, if so max_allocated_time does not add this task and exit
        if(time_allocated + a_ongoing_stage->get_current_allocated_time() > a_ongoing_stage->get_max_allocated_time())
        {
            cout << "Current task will exceed maximum allocated time" << endl;
            return;
        }
    }

    // transfer the task from this Stage to dest Stage

    // therefore insert task in dest Stage and erase from this stage
    src[to_stage - 1]->insert_task(item_to_remove->first, item_to_remove->second);

    // erase using const_iterator from earlier
    src[from_stage - 1]->get_tasks()->erase(item_to_remove);

    // check if from_stage is today or ongoing
    if(from_stage - 1 <= stage_limit)   // Today or Ongoing
    {
        // perform static cast
        Ongoing * a_ongoing_stage = static_cast<Ongoing *> (src[from_stage - 1]);
        // update the current_allocated_time 
        // since the task was transfered from Today or Ongoing, the current_allocated_time needs to be decreased
        a_ongoing_stage->decrease_current_allocated_time(time_allocated);
    }
    
    // check if to_stage is today or ongoing
    if(to_stage - 1 <= stage_limit)   // today
    {
        // perform static cast
        Ongoing * a_ongoing_stage = static_cast<Ongoing *> (src[to_stage - 1]);
        // update the current_allocated_time 
        // since the task was transfered to Today or Ongoing, the current_allocated_time needs to be increased
        a_ongoing_stage->increase_current_allocated_time(time_allocated);
    }
}

int main(void)
{
    const int current_size = 3;
    Stage ** current = new Stage * [current_size];
    current[0] = new Ongoing(); // Ongoing
    current[1] = new Backlog(); // backlog
    current[2] = new Done();    // done
    
    // load all data from disk to memory
    for(int i = 0; i < current_size; i++)
    {
        current[i]->load_tasks();
    }

    vector<string> list_stages;
    list_stages.push_back("Ongoing");
    list_stages.push_back("Backlog");
    list_stages.push_back("Done");

    bool exit = false;
    int choice = 0;

    string s_data;
    size_t size_t_data {0};

    while(exit == false)
    {
        cout << "Menu" << endl;
        cout << "1) Stage" << endl;
        cout << "2) Print all stages" << endl;
        cout << "3) Transfer task" << endl;
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
                
                switch(choice)
                {
                case 1:
                    cout << "Does not exist yet" << endl;
                    break;
                case 2:
                    current[0]->menu();
                    break;
                case 3:
                    current[1]->menu();
                    break;
                case 4:
                    current[2]->menu();
                    break;
                case 5:
                    cout << "Go back ..." << endl;
                    break;
                default:
                    cout << "Choice does not exist" << endl;
                    break;
                }                
                break;
            case 2:
                // print all tasks in each stage
                for(int i = 0; i < current_size; i++)
                {
                    cout << current[i]->get_stage() << endl;
                    current[i]->print_all_tasks();
                }
                break;
            case 3:
                transfer_task(current, list_stages, 0);
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
    for(int i = 0; i < current_size; i++)
    {
        current[i]->save_tasks();
    }
    
    // delete backlog and done
    delete current[0];
    delete current[1];
    delete current[2];
    // delete current
    delete [] current;
    return 0;
}