// This is the Binary Search Tree project, which sorts integer values into a binary tree. Last modified by Jason Randolph on 4-7-23.

// Imports
#include <iostream>
#include <cstring>
#include "node.h"

using namespace std;

// Function prototypes
void addVertex(Node** adjacency, char* label, int &vertexNum);
void addEdge(Node** adjacency, char* label);
void deleteVertex(Node** adjacency, char* label, int &vertexNum);
void deleteEdge(Node** adjacency, char* label);
void findPath(Node** adjacency, char* begin, char* end);
void print(Node** adjacency);

int main() { 
  // Initializing variables
  Node* adjacency[21];
  for(int i = 1; i < 21; i++) {
    adjacency[i] = NULL; 
  }
  char temp[5];
  strcpy(temp, "head");
  Node* head = new Node(temp);
  adjacency[0] = head;
  char input[20];
  int vertexNum = 0;

  cout << "Welcome to Graph Creator!" << endl;
  
  // Standard repeating message sequence using bool and while loop.
  bool active = true;
  while(active == true) {
    cout << "\nPlease input a command below. You may \"ADD VERTEX,\" \"ADD EDGE,\" \"REMOVE VERTEX,\" \"REMOVE EDGE,\" \"PATH,\" \"PRINT,\" and \"QUIT.\"" << endl;
    cin.get(input, 20);
    cin.clear();
    cin.ignore(10000, '\n');
	  
    if(strcmp(input, "ADD VERTEX") == 0) {
      cout << "What is the vertex label?" << endl;
      cin >> input;
      cin.clear();
      cin.ignore(10000, '\n');
      addVertex(adjacency, input, vertexNum);
    } else if(strcmp(input, "ADD EDGE") == 0) {
      cout << "What is the edge label?" << endl;
      cin >> input;
      cin.clear();
      cin.ignore(10000, '\n');
      // addEdge(adjacency, input);
    } else if(strcmp(input, "REMOVE VERTEX") == 0) {
      cout << "What is the vertex label?" << endl;
      cin >> input;
      cin.clear();
      cin.ignore(10000, '\n');
      deleteVertex(adjacency, input, vertexNum);
    } else if(strcmp(input, "REMOVE EDGE") == 0) {
      cout << "What is the edge label?" << endl;
      cin >> input;
      cin.clear();
      cin.ignore(10000, '\n');
      // deleteEdge(adjacency, input);
    } else if(strcmp(input, "PATH") == 0) {
      char begin[10];
      char end[10];
      cout << "What is the beginning vertex label?" << endl;
      cin >> begin;
      cin.clear();
      cin.ignore(10000, '\n');
      cout << "What is the ending vertex label?" << endl;
      cin >> end;
      cin.clear();
      cin.ignore(10000, '\n');
      // findPath(adjacency, begin, end);
    } else if(strcmp(input, "PRINT") == 0) {
      print(adjacency);
    } else if(strcmp(input, "QUIT") == 0) {
      active = false;
    } else {
      cout << "\nSorry, invalid input." << endl; 
    }
  }
  return 0;
}

void deleteVertex(Node** adjacency, char* label, int &vertexNum) {
  vertexNum--;
  int a = 0;
  Node* current = adjacency[0];
  while(current != NULL) {
    if(strcmp(current->getNext()->getLabel(), label) != 0) {
      a++;
      current = current->getNext();
    } else {
      break;
    }
  }
  Node* temp = current->getNext();
  current->setNext(current->getNext()->getNext());
  delete temp;
  temp = NULL;
  for(int i = 1; i < vertexNum; i++) {
    if(strcmp(adjacency[i]->getLabel(), label) == 0) {
      // delete all Nodes in the linked list
    }
  }
}

void addVertex(Node** adjacency, char* label, int &vertexNum) {
  vertexNum++;
  int i = 1;
  while(adjacency[i] != NULL) {
    i++; 
  }
  Node* newNode = new Node(label);
  adjacency[i] = newNode;
  for(int k = 1; k < i; k++) {
    Node* current = adjacency[k];
    while(current->getNext() != NULL) {
      current = current->getNext();
    }
    char label[2];
    strcpy(label, "F");
    Node* edge = new Node(label);
    current->setNext(edge);
  }
  for(int j = 0; j < vertexNum; j++) {
    char label[2];
    strcpy(label, "F");
    Node* edge = new Node(label);
    newNode->setNext(edge);
    newNode = newNode->getNext();
  }
  Node* tempNode = adjacency[0];
  while(tempNode->getNext() != NULL) {
    tempNode = tempNode->getNext();
  }
  Node* newHeaderNode = new Node(label);
  tempNode->setNext(newHeaderNode);
}

void print(Node** adjacency) {
  for(int i = 0; i < 21; i++) {
    if(adjacency[i] != NULL) {
      Node* tempNode = adjacency[i];
      while(tempNode != NULL) {
        if(strcmp(tempNode->getLabel(), "head") != 0) {
	  cout << tempNode->getLabel() << "\t";
	} else {
	  cout << "\t";
	}
        tempNode = tempNode->getNext();
      }
      cout << endl;
    }
  }
}


