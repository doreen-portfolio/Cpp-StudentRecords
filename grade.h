/**
 *  grade.h
 */

/**
 *  Grade
 *  
 *  Class that stores a course as a string and a score as an int in Grade object.
 */
class Grade 
{
public:
	/**
	 *  empty Grade constructor.
	 */
	Grade(){}
	/**
	 *  Grade constructor.
	 */
	Grade(const std::string c, int s)
	{
		course_ = c;
		score_  = s;
	}
	friend class Student;
	friend class FindCourse;
	friend class FindGrade;
	friend class FindCourseGrade;
	friend class FindCourseGradeRange;
	friend std::ostream& operator<<(std::ostream& os, const Grade& g); // sample output: comp3512 90
	friend std::istream& operator>>(std::istream& is, Grade& g);
private:
	std::string course_; // e.g. comp3512
	int score_; // e.g. 90
};

/**
 *  overloaded ostream operator to output Grade object's course and score.
 */
inline std::ostream& operator<<(std::ostream& os, const Grade& g)
{
	return os << g.course_ << " " << g.score_;
}

/**
 *  overloaded istream operator to take input and store as course and score in a Grade object.
 */
inline std::istream& operator>>(std::istream& is, Grade& g)
{
	return is >> g.course_ >> g.score_;
}