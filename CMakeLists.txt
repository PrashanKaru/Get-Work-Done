# set the minimum required cmake version
# this should be the cmake installed on machine
cmake_minimum_required(VERSION 3.13.4)

# create a varaible which holds the name of the project, which will be used later
# doing this will allow the name to be changed in one place instead of many places
set(this get_work_done)

# set the name of PROJECT_NAME to ${this} (i.e. testing_example)
# setting language-name CXX means CPP
project(${this} CXX)

# set C++ standard to C++14
set(CMAKE_CXX_STANDARD 14)

# lots of warnings and all warnings as 
add_compile_options(-Wall -Wextra -pedantic -Werror)

# set headers variable to all the header paths from root of project
# set(headers include/my_math.h)
include_directories(include)

# set sources variable to all the source paths from root of project
set(src
    src/application.cpp
    src/Backlog.cpp
    src/Date.cpp
    src/Done.cpp
    src/input.cpp
    src/main.cpp
    src/Ongoing.cpp
    src/Stage.cpp
    src/Task.cpp
    src/Today.cpp
)

add_executable(${this} ${src})

include(GNUInstallDirs)

install(TARGETS ${this}
    DESTINATION ${CMAKE_INSTALL_BINDIR})

