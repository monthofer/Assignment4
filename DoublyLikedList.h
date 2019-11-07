/*
* Sarah Monthofer
* monthofer@chapman.edu
* 2317035
* CPSC 350 - Assignment 4
*
* Description: this file contians all essential functions of the doubly linked list
        most of the implementation was generic and taken from class
*/

#include <iostream>
#include "ListNode.h"

using namespace std;

template <class T>
class DoublyLikedList {
  public:
    unsigned int size;
    // pointers to front and back nodes
    ListNode<T> *front;
    ListNode<T> *back;

    // constructor and destructor
    DoublyLinkedList();
    ~DoublyLinkedList();

    // basic Linked List functionality
    void insertBack(T data);
    int deletePos(int pos);
    void printList();
    T removeFront();
    T getFront();
    bool isEmpty();
    unsigned int getSize();;
};

// constructor
template <class T>
DoublyLikedList<T>::DoublyLikedList() {
  size = 0;
  front = NULL;
  back = NULL;
}

// destructor
template <class T>
DoublyLikedList<T>::~DoublyLikedList() {

}

// insert in the back of the doubly linked list
template <class T>
void DoublyLikedList<T>::insetBack(T d) {
  ListNode<T> *node = new ListNode<T>(d);

  // if LinkedList is Empty make the front equal to data node sent in
  if(size == 0) {
      front = node;
  }

  // if the LinkedList is not empty add it to the back of LinkedList
  else {
      back->next = node;
      node->prev = back;
  }
  back = node;
  ++size;
}

// delete a ListNode at a specfic postition
template <class T>
void DoublyLikedList<T>::deletePos(int pos) {
  int idx = 0;
  ListNode<T> *curr = front;
  ListNode<T> *prev = front;

  // find the index of position of an item in LinkedList
  while(idx != pos) {
    prev = curr;
    curr = curr->next;
    ++idx;
  }

  // delete item at the index and update pointers
  prev->next = curr->next;
  curr->next->prev = prev;
  curr->next = NULL;
  curr->prev = NULL;
  curr->data = NULL;

  --size;
  delete curr;
}

// print the contents of a doubly linked list
template <class T>
void DoublyLikedList<T>::printList(){
  ListNode<T> *curr = front;

  // print out the nodes
  while(true) {
    if (curr->next == NULL) {
      break;
    }
    cout << curr->data << endl;
    curr = curr->next;
  }
}

// remove from the front of the doubly linked list
template <class T>
T DoublyLikedList<T>::removeFront() {
  // make sure LinkedList is not empty
  if(!isEmpty()) {
    // create pointer to front node
    ListNode<T> *node = front;

    // if there is only one node null pointers
    if(front->next == NULL) {
      front = NULL;
      back = NULL;
    }

    // if there is more than one node update pointers
    else {
      front->next->prev = NULL;
      front = front->next;
    }
    T temp = node->data;
    delete node;
    --size;
    return temp;
  }

  // LinkedList is empty, return T
  else {
      return T();
  }
}

// return the data at front of the LinkedList
template <class T>
T DoublyLinkedList<T>::getFront() {
  return front->data;
}

// return the size of the LinkedList (aka how many items it contains)
template <class T>
unsigned int DoublyLikedList<T>::getSize() {
  return size;
}

// boolean to check if the LinkedList is empty
template <class T>
bool DoublyLikedList<T>::isEmpty() {
  return(size == 0);
}
