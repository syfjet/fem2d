#pragma once
#include <iostream>
#include <vector>
#include <array>
using namespace std; 

class Object{
public:
	class Node
	{
	public:
		int part = 0;
		array<double,3> coordinate = {0,0,0};	
		vector<int> connection;	
		double px = 0;
		double py = 0;
		double ux = 0;
		double uy = 0;		
	protected:
	private:				
	}; 

	class Segment
	{
	public:
		int cell = 0;
		int part = 0;
		array<int,2> index_node;	
		int type = 0;
		double lenght;
	protected:
	private:					
	};  

	class Cell
	{
	public:
		int part = 0;
		array<int,4> index_node;	
		array<int,4> connection = {-1,-1,-1,-1};

		double E = 0;
		double nu = 0;
		double area = 0;
		array<array<double,8>,3> B_matrix;  
		array<double,3> epsilon = {0,0,0};
		array<double,3> stress = {0,0,0};
		double full_stress = 0;
	};
	vector<Node> node;			
	vector<Segment> segment;	
	vector<Cell> cell;

};


 