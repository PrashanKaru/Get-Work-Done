#ifndef _APPLICATION_H_
#define _APPLICATION_H_

// standard C++ include files
#include <vector>

// project provided include files
#include "stage.h"

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
    stage** stages;
    unsigned short num_of_stages;
    vector<string> stages_in_app;
};

#endif
