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

 
    vector<double> temp_index(obj.node.size());
    vector<double> temp_ux1(obj.node.size());
    vector<double> temp_uy1(obj.node.size());
    vector<double> temp_ux2(obj.node.size());
    vector<double> temp_uy2(obj.node.size());

    
    Linalg::K_rigid_sparse K_rigid_;
 
    for (int i = 0; i < 2*obj.node.size(); ++i)
    {
        Linalg::k_rigid.push_back(K_rigid_);
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
        double temp;
        for (int k = 0; k < temp_local_K_matrix.size(); ++k)
        {
            for (int j = 0; j < temp_local_K_matrix[0].size(); ++j)
            {   
                temp = 0;
                for (int l = 0; l < B_matrix_T[0].size(); ++l)
                {
                    temp += B_matrix_T[k][l]*Shift::hooke_matrix[l][j];
                }   
                temp_local_K_matrix[k][j] = temp;
            }
        }

        for (int k = 0; k < local_K_matrix.size(); ++k)
        {
            for (int j = 0; j < local_K_matrix[0].size(); ++j)
            {   
                temp = 0;
                for (int l = 0; l < temp_local_K_matrix[0].size(); ++l)
                {
                    temp += temp_local_K_matrix[k][l]*obj.cell[i].B_matrix[l][j]; 
                }
                obj.cell[i].local_K_matrix[k][j] = temp*obj.cell[i].area;
            }
        } 
    }

    for (int i = 0; i < obj.node.size(); ++i)
    {

        for (int j = 0; j < obj.node.size(); ++j)
        {
            temp_index[j] = 0;
        }
     
        for (int j = 0; j < obj.node.size(); ++j)
        {
            temp_ux1[j] = 0;
            temp_uy1[j] = 0;
            temp_ux2[j] = 0;
            temp_uy2[j] = 0;        
        }
     
        int i_c,i_n,l;
        for (int j = 0; j < obj.node[i].connection.size(); ++j)
        {   
            i_c = obj.node[i].connection[j];

            for (int k = 0; k < obj.cell[i_c].index_node.size(); ++k)
            {   
                i_n = obj.cell[i_c].index_node[k];
                
                if (i == i_n)
                {
                    l = 2*k;
                }
            }    
            for (int k = 0; k < obj.cell[i_c].index_node.size(); ++k)
            {   
                i_n = obj.cell[i_c].index_node[k];
                temp_index[i_n] = 1; 

                temp_ux1[i_n] +=  obj.cell[i_c].local_K_matrix[l][2*k];   
                temp_uy1[i_n] +=  obj.cell[i_c].local_K_matrix[l][2*k+1];
                temp_ux2[i_n] +=  obj.cell[i_c].local_K_matrix[l+1][2*k];   
                temp_uy2[i_n] +=  obj.cell[i_c].local_K_matrix[l+1][2*k+1];                
            }
        }

        for (int j = 0; j < obj.node.size(); ++j)
        {   
            if (temp_index[j] > 0)
            {
                Linalg::k_rigid[2*i].index.push_back(2*j);
                Linalg::k_rigid[2*i].index.push_back(2*j+1);
                Linalg::k_rigid[2*i].element.push_back(temp_ux1[j]);
                Linalg::k_rigid[2*i].element.push_back(temp_uy1[j]);

                Linalg::k_rigid[2*i+1].index.push_back(2*j);
                Linalg::k_rigid[2*i+1].index.push_back(2*j+1);
                Linalg::k_rigid[2*i+1].element.push_back(temp_ux2[j]);
                Linalg::k_rigid[2*i+1].element.push_back(temp_uy2[j]);
            }

            //This step for individual nodes not includes in the mesh
            if ((temp_index[i] == 0) && (i==j))
            {
                Linalg::k_rigid[2*i].index.push_back(2*j);
                Linalg::k_rigid[2*i].index.push_back(2*j+1);
                Linalg::k_rigid[2*i].element.push_back(0.0);
                Linalg::k_rigid[2*i].element.push_back(0.0);
                Linalg::k_rigid[2*i+1].index.push_back(2*j);
                Linalg::k_rigid[2*i+1].index.push_back(2*j+1);
                Linalg::k_rigid[2*i+1].element.push_back(0.0); 
                Linalg::k_rigid[2*i+1].element.push_back(0.0);                 
            }            
        }
    }  


};
