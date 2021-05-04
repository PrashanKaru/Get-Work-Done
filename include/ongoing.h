#ifndef _ONGOING_H_
#define _ONGOING_H_

// project provided include files
#include "stage.h"

class ongoing: public stage
{
  public:
    // constructor

    // no parameter constructor
    ongoing();

    // constructor with parameter that allows setting the stage field from stage Class
    ongoing(string src);

    // methods

    // this will be used to load the tasks from disk
    virtual void load_tasks(void) override;

    // this will be used to save the tasks to disk
    virtual void save_tasks(void) override;

    // print menu for current menu and perform action per user request
    virtual void menu(void) override;

    // increase the current_allocated_time with the value provided as a parameter to the method
    void increase_current_allocated_time(float time_allocated);

    // decrease the current_allocated_time with the value provided as a parameter to the method
    void decrease_current_allocated_time(float time_allocated);

    // accessors

    // setter max_allocated_time
    bool set_max_allocated_time(float& max_allocated_time);

    // getter max_allocated_time
    float get_max_allocated_time(void);

    // getter current_allocated_time
    float get_current_allocated_time(void);

    // destructor
    virtual ~ongoing();

  private:
    // this will hold the maximum allocated time that all the task's time allocated can add up to
    float max_allocated_time;
    // this will hold the current allocated time that all the task's time allocated add up to
    float current_allocated_time;
};

#endif
