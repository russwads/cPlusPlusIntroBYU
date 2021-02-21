#include<sstream>
#include"COURSE.h"

using namespace std;

Course::Course()
{
	this->courseName = "NSFW 666";
}
Course::Course(string in_courName)
{
	this->courseName = in_courName;
}
Course::~Course() {};

string Course::getCourName() { return courseName; }
string Course::TOSTRING() const
{
	ostringstream ss;
	ss << '(' << courseName << ',';
	return ss.str();
}