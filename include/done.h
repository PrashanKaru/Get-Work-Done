#ifndef _DONE_H_
#define _DONE_H_

// standard include files

// personal include files
#include "stage.h"

class done: public stage
{
  public:
    // constructor
    done();
    // methods

    // remove task - override
    // this overrided method should have no functionality
    virtual void remove_task(void) override final;

    // modify task
    // this overrided method should have no functionality
    virtual void modify_task(void) override final;

    // print menu for current menu and perform action per user request
    virtual void menu(void) override final;

    // destructor
    virtual ~done();

  private:
};

#endif
