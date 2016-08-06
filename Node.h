/** @brief file with attributes and signatures for TBST Nodes
 @file NodeData.h
 @author Sean Lai and Sai Badey */

#ifndef L5Node_H
#define L5Node_H

#include "NodeData.h"

class Node {
private:
    NodeData* item;  // Pointer to object containing actual data
    Node* leftChildPtr;  // Pointer to left child
    Node* rightChildPtr;  // Pointer to right child
    bool isLeftThread, isRightThread; // flags specify thread or child pointer
    
public:
    // De & Constructors, including default + copy constructors
    Node();  // you supply the rest
    Node(Node &other);
    ~Node();
    
    void setItem(NodeData* item);  // data set / get ---------------
    NodeData* getItem() const;
    
    Node* getLeftChildPtr() const;  // child pointer + thread set / get --
    Node* getRightChildPtr() const;
    void setLeftChildPtr(Node*);
    void setRightChildPtr(Node*);
    
    void setisLeftThread(bool);
    void setisRightThread(bool);
    bool getisLeftThread() const;
    bool getisRightThread() const;
}; // end Node.h
#include "Node.cpp"
#endif


