#include "solver.h"

Solver::Solver(){};
Solver::~Solver(){};         

void Solver::FEM_solver(Object &obj)
{

    Shift::define_matrix(obj);    
    Linalg::solve_linear_system(obj);    
    Stress_value::define_stress_values(obj);
    Out::out_paraview(obj);
};
