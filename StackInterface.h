/**
 * F18 CSCI232 Data Structures and Algorithms
 * 
 * Stack ADT Interface
 * 
 * Phillip J. Curtiss, Assistant Professor
 * pcurtiss@mtech.edu, 406-496-4807
 * Department of Computer Science, Montana Tech
 */

#ifndef STACK_INTERFACE_H
#define STACK_INTERFACE_H

template <class ItemType>
class StackInterface
{
  public:
	/** Sees whether this stack is empty.
    @return True if the stack is empty, or false if not. */
	virtual bool isEmpty() const = 0;

	/** Adds a new entry to the top of this stack.
    @post If the operation was successful, newEntry is at the top of the stack.
    @param newEntry The object to be added as a new entry.
    @return True if the addition is successful or false if not. */
	virtual bool push(const ItemType &newEntry) = 0;

	/** Removes the top of this stack.
    @post If the operation was successful, the top of the stack
    has been removed.
    @return True if the removal is successful or false if not. */
	virtual bool pop() = 0;

	/** Returns the top of this stack.
    @pre The stack is not empty.
    @post The top of the stack has been returned, and
    the stack is unchanged.
    @return The top of the stack. */
	virtual ItemType peek() const = 0;

	/** Destroys object and frees memory allocated by object. */
	virtual ~StackInterface() {}
}; // end StackInterface
#endif