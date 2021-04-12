# Get Work Done

The aim of this project is to help people get work done, hence the name get_work_done. 

The application has 4 stages, Backlog, Ongoing, Today and Done. 

## Backlog 

This stage contains all the tasks that needs to be completed. This is the stage where a task is also inserted and the details of the task.

## Ongoing 

This stage is designed such that you only focus on a selected few tasks from Backlog for the next 'x' number of hours, where 'x' is a value that can be set by the user.

## Today 

This stage is designed such that you only focus on completing a selected number of tasks from Ongoing.

## Done 

The completed tasks will be transferred to this stage. It will allow the user to see how long they intally suggested to complete a specific task and how long it actually took them so that they can learn to make better predictions in the future.

Currently the application will help people have a structure when it comes to getting their work done. However, this functionality is not the end goal of this project. The end goal is to design a machine learning algorithm that will give a more appropropriate estimated time as to how long it will take to complete the task. This will allow one to better plan their days and get their work done. 


## Language used in this project

The code is written in C++14 only.

The machine learning ascpect will involve Python intially but the final implmentation will be in C++, possibly using the Shark machine learning library or the mlpack machine learning library. 

## Current interface of application and the future

Currently the application only works on command line. However, the future aim is to make it a GUI application using Qt.

## Installation

**Note: Currently this application can only be installed on Linux. Support for Windows and MacOS will come soon.**

```
mkdir build
cd build
cmake ..
make 
sudo make install
```

## Testing

Currently the code has been tested on Debian 10 (buster) using g++ (v8.3.0) and all tests have been successful. 

**Cannot guarentee it will work on other configurations, so please use the software at your own risk.**
