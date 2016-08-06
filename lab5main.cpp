/**
 @file lab5main.cpp
 Main file for the threaded binary search tree lab. Contains methods
 to input default file ("hamlet.txt") or sequences of files in commandline
 arguments. The functions will add a token of each word in the text file into
 the tbst, and tbst will print the sorted content of the tokens either 
 most to least or least to most frequency. The printout can be in console or
 output file ("lab5output.txt").
 
 @author Sean Lai
 @author Sai Badey
 @section ASSIGNEMT Lab5
 @section DUE_DATE
 */

#include <string.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <cctype>
#include "tbst.h"
#include "NodeData.h"

using namespace std;

bool printToFile = false;

// Global variables.
string* tokenInsertArr;
const char** filename;
const char* defaultFile[] = {"hamlet.txt"};
const char* outputFileName[] = {"lab5out.txt"};
string stringInitializer = "";
int numFiles;
int numOfTokens = 0;
int printCount = 0;
int const printAmount = 21;
int const printAmountPerLineMax = 7;
ofstream fout;
bool ifFileArg = false;
bool noMoreFiles = false;
bool debug = false;

// Introduction strings
string intro1 = "Lab 5:";
string intro2 = "This program will take file(s) and process it to insert every string as a token inside a threaded binary search tree. It will then print the content result of the tbst, from either least to most or most to least per frequency. Commandline FILE will print all the contents into a output file instead of console. CommandLine debug will print out the process into the console.";
string intro3 = "CONTENT OUTPUT: ";
string error1 = " does not exist.";
string error2 = "File does not exist.";

// Prototypes
void printTokens(NodeData* nodeArray, int arraySize, bool isMostToLeast);
void processFile(ifstream &inputFile, int targetIndex, tbst* tree);
void print(NodeData* node);
void printIntro(bool ifFile);

/**
 * Main method. It will first print the introduction. Then it will handle command
 * line arguments. It will either process file for default txt file or files
 * specified in the command line arguments. It will delete any allocated memories
 * in the end. Prints out the first 21 elements of ouput.
 */
int main(int argc, const char * argv[])
{
    
    numFiles = argc;
    
    if(numFiles > 1) { // If more than one argument
    if (strcmp(argv[argc-1], "DEBUG") == 0) {
            debug = true;
            numFiles--;
        }
    else if (strcmp(argv[argc-1], "FILE") == 0) {
        printToFile = true;
        numFiles--;
    }
    }
    if(numFiles > 2) // If there are more than two .txt file commands
    {
    if (strcmp(argv[argc-2], "FILE") == 0) {
        printToFile = true;
        numFiles--;
    }
    }
    
    filename = new const char*[numFiles];
    
    if(numFiles > 1)
    {
        for (int i = 1; i <= numFiles; i++) {
            filename[i-1] = argv[i];
            ifFileArg = true;
        }
    }

    if(printToFile)
    fout.open(outputFileName[0]);
    
    printIntro(ifFileArg);
    
    // Runs a for loop to input files. If the file is not found, it will produce
    // an error message. If multiple files was in the commandline arguments,
    // It will attempt to skip to the next file if a file does not exist until the
    // end.
    for (int targetIndex=0; targetIndex < numFiles; targetIndex++) {
        
        tbst* tree = new tbst();
        if (ifFileArg)
        {
            ifstream inputFile((filename[targetIndex]));
            bool hasNextFile = true;
            while ((!inputFile && targetIndex < numFiles - 1) && hasNextFile)  {
                cerr << (filename[targetIndex]) << error1 << endl;
                cout << endl;
                targetIndex++;
                ifstream inputFile((filename[targetIndex]));
                if(inputFile)
                hasNextFile = false;
            }
            if (inputFile || !hasNextFile) {
                cout << (filename[targetIndex]) << endl;
                ifstream inputFile((filename[targetIndex]));
                processFile( inputFile, targetIndex, tree);
            }
        }
        else
        {
            ifstream inputFile(defaultFile[0]);
            if(!inputFile)
                cerr << error2 << endl;
            else
            {
                cout << (defaultFile[0]) << endl;
                processFile( inputFile, targetIndex, tree);
            }
        }
        delete tree;
    }
    delete [] filename;
    return 0;
}

