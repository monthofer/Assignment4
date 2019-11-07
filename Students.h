/*
* Sarah Monthofer
* monthofer@chapman.edu
* 2317035
* CPSC 350 - Assignment 4
*
* Description: this file decalres the student wait variables and
          calls the constructors and destructors
*/

#include <iostream>

using namespace std;

class Students {
  public:
    // time variables
    int windowTime;
    int entryTime;
    int queueTime;
    int idleTime;
    
    // constructors and destructors
    Students();
    Students(int time1, int entry);
    ~Students();
};
