#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <cstring>
using namespace std;

class student;

class node{
public:
  node(student* p_student); //pass in student parameter
  ~node();
  void setValue(student* newvalue);
  student* getStudent();
  void setNext(node* newnext);
  node* getNext();//get next Node pointer
  
private:
  student* m_student; //define student member...(holding pointer object)
  node* next;
};
#endif
