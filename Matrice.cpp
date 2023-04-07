#include"Matrice.hpp"


 
Matrice :: Matrice(int lig, int col)
{
    ligne = lig;
    colonne = col;
    mat = std::vector<std::vector<float>> (ligne, std::vector<float>(colonne, 0.0));
}

void Matrice :: AfficheMatrice()
{
    std::string s = std::to_string(mat[1][1]);
    std::cout << s.size() << std::endl;
    for (int x = 0; x < ligne; ++x)
    {
      for (int y = 0; y < colonne; ++y)
      {
        std::cout<<(char)mat[x][y];
        std::cout << mat[x][y]<< "   " ;
      }

      std::cout << std::endl;
    }
}



