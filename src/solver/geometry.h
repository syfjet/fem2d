#pragma once
#include <iostream>
#include <cmath>
#include <array>
#include "../object.h"

using namespace std; 
class Geometry
{	
	public:
		Geometry();
		~Geometry();
	protected:
		void geometry_area(int i, Object &obj);
		void geometry_b_matrix(int i, Object &obj);
	private:
		array<double,4> B = {0,0,0,0};
    	array<double,4> C = {0,0,0,0};	
}; 

 
 
