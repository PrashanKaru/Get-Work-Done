#ifndef _APPLICATION_H_
#define _APPLICATION_H_

// standard include files
#include <vector>

// personal include files
#include "Stage.h"

class application
{
    public:
        // constructor 
        application();

        // method

        // run the application
        void run(void);

        // transfer_task
        void transfer_task(void);

        // destructor
        ~application();
    private:
        // this will hold all the stages in the application
        Stage ** stages;
        unsigned short num_of_stages;
        vector<string> stages_in_app;
};

#endif