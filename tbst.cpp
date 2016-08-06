/**
 @file tbst.cpp
 Source file that contains functions that deals with the overall threaded
 binary search tree. It contains constructor that sets a Node to its root,
 and destructor. Contains recursive and iterative traversal functions and printing
 functions. Also contains insert and remove functions that deals with the Nodes in the
 tree.
 
 @author Sean Lai
 @author Sai Badey
 @section ASSIGNEMT Lab5
 @section DUE_DATE
 */

#include "tbst.h"
#include "NodeData.h"
#include "Node.h"
using namespace std;


/* default constructor
 * Creates a tbst root pointing at the parameter
 * @param root - the root Node
 */
tbst::tbst()
{
    rootPtr = NULL;
    printCount = 0;
    nodeCount = 0;
}


// Destructor
// removes the tree by calling clear function
// Note: most of the deletion process is done recursively by Node
tbst::~tbst(){
    clear();
}

/**
 * Returns whether or the tree is empty
 * @return bool
 */
bool tbst::isEmpty() {
    return rootPtr == NULL;
}

/**
 * Allows outside functions to access the root of the tree
 */
Node* tbst::getRootPtr()
{
    return rootPtr;
}

/**
 * Calls the real recursive pre order traversal and hands it the tree's root
 */
void tbst::recPreOrderTraversal(){
    recPreOrderTraversal(rootPtr);
}

/**
 * Main recursive function for preorder.
 * The recursive function calls on print nodes to handle printing.
 * @param subTree - the tbst tree for traversal
 * @param printCount - count of elements
 */
void tbst::recPreOrderTraversal(Node* subTree)
{
    // as long as the subtree is not null, recurses left children, then right children
    if(subTree != NULL)
    {
        printNodes(&subTree);
        
        if(hasLeftChild(&subTree))
        {
            recPreOrderTraversal(subTree->getLeftChildPtr());
        }
        
        if(hasRightChild(&subTree))
        {
            recPreOrderTraversal(subTree->getRightChildPtr());
        }
        
    }
}

/**
 * Calls the real recursive post order traversal and hands it the tree's root
 */
void tbst::recPostOrderTraversal(){
    recPostOrderTraversal(rootPtr);
}

/**
 * Main recursive function for post order.
 * The recursive function calls on print nodes to handle printing.
 * @param subTree - the tbst tree for traversal
 * @param printCount - count of elements
 */
void tbst::recPostOrderTraversal(Node* subTree)
{
    // as long as the subtree is not null, recurses left children, then right children
    if(subTree != NULL)
    {
        if(hasLeftChild(&subTree))
        {
            recPreOrderTraversal(subTree->getLeftChildPtr());
        }
        
        if(hasRightChild(&subTree))
        {
            recPreOrderTraversal(subTree->getRightChildPtr());
        }
        
        printNodes(&subTree);
    }
}

/**
 * Calls the real recursive in order traversal and hands it the tree's root
 */
void tbst::recInOrderTraversal(){
    recInOrderTraversal(rootPtr);
}
/**
 * Main recursive function for in order.
 * The recursive function calls on print nodes to handle printing.
 * @param subTree - the tbst tree for traversal
 * @param printCount - count of elements */
void tbst::recInOrderTraversal(Node* subTree)
{
    // as long as the subtree is not null, recurses left children, then right children
    if(subTree != NULL)
    {
        if(hasLeftChild(&subTree))
        {
            recPreOrderTraversal(subTree->getLeftChildPtr());
        }
        printNodes(&subTree);
        
        if(hasRightChild(&subTree))
        {
            recPreOrderTraversal(subTree->getRightChildPtr());
        }
        
        
    }
}

/**
 * Main iterative function for inorder.
 * Takes in a function pointer to perform any function while traversing tree
 * @param visit - the function to perform
 */
void tbst::iterInOrderTraversal(void (visit(NodeData*)))
{
    //The two node pointers and while loop below initialize current at the left most node
    //in the subtree. And sets up a previous pointer for future use
    Node* current = rootPtr;
    Node* previous = NULL; // Valgrind sometimes shows that this pointer var is not used but it is.
    while(hasLeftChild(&current))
    {
        current = current->getLeftChildPtr();
    }
    
    //traverses through the tree and performs the visit function
    while(current != NULL)
    {
        (*visit)(current->getItem());
        
        previous = current;
        current = current->getRightChildPtr();
        
        //goes extreme left node as long as the right child pointer is not threaded
        //then while loop is triggered and goes to right child before repeating until tree's end
        if(current!= NULL)
        {
            if(!hasRightChild(&current))
            {
                while(hasLeftChild(&current))
                {
                    current = current->getLeftChildPtr();
                }
            }
        }
    }
}

