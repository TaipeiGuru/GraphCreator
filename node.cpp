// Node CPP files for Red Black Tree.

#include "node.h"
#include <iostream>
#include <cstring>

using namespace std;

Node::Node(char* myLabel) {
  next = NULL;
  strcpy(label, myLabel);
  strcpy(beginVertex, "NULL");
  strcpy(endVertex, "NULL");
}

Node::~Node() {
  next = NULL;
}

// Getters
char* Node::getLabel() {
  return label;
}

char* Node::getBeginVertex() {
  return beginVertex;
}

char* Node::getEndVertex() {
  return endVertex;
}

Node* Node::getNext() {
  return next; 
}

// Setters
void Node::setLabel(char* myLabel) {
  strcpy(label, myLabel);
}

void Node::setBeginVertex(char* myLabel) {
  strcpy(beginVertex, myLabel);
}

void Node::setEndVertex(char* myLabel) {
  strcpy(endVertex, myLabel);
}

void Node::setNext(Node* nextNode) {
  next = nextNode; 
}
