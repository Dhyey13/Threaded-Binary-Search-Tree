/** @brief header with attributes + signatures for tbst.cpp
 @file tbst.h
 @author Sean Lai and Sai Badey */

#ifndef TBST_H
#define TBST_H

#include <iostream>
#include "Node.h"

class tbst
{
    
private:
    // Private global variables
    int data;
    Node* rootPtr;
    int printCount;
    int nodeCount;
    string strNull = " null ";
    // Private methods included in traversals and inserts
    void insertRight(Node* newNode,Node** current,Node** predecessor,Node** successor);
    void insertLeft(Node* newNode,Node** current,Node** predecessor,Node** successor);
    void stepRight(Node** current, Node** parent, Node** predecessor);
    void stepLeft(Node** current, Node** parent, Node** successor);
    bool isLeaf(Node* targetNode);
    bool hasRightChild(Node** targetNode);
    bool hasLeftChild(Node** targetNode);
    void threading(Node* targetNode, Node* predecessor, Node* successor);
    void recPreOrderTraversal(Node* subTree);
    void recPostOrderTraversal(Node* subTree);
    void recInOrderTraversal(Node* subTree);
    
public:
    // Constructors and destrcutors
    tbst();
    ~tbst();
    void clear();
    
    // Gets and booleans
    Node* getRootPtr();
    bool isEmpty();
    bool insert(string target);
    int getNumberOfNodes();
    
    // Remove functions, contains
    bool remove(string target);
    bool remove(Node* target);
    void removeLeaf(Node** parent, Node** current);
    bool contains(Node* subTree);
    
    // Traversals
    void recPreOrderTraversal();
    void recPostOrderTraversal();
    void recInOrderTraversal();
    void iterInOrderTraversal(void (visit(NodeData*)));
    
    // Print functions
    void printNodes(Node** subTree);
    void print(Node* node);

    // Converts tree to array
    void treeToArray(Node* subTree, NodeData* array);
    void treeToArray(Node* subTree, NodeData* array, int* arrayPosition);
    
};
#include "tbst.cpp"

#endif