/**
 * Prints the node's contents, then prints the pointers of the nodes for validation
 * @Param: the node which is being checked
 */
void tbst::printNodes(Node** subTree)
{
    Node* temp = *subTree;
    cout << temp->getItem()->getToken() << " ";
    if(temp->getLeftChildPtr() != NULL)
        cout << temp->getLeftChildPtr()->getItem()->getToken() << " ";
    else
        cout << strNull;
    if(temp->getRightChildPtr() != NULL)
        cout << temp->getRightChildPtr()->getItem()->getToken() << endl;
    else
        cout << strNull << endl;
}

// Get the number of nodes present in tbst
int tbst::getNumberOfNodes()
{
    return nodeCount;
    // return the number of nodes
}

/**
 * Threading function is for modularity. It threads the nodes which were just inserted
 * @Param, the target node which is being threaded, and its predecessor and successor nodes
 */
void tbst::threading(Node* targetNode, Node* predecessor, Node* successor)
{
    targetNode->setRightChildPtr(successor);
    targetNode->setLeftChildPtr(predecessor);
    targetNode->setisRightThread(successor != NULL);
    targetNode->setisLeftThread(predecessor != NULL);
}

/**
 * insert function which takes in a string
 * inserts string into a node data object inside a node in the tree
 * @param target - string to insert into the tree
 * Returns bool to check if insert worked.
 */
bool tbst::insert(string target)
{
    //checks for empty string
    if (target == "")
    {
        return false;
    }
    
    //wraps the string object insdie a node data then a node
    NodeData* newNodeData = new NodeData(0, target);
    Node* newNode = new Node();
    newNode->setItem(newNodeData);
    
    //insert at the root if empty
    if (this->isEmpty())
    {
        rootPtr = newNode;
        nodeCount++;
        rootPtr->getItem()->increaseFrequency();
        return true;
    }
    
    bool found = false;
    Node* current = rootPtr;
    Node* parent = rootPtr;
    Node* successor = NULL;
    Node* predecessor = NULL;
    
    while(!found)
    {
        //if a copy of the to-be-inserted node is found, increment frequency and delete new node
        if( *newNodeData == *current->getItem())
        {
            current->getItem()->increaseFrequency();
            delete newNode;
            found = true;
        }
        //if inserting left of the current node
        else if ( *newNodeData < *current->getItem() && !hasLeftChild(&current))
        {            insertLeft(newNode, &current, &predecessor, &successor);
            threading(newNode, predecessor, successor);
            found = true;
        }
        //if inserting right of the current node
        else if ( *newNodeData > *current->getItem() && !hasRightChild(&current))
        {
            insertRight(newNode, &current, &predecessor, &successor);
            threading(newNode, predecessor, successor);
            found = true;
        }
        //if insert spot is not found, step to the left if new node is less than current node
        else if ( *newNodeData < *current->getItem())
        {
            stepLeft(&current, &parent, &successor);
        }
        //if insert spot is not found, step to the right if new node is greater than current node
        else if ( *newNodeData > *current->getItem())
        {
            stepRight(&current, &parent, &predecessor);
        }
    }
    return found; //allows you to quit the while loop since you found the insert spot
}

/**
 * The insert function which inserts a new node to the right of the current node
 * Also updates the threads.
 */
void tbst::insertRight(Node* newNode,Node** current,Node** predecessor,Node** successor)
{
    Node * temp = *current;
    temp->setRightChildPtr(newNode);
    temp->setisRightThread(false);
    temp->getRightChildPtr()->getItem()->increaseFrequency();
    predecessor = current;
    nodeCount++;
}

/**
 * The insert function which inserts a new node to the left of the current node
 * @param: the current node to update and its parent and successor threads
 */
void tbst::insertLeft(Node* newNode,Node** current,Node** predecessor,Node** successor)
{
    Node * temp = *current;
    temp->setLeftChildPtr(newNode);
    temp->setisLeftThread(false);
    temp->getLeftChildPtr()->getItem()->increaseFrequency();
    successor = current;
    nodeCount++;
}

