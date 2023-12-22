#include <iostream>
#include <string>
using namespace std;

void function1(string str = "")
{

    if (str.length() == 0)
    {
        cout << "this is function 1" << endl;
    }
    else
    {
        cout << str << endl;
    }
}