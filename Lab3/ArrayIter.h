#ifndef ARRAYITER_H
#define ARRAYITER_H
enum myMode {SEQUENTIAL, PRIME, COMPOSITE, FIB};
#define MAX_ARRAY 1000

template<typename T>
class ArrayIter
{
private:
	T* array;
	int arraySize = 0;

public:
	ArrayIter(const int array_size) { array = (T*)malloc(sizeof(T)*array_size); }
	~ArrayIter() { free(array); }
	void push_back(T the_value) 
	{ 
		if (arraySize < 0) {};
		if (arraySize >= 1000) {};
		array[arraySize] = the_value;
		arraySize++;
	}

	class Iter
	{
		friend class ArrayIter<T>;

	private:
		T * array;
		int index;
		int mode;
		int arraySize;
/*		bool isValid() 
		{ 
			switch (myMode)
			{
			case SEQUENTIAL: return true;
			case PRIME: return isPrime(array[index]);
			case COMPOSITE: return !isPrime(array[index]);
			case FIB: return isFib(array[index]);
			default: return false;
			}
		}
*/		

	public:
		Iter(T* array) {};
		Iter(T* array, int arraySize) {};
		Iter(T* array, int arraySize, int index) {};
		Iter(T* array, int arraySize, int index, int mode) {};

		bool operator!=(const Iter& current) const 
		{ 
			if (index != current.index)
				return false;
			else
				return true;
		}
		T& operator[](int in_index) const { return array[in_index]; }
		T& operator*()	{ return array[index]; }
		Iter& operator++() 
		{ 
//			do
//			{
				index++;
//				if (index >= arraySize) break;
//			} 
//			while (!isValid());
			return *this;
		}

		std::string toString() const
		{
			std::stringstream ss;
			ss << "size=" << arraySize << " index=" << index << " mode=" << mode << endl;
			return ss.str();
		}
/*		std::string fibString() const
		{
			std::stringstream ss;
			T num1 = array[index - 1];
			T num2 = array[index - 2];
			ss << "=" << num2 << "+" << num1;
			return ss.str();
		}
*/		
		friend std::ostream& operator<< (std::ostream& os, const Iter& iter)
		{
			os << iter.toString();
			return os;
		}

	};

	Iter begin() { return Iter(array, arraySize, 0); }
	Iter begin(myMode mode) { return Iter(array, arraySize, 0, mode); }
	Iter end() { return Iter(array, arraySize, arraySize); }
	bool isPrime(int number) 
	{ 
		int i;
		if (number < 2) return false;
		for (i = 2; i < number; i++)
		{
			if (number % i == 0) return false;
		}
		return true;
	}
	bool isFib(int number1, int number2, int number3) 
	{ 
		int fibtest = number2 + number3;
		if (fibtest == number1)
		{
			return true;
		}
		else { return false; }
	}
	std::string toString() const 
	{ 
		
	}
	friend std::ostream& operator<< (std::ostream& os, const ArrayIter<T>& myArray)
	{
		os << myArray.toString();
		return os;
	}
};



#endif