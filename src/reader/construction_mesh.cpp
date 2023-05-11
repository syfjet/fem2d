#include "construction_mesh.h"

Construction_mesh::Construction_mesh(){}
Construction_mesh::~Construction_mesh(){}

void Construction_mesh::node_connection(Object &obj)
{
	for (int i = 0; i < obj.cell.size();++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			obj.node[obj.cell[i].index_node[j]].connection.push_back(i);
		}
	}
	cout<<"node_connection end"<<endl;
}	

void Construction_mesh::cell_connection(Object &obj)
{
    int i_node;
 
	for (int i = 0; i < obj.cell.size();++i) //
	{	
		vector<int> cell_massive;
       
		for (int j = 0; j < 3; ++j)
		{
			i_node = obj.cell[i].index_node[j];
			for (int k = 0; k < obj.node[i_node].connection.size(); ++k)
			{
				cell_massive.push_back(obj.node[i_node].connection[k]);
			}
		}

		for (int j = 0; j < cell_massive.size();++j)
		{	
			int pos = 0;
			for (int k = j; k < cell_massive.size(); ++k)
			{	
				if ((cell_massive[j] == cell_massive[k]) && (cell_massive[k] != i) && (cell_massive[j] != i) )
				{
					++pos;
				}
			}	
			if (pos == 2)
			{
                //Construction_mesh::orientation_cell_cell(cell_massive[j],obj.cell[i].connection,obj.cell[i].index_node,obj.cell[cell_massive[j]].index_node);
                Construction_mesh::orientation_cell_cell(cell_massive[j],obj.cell[i].connection,obj.cell[i].index_node,obj.cell[cell_massive[j]].index_node);
			}
		}
		cell_massive.clear();
	}
	cout<<"cell_connection end"<<endl;
}

void Construction_mesh::orientation_cell_cell(int index,array<int,3> &connection, array<int,3> &index_node, array<int,3> &index_node_contact_cell)
{
    int pos[] = {0,0,0};
	for (int i = 0; i < 2;++i)
	{
        if (index_node[0] == index_node_contact_cell[i] || index_node[1] == index_node_contact_cell[i])
        {
            ++pos[0];
            if (pos[0] == 2)
            {
                connection[0] = index;
                break;
            }
        }
        if (index_node[1] == index_node_contact_cell[i] || index_node[2] == index_node_contact_cell[i])
        {
            ++pos[1];
            if (pos[1] == 2)
            {
                connection[1] = index;
                break;
            }
        }
        if (index_node[0] == index_node_contact_cell[i] || index_node[2] == index_node_contact_cell[i])
        {
            ++pos[2];
            if (pos[2] == 2)
            {
                connection[2] = index;
                break;
            }
        }
	}
}

void Construction_mesh::bound_construct(Object &obj)
{
	for (int i = 0; i < obj.segment.size();++i) //
	{	
		vector <int> index_cell;
		for (int j = 0; j < 2;++j)
		{
			for (int k = 0; k < obj.node[obj.segment[i].index_node[j]].connection.size();++k)
			{
				index_cell.push_back(obj.node[obj.segment[i].index_node[j]].connection[k]);
			}
		}

		for (int j = 0; j < index_cell.size();++j)
		{	
			int pos = 0;
			for (int k = j; k < index_cell.size();++k)
			{
				if (index_cell[j] == index_cell[k])
				{
					++pos;
					if (pos == 2)
					{
						obj.segment[i].cell = index_cell[j];
					}
				}
			}
		}
		index_cell.clear();
	}
};

