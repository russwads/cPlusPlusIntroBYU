//C++ Include files
#include<iostream>
#include<string>
#include<vector>
#include<ctime>
#include<sstream>
#include<fstream>
#include<cstdlib>
#include<iomanip>
#include<cctype>

//SNAP LAB Include files
#include"CDH.h"
#include"COURSE.h"
#include"CR.h"
#include"CSG.h"
#include"SNAP.h"

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif

using namespace std;

/**
Deletes all class members in each vector
*/
void DeleteVectors(vector<SNAP*> &snaps, vector<CSG*> &csgs, vector<CDH*> &cdhs, vector<CR*> &crs)
{
	for (int i = 0; i < snaps.size(); i++)
	{
		delete snaps[i];
	}
	for (int i = 0; i < csgs.size(); i++)
	{
		delete csgs[i];
	}
	for (int i = 0; i < cdhs.size(); i++)
	{
		delete cdhs[i];
	}
	for (int i = 0; i < crs.size(); i++)
	{
		delete crs[i];
	}
}
/**
Parses CDH class members to match course days together
Returns function into one string
(ex. 
Input:
cdh(CS101,M,9AM)
cdh(CS101,W,9AM)
cdh(CS101,F,9AM)

Output:
MWF
*/
string MatchDays(vector<CDH*> cdhs, int i)
{
	string in_cour = cdhs[i]->getCourName();
	string days;
	string test = cdhs[i]->getDays();
	if ((test != "M") || (test != "T"))
	{
		if ((test == "W") || (test == "Th")) { i--; }
		else {}
	}
	else {}
	for (i; i < cdhs.size(); i++)
	{
		string buffer = cdhs[i]->getCourName();
		if (in_cour == buffer)
		{
			string daybuff = cdhs[i]->getDays();
			days += daybuff;
		}
	}
	return days;
}
/**
Parsing through input lines and files to create strings with correct length
Used for names, addresses, phone numbers, etc.
*/
string WordReturn(string line, int i)
{
	string currentWord = "";
	for (i; i < line.length(); i++)
	{
		if ((ispunct(line[i]))&&(line[i] != '-')&&(line[i] != '+'))
		{
			return currentWord;
		}
		else
		{
			currentWord += line[i];
		}
	}
	return "WT??";
}
/**
Creates a CR (course,room) class and adds it to the CR pointer vector
*/
int CRMaker(string line, int i, string in_coursName, string in_room, vector<CR*> &crs)
{
	i = 3;
	in_coursName = WordReturn(line, i);
	i = i + in_coursName.length() + 1;
	in_room = WordReturn(line, i);
	CR* room = new CR(in_coursName, in_room);
	crs.push_back(room);
	return 0;
}
/**
Creates a CDH (course,day,hour) class and adds it to the CDH pointer vector
*/
int CDHMaker(string line, int i, string in_coursName, string in_days, string in_hour, vector<CDH*> &cdhs)
{
	i = 4;
	in_coursName = WordReturn(line, i);
	i = i + in_coursName.length() + 1;
	in_days = WordReturn(line, i);
	i = i + in_days.length() + 1;
	in_hour = WordReturn(line, i);
	CDH* info = new CDH(in_coursName, in_days, in_hour);
	cdhs.push_back(info);
	return 0;
}
/**
Creates a CSG (course,studentID,grade) class and adds it to the CSG pointer vector
*/
int CSGMaker(string line, int i, string in_coursName, int in_studID, string in_grade, vector<CSG*> &csgs)
{
	i = i + 1;
	in_coursName = WordReturn(line, i);
	i = i + in_coursName.length() + 1;
	string buffer;
	buffer = WordReturn(line, i);
	in_studID = stoi(buffer);
	i = i + buffer.length() + 1;
	in_grade = WordReturn(line, i);
	CSG* course = new CSG(in_coursName, in_studID, in_grade);
	csgs.push_back(course);
	return 0;
}
/**
Creates a SNAP (studentID,name,address,phone#) class and adds it to the SNAP pointer vector
*/
int SNAPMaker(string line, int i, int &in_studID, string in_name, string in_address, string in_phone, vector<SNAP*> &snaps)
{
	string currentWord = "";
	for (i; i < line.length(); i++)
	{
		if (ispunct(line[i]))
		{
			in_studID = stoi(currentWord);
			i = i + 1;
			currentWord = "";

			in_name = WordReturn(line,i);
			i = i + in_name.length()+1;
			in_address = WordReturn(line,i);
			i = i + in_address.length()+1;
			in_phone = WordReturn(line,i);
			SNAP* student = new SNAP(in_studID, in_name, in_address, in_phone);
			snaps.push_back(student);
			return 0;
		}
		else
		{
			currentWord += line[i];
		}
	}
	return 1110;
}

