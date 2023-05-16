#include "linalg.h"

Linalg::Linalg(){};
Linalg::~Linalg(){};         

void Linalg::update_K_rigid(vector<double> &U)
{
    for (int i = 0; i < Linalg::k_rigid.size(); ++i)
    {   
        if (U[i] == 0)
        {
            for (int j = 0; j < Linalg::k_rigid[i].index.size(); ++j)
            {              
                Linalg::k_rigid[i].element[j] = 0;
                if ((Linalg::k_rigid[i].index[j] == i) && (Linalg::k_rigid[i].element[j] == 0))
                {
                    Linalg::k_rigid[i].element[j] = 1;
                }                   
            }

            for (int k = 0; k < Linalg::k_rigid.size(); ++k)
            {   
                for (int j = 0; j < Linalg::k_rigid[k].index.size(); ++j)
                {              
                    if (Linalg::k_rigid[k].index[j] == i)
                    {
                        Linalg::k_rigid[k].element[j] = 0;   
                    }  
                }
            }
        }
    }

}

void Linalg::solve_linear_system(Object &obj)
{

    vector<double> U(2*obj.node.size(),1);
    vector<double> x(2*obj.node.size(),0); 
    vector<double> r(2*obj.node.size(),0); 
    vector<double> As(2*obj.node.size(),0); 
    vector<double> s(2*obj.node.size(),0); 
 
    Boundary::boundary_set(obj,U);
    Linalg::update_K_rigid(U);
    double tol, temp,rr,rAs,sAs,alpha,beta;

    tol = 1e-3;

    for (int i = 0; i < obj.node.size(); ++i)
    {  
       U[2*i] = obj.node[i].px; 
       U[2*i+1] = obj.node[i].py;     
    }

    for (int i = 0; i< Linalg::k_rigid.size(); ++i)
    {   
        r[i] = -U[i];
        s[i] = r[i];
    }

    for (int k = 0; k < 10000; ++k)
    {   
        rr = 0;
        sAs = 0;
        for (int i = 0; i < Linalg::k_rigid.size(); ++i)
        {   
            temp = 0;
            for (int j = 0; j < Linalg::k_rigid[i].index.size(); ++j)
            {
                temp += Linalg::k_rigid[i].element[j]*s[Linalg::k_rigid[i].index[j]];     
            }
            As[i] = temp;
            rr += r[i]*r[i];
            sAs += s[i]*As[i];            
        }

        alpha = rr/sAs;

        for (int i = 0; i < Linalg::k_rigid.size(); ++i)
        {
            x[i] = x[i]-alpha*s[i];   
        }

        rr = 0;
        beta = 0;
        rAs = 0;
        sAs = 0;

        for (int i = 0; i< Linalg::k_rigid.size(); ++i)
        {
            temp = 0;
            for (int j = 0; j < Linalg::k_rigid[i].index.size(); ++j)
            {
                temp+=Linalg::k_rigid[i].element[j]*x[Linalg::k_rigid[i].index[j]];    
            }
            r[i] = temp-U[i];
            rr += r[i]*r[i];  
            rAs += r[i]*As[i];
            sAs += s[i]*As[i];
        }

        if (rr < tol)
        {
            break;
        }
        else
        {
            beta = -rAs/sAs;
            for (int i = 0; i< Linalg::k_rigid.size(); ++i)
            {  
                s[i] = r[i]+beta*s[i];  
            }     
        }

        if (k > 9999)
        {
            cout<<"Not stable solution!"<<endl;
        }
        cout<<"iter step = "<<k<<endl;
    }

    for (int i = 0; i < obj.node.size(); ++i)
    {   
        obj.node[i].ux = x[2*i];
        obj.node[i].uy = x[2*i+1];
    } 

};
////////////////////////////
//Exact Linear solver Gauss
////////////////////////////

    // double divider;
    // double factor;
    // for (int i = 0; i < Linalg::k_rigid.size(); ++i)
    // {     
        

    //    // if (Linalg::k_rigid[i].element[0]!=0)
    //     //{

    //         // STROK_f.clear();
    //         // STROK_f.resize(Linalg::k_rigid.size(),0);           
    //         for (int l = 0; l < Linalg::k_rigid.size(); ++l)
    //         {
    //            STROK_f[l] = 0; 
    //         }

            
    //         for (int l = 0; l < Linalg::k_rigid[i].index.size(); ++l)
    //         {
    //            STROK_f[Linalg::k_rigid[i].index[l]] = Linalg::k_rigid[i].element[l]; 
    //         }

    //         divider = STROK_f[i];

    //         for (int j = 0; j < Linalg::k_rigid.size(); ++j)
    //         {
    //            STROK_f[j] /= divider; 
    //         }
    //         U[i] /= divider;
    //         for (int j = i+1; j < Linalg::k_rigid.size(); ++j)
    //         {   
 
    //            for (int l = 0; l < Linalg::k_rigid.size(); ++l)
    //             {
    //                STROK_s[l] = 0; 
    //             }
    //             for (int l = 0; l < Linalg::k_rigid[j].index.size(); ++l)
    //             {
    //                STROK_s[Linalg::k_rigid[j].index[l]] = Linalg::k_rigid[j].element[l]; 
    //             }               
    //             if (STROK_s[j]!=0)
    //             {

  

    //                 factor = STROK_s[i];
    //                 for (int k = i; k < Linalg::k_rigid.size(); ++k)
    //                 {   
    //                     if (STROK_f[k]!=0)
    //                     {
    //                         STROK_s[k]-= factor*STROK_f[k];        
    //                     }
                        
    //                 }
    //                 STROK_s[i] = 0;
    //                 U[j] -= factor*U[i]; 
    //                 Linalg::k_rigid[j].index.clear();
    //                 Linalg::k_rigid[j].element.clear();
    //                 for (int l = 0; l < Linalg::k_rigid.size(); ++l)
    //                 {
    //                     if (STROK_s[l]!=0)
    //                     {
    //                         Linalg::k_rigid[j].index.push_back(l);
    //                         Linalg::k_rigid[j].element.push_back(STROK_s[l]);
    //                     } 
    //                 }
    //             }            

    //         } 

    //         Linalg::k_rigid[i].index.clear();
    //         Linalg::k_rigid[i].element.clear();
    //         for (int l = 0; l < Linalg::k_rigid.size(); ++l)
    //         {
    //             if (STROK_f[l]!=0)
    //             {
    //                 Linalg::k_rigid[i].index.push_back(l);
    //                 Linalg::k_rigid[i].element.push_back(STROK_f[l]);
    //             } 
    //         }  
    //    // }

    // }

    // double temp;
    // for (int i = Linalg::k_rigid.size()-1; i > -1; --i)
    // {   

    //     temp = 0;

    //     for (int l = 1; l < Linalg::k_rigid[i].index.size(); ++l)
    //     {   

    //         temp += Linalg::k_rigid[i].element[l]*U[Linalg::k_rigid[i].index[l]];
    //     }
 
    //     U[i] = (U[i] - temp);
    // }

////////////////////////////
//Exact Linear solver Gauss
////////////////////////////
