#ifndef SNAP_H
#define SNAP_H

#include<string>

using namespace std;

class SNAP
{
private:
	int studentID = 0;
	string name;
	string address;
	string phone_number;

public:
	SNAP();
	SNAP(int in_studentID, string in_name, string in_address, string in_phone);
	~SNAP();

	int getStudID();
	string getName();
	string getAddress();
	string getPhone();
	string TOSTRING() const;
	string DIRECTORY() const;
};

#endif
