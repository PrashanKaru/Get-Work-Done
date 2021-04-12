#ifndef _TODAY_H_
#define _TODAY_H_

// standard include files

// personal include files
#include "Ongoing.h"

class Today : public Ongoing
{
    public:
        // constructor
        Today();

        // methods
        
        // this method will increase the time spent for a specfic ID
        void increase_time_spent(void);

        // print menu for current menu and perform action per user request
        virtual void menu(void) override;

        // destructor
        virtual ~Today();
};

#endif