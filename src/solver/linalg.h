#pragma once
#include <iostream>
#include <vector>
#include <cmath>
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
		class K_rigid_sparse
		{	public:
			vector<int> index;
			vector<double> element; 
		};
		vector<K_rigid_sparse> k_rigid;
	private:
		void update_K_rigid(vector<double> &U);
}; 

 
 
