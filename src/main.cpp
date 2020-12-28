// standard include files
#include <iostream>

// own include files
#include "Date.h"

using namespace std;

int main(void)
{
    Date date_obj(5, 5, 5);
    // date_obj.set_date_stdin();
    cout << date_obj.get_date() << endl;
    return 0;
}