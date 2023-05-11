#include <iostream>
#include "numerical.h"
#include "object.h"
#include "reader/read_input_file.h"
#include "solver/solver.h"
int main()
{
	std::string name_file;

	Object obj;
	Numerical numer;

	Read_input_file *read_file = new Read_input_file;
	cin >> name_file;
 	read_file -> read(name_file,obj,numer); 
 	delete read_file;
 	Solver *solver = new Solver;
 	solver -> FEM_solver(obj);
 	delete solver;
	return 0;		
} 
