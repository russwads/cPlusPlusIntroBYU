#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include"LinkedListInterface.h"
#include<string>
#include<sstream>

using std::string;
using std::ostream;

template<typename T> class LinkedList : public LinkedListInterface<T>
{
private:
/**
	Linked List Node
*/
	struct Node
	{
		T data;
		Node *next;

		Node(T data_item) : next(NULL) { this->data = data_item; }
		Node(T data_item, Node* next_ptr) { this->data = data_item; this->next = next_ptr; }
	};
	Node* head;

public:
/**
Constructor of LinkedList
*/
	LinkedList() { this->head = NULL; }

/**
A function that returns true if the given value is located inside of the data
@param value: the value of T that must be matched to return the function as true
*/
	bool searchMatch(T value)
	{
		Node* ptr = head;
		while (ptr != NULL)
		{
			if (ptr->data == value) { return true; }
			ptr = ptr->next;
		}
		return false;
	}

/**
Inserts beginning node into Linked List
@param value: the value that is going into the linked list
*/
	bool insertHead(T value)
	{
		if (searchMatch(value)) return false;
		head = new Node(value, head);
		return true;
	}
	//check
/**
Inserts ending node into Linked List
@param value: the value that is going into the linked list
*/
	bool insertTail(T value)
	{
		if (searchMatch(value)) return false;
		if (this->head == NULL) //if there is no head, the new node will be created as the head of the list, despite it being the tail
		{
			head = new Node(value, head);
			return true;
		}
		else
		{
			Node* temp_ptr = head;
			while (temp_ptr->next != NULL)
			{
				temp_ptr = temp_ptr->next;
			}
			temp_ptr->next = new Node(value);
			return true;
		}
		return false;
	}
	//check
/**
Inserts node after selected node of data
@param matchNode: node that must be in the list before the new node enters into the list
@param node: new node entering into the list
*/
	bool insertAfter(T matchNode, T node)
	{
		if (searchMatch(node)) return false;
		Node* ptr = head;
		while (ptr != NULL)
		{
			if (ptr->data == matchNode) //checks to see if the matchNode is in the list
			{
				Node* new_node = new Node(node, ptr->next); //Creates new node
				ptr->next = new_node; //Sets new "next" pointer values
				return true;
			}
			ptr = ptr->next; //Increments until the end of the list so the "if" statement can check every node
		}
		return false;
	}
	//check
/**
Removes selected value from the linked list
@param value: the selected value to be removed from the list
*/
	bool remove(T value)
	{
		bool truth = searchMatch(value);
		unsigned int list_size = this->size();
		if (truth == true)
		{
			Node* ptr = head;
			unsigned int iter = 0;
			while (ptr != NULL)
			{
				if (ptr->data == value) 
				{ 
					Node* ptr2 = head;
					for (unsigned int i = 0; i < iter; i++)
					{
						ptr2 = ptr2->next;
					}
					ptr2->next = ptr2->next->next;
					delete ptr;
					return true;
				}
				ptr = ptr->next;
				iter++;
			}
		}
		else { return false; }
	}
	//check
/**
Clears linked list of all values
*/
	bool clear()
	{
		if (!head) { return false; } //returns false if there is no head or the head data is NULL
		if (!head->next) { delete head; return true; } //deletes just the head if there are no other nodes
		else
		{
			Node* ptr1 = head->next;
			for (int i = 0; i < this->size(); i++) //For the number of nodes, the pointer goes to the tail and deletes the nodes one by one
			{
				while (ptr1 != NULL)
				{
					ptr1 = ptr1->next;
				}
				delete ptr1;
				Node* ptr1 = head->next;
			}
			delete head;	 //Deleting all other nodes and pointers
			delete ptr1;
			return true;
		}
	}
	//check
/**
Returns node that resides at the desired index
@param index: the index number of the list
*/
	T at(int index)
	{
		try 
		{
			if (!head) { throw index; } //returns the fail data if there is no head or the head data is NULL
			if ((index < 0) || (index > this->size()))
			{
				throw index;
			}
			else if (index == 0) { return head->data; }
			else
			{
				Node* ptr = head;
				unsigned int iter = 1;
				while (ptr != NULL)
				{
					if (iter == index)
					{
						T value = ptr->data;
						return value;
					}
					ptr = ptr->next;
					iter++;
				}
			}
		}
		catch (int index)
		{
			cout << "";
		}
	}
	//check
/**
Returns size of the linked list
*/
	int size()
	{
		Node* ptr = head;
		unsigned int count = 0;
		while (ptr != NULL)
		{
			ptr = ptr->next;
			count++;
		}
		return count;
	}
	//check
/**
Returns a string of all values in the linked list
*/
	string toString() const;
	//check
/**
	Sends the toString function into the output stream
*/
	friend std::ostream& operator<< (ostream& os, const LinkedList<T>& LLfin)
	{
		os << LLfin.toString();
		return os;
	}// end operator<<
	//check
	~LinkedList() { clear(); }
};

#endif

template<typename T>
inline string LinkedList<T>::toString() const
{
	Node* temp_ptr = head;
	if (temp_ptr == NULL) { return "Empty"; }

	ostringstream ss;
	while (temp_ptr != NULL)
	{
		ss << temp_ptr->data;
		if (temp_ptr->next != NULL) { ss << " "; }
		temp_ptr = temp_ptr->next;
	}
	return ss.str();
}
