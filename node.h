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
  char* getLabel();
  char* getBeginVertex();
  char* getEndVertex();
  Node* getNext();
 
 // setters
  void setNext(Node* nextNode);
  void setLabel(char* myLabel);
  void setBeginVertex(char* myLabel);
  void setEndVertex(char* myLabel);

 private:
 // node data
  Node* next;
  char label[10];
  char beginVertex[10];
  char endVertex[10];
};
#endif
