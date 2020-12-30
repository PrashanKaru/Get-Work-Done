// standard include files
#include <iostream>

// own include files
#include "Stage.h"

using namespace std;

int main(void)
{
    Stage * current = new Stage("current");
    Stage * ongoing = new Stage("ongoing");

    bool exit = false;
    int choice = 0;

    while(exit == false)
    {
        cout << "Menu" << endl;
        cout << "1) Insert task" << endl;
        cout << "2) Transfer task" << endl;
        cout << "3) Print" << endl;
        cout << "4) Save tasks" << endl;
        cout << "5) Load tasks" << endl;
        cout << "6) Modify tasks" << endl;
        cout << "7) Exit" << endl;
        cin >> choice;
        // to ignore the \n that is present due to cin so that getline won't fail
        cin.ignore();

        switch(choice)
        {
            case 1:
                current->insert_task();
                break;
            case 2:
            {
                size_t ID = 0;
                cout << "Enter ID to remove" << endl;
                cin >> ID;
                current->transfer_task(*ongoing, ID);
                cout << "printing all contents of ongoing" << endl;
                ongoing->print_all_tasks();
            }
                break;
            case 3:
                cout << "Print Menu" << endl;
                cout << "1) Print All" << endl;
                cout << "2) Print topic" << endl;
                cout << "3) Print due date" << endl;
                cout << "4) Print time allocated" << endl;
                cout << "5) Print ID" << endl;
                cout << "6) Back" << endl;
                cout << "Enter choice: ";
                cin >> choice;
                switch(choice)
                {
                    case 1:
                        current->print_all_tasks();
                        break;
                    case 2:
                    {
                        string topic;
                        cout << "Enter topic: ";
                        cin >> topic;
                        current->print_specific_topic(topic);
                    }
                        break;
                    case 3:
                    {
                        string due_date;
                        cout << "Enter due date: ";
                        cin >> due_date;
                        current->print_specific_due_date(due_date);
                    }
                        break;
                    case 4:
                    {
                        float time_allocated {0.0};
                        cout << "Enter time allocated: ";
                        cin >> time_allocated;
                        current->print_specific_time_allocated(time_allocated);
                    }
                        break;
                    case 5:
                    {
                        size_t ID;
                        cout << "Enter ID: ";
                        cin >> ID;
                        current->print_ID(ID);
                    }
                        break;
                    case 6:
                        cout << "Going back ..." << endl;
                        break;
                    default:
                        break;
                }
                break;
            case 4:
                current->save_tasks();
                break;
            case 5:
                current->load_tasks();
                break;
            case 6:
            {
                size_t id {0};
                cout << "Task to modify: ";
                cin >> id;
                current->modify_task(id);
            }
                break;
            case 7:
                exit = true;
                break;
            default:
                cout << "Invalid choice" << endl;
                break;
        }
    }
    delete ongoing;
    delete current;
    return 0;
}