//+
Point(1) = {0, 0, 0, 1.0};
//+
Point(2) = {0, 1, 0, 1.0};
//+
Point(3) = {1, 1, 0, 1.0};
//+
Point(4) = {1, 0, 0, 1.0};
//+
//+
Point(5) = {0, 0.3, 0, 1.0};
Point(6) = {0.3, 0., 0, 1.0};


//+
Circle(1) = {5, 1, 6};
//+
Line(2) = {5, 2};
//+
Line(3) = {3, 4};
//+
Line(4) = {6, 4};
//+
Line(5) = {2, 3};
//+
Curve Loop(1) = {2, 5, 3, -4, -1};
//+

Plane Surface(1) = {1};
//+
Transfinite Curve {5, 3, 2,  4} = 10 Using Progression 1;
Transfinite Curve {1} = 8 Using Progression 1;

Transfinite Surface {1};
//+
Recombine Surface {1};
