C++ Student Records Program
===========================

This program reads in student records from a file, stores them in a vector and sorts them in ascending order by student id. The user may enter any of the following commands to retrieve student records:

1) show: displays all the info about matching records 
2) showid: only displays the IDs of matching records 
3) [show | showid] name [first name] [last name]: shows students matching first name and last name 
4) [show | showid] name [first name] *: shows students matching first name 
5) [show | showid] name * [last name]: shows students matching last name 
6) [show | showid] grade [course] [grade]: shows students with matching course and grade 
7) [show | showid] grade [course] [low grade] [high grade]: shows students whose grade in course is between low grade and high grade 

If an invalid command is entered, an empty line is printed.

To run the program, enter the following command: ./a1 input
