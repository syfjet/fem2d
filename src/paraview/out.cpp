#include "out.h"

Out::Out(){};
Out::~Out(){};       

 
void Out::out_paraview(Object &obj)
{

        ofstream out;
        out.open("results/results.vtu");
        if (out.is_open())
        {
            out << "<VTKFile type='UnstructuredGrid' version='0.1' byte_order='BigEndian'>"<<"\n";
            out << "<UnstructuredGrid>"<<"\n";
            out << "<Piece NumberOfPoints='"<<obj.node.size()<<"' NumberOfCells='"<<obj.cell.size()<<"'>"<<"\n";
            out << "<Points>"<<"\n";
            out << "<DataArray type='Float64' NumberOfComponents='3' Format='ascii'>"<<"\n";
 
            for (int i = 0;i<obj.node.size();++i)
            {
                out << obj.node[i].coordinate[0]<< " " <<obj.node[i].coordinate[1]<< " " <<obj.node[i].coordinate[2]<<"\n";
            }
            out << "</DataArray>"<<"\n";
            out << "</Points>"<<"\n";


            out << "<PointData Vectors='Velocity'>"<<"\n";
            out << "<DataArray type='Float64' Name='Ux' Format='ascii'>"<<"\n";
 
            for (int i = 0;i<obj.node.size();++i)
            {
                out << obj.node[i].ux<<"\n";
            }
            out << "</DataArray>"<<"\n";

            out << "<DataArray type='Float64' Name='Uy' Format='ascii'>"<<"\n";
 
            for (int i = 0;i<obj.node.size();++i)
            {
                out << obj.node[i].uy<<"\n";
            }
            out << "</DataArray>"<<"\n";


            out << "<DataArray type='Float64' Name='U' Format='ascii'>"<<"\n";
 
            for (int i = 0;i<obj.node.size();++i)
            {
                out << sqrt(pow(obj.node[i].ux,2)+pow(obj.node[i].uy,2))<<"\n";
            }
            out << "</DataArray>"<<"\n";
            out << "</PointData>"<<"\n";
 


            out << "<CellData Scalars='scalars'>"<<"\n";

            out << "<DataArray type='Float64' Name='Parts' format='ascii'>"<<"\n";
            for (int i = 0;i<obj.cell.size();++i)
            {
             out << obj.cell[i].part<<"\n";
            }    
            out << "</DataArray>"<<"\n";


            out << "<DataArray type='Float64' Name='e_x' format='ascii'>"<<"\n";
            for (int i = 0;i<obj.cell.size();++i)
            {
                out << obj.cell[i].epsilon[0]<<"\n";
            }   
            out << "</DataArray>"<<"\n";

            out << "<DataArray type='Float64' Name='e_y' format='ascii'>"<<"\n";
            for (int i = 0;i<obj.cell.size();++i)
            {
                out << obj.cell[i].epsilon[1]<<"\n";
            }   
            out << "</DataArray>"<<"\n";

            out << "<DataArray type='Float64' Name='gamma_xy' format='ascii'>"<<"\n";
            for (int i = 0;i<obj.cell.size();++i)
            {
                out << obj.cell[i].epsilon[2]<<"\n";
            }   
            out << "</DataArray>"<<"\n";


            out << "<DataArray type='Float64' Name='stress_x' format='ascii'>"<<"\n";
            for (int i = 0;i<obj.cell.size();++i)
            {
                out << obj.cell[i].stress[0]<<"\n";
            }   
            out << "</DataArray>"<<"\n";

            out << "<DataArray type='Float64' Name='stress_y' format='ascii'>"<<"\n";
            for (int i = 0;i<obj.cell.size();++i)
            {
                out << obj.cell[i].stress[1]<<"\n";
            }   
            out << "</DataArray>"<<"\n";

            out << "<DataArray type='Float64' Name='tau_xy' format='ascii'>"<<"\n";
            for (int i = 0;i<obj.cell.size();++i)
            {
                out << obj.cell[i].stress[2]<<"\n";
            }   
            out << "</DataArray>"<<"\n";

            out << "<DataArray type='Float64' Name='stress' format='ascii'>"<<"\n";
            for (int i = 0;i<obj.cell.size();++i)
            {
                out << obj.cell[i].full_stress<<"\n";
            }   
            out << "</DataArray>"<<"\n";
 

            out << "<DataArray type='Float64' Name='area' format='ascii'>"<<"\n";
            for (int i = 0;i<obj.cell.size();++i)
            {
                out << obj.cell[i].area<<"\n";
            }   
            out << "</DataArray>"<<"\n";

             
            out << "</CellData>"<<"\n"; 

            out << "<Cells>"<<"\n";     
            out << "<DataArray type='Int32' Name='connectivity' format='ascii'>"<<"\n";     
            for (int i = 0;i<obj.cell.size();++i)
            {
                out << obj.cell[i].index_node[0]<< " "<< obj.cell[i].index_node[1]<< " " << obj.cell[i].index_node[2] <<"\n";
            }   
            out << "</DataArray>"<<"\n";
            out << "<DataArray type='Int32' Name='offsets' format='ascii'>"<<"\n";
            for (int i = 0;i<obj.cell.size();++i)
            {
                out << 3*(i+1) <<"\n";
            }   
            out << "</DataArray>"<<"\n";
            out << "<DataArray type='Int32' Name='types' format='ascii'>"<<"\n";
            for (int i = 0;i<obj.cell.size();++i)
            {
                out << 5 <<"\n";
            }   
            out << "</DataArray>"<<"\n";    
            out << "</Cells>"<<"\n";
            out << "</Piece>"<<"\n";
            out << "</UnstructuredGrid>"<<"\n"; 
            out << "</VTKFile>"<<"\n";                  
        }
        out.close();
};
