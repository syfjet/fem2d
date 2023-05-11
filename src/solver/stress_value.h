#pragma once
#include <iostream>
#include <vector>
#include <array>
#include "shift.h"
#include "../object.h"

using namespace std; 
class Stress_value: virtual Shift
{	
	public:
		Stress_value();
		~Stress_value();
	protected:
		void define_stress_values(Object &obj);
	private:
		void epsilon(int i,Object &obj);
		void stress(int i,Object &obj);
}; 

 
 
