#include "mesh_input.h"
#include "mesh_node.h"
#include <stdlib.h>
#define OUTPUT_FILE_POSTFIX "_out"
#define INPUT_FILE_NAME "matlabtris"
#define INPUT_FILE_EXTENSION ".inp"
#define LINE_SIZE 200

mesh_input::mesh_input()
{
		numberOfNodes = 0;
	    positionOfNodesInInputFile = 0;
		positionOfFirstElementInInputFile = 0;
		positionToAppendNodesInOutputFile =0;
}

mesh_input::~mesh_input()
{
	//dtor
}

//Appends the elements section and the postlude to the output file
//	and closes both the input and output files
void mesh_input::CloseFiles()
{
#ifdef DEBUG

	//Seek to appropriate positions in both files
	inputFile.seekg(positionOfFirstElementInInputFile);
	outputFile.seekg(positionToAppendNodesInOutputFile);

	//Iterate through the rest of the input file and copy its contents
	//	to the output file

char currentLine[LINE_SIZE] = "";
	while( (inputFile.rdstate() & std::ifstream::eofbit ) != 1 )
	{
		inputFile.getline(currentLine, LINE_SIZE);
        outputFile.write(currentLine, LINE_SIZE);
	}

#endif


	//Close the files
	inputFile.close();
	outputFile.close();
}

void mesh_input::init()
{
    //Open the input file for reading
    //cout << "Input File name: ";
    char inputFileName[LINE_SIZE] = INPUT_FILE_NAME;
    char outputFileName[LINE_SIZE] = "";
	strcpy(outputFileName, inputFileName);
    strcat(outputFileName, OUTPUT_FILE_POSTFIX);
    strcat(inputFileName, INPUT_FILE_EXTENSION);
    strcat(outputFileName, INPUT_FILE_EXTENSION);

    //cin >> inputFileName;

    inputFile.open(inputFileName, fstream::in | fstream::out );
    outputFile.open(outputFileName, ofstream::out | ofstream::trunc);

	CopyPrelude();
	CopyInitialNodes();
}


void mesh_input::CopyPrelude()
{
    //Traverse to the beginning of the nodes list
    char currentLine[LINE_SIZE] = "";
    while(strncmp(currentLine, "*Node", 5)  != 0)
    {
       inputFile.getline(currentLine, LINE_SIZE);
       outputFile << currentLine <<endl;
	}

    positionOfNodesInInputFile = inputFile.tellg();
    cout << positionOfNodesInInputFile;
}

void mesh_input::CopyInitialNodes()
{
    //Traverse to the beginning of the elements list
	char currentLine[LINE_SIZE] = "";
    while(true)
    {
		inputFile.getline(currentLine, LINE_SIZE);
		if(strncmp(currentLine, "*Elem", 5) != 0)
		{
			outputFile << currentLine <<endl;
			numberOfNodes++;
		}
		else
			break;
    }
   	char nextChar = ' ';
    outputFile.put(nextChar);

    positionToAppendNodesInOutputFile= outputFile.tellp();
    positionOfFirstElementInInputFile = inputFile.tellg();
}


//Duplicates a given node from the input file and appends the
//	duplicate to the tail end of the nodes list in the output file
uint16_t mesh_input::DuplicateNode(uint16_t nodeNumber)
{
	char unusedBuffer[LINE_SIZE] = "";

	inputFile.seekg(positionOfNodesInInputFile);
	//Find the node to duplicate
    for(int i = 0; i < nodeNumber-1; i++)
    {
        inputFile.getline(unusedBuffer, LINE_SIZE);
    }
    //Seek to the appension point for the output file
	outputFile.seekp(positionToAppendNodesInOutputFile);


	char nextChar = ' ';
	//Technically Optional Formatting
	inputFile.get(nextChar);
	inputFile.get(nextChar);
	while(nextChar == ' ')
	{
		outputFile.put(nextChar);
		inputFile.get(nextChar);
	}

	//First, we want to append the *new* node number
	//Create a character array to hold the new node number as a string
	char newNodeNumber[8];
	itoa(++numberOfNodes, newNodeNumber, 10);
	//Add a comma at the end
	char comma[2] = {',','\0'};
	strcat(newNodeNumber, comma);
	//Append the node number as a character string
	outputFile.write(newNodeNumber, strlen(newNodeNumber) );

	//Then, we ignore the old node number in the inputFile, seeking to the beginning of the coordinates list
	inputFile.ignore(LINE_SIZE, ',');

	//Finally, we copy the node's list coordinates character-for-character
	while(nextChar != '\n')
	{
		inputFile.get(nextChar);
		outputFile.put(nextChar);
	}

	//Update our record of where to append new nodes
    positionToAppendNodesInOutputFile = outputFile.tellp();
    return numberOfNodes;
}


/*
uint16_t FindPositionOfFirstDifferingCharacter(char* charStringToSearch, uint16_t maximumSearch = LINE_SIZE)
{
	uint16_t position = 0;
	char characterToIgnore = charStringToSearch[position];

	while(charStringToSearch[position] == characterToIgnore)
	{
		position++;
	}
	return position;
}
*/

