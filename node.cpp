// Node CPP files for Red Black Tree.

#include "node.h"
#include <iostream>

using namespace std;

Node::Node(char* myLabel) {
  next = NULL;
  strcpy(label, myLabel);
}

Node::~Node() {
  next = NULL;
}

// Getters
char* Node::getLabel() {
  return label;
}

Node* Node::getNext() {
  return next; 
}

// Setters
void Node::setLabel(char* myLabel) {
  strcpy(label, myLabel);
}

void Node::setNext(Node* nextNode) {
  next = nextNode; 
}
