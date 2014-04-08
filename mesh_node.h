#ifndef MESH_NODE_H
#define MESH_NODE_H
#define NODE_DIMENSIONS 2

class mesh_node
{
	public:
		mesh_node();
		int sourceNodeNumber;
		float coordinates[NODE_DIMENSIONS];


};

#endif // MESH_NODE_H
