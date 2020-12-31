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

        // print menu for current menu and perform action per user request
        virtual void menu(void) override;

        // destructor
        ~Today();

};

#endif