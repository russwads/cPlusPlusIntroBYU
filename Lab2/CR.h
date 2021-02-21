#ifndef CR_H
#define CR_H

#include"COURSE.h"
#include<string>

using namespace std;

class CR : public Course
{
private:
	string room;

public:
	CR();
	CR(string in_courName, string in_room);
	~CR();

	string getRoom();
	string TOSTRING() const;
};

#endif