/**
 * Allows the current node to step to the left. Also updates the threads to allow for easy insert.
 * @param: the current node to update and its parent and successor threads
 */
void tbst::stepLeft(Node** current, Node** parent, Node** successor)
{
    *parent = *current;
    Node * temp = *current;
    *successor = *parent;
    *current = temp->getLeftChildPtr();
}

/**
 * Allows the current node to step to the rights. Also updates the threads to allow for easy insert.
 * @param: the current node to update and its parent and predecessor threads
 */
void tbst::stepRight(Node** current, Node** parent, Node** predecessor)
{
    *parent = *current;
    Node * temp = *current;
    *predecessor = *parent;
    *current = temp->getRightChildPtr();
}

/**
 * delete function for the tbst.
 * wraps the string to delete inside a node and calls the main delete function to delete it.
 * This function does not work. We accept pointloss since we did not implement in time.
 * @param target - string to delete
 */
bool tbst::remove(string target)
{
    if (this->isEmpty())
    {
//        cout << "tree is empty" << endl;
        return false;
    }
    else if (target == rootPtr->getItem()->getToken() &&
             (rootPtr->getLeftChildPtr() == NULL &&
              rootPtr->getRightChildPtr() == NULL))
    {
//        cout << "deleting root" << endl;
        delete rootPtr; //check delete statement
        return true;
    }
    else
    {
        NodeData* newNodeData = new NodeData(0, target);
        Node* newNode = new Node();
        newNode->setItem(newNodeData);
        
        if(contains(newNode)){
//            cout << "found new node!" << endl;
            return remove(newNode);
        }
        else{
//            cout << "could not find in list";
            return false;
        }
        
    }
}

/**
 * main delete function for the tbst.
 * Deletes based on the number of children.
 * This function does not work. We accept pointloss since we did not implement in time.
 * @param data - node to delete
 */
bool tbst::remove(Node* target)
{
    bool found = false;
    Node* current = rootPtr;
    Node* parent = NULL;
    Node* successor = NULL;
    Node* predecessor = NULL;
    
    while(!found)
    {
//        cout << "entered wile loop" << endl;
        if( target->getItem() == current->getItem())
        {
            if(isLeaf(current))
            {
                removeLeaf(&parent, &current);
                found = true;
            }
            
            else if(hasLeftChild(&current) && hasRightChild(&current))
            {
                Node* switchNode = current->getRightChildPtr();
                Node* switchNodeParent = current;
                
                while(!switchNode->getisLeftThread()){
                    switchNodeParent = switchNode;
                    switchNode = switchNode->getLeftChildPtr();
                }
                
                //replace the current node
                current->setItem(switchNode->getItem());
                switchNodeParent->setLeftChildPtr(current);
                switchNodeParent->setisLeftThread(true);
                
                if(current == rootPtr){
                    rootPtr = switchNode;
                }
                remove( switchNode);
                
                found = true;
            }
            
            
            //right child only
            else if ( !hasLeftChild(&current) && hasRightChild(&current))
            {
                Node* rightChild = current->getRightChildPtr();
                
                if(parent->getRightChildPtr() == current){
                    parent->setRightChildPtr(rightChild);
                }
                else
                {
                    parent->setLeftChildPtr(rightChild);
                }
                
                if(rightChild->getisLeftThread()
                   || rightChild->getLeftChildPtr() == NULL)
                {//has no left child
                    rightChild->setLeftChildPtr(current->getLeftChildPtr());
                    rightChild->setisLeftThread(current->getisLeftThread());
                }
                
                
                cout << parent->getisLeftThread() << " " << parent->getisRightThread();
                
                found = true;
            }
            //left child only
            else if (hasLeftChild(&current) && !hasRightChild(&current))
            {
                Node* leftChild = current->getLeftChildPtr();
                
                if(parent->getRightChildPtr() == current){
                    parent->setRightChildPtr(leftChild);
                }
                else
                {
                    parent->setLeftChildPtr(leftChild);
                }
                
                if(leftChild->getisRightThread() || leftChild->getRightChildPtr() == NULL)
                {//has no left child
                    leftChild->setRightChildPtr(current->getRightChildPtr());
                    leftChild->setisRightThread(current->getisRightThread());
                }
                
                cout << parent->getisLeftThread() << " " << parent->getisRightThread();
                found = true;
            }
        }
        
        else if ( target->getItem() > current->getItem())
        {
//            cout << "I stepped left";
            stepLeft(&current, &parent, &successor);
        }
        
        else if ( target->getItem() < current->getItem())
        {
//            cout << "I stepped right";
            stepRight(&current, &parent, &predecessor);
        }
    }
    cout << endl;
    //    recPreOrderTraversal();
    return found;
}


