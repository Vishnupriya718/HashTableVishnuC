#include <iostream>
#include <iomanip>
#include <cstring>
#include "node.h"
#include "student.h"

using namespace std;

// Function prototypes
void addStudent(node** table, int tableSize);
void addRecursive(node*& current, node* newNode);

void printStudents(node** table, int tableSize);
void printRecursive(node* current);

void deleteStudent(node** table, int tableSize);
void deleteRecursive(node*& current, int id);

void averageGpa(node** table, int tableSize);
void averageRecursive(node* current, float& sum, int& count);

// Hash function
int hashFunction(int id, int tableSize) {
    return id % tableSize;
}

int main() {
    int tableSize = 100;

    node** table = new node*[tableSize];

    // Initialize buckets
    for (int i = 0; i < tableSize; i++) {
        table[i] = NULL;
    }

    char command[20];

    cout << "Enter a command (ADD, PRINT, DELETE, AVERAGE, QUIT):" << endl;

    while (true) {
        cin >> command;

        if (strcmp(command, "ADD") == 0) {
            addStudent(&table, tableSize);
        }
        else if (strcmp(command, "PRINT") == 0) {
            printStudents(table, tableSize);
        }
        else if (strcmp(command, "DELETE") == 0) {
            deleteStudent(table, tableSize);
        }
        else if (strcmp(command, "AVERAGE") == 0) {
            averageGpa(table, tableSize);
        }
        else if (strcmp(command, "QUIT") == 0) {
            break;
        }
        else {
            cout << "Unknown command." << endl;
        }
    }

    // Cleanup memory
    for (int i = 0; i < tableSize; i++) {
        while (table[i] != NULL) {
            node* temp = table[i];
            table[i] = table[i]->getNext();
            delete temp->getStudent();
            delete temp;
        }
    }

    delete[] table;

    return 0;
}

// ADD STUDENT
void addStudent(node** table, int tableSize) {
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

    student* s = new student(fname, lname, id, gpa);
    node* newNode = new node(s);
// Count how many nodes are already in this bucket
    int index = hashFunction(id, tableSize);
    int chainLength = 0;
    node* temp = table[index];

    while (temp != NULL) {
      chainLength++;
      temp = temp->getNext();
    }

    if (chainLength >= 3) {
        cout << "Warning: Chain length exceeded 3 at index "
             << index << endl;
    }
    // Insert into correct bucket using recursion
  
    addRecursive(table[index], newNode);
}

void addRecursive(node*& current, node* newNode) {
    if (current == NULL ||
        newNode->getStudent()->getID() < current->getStudent()->getID()) {

        newNode->setNext(current);
        current = newNode;
        return;
    }

    node* temp = current->getNext();
    addRecursive(temp, newNode);
    current->setNext(temp);
}

// PRINT STUDENTS
void printStudents(node** table, int tableSize) {
    bool empty = true;

    for (int i = 0; i < tableSize; i++) {
        if (table[i] != NULL) {
            printRecursive(table[i]);
            empty = false;
        }
    }

    if (empty) {
        cout << "No students in table." << endl;
    }
}

void printRecursive(node* current) {
    if (current == NULL) return;

    student* s = current->getStudent();
    cout << s->getFirst() << " "
         << s->getLast() << ", "
         << s->getID() << ", "
         << fixed << setprecision(2)
         << s->getGPA() << endl;

    printRecursive(current->getNext());
}

// DELETE STUDENT
void deleteStudent(node** table, int tableSize) {
    int id;
    cout << "Enter student ID to delete: ";
    cin >> id;

    int index = hashFunction(id, tableSize);
    deleteRecursive(table[index], id);
}

void deleteRecursive(node*& current, int id) {
    if (current == NULL) {
        cout << "Student not found." << endl;
        return;
    }

    if (current->getStudent()->getID() == id) {
        node* temp = current;
        current = current->getNext();

        delete temp->getStudent();
        delete temp;

        cout << "Student deleted." << endl;
        return;
    }

    node* temp = current->getNext();
    deleteRecursive(temp, id);
    current->setNext(temp);
}

// AVERAGE GPA
void averageGpa(node** table, int tableSize) {
    float sum = 0;
    int count = 0;

    for (int i = 0; i < tableSize; i++) {
        averageRecursive(table[i], sum, count);
    }

    if (count == 0) {
        cout << "No students in table." << endl;
    }
    else {
        cout << fixed << setprecision(2)
             << (sum / count) << endl;
    }
}

void averageRecursive(node* current, float& sum, int& count) {
    if (current == NULL) return;

    sum += current->getStudent()->getGPA();
    count++;

    averageRecursive(current->getNext(), sum, count);
}
