#ifndef QS_H
#define QS_H
#include<string>
#include<sstream>
#include"QSInterface.h"
using std::string;
using std::ostringstream;

template<typename T>
class QS : public QSInterface<T>
{
private:
	size_t array_capacity;
	size_t array_elements;
	size_t comparisons;
	size_t exchanges;
	T * quicksort;

public:
	QS() : array_capacity(0), array_elements(0) {}
	~QS() 
	{
		clear();
		free(quicksort);
	}

	/** Dynamically allocate an initial array to the QuickSort class. */
	bool createArray(size_t capacity)
	{
		if (array_capacity > 0) { free(quicksort); }
		array_capacity = capacity;
		array_elements = 0;
		quicksort = (T*)malloc(sizeof(T) * capacity);
		return true;
	}

	/** Add an element to the QuickSort array. Dynamically grow array as needed. */
	bool addElement(T element)
	{
		if (array_elements == array_capacity) 
		{ 
			array_capacity = array_capacity * 2;
			quicksort = (T*)realloc(quicksort, sizeof(T) * array_capacity);
		}
		quicksort[array_elements] = element;
		array_elements++;
		return true;
	}

	/** Sort the elements of a QuickSort subarray using median and partition functions. */
	bool sort(size_t left, size_t right)
	{
		int middle = medianOfThree(left, right);
		int pivot = partition(left, right, middle);
		return true;
	}

	/** Sort all elements of the QuickSort array using median and partition functions. */
	bool sortAll()
	{
		int middle = medianOfThree(0, array_elements);
		int pivot = partition(0, array_elements, middle);
		sort(0, pivot);
		sort(pivot, array_elements);
		return true;
	}

	/** Removes all items from the QuickSort array. */
	bool clear()
	{
//		free(quicksort);
		array_elements = 0;
		return true;
	}

	/** Return size of the QuickSort array. */
	size_t capacity() const { return array_capacity; }

	/** Return number of elements in the QuickSort array. */
	size_t size() const { return array_elements; }

	/** The median of three pivot selection has two parts:
	1) Calculates the middle index by averaging the given left and right indices:
	middle = (left + right)/2
	2) Then bubble-sorts the values at the left, middle, and right indices.

	After this method is called, data[left] <= data[middle] <= data[right].

	@param left - the left boundary for the subarray from which to find a pivot
	@param right - the right + 1 boundary for the subarray from which to find a pivot
	@return the index of the pivot (middle index).
	Return -1 if	1) the array is empty,
	2) if either of the given integers is out of bounds,
	3) or if the left index is not less than the right index.
	*/
	int medianOfThree(size_t left, size_t right)
	{
		if ((left < 0) || (left >= array_elements)) { return -1; }
		if ((right <= left) || (right > array_elements)) { return -1; }
		int middle = (left + right) / 2;
		if (quicksort[left] > quicksort[middle])
		{
			swap(quicksort[left], quicksort[middle]);
			exchanges++;
		}
		if (quicksort[left] > quicksort[right - 1])
		{
			swap(quicksort[left], quicksort[right - 1]);
			exchanges++;
		}
		if (quicksort[middle] > quicksort[right - 1])
		{
			swap(quicksort[middle], quicksort[right - 1]);
			exchanges++;
		}
		comparisons = comparisons + 3;
		return middle;
	}

	/** Partitions a subarray around a pivot value selected according
	to median-of-three pivot selection. Because there are multiple ways
	to partition a list, follow the algorithm on page 611.

	The values which are smaller than the pivot should be placed to the left of the pivot;
	the values which are larger than the pivot should be placed to the right of the pivot.

	@param left - left index for the subarray to partition.
	@param right - right index + 1 for the subarray to partition.
	@param pivotIndex - index of the pivot in the subarray.
	@return the pivot's ending index after the partition completes:
	Return -1 if	1) the array is empty,
	2) if any of the given indexes are out of bounds,
	3) if the left index is not less than the right index.
	*/
	int partition(size_t left, size_t right, size_t pivotIndex)
	{
		if ((left < 0) || (left >= array_elements)) { return -1; }
		if ((right <= left) || (right > array_elements)) { return -1; }
		if ((pivotIndex < left) || (pivotIndex > right)) { return -1; }
		swap(quicksort[left], quicksort[pivotIndex]);
		int i = left + 1;
		int j = right - 1;

		do
		{
			while ((quicksort[i] <= quicksort[left])) 
			{ 
				comparisons++;
				if (quicksort[i] > quicksort[left]) { break; } 
				else { i++; } 
			}
			if (i != j)
			{
				while ((quicksort[left] > quicksort[j])) 
				{ 
					comparisons++;
					if (quicksort[j] < quicksort[left]) { break; }
					else { j--; }
				}
			}
			if ((quicksort[i] < quicksort[j]) || (quicksort[i] > quicksort[j])) { swap(quicksort[i], quicksort[j]); exchanges++; j--; }
		} while (i < j);
		swap(quicksort[left], quicksort[j]);
		return j;
	}

	/** @return: comma delimited string representation of the array. */
	string toString() const
	{
		ostringstream ss;
		for (unsigned int i = 0; i < array_elements; i++)
		{
			if ((i > 0) && (i < array_elements)) { ss << ","; }
			ss << quicksort[i];
		}
		return ss.str();
	}

	/** Friend insertion operator for toString function */
	friend ostream& operator<< (ostream& os, const QS<T>& myArray)
	{
		os << myArray.toString();
		return os;
	}
};

#endif /* QSINTERFACE_H_ */
