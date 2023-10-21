//============================================================================
// Name        : Project two.cpp
// Author      : Wasan Alabed
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>                                                                  
#include "CSVparser.hpp"
using namespace std;


//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// define a structure to hold bid information
struct Course {
    string courseNamber; // unique identifier
    string courseTitle;
    string prerequisites;
   
};
//Internal structure for tree node
struct Node {
    Course course;
    Node* left;
    Node* right;
    Node() {
        left = nullptr;
        right = nullptr;
    }
    //initialize with a course
    Node(Course aCourse) :
        Node() {
        this->course = aCourse;
    }
};

//============================================================================
// Binary Search Tree class definition
//============================================================================
/*
*class containing data member and method to implement a bst
*/
class BinarySearchTree {
private:
    Node* root;
    void addNode(Node* node, Course course);
    void printSampleSchedule(Node* node);
    void printCourseInformation(Node* node, string courseNumber);
    

public:
    BinarySearchTree();
    
    void Insert(Course course);
    void printCourseInformation(string  courseNumber);
    void printSampleSchedule();
    int numPrerequisiteCourses(string courseNumber);
    Course search(string courseNumber);

};
/*
*Default constructor
* Add a course to some node
*/

void BinarySearchTree::addNode(Node* node, Course aCourse) {
    if (node != nullptr) {
        //if node larger than course 
        if (node->course.courseNamber.compare(aCourse.courseNamber) > 0) {
            if (node->left == nullptr) {
                node->left = new Node(aCourse);
                return;
            }
            else {
                this->addNode(node->left, aCourse);
            }
        }
        else if (node->course.courseNamber.compare(aCourse.courseNamber) < 0) {
            if (node->right == nullptr) {
                node->right = new Node(aCourse);
                return;
            }
            else {
                this->addNode(node->right, aCourse);
            }
        }
    }
}
// print sample schedule in order
void BinarySearchTree::printSampleSchedule(Node * node)
{
    if (node != nullptr) {
       
        printSampleSchedule(node->left);
        cout << node->course.courseNamber << " ," << node->course.courseTitle << endl;
        printSampleSchedule(node->right);
    }

}

void BinarySearchTree::printCourseInformation(Node* node, string courseNumber) {
    if (node != nullptr) {
        if (node->course.courseNamber.compare(courseNumber) == 0) {
            cout << "Course Number: " << node->course.courseNamber << endl;
            cout << "Course Title: " << node->course.courseTitle << endl;
            int size = numPrerequisiteCourses(courseNumber);
            cout << "Prerequisites: ";
            if (size == 0) {
                cout << "No prerequisites" << endl;
            }
            else {
                for (int i = 0; i < size; i++) {
                    cout << node->course.prerequisites.at(i);
                    if (i != size - 1) {
                        cout << ",";
                    }
                }
                cout << endl;
            }
        }
        else if (node->course.courseNamber.compare(courseNumber) < 0) {
            printCourseInformation(node->left, courseNumber);
        }
        else {
            printCourseInformation(node->right, courseNumber);
        }
    }
}
    
    
BinarySearchTree::BinarySearchTree()
    {
        root = nullptr;
    }
 
void BinarySearchTree::Insert(Course course)
    {
        if (root == nullptr) {
            root = new Node(course);
        }
        else {
            addNode(root, course);
        }
    }

void BinarySearchTree::printCourseInformation(string courseNumber)
    {
        printCourseInformation(root, courseNumber);
    }

void BinarySearchTree::printSampleSchedule()
    {
        printSampleSchedule(root);
    }

int BinarySearchTree::numPrerequisiteCourses(string courseNumber) {
    Course course = search(courseNumber);
    int count = course.prerequisites.size();
    return count;
}

Course BinarySearchTree::search(string courseNumber)
    {
        Node* current = root;
        //keep looping downwards until bottom reached or matching courseNumber found
        while (current != nullptr) {
            //if match found return current course
            if (current->course.courseNamber==courseNumber) {
                return current->course;
            }
            // if smaller traverse left
            else if (current->course.courseNamber<courseNumber ) {
                current = current->left;
            }
            else {
                current = current->right;
            }
        }
            
        return Course();
    }

//============================================================================
// Static methods used for testing
//============================================================================
/**
* Load a ABCU containing bids into a container
*
* @param csvPath the path to the CSV file to load
* @return a container holding all the course read
*/
void loadCourseData(string csvPath, BinarySearchTree* bst) {
    cout << "Loading CSV file " << csvPath << endl;
    csv::Parser file = csv::Parser(csvPath);
    vector<string> header = file.getHeader();
    for (auto const& c : header) {
        cout << c << ",";
    }
    cout << "" << endl;

    try {
        //loop to read rows of a CSV file
        for (unsigned int i = 0; i < file.rowCount(); i++) {
            //Create a data structure and add to the collection of courses
            Course course;
            course.courseNamber = file[i][1];
            course.courseTitle = file[i][0];
            course.prerequisites = file[i][8];
            //push this course to the end
            bst->Insert(course);
        }
    }
    catch (csv::Error& e) {
        std::cerr << e.what() << std::endl;
    }
}
    // function to convert string to double
    double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}
    //main method
  
int main(int argc, char*argv[]) {

    string csvPath, courseNumber;
    csvPath = "ABCU_Input.csv"; //  the actual file name.
    courseNumber = "";

    // Define a binary search tree to hold all courses
    BinarySearchTree* bst = new BinarySearchTree();
    Course course;

    // Add courses to the binary search tree
       
        bst->Insert(course);
        

    int choice = 0;
    while (choice != 4) {
        cout << "Welcome to the course planner." << endl;
        cout << "  1. Load Data Structure" << endl;
        cout << "  2. Print Course List" << endl;
        cout << "  3. Print Course" << endl;
        cout << "  4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter the name of the file to load: ";
            cin >> csvPath;
            loadCourseData(csvPath, bst);
            break;

        case 2:
            cout << "Here is a sample schedule:" << endl;
            bst->printSampleSchedule();                                                                                                                                                                                                                    
            break;

        case 3:
            cout << "What course do you want to know about?" << endl;
            cin >> courseNumber;
            bst->printCourseInformation(courseNumber);
            break;

        case 4:
            cout << "Thank you for using the course planner." << endl;
            break;
        default: 
            cout << "Goodbye." << endl;
            break;
        }
           
            
    }
        
}