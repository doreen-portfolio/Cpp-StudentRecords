/**
 *  student.h
 */
#include "name.h"
#include "grade.h"

/**
 *  Student
 *  
 *  Class that creates Student object that stores an id as string and a first and last names in a Name object and courses and grades in a vector of Grade objects.
 */
class Student 
{
public:
	/**
	 *  empty Student constructor
	 */
	Student(){}
	/**
	 *  Student constructor
	 */
	Student(std::string id,  Name& n, std::vector<Grade> v)
	{
		id_          = id;
		name_        = n;
		gradeVector_ = v;
	}
	friend class Grade;
	friend class FindID;
	friend class FindFname;
	friend class FindLname;
	friend class FindCourse;
	friend class FindGrade;
	friend class FindCourseGrade;
	friend class FindCourseGradeRange;
	friend std::ostream& operator<<(std::ostream& os, const Student& s);
	friend std::istream& operator>>(std::istream& is, Student& s);
	friend bool cmp(const Student& s1, const Student& s2);
	void display(std::ostream& os) const
	{
		os << id_ << std::endl << name_ << std::endl;
		for(std::vector<Grade>::size_type i = 0; i < gradeVector_.size(); ++i)
		{
			os << gradeVector_[i] << std::endl;
		}
	}
	void display_id(std::ostream& os) const
	{
		os << id_ << std::endl;
	}
private:
	int                ncourses;
	std::string        id_; // e.g. a11111111
	Name               name_;
	std::vector<Grade> gradeVector_; // vector of Grades to store all courses and their scores
};

/**
 *  overloaded ostream operator to output Student object's id, first and last names, and courses and grades.
 */
inline std::ostream& operator<<(std::ostream& os, const Student& s)
{
	os << s.id_ << std::endl << s.name_ << std::endl;
	for(std::vector<Grade>::size_type i = 0; i < s.gradeVector_.size(); ++i)
	{
		os << s.gradeVector_[i] << std::endl;
	}
	return os;
}

/**
 *  overloaded istream operator to take input and store them as id, first and last names, and courses and grades in Student object. 
 */
inline std::istream& operator>>(std::istream& is, Student& s)
{
	Grade g;
	s.gradeVector_.clear();
	is >> s.id_ >> s.name_ >> s.ncourses;
	for(int i = 0; i < s.ncourses; i++)
	{
		is >> g;
		s.gradeVector_.push_back(g);
	}
	return is;
}