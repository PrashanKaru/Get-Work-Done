#ifndef _DATE_H_
#define _DATE_H_

// standard C++ include files
#include <string>

using namespace std;

class date
{
  public:
    // constructors
    // call when creating a new task only
    date();
    // call when loading from file
    date(unsigned short day, unsigned short month, unsigned short year);

    // accessors
    // setter for date
    void set_date_stdin(void);

    // setter for date
    void set_date(string& date);

    // getter for date
    string get_date(void);

  private:
    // methods
    void get_value(string user_prompt, string error_message, unsigned short min, unsigned short max,
                   unsigned short& value);
    // fields
    unsigned short day;
    unsigned short month;
    unsigned short year;
};

#endif