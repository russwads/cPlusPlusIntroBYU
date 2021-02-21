#include<sstream>
#include"CDH.h"
#include"COURSE.h"

using namespace std;

CDH::CDH()
{
	Course b;
	this->days = "CRAP";
	this->hour = "25:10";
}
CDH::CDH(string in_courName, string day, string in_hour) : Course(in_courName)
{
	this->days = day;
	this->hour = in_hour;
}
CDH::~CDH() {};

string CDH::getHour() { return hour; }
string CDH::getDays() { return days; }
string CDH::TOSTRING() const
{
	ostringstream ss;
	ss << "cdh" << Course::TOSTRING() << days << ',' << hour << ')';
	return ss.str();
}