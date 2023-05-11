#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "../object.h"
#include "shift.h"
#include "stress_value.h"
#include "linalg.h"
#include "../paraview/out.h"
using namespace std; 

class Solver: virtual Shift, virtual Linalg, Stress_value, Out
{	
public:
	Solver();
	~Solver();
	void FEM_solver(Object &obj);
protected:
private:

};
