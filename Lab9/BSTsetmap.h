#ifndef BST_H
#define BST_H

#include<string>
#include<sstream>

using std::string;
using std::ostringstream;

template<typename T>
class BST
{
private:
	struct Node
	{
	public:
		T data;
		T data2;
		Node* lft;
		Node(const T& item, const T& item2) : data(item), data2(item2), lft(nullptr) { ; }
		Node(const T& item, const T& item2, Node* left) : data(item), data2(item2), lft(left) { ; }
	};
	Node* head = nullptr;
	size_t bstsize = 0;

	/** Recursive function buffer for addNode */
	bool insertBuff(Node*& node, const T& value1, const T& value2)
	{
		if (node == NULL) { node = new Node(value1,value2); return true; } //Adds new node to BST 
		else if ((node->data == value1) && (node->data2 == value2)) { return false; } //Fail-safe if search() fails to execute correctly
		else if (value2 != node->data2) { return insertBuff(node->lft, value1, value2); } //Recursive function begins to the left when value is less than node value
		else { return false; }//Syntax Error; removing complier warnings
	}
	/** Recursive function buffer for removeNode */
	bool deleteBuff(Node*& node, const T& value)
	{
		if (node == NULL) { return false; }
		else if (value != node->data) { return deleteBuff(node->lft, value); }
		else
		{
			node = node->lft;
			return true;
		}
	}
	/** Recursive function counterpart for clearTree */
	bool clear(Node*& node)
	{
		if (node->lft != NULL) { clear(node->lft); }
		else
		{
			delete node;
			node = NULL;
			return true;
		}
	}

public:
	BST() { ; }

	/** Returns the search function, with access to the head tempnode */
	bool treeSearch(T value) const
	{ 
		return search(head, value); 
	}
	/** Returns true if the value is located in the BST, else false */
	bool search(Node* tempnode, T value) const
	{
		if (tempnode == NULL) { return false; } //If the node is empty, return false
		else if (tempnode->data == value) { return true; } //If the data for the node is equal to the value given, return true
		else if (value != tempnode->data) { return search(tempnode->lft, value); } //Travels to the left if the value is less than the node, and begins recursion
		else { return false; }
	}

	/** Return true if node added to BST, else false */
	bool addNode(const T& value1, const T& value2)
	{
		bool truth = search(head, value1);
		if (truth == true) { return false; }
		else { bstsize++; return insertBuff(head, value1, value2); }
	}
	/** Return true if node removed from BST, else false */
	bool removeNode(const T& value)
	{
		bool truth = search(head, value);
		if (truth == false) { return false; }
		else { bstsize--; return deleteBuff(head, value); }
	}

	/** Return true if BST cleared of all nodes, else false */
	bool clearTree()
	{
		if (head == NULL) { return true; }
		else { bstsize = 0; return clear(head); }
	}
	/** Output nodes at a given level */
	bool outLevel(Node* root, int level, ostringstream& out) const
	{
		if (root == NULL) return false;
		if (level == 0)
		{
			out << root->data << ": " << root->data2 << endl;
			if (root->lft != NULL) return true;
			return false;
		}
		bool left = outLevel(root->lft, level - 1, out);
		return left;
	}
	/** Returns the size of the BST */
	size_t getSize() const { return bstsize; }
	/** Return a level order traversal of a BST as a string */
	string toString() const
	{
		ostringstream ss;
		if (head == NULL) 
			ss << " Empty";
		else
		{
			int level = -1;
			do
			{
				++level;
			} while (outLevel(head, level, ss));
		}
		return ss.str();
	}


/**	class Iterator
	{
	private:
		BST<T> hello;
		Node* root;
		size_t treesize;

	public:
		Iterator() { ; }
		Iterator(Node* groot) : root(groot) { ; }
		Iterator(BST<T> hi, Node* groot) : hello(hi), root(groot) { ; }
		Iterator(const Iterator& other) : hello(other.hello), root(other.root) { ; }
		Iterator(Iterator&& other) : hello(other.hello), root(other.root) { other.hello = nullptr; other.root = nullptr; }

		/** Return true if iterators are not equal, else false *
		bool operator!=(const Iterator& rhs) const
		{
			return !(root == *rhs);
		}

		/** Return true if iterators are equal, else false *
		bool operator==(const Iterator& rhs) const
		{
			return (root == *rhs);
		}

/**		/** Post increment iterator operator *
		Iterator operator++()
		{
			treesize++;
		}
*
		/** Dereference iterator operator *
/**		T operator*() const
		{
			return ;
		}
*		~Iterator() {;}
	}; 
	Iterator begin() 
	{ 
		Node* begin_iter = head;
		Iterator iter = new Iterator(begin_iter);
		return iter;
	}
	Iterator end() 
	{ 
		Node* begin_iter = head;
		do {
			begin_iter = begin_iter->lft;
		} while (begin_iter->lft != NULL);
		Iterator buff_finish = new Iterator(begin_iter->lft);
		Iterator iter = buff_finish;
		delete buff_finish;
		return iter;
	}
/**	Iterator find(T& value) 
	{ 
		
	}*/
	~BST() { while (head != NULL) { clearTree(); } }
};

#endif

/*		if ((level == 1) && !root->lft) out << " _";
bool left = outLevel(root->lft, level - 1, out);
//		bool right = outLevel(level - 1, out);
//		if ((level == 1) && root->lft) out << " _";
return left; */