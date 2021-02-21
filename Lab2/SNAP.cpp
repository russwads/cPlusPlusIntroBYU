#include<sstream>
#include"SNAP.h"

using namespace std;

SNAP::SNAP()
{
	this->studentID = 84121;
	this->name = "John Doe";
	this->address = "123 Fake St";
	this->phone_number = "KL5-3226";
}
SNAP::SNAP(int in_studentID, string in_name, string in_address, string in_phone)
{
	this->studentID = in_studentID;
	this->name = in_name;
	this->address = in_address;
	this->phone_number = in_phone;
}
SNAP::~SNAP() {};

int SNAP::getStudID() { return studentID; }
string SNAP::getName() { return name; }
string SNAP::getAddress() { return address; }
string SNAP::getPhone() { return phone_number; }
string SNAP::TOSTRING() const
{
	ostringstream ss;
	ss << "snap(" << studentID << ',' << name << ',' << address << ',' << phone_number << ')';
	return ss.str();
}
string SNAP::DIRECTORY() const
{
	ostringstream ss;
	ss << name << ", " << studentID << ", " << address << ", " << phone_number;
	return ss.str();
}