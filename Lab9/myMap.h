#ifndef MYMAP_H
#define MYMAP_H

#include"MapInterface.h"
#include<string>

using std::string;

template<typename K, typename V>
class Map : public MapInterface<K,V>
{
private:
	
public:
	static const int HashTableSize = 31;
	static const int BonusHashTableSize = 7;

	Map() 
	{
		
	}
	~Map() {}

	/** Read/write index access operator.
	If the key is not found, an entry is made for it.
	@return: Read and write access to the value mapped to the provided key. */
	V& operator[](const K& key)
	{

	}

	/** @return: the number of elements removed from the Map. */
	size_t erase(const K& key)
	{

	}

	/** Removes all items from the Map. */
	void clear()
	{

	}

	/** @return: number of Key-Value pairs stored in the Map. */
	size_t size() const
	{

	}

	/** @return: maximum number of Key-Value pairs that the Map can hold. */
	size_t max_size() const
	{

	}

	/** @return: string representation of Key-Value pairs in Map. */
	string toString() const
	{

	}
};

#endif