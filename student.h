#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <cstring>
using namespace std;

// this is the Student class  version of my old struct
class student {
public:
  // constructor: just copy everything in
    student(const char* f, const char* l, int id, float g) {
        strcpy(fname, f);
        strcpy(lname, l);
        studentid = id;
        GPA = g;
    }

    // getters 
    const char* getFirst() { return fname; }
    const char* getLast() { return lname; }
    int getID() { return studentid; }
    float getGPA() { return GPA; }

private:
    // char arrays
    char fname[15];
    char lname[30];
    int studentid;
    float GPA;
};

#endif
