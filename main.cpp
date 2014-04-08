//Edge Liberation Mesh Processor
//Ethan Goff, May 2016

#include <map>
#include "mesh_input.h"

using namespace std;

//We want to read in the data from a file, and find any shared edges, creating a new edge
//	node to replace the match's edge, decoupling the two elements.
//
//	The idea behind this algorithm is to use a hashmap to achieve linear search time
//	for large lists of elements. To do so, we'll create the map such that each edge node
//	is a key, with a matched value of true. We'll also create a vector of the new nodes we'll need
//	to add to the node list.
//
//	As we scan the file, we'll check if the nodes we read already exist in the map. If
//	they do, we'll add a brand new node to the vector, and we'll replace the duplicate
//	we found in the original element list. With this new node. This way, we'll do all the
//	work in a single pass, replacing duplicates as we find them.

int main()
{
    //Our map will have integer keys which correspond with
    //	boolean values. As we add nodes, we'll set the boolean
    //	to true, which will allow us to quickly later see if a node
    //  has been encountered in the past.
    //map <unsigned long int, bool> encounteredNodes;

    mesh_input testInput;
    testInput.init();

	testInput.CloseFiles();

#ifdef DEBUG

    //char* currentElement[20];
    //while()
    	//c
    //{

        //Retrieve the next element from the elements file
       // inputFile.getline(currentElement, 20, 'd');

        //We attempt to find the node within the current element. If the node
        //  has been encountered before, we'll duplicate it in the nodes file,
        //	then replace  the node number where it occured the second time
        //	with the number of this new duplicate.
        //If the node has not been encountered, it is added to the
        //	the map of encountered nodes for future searches.

       // for(int i=0; i<3; i++)
        //{
          //  int currentNodeNumber =  currentElement[3+i] ;
            //Read an edge node within the current element. If the node
            //	has been encountered, currentNodeIsRedundant will point
            //  to a TRUE value. If not, it will point to a FALSE value, which
            //	is the default value for a bool type (our map's value type).
            //currentNodeIsRedundant* = existingNodes[ (currentNodeNumber) ];

            //If the current node has already been encountered...
            //if(currentNodeIsRedundant)
            //{
                //...replicate it,
                //              replicatedNodeNumber = replicateNode(currentElement[3+i]);


            //}

            //If the current node has NOT been encountered previously...
            //else
             //   *currentNodeIsRedundant = true;
        //}
    //}

#endif


    return 0;
}
