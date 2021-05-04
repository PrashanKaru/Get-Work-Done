#ifndef _BACKLOG_H_
#define _BACKLOG_H_

// project provided include files
#include "stage.h"

class backlog: public stage
{
  public:
    // constructor
    backlog();

    // methods

    // bring the insert_task from Stage class as well
    using stage::insert_task;

    // insert new task from stdin - overloaded insert_task(size_t, task *)
    void insert_task(void);

    // print a single task
    // should print without time taken as ongoing should not have this info
    virtual void print_task(unordered_map<size_t, task*>::const_iterator current_task) override final;

    // print menu for current menu and perform action per user request - no implmentation in base class
    virtual void menu(void) override final;

    // destructor
    virtual ~backlog();

  private:
};

#endif
