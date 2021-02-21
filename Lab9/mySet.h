#ifndef MYSET_H
#define MYSET_H

#include"SetInterface.h"
#include<string>
#include"BSTsetmap.h"

using std::string;

template<typename T>
class Set : public SetInterface<T>
{
private:
	BST<T> set_nodes;

	template<typename T1, typename T2>
	struct Pair
	{
		T1 first;
		T2 second;
		Pair() : first(), second() { ; }
		Pair(T1& a) : first(a), second() { ; }
		Pair(T1& a, T2& b) : first(a), second(b) { ; }
	};
public:
	Set() {}
	~Set() {}

	/** Inserts item into the set, if the container doesn't
	already contain an element with an equivalent value.
	@return: pair.first = pointer to item
	pair.second = true if successfully inserted, else false. 
	Pair<T*, bool> insertPair(const T& item)
	{
		string one, two;
		int i = 0;
		while (!isspace(item[i])) { i++; }
		int j = item.length() - 1;
		one = item.substr(0, i);
		i++;
		two = item.substr(i, j - i);
		bool truth = set_nodes.addNode(one, two);
		return item, truth;
	}
	*/
	bool insert(const T& item) 
	{ 
		string one, two;
		int i = 0;
		if (item == "") { return false; }
		while (!isspace(item[i])) 
		{
			i++;
			if (i == item.length() - 1) { break; }
		}
		int j = item.length();
		one = item.substr(0, i);
		i++;
		two = item.substr(i, j - i);
		return set_nodes.addNode(one, two); 
	}

	/** @return: the number of elements removed from the Set. */
	size_t erase(const T& item)
	{
		size_t i = 0;
		while (set_nodes.removeNode(item))
			i++;
		return i;
	}

	/** Removes all items from the set. */
	void clear()
	{
		set_nodes.clearTree();
	}

	/** @return: the number of elements contained by the Set. */
	size_t size() const
	{
		return set_nodes.getSize();
	}

	/** @return: return 1 if contains element equivalent to item, else 0. */
	size_t count(const T& item) const
	{
		bool truth = set_nodes.treeSearch(item);
		if (truth == true) { return 1; }
		else { return 0; }
	}

	/** @return: string representation of items in Set. */
	string toString() const
	{
		return set_nodes.toString();
	}
};
#endif