/**
 * Processes the file input. It will first clear out any blanks and spaces
 * in front. It will insert string tokens for each words separated by punctuation
 * or spaces. Punctuations are considered tokens while spaces are not.
 * Calls the print function to print the contents of the tree at the end.
 * @param inputFile - the file input
 * @param targetIndex - the number of files
 * @param tree - the tbst tree to input the tokens
 */
void processFile(ifstream &inputFile, int targetIndex, tbst* tree)
{
    if(!noMoreFiles) {
        char targetChar;
        targetChar = inputFile.get();
        while (isblank(targetChar) || isspace(targetChar)){
            targetChar = inputFile.get();
            if (debug)
                cout << "Removed preceding blank, tab or enter" << endl;
        }
        
        string insertStr;
        insertStr = insertStr + targetChar;
        while(!inputFile.eof()){
            targetChar = inputFile.get();
            // Checks if char is blank or space
            if (isblank(targetChar) || isspace(targetChar) || inputFile.eof())
            {
                tree->insert(insertStr);
                if (debug)
                    cout << "Inserted token: " << insertStr << endl;
                insertStr = stringInitializer;
            }
            // Checks if the char is alphabet or apostrophe
            else if (isalpha(targetChar) || targetChar == '\'')
            {
                insertStr = insertStr + targetChar;
            }
            // Case if the char is any other punctuation.
            else
            {
                if (debug)
                    cout << "Inserted token: " << insertStr << endl;
                tree->insert(insertStr);
                insertStr = stringInitializer;
                insertStr = insertStr + targetChar;
                if (debug)
                    cout << "Inserted token: " << insertStr << endl;
                tree->insert(insertStr);
                insertStr = stringInitializer;
            }
        }
    }
    int arraySize = tree->getNumberOfNodes();
    NodeData* nodeArray = new NodeData[arraySize];
    tree->treeToArray(tree->getRootPtr(), nodeArray);

    printTokens(nodeArray, arraySize, true);
    cout << endl;
    delete [] nodeArray;
}

/**
 * Prints the content of the tbst. It will print the seven element and will add
 * a endline. Every element is in format of [token:frequency].
 * @param nodeArray - the node data
 * @param arraySize - the number of the nodes
 * @param isMostToLeast - true will print most to least, false will print least to most
 */
void printTokens(NodeData* nodeArray, int arraySize, bool isMostToLeast)
{
    
    int switchIndex = 0;
    int enterTracker = 0;
    NodeData temp; // *always* initialize variables
    
    // Uses traversal and creates an nodeArray recursivly and fills the
    // contents with the nodes.
    for (int traversalIndex=1; traversalIndex < arraySize; ++traversalIndex)
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
    
    // Prints to console or output file.
    for(int traversalIndex = 0; traversalIndex < arraySize; traversalIndex++) {
        if (nodeArray[traversalIndex].getFrequency() != 0)
        {
            if (printToFile)
                fout << "[" << nodeArray[traversalIndex].getToken() << ": " << nodeArray[traversalIndex].getFrequency() << "] ";
            else
                cout << "[" << nodeArray[traversalIndex].getToken() << ": " << nodeArray[traversalIndex].getFrequency() << "] ";
            enterTracker++;
            if (enterTracker % printAmountPerLineMax == 0)
            {
                cout << endl;
            }
        }
    }
    // Creates a endline at end if the number of nodes are less than 21.
    if (arraySize % 7 != 0 && arraySize < 21)
    {
        cout << endl;
    }
}

/**
 * formats the prints of the traversals, it will have a line break every
 * seven elements
 * @param node - the node input
 */
void print(NodeData* node)
{
    if (printToFile)
        fout << "[" << node->getToken() << ": " << node->getFrequency() << "] ";
    else
        cout << "[" << node->getToken() << ": " << node->getFrequency() << "] ";
    printCount++;
    if (printCount % 7 == 0 && printCount != 0){
        cout << endl;
    }
}

/**
 * Prints the introduction.
 * @param ifFile - true if prints to a output file. False of console.
 */
void printIntro(bool ifFile)
{
    if (ifFile) {
        fout << intro1 << endl;
        fout << intro2 << endl << endl;
        fout << intro3 << endl;
    }
    else
    {
        cout << intro1 << endl;
        cout << intro2 << endl << endl;
        cout << intro3 << endl;
    }
}
