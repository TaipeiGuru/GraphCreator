// This is the Binary Search Tree project, which sorts integer values into a binary tree. Last modified by Jason Randolph on 4-7-23.

// Imports
#include <iostream>
#include <cstring>
#include "node.h"

using namespace std;

// Function prototypes
void addVertex(Node** &adjacency, char* label);
void addEdge(Node** &adjacency, char* label);
void deleteVertex(Node** &adjacency, char* label);
void deleteEdge(Node** &adjacency, char* label);
void findPath(Node** &adjacency, char* begin, char* end);
void print(Node** adjacency);

int main() { 
  // Initializing variables
  Node* adjacency[21];
  for(int i = 1; i < 21; i++) {
    adjacency[i] = NULL; 
  }
  Node* head = new Node("head");
  adjacency[0] = head;
  char input[20];

  cout << "Welcome to Graph Creator!" << endl;
  
  // Standard repeating message sequence using bool and while loop.
  bool active = true;
  while(active == true) {
    cout << "\nPlease input a command below. You may \"ADD VERTEX,\" \"ADD EDGE,\" \"REMOVE VERTEX,\" \"REMOVE EDGE,\" \"PATH,\" \"PRINT,\"and \"QUIT.\"" << endl;
    cin.getline(input, 20);
    cin.clear();
    cin.ignore(10000, '\n');
	  
    if(strcmp(input, "ADD VERTEX") == 0) {
      cout << "What is the vertex label?" << endl;
      cin.get(input, 10);
      cin.clear();
      cin.ignore(10000, '\n');
      addVertex(adjacency, input);
    } else if(strcmp(input, "ADD EDGE") == 0) {
      cout << "What is the edge label?" << endl;
      cin.get(input, 10);
      cin.clear();
      cin.ignore(10000, '\n');
      addEdge(adjacency, input);
    } else if(strcmp(input, "REMOVE VERTEX") == 0) {
      cout << "What is the vertex label?" << endl;
      cin.get(input, 10);
      cin.clear();
      cin.ignore(10000, '\n');
      deleteVertex(adjacency, input);
    } else if(strcmp(input, "REMOVE EDGE") == 0) {
      cout << "What is the edge label?" << endl;
      cin.get(input, 10);
      cin.clear();
      cin.ignore(10000, '\n');
      deleteEdge(adjacency, input);
    } else if(strcmp(input, "PATH") == 0) {
      char begin[10];
      char end[10];
      cout << "What is the beginning vertex label?" << endl;
      cin.get(begin, 10);
      cin.clear();
      cin.ignore(10000, '\n');
      cout << "What is the ending vertex label?" << endl;
      cin.get(end, 10);
      cin.clear();
      cin.ignore(10000, '\n');
      findPath(adjacency, begin, end);
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

void addVertex(Node** &adjacency, char* label) {
	int i = 0;
  while(adjacency[i] == NULL) {
    i++; 
  }
  Node* newNode = new Node(label);
  adjacency[i] = newNode;
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
        cout << tempNode->getLabel() << "\t";
        tempNode = tempNode->getNext();
      }
    }
  }
}


