
// This is the Graph Creator project, which creates graphs of nodes and can find the shortest path betwee them. Last modified by Jason Randolph on 6-7-23.

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
void print(Node** adjacency);
char* intToChar(int weight, char* myChar);
int charToInt(char* myChar);
void findPath(Node** adjacency, char* begin, char* end, int vertexNum);
void createPath(char*** table, char** path, char* begin, char* end, int vertexNum, int &total);

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
      bool exists = false;
      char myLabel[10];
      // check to see if vertex exists
      for(int i = 0; i < 20; i++) {
        if(adjacency[i] != NULL) {
          strcpy(myLabel, adjacency[i]->getLabel());  
          if(strcmp(myLabel, input) == 0) {
            exists = true;
          }
        }
      }
      if(exists == false) {
        cout << "This vertex does not exist." << endl;
      } else {
        deleteVertex(adjacency, input, vertexNum);
      }
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

// function that converts a char array to an int
int charToInt(char* myChar) {
  // get size of integer
  int size = strlen(myChar);
  int degreeCounter = 1;
  int output = 0;
  // starting from the 1s digit, convert to integer, multiply by appropriate degree, and then add to output
  for(int i = size-1; i >= 0; i--) {
    output += (myChar[i]-'0')*degreeCounter;
    degreeCounter *= 10;
  }
  return output;
}

// function that converts an integer to a char. Help from https://www.geeksforgeeks.org/cpp-program-for-int-to-char-conversion/
char* intToChar(int weight, char* myChar) {
  int divisor = 100000;
  int modulo;
  int numDegree = 0;
  int dupNum = weight;
  // find degree of number
  while(dupNum/10 != 0) {
    numDegree++;
    dupNum /= 10;
  }
  numDegree++;
  myChar = new char[numDegree+1];
  myChar[numDegree] = '\0';
  // find modulo and add to char array. Then, divide by 10 and repeat process until the number has been fully converted
  for(int b = 0; b < 3; b++) {
    while(weight % divisor != 0 && weight % divisor > 9) {
      divisor /= 10;
    }
    modulo = weight % divisor;
    weight = (weight-modulo)/10;
    // adding to char array using + '0'
    for(int i = numDegree-1; i >= 0; i--) {
      if(isdigit(myChar[i]) == 0) {
        myChar[i] = (char)modulo+'0';
        break;
      }
    }
  }
  return myChar;
}

