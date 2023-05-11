#include "shift.h"

Shift::Shift(){};
Shift::~Shift(){};         


void Shift::hooke(int i,Object &obj)
{
    Shift::hooke_matrix[0][0] = obj.cell[i].E/(1.0-obj.cell[i].nu*obj.cell[i].nu);
    Shift::hooke_matrix[0][1] = obj.cell[i].nu*obj.cell[i].E/(1.0-obj.cell[i].nu*obj.cell[i].nu);
    Shift::hooke_matrix[0][2] = 0;
    Shift::hooke_matrix[1][0] = obj.cell[i].nu*obj.cell[i].E/(1.0-obj.cell[i].nu*obj.cell[i].nu);
    Shift::hooke_matrix[1][1] = obj.cell[i].E/(1.0-obj.cell[i].nu*obj.cell[i].nu);
    Shift::hooke_matrix[1][2] = 0;
    Shift::hooke_matrix[2][0] = 0;
    Shift::hooke_matrix[2][1] = 0;
    Shift::hooke_matrix[2][2] = obj.cell[i].E/(1.0-obj.cell[i].nu*obj.cell[i].nu)*0.5*(1.0-obj.cell[i].nu);   
}


void Shift::define_matrix(Object &obj)
{
    array<array<double,3>,6> B_matrix_T;    
    array<array<double,3>,6> temp_local_K_matrix;
    array<array<double,6>,6> local_K_matrix;
    int i0,i1,i2,i3,i4,i5;

    vector<double> vec(2*obj.node.size()); 
    for (int i = 0; i < 2*obj.node.size(); ++i)
    {
        Linalg::K_rigid.push_back(vec);  
    }

    for (int i = 0; i < obj.cell.size(); ++i)
    {
        Geometry::geometry_area(i, obj);
        Geometry::geometry_b_matrix(i, obj);
        Shift::hooke(i,obj);
 
        for (int k = 0; k < B_matrix_T.size(); ++k)
        {
            for (int j = 0; j < B_matrix_T[0].size(); ++j)
            {         
                B_matrix_T[k][j] = obj.cell[i].B_matrix[j][k];
            }
        }

        for (int k = 0; k < temp_local_K_matrix.size(); ++k)
        {
            for (int j = 0; j < temp_local_K_matrix[0].size(); ++j)
            {   
                temp_local_K_matrix[k][j] = 0;
                for (int l = 0; l < B_matrix_T[0].size(); ++l)
                {
                    temp_local_K_matrix[k][j] += B_matrix_T[k][l]*Shift::hooke_matrix[l][j];
                }   
            }
        }

        for (int k = 0; k < local_K_matrix.size(); ++k)
        {
            for (int j = 0; j < local_K_matrix[0].size(); ++j)
            {   
                local_K_matrix[k][j] = 0;
                for (int l = 0; l < temp_local_K_matrix[0].size(); ++l)
                {
                    local_K_matrix[k][j] += temp_local_K_matrix[k][l]*obj.cell[i].B_matrix[l][j]; 
                }
            }
        } 

        i0 = 2*obj.cell[i].index_node[0];
        i1 = i0+1;
        i2 = 2*obj.cell[i].index_node[1];
        i3 = i2+1;
        i4 = 2*obj.cell[i].index_node[2]; 
        i5 = i4+1;
        array<int,6> ind = {i0,i1,i2,i3,i4,i5};
        
        for (int k = 0; k < local_K_matrix.size(); ++k)
        {
            for (int j = 0; j < local_K_matrix.size(); ++j)
            {
                Linalg::K_rigid[ind[k]][ind[j]] += local_K_matrix[k][j]*obj.cell[i].area;
            }
        }
    }  
};
