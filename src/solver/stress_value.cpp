#include "stress_value.h"

Stress_value::Stress_value(){};
Stress_value::~Stress_value(){};         

void Stress_value::define_stress_values(Object &obj)
{
    for (int i = 0; i < obj.cell.size(); ++i)
    {
        Stress_value::epsilon(i,obj);
        Stress_value::stress(i,obj);
    }
}

void Stress_value::epsilon(int i,Object &obj)
{

    array<int,3> ii;
    array<double,6> U;

    ii[0] = obj.cell[i].index_node[0];
    ii[1] = obj.cell[i].index_node[1];
    ii[2] = obj.cell[i].index_node[2];

    U[0] = obj.node[ii[0]].ux;
    U[1] = obj.node[ii[0]].uy;
    U[2] = obj.node[ii[1]].ux;
    U[3] = obj.node[ii[1]].uy;
    U[4] = obj.node[ii[2]].ux;
    U[5] = obj.node[ii[2]].uy;

    for (int j = 0; j < U.size(); ++j)
    {
        obj.cell[i].epsilon[0] += obj.cell[i].B_matrix[0][j]*U[j];
        obj.cell[i].epsilon[1] += obj.cell[i].B_matrix[1][j]*U[j];
        obj.cell[i].epsilon[2] += obj.cell[i].B_matrix[2][j]*U[j];
    }
}

void Stress_value::stress(int i,Object &obj)
{
    array<double,3> U;
    U[0] = obj.cell[i].epsilon[0];
    U[1] = obj.cell[i].epsilon[1];
    U[2] = obj.cell[i].epsilon[2];
   
    for (int j = 0; j < obj.cell[i].stress.size(); ++j)
    {
        for (int k = 0; k < U.size(); ++k)
        {
           
           obj.cell[i].stress[j] += Shift::hooke_matrix[j][k]*U[k];
        }
    }

obj.cell[i].full_stress = sqrt(obj.cell[i].stress[0]*obj.cell[i].stress[0]-obj.cell[i].stress[0]*obj.cell[i].stress[1]+obj.cell[i].stress[1]*obj.cell[i].stress[1]+3.*obj.cell[i].stress[2]*obj.cell[i].stress[2]);  
};