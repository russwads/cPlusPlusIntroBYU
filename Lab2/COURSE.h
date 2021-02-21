#ifndef COURSE_H
#define COURSE_H

#include<vector>
#include<string>

using namespace std;

class Course
{
private:
	string courseName;

public:
	Course();
	Course(string in_courName);
	~Course();

	string getCourName();
	string TOSTRING() const;
};


#endif
