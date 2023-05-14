/******************************************************************************
# Program Desc.:      This program is a website bookmarking program. The program
#                     implements a binary search tree to store website
#                     information.
# File:               app.cpp
# File Description:   Driver program for website bookmarking program.
# Input:              User input from menu options, data for new websites
#                     and test data for loading (input.txt)
# Output:             Diplay menu options, and data for new groups and
#                     save data (output.txt)
#******************************************************************************/
#include <iostream>
#include <cmath>
using namespace std;

#include "bst.h"
#include "website.h"

// Function Prototypes
void menu(Bst &bst);
int validateMenuOpt();
// for menu options
void addWebsite(Bst &bst);
void displayAll(Bst &bst);
void removeWebsite(Bst &bst);
void removeWebsites(Bst &bst);
void monitor(Bst &bst);

#include <iostream>
using namespace std;

int main()
{
   Bst bst;

   bst.loadFromFile("input.txt"); // load test data from file

   menu(bst);

   return 0;
}

// Function Definitions

// Menu function
void menu(Bst &bst)
{
   int menuOption = 0;
   while (menuOption != 6)
   {
      cout << "Website Bookmark Program" << endl
           << "1. Add new website" << endl
           << "2. Display all websites" << endl
           << "3. Remove website" << endl
           << "4. Remove all websites that match topic" << endl
           << "5. Monitor BST Performance" << endl
           << "6. Exit" << endl;

      menuOption = validateMenuOpt();

      switch (menuOption)
      {
      case 1:
      {
         // Add new website
         addWebsite(bst);
         break;
      }
      case 2:
      {
         // Display by topic
         displayAll(bst);
         break;
      }
      case 3:
      {
         // Remove website
         removeWebsite(bst);
         break;
      }
      case 4:
      {
         // Remove all websites that match topic
         removeWebsites(bst);
         break;
      }
      case 5:
      {
         // Monitor BST Performance
         monitor(bst);
         break;
      }
      case 6:
      {
         // Exit
         cout << "Exiting program..." << endl;
         break;
      }
      default:
      {
         cout << "Invalid option. Please try again." << endl;
         break;
      }
      }
   }
}

// Function to return valid menu option
// Decription: Prompts user for valid menu option between 1 and 7. Returns
//             valid menu option as int or 0. Checks for invalid ints and
//             non-integer input.
// Input: None
// Output: Valid menu option as int or 0 if invalid
int validateMenuOpt()
{
   int menuOption = 0;
   cout << "Enter menu option: ";
   cin >> menuOption;
   if (cin.fail())
   {
      cin.clear();
      cin.ignore(1000, '\n');
      return menuOption = 0; // return 0 fail
   }
   else if (menuOption < 1 || menuOption > 6)
   {
      return menuOption = 0; // return 0 fail
   }
   cin.ignore(1000, '\n');
   return menuOption; // return valid menu option
}

// addWebsite function
// Description: Prompts user for website data and adds website to
//              bst. Rejects duplicates and notifies user.
// Input: Bst &bst
// Output: None
void addWebsite(Bst &bst)
{
   // variables for website data
   char *keyword = new char[MAX_CSTRING];
   char *topic = new char[MAX_CSTRING];
   char *URL = new char[MAX_CSTRING];
   char *summary = new char[MAX_PARAGRAPH];
   char *review = new char[MAX_PARAGRAPH];
   int rating = 0;
   Website *website = new Website;

   // display prompts and get user input
   cout << "Enter keyword: ";
   cin.getline(keyword, MAX_CSTRING);
   cout << "Enter topic: ";
   cin.getline(topic, MAX_CSTRING);
   cout << "Enter URL: ";
   cin.getline(URL, MAX_CSTRING);
   cout << "Enter summary: ";
   cin.getline(summary, MAX_PARAGRAPH);
   cout << "Enter review: ";
   cin.getline(review, MAX_PARAGRAPH);
   cout << "Enter rating: ";
   cin >> rating;
   cin.ignore(1000, '\n');
   cin.clear();
   // set website data
   website->setKeyword(keyword);
   website->setTopic(topic);
   website->setURL(URL);
   website->setSummary(summary);
   website->setReview(review);
   website->setRating(rating);
   // add website to bst
   if (!bst.insert(*website))
   {
      cout << "Website already exists." << endl;
   }
   else
   {
      cout << "Website added." << endl;
   }
   // deallocate memory
   delete website;
   website = nullptr;
   delete[] keyword;
   keyword = nullptr;
   delete[] topic;
   topic = nullptr;
   delete[] URL;
   URL = nullptr;
   delete[] summary;
   summary = nullptr;
   delete[] review;
   review = nullptr;
}

