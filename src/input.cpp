#ifndef _INPUT_H_
#define _INPUT_H_

// standard C++ include files
#include <iostream>
#include <string>

using namespace std;

template<typename T> bool get_from_stdin(string prompt, T& src)
{
    cout << prompt;
    cin >> src;

    // input type is not valid for type specified
    if(cin.fail() == true)
    {
        // clear error flag
        cin.clear();
        // ignore 100 characters or if \n comes before 100 characters stop ignoring
        cin.ignore(100, '\n');
        return false;
    }
    cin.ignore(100, '\n');
    return true;
}

#endif
