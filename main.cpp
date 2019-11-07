/*
* Sarah Monthofer
* monthofer@chapman.edu
* 2317035
* CPSC 350 - Assignment 4
*
* Description: read from file path sent in through comman line and move students
          from the queue to the windows availble
*/

#include <iostream>
#include <string>
#include <fstream>
#include "Simulation.h"

using namespace std;
int main(int argc, char** argv) {
  // create an Simulation student object
  Simulation s;

  // no file sent in command line
  if (argc != 2)
  {
    cout << "ERROR - INVALID NUMBER OR ARGUMENTS" << endl;
    exit(1);
  }

  // file sent in command line
  else if (argc >= 2) {
    // variables to track time passing and windows open
    int openWindows;
    int currentTime;
    bool keepRunning = true;
    string file = argv[1];

    if(s.openFile(file)) {
      while (keepRunning) {
        // run while there is still input from argv[1]
        if (s.studentQueue.isEmpty()) {
          keepRunning = false;
        }

        // remove people waiting in queue and place them at windows until all windows are full
        for (int i = 0; i < s.totalWindows; ++i) {
          if (s.windowArray[i]->windowTime < 1) {
            if (!s.studentQueue.isEmpty()) {
              Students* student = s.studentQueue.frontNode(); // pointer to front node in queue
              if (student->entryTime <= currentTime) {
                if (s.windowArray[i]->idleTime > 0) {
                  s.idleStats.enqueue(s.windowArray[i]->idleTime);
                }
                // add student to windowArray and remove them from wait queue
                s.windowArray[i] = s.studentQueue.dequeue();
                s.waitStats.enqueue(s.windowArray[i]->queueTime);
              }
            }
          }
        }
        currentTime++;
        s.trackTime(currentTime);
      }

      // if there are not enough students to fill the windows during the Simulation
      // then these windows stay idle
      for(int i = 0; i < s.totalWindows; ++i) {
        if(s.windowArray[i]->idleTime > 0) {
            s.idleStats.enqueue(s.windowArray[i]->idleTime);
        }
      }

      // print calculations
      cout << "Simulation Statistics" << endl;
      cout << endl;
      cout << "Mean Student Wait Time: " << s.meanWaitTime() << endl;
      cout << "Median Wait Time: " << s.medianWaitTime() << endl;
      cout << "Longest Student Wait Time: " << s.longestWaitTime() << endl;
      cout << "Number of Students Waiting over 10 Minutes: " << s.studentsWaitOverTen() << endl;
      cout << "Mean Window Idle Time: " << s.meanIdleTime() << endl;
      cout << "Longest Window Idle Time: " << s.longestIdleTime() << endl;
      cout << "Number of Windows Idle over 5 Minutes: " << s.windowIdleOverFive() << endl;
    }
  }
}
