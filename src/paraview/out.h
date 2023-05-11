#pragma once
#include <iostream>
#include <fstream>
#include <cmath>
#include "../object.h"
using namespace std; 

class Out
{	
public:
	Out();
	~Out();
protected:
	void out_paraview(Object &obj);
private:
};
