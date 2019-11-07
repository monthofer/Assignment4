/*
* Sarah Monthofer
* monthofer@chapman.edu
* 2317035
* CPSC 350 - Assignment 4
*
* Description: this file contians the Simulation variables, constructors and
        destructors and calls all the methods needed to calculate
        the simulation statistics
*/

#include <iostream>
#include "Students.h"
#include "GenQueue.h"

using namespace std;
class Simulation {
  private:
    // variables
    int entryTime;
    int timeAtWindow;
    int studentsAtEachTick;
    int medianArrayCount;
    int idleArrayCount; 

  public:
    // variables
    int totalWindows;
    int totalStudents;
    int *medianArray;
    int *idleArray;
    Students* *windowArray;
    GenQueue<Students*> studentQueue;
    GenQueue<int> waitStats;
    GenQueue<int>idleStats;

    // constructors and destructors
    Simulation();
    ~Simulation();

    // setup methods for calculations from input data
    bool openFile(string file);
    bool trackTime(int time1);

    // Simulation calculation method calls
    double meanWaitTime();
    double medianWaitTime();
    int longestWaitTime();
    int studentsWaitOverTen();
    double meanIdleTime();
    int longestIdleTime();
    int windowIdleOverFive();
};
