/*
* Sarah Monthofer
* monthofer@chapman.edu
* 2317035
* CPSC 350 - Assignment 4
*
* Description: this file contians the initial setup for each student
*/

#include <iostream>
#include "Students.h"

using namespace std;

// students info deafult constructor
Students::Students() {
  windowTime = 0;
  entryTime = 0;
  queueTime = 0;
  idleTime = 0;
}

// students info constructor
Students::Students(int time1, int entry) {
  windowTime = time1;
  entryTime = entry;
  idleTime = 0;
  queueTime = 0;
}

// students destructor
Students::~Students() {

}
