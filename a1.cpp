/**
 *  DOREEN CHAN-YING
 *  COMP3512
 *  ASSIGNMENT 1
 *  
 *  a1.cpp
 *  @version 1
 */

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>
#include <cstring>
#include <iterator>
#include <vector>
#include <algorithm>
#include "student.h"
using namespace std;

/**
 * 	PROTOTYPES
 */
bool get_cmd(const string& prompt, char*oneline);
bool cmp(const Student& s1, const Student& s2);

/**
 * 	FUNCTORS
 */
/**
 *  FindID
 *  
 *  Function class that returns true if a Student has a matching id, otherwise it returns false if a Student does not have a matching id.
 *
 */
class FindID 
{
    std::string x_; /* id to be found */
public:
    FindID(const std::string& x) : x_(x) {}
    bool operator()(const Student& s)
	{ 
		return s.id_ == x_; 
	}
};

/**
 *  FindFname
 *  
 *  Function class that returns true if a Student has a matching first name, otherwise it returns false if a Student does not have a matching first name.
 *
 */
class FindFname 
{
    std::string x_; /* first name to be found */
public:
    FindFname(const std::string& x) : x_(x) {}
    bool operator()(const Student& s)
	{ 
		return s.name_.first_ == x_; 
	}
};

/**
 *  FindLname
 *  
 *  Function class that returns true if a Student has a matching last name, otherwise it returns false if a Student does not have a matching last name.
 *
 */
class FindLname 
{
    std::string x_; /* last name to be found */
public:
    FindLname(const std::string& x) : x_(x) {}
    bool operator()(const Student& s)
	{ 
		return s.name_.last_ == x_; 
	}
};

/**
 *  FindCourseGrade
 *  
 *  Function class that returns 1 if a Student has a matching course and associated grade, otherwise it returns 0 if a Student does not have a matching course and grade.
 *
 */
class FindCourseGrade 
{
    std::string c_; /* course to be found */
	int x_; /* grade to be found */
public:
    FindCourseGrade(const std::string& c, const int& x) : c_(c), x_(x) {}
    bool operator()(const Student& s)
	{ 
		for(vector<Grade>::size_type i = 0; i < s.gradeVector_.size(); i++)
		{ 
			if (s.gradeVector_[i].course_ == c_ && s.gradeVector_[i].score_ == x_)
			{
				return true;
			}
		}
		return false;
	}
};

/**
 *  FindCourseGradeRange
 *  
 *  Function class that returns 1 if a Student has a matching course and its associated grade is within the specified range,
 otherwise it returns 0 if a Student does not have a matching course and grade that falls within range.
 *
 */
class FindCourseGradeRange 
{
    std::string c_; /* course to be found */
	int low_; /* low end of grade range */
	int high_; /* high end of grade range */
public:
    FindCourseGradeRange(const std::string& c, const int& low, const int& high) : c_(c), low_(low),high_(high)  {}
    bool operator()(const Student& s)
	{ 
		for(vector<Grade>::size_type i = 0; i < s.gradeVector_.size(); i++)
		{ 
			if (s.gradeVector_[i].course_ == c_)
			{
				if(s.gradeVector_[i].score_ >= low_ && s.gradeVector_[i].score_ <= high_)
				{
					return true;
				}
			}
		}
		return false;
	}
};

