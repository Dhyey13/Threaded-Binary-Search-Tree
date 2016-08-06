/**
 @file NodeData.cpp
 NodeData source file contains method for implementing data nodes for a threaded
 tree node. Contains common functions such as constructors, assignment operators,
 comparison operators, mutation and gets for the data.
 
 @author Sean Lai
 @author Sai Badey
 @section ASSIGNEMT Lab5
 @section DUE_DATE 
 */

#include <sstream>
#include <iostream>
#include <string>
#include <stdlib.h>
#include "NodeData.h"

using namespace std;

/**
 * default constructor
 * sets a new NodeData with frequency 0 and blank token.
 */
NodeData::NodeData(){
    setData(0, "");
}

/**
 * copy constructor
 * copies the other NodeData to current NodeData
 * @param other - the other NodeData
 */
NodeData::NodeData(NodeData& other){
    setData(other.getFrequency(), other.getToken());
}

/**
 * constructor, sets the frequency and token to parameters
 * @param frequency - the int frequency
 * @param token - the string token
 */
NodeData::NodeData(int frequency, string token){
    setData(frequency, token);
}


/** 
  * operator=
  * Assign the current NodeData to the other NodeData
  * @param other - other NodeData
  * return the new NodeData
  */
NodeData& NodeData::operator=(const NodeData& other)
{
    if(!(*this==other)) {
        this->setData(other.getFrequency(), other.getToken());
    }
    return *this;
    // Assigns values from other to this node;
    // Returns this node;
}

// Comparision operators --------------------
/**
 * operator==
 * Compares the token of current NodeData to other
 * @param other - other NodeData
 * return Bool
 */
bool NodeData::operator==(const NodeData& other) const
{
    return this->getToken().compare(other.getToken()) == 0;
    // Compare the token, if equal return true;
}

/**
 * operator<
 * Compares the token of current NodeData to other
 * @param other - other NodeData
 * return Bool
 */
bool NodeData::operator<(const NodeData& other) const
{
    return this->getToken().compare(other.getToken()) < 0;
    // Compare the token, return true if current is less than other
}

/**
 * operator>
 * Compares the token of current NodeData to other
 * @param other - other NodeData
 * return Bool
 */
bool NodeData::operator>(const NodeData& other) const
{
    return this->getToken().compare(other.getToken()) > 0;
    // Compare the token, return true if current is greater than other
}

// Mutate and Get ---------------------------------
/**
 * increaseFrequency
 * Increases the frequency of the NodeData by one.
 */
void NodeData::increaseFrequency()
{
    this->frequency++;
}

/**
 * decreaseFrequency
 * decreases the frequency of the NodeData by one.
 */
void NodeData::decreaseFrequency()
{
    this->frequency--;
}

/**
 * Gets the frequency
 * @return int - the frequency
 */
int NodeData::getFrequency() const
{
    return frequency;
}

/**
 * Gets the token
 * @return string - the token
 */
string NodeData::getToken() const
{
    return token;
}

/**
 * Sets the frequency
 * Sets the token to the string parameter
 * @oaram newToken - string token
 */
void NodeData::setToken(string newToken)
{
    this->token = newToken;
}

// Sets the data for current NodeData
// @param frequency - the int frequency
// @param token - the string token
void NodeData::setData(int newFrequency, string newToken)
{
    if(newFrequency >= 0){
        frequency = newFrequency;
    }
    token = newToken;
    // Sets the current NodeData according to parameter
}