// function that finds the shortest path between two nodes
void findPath(Node** adjacency, char* begin, char* end, int vertexNum) {
  // Creating Djikstra's table. Help with triple pointer from Galbraith
  char*** table = new char**[vertexNum];
  bool beginExists = false;
  bool endExists = false;
  char myLabel[10];
  // initializing rows of the table
  for (int i = 0; i < vertexNum; i++) {
    table[i] = new char*[3];
  }
  // check to see if vertices exist
  for(int i = 0; i < 20; i++) {
    if(adjacency[i] != NULL) {
      strcpy(myLabel, adjacency[i]->getLabel());  
      if(strcmp(myLabel, begin) == 0) {
        beginExists = true;
      }
      if(strcmp(myLabel, end) == 0) {
        endExists = true;
      }
    }
  }
  // if not, alert user and end the function
  if(beginExists == false || endExists == false) {
    cout << "One of your vertices is invalid." << endl;
    return;
  }
  // create arrays for visited/unvisited nodes
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
  // add in nodes from adjacency table
  Node* current = adjacency[0]->getNext();
  for(int i = 0; i < vertexNum; i++) {
    if(current != NULL) {
      strcpy(visited[i], " ");
      strcpy(unVisited[i], current->getLabel());
      // set up Djikstra's table with vertices
      strcpy(table[i][0], current->getLabel());
      // if the node is the beginning vertex, set distance to 0. Otherwise, set to max distance (999999 as arbitrary value)
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
  // main loop that constructs Djikstra's table
  while(unvisited > 0) {
    smallest = 999999;
    for(int c = 0; c < vertexNum; c++) {
      // convert int to char
      int data = atoi(table[c][1]);
      // look for vertex with smaller distance
      if(data < smallest) {
        // check to see if vertex has been visited
      	bool exists = false;
      	for(int h = 0; h < vertexNum; h++) {
      	  if(strcmp(visited[h], table[c][0]) == 0) {
      	    exists = true;
      	  }
      	}
        // if vertex has lowest number and is unvisited, save that index
      	if(exists == false) { 
      	  smallest = data;
      	  index = c;
      	  break;
      	}
      }
    }
    strcpy(smallestVertex, table[index][0]);
    // retrieve distance of smallest vertex
    int cumulativeDist = charToInt(table[index][1]);
    Node* traversal;
    // find the correct row in the adjacency table for the smallest vertex
    for(int d = 0; d < 20; d++) {
      if(strcmp(adjacency[d]->getLabel(), smallestVertex) == 0) {
        traversal = adjacency[d]->getNext();
        break;
      }
    }
    // in that row, find any neighhboring vertices
    for(int e = 0; e < vertexNum; e++) {
      if(strcmp(traversal->getLabel(), "T") == 0) {
        char end[10];
        strcpy(end, traversal->getEndVertex());
        int weight = traversal->getWeight();
        // find edge vertex in Djikstra table
        for(int f = 0; f < vertexNum; f++) {
          if(strcmp(table[f][0], end) == 0) {
            // find the previous shortest length
            int prevShortest = charToInt(table[f][1]);
            // if the new length is less than the previous shortest, update it in Djikstra's table
            if(cumulativeDist + weight < prevShortest) {
              char* myChar;
              strcpy(table[f][1], intToChar(cumulativeDist + weight, myChar));
              strcpy(table[f][2], smallestVertex); 
            }
          }
        }
      }
      // repeat through the row
      traversal = traversal->getNext();
    }
    // add the smallest vertex to the visited array and remove it from unvisited
    strcpy(visited[vertexNum-unvisited], table[index][0]);
    unvisited--;
  }
  char* path[vertexNum];
  int total;
  for(int var = 0; var < vertexNum; var++) {
    // set each element in the path array to space
    path[var] = new char[10];
    strcpy(path[var], " ");
    // if the vertex in the Djikstra's table matches the end vertex, set its distance value to the distance
    if(strcmp(table[var][0], end) == 0) {
      total = charToInt(table[var][1]);
    }
  }
  // if total is greater than the max, this means there was no complete path from beginning to end. Alert the user and end the function
  if(total >= 999999) {
    cout << "No path exists between " << begin << " and " << end << endl;
    return;
  }
  // create the shortest path
  createPath(table, path, begin, end, vertexNum, total);
  cout << "Shortest Path: "; 
  for(int test = vertexNum-1; test >= 0; test--) {
    if(strcmp(path[test], " ") != 0) {
      cout << path[test] << " "; 
    }
  }
  cout << endl;
  cout << "Total distance: " << total << endl;
}

// function that creates the shortest path
void createPath(char*** table, char** path, char* begin, char* end, int vertexNum, int &total) {
  char nextEnd[10];
  // add ending vertex to the path
  for(int i = 0; i < vertexNum; i++) {
    if(strcmp(path[i], " ") == 0) {
      strcpy(path[i], end);
      break;
    }
  }
  // set the next End to the previous vertex of the current end
  for(int j = 0; j < vertexNum; j++) {
    if(strcmp(table[j][0], end) == 0) {
      strcpy(nextEnd, table[j][2]);
      break;
    }
  }
  // if beginning and ending vertices don't match, recursively call the function
  if(strcmp(begin, end) != 0) {
    createPath(table, path, begin, nextEnd, vertexNum, total);
  } 
}

// function that deletes edges
void deleteEdge(Node** adjacency, char* begin, char* end) {
  // check to see if vertices exist
  bool beginExists = false;
  bool endExists = false;
  char myLabel[10];
  for(int i = 0; i < 20; i++) {
    if(adjacency[i] != NULL) {
      strcpy(myLabel, adjacency[i]->getLabel());  
      if(strcmp(myLabel, begin) == 0) {
        beginExists = true;
      }
      if(strcmp(myLabel, end) == 0) {
        endExists = true;
      }
    }
  }
  if(beginExists == false || endExists == false) {
    cout << "One of your vertices is invalid." << endl;
    return;
  }
  int counter = 0;
  Node* temp = adjacency[0];
  // find column number of vertex
  while(strcmp(temp->getLabel(), end) != 0) {
    // checks to see if vertex exists
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

// function that adds edges
void addEdge(Node** adjacency, char* begin, char* end, int weight) {
  int counter = 0;
  Node* temp = adjacency[0];
  // find column number of vertex
  while(strcmp(temp->getLabel(), end) != 0) {
    // checks to see if vertex exists
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

// function that deletes vertices
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

// function that adds vertices
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

// function that prints the adjacency table
void print(Node** adjacency) {
  // for loop and while loop used to cycle through adjacency table and print values
  for(int i = 0; i < 21; i++) {
    if(adjacency[i] != NULL) {
      Node* tempNode = adjacency[i];
      while(tempNode != NULL) {
        // ignore head pointer, has no node data
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
