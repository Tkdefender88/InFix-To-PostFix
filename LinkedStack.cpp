/**
 * F18 CSCI232 Data Structures and Algorithms
 * 
 * Stack ADT using linked list
 * 
 * Phillip J. Curtiss, Assistant Professor
 * pcurtiss@mtech.edu, 406-496-4807
 * Department of Computer Science, Montana Tech
 */

#ifndef LINKED_STACK_IMP
#define LINKED_STACK_IMP

#include <cassert>		 // For assert
#include "LinkedStack.h" // Stack class specification file

template <class ItemType>
LinkedStack<ItemType>::LinkedStack() : topPtr(nullptr)
{
} // end default constructor

template <class ItemType>
LinkedStack<ItemType>::LinkedStack(const LinkedStack<ItemType> &aStack)
{
	// Point to nodes in original chain
	Node<ItemType> *origChainPtr = aStack.topPtr;

	if (origChainPtr == nullptr)
	{
		topPtr = nullptr; // Original stack is empty
	}
	else
	{
		// Copy first node
		topPtr = new Node<ItemType>();
		topPtr->setItem(origChainPtr->getItem());

		// Point to last node in new chain
		Node<ItemType> *newChainPtr = topPtr;

		// Advance original-chain pointer
		origChainPtr = origChainPtr->getNext();

		// Copy remaining nodes
		for (; origChainPtr != nullptr;)
		{
			// Get next item from original chain
			ItemType nextItem = origChainPtr->getItem();

			// Create a new node containing the next item
			Node<ItemType> *newNodePtr = new Node<ItemType>(nextItem);

			// Link new node to end of new chain
			newChainPtr->setNext(newNodePtr);

			// Advance pointer to new last node
			newChainPtr = newChainPtr->getNext();

			// Advance original-chain pointer
			origChainPtr = origChainPtr->getNext();
		} // end while

		newChainPtr->setNext(nullptr); // Flag end of chain
	}								   // end if
} // end copy constructor

template <class ItemType>
LinkedStack<ItemType>::~LinkedStack()
{
	// Pop until stack is empty
	for (; !isEmpty();)
	{
		pop();
	}
} // end destructor

template <class ItemType>
bool LinkedStack<ItemType>::isEmpty() const
{
	return topPtr == nullptr;
} // end isEmpty

template <class ItemType>
bool LinkedStack<ItemType>::push(const ItemType &newEntry)
{
	Node<ItemType> *newNodePtr = new Node<ItemType>(newEntry, topPtr);
	topPtr = newNodePtr;
	newNodePtr = nullptr;

	return true;
} // end push

template <class ItemType>
bool LinkedStack<ItemType>::pop()
{
	bool result = false;
	if (!isEmpty())
	{
		// Stack is not empty; delete top
		Node<ItemType> *nodeToDeletePtr = topPtr;
		topPtr = topPtr->getNext();

		// Return deleted node to system
		nodeToDeletePtr->setNext(nullptr);
		delete nodeToDeletePtr;
		nodeToDeletePtr = nullptr;

		result = true;
	} // end if

	return result;
} // end pop

template <class ItemType>
ItemType LinkedStack<ItemType>::peek() const 
{
	// Enforce precondition
	if (isEmpty())
	{
		throw std::logic_error("peek() called with empty stack.");
	}

	// Stack is not empty; return top
	return topPtr->getItem();
} // end peek

#endif