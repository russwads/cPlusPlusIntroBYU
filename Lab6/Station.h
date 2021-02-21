#ifndef STATION_H
#define STATION_H

#include<string>
#include<sstream>

using std::string;
using std::ostream;
using std::ostringstream;

template<typename T>
class Station
{
private:
	MyVector<unsigned int> train;
	MyStack<unsigned int> stacks;
	MyQueue<unsigned int> queues;
	T turntableCar;
	bool emptyStat;
	const string test = "test";
public:
	Station() : train(),stacks(),queues(),turntableCar(NULL),emptyStat(true) { ; }
	string addCar(T value) 
	{ 
		if (emptyStat == true)
		{
			turntableCar = value;
			emptyStat = false;
			return "OK";
		}
		else { return "Station full!"; }
	}
	string removeCar() 
	{ 
		if (emptyStat == false)
		{
			train.push_back(turntableCar);
			turntableCar = NULL;
			emptyStat = true;
			return "OK";
		}
		else { return "Station empty!"; }
	}
	string topCar() 
	{ 
		ostringstream ss;
		ss << turntableCar;
		return ss.str();
	}
	string addStack() 
	{ 
		if (emptyStat == false)
		{
			stacks.push(turntableCar);
			turntableCar = NULL;
			emptyStat = true;
			return "OK";
		}
		else { return "Station empty!"; }
	}
	string removeStack() 
	{ 
		if (stacks.size() == 0) { return "Stack empty!"; }
		else if (emptyStat == true)
		{
			turntableCar = stacks.top();
			stacks.pop();
			emptyStat = false;
			return "OK";
		}
		else { return "Station full!"; }
	}
	string topStack() 
	{ 
		ostringstream ss;
		ss << stacks.top();
		return ss.str();
	}
	string sizeStack() 
	{ 
		ostringstream ss; 
		ss << stacks.size(); 
		return ss.str();
	}
	string addQueue() 
	{
		if (emptyStat == false)
		{
			queues.push(turntableCar);
			turntableCar = NULL;
			emptyStat = true;
			return "OK";
		}
		else { return "Station empty!"; }
	}
	string removeQueue() 
	{
		if (queues.size() == 0) { return "Queue empty!"; }
		else if (emptyStat == true)
		{
			turntableCar = queues.top();
			queues.pop();
			emptyStat = false;
			return "OK";
		}
		else { return "Station full!"; }
	}
	string topQueue() 
	{ 
		ostringstream ss;
		ss << queues.top();
		return ss.str();
	}
	string sizeQueue() 
	{ 
		ostringstream ss;
		ss << queues.size();
		return ss.str();
	}
	string find(T value) 
	{ 
		unsigned int val = 0;
		while (val != value)
		{
			for (int i = 0; i < train.size(); i++)
			{
				val = train.at(i);
				if (val == value) { break; }
			}
			if (val == value) { break; }
			for (int j = 0; j < train.size(); j++)
			{
				val = stacks.at(j);
				if (val == value) { break; }
			}
			if (val == value) { break; }
			for (int k = 0; k < train.size(); k++)
			{
				val = queues.at(k);
				if (val == value) { break; }
			}
			if (val == value) { break; }
			val = turntableCar;
			if (val == value) { break; }
		}
	}
	string toString() const 
	{ 
		string finish = train.toString();
		return finish;
	}
	~Station() { ; }
};

#endif
