/******************************************************************************
# Program Desc.:      This program is a website bookmarking program. The program
#                     implements a binary search tree to store website 
#                     information.
# File:               bst.h
# File Description:   Header file for the binary search tree ADT class. 
#                     Contains the hash bst and functions to manipulate the
#                     data.
# Input:              None
# Output:             None
#******************************************************************************/
#ifndef BST_H 
#define BST_H
#include <iostream>
#include <cstring>
#include <fstream>

#include "website.h"

using namespace std;

class Bst
{
public:
   // '!!' indicates required functions per submission requirements
   // should make all recursive
   Bst(); // constructor !!
   ~Bst(); // destructor !!
   bool insert(Website& aWebsite); // add website to the BST !!
   bool removeKeyword(const char * keyword); // remove website by keyword !!
   bool removeTopic(char * topic); // removes all websites matching topic !!
   bool retrieve(const char * keyword, Website& aWebsite) const;//get site by key
   void displayAll(); // dsp all sites alphabetically !!
   int monitor(); // display height of tree!!
   int getSize() const; // return number of nodes in Bst

   void loadFromFile(const char * filename); // load test data from file

private:
   struct Node // node struct bst
   {
      Node(const Website& aWebsite) // node constructor
      {
         data = new Website(aWebsite);
         left = nullptr;
         right = nullptr;
      };
      ~Node() // node destructor
      {
         if(data)
         {
            delete data;
         }
         data = nullptr;
         left = nullptr;
         right = nullptr;
      };
      Website * data = nullptr;
      Node * left = nullptr;
      Node * right = nullptr;
   };
   Node * root = nullptr; // root node of bst
   int size; // current number of websites (nodes) in the bst 

   // private helper functions
   bool retrieve(Node* root, const char* key, Website& aWebsite) const; //!!
   void destroy(Node *& currRoot); // destroy the hash Bst
   void add(Node *& currRoot, const Website& website); // add a site to bst
   bool removeKeyword(Node *& currRoot, const char * keyword); //rm site frm bst
   bool removeTopic(Node *& currRoot, const char * topic); //rm site frm bst 
   void displayAll(Node * currRoot); // display all sites in bst
   int getHeight(Node * currRoot); // get height of bst
};

#endif

