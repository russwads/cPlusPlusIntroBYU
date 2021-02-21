#ifndef MYDEQUE_H
#define MYDEQUE_H

#include"DequeInterface.h"
#include<string>
#include<sstream>

using std::string;
using std::ostream;
using std::ostringstream;

template <typename T>
class MyDeque : public DequeInterface<T> //is-a relationships
{
private:
	size_t deque_capacity;
	size_t num_items;
	size_t front_index;
	size_t rear_index;
	T* the_data;
	void ave_reallocate(size_t new_size) 
	{ 
		T* new_data = new T[new_size];
		for (unsigned int i = 0; i < deque_capacity; i++)
		{
			new_data[i] = the_data[i];
		}
		deque_capacity = new_size;
		delete[] the_data;
		the_data = new_data;
	}
	void sta_reallocate(size_t new_size)
	{
		T* new_data = new T[new_size];
		for (unsigned int i = 4; i < deque_capacity; i++)
		{
			new_data[i] = the_data[i];
		}
		deque_capacity = new_size;
		delete[] the_data;
		the_data = new_data;
	}
public:
	MyDeque() : deque_capacity(DEFAULT_CAPACITY), num_items(0), front_index(DEFAULT_CAPACITY - 1), rear_index(0), the_data(new T[DEFAULT_CAPACITY]) {};
	MyDeque(int in_front, int in_back) : deque_capacity(DEFAULT_CAPACITY), num_items(0), front_index(in_front), rear_index(in_back), the_data(new T[DEFAULT_CAPACITY]) {};
	static const size_t DEFAULT_CAPACITY = 4;
	const bool isFull() 
	{ 
		if (deque_capacity == num_items) { return true; }
		else { return false; }
	}
	void push_front(const T& value) 
	{ 
		if (isFull() == true) { size_t new_size = deque_capacity * 2; sta_reallocate(new_size); } //reallocates data if the array is full already
		else {}; //Does nothing to continue with the function

		if (num_items >= 1) //If there is at least 1 item in the array
		{
			num_items++;
			front_index--;
			the_data[front_index] = value;
		}
		else if (num_items == 1)
		{
			num_items++;
			front_index = 2;
			the_data[front_index] = value;
		}
		else //If the array is empty
		{
			num_items = 1;
			the_data[front_index] = value;
		}
	}
	void push_back(const T& value) 
	{ 
		if (isFull() == true) { size_t new_size = deque_capacity * 2; ave_reallocate(new_size); } //reallocates data if the array is full already
		else {}; //Does nothing to continue with the function

		if (num_items > 1) //If there is at least 1 item in the array
		{
			num_items++;
			rear_index++;
			the_data[rear_index] = value;
		}
		else if (num_items == 1)
		{
			num_items++;
			if (front_index == 0) { rear_index = 1; }
			else { ; }
			the_data[rear_index] = value;
		}
		else //If the array is empty
		{
			num_items = 1;
			the_data[front_index] = value;
		}
	}
	void pop_front() 
	{ 
		if (empty() == false)
		{
			num_items--;
			the_data[front_index] = NULL;
			if (front_index != 3) { front_index++; }
			else { ; }
		}
		else { ; }

		if ((front_index == rear_index) && (front_index != 0) && (rear_index != 0)) //Queue reset
		{
			front_index = 0;
			rear_index = 0;
		}
		else { ; }
	}
	void pop_back() 
	{ 
		if (empty() == false)
		{
			num_items--;
			the_data[rear_index] = NULL;
			if (rear_index != 0) { rear_index--; }
			else { rear_index = 0; }
		}
		else {};

		if ((front_index == rear_index) && (front_index != 0) && (rear_index != 0)) //Queue reset
		{
			front_index = 0;
			rear_index = 0;
		}
		else { ; }
	}
	T& front() { return the_data[front_index];  }
	T& back() { return the_data[rear_index]; }
	size_t size() const 
	{ 
/*		size_t count = 0;
		int i = front_index;
		while (the_data[i] != NULL) 
		{ 
			if (i + 1 == deque_capacity) { i = 0; count++; }
			else { i++; count++; }
		}
		return count; */
		return num_items;
	}
	bool empty() const 
	{ 
		if (num_items == 0) { return true; }
		else { return false; }
	}
	T& at(size_t index) { return the_data[index]; }
	string toString() const
	{ 
		ostringstream ss;
		for (int i = front_index; i != rear_index + 1; i++)
		{
			if (i == deque_capacity) { i = -1; }
			else { ss << the_data[i] << " "; }
		}
		return ss.str();
	}

	~MyDeque() {};
};

#endif
