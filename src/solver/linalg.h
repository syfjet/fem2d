#pragma once
#include <iostream>
#include <vector>
#include "boundary.h"
#include "../object.h"

using namespace std; 
class Linalg: Boundary
{	
	public:
		Linalg();
		~Linalg();
	protected:
		void solve_linear_system(Object &obj);
		vector<vector<double>> K_rigid;
	private:
		void update_K_rigid(vector<double> &U);
}; 

 
 