/**
 *  main
 *  
 *  Reads Student objects from a specified file and stores them in a vector of Students. The vector of Students is sorted in ascending order by student id using the STL sort function and cmp function. In a while loop, the program prompts the user for a command. The command is stored in a char array and tokenized for each word.
 *
 *  If the user calls "show", all Student records are displayed. If the user calls "showid", all the Student ids are displayed. 
 *
 *  If the user calls "id" followed by a id after "show" or "showid", the record matching that id will be displayed if it is found. Otherwise if the id is not found, a blank line is displayed.
 *
 *  If the user calls "name" followed by a first and a last name (which can be "*" to indicated all) after "show" or "showid", the records matching that name will be displayed if it is found. Otherwise if the name is not found, a blank line is displayed.
 * 
 *  If the user calls "grade" followed by a course name and one integer after "show" or "showid", the records that have that course and associated grade matching that integer will be displayed. Otherwise if a matching record is not found, a blank line is displayed.
 *
 *  If the user calls "grade" followed by a course name and two integers after "show" or "showid", the records that have that course and an associated grade that is within the range of the two integers specifed will be displayed. Otherwise if a matching record is not found, a blank line is displayed.
 *
 *  If the user inputs an invalid command, then a blank line is displayed.  
 *
 *  @functionCall get_cmd Displays menu to prompt user for a command and stores command in a char array.
 *  @functionCall cmp Sorts Student objects in ascending order by student id.
 *
 *  @param argc number of arguments.
 * 	@param argv argument.
 *
 */
