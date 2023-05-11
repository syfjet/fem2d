#pragma once
#include <iostream>
#include <vector>
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

 
 
