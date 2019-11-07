/*
* Sarah Monthofer
* monthofer@chapman.edu
* 2317035
* CPSC 350 - Assignment 4
*
* Description: this file makes all the calculations for Simulation.h methods called
*/

#include <iostream>
#include <fstream>
#include <queue>
#include "Simulation.h"

using namespace std;

// Simulation constructor - sets all values in simulation to starting values
Simulation::Simulation() {
  totalWindows = 0;
  totalStudents = 0;
  entryTime = 0;
  timeAtWindow = 0;
  studentsAtEachTick = 0;
  medianArrayCount = 0;
  idleArrayCount = 0;
}

// Simulation Destructor - deletes all arrays used to store simulation data
Simulation::~Simulation() {
  delete[] medianArray;
  delete[] idleArray;
  delete[] windowArray;
}

// method to open the file and assign its contents to the proper variables needed for the simulation
bool Simulation::openFile(string file) {
    // read from file sent in through command line
    string line;
    int numLines = 0;
    int currLine = 1;
    ifstream inputStream;
    inputStream.open(file.c_str());

    // count the number of lines in the input file
    ifstream in(file);
    std::string str;
    while(std::getline(in, str)) {
      numLines++;
    }

    // read info from the file until end of file
    while(getline(inputStream, line)) {
      // first line in file contians the number of open widows
      if (currLine == 1) {
        // use the variable on the first line - the number of windows open
        // create a windowArray based on this size then call the Student class with initial window data
        totalWindows = atoi(line.c_str());
        windowArray = new Students*[totalWindows];
        for (int i = 0; i < totalWindows; ++i) {
          Students* newStudent = new Students();
          windowArray[i] = newStudent;
        }
        currLine++;
      }

      // any even line in file will be the time the student arrives
      if (currLine % 2 == 0) {
        // read line from file as string and save into entry time
        entryTime = atoi(line.c_str());
        currLine++;
      }

      // if odd line other than first line the line contains the number of students
      // to arrive at the time above
      if ((currLine % 2 == 1) && (currLine != 1)) {
        studentsAtEachTick = atoi(line.c_str());
        currLine++;

        // the lines below will be the amount of time amount of time each above student needs
        for (int i = 0; i < studentsAtEachTick; ++i) {
          getline(inputStream, line);
          timeAtWindow = atoi(line.c_str());
          currLine++;
          totalStudents++;

          // add the new student and the time they require at the window to thier appropriate queue
          Students* newStudent = new Students(timeAtWindow, entryTime);
          studentQueue.enqueue(newStudent);
        }
      }
    }
}

// keep track of time in simulation
bool Simulation::trackTime(int currentTime) {
  // for each tick of the clock add time time to the window time or idle time
  // if the window is occupied or unoccupied
  for (int i = 0; i < totalWindows; ++i) {
    // if a student is occuping a window decrease time
    if (windowArray[i]->windowTime-- > 0) {
      windowArray[i]->windowTime;
    }
    // if a student is not at a window increase idle time
    else {
      windowArray[i]->idleTime++;
    }
  }

  if (!studentQueue.isEmpty()) {
    // point to student stored in front of the student Queue
    ListNode<Students*> *current = studentQueue.front;

    while(current != NULL) {
      if (current->data->entryTime < currentTime) {
        current->data->queueTime += 1;
      }
      current = current->next;
    }
  }
}

// calcualte the mean wait time of students in input file
double Simulation::meanWaitTime() {
  // mean calculation variables
  ListNode<int> *current = waitStats.front;
  double numItems = 0.0;
  double mean = 0.0;
  double sum = 0.0;

  // sum nodes until there are no more by following pointers
  while (current != NULL) {
    sum += current->data;
    current = current->next;
    numItems++;
  }

  // calcualte mean
  mean = (double) (sum / numItems);
  return mean;
}

// calcualte the median wait time of students in input file
double Simulation::medianWaitTime() {
  ListNode<int> *current = waitStats.front;
  medianArray = new int[medianArrayCount];
  int middle;
  double medianWait;
  int temp;

  // count the number of items in the median array
  while(current != NULL) {
    current = current->next;
    medianArrayCount++;
  }

  // follow pointers to next nodes
  for (int i = 0; i < medianArrayCount; ++i) {
    medianArray[i] = current->data;
    current = current->next;
  }

  // sort median array in ascending order
  for (int i = 0; i < medianArrayCount; ++i) {
    for (int j = i + 1; j < medianArrayCount; ++j) {
      if (medianArray[i] > medianArray[j]) {
        temp = medianArray[i];
        medianArray[i] = medianArray[j];
        medianArray[j] = temp;
      }
    }
  }

  // calcualte the median of the now sorted array
  middle = medianArrayCount / 2;
  if (medianArrayCount % 2 == 0) {
    medianWait = ((medianArray[middle] + medianArray[middle + 1]) / 2.0);
  }
  else {
    medianWait = ((medianArray[middle + 0]) / 1.0);
  }

  return medianWait;
}

// calcualte longest wait time
int Simulation::longestWaitTime() {
  if (medianArrayCount > 0) {
    return medianArray[medianArrayCount - 1];
  }
  else {
    return 0;
  }
}

// calculate the number of sudents who have to wait for a window for more than 10 minutes
int Simulation::studentsWaitOverTen() {
  if (medianArrayCount > 0) {
    int overTen = 0;
    for (int i = 0; i < medianArrayCount; i++) {
      if (medianArray[i] > 10) {
        overTen++;
      }
    }
    return overTen;
  }
  else {
    return 0;
  }
}

// calculate the mean idle time of windows based on input file data
double Simulation::meanIdleTime() {
  ListNode<int> *current = idleStats.front;
  double numItems = 0.0;
  double meanIdleTime = 0.0;
  double sum = 0.0;

  while(current != NULL) {
    sum += current->data;
    current = current->next;
    numItems++;
  }

  // calcualte mean idle time for windows
  meanIdleTime = (double) (sum / numItems);
  return meanIdleTime;
}

// method to calcualte the longest window idle time
int Simulation::longestIdleTime() {
  ListNode<int> *current = idleStats.front;
  idleArrayCount = 0;

  // count items in the idleStats array
  while (current != NULL) {
    current = current->next;
    idleArrayCount++;
  }

  idleArray = new int[idleArrayCount];
  int max = idleArray[0];

  // sort though the idleArray to find the largest value
  for (int i = 0; i < idleArrayCount; ++i) {
    idleArray[i] > current->data;
    if (idleArray[i] > max) {
      max = idleArray[i];
    }
    current = current->next;
  }
  return max;
}

// calculate the number of windows who have an idle wait time over 5 minutes
int Simulation::windowIdleOverFive() {
  int idleOverFive;

  for (int i = 0; i < idleArrayCount; ++i) {
    if (idleArray[i] > 5) {
      idleOverFive++;
    }
  }
  return idleOverFive;
}
