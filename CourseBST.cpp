//Name: CourseBST.cpp
//Author: Cody Faircloth

#include <iostream>
#include <fstream>
#include "CSVParser.hpp"

using namespace std;

struct Course {
	string courseNumber;
	string courseName;
	vector<string> prerequisites;

	Course() {}
};



struct Node {
	Course course;
	Node* left;
	Node* right;

	Node() {
		left = nullptr;
		right = nullptr;
	}

	Node(Course nextCourse) : Node() {
		this->course = nextCourse;
	}
};

class CourseBST {
private:
	Node* root;
	void addNode(Node* node, Course course);
	void printSampleSchedule(Node* node);
	void printCourseInformation(Node* node, string courseNum);
public:
	CourseBST();
	virtual ~CourseBST();
	void DeleteRecursive(Node* node);
	void Insert(Course course);
	int NumPrerequisiteCourses(Course course);
	void PrintSampleSchedule();
	void PrintCourseInformation(string courseNum);
};
//BST constructor; sets root to nullptr
CourseBST::CourseBST() {
	root = nullptr;
}
//BST Destructor
CourseBST::~CourseBST() {
	DeleteRecursive(root);
}
//Recursively deletes BST; used by Destructor
void CourseBST::DeleteRecursive(Node* node) {
	if (node) {
		DeleteRecursive(node->left);
		DeleteRecursive(node->right);
		delete node;
	}
}
//Inserts node into BST
void CourseBST::Insert(Course course) {
	//If root is nullptr, assign course object to root
	if (root == nullptr) {
		root = new Node(course);
	}
	//Else call addNode() function with root and course object
	else {
		addNode(root, course);
	}
}
//Returns number of prerequisites for the course object
int CourseBST::NumPrerequisiteCourses(Course course) {
	int count = 0;
	for (unsigned int i = 0; i < course.prerequisites.size(); i++) {
		if (course.prerequisites.at(i).length() > 0) {
			count++;
		}
	}
	return count;
}
//Passes root to printSampleSchedule() to print BST in alphanumeric order
void CourseBST::PrintSampleSchedule() {
	printSampleSchedule(root);
}
//Passes BST root and courseNumber to printCourseInformation() for search and printing
void CourseBST::PrintCourseInformation(string courseNum) {
	printCourseInformation(root, courseNum);
}
//Determines and sets correct alphanumeric location for course object based on courseNumber
void CourseBST::addNode(Node* node, Course course) {
	//If course object courseNumber is less than current node's courseNumber
	if (node->course.courseNumber.compare(course.courseNumber) > 0) {
		//If left child node is nullptr, assign to left child node
		if (node->left == nullptr) {
			node->left = new Node(course);
		}
		//Else traverse the left child node
		else {
			addNode(node->left, course);
		}
	}
	//Else course object course number is greater than current node's courseNumber
	else {
		//If right child node is nullptr, assign to right child node
		if (node->right == nullptr) {
			node->right = new Node(course);
		}
		//Else traverse the right child node
		else {
			addNode(node->right, course);
		}
	}
}
//Prints BST of course objects in order using recursive function calls
void CourseBST::printSampleSchedule(Node* node) {
	if (node != nullptr) {
		printSampleSchedule(node->left);
		cout << node->course.courseNumber << ", " << node->course.courseName << endl;
		printSampleSchedule(node->right);
	}
	return;
}
//Displays the course information including prerequisites of a passed courseNumber
void CourseBST::printCourseInformation(Node* curr, string courseNum) {
	//Traverse BST until courseNumber is matched or end of tree is reached
	while (curr != nullptr) {
		//If passed courseNumber matches current node's courseNum
		if (curr->course.courseNumber.compare(courseNum) == 0) {
			//Print courseNumber and courseName
			cout << endl << curr->course.courseNumber << ", " << curr->course.courseName << endl;
			unsigned int size = NumPrerequisiteCourses(curr->course);
			cout << "Prerequisite(s): ";
			//If prerequisites exist iterate throught prerequistites and print each
			if (size > 0) {
				for (unsigned int i = 0; i < size; i++) {
					cout << curr->course.prerequisites.at(i);
					if (i != size - 1) {
						cout << ", ";
					}
				}
			}
			//If no prerequisites exist print none
			else {
				cout << "None";
			}
			cout << endl;
			return;
		}
		//If passed courseNumnber is less than curr's courseNumber traverse down left child node
		else if (courseNum.compare(curr->course.courseNumber) < 0) {
			curr = curr->left;
		}
		//If passed courseNumber is greater than curr's courseNumber traverse down right child node
		else {
			curr = curr->right;
		}
	}
	//If course not found inform user
	cout << "Course " << courseNum << " not found." << endl;
}
//Loads courses into BST
void loadCourses(string csvPath, CourseBST* coursesBST) {
	cout << "Loading CSV file " << csvPath << endl;
	csv::Parser courseFile = csv::Parser(csvPath);
	vector<string> header = courseFile.getHeader();
	for (auto const& c : header) {
		cout << c << " | ";
	}
	cout << "" << endl;

	try {
		for (unsigned int i = 0; i < courseFile.rowCount(); i++) {
			Course course;
			course.courseNumber = courseFile[i][0];
			course.courseName = courseFile[i][1];
			if (courseFile[i][2].compare("") > 0) {
				course.prerequisites.push_back(courseFile[i][2]);
			}
			if (courseFile[i][3].compare("") > 0) {
				course.prerequisites.push_back(courseFile[i][3]);
			}
			coursesBST->Insert(course);
		}
	}


	catch (csv::Error &e) {
		std::cerr << e.what() << std::endl;

	}

}