int main(int argc, char* argv[])
{
	VS_MEM_CHECK;	//Check for Memory Leaks

//*****************************************************************************************************************
//Opening in and out files argv[1] and argv[2]

	string line;
	ifstream inFile(argv[1]);
	if (argc < 1)
	{
		cout << "Insufficient File Number." << endl << "Please include in and out argument." << endl << "Exiting...";
		getline(cin, line);
		return -1;
	}
	if (!inFile)
	{
		cout << "Opening Reading File FAILED. Exiting..." << endl;
		return -1;
	}
	cout << "Opening Reading File Successful!" << endl;

	ofstream outFile(argv[2]);
	if (!outFile)
	{
		cout << "Opening Writing File FAILED. Exiting..." << endl;
		return -1;
	}
	cout << "Opening Writing File Successful!" << endl;

	vector<SNAP*> snaps;
	vector<CSG*> csgs;
	vector<CDH*> cdhs;
	vector<CR*> crs;

//*****************************************************************************************************************
// Reading in from File "inFile(argv[1])"
// Allocating Class Data & Writing Input Lines to "outFile(argv[2])"

	outFile << "Input Strings:" << endl;
	while (getline(inFile, line))
	{
		string currentWord;

		for (int i = 0; i < line.length(); i++)
		{
			try 
			{
				// Catches lines not starting with class names
				if (ispunct(line[i]))
				{
					if (currentWord == "snap")
					{
						int in_studID = 0;
						i = 5;
						string in_name;
						string in_address;
						string in_phone;
						SNAPMaker(line, i, in_studID, in_name, in_address, in_phone, snaps);
					}
					else if (currentWord == "csg")
					{
						string in_courName;
						int in_studentID = 0;
						string in_grade;
						CSGMaker(line, i, in_courName, in_studentID, in_grade, csgs);
					}
					else if (currentWord == "cdh")
					{
						string in_courName;
						string in_day;
						string in_hour;
						CDHMaker(line, i, in_courName, in_day, in_hour, cdhs);
					}
					else if (currentWord == "cr")
					{
						string in_courName;
						string in_room;
						CRMaker(line, i, in_courName, in_room, crs);
					}
				}
				else
				{
					// Add the character to the current word
					currentWord += line[i];
				}
			}
			catch (string param)
			{
				outFile << "Undefined Class";
			}
		}

		outFile << line << endl;
	}
	outFile << endl;

//*****************************************************************************************************************
//Writing Vectors

	outFile << "Vectors:" << endl;
	for (int i = 0; i < snaps.size(); i++)
	{
		outFile << snaps[i]->TOSTRING() << endl;
	}
	for (int i = 0; i < csgs.size(); i++)
	{
		outFile << csgs[i]->TOSTRING() << endl;
	}
	for (int i = 0; i < cdhs.size(); i++)
	{
		outFile << cdhs[i]->TOSTRING() << endl;
	}
	for (int i = 0; i < crs.size(); i++)
	{
		outFile << crs[i]->TOSTRING() << endl;
	}
	outFile << endl;

//*****************************************************************************************************************
//Writing Course Grades

	outFile << "Course Grades:" << endl;
	int i = 0;
	while (i < crs.size())
	{
		string cour = crs[i]->getCourName();
		string room = crs[i]->getRoom();
		for (int j = 0; j < cdhs.size(); j++)
		{
			string buff_cour1 = cdhs[j]->getCourName();
			if (buff_cour1 == cour)
			{
				string days = MatchDays(cdhs, j);
				for (int k = 0; k < csgs.size(); k++)
				{
					string buff_cour2 = csgs[k]->getCourName();
					if (buff_cour2 == cour)
					{
						int studID = csgs[k]->getStudID();
						string grade = csgs[k]->getGrade();
						for (int l = 0; l < snaps.size(); l++)
						{
							int buffstudID = snaps[l]->getStudID();
							if (buffstudID == studID)
							{
								string name = snaps[l]->getName();
								outFile << cour << " " << days << ", " << room << " ";
								outFile << name << " " << studID << ", " << grade << endl;
							}
						}
					}
				}
				break;
			}
		}
		i++;
		outFile << endl;
	}


//*****************************************************************************************************************
//Writing Student Schedules

	outFile << "Student Schedules:" << endl;

	for (int i = 0; i < snaps.size(); i++)
	{
		outFile << snaps[i]->DIRECTORY() << endl;
		string cSched;
		int identity = snaps[i]->getStudID();
		for (int j = 0; j < csgs.size(); j++)
		{
			int buffID = csgs[j]->getStudID();
			if (identity == buffID)
			{
				cSched = csgs[j]->getCourName();
				string buffClass1;
				for (int k = 0; k < cdhs.size(); k++)
				{
					buffClass1 = cdhs[k]->getCourName();
					if ((cSched == buffClass1) && (identity == buffID))
					{
						string buffDays = MatchDays(cdhs, k);
						string buffHour = cdhs[k]->getHour();
						for (int l = 0; l < crs.size(); l++)
						{
							string buffClass2 = crs[l]->getCourName();
							if (cSched == buffClass2)
							{
								string buffRoom = crs[l]->getRoom();
								outFile << "  " << cSched << " " << buffDays << " " << buffHour << ", " << buffRoom << endl;
							}
						}
						break;
					}
				}
			}
		}
		outFile << endl;
	}
	

//*****************************************************************************************************************
//Closing Files and Deleting Vector Pointers

	inFile.close();
	outFile.close();
	DeleteVectors(snaps, csgs, cdhs, crs);

	cout << "Writing successful. Closing..." << endl;
	return 0;
}