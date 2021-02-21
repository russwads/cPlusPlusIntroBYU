/**
LAB 6 -- Railroad
by Rusty Steel Wool

"Create a railroad train station that warehouses train cars
as well as changes the order of cars entering and leaving the
station. Cars enter the train station only if the turntable 
is empty. From the turntable cars can be moved to a "stack" 
storage facility (LIFO), a "queue" storage facility (FIFO), or
a "deque" storage facility (double ended queue). Train cars 
depart from the turntable of the train station to a vector of cars."

*/

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK;
#endif

#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<cctype>
#include"MyDeque.h"
#include"MyQueue.h"
#include"MyStack.h"
#include"MyVector.h"
#include"Station.h"

using namespace std;

int main(int argc, char* argv[])
{
	if (argc < 3)
	{
		cout << "Insufficient number of arguments. Closing..." << endl;
		return -1;
	}
	ifstream in(argv[1]);
	if (!in)
	{
		cout << "Opening input file failed. Closing..." << endl;
		return -1;
	}
	ofstream out(argv[2]);
	if (!out)
	{
		cout << "Opening output file failed. Closing..." << endl;
		return -1;
	}
	cout << "Opening files successful!" << endl;

//**************************************************************************************
// Reading and Writing File Data
	Station<unsigned int> trntbl;
	
	string action, location, line; //Input devices to find correct cooresponding function
	string strtrain_num; //Buffer for input train number
	unsigned int train_num = 0; //The input train number which will go into the station, stack, queue, or train vector

	while (getline(in, line))
	{
		out << line << " "; //Outputs the entire line as given
		int lengthln = line.length(); //Aids in finding train number values
		int i = 0; //Aids in finding the length of a given word
		int j = 0; //Aids in finding the beginning of the location value
		if (lengthln != 0) { while (!ispunct(line[i])) { i++; } }//Parses through to find the end of the first value
		action = line.substr(0, i); //Creates a substring cooresponding to the action/function needed to be done

		if (action == "Add")
		{
			//Parsing through to find the location where upon we will add the new train
			j = i + 1;
			location = line.substr(j, 4);
			if (location == "stat") { location = "station"; }
			else if (location == "stac") { location = "stack"; }
			else if (location == "queu") { location = "queue"; }
			string result; //Output source of the function's result

			if (location == "station")//Adds car to the station
			{
				//Finding the name of the train (number)
				strtrain_num = line.substr(lengthln - 1, 1);
				train_num = stoi(strtrain_num);
				result = trntbl.addCar(train_num);
				out << result;
			}
			else if (location == "stack")//Adds car to the stack and removes from the station
			{
				result = trntbl.addStack();
				out << result;
			}
			else if (location == "queue")//Adds car to the queue and removes from the station
			{
				result = trntbl.addQueue();
				out << result;
			}
			else //Coding Syntax Error Catch
			{
				cout << "Error";
			}
		}
		else if (action == "Remove")
		{
			//Parsing and finding location of removal
			int length = line.length();
			j = i + 1;
			location = line.substr(j, length - 7);
			string result;

			if (location == "station") //Remove the car from the station
			{
				result = trntbl.removeCar();
				out << result;
			}
			else if (location == "stack")//Remove the car from the stack and add to the station
			{
				result = trntbl.removeStack();
				out << result;
			}
			else if (location == "queue")//Remove the car from the queue and add to the station
			{
				result = trntbl.removeQueue();
				out << result;
			}
			else //Coding Syntax Error Catch
			{
				cout << "Error";
			}
		}
		else if (action == "Top")
		{
			//Parsing and finding either top of station, stack, or queue
			int length = line.length();
			j = i + 1;
			location = line.substr(j, length - 4);
			string result;

			if (location == "station") //Returns the car in the station
			{
				result = trntbl.topCar();
				out << result;
			}
			else if (location == "stack")//Returns the car at the top of the stack (LIFO)
			{
				result = trntbl.topStack();
				out << result;
			}
			else if (location == "queue")//Returns the car at the top of the cue (FIFO)
			{
				result = trntbl.topQueue();
				out << result;
			}
			else //Coding Syntax Error Catch
			{
				cout << "Error";
			}
		}
		else if (action == "Size")
		{
			//Parsing and finding either top of station, stack, or queue
			int length = line.length();
			j = i + 1;
			location = line.substr(j, length - 4);
			string result;

			if (location == "stack")//Returns the car at the top of the stack (LIFO)
			{
				result = trntbl.sizeStack();
				out << result;
			}
			else if (location == "queue")//Returns the car at the top of the cue (FIFO)
			{
				result = trntbl.sizeQueue();
				out << result;
			}
			else //Coding Syntax Error Catch
			{
				cout << "Error";
			}
		}
		else if (action == "Find")
		{
			strtrain_num = line.substr(lengthln - 1, 1); //Finding the name of the train
			train_num = stoi(strtrain_num);


		} 
		else if (action == "Train") //Outputs train vector files using toString
		{
			out << trntbl.toString();
		}
		else 
		{
			out << "OOPS" << endl;
		}
		out << endl;
	}

	in.close();
	out.close();
	return 0;
}