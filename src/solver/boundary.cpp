#include "boundary.h"

Boundary::Boundary(){};
Boundary::~Boundary(){};         

void Boundary::boundary_set(Object &obj,vector<double> &U)
{

    for (int i = 0; i < obj.segment.size(); ++i)
    {
        if (obj.segment[i].type == 1)
        {

            U[2*obj.segment[i].index_node[0]] = 0; 
            U[2*obj.segment[i].index_node[0]+1] = 0; 
            U[2*obj.segment[i].index_node[1]] = 0; 
            U[2*obj.segment[i].index_node[1]+1] = 0; 
          
        }
        else if (obj.segment[i].type == 2)
        {
            U[2*obj.segment[i].index_node[0]] = 0; 
            U[2*obj.segment[i].index_node[1]] = 0; 
                      
        }
        else if (obj.segment[i].type == 3)
        {
            U[2*obj.segment[i].index_node[0]+1] = 0; 
            U[2*obj.segment[i].index_node[1]+1] = 0;         
        }
    }

};