#ifndef MYQUEUE_H
#define MYQUEUE_H

#include"MyDeque.h"
#include<string>
#include<sstream>

using std::string;
using std::ostream;
using std::ostringstream;

template<typename T>
class MyQueue
{
private:
	MyDeque<T> container;
public:
	MyQueue() : container(0, 0) { ; }
	void push(T value) { container.push_back(value); }
	void pop() { container.pop_front(); }
	T& top() { return container.front(); }
	size_t size() { return container.size(); }
	T& at(size_t index) { return container.at(index); }
	string toString() const { return container.toString(); }
	~MyQueue() { ; }
};

#endif
