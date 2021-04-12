#ifndef _DATE_H_
#define _DATE_H_

#include <string>

using namespace std;

class Date
{
    public:
        // constructors
        // call when creating a new task only
        Date(); 
        // call when loading from file
        Date(unsigned short day, unsigned short month, unsigned short year); 
        
        // accessors
        // setter for date 
        void set_date_stdin(void);

        // setter for date
        void set_date(string & date);

        // getter for date
        string get_date(void);
    private:
        // methods
        void get_value(string user_prompt, string error_message, unsigned short min, unsigned short max, unsigned short & value);
        // fields
        unsigned short day;
        unsigned short month;
        unsigned short year;
};

#endif