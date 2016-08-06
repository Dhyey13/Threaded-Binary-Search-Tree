/**
 @file Node.cpp
 Node source file, contains functions that implements Nodes in the threaded
 binary search tree (tbst). Contains a constructor, copy construc, destructor.
 Each node will contain the data object, pointer to left and right, boolean to 
 indicate whether it is a thread. Contains set and get functions for the objects
 in the Node.
 
 @author Sean Lai
 @author Sai Badey
 @section ASSIGNEMT Lab5
 @section DUE_DATE
 */


#include "Node.h"

/**
  * Default constructor for Node
  * Sets the item to NULL, leftChildPtr and rightChildPtr to NULL
  */
Node::Node()
{
    setItem(NULL);
    
    setLeftChildPtr(NULL);
    setRightChildPtr(NULL);
    
    setisLeftThread(false);
    setisRightThread(false);
}

/**
  * Copy constructor
  * Copies the other node to current
  *param other - other Node
  */
Node::Node(Node &other)
{
    this->setLeftChildPtr(other.getLeftChildPtr());
    this->setRightChildPtr(other.getRightChildPtr());
    
    this->setisLeftThread(other.getisLeftThread());
    this->setisRightThread(other.getisRightThread());
    
    this->setItem(other.getItem());
    //Copy the value of other to current
}

/**
 * destructor
 * deletes the contents of the Node
 */
Node::~Node()
{
    delete item;
    if(!this->getisLeftThread()) {
        delete this->getLeftChildPtr();
        this->setisLeftThread(false);

    }
    if(!this->getisRightThread()) {
        delete this->getRightChildPtr();
        this->setisRightThread(false);
    }
    // set all pointers to NULL;
}

/* Sets the item contained in the node to new data
 * @param item - the NodeData
 */
void Node::setItem(NodeData* newItem)
{
    this->item = newItem;
}

/* Sets the item contained in the node to new data
 * @return item - the NodeData
 */
NodeData* Node::getItem() const{
    return item;
}

/* Returns left pointer
 * @return pointer to the left
 */
Node* Node::getLeftChildPtr() const
{
    return leftChildPtr;
}

/* Returns right pointer
 * @return pointer to the right
 */
Node* Node::getRightChildPtr() const
{
    return rightChildPtr;
}

/* sets left pointer
 * @param pointer to the left
 */
void Node::setLeftChildPtr(Node* setNode)
{
    leftChildPtr = setNode;
}

/* sets right pointer
 * @param pointer to the right
 */
void Node::setRightChildPtr(Node* setNode)
{
    rightChildPtr = setNode;
}

/* sets bools in data of whehter the pointer to left is a thread
 * @param isThread - boolean
 */
void Node::setisLeftThread(bool isThread)
{
    isLeftThread = isThread;
}

/* sets bools in data of whehter the pointer to right is a thread
 * @param isThread - boolean
 */
void Node::setisRightThread(bool isThread)
{
    isRightThread = isThread;
}

/**
 * Returns bool in the data, whether the pointer to left is a thread
 * @return isLeftThread - boolean
 */
bool Node::getisLeftThread() const
{
    return isLeftThread;
}

/**
 * Returns bool in the data, whether the pointer to right is a thread
 * @return isLeftThread - boolean
 */
bool Node::getisRightThread() const
{
    return isRightThread;
}
