// standard include files
#include <iostream>

// own include files
#include "Stage.h"

using namespace std;

int main(void)
{
    string stage("current");
    Stage * current = new Stage(stage);

    bool exit = false;
    int choice = 0;

    while(exit == false)
    {
        cout << "Menu" << endl;
        cout << "1) Insert task" << endl;
        cout << "2) Remove task" << endl;
        cout << "3) Print all tasks" << endl;
        cout << "4) Save tasks" << endl;
        cout << "5) Load tasks" << endl;
        cout << "6) Exit" << endl;
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
                current->remove_task(ID);
            }
                break;
            case 3:
                current->print_all_tasks();
                break;
            case 4:
                current->save_tasks();
                break;
            case 5:
                current->load_tasks();
                break;
            case 6:
                exit = true;
                break;
            default:
                cout << "Invalid choice" << endl;
                break;
        }
    }

    delete current;
    return 0;
}