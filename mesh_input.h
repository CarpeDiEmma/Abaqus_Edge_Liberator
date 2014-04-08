#include <fstream>
#include <iostream>
#include <string>
using namespace std;



#ifndef MESH_INPUT_H
#define MESH_INPUT_H


class mesh_input
{
	public:
		mesh_input();
		virtual ~mesh_input();
		void init();
		void DuplicateNode(uint16_t nodeNumber);
		void CloseFiles();

	protected:
	private:
    	void CopyPrelude();
		void CopyInitialNodes();

		fstream inputFile;
		uint16_t numberOfNodes;
	    streampos positionOfNodesInInputFile;
		streampos positionOfFirstElementInInputFile;

		ofstream outputFile;
		streampos positionToAppendNodesInOutputFile;

};

#endif // MESH_INPUT_H
