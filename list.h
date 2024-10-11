#ifndef CS20A_LIST_H
#define CS20A_LIST_H

#include<iostream>
#include<assert.h>

// Linked List object that maintains both head and tail pointers
// and the num_nodes of the list.  Note that you have to keep the head,
// tail and num_nodes consistent with the intended state of the List 
// otherwise very bad things happen. 
template<typename Type>
class List {
public:

	List();

	List(const List<Type>& other);

	List<Type>& operator=(const List<Type>& other);

	~List();

	void	print() const;
	bool	empty() const;

	void	push_front(const Type& item);
	void	push_back(const Type& item);
	void	add_at(int index, const Type& item);

	// Note that the user must first ensure the list is not empty
	// prior to calling these functions.
	Type	front() const;
	Type	rear() const;
	Type	get_at(int index) const;

	int		size() const;
	int		find(const Type& item) const;

	bool	pop_front();
	bool	pop_rear();
	bool	pop_at(int index);

#ifndef MAKE_MEMBERS_PUBLIC
private:
#endif
	// Forward declare the nodes for our List.
	// Will be implemented along with list's
	// member functions
	class Node;

	// We'll have both head and tail points for 
	// Fast insertion/deletion from both ends.
	Node* head;
	Node* tail;

	// Keep track of num_nodes of list
	int	num_nodes;
};


/* List Implementation
//
//  Since List is a template class (which is not an actual
//  class yet, not until we actually instantiate the list)
//  we need to keep the implementation together with
//  the definition.  There are ways to simulate having
//  separate "implementation/definition" with templates,
//  but they aren't necessary and can be confusing.
*/

/* Node definition
//		Already implemented, nothing to do here but to use it.
*/
template<typename Type>
class List<Type>::Node {
public:
	Node() :next(nullptr), prev(nullptr) {}
	Node(Type item, Node* p, Node* n) : item(item), next(n), prev(p) {}

	Type  item;
	Node* next;
	Node* prev;
};



/* List default constructor
//		Set head and tail pointer to point to nothing, num_nodes is zero
//		Already implemented, nothing to do.
*/
template<typename Type>
List<Type>::List() :head(nullptr), tail(nullptr), num_nodes(0) {}


/* Copy constructor
//		This should create an entirely new linked list with the same
//		number of Nodes and the Values stored these Nodes in the same
//		order as seen the other list’s Nodes.  This should not result
//		in any memory leaks or aliasing.
*/
template<typename Type>
List<Type>::List(const List<Type>& other)
{
	head = nullptr;
	tail = nullptr;
	num_nodes = 0;

	for (Node* i = other.head; i != nullptr; i = i->next)
	{
		//this->push_back();
		if (head == nullptr)
		{
			head = tail = new Node(i->item, nullptr, nullptr);
		}
		else
		{
			tail = tail->next = new Node(i->item, tail, nullptr);
		}
		num_nodes++;
	}
}

/* Overloaded assignment operator
//		Causes the already existing linked list to be identical to the
//		other linked list without causing any memory leaks or aliasing.
*/
template<typename Type>
List<Type>& List<Type>::operator=(const List<Type>& other) {
	if (this == &other)
	{
		return *this;
	}

	//deleting this old memory
	while (head != nullptr)
	{
		Node* temp = head;
		head = head->next;
		delete temp;
	}
	num_nodes = 0;

	for (Node* i = other.head; i != nullptr; i = i->next)
	{
		if (head == nullptr)
		{
			head = tail = new Node(i->item, nullptr, nullptr);
		}
		else
		{
			tail = tail->next = new Node(i->item, tail, nullptr);
		}
		num_nodes++;
	}

	return *this;
}


/* List destructor
//		Traverses the nodes and deletes them without causing memory leaks
*/
template<typename Type>
List<Type>::~List()
{
	Node* temp = head;

	while (temp != nullptr)
	{
		Node* obj = temp->next;
		delete temp;
		temp = obj;
		num_nodes--;
	}
}

/* List print
//		Traverses list and prints items in list to console
//		Assumes << is overloaded for object Type.
*/

template<typename Type>
void List<Type>::print() const {
	//Professor, I did not understand how exactly you want us to print
	//because when I runned test_print(1), I did not understand what gaps you were stating
	//so I decided to print how I think it should be:D
	Node* p;
	p = head;
	while (p != nullptr)
	{
		std::cout << p->item;

		if (p->next != nullptr)
		{
			std::cout << ' ';
		}

		p = p->next;
	}
	std::cout << std::endl;
}

/* List empty
//		returns true if there are no items in the list
//		otherwise returns false.
*/
template<typename Type>
bool List<Type>::empty() const {
	return 0 == num_nodes;
}


/* List push_front
//		Adds a new item to the front of the list
//		updates head, tail, and num_nodes accordingly.
//
//		Two cases to consider: If the list is empty
//		and if the list has items already it.
*/
template<typename Type>
void List<Type>::push_front(const Type& item) {
	if (this->empty())
	{
		head = tail = new Node(item, nullptr, nullptr);
	}
	else
	{
		head = head->prev = new Node(item, nullptr, head);
	}
	num_nodes++;
}

