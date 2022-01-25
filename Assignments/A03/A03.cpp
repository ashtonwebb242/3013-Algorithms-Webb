/***********************************
Author:     Ashton Webb
Email:      ashtonwebb46@gmail.com
Assignment: A04
Title:      Linked List 
Course:     3013
Semester:   Spring 2020


Description:
This program allows a linked list to work as an array.
The goal is to comment this code.

Files:
main driver     main.cpp


****************************************/



#include <iostream>

using namespace std;

int A[100];



/*
*   Node
*
*   Description:
*    Stores an integer and a node pointer. Will ne used to implement a linked list.
*   Methods:
*       Node()
*       Node(int)
*/
struct Node {
    int x;
    Node *next;
    Node() {
        x = -1;
        next = NULL;
    }
    Node(int n) {
        x = n;
        next = NULL;
    }
};


/**
 * List
 * 
 * Description:
 *     This Class is a Linked List. COntaining nodes that are linked to one another by the implementation of pointers.
 * 
 * Public Methods:
 *                          List()                               
 *      void                Push(int val)
 *      void                Insert(int val)
 *      void                PrintTail()
 *      string              Print()
 *      int                 Pop()
 *      List                operator+(const List &Rhs)
 *      int                 operator[](int index)
 *      friend              ostream &operator<<(ostream &os, List L)
 * 
 * Private Methods:
 *     None
 * 
 * Usage: 
 * 
 *      List L();          // Create Instance of List
 *      L.Push();          // pushes a node to the end of the list
 *     L.Insert(2)         // Inserts a new Node to the front of the list.
 *      
 */
class List {
private:
    Node *Head;    //beginning/front of the list
    Node *Tail;    //the end of the list
    int Size;      //number of nodes in the list

public:

   //Sets head and tail to NULL, and size to zero.
    List() {
        Head = Tail = NULL;
        Size = 0;
    }
/**
     * Public : Push
     *
     * @brief This adds a node to the end of the list. If there are no nodes
    *       in the list then it will set head and tails equal to the first node.
     *
     * @param val  -  the number being added to the end of the list
     *
     * @return void.
     */
    void Push(int val) {
        // allocate new memory and init node
        Node *Temp = new Node(val);

        if (!Head && !Tail) {
            Head = Tail = Temp;
        } else {
            Tail->next = Temp;
            Tail = Temp;
        }
        Size++;
    }
/**
     * Public : Insert
     *
     * @brief  Adds a node to the beginning of the list.
     * @param val An integer to be stored.
     *
     * @return void
     */
    void Insert(int val) {
        // allocate new memory and init node
        Node *Temp = new Node(val);

        // figure out where it goes in the list

        Temp->next = Head;
        Head = Temp;
        if (!Tail) {
            Tail = Head;
        }
        Size++;
    }
  /**
     * Public : PrintTail
     *
     * @brief  prints the number at the tail
     *
     * @param None
     *
     * @return void
     */
    void PrintTail() {
        cout << Tail->x << endl;
    }

    string Print() {
        Node *Temp = Head;
        string list;

        while (Temp != NULL) {
            list += to_string(Temp->x) + "->";
            Temp = Temp->next;
        }

        return list;
    }

    // not implemented
    int Pop() {
        Size--;
        return 0; //
    }
 /**
     * Public : operator+
     *
     * @brief Allows two lists to be added to a new list.
     *
     * @param Rhs A const List
     *
     * @return List and NewList
     */
    List operator+(const List &Rhs) {
        // Create a new list that will contain both when done
        List NewList;

        // Get a reference to beginning of local list
        Node *Temp = Head;

        // Loop through local list and Push values onto new list
        while (Temp != NULL) {
            NewList.Push(Temp->x);
            Temp = Temp->next;
        }

        // Get a reference to head of Rhs
        Temp = Rhs.Head;

        // Same as above, loop and push
        while (Temp != NULL) {
            NewList.Push(Temp->x);
            Temp = Temp->next;
        }

        // Return new concatenated version of lists
        return NewList;
    }
 /**
     * Public : operator[]
     *
     * @brief    Implements the [] operator.  This function returns an
    *            int value as if the list was an array.
     *
     * @param    int index the subscript of the value wanting to be retrieved
     *                
     * @return     int Temp->x  the value at that subscript
     */
    
    int operator[](int index) {
        Node *Temp = Head;

        if (index >= Size) {
            cout << "Index out of bounds, exiting";
            exit(0);
        } else {

            for (int i = 0; i < index; i++) {
                Temp = Temp->next;
            }
            return Temp->x;
        }
    }
 /**
     * Public operator<<
     *
     * @brief      prints out the list
     *
     * @param      ostream  :  &os
    *              Lists    :  L
     *
     * @return     ostream  :  os
     */
    friend ostream &operator<<(ostream &os, List L) {
        os << L.Print();
        return os;
    }
};

int main(int argc, char **argv) {
    List L1;
    List L2;

    for (int i = 0; i < 25; i++) {
        L1.Push(i);
    }

    for (int i = 50; i < 100; i++) {
        L2.Push(i);
    }

   // cout << L1 << endl;
    
    L1.PrintTail();        // Prints tail of L1
    L2.PrintTail();        // Prints tail of L2

    List L3 = L1 + L2;     // Adds L1 and L2 to a new list L3
    cout << L3 << endl;    // Prints the contents of L3

    cout << L3[5] << endl; // Prints the 5th item in L3

    return 0;
}
