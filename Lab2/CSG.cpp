#include<sstream>
#include"CSG.h"
#include"COURSE.h"
#include"SNAP.h"

using namespace std;

CSG::CSG()
{
	Course a;
	this->grade = "G-";
	this->studentID = 84121;
}
CSG::CSG(string in_courName, int in_studID, string in_grade) : Course(in_courName)
{
	this->grade = in_grade;
	this->studentID = in_studID;
}
CSG::~CSG() {};

int CSG::getStudID() { return studentID; }
string CSG::getGrade() { return grade; }
string CSG::TOSTRING() const
{
	ostringstream ss;
	ss << "csg" << Course::TOSTRING() << studentID << ',' << grade << ')';
	return ss.str();
}