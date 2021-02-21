#ifndef CDH_H
#define CDH_H

#include"COURSE.h"
#include<string>

using namespace std;

class CDH : public Course
{
	string days;
	string hour;
	friend class CR;

public:
	CDH();
	CDH(string in_courName, string day, string in_hour);
	~CDH();

	string getDays();
	string getHour();
	string TOSTRING() const;
};

#endif
