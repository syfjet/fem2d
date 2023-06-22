#include "construction_mesh.h"

Construction_mesh::Construction_mesh(){}
Construction_mesh::~Construction_mesh(){}

void Construction_mesh::node_connection(Object &obj)
{	
	int c_node;
	for (int i = 0; i < obj.cell.size();++i)
	{	

		for (int j = 0; j < obj.cell[i].index_node.size(); ++j)
		{	
			c_node = obj.cell[i].index_node[j];
			obj.node[c_node].connection.push_back(i);
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
       
		for (int j = 0; j < obj.cell[i].index_node.size(); ++j)
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
                Construction_mesh::orientation_cell_cell(cell_massive[j],obj.cell[i].connection,obj.cell[i].index_node,obj.cell[cell_massive[j]].index_node);
			}
		}
		cell_massive.clear();
	}
	cout<<"cell_connection end"<<endl;
}


void Construction_mesh::orientation_cell_cell(int index,array<int,3> &connection, array<int,3> &index_node, array<int,3> &index_node_contact_cell)
{
    auto posit
    {
        [](int ind, int &index, int (&pos)[3], array<int,3> &connection,int &flag)
        {
            ++pos[ind];
            if (pos[ind] == 2)
            {
                connection[ind] = index;
                flag = 1;
            }           
        }
    };

    int pos[] = {0,0,0};
    int flag = 0;
    for (int i = 0; i < connection.size();++i)
    {
        if (index_node[0] == index_node_contact_cell[i] || index_node[1] == index_node_contact_cell[i])
        {
            posit(0,index,pos,connection,flag);
        }
        if (index_node[0] == index_node_contact_cell[i] || index_node[2] == index_node_contact_cell[i])
        {
            posit(1,index,pos,connection,flag);
        }
        if (index_node[1] == index_node_contact_cell[i] || index_node[2] == index_node_contact_cell[i])
        {
            posit(2,index,pos,connection,flag);
        }    
        if (flag == 1){break;}
    }
}





void Construction_mesh::bound_construct(Object &obj)
{
	for (int i = 0; i < obj.segment.size();++i) //
	{	
		vector <int> index_cell;
		for (int j = 0; j < obj.segment[i].index_node.size();++j)
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

