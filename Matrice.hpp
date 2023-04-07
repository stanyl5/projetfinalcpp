#include <iostream>
#include <cmath>
#include<fstream>
#include<vector>
#include<string>
#include<sstream>
#include <array>
#include<string.h>

#include "Point.hpp"


struct Matrice
{
    int ligne;
    int colonne;
    std::vector<std::vector<float>> mat;

    Matrice(int lig, int col);
    void AfficheMatrice();
    void dessiner_ligne(Point point);


};