/* List push_back
//		Adds a new item to the rear of the list
//		updates head, tail, and num_nodes accordingly.
//
//		Two cases to consider: If the list is empty
//		and if the list has items already it.
*/
template<typename Type>
void List<Type>::push_back(const Type& item)
{
	if (this->empty())
	{
		this->push_front(item);
	}
	else
	{
		tail = tail->next = new Node(item, tail, nullptr);
		num_nodes++;//
	}
}

/* List add_at
//		Adds a new item at the index indicated
//		updates head, tail, and num_nodes accordingly.
//
//		If the index less than or equal to zero add to the front.
//		If the index is greater than or equal to
//			the num_nodes of the list, add to the rear.
//		All other cases, add the item to the appropriate
//			location
*/
template<typename Type>
void List<Type>::add_at(int index, const Type& item) {
	if (index <= 0)
	{
		this->push_front(item);
	}
	else if (index >= num_nodes)
	{
		this->push_back(item);
	}
	else
	{
		Node* temp = head;
		while (index > 0)
		{
			temp = temp->next;
			index--;
		}

		Node* addat = new Node(item, temp->prev, temp);
		addat->prev->next = addat;
		addat->next->prev = addat;
		num_nodes++;
	}
}

/*  List front
//		returns the first item in the list.
*/
template<typename Type>
Type List<Type>::front() const {
	// Force check that the head is pointing to a Node
	// Typical solution for deployement code is to throw
	// exceptions, but since we haven't covered that yet
	// we'll make due with assert, which is used for testing
	assert(head != nullptr);

	return this->head->item;
}

/* List rear
//		returns the last item in the list
*/
template<typename Type>
Type List<Type>::rear() const {

	// Force check that the tail is pointing to a Node
	// Typical solution for deployement code is to throw
	// exceptions, since we haven't covered that yet
	// we'll make due with assert, which is used for testing
	assert(tail != nullptr);


	return this->tail->item;

}

/* List get_at
//		returns the item at index
*/
template<typename Type>
Type List<Type>::get_at(int index) const {

	// Force index to be correct before getting the Item
	// Typical solution for deployement code is to throw
	// exceptions, since we haven't covered that yet
	// we'll make due with assert, which is used for testing
	assert(index >= 0 && index < num_nodes);

	Node* temp = head;
	while (index > 0)
	{
		temp = temp->next;
		index--;
	}
	return temp->item;
}

/* List size
//		return the num_nodes of the list
*/
template<typename Type>
int List<Type>::size() const {
	return this->num_nodes;
}

/* List find
//		Traverses the list to see if the item is in the list
//		if it is return the index of that item, otherwise
//		return -1. Assumes the == operator is overloaded for
//		object Type.
*/
template<typename Type>
int List<Type>::find(const Type& item) const {
	int index = 0;
	for (Node* i = head; i != nullptr && i->item != item; i = i->next)
	{
		index++;
	}

	return index < num_nodes ? index : -1;

}

/* List pop_front
//		Removes the first item in the list returns true
//		if the item was deleted, false otherwise. Updates
//		head, tail, and num_nodes accordingly.
//
//		Must consider at least two cases where the list: is empty,
//		has one or more items.
*/
template<typename Type>
bool List<Type>::pop_front()
{
	if (head == nullptr) //num_nodes = 0 || tail = nullptr;
	{
		return false;
	}
	else if (num_nodes == 1)
	{
		Node* temp = head = tail;
		tail = head = nullptr;
		delete temp;
		num_nodes--;
		return true;
	}
	else
	{
		Node* popfront = head;
		head = popfront->next;
		delete popfront;
		num_nodes--;
		head->prev = nullptr;
		return true;
	}

}
/* List pop_rear
//		Removes the last item in the list returns true
//		if the item was deleted, false otherwise. Updates
//		head, tail, and num_nodes accordingly.
//
//		Must consider at least three cases where the list: is empty,
//		has one item, has two or more items.
*/
template<typename Type>
bool List<Type>::pop_rear() {
	if (tail == nullptr)
	{
		return false;
	}
	else if (num_nodes == 1) //case when 1 Node
	{
		Node* temp = tail = head;
		head = tail = nullptr;
		delete temp;
		num_nodes--;
		return true;
	}
	else
	{
		Node* rear = tail;
		tail = rear->prev;
		delete rear;
		num_nodes--;
		tail->next = nullptr;
		return true;
	}
}

/* List pop_at
//		Removes the item at the index returns true
//		if the item was deleted, false otherwise. Updates
//		head, tail, and num_nodes accordingly. If the index is
//		out of bounds return false.
*/
template<typename Type>
bool List<Type>::pop_at(int index)
{
	if (index >= num_nodes || index < 0)
	{
		return false;
	}

	Node* temp = head;

	if (index == 0)
	{
		this->pop_front(); // or this->pop_back();
		return true;
	}
	else
	{
		while (index > 0)
		{
			temp = temp->next;
			index--;
		}

		if (tail == temp)
		{
			this->pop_rear();
		}
		else
		{

			if (temp->prev == nullptr)
			{
				head = temp->next;
			}
			else
			{
				temp->prev->next = temp->next;
			}

			//tail->prev = nullptr
			if (temp->next == nullptr)
			{
				tail = temp->prev;
			}
			else
			{
				temp->next->prev = temp->prev;
			}

			delete temp;
			num_nodes--;
		}

		return true;

	}

}

#endif


