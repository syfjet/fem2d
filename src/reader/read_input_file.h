#pragma once
#include <iostream>
#include <regex>
#include <fstream>
#include <cmath>
#include "../object.h"
#include "../numerical.h"
#include "construction_mesh.h" 

using namespace std; 

class Read_input_file: public Numerical, protected Construction_mesh
{	
public:
	Read_input_file();
	~Read_input_file();
	string mesh_file;		
	void read(string input_file,Object &obj, Numerical &numer);

protected:

private:
	void read_mesh(Object &obj);
	void boundary_init(Object &obj,vector <int>& number,vector <string>& type_boundary);
	void cell_init(Object &obj,vector <int>& parts,vector <double>& E, vector <double>& nu);
	void error(string text, string text_);

};
