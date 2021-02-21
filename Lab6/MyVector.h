#ifndef MYVECTOR_H
#define MYVECTOR_H

#include"MyDeque.h"
#include<string>
#include<sstream>

using std::string;
using std::ostream;
using std::ostringstream;

template<typename T>
class MyVector
{
private:
	MyDeque<T> container;
public:
	MyVector() : container(0,0) { ; }
	void push_back(const T& value) { container.push_back(value); }
	void pop_back() { container.pop_back(); }
	T& front() { return container.front(); }
	T& back() { return container.back(); }
	size_t size() { return container.size(); }
	T& at(size_t index) { return container.at(index); }
	string toString() const { return container.toString(); }
	~MyVector() { ; }
};

#endif