//Main
int main(int argc, char* argv[]) {
	//Command line args
	string csvPath;
	string courseId;
	switch (argc) {
	case 2:
		csvPath = argv[1];
		break;
	case 3:
		csvPath = argv[1];
		courseId = argv[2];
		break;
	default:
		csvPath = "";
		courseId = "";
		break;
	}

	CourseBST* coursesBST = nullptr;
	cout << "Welcome to the course planner." << endl;
	cout << endl;
	int userChoice = 0;

	while (userChoice != 9) {
		cout << "  1. Load Data Structure." << endl;
		cout << "  2. Print Course List." << endl;
		cout << "  3. Print Course." << endl;
		cout << "  9. Exit." << endl;
		cout << endl;
		cout << "What would you like to do? ";
		cin >> userChoice;

		switch (userChoice) {
		case 1:
			if (coursesBST == nullptr) {
				coursesBST = new CourseBST();
			}
			if (csvPath.length() == 0) {
				cout << "Enter the file name: ";
				cin >> csvPath;
			}
			loadCourses(csvPath, coursesBST);
			csvPath = "";
			break;
		case 2:
			if (coursesBST != nullptr) {
				cout << "Here is a sample schedule: " << endl;
				cout << endl;
				coursesBST->PrintSampleSchedule();
				cout << endl;
			}
			else {
				cout << "No courses have been loaded. Try option 1." << endl;
				cout << endl;
			}
			break;
		case 3:
			if (coursesBST != nullptr) {
				if (courseId.length() == 0) {
					cout << "What course do you want to know about? ";
					cin >> courseId;
					for (auto& userChoice : courseId) userChoice = toupper(userChoice);
				}
				coursesBST->PrintCourseInformation(courseId);
				cout << endl;
			}
			else {
				cout << "No courses have been loaded. Try option 1." << endl;
				cout << endl;
			}
			courseId = "";
			break;
		default:
			if (userChoice != 9) {
				cout << userChoice << " is not a valid option." << endl;
			}
			break;
		}
	}
	cout << "Thank you for using the course planner!" << endl;
	return 0;
}
