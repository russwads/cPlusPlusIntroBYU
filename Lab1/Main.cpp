#include<iostream>
#include<string>
#include<vector>
#include<ctime>
#include<sstream>
#include<fstream>
#include<cstdlib>
#include<iomanip>
#include<cctype>

//Checks memory leak status
#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif

using namespace std;

/**
	Calculates the average for the test number
	@param students the number of students who took the test
	@param a array pointer that nests the students and their test scores
	@param test the test number undergoing a class average
*/
double AverageCalc(int students, int** a, int test) 
{
	double sumStud = 0;
	for (int i = 0; i < students; i++)
	{
		sumStud = sumStud + a[i][test];
	}
	double average = (sumStud / students);
	return average;
}

/**
	Same as AverageCalc, but determines entire class's score average
	@param
	@param
*/
double ClassAveCalc(int tests, double* c)
{
	double sumAve = 0;
	for (int i = 0; i < tests; i++) 
	{
		sumAve = sumAve + c[i];
	}
	double average = (sumAve / tests);
	return average;
}

/**
	Same as AverageCalc, but instead takes average test scores for each student
	@param
	@param
	@param
*/
double StudentAve(int tests, int** a, int student)
{
	double sumTest = 0;
	for (int i = 0; i < tests; i++)
	{
		sumTest = sumTest + a[student][i];
	}
	double average = (sumTest / tests);
	return average;
}

/**
	Calculates the grade 
	@param c an array of test averages
	@param
	@param
*/
string GradeCalc(double* c, int g, int grade)
{
	double BuffAve = c[g];
	double diff = grade - BuffAve;
	if (diff > 15) { return "A"; }
	else if ((diff <= 15) && (diff > 5)) { return "B"; }
	else if ((diff <= 5) && (diff > -5)) { return "C"; }
	else if ((diff <= -5) && (diff > -15)) { return "D"; }
	else if (diff <= -15) { return "E"; }
	else { return "FAIL"; }
}

/**
	Same as GradeCalc, but uses different parameters and calcualtes the student's grade on all tests
	@param
	@param
*/
string StudentGrade(double grade, double classAve)
{
	double diff = grade - classAve;
	if (diff > 15) { return "A"; }
	else if ((diff <= 15) && (diff > 5)) { return "B"; }
	else if ((diff <= 5) && (diff > -5)) { return "C"; }
	else if ((diff <= -5) && (diff > -15)) { return "D"; }
	else if (diff <= -15) { return "E"; }
	else { return "FAIL"; }
}

/**
	Uses array d to add totals for each grade in each test
	@param
	@param
	@param
	@param
	@param
*/
void GradeSort(int** a, double*c, int** d, int students, int tests)
{
	for (int j = 0; j < tests; j++) 
	{
		int accelsior = 0;
		int brilliant = 0;
		int commecica = 0;
		int danger = 0;
		int effortno = 0;
		for (int i = 0; i < students; i++)
		{
			int grade = a[i][j];
			string test = GradeCalc(c, j, grade);
			if (test == "A") { accelsior++; }
			else if (test == "B") { brilliant++; }
			else if (test == "C") { commecica++; }
			else if (test == "D") { danger++; }
			else if (test == "E") {	effortno++;	}
			else { cout << "FAIL"; }
		}
		d[j][0] = accelsior;
		d[j][1] = brilliant;
		d[j][2] = commecica;
		d[j][3] = danger;
		d[j][4] = effortno;
	}
}

/**
	Deletes arrays to ensure there are no memory links by the end of the program
	@param a
	@param b
	@param c
	@param d 
	@param students
	@param tests
*/
double DeleteArray(int** a, string* b, double* c, int** d, double* e, int students, int tests)
{
	//Deletes pointer array for test scores
	for (int i = 0; i < students; i++)
	{
/*		for (int j = 0; j < tests; j++)
		{
			delete a[i][j];
		}
*/		delete[] a[i];
	}
	delete[] a;
	
	//Deletes pointer array for student names
/*	for (int i = 0; i < students; i++)
	{
		delete b[i];
	}
*/	delete[] b;

	//Deletes pointer array for test averages
/*	for (int i = 0; i < tests; i++)
	{
		delete c[i];
	}
*/	delete[] c;

	//Deletes pointer array for grade counts
	for (int i = 0; i < tests; i++)
	{
/*		for (int j = 0; j < 5; j++)
		{
			delete &d[i][j];
		}
*/		delete[] d[i];
	}
	delete[] d;

	//Deletes pointer array for student averages
	/*	for (int i = 0; i < students; i++)
	{
	delete e[i];
	}
	*/	delete[] e;

	return 0;
}