/**
 * delete function for a leaf.
 * This funciton attempts to remove a leaf.
 * This does not work and is part of the remove function.
 * We accept point loss.
 * @param data - string to delete
 */
void tbst::removeLeaf(Node** parent, Node** current)
{
    Node* tempParent = *parent;
    Node* tempCurrent = *current;
    if(tempParent->getRightChildPtr() == *current){
        //check null statement
        tempParent->setRightChildPtr(tempCurrent->getRightChildPtr());
        tempParent->setisRightThread(tempCurrent->getisRightThread());
        delete *current;
    }
    else
    {
        tempParent->setLeftChildPtr(tempCurrent->getLeftChildPtr());
        tempParent->setisLeftThread(tempCurrent->getisLeftThread());
        delete *current;
    }
}

/**
 * clear function for the tbst. Deletes a all nodes and set current to root
 */
void tbst::clear()
{
    delete rootPtr;
    rootPtr = NULL;
}

/**
 * search function for the tbst. search a the tree for the target data
 * @data - target data for the search
 */
bool tbst::contains(Node* subTree)
{
    if (subTree == NULL) {
        return false;
    }
    Node* current = rootPtr;
    Node* previous = NULL;
    while(!current->getisLeftThread() && current->getLeftChildPtr() != NULL)
    {
        current = current->getLeftChildPtr();
    }
    //previous loc are all initializers which start current at the left most node
    //sets up a previosu pointer for help later
    
    //traverses through the entire tree while searching for the node
    while(current != NULL)
    {
        if(current->getItem() == subTree->getItem())
        {
            return true;
        } //in node is found, immediate return true to exit loop and method
        
        previous = current;
        current = current->getRightChildPtr();
        
        //steps right once, then loops to left most node while right is not threaded
        if(previous->getRightChildPtr() != NULL && !previous->getisRightThread())
        {
            while(!current->getisLeftThread() && current->getLeftChildPtr() != NULL)
            {
                current = current->getLeftChildPtr();
            }
        }
    }
    //node has not been found yet and entire tree has been traversed
    return false;
}

/**
 * Converts the tree to an array
 * @param data - string to delete
 */
void tbst::treeToArray(Node* subTree, NodeData* array)
{
    int arrayPosition = 0;
    treeToArray(subTree, array, &arrayPosition);
}

/**
 * Convers the tree to an array
 * @Param node to start converting into an array from
 */
void tbst::treeToArray(Node* subTree, NodeData* array, int* arrayPosition)
{
    if (subTree == NULL) {
        return;
    }
    
    array[*arrayPosition] = *subTree->getItem();
    (*arrayPosition)++;
    
    if(!subTree->getisLeftThread() && subTree->getLeftChildPtr() != NULL)
    {
        treeToArray(subTree->getLeftChildPtr(), array, arrayPosition);
    }
    
    if(!subTree->getisRightThread() && subTree->getRightChildPtr() != NULL)
    {
        treeToArray(subTree->getRightChildPtr(), array, arrayPosition);
    }
}

/**
 * A boolean which returns false if there is any children.
 * Checks for both nulls and threads.
 */
bool tbst::isLeaf(Node* targetNode)
{
    return (!hasLeftChild(&targetNode))
    && (!hasRightChild(&targetNode));
}

/**
 * A boolean which returns false if there is a left child.
 * Checks for both nulls and threads.
 */
bool tbst::hasLeftChild(Node** targetNode)
{
    Node* temp = *targetNode;
    return (!temp->getisLeftThread() && temp->getLeftChildPtr() != NULL);
}

/**
 * A boolean which returns false if there is right children.
 * Checks for both nulls and threads.
 */
bool tbst::hasRightChild(Node** targetNode)
{
    Node* temp = *targetNode;
    return (!temp->getisRightThread() && temp->getRightChildPtr() != NULL);
}
