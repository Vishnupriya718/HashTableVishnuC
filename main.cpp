#include <iostream>
#include <iomanip>
#include <cstring>
#include "node.h"
#include "student.h"

using namespace std;

//  prototypes so main knows these exist
void addStudent(node*& head);
void addRecursive(node*& current, node* newNode);

void printStudents(node* head);
void printRecursive(node* current);

void deleteStudent(node*& head);
void deleteRecursive(node*& current, int id);

void averageGpa(node* head);
void averageRecursive(node* current, float& sum, int& count);

int main() {
  // size of the hash table 
  const int TABLE_SIZE = 100;
  // array of node pointers; each index represents the head of linked list (basically chaining)

  node** table= new node*[TABLE_SIZE];

  // initalizing all the buckets to null

  for( int i = 0;i < TABLE_SIZE; i++)  {
    table[i] = NULL;
  }
  node* head = NULL; // temporary: will be removed in next steps

  char command[10];

    cout << "Enter a command (ADD, PRINT, DELETE, AVERAGE, QUIT):" << endl;

    while (true) {
        cin >> command;

        if (strcmp(command, "ADD") == 0) {
            addStudent(head);
        }
        else if (strcmp(command, "PRINT") == 0) {
            printStudents(head);
        }
        else if (strcmp(command, "DELETE") == 0) {
            deleteStudent(head);
        }
        else if (strcmp(command, "AVERAGE") == 0) {
            averageGpa(head);
        }
        else if (strcmp(command, "QUIT") == 0) {
            break;
        }
        else {
            cout << "Unknown command." << endl;
        }
    }

    //  cleanup, memory leaks 
    while (head != NULL) {
        node* temp = head;
        head = head->getNext();
        delete temp->getStudent();
        delete temp;
    }

    return 0;
}

// ADD STUDENT
void addStudent(node*& head) {
    // gather info from user
    char fname[15];
    char lname[30];
    int id;
    float gpa;

    cout << "Enter first name: ";
    cin >> fname;

    cout << "Enter last name: ";
    cin >> lname;

    cout << "Enter student ID: ";
    cin >> id;

    cout << "Enter GPA: ";
    cin >> gpa;

    // make the student object
    student* s = new student(fname, lname, id, gpa);

    //  wrap it in a node bc linked list moment
    node* newNode = new node(s);

    //  recursion handles sorted insertion
    addRecursive(head, newNode);
}
void addRecursive(node*& current, node* newNode) {
    if (current == NULL ||
        newNode->getStudent()->getID() < current->getStudent()->getID()) {

        newNode->setNext(current);
        current = newNode;
        return;
    }

    node* temp = current->getNext();   // copy next pointer
    addRecursive(temp, newNode);       // recurse on the copy
    current->setNext(temp);            // write back updated pointer
}
// PRINT STUDENT
void printStudents(node* head) {
    if (head == NULL) {
        cout << "No students in list." << endl;
        return;
    }
    printRecursive(head);
}

void printRecursive(node* current) {
    if (current == NULL) return;

    student* s = current->getStudent();
    cout << s->getFirst() << " " << s->getLast() << ", "
         << s->getID() << ", "
         << fixed << setprecision(2) << s->getGPA() << endl;

    printRecursive(current->getNext());
}


// DELETE STUDENT

void deleteStudent(node*& head) {
    if (head == NULL) {
        cout << "List is empty." << endl;
        return;
    }

    int id;
    cout << "Enter student ID to delete: ";
    cin >> id;

    deleteRecursive(head, id);
}

void deleteRecursive(node*& current, int id) {
    if (current == NULL) {
        cout << "Student not found." << endl;
        return;
    }

    // found the node to delete
    if (current->getStudent()->getID() == id) {
        node* temp = current;
        current = current->getNext();

        delete temp->getStudent();
        delete temp;

        cout << "Student deleted." << endl;
        return;
    }

    // FIXED: cannot pass current->getNext() directly
    node* temp = current->getNext();
    deleteRecursive(temp, id);
    current->setNext(temp);
}
// AVERAGE GPA
// function so main doesn't deal with sum/count directly
void averageGpa(node* head) {
    if (head == NULL) {
        cout << "No students in list." << endl;
        return;
    }

    float sum = 0;
    int count = 0;

    //recursion does the heavy lifting
    averageRecursive(head, sum, count);

    cout << fixed << setprecision(2) << (sum / count) << endl;
}

//recursive helper: walk the list, add GPAs, count students
void averageRecursive(node* current, float& sum, int& count) {
    if (current == NULL) return;  // base case

    sum += current->getStudent()->getGPA();
    count++;

    averageRecursive(current->getNext(), sum, count);
}


