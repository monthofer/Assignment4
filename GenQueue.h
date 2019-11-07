/*
* Sarah Monthofer
* monthofer@chapman.edu
* 2317035
* CPSC 350 - Assignment 4
*
* Description: this file contians all essential functions of a queue
        most of the implementation was generic and taken from class
*/

#include <iostream>
#include "ListNode.h"

using namespace std;

template <class T>
class GenQueue {
  // http://www.cplusplus.com/forum/general/68316/
  public:
    // pointers and variables
    unsigned int numElements;
    ListNode<T> *front;
    ListNode<T> *back;

    // constructor and destructor
    GenQueue();
    ~GenQueue();

    // queue functionality
    T dequeue();
    T frontNode();
    T backNode();
    void enqueue(T d);
    void printQueue();
    bool isEmpty();
    unsigned int getSize();
};

// dafault constructor for GenQueue
template <class T>
GenQueue<T>::GenQueue() {
    numElements = 0;
    front = NULL;
    back = NULL;
}

// destructor for GenQueue
template <class T>
GenQueue<T>::~GenQueue() {

}

// dequeue allows the user to remove the node at the head of the queue
template <class T>
T GenQueue<T>::dequeue() {
    if(!isEmpty()) {
        ListNode<T> *node = front; // pointer to the front node
        T temp = node->data;

        // if the front pointer is the only pointer in the queue set all pointers to NULL
        if(front->next == NULL) {
            front = NULL;
            back = NULL;
        }
        // if there are multiple nodes update the front pointer to add the node to the front
        else {
            front->next->prev = NULL;
            front = front->next;
        }
        delete node;
        --numElements;
        return temp;
    }
    else {
        return T();
    }
}

// return front node
template <class T>
T GenQueue<T>::frontNode() {
    return front->data;
}

// return back node
template <class T>
T GenQueue<T>::backNode() {
    return back->data;
}

// Enqueue allows the user to add a node at the tail of the queue
template <class T>
void GenQueue<T>::enqueue(T d) {
    ListNode<T> *node = new ListNode<T>(d); // temporary node to point to data

    // if the queue is Empty add the new node to end of the queue, which is techinically the front
    if(numElements == 0) {
        front = node;
    }
    // if the queue has nodes update pointers to add to the tail
    else {
        back->next = node;
        node->prev = back;
    }

    back = node;
    ++numElements;
}

// print the contents of the queue
template <class T>
void GenQueue<T>::printQueue() {
    ListNode<T> *curr = front;

    while(true) {
      // follow the node pointers until there are none left and print node contents
        if(curr != NULL) {
            cout << curr->data << endl;
            curr = curr->next;
        }
        else {
            break;
        }
    }
}

// boolean to check if the queue is Empty
template <class T>
bool GenQueue<T>::isEmpty() {
    return (numElements == 0);
}

// check the size of the gueue
template <class T>
unsigned int GenQueue<T>::getSize() {
    return numElements;
}