int main(int argc, char* argv[])
{
	Student         s; /* Student object to store */
	vector<Student> studentVector; /* vector of Students to store Student objects */
	string          cmd1;
	string          cmd2;
	string          id;
	string          fname;
	string          lname;
	string          course;
	int             grade;
	int             gradehigh;
	int             gradelow;
	char            oneline[256]; /* char array that stores user input */
	vector<char*>   cmdvec; /* vector of char* to store user input as tokens */
	char*           token; /* char* token to tokenize user input */
	
	if(argc != 2) 
	{
		cerr << "usage: " << argv[0] << " <source file>\n";
		return 0;
	}
	ifstream f(argv[1]);
	if(!f)
	{
		cerr << "unable to open " << argv[1] << endl;
		return 1;
	}
	/*
	 *  Reads in Student objects from a file and stores them in a vector of Students.
	 */
	while(f >> s)
	{
		studentVector.push_back(s);
	}
	/*
	 *  Sorts Student vector in ascending order by student id.
	 */
	sort(studentVector.begin(), studentVector.end(), cmp);
	
	string menu ="=========================MENU=========================\n1) show: displays all the info about matching records\n2) showid: only displays the IDs of matching records\n3) [show | showid] name <first name> <last name>: shows students matching first name and last name\n4) [show | showid] name <first name> *: shows students matching first name\n5) [show | showid] name * <last name>: shows students matching last name\n6) [show | showid] grade <course> <grade>: shows students with matching course and grade\n7) [show | showid] grade <course> <low grade> <high grade>: shows students whose grade in course is between low grade and high grade\n======================================================\n";
	/*
	 *  Prompts user by displaying menu and storing user input in a char array. Tokenizes words in char array and searches records based on specified commands.
	 */
	while(get_cmd(menu, oneline))
	{
		token = strtok(oneline, " ");
		cmdvec.push_back(token);
		while((token = strtok(NULL, " ")) != NULL)
		{
			cmdvec.push_back(token);
		}
		if(cmdvec.size() == 1 && cmdvec[0] == NULL)
		{
			cmdvec.clear();
			cout << endl;
			continue;
		}
		
		if(cmdvec.size() == 1)
		{
			cmd1 = cmdvec[0];
			/*
			 *  display all Student records.
			 */
			if(cmd1.compare("show") == 0)
			{
				for(vector<Student>::size_type i = 0; i < studentVector.size(); i++) 
				{
					studentVector[i].display(cout);
				}
				cout << endl;
			}
			/*
			 *  display all Student ids.
			 */
			else if(cmd1.compare("showid") == 0)
			{
				for(vector<Student>::size_type i = 0; i < studentVector.size(); i++) 
				{
					studentVector[i].display_id(cout);
				}
				cout << endl;
			} 
			else 
			{
				cout << endl;
			}
		}
		else if(cmdvec.size() > 1)
		{
			cmd1 = cmdvec[0];
			cmd2 = cmdvec[1];
			if(cmd1.compare("show") == 0) 
			{
				/*
				 *  find Student records by student id.
				 */
				if(cmd2.compare("id") == 0)
				{
					id = cmdvec[2];
					vector<Student>::iterator it =
						std::find_if(studentVector.begin(), studentVector.end(),
							FindID(id));
					if (it != studentVector.end()) 
					{
						cout << *it;
					} 
					cout << endl;
				}
				/*
				 *  display all Student records.
				 */
				else if(cmd2.compare("name") == 0)
				{
					fname = cmdvec[2];
					lname = cmdvec[3];
					if(fname == "*" && lname == "*")
					{
						for(vector<Student>::size_type i = 0; i < studentVector.size(); i++) 
						{
							studentVector[i].display(cout);
						}
					}
					/*
					 *  find Student records by first name.
					 */
					if(fname != "*" && lname == "*")
					{
						vector<Student>::iterator it =
						find_if(studentVector.begin(), studentVector.end(), FindFname(fname));
						while (it != studentVector.end()) 
						{
							cout << *it;
							it =
							find_if(it+1, studentVector.end(), FindFname(fname));
						}
					}
					/*
					 *  find Student records by last name.
					 */
					if(fname == "*" && lname != "*")
					{
						vector<Student>::iterator it =
						find_if(studentVector.begin(), studentVector.end(),	FindLname(lname));
						while (it != studentVector.end()) 
						{
							cout << *it;
							it =
							find_if(it+1, studentVector.end(), FindLname(lname));
						}
					}
					/*
					 *  find Student records by both first and last names.
					 */
					if(fname != "*" && lname != "*")
					{
						vector<Student> temp;
						vector<Student>::iterator it =
						find_if(studentVector.begin(), studentVector.end(),	FindFname(fname));
						while (it != studentVector.end()) 
						{
							temp.push_back(*it);
							it =
							find_if(it+1, studentVector.end(), FindFname(fname));
						}
						it =
						find_if(temp.begin(), temp.end(),	FindLname(lname));
						while (it != temp.end()) 
						{
							cout << *it;
							it =
							find_if(it+1, temp.end(), FindLname(lname));
						}
					}
					cout << endl;
				}
				/*
				 *  find Student records by course and grade.
				 */
				else if(cmd2.compare("grade") == 0)
				{
					course = cmdvec[2];
					if(cmdvec.size() == 4) 
					{ 
						istringstream buffer1(cmdvec[3]); 
						buffer1 >> grade;
						vector<Student>::iterator it =
						find_if(studentVector.begin(), studentVector.end(), FindCourseGrade(course, grade));
						while (it != studentVector.end()) 
						{
							cout << *it;
							it =
							find_if(it+1, studentVector.end(), FindCourseGrade(course, grade));
						}
					} 
					/*
					 *  search and display Student records by course and grade range.
					 */
					else if(cmdvec.size() == 5) 
					{ 
						vector<Student> tempVec;
						istringstream buffer2(cmdvec[3]);
						buffer2 >> gradelow;
						istringstream buffer3(cmdvec[4]);
						buffer3 >> gradehigh;
						vector<Student>::iterator it =
						find_if(studentVector.begin(), studentVector.end(), FindCourseGradeRange(course, gradelow, gradehigh));
						while (it != studentVector.end()) 
						{
							cout << *it;
							it =
							find_if(it+1, studentVector.end(), FindCourseGradeRange(course, gradelow, gradehigh));
						}
					}
					cout << endl;
				}
			}
			if(cmd1.compare("showid") == 0) 
			{
				/*
				 *  find specified student id.
				 */
				if(cmd2.compare("id") == 0)
				{
					id = cmdvec[2];
					vector<Student>::iterator it =
						std::find_if(studentVector.begin(), studentVector.end(),
							FindID(id));
					if (it != studentVector.end()) 
					{
						Student temp = *it;
						temp.display_id(cout);
					}
					cout << endl;
				}
				else if(cmd2.compare("name") == 0)
				{
					fname = cmdvec[2];
					lname = cmdvec[3];
					/*
					 *  display all student ids.
					 */
					if(fname == "*" && lname == "*")
					{
						for(vector<Student>::size_type i = 0; i < studentVector.size(); i++) 
						{
							studentVector[i].display_id(cout);
						}
					}
					/*
					 *  find student ids by first names.
					 */
					if(fname != "*" && lname == "*")
					{
						vector<Student>::iterator it =
						find_if(studentVector.begin(), studentVector.end(), FindFname(fname));
						while (it != studentVector.end()) 
						{
							Student temp = *it;
							temp.display_id(cout);
							it =
							find_if(it+1, studentVector.end(), FindFname(fname));
						}
					}
					/*
					 *  find student ids by last names.
					 */
					if(fname == "*" && lname != "*")
					{
						vector<Student>::iterator it =
						find_if(studentVector.begin(), studentVector.end(), FindLname(lname));
						while (it != studentVector.end()) 
						{
							Student temp = *it;
							temp.display_id(cout);
							it =
							find_if(it+1, studentVector.end(), FindLname(lname));
						}
					}
					/*
					 *  find student ids by both first and last names.
					 */
					if(fname != "*" && lname != "*")
					{
						vector<Student> tempVec;
						vector<Student>::iterator it =
						find_if(studentVector.begin(), studentVector.end(),	FindFname(fname));
						while (it != studentVector.end()) 
						{
							tempVec.push_back(*it);
							it =
							find_if(it+1, studentVector.end(), FindFname(fname));
						}
						it =
						find_if(tempVec.begin(), tempVec.end(),	FindLname(lname));
						while (it != tempVec.end()) 
						{
							Student temp = *it;
							temp.display_id(cout);
							it =
							find_if(it+1, tempVec.end(), FindLname(lname));
						}
					}
					cout << endl;
				}
				/*
				 *  find student ids by grade.
				 */
				else if(cmd2.compare("grade") == 0)
				{
					course = cmdvec[2];
					/*
					 *  find student ids by course and grade.
					 */
					if(cmdvec.size() == 4) 
					{ 
						istringstream buffer4(cmdvec[3]);
						buffer4 >> grade; 
						
						vector<Student>::iterator it =
						find_if(studentVector.begin(), studentVector.end(), FindCourseGrade(course, grade));
						while (it != studentVector.end()) 
						{
							Student temp = *it;
							temp.display_id(cout);
							it =
							find_if(it+1, studentVector.end(), FindCourseGrade(course, grade));
						}
					} 
					/*
					 *  find student ids by course and grade range.
					 */
					else if(cmdvec.size() == 5) 
					{ 
						istringstream buffer5(cmdvec[3]);
						buffer5 >> gradelow;
						istringstream buffer6(cmdvec[4]);
						buffer6 >> gradehigh;
						vector<Student>::iterator it =
						find_if(studentVector.begin(), studentVector.end(), FindCourseGradeRange(course, gradelow, gradehigh));
						while (it != studentVector.end()) 
						{
							Student temp = *it;
							temp.display_id(cout);
							it =
							find_if(it+1, studentVector.end(), FindCourseGradeRange(course, gradelow, gradehigh));
						}
					}
					cout << endl;
				}
			}
		} 
		else 
		{
			cout << endl;
		}
		/*
		 *  clears the vector of command tokens.
		 */
		cmdvec.clear();
	}
}

/**
 *  get_cmd
 * 
 *  Displays prompt and reads in a line, storing it into char array. 
 *  
 *  @param prompt  string to prompt user for a command.
 *  @param oneline	 char array to store command.
 *
 *  @return bool  true if successful in reading in a line, false if unsuccessful in reading in a line.
 *
 */
bool get_cmd(const string& prompt, char* oneline)
{
	while(1)
	{
		cerr << prompt;
		if(!cin.getline(oneline, 256))
		{
			cin.clear();
			break;
		} else {
			return true;
		}
	}
	return false;
}

/**
 *  cmp
 * 
 *  Compares Student objects to sort them in ascending order by student id. 
 *  
 *  @param s1  first Student.
 *  @param s2  second Student.
 *
 *  @return bool  true if the first Student's id is smaller than the second Student's, false if the first Student's id is larger than the second Student's.
 *
 */
bool cmp(const Student& s1, const Student& s2) 
{
	return s1.id_ < s2.id_; 
}