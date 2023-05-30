// Node class for Red Black Tree.

#ifndef NODE_H
#define NODE_H
#include <iostream>
using namespace std;

class Node {
 public:
 
 // constructor and destructor
  Node(char* myLabel);
  ~Node();
 
 // getters
  int getLabel();
  Node* getNext();
 
 // setters
  void setNext(Node* nextNode);
  void setLabel(char* myLabel);

 private:
 // node data
  Node* next;
  char label[10];
};
#endif
