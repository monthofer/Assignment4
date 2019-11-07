/*
* Sarah Monthofer
* monthofer@chapman.edu
* 2317035
* CPSC 350 - Assignment 4
*
* Description: this file contians the constructors and destructors of the linked list
        most of the implementation was generic and taken from class
*/

#include <iostream>

using namespace std;

template <class T>
class ListNode {
    public:
        T data;
        ListNode<T> *next;
        ListNode<T> *prev;

        ListNode();
        ListNode(T data);
        ~ListNode();
};

// ListNode deafult constructor
template <class T>
ListNode<T>::ListNode() {

}

// ListNode constructor if parameter data is sent in
template <class T>
ListNode<T>::ListNode(T input) {
    data = input;
    next = NULL;
    prev = NULL;
}

// ListNode destructor to null all pointers
template <class T>
ListNode<T>::~ListNode() {
    // null pointers
    if(next != NULL) {
        next = NULL;
        prev = NULL;

        // delete pointers
        delete next;
        delete prev;
    }
}
