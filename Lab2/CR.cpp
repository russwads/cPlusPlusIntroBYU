#include<sstream>
#include"CR.h"
#include"COURSE.h"

using namespace std;

CR::CR()
{
	Course c;
	this->room = "THX 1138";
}
CR::CR(string in_courName, string in_room) : Course(in_courName)
{
	this->room = in_room;
}
CR::~CR() {};

string CR::getRoom() { return room; }
string CR::TOSTRING() const
{
	ostringstream ss;
	ss << "cr" << Course::TOSTRING() << room << ')';
	return ss.str();
}