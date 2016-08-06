/** @brief header with attributes + signatures for NodeData
 @file NodeData.h
 @author Sean Lai and Sai Badey */

#ifndef L5NodeData_H
#define L5NodeData_H

#include <string>  // needed in .ccp
using namespace std;

class NodeData {
    
private:
    string token;
    int frequency;
   
    
public:
    // De & Constructors, including default + copy constructors
     NodeData();  // you supply the rest
    NodeData(NodeData& other);
    NodeData(int frequency, string token);
    NodeData& operator=(const NodeData& other);  // for use by copy constructor
    
    // Comparision operators --------------------
    bool operator==(const NodeData& other) const;  // you supply the rest as needed
    bool operator<(const NodeData& other) const;
    bool operator>(const NodeData& other) const;
    
    // Mutate and Get ---------------------------------
    void increaseFrequency();
    void decreaseFrequency();
    int getFrequency() const;
    string getToken() const;
    void setToken(string token);
    void setData(int frequency, string token);
};
#include "NodeData.cpp"
#endif
