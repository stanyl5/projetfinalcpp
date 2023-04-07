#include <iostream>
#include <cmath>
#include<fstream>
#include<vector>
#include<string>
#include<sstream>
#include <array>

#include "Point.hpp"

struct Image
{
    std ::string qualite;
    int ligne;
    int colonne;
    int valmax;
    std :: vector<std :: vector< std:: array<int,3>>> image;
    
    void afficheImage();
    void dessiner_ligne(Point point);
    
};