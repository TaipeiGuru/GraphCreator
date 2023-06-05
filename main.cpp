
// This is the Binary Search Tree project, which sorts integer values into a binary tree. Last modified by Jason Randolph on 4-7-23.

// Imports
#include <iostream>
#include <cstring>
#include <stdlib.h>
#include "node.h"

using namespace std;

// Function prototypes
void addVertex(Node** adjacency, char* label, int &vertexNum);
void addEdge(Node** adjacency, char* begin, char* end, int weight);
void deleteVertex(Node** adjacency, char* label, int &vertexNum);
void deleteEdge(Node** adjacency, char* begin, char* end);
void findPath(Node** adjacency, char* begin, char* end, int vertexNum);
void print(Node** adjacency);
char* intToChar(int weight, char* myChar);

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
      char begin[10];
      char end[10];
      int weight;
      cout << "What is the edge weight?" << endl;
      cin >> weight;
      cin.clear();
      cin.ignore(10000, '\n');
      cout << "What is the first vertex?" << endl;
      cin >> begin;
      cin.clear();
      cin.ignore(10000, '\n');
      cout << "What is the last vertex?" << endl;
      cin >> end;
      cin.clear();
      cin.ignore(10000, '\n');
      addEdge(adjacency, begin, end, weight);
    } else if(strcmp(input, "REMOVE VERTEX") == 0) {
      cout << "What is the vertex label?" << endl;
      cin >> input;
      cin.clear();
      cin.ignore(10000, '\n');
      deleteVertex(adjacency, input, vertexNum);
    } else if(strcmp(input, "REMOVE EDGE") == 0) {
      char begin[10];
      char end[10];
      cout << "What is the first node?" << endl;
      cin >> begin;
      cin.clear();
      cin.ignore(10000, '\n');
      cout << "What is the last node?" << endl;
      cin >> end;
      cin.clear();
      cin.ignore(10000, '\n');
      deleteEdge(adjacency, begin, end);
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
      findPath(adjacency, begin, end, vertexNum);
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

void findPath(Node** adjacency, char* begin, char* end, int vertexNum) {
  char* table[vertexNum][3];
  char* visited[vertexNum];
  char* unVisited[vertexNum];
  for (int i = 0; i < vertexNum; i++) {
    for (int j = 0; j < 3; j++) {
      table[i][j] = new char[10]; 
    }
  }

  for (int i = 0; i < vertexNum; i++) {
    visited[i] = new char[10];
    unVisited[i] = new char[10];
  }
  Node* current = adjacency[0]->getNext();
  
  // configure visited and unVisited arrays
  for(int i = 0; i < vertexNum; i++) {
    if(current != NULL) {
      strcpy(visited[i], " ");
      strcpy(unVisited[i], current->getLabel());
      strcpy(table[i][0], current->getLabel());
      if(strcmp(table[i][0], begin) == 0) {
        strcpy(table[i][1], "0");
      } else {
        strcpy(table[i][1], "999999");
      }
      strcpy(table[i][2], "NULL");
      current = current->getNext();
    }
  }
  int smallest;
  int index;
  int unvisited = vertexNum;
  char smallestVertex[10];
  while(unvisited > 0) {
    smallest = 999999;
    for(int c = 0; c < vertexNum; c++) {
      int data = atoi(table[c][1]);
      if(data < smallest) {
	      bool exists = false;
	      for(int h = 0; h < vertexNum; h++) {
	        if(strcmp(visited[h], table[c][0]) == 0) {
	          exists = true;
	        }
	      }
	      if(exists == false) { 
          smallest = data;
          index = c;
          break;
        }
      }
    }
    cout << index << endl;
    strcpy(smallestVertex, table[index][0]);
    Node* traversal;
    for(int d = 0; d < 20; d++) {
      if(strcmp(adjacency[d]->getLabel(), smallestVertex) == 0) {
        traversal = adjacency[d]->getNext();
        break;
      }
    }
	  // find nodes in LL that match the end node
    for(int e = 0; e < vertexNum; e++) {
      // edge is found
      if(strcmp(traversal->getLabel(), "T") == 0) {
        char end[10];
        strcpy(end, traversal->getEndVertex());
        int weight = traversal->getWeight();
        for(int f = 0; f < vertexNum; f++) {
          // find the end vertex in the Djikstra table
          if(strcmp(table[f][0], end) == 0) {
            // if begin vertex value + edge weight is < end vertex value, replace
            int newWeight = charToInt(table[f][0]) + weight;
            int oldWeight = charToInt(table[index][0]);
            cout << "new: " << newWeight << " old: " << oldWeight << endl;
            if(newWeight < oldWeight) {
              char* myChar;
              strcpy(table[f][1], intToChar(weight, myChar));
              strcpy(table[f][2], smallestVertex);
            }
          }
        }
      }
      traversal = traversal->getNext();
    }
    strcpy(visited[vertexNum-unvisited], table[index][0]);
    unvisited--;
  }
  for(int a = 0; a < vertexNum; a++) {
    for(int b = 0; b < 3; b++) {
      cout << table[a][b] << " ";
    }
    cout << endl;
  }
}

int charToInt(char* myChar) {
  int size = strlen(myChar);
  int degreeCounter = 1;
  int output = 0;
  for(int i = size-1; i >= 0; i--) {
    output += (myChar[i]-'0')*degreeCounter;
    degreeCounter *= 10;
  }
  return output;
}

char* intToChar(int weight, char* myChar) {
  int divisor = 100000;
  int modulo;
  int numDegree = 0;
  int dupNum = weight;
  while(dupNum/10 != 0) {
    numDegree++;
    dupNum /= 10;
  }
  numDegree++;
  myChar = new char[numDegree+1];
  myChar[numDegree] = '\0';
  for(int b = 0; b < 3; b++) {
    while(weight % divisor != 0 && weight % divisor > 9) {
      divisor /= 10;
    }
    modulo = weight % divisor;
    weight = (weight-modulo)/10;
    for(int i = numDegree-1; i >= 0; i--) {
      if(isdigit(myChar[i]) == 0) {
        myChar[i] = (char)modulo+'0';
        break;
      }
    }
  }
  return myChar;
}

void deleteEdge(Node** adjacency, char* begin, char* end) {
  int counter = 0;
  Node* temp = adjacency[0];
  // find column number of vertex
  while(strcmp(temp->getLabel(), end) != 0) {
    if(temp->getNext() != NULL) {
      temp = temp->getNext();
      counter++;
    } else {
      cout << "Your ending vertex doesn't exist." << endl;
      return;
    }
  }
  // find row number of vertex
  for(int i = 1; i < 21; i++) {
    if(adjacency[i] != NULL) { 
      if(strcmp(adjacency[i]->getLabel(), begin) == 0) {
        // find intersecting Node and change data
        Node* current = adjacency[i];
        for(int j = 0; j < counter; j++) {
          current = current->getNext();
        }
        char temp[10];
        strcpy(temp, "F");
        current->setLabel(temp);
        strcpy(temp, "NULL");
        current->setBeginVertex(temp);
        strcpy(temp, "NULL");
        current->setEndVertex(temp);
        current->setWeight(0);
        break;
      }
    }
  }
}

void addEdge(Node** adjacency, char* begin, char* end, int weight) {
  int counter = 0;
  Node* temp = adjacency[0];
  // find column number of vertex
  while(strcmp(temp->getLabel(), end) != 0) {
    if(temp->getNext() != NULL) {
      temp = temp->getNext();
      counter++;
    } else {
      cout << "Your ending vertex doesn't exist." << endl;
      return;
    }
  }
  // find row number of vertex
  for(int i = 1; i < 21; i++) {
    if(adjacency[i] != NULL) { 
      if(strcmp(adjacency[i]->getLabel(), begin) == 0) {
        // find intersecting Node and change data
        Node* current = adjacency[i];
        for(int j = 0; j < counter; j++) {
          current = current->getNext();
        }
        char temp[10];
        strcpy(temp, "T");
        current->setLabel(temp);
        strcpy(temp, begin);
        current->setBeginVertex(temp);
        strcpy(temp, end);
        current->setEndVertex(temp);
        current->setWeight(weight);
        break;
      }
    }
  }
}

// vertex does not exist?
void deleteVertex(Node** adjacency, char* label, int &vertexNum) {
  int a = 0;
  // find deleted vertex in header
  Node* current = adjacency[0];
  while(current != NULL) {
    if(strcmp(current->getNext()->getLabel(), label) != 0) {
      a++;
      current = current->getNext();
    } else {
      break;
    }
  }
  // delete vertex in header
  Node* temp = current->getNext();
  current->setNext(current->getNext()->getNext());
  delete temp;
  temp = NULL;
  // run through array
  for(int i = 1; i < 21; i++) {
    if(adjacency[i] != NULL) {
      // if vertex matches, delete all items in LL
      if(strcmp(adjacency[i]->getLabel(), label) == 0) {
        Node* current = adjacency[i];
        while(current != NULL) {
  	      adjacency[i] = current->getNext();
  	      delete current;
  	      current = adjacency[i];
        }
        // otherwise, traverse to deleted Node, delete it, and repair LL
      } else {
        Node* temp = adjacency[i];
        for(int j = 0; j < a; j++) {
          temp = temp->getNext();
        }
        Node* tempNode = temp->getNext();
        if(temp->getNext()->getNext() != NULL) {
          temp->setNext(temp->getNext()->getNext());
        } else {
          temp->setNext(NULL);
        }
        delete tempNode;
        tempNode = NULL;
      }  
    } 
  }
  vertexNum--;
}

void addVertex(Node** adjacency, char* label, int &vertexNum) {
  vertexNum++;
  int i = 1;
  // find empty row
  while(adjacency[i] != NULL) {
    i++; 
  }
  // add new vertex in column
  Node* newNode = new Node(label);
  adjacency[i] = newNode;
  // add new LL at new vertex row
  for(int j = 0; j < vertexNum; j++) {
    char label[2];
    strcpy(label, "F");
    Node* edge = new Node(label);
    newNode->setNext(edge);
    newNode = newNode->getNext();
  }
  // add new cells at non-vertex rows
  for(int k = 1; k <= vertexNum; k++) {
    if(strcmp(adjacency[k]->getLabel(), label) != 0) {
      Node* current = adjacency[k];
      while(current->getNext() != NULL) {
        current = current->getNext();
      }
      char label[2];
      strcpy(label, "F");
      Node* edge = new Node(label);
      current->setNext(edge);
    }
  }
  // add new vertex to header
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
