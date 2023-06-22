#pragma once
#include <iostream>
#include <vector>
#include <array>
#include <fstream>
#include <regex>
#include "../object.h"

using namespace std; 

class Construction_mesh 
{
public:
	Construction_mesh();
	~Construction_mesh();
protected:
	void node_connection(Object &obj);		
	void cell_connection(Object &obj);	
	void bound_construct(Object &obj);		
private:
	void orientation_cell_cell(int index,array<int,3> &connection, array<int,3> &index_node, array<int,3> &index_node_contact_cell);
}; 
 