/******************************************************************************
# Program Desc.:      This program is a website bookmarking program. The program
#                     implements a binary search tree to store website 
#                     information.
# File:               bst.cpp
# File Description:   Implementation file for the Binary search tree ADT class. 
#                     Contains the hash bst and functions to manipulate the 
#                     data.
# Input:              None
# Output:             None
#******************************************************************************/
#include "bst.h"
#include "website.h"

//Function Definitions

// Default constructor
// Description: Initializes the Bst to NULL
// Input: None
// Output: None
Bst::Bst()
{  
   root = nullptr;
   size = 0;
} 

// Destructor
Bst::~Bst()
{
   destroy(root);
}

// Destroy
// Description: Recursive private function to destroy the binary search tree
// Input: None
// Output: None
void Bst::destroy(Node *& currRoot)
{
   if(currRoot)
   {
      destroy(currRoot->left);
      destroy(currRoot->right);
      delete currRoot;
      currRoot = nullptr;
   }
}

// Insert
// Description: Inserts a website into Bst. If the website
//              keyword already exists, the function returns false. First 
//              checks if the website already exists, then calls the private
//              helper function add to insert the website.
// Input: website - the website to be inserted
// Output: true if the website was inserted, false if the website
//         already exists
bool Bst::insert(Website& website)
{
   Website * dummy = new Website;
   // copy the keyword of the website
   char * keyword = new char[strlen(website.getKeyword()) + 1];
   strcpy(keyword, website.getKeyword());
   // first check if the website already exists
   if(retrieve(keyword, *dummy))
   {
      delete [] keyword;
      keyword = nullptr;
      delete dummy;

      return false;
   }
   else
   {
      delete [] keyword;
      keyword = nullptr;
      delete dummy;

      add(root, website);
      size += 1;
      return true;
   }
}

// Add
// Description: Adds a website to the Bst. Private helper function for insert.
//              Uses overloaded operator < to compare websites.
//              WARNING: This function does not check if the website already
//              exists. It is the responsibility of the calling function check.
// Input: website - the website to be added
//        currRoot - the current root of the Bst
// Output: none
void Bst::add(Node *& currRoot, const Website& website)
{
   if(!currRoot) // if the current root is null, add the website
   {
      currRoot = new Node(website);
      currRoot->left = nullptr;
      currRoot->right = nullptr;
   }
   else if(website < *currRoot->data) // if website < curr root, add to the left
   {
      add(currRoot->left, website);
   }
   else // website > curr root. OR website == curr root.
   {
      add(currRoot->right, website);
   }
}

// Remove by keyword
// Description: Removes a website from the Bst by keyword. If the website
//              exists, the function returns true and the website is removed.
//              If the website does not exist, the function returns false.
// Input: keyword - the keyword of the website to be removed
// Output: true if the website was removed, false if the website
//         does not exist
bool Bst::removeKeyword(const char * keyword)
{
   bool removed = removeKeyword(root, keyword);
   if(removed)
   {
      size--;
   }
   return removed;
}

// Remove by keyword (overloaded helper)
// Description: Removes a website from the Bst by keyword. If the website
//              exists, the function returns true and the website is removed.
//              If the website does not exist, the function returns false.
// Input: keyword - the keyword of the website to be removed
//        currRoot - the current root of the Bst
// Output: true if the website was removed, false if the website
//         does not exist
bool Bst::removeKeyword(Node *& currRoot, const char * keyword)
{
   if(!currRoot) // if the current root is null, the website does not exist
   {
      return false;
   }
   else if(strcmp(keyword, currRoot->data->getKeyword()) < 0)
   // if keyword < curr root, remove from the left
   {
      return removeKeyword(currRoot->left, keyword);
   }
   else if(strcmp(keyword, currRoot->data->getKeyword()) > 0) 
   // if keyword > curr root, remove from the right
   {
      return removeKeyword(currRoot->right, keyword);
   }
   else // keyword == curr root. DELETE THE NODE
   {
      // if node has no children
      if(!currRoot->left && !currRoot->right)
      {
         delete currRoot;
         currRoot = nullptr;
         return true;
      }
      // if the node has one child
      else if(!currRoot->left || !currRoot->right)
      {
         Node * temp = currRoot;
         if(!currRoot->left) // if the node has a right child
         {
            currRoot = currRoot->right; // set curr root to right child
         }
         else
         {
            currRoot = currRoot->left; // set curr root to left child
         }
         delete temp;
         temp = nullptr;
         return true;
      }
      // if the node has two children
      else
      {
         Node * successor = currRoot->right;
         while(successor->left) // find the successor
         {
            successor = successor->left; // set successor to left child
         }
         Website* temp = currRoot->data;
         currRoot->data = successor->data;
         successor->data = temp;
         // remove the successor
         removeKeyword(currRoot->right, successor->data->getKeyword());
         return true; // return true
      }
   }
}

// Remove by topic
// Description: Removes all websites from the Bst by topic. First, 
//              traverse the bst to find the website with the topic.
//              If the website exists, the function calls the removeKeyword
//              function to remove the website. If the website does not exist,
//              the function returns false.
// Input: topic - the topic of the websites to be removed
// Output: true if the websites were removed, false if no websites found. 
bool Bst::removeTopic(char * topic)
{
   return removeTopic(root, topic);
}

