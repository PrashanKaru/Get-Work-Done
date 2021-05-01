// standard include files
#include <iostream>

// own include files
#include "../include/date.h"
#include "input.cpp"

// constructor - no fields as parameters therefore set to 1
date::date(): date(1, 1, 1)
{
}

// constructor - call when loading from file
date::date(unsigned short day, unsigned short month, unsigned short year): day(day), month(month), year(year)
{
}

// setter for date
void date::set_date_stdin(void)
{
    // this will hold the different values that will be used to set the fields
    unsigned short value {0};

    // get day
    get_value("Enter day: ", "Error, a valid day is between 1 and 31", 1, 31, value);

    // set the day
    this->day = value;

    cout << endl;

    // get month
    get_value("Enter month: ", "Error, a valid month is between 1 and 12", 1, 12, value);

    // set the month
    this->month = value;

    cout << endl;

    // get month
    get_value("Enter year: ", "Error, valid year has to be 2021 or later", 2021, 65535, value);

    // set the year
    this->year = value;
}

string date::get_date(void)
{
    return to_string(this->day) + "/" + to_string(this->month) + "/" + to_string(this->year);
}

// setter for date
void date::set_date(string& date)
{
    sscanf(date.c_str(), "%hu/%hu/%hu", &this->day, &this->month, &this->year);
}

void date::get_value(string user_prompt, string error_message, unsigned short min, unsigned short max,
                     unsigned short& value)
{
    bool success = false;

    // until a valid value has been given stay in loop
    while(success == false)
    {
        // get value until valid input is given
        while(get_from_stdin<unsigned short>(user_prompt, value) == false)
        {
            cout << endl;
            cout << "Invalid input given" << endl;
            cout << "Try again" << endl;
            cout << endl;
        }

        // if value is is not within bounds, the value needs to be entered again
        if(value < min || value > max)
        {
            cout << endl;
            // A valid input has not been given, therefore, print error message to ask user to print a valid input
            cout << error_message << endl;
            cout << "Try again" << endl;
            cout << endl;
        }
        else
        {
            success = true;
        }
    }
}
