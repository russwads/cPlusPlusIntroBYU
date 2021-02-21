#ifndef CSG_H
#define CSG_H

#include"COURSE.h"
#include<string>

using namespace std;

class CSG : public Course
{
private:
	int studentID;
	string grade;
	friend class SNAP;

public:
	CSG();
	CSG(string in_courName, int in_studID, string in_grade);
	~CSG();

	int getStudID();
	string getGrade();
	string TOSTRING() const;
};

#endif
