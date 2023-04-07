#include <iostream>
#include <cmath>
#include<fstream>
#include<vector>
#include<string>
#include<sstream>

#include "Image.hpp"
#include "Matrice.hpp"

#include "Point.hpp"

Point Houghnormale(std ::vector<Point> vecpoints)
{
    Matrice buffer(30,30);
    for (unsigned int i= 0; i< vecpoints.size(); i++)
    {
        for (unsigned int j=0; j<30; j++)
        {
            //std :: cout << "condition i = " <<i << " : " << vecpoints[i].x * j + vecpoints[i].y <<  std :: endl ;
                
            if (vecpoints[i].x * j + vecpoints[i].y>0 && vecpoints[i].x * j + vecpoints[i].y<30)
            {
                buffer.mat[j][vecpoints[i].x * j + vecpoints[i].y] ++;
            }
        }
    }
    float max =-10.00;
    Point coormax{0,0};
    for (int i=0 ; i<30; i++)
    {
        for (int j=0;j<30;j++)
        {
            std :: cout << "coordonnées : ("<<i << ","<<j<<") : " << buffer.mat[i][j]<< std :: endl ;
                
            if (max<buffer.mat[i][j])
            {
                max = buffer.mat[i][j];
                coormax.x = i;
                coormax.y = j;
            }
        }
    }
    return coormax;
}

int main ()
{
    Point P {1.0,2.0};
    Point Q {2.0,3.0};
    Point R {4.0,5.0};
    std :: vector<Point> v;
    for (int i = 0; i<20; i++)
    { 
        Point S {i, i%3} ;
        v.push_back (S);
    }
    /* for (int i = 0; i<20; i++)
    { 
        v[i].AffichePoint();
    } */
    v.push_back (P);
    v.push_back (Q);
    v.push_back (R);
    Point S= Houghnormale(v);
    S.AffichePoint();
}