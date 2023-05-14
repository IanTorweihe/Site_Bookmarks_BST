# Website Bookmarking Program

This is a website bookmarking program that uses a Binary Search Tree (BST) to store website information. The program is designed to create a BST, insert websites based on their keyword, remove websites by keyword or topic, retrieve information about a particular website, display all websites in alphabetical order, and monitor the height of the tree.

## Program Description

The `app.cpp` file is the driver program for the website bookmarking program. It provides a menu-based user interface that allows users to interact with the BST and test its functionalities.

## Features

1. **Add new website:** Add a new website to the BST.
2. **Display all websites:** Display all the websites stored in the BST.
3. **Remove website:** Remove a specific website from the BST using its keyword.
4. **Remove all websites matching a topic:** Remove all websites associated with a specific topic.
5. **Monitor BST performance:** Monitor and display the performance statistics of the BST.

## Input

User input from menu options, data for new websites, and test data for loading (`input.txt`).

## Output

Display menu options, website data, and save data (`output.txt`).

## How to Run

1. Compile the program:
   ```sh
   g++ -o app app.cpp bst.cpp website.cpp
   

2. Run the executable:
   ```sh
   ./app
   

## Usage

When running the program, you will be presented with a menu that allows you to perform various actions on the BST. To select an option, enter the corresponding number and press enter. The program will then prompt you for the required information, depending on the action you have chosen.