// displayAll function
// Description: Displays all websites in bst using overloaded display
// Input: Bst &bst
// Output: None
void displayAll(Bst &bst)
{
   if (bst.getSize() == 0)
   {
      cout << "No websites to display." << endl;
   }
   else
   {
      bst.displayAll();
   }
}

// remove website function (by keyword)
// Description: Prompts user for website keyword and removes website from bst.
//              First checks if website exists via retrieve function and
//              displays website if so. If not, notifies user. Then if exists
//              removes website with removeTopic and notifies user.
// Input: Bst &bst
// Output: None
void removeWebsite(Bst &bst)
{
   // variables
   char *keyword = new char[MAX_CSTRING];
   Website *website = new Website; // website to be removed
   // Prompt user for keyword
   cout << "Enter keyword: ";
   cin.getline(keyword, MAX_CSTRING);
   // check if website exists
   if (!bst.retrieve(keyword, *website))
   {
      cout << "Website does not exist." << endl;
   }
   else // website exists
   {
      // prompt user to confirm and display website
      cout << "Are you sure you want to remove this website? (y/n)" << endl;
      website->display();
      char confirm = 'n';
      cin >> confirm;
      cin.ignore(1000, '\n');
      cin.clear();
      if (confirm == 'y')
      {
         // remove website
         if (!bst.removeKeyword(keyword))
         {
            cout << "Website could not be removed." << endl;
         }
         else
         {
            cout << "Website removed." << endl;
         }
      }
      else
      {
         cout << "Website not removed." << endl;
      }
   }
   // deallocate memory
   delete[] keyword;
   keyword = nullptr;
   if (website)
   {
      delete website;
      website = nullptr;
   }
}

// removeWebsites function (by Topic)
// Description: Removes all websites matching topic. If no websites match
//              topic, notifies user. If match, removes all. Removal via
//              removeTopic function.
// Input: Bst &bst
// Output: None
void removeWebsites(Bst &bst)
{
   // variables
   char *topic = new char[MAX_CSTRING];
   // Prompt user for topic
   cout << "Enter topic: ";
   cin.getline(topic, MAX_CSTRING);
   // check if website exists
   if (!bst.removeTopic(topic))
   {
      cout << "No websites match topic." << endl;
   }
   else // websites exist and were removed
   {
      cout << "Websites removed." << endl;
   }
   // deallocate memory
   delete[] topic;
   topic = nullptr;
}

// monitor function
// Description: Displays bst performance data
// Input: Bst &bst
// Output: None
void monitor(Bst &bst)
{
   int height = bst.monitor();
   int nodeCount = bst.getSize();
   // display performance data
   if (nodeCount == 0)
   {
      cout << "No websites to monitor." << endl;
   }
   else
   {
      // performance ratio is actual height / minimum height
      // higher ratio means bst is more unbalanced
      // the optimal ratio is 1.0
      double minHeight = ceil(log2(static_cast<double>(nodeCount + 1)));
      double performanceRatio = static_cast<double>(height) / minHeight;
      cout << "Actual Height: " << height << endl;
      cout << "Minimum Height: " << minHeight << endl;
      cout << "Node count: " << nodeCount << endl;
      cout << "Performance Ratio: " << performanceRatio << endl;
      cout << "Optimal Ratio: 1.0" << endl;
      cout << "Worst Case Ratio: " << static_cast<double>(nodeCount) / minHeight
           << endl;
   }
}
