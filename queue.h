#ifndef QUEUE_H_
#define QUEUE_H_

#include"list.h"

// Queue ADT using linked list as primary data structure.
// 
template<typename Type>
class Queue {
public:

	Queue();

	// Basic queue operations
	void	push(Type item);
	void	pop();
	Type	peek() const;

	// Check to see if there is anything on the queue
	bool	empty() const;

	// Use to see what is in the queue for debugging
	void	print() const;
#ifndef MAKE_MEMBERS_PUBLIC
private:
#endif
	List<Type> m_list;
};


// Queue Implementation
//

// Queue() Default constrcutor:
//		Call the defualt constructor for its List.
//		Already implemented.
template<typename Type>
Queue<Type>::Queue() :m_list() {}

// push():
//		Add item to the queue in a manor appropriate for
//		Queue behavoir.
//
template<typename Type>
void Queue<Type>::push(Type item) {

	m_list.push_front(item);

}

// pop():
//		Remove the item on the "top" of the queue.
//
template<typename Type>
void Queue<Type>::pop() {

	/* TODO */
	m_list.pop_rear();

}

// isEmpty():
//		return true if there are no items in the queue
//		otherwise return false.
//
template<typename Type>
bool Queue<Type>::empty() const {

	if (m_list.empty())
	{
		return true;
	}

	return false;
}

// peek():
//		Look at the "front" of the queue without changing the
//		Queue itself.
//
template<typename Type>
Type Queue<Type>::peek() const {

	/* TODO */
	

	return m_list.rear();
}

// print()
//		Print to console the elements.
//		Used for debugging.
//
template<typename Type>
void Queue<Type>::print() const {

	/* TODO */
	m_list.print();

}













#endif // _
