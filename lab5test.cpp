//
//  lab5test.cpp
//  lab05
//
//  Created by Sean on 3/2/14.
//  Copyright (c) 2014 Sean. All rights reserved.
//

#include <string.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <sstream>
#include "tbst.h"
#include "NodeData.h"

using namespace std;

bool printToFile = false;
bool debug = false;
int numOfNodes = 13;
int nodeNumArg = 0;
bool bools[52];
int const printAmount = 21;
int const printAmountPerLineMax = 7;
int printCount = 0;

const char* alpha[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"};

void printTokens(NodeData* nodeArray, int arraySize, bool isMostToLeast);
string stringGenerator(int seed);
int randNumber();
void print(NodeData* node);



int main(int argc, const char * argv[])
{
    for ( int i = 0 ; i < 52; i++)
    {
        bools[i] = 0;
    }
    
    int insertTotal = 52;
    if(argc > 1)
    {
        if (strcmp(argv[argc-1], "DEBUG") == 0) {
            debug = true;
        }
        string str = argv[argc-2];
        istringstream (str) >> nodeNumArg;
        if (nodeNumArg > 0 && nodeNumArg < 53)
        {
            insertTotal = nodeNumArg;
        }
    }
    tbst* tree1 = new tbst();
    
    for(int i = 0; i < insertTotal; i++)
    {
        for (int j = 0; j < i + 1; j++) {
            
            tree1->insert(alpha[j]);
        }
    }
    
    //These statements test tree to array and print tokens when there are a lot of nodes
    int arraySize = tree1->getNumberOfNodes();
    NodeData* nodeArray = new NodeData[arraySize];
    tree1->treeToArray(tree1->getRootPtr(), nodeArray);
    printTokens(nodeArray, arraySize, true);
    
    // TESTS:
    
    tbst* tree2 = new tbst();
    tree2->insert(""); // Should add nothing.
    
    tree2->insert("a"); //tests print out statement when there are less than 21 nodes
    tree2->insert("a");
    tree2->insert("a"); // Tests frequency
    cout << endl;
    //These statements test tree to array and print tokens when there are very few nodes
    delete [] nodeArray;
    arraySize = tree2->getNumberOfNodes();
    nodeArray = new NodeData[arraySize];
    tree2->treeToArray(tree2->getRootPtr(), nodeArray);
    printTokens(nodeArray, arraySize, true);
    
    
    cout << endl;
    //tests the recursive pre order as well as the threading for the root
    tree2->recPreOrderTraversal();
    tree2->insert("b");
    cout << endl;
    tree2->recPostOrderTraversal();
    tree2->insert("c");
    cout << endl;
    tree2->recInOrderTraversal();
    
    cout << endl;
    //testing our iterative in order traversal as well as the visit implementation AND the print function
    tree2->insert("d");
    void (*printtest)(NodeData*) = &print;
    tree2->iterInOrderTraversal(printtest);
    cout << endl;
    if (tree2->contains(tree1->getRootPtr()))
    {
        cout << "Tree2 contains tree1's nodes." << endl;
    }
    else
        cout << "Tree2 does not contain tree1's nodes" << endl;
    
    if (tree2->contains(tree2->getRootPtr()))
    {
        cout << "Tree2 contains tree2's root." << endl;
    }
    else
        cout << "Tree2 does not contain tree2's root" << endl;

    delete tree1;
    delete tree2;
    delete [] nodeArray;
    return 0;
}

void printTokens(NodeData* nodeArray, int arraySize, bool isMostToLeast)
{
    
    int switchIndex = 0;
    int enterTracker = 0;
    NodeData temp; // *always* initialize variables
    
    for (int traversalIndex=1; traversalIndex < arraySize; ++traversalIndex) // use pre-increment to avoid unneccessary temporary object
    {
        temp.setData(nodeArray[traversalIndex].getFrequency(), nodeArray[traversalIndex].getToken());
        switchIndex = traversalIndex-1;
        if (isMostToLeast)
        {
            while((switchIndex >= 0) && ((nodeArray[switchIndex].getFrequency() < temp.getFrequency() ||
                                          ((nodeArray[switchIndex].getFrequency() == temp.getFrequency() && nodeArray[switchIndex].getToken() < temp.getToken() )))))
            {
                nodeArray[switchIndex+1] = nodeArray[switchIndex];
                switchIndex -= 1;
            }
        }
        else
        {
            while((switchIndex >= 0) && ((nodeArray[switchIndex].getFrequency() > temp.getFrequency() ||
                                          ((nodeArray[switchIndex].getFrequency() == temp.getFrequency() && nodeArray[switchIndex].getToken() > temp.getToken() )))))
            {
                nodeArray[switchIndex+1] = nodeArray[switchIndex];
                switchIndex -= 1;
            }
            
        }
        nodeArray[switchIndex+1] = temp;
    }
    
    if(arraySize > printAmount)
        arraySize = printAmount;
    
    for(int traversalIndex = 0; traversalIndex < arraySize; traversalIndex++) {
        if (nodeArray[traversalIndex].getFrequency() != 0)
        {
            cout << "[" << nodeArray[traversalIndex].getToken() << ": " << nodeArray[traversalIndex].getFrequency() << "] ";
            enterTracker++;
            if (enterTracker % printAmountPerLineMax == 0)
            {
                cout << endl;
            }
            if (arraySize % 7 != 0 && arraySize < 21)
            {
                cout << endl;
            }
        }
    }
    
}

void print(NodeData* node)
{
    cout << "[" << node->getToken() << ": " << node->getFrequency() << "] ";
    printCount++;
    if (printCount % 7 == 0 && printCount != 0){
        cout << endl;
    }
}

string stringGenerator(int seed)
{
    char retChar;
    string retVal = "";
    if(seed >= 26)
    {
        seed+= 39;
        retChar = (char) seed;
    }
    else
    {
        seed += 97;
        retChar = (char) seed;
    }
    retVal += retChar;
    return retVal;
}