// Remove by topic (overloaded private helper)
// Description: Removes all websites from the Bst by topic. First,
//              traverse the bst to find the website with the topic.
//              If the website exists, the function calls the removeKeyword
//              function to remove the website. If the website does not exist,
//              the function returns false.
bool Bst::removeTopic(Node *& currRoot, const char * topic)
{
   // if the current root is null, end of tree or empty tree
   if(currRoot == nullptr)
   {
      return false;
   }

   bool removedR = false; // flag to check if the topic was found
   bool removedL = false; // flag to check if the topic was found
   
   // traverse branches first so delete is called on the leaf nodes first
   removedL = removeTopic(currRoot->left, topic);
   removedR = removeTopic(currRoot->right, topic);

   if(strcmp(topic, currRoot->data->getTopic()) == 0) // topic match delete
   {
      size--;
      return removeKeyword(currRoot, currRoot->data->getKeyword());
      // above line should always return true
   }
   return removedL || removedR; // return true if topic was found
}

// retrieve
// Description: Retrieve website matching search key from bst
//              If the websites exists, the function returns true and 
//              the website is passed back by reference.
//              If the website does not exist, the function returns false.
// Input: keyword - the keyword of the website to be retrieved
// Output: true if the website was retrieved, false if the website
bool Bst::retrieve(const char * keyword, Website& aWebsite) const
{
   return retrieve(root, keyword, aWebsite);
}

// retrieve (overloaded private helper)
// Description: Retrieve website matching search key from bst
//              If the websites exists, return true and the website is passed
//              back by reference. Else return false.
// Input: keyword - the keyword of the website to be retrieved
//        currRoot - the current root of the Bst
// Output: the website if the website was retrieved, null if the website
bool Bst::retrieve(Node* root, const char* key, Website& aWebsite) const
{
   if(!root) // if the current root is null end of tree or empty tree
   {
      return false;
   }
   else if(strcmp(key, root->data->getKeyword()) < 0)
   // if keyword < curr root, retrieve from the left
   {
      return retrieve(root->left, key, aWebsite);
   }
   else if(strcmp(key, root->data->getKeyword()) > 0)
   // if keyword > curr root, retrieve from the right
   {
      return retrieve(root->right, key, aWebsite);
   }
   else // keyword == curr root. FOUND WEBSITE
   {
      aWebsite = *root->data; // deepcpy data from node to aWebsite
      return true;
   }
}

// displayAll
// Description: Displays all websites in the bst. If the Bst is empty,
//              the function returns false, else display all websites
//              alphabetically and return true. Use the
//              overloaded operator<< to display the websites.
// Input: None
// Output: none
void Bst::displayAll()
{
   displayAll(root);
}

// displayAll (overloaded private helper)
// Description: Displays all websites in the bst. If the Bst is empty,
//              the function returns false, else display all websites
//              alphabetically with index and return true. Use the
//              overloaded operator<< to display the websites.
// Input: currRoot - the current root of the Bst
// Output: none
void Bst::displayAll(Node * currRoot)
{
   if(currRoot == nullptr) // if the current root is null end of tree or empty
   {
      return;
   }
   displayAll(currRoot->left); // display left subtree
   cout << *currRoot->data << endl; // display current node
   displayAll(currRoot->right); // display right subtree
}

// monitor
// Description: Displays height of the bst. If the tree is empty,
//              the function returns 0. 
// Input: index - the index to be monitored
// Output: the length of the chain at the index, 0 if the index is empty, and
//         -1 if the index is out of bounds
int Bst::monitor()
{
   return getHeight(root);
}

// getHeight
// Description: Returns the height of the bst. If the tree is empty,
//              the function returns 0.
// Input: root
// Output: the height of the bst
int Bst::getHeight(Node * root)
{
   if(!root) // if the current root is null end of tree or empty
   {
      return 0;
   }
   else
   {
      int leftHeight = getHeight(root->left); // get height of left subtree
      int rightHeight = getHeight(root->right); // get height of right subtree
      if(leftHeight > rightHeight) // return the larger height
      {
         return leftHeight + 1;
      }
      else
      {
         return rightHeight + 1;
      }
   }
}

// getSize()
// Description: Returns the size of the hash Bst.
// Input: None
// Output: the size of the hash Bst
int Bst::getSize() const
{
   return size;
}

// loadFromFile
// Description: Loads websites from file into the hash Bst. Uses the
//              insert function to insert the websites into the hash Bst.
// Input: filename - the name of the file to be loaded
// Output: none

void Bst::loadFromFile(const char* filename)
{
   
   ifstream inFile(filename);
   if (!inFile) // if the file cannot be opened
   {
      cout << "Error opening file" << endl;
      return;
   }

   char topic[MAX_CSTRING], url[MAX_CSTRING], summary[MAX_PARAGRAPH], 
        review[MAX_PARAGRAPH], keyword[MAX_CSTRING];

   int rating = 0;

   while (inFile.getline(keyword, MAX_CSTRING)) // while there is data to read
   {
      if (strlen(keyword) == 0) // blank line encountered
      {
         continue;
      }
      inFile.getline(topic, MAX_CSTRING);
      inFile.getline(url, MAX_CSTRING);
      inFile.getline(summary, MAX_PARAGRAPH);
      inFile.getline(review, MAX_PARAGRAPH);
      inFile >> rating;
      inFile.ignore(); // ignore newline

      // init new website
      Website* website = new Website();
      // set website data
      website->setKeyword(keyword);
      website->setTopic(topic);
      website->setURL(url);
      website->setSummary(summary);
      website->setReview(review);
      website->setRating(rating);

      insert(*website);
      
      //PRINT STATEMENTS FOR TESTING
      /*
      int count = 0;
      count++;
      cout << "Website " << count << " added." << endl;
      cout << *website << endl;
      */
      //Deallocate memory
      delete website; // delete website
      website = nullptr;
   }
}

