#include "linalg.h"

Linalg::Linalg(){};
Linalg::~Linalg(){};         

void Linalg::update_K_rigid(vector<double> &U)
{

    for (int k = 0; k < Linalg::K_rigid.size(); ++k)
    {
        for (int j = 0; j < Linalg::K_rigid[0].size(); ++j)
        {   
            Linalg::K_rigid[k][j] = Linalg::K_rigid[k][j]*U[j]; 
            Linalg::K_rigid[j][k] = Linalg::K_rigid[j][k]*U[j]; 
        }
        if (Linalg::K_rigid[k][k] == 0) 
        {
            Linalg::K_rigid[k][k] = 1;
        }
    }

}

void Linalg::solve_linear_system(Object &obj)
{
    vector<double> U(2*obj.node.size(),1); 
    vector<vector<double>> LU(2*obj.node.size(), vector<double>(2*obj.node.size(),0));

    Boundary::boundary_set(obj,U);
    Linalg::update_K_rigid(U);

    for (int i = 0; i < obj.node.size(); ++i)
    {   
        U[2*i] = obj.node[i].px;
        U[2*i+1] = obj.node[i].py;    
    }

    double temp;
    for (int j = 0; j < Linalg::K_rigid.size()-1; ++j)
    {
        for (int i = j+1; i < Linalg::K_rigid.size(); ++i)
        {
            if (Linalg::K_rigid[i][j]!=0)
            {
                temp = Linalg::K_rigid[i][j]/Linalg::K_rigid[j][j];
                for (int k = j+1;k<Linalg::K_rigid.size(); ++k)
                {
                    Linalg::K_rigid[i][k] = Linalg::K_rigid[i][k]-temp*Linalg::K_rigid[j][k];
                }
                Linalg::K_rigid[i][j] = temp; 
            }  
        }
    }
   
    for (int i = 1; i < Linalg::K_rigid.size(); ++i)
    {   
        temp = 0;
        for (int j = 0; j < i; ++j)
        {
            temp+= Linalg::K_rigid[i][j]*U[j];
        }  
        U[i] = (U[i] - temp);
    }

    for (int i = Linalg::K_rigid.size()-1; i > -1; --i)
    {   
        temp = 0;
        for (int j = i+1; j < Linalg::K_rigid.size(); ++j)
        {
            temp+= Linalg::K_rigid[i][j]*U[j];
        }  
        U[i] = (U[i] - temp)/Linalg::K_rigid[i][i];
    }

    for (int i = 0; i < obj.node.size(); ++i)
    {   
        obj.node[i].ux = U[2*i];
        obj.node[i].uy = U[2*i+1];
    } 
};