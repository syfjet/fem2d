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
		double fx = 0;
		double fy = 0;
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
		double area;
	protected:
	private:					
	};  

	class Cell
	{
	public:
		int part = 0;
		array<int,3> index_node;	
		array<int,3> connection = {-1,-1,-1};

		double E = 0;
		double nu = 0;
		double volume = 0;
		array<array<double,6>,3> B_matrix  = {{{0}}};  
		array<double,3> epsilon = {0,0,0};
		array<double,3> stress = {0,0,0};
		double full_stress = 0;
	};
	vector<Node> node;			
	vector<Segment> segment;	
	vector<Cell> cell;

};


 