#ifndef _DONE_H_ 
#define _DONE_H_ 

// standard include files 

// personal include files 
#include "Stage.h"

class Done : public Stage
{
    public:
        // constructor
        Done();
        // methods

        // remove task - override
        // this overrided method should have no functionality
        virtual void remove_task(size_t id) override final;

        // modify task
        // this overrided method should have no functionality
        virtual void modify_task(size_t id) override final;
       
        // print menu for current menu and perform action per user request
        virtual void menu(void) override final;

        // destructor
        virtual ~Done();
    private:
};

#endif