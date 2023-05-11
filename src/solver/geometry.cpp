#include "geometry.h"

Geometry::Geometry(){};
Geometry::~Geometry(){};         

void Geometry::geometry_area(int i, Object &obj)
{

    Geometry::B[0] = obj.node[obj.cell[i].index_node[1]].coordinate[1]-obj.node[obj.cell[i].index_node[2]].coordinate[1];
    Geometry::B[1] = obj.node[obj.cell[i].index_node[2]].coordinate[1]-obj.node[obj.cell[i].index_node[0]].coordinate[1];
    Geometry::B[2] = obj.node[obj.cell[i].index_node[0]].coordinate[1]-obj.node[obj.cell[i].index_node[1]].coordinate[1];

    Geometry::C[0] = obj.node[obj.cell[i].index_node[2]].coordinate[0]-obj.node[obj.cell[i].index_node[1]].coordinate[0];
    Geometry::C[1] = obj.node[obj.cell[i].index_node[0]].coordinate[0]-obj.node[obj.cell[i].index_node[2]].coordinate[0];
    Geometry::C[2] = obj.node[obj.cell[i].index_node[1]].coordinate[0]-obj.node[obj.cell[i].index_node[0]].coordinate[0]; 

    obj.cell[i].area = 0.5*abs(Geometry::C[2]*Geometry::B[1]-Geometry::B[2]*Geometry::C[1]);
}

void Geometry::geometry_b_matrix(int i, Object &obj)
{
    obj.cell[i].B_matrix[0][0] = 0.5*Geometry::B[0]/obj.cell[i].area;
    obj.cell[i].B_matrix[0][1] = 0;
    obj.cell[i].B_matrix[0][2] = 0.5*Geometry::B[1]/obj.cell[i].area;
    obj.cell[i].B_matrix[0][3] = 0;
    obj.cell[i].B_matrix[0][4] = 0.5*Geometry::B[2]/obj.cell[i].area;
    obj.cell[i].B_matrix[0][5] = 0;
    obj.cell[i].B_matrix[1][0] = 0;
    obj.cell[i].B_matrix[1][1] = 0.5*Geometry::C[0]/obj.cell[i].area;
    obj.cell[i].B_matrix[1][2] = 0;
    obj.cell[i].B_matrix[1][3] = 0.5*Geometry::C[1]/obj.cell[i].area;
    obj.cell[i].B_matrix[1][4] = 0;
    obj.cell[i].B_matrix[1][5] = 0.5*Geometry::C[2]/obj.cell[i].area;
    obj.cell[i].B_matrix[2][0] = 0.5*Geometry::C[0]/obj.cell[i].area;
    obj.cell[i].B_matrix[2][1] = 0.5*Geometry::B[0]/obj.cell[i].area;
    obj.cell[i].B_matrix[2][2] = 0.5*Geometry::C[1]/obj.cell[i].area;
    obj.cell[i].B_matrix[2][3] = 0.5*Geometry::B[1]/obj.cell[i].area;
    obj.cell[i].B_matrix[2][4] = 0.5*Geometry::C[2]/obj.cell[i].area;
    obj.cell[i].B_matrix[2][5] = 0.5*Geometry::B[2]/obj.cell[i].area;

};