int main(int argc, char* argv[]) 
{
	VS_MEM_CHECK;	//Check for Memory Leaks

	int students = 0;
	int tests = 0;
	
	string line;
	cout << "Reading Files..." << endl;
	ifstream inFile(argv[1]); //Opening file including test scores
	if (argc < 1) 
	{
		cout << "Insufficient File Number." << endl << "Please include in and out argument." << endl << "Exiting...";
		return -1;
	}
	if (!inFile) 
	{
		cout << "Opening Reading File FAILED. Exiting..." << endl;
		return -1;
	}
	cout << "Opening Reading File Successful!" << endl;
	inFile >> students >> tests;	

	//Dynamic Int Array for the scores of each student
	//a[i][j] = i resembles the number of students; j resembles the number of tests.
	int** a = new int*[students];
	for (int i = 0; i < students; ++i) 
	{
		a[i] = new int[tests];
	}
	//Dynamic String Array for the names of students
	//b[i] = i resembles the number of students
	string* b = new string[students];
	int r = 0 - 1;

//*****************************************************************************************************************
// Reading in from File "inFile(argv[1])"
// Allocating Student and Test data

	while (getline(inFile, line)) 
	{
		if (!isalnum(line[0])) 
		{  }
		else 
		{
			//Integers i searches for when digit begins
			int i = 0;
			while (!isdigit(line[i])) { i++; }
			int q = i;
			//Integer j searches for when name ends
			int j = i - 1;
			while (isspace(line[j])) { j--; }

			//Enters integers into Int array
			for (int k = 0; k < tests; k++)
			{
				//Counts the number of steps q travels to get to the space
				int count = 0;
				while (!isspace(line[q]) && q < line.length()) { q++; count++; }
				//Creates number value to go into Array
				//q - count = first number, q = last number
				string StoI = line.substr(q - count, q);
				//Converts string to int using function stoi()
				int bufferint = stoi(StoI);
				//Places bufferint into array "a" at position [r][k]
				a[r][k] = bufferint;
				//Checks size of array and prevents size from overflowing
				if (q < line.length()) { q = q + 1; }
			}

			//Enters names into String array
			string buffer = line.substr(0, j + 1);
			b[r] = buffer;
		}
		++r;
	} 

//*****************************************************************************************************************
// Allocating Grade Data

	//Dynamic Double Array for test averages
	//c[i] = i resembles the test number
	double* c = new double[tests];
	//Dynamic 2D Integer Array for test grade totals
	int** d = new int*[tests];
	for (int i = 0; i < tests; ++i)
	{
		d[i] = new int[5];
	}

// Allocating Average Data
	for (int i = 0; i < tests; i++)
	{
		double average = AverageCalc(students, a, i);
		c[i] = average;
	}

// Allocating Test Grade Totals Data
	GradeSort(a, c, d, students, tests);

//*****************************************************************************************************************
// Allocating BONUS Data

	//Dynamic Double Array for student averages
	//e[i] = i resembles the student "number"
	double* e = new double[students];
	//Shows class average for all tests
	double classAve = 0;

//Allocating Class Average Data
	classAve = ClassAveCalc(tests, c);

//Allocating Student Averages Data
	for (int i = 0; i < students; i++)
	{
		double average = StudentAve(tests, a, i);
		e[i] = average;
	}

//*****************************************************************************************************************
// Writing into File "outFile(argv[2])"
	cout << "Writing Files..." << endl;

	ofstream outFile(argv[2]); //Opening file to write averages and student scores
	if (!outFile)
	{
		cout << "Opening Writing File FAILED. Exiting..." << endl;
		return -1;
	}
	cout << "Opening Writing File Successful!" << endl;

// Writing Test Averages
	outFile << "Exam Averages:" << endl;
	for (int i = 0; i < tests; i++)
	{
		outFile << "Exam  " << i + 1 << " average =" << fixed << setprecision(1) << c[i] << setw(4);
		outFile << d[i][0] << "(A)" << setw(5);
		outFile << d[i][1] << "(B)" << setw(5);
		outFile << d[i][2] << "(C)" << setw(5);
		outFile << d[i][3] << "(D)" << setw(5);
		outFile << d[i][4] << "(E)" << endl;
	}
	outFile << endl;

// Writing Student Names & Grades (test grade, letter grade)
	outFile << "Student Exam Grades:" << endl;
	for (int r = 0; r < students; r++)
	{
		//Writes names into text file
		string buffer = b[r];
		outFile << right << setw(5) << buffer << right << setw(25 - buffer.size());
		//Writes test scores into text file
		for (int q = 0; q < tests; q++)
		{
			outFile << a[r][q];
			int grade = a[r][q];
			string letter = GradeCalc(c, q, grade);
			outFile << "(" << letter << ")" << right << setw(9);
		}
		outFile << endl;
	}
	outFile << endl;

// BONUS: Writing Class Average and Student Final Exam Grades
	outFile << "Class Average = " << fixed << setprecision(1) << classAve << endl;
	outFile << "Student Final Exam Grade:" << endl;
	for (int r = 0; r < students; r++)
	{
		//Writes names into text file
		string buffer = b[r];
		outFile << right << setw(5) << buffer << right << setw(25 - buffer.size());
		outFile << fixed << setprecision(1) << e[r];
		double grade = e[r];
		string letter = StudentGrade(grade, classAve);
		outFile << "(" << letter << ")" << endl;
	}

//*****************************************************************************************************************
// Closing All Files and Deleting All Arrays
	inFile.close();
	outFile.close();
	double CloseSuccess = DeleteArray(a, b, c, d, e, students, tests);
	cout << "Reading and Writing Grade Files Successful! Closing..." << endl;
	return 0;
}