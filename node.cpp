#include <iostream>
#include "node.h"

using namespace std;

//defines student
node::node(student* value){
  m_student=value;
  next = NULL;
}

//deletes class
node::~node(){
  next = NULL;
}

//gives you student
student* node::getStudent(){
  return m_student;
}

//defines the next thing in the linked list
void node::setNext(node* newnext){
  next = newnext;
}

//gives you next thing in linked list
node* node::getNext(){
  return next;
}
