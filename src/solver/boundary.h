#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include "../object.h"

using namespace std; 
class Boundary
{	
	public:
		Boundary();
		~Boundary();
	protected:
		void boundary_set(Object &obj,vector<double> &U);
	private:
	
}; 

 
 
