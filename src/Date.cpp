// standard include files
#include <iostream>

// own include files
#include "Date.h"

// constructor - no fields as parameters therefore set to 1
Date::Date():
Date(1, 1, 1)
{

}

// constructor - call when loading from file
Date::Date(unsigned short day, unsigned short month, unsigned short year):
day(day), month(month), year(year)
{

}

// setter for date 
void Date::set_date_stdin(void)
{
    // this will hold the different values that will be used to set the fields
    unsigned short value {0};

    // get day
    get_value("Enter day: ", "Error, please enter a valid day between 1 and 31", 1, 31, value);

    // set the day
    this->day = value;

    // get month
    get_value("Enter month: ", "Error, please enter a valid month between 1 and 12", 1, 12, value);

    // set the month
    this->month = value;

    // get month
    get_value("Enter year: ", " ", 0, 65535, value);

    // set the year
    this->year = value;
    
}

string Date::get_date(void)
{
    return to_string(this->day) + "/" + to_string(this->month) + "/" + to_string(this->year);
}

void Date::get_value(string user_prompt, string error_message, unsigned short min, unsigned short max, unsigned short & value)
{
    // ask user to enter a number
    cout << user_prompt;
    cin >> value;

    while(value < min || value > max)
    {
        // A valid input has not been given, therefore, print error message to ask user to print a valid input
        cout << error_message << endl;
        // get user to enter value again
        cout << user_prompt;
        cin >> value;
    }
}
