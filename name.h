/**
 *  name.h
 */

/**
 *  Name
 *  
 *  Class that stores a string as first name and a string as last name in Name object.
 */
class Name 
{
public:
	/**
	 *  empty Name constructor.
	 */
	Name(){}
	/**
	 *  Name constructor.
	 */
	Name(std::string fname, std::string lname)
	{
		first_ = fname;
		last_  = lname;
	}
	friend class Student;
	friend class FindFname;
	friend class FindLname;
	friend std::ostream& operator<<(std::ostream& os, const Name& n); // sample output: homer simpson
	friend std::istream& operator>>(std::istream& is, Name& n);
private:
	std::string first_; // e.g. homer
	std::string last_; // e.g. simpson
};

/**
 *  overloaded ostream operator to output Name object's first and last names.
 */
inline std::ostream& operator<<(std::ostream& os, const Name& n)
{
	return os << n.first_ << " " << n.last_;
}

/**
 *  overloaded istream operator to take input and store them as first and last names in a Name object
 */
inline std::istream& operator>>(std::istream& is, Name& n)
{
	return is >> n.first_ >> n.last_;
}
