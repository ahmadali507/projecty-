#include<iostream>
using namespace std;

#include"test1.h"

void function2 (){
    
    function1("from header file 2");
    cout << "this is function 2" << endl;

}