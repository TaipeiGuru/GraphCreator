// This is the Binary Search Tree project, which sorts integer values into a binary tree. Last modified by Jason Randolph on 4-7-23.

// Imports
#include <iostream>
#include <cstring>
#include "node.h"

using namespace std;

// Function prototypes
void addVertex(Node* &adjacency, char* label);
void addEdge(Node* &adjacency, char* label);
void deleteVertex(Node* &adjacency, char* label);
void deleteEdge(Node* &adjacency, char* label);
void findPath(Node* &adjacency, char* begin, char* end);
void print(Node* adjacency);

int main() { 
  
	// Initializing variables
  Node* adjacency[21];
  for(int i = 0; i < 21; i++) {
    adjacency[i] = NULL; 
  }
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

