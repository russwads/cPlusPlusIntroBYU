#ifndef MYSTACK_H
#define MYSTACK_H

#include"MyDeque.h"
#include<string>
#include<sstream>

using std::string;
using std::ostream;
using std::ostringstream;

template<typename T>
class MyStack
{
private:
	MyDeque<T> container;
public:
	MyStack() :container(4 - 1, 4 - 1) { ; }
	void push(T value) { container.push_front(value); }
	void pop() { container.pop_front(); }
	T& top() { return container.front(); }
	size_t size() { return container.size(); }
	T& at(size_t index) { return container.at(index); }
	string toString() const { return container.toString(); }
	~MyStack() { ; }
};

#endif

