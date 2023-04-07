#include <iostream>
#include <cmath>
#include<fstream>
#include<vector>
#include<string>
#include<sstream>
#include <string.h>

#include "Image.hpp"
#include <fstream>

using namespace std;



Image lirefichier ()
{
    std :: ifstream monfichier ("m1projetcpp2.ppm"); // Ouverture du fichier
    Image image;
    if (monfichier) // On s'assure que le fichier est bien ouvert
    {
        
        int compteur=0; // Le compteur ne tient pas compte des commentaires, et permet d'évoluer dans le code au rythme prédéfini.
        
        std :: string ligne; 
        while(getline(monfichier, ligne)) 
            {
                if (ligne[0] != '#')  // On ignore les commentaire du fichier ppm
                {
                    if (compteur == 0)
                    {
                        // Récupération du numéro de variante
                        
                        image.qualite = ligne; 

                    }
                    else
                    {
                        if (compteur == 1)
                        {           
                            // Récupération de format de l'image :
                            // Resolution[0] = largeur,
                            // Resolution[1] = hauteur  

                            std :: array<int,2> resolution;
                            std::string parseNum;
                            std::stringstream streamLigne(ligne);
                            int res=0;
                            while(std::getline(streamLigne,parseNum,' '))
                            {
                                resolution[res] = std::stoi(parseNum);
                                res++;
                            } 
                            image.ligne = resolution[0];
                            image.colonne = resolution[1];
                            
                        }
                    else
                    {
                        if (compteur==2)
                        {
                            // Récupération de la valeur maximale
                            image.valmax = std :: stoi(ligne);
                        }
                        else  // Si le compteur vaut 3
                        {  
                            // On initialise une matrice 3D avec la valeur 0
                            std :: array<int,3>  vecteur;
                            std :: vector<std :: array<int,3> > intermediaire (image.colonne, vecteur)  ;
                            image.image = std :: vector<std :: vector< std:: array<int,3>>>  (image.ligne,intermediaire) ;
                            
                            // On boucle sur la largeur de l'image, sa hauteur, et pour chaque composante de la couleur    
                            for (int i = 0;i<image.ligne;i++)
                            { 
                                for (int j =0; j< image.colonne; j++)
                                {
                                    for (int k=0; k<3;k++) // Boucle sur la couleur
                                    {
                                        // On affecte la valeur récupérée dans l'image
                                        image.image[i][j][k] = stoi (ligne);  // Cette ligne est en premier, car la première valeur a été récupérée dans la condition du while
                                        getline(monfichier,ligne); 
                                    }
                                }

                            }
                            return image; // On retourne l'image 
                        }
                    }
                }
                compteur ++;

            }

        }
    }
    std :: cout << "Attention, il y a eu une erreur." ;
    return image ; 
}


void ecrire_fichier(Image A){
    
    std::ofstream fichier("image.ppm", std::ios::binary);

    // En-tête de l'image
    fichier << "P3\n# resolution\n";
    fichier << A.ligne;
    fichier << " ";
    fichier << A.colonne;
    fichier << "\n# avec 255 comme val max\n255\n# debut de l image\n";
    
    // Pixels de l'image
    
    for (int i = 0; i < A.ligne; i++){
        for (int j = 0; j < A.colonne; j++){
            for (int k = 0; k < 3; k++) {
                fichier << A.image[i][j][k];
                fichier << "\n";
                }
            }
            
        }

        fichier.close();
}
    

    



struct Matrice
{
  int ligne;
  int colonne;
  std::vector<std::vector<int>> mat;

  Matrice(int lig = 0, int col = 0)
  {
    ligne = lig;
    colonne = col;
    mat = std::vector<std::vector<int>>(ligne, std::vector<int>(colonne, 255));
  }

  void AfficheMatrice()
  {
    for (int x = 0; x < ligne; ++x)
    {
      for (int y = 0; y < colonne; ++y)
      {
        std::cout <<mat[x][y]<< " ";
      }

      std::cout << std::endl;
    }
  }


};

double Norme(double x, double y) {
    return sqrt(abs(x- y));
}

Matrice dessiner_ligne(Matrice mat, float m, float p)
// m est le coefficient directeur de la droite 
// p est l'ordonée à l'origine
{
    int lignes = mat.ligne;
    int colonnes = mat.colonne;
    if (abs(m)<=1){
            for(int j = 0; j < colonnes; j++) {
                if (((int)(m*j+p)<=lignes-1)&&((int)(m*j+p)>=0)){ // pour eviter que la droite "depasse" l'image
<<<<<<< HEAD
                    //std::cout<< (int)(m*j+p) << " "<< m*j+p<< " " << Norme((int)(m*j+p),m*j+p)*255<< " ";
                    //std::cout << int(m*j+p)/(m*j+p)<< " "; 
                    
                    mat.mat[(int)(m*j+p)][j] = Norme((int)(m*j+p),m*j+p)*255;                     
                }
                if (((int)(m*j+p)+1<=lignes-1)&&((int)(m*j+p)+1>=0)){ // pour eviter que la droite "depasse" l'image
                    mat.mat[(int)(m*j+p)+1][j] = (1-Norme((int)(m*j+p),m*j+p))*255;      // Colorisation du pixel en dessous         
=======
                                       
                    mat.mat[(int)(m*j+p)][j] = 255-(1-Norme((int)(m*j+p),m*j+p))*255;                    
                }
                if (((int)(m*j+p)+1<=lignes-1)&&((int)(m*j+p)+1>=0)){ // pour eviter que la droite "depasse" l'image
                    mat.mat[(int)(m*j+p)+1][j] = 255-Norme((int)(m*j+p),m*j+p)*255;                    
>>>>>>> 2633d6abca803f04e36c5be36ce22b1a64b92de9
                }
            }
    }
    if (abs(m)>1){
        for(int i = 0; i < lignes; i++) {
            if (((int)((i-p)/m)<=colonnes-1)&&((int)((i-p)/m)>=0)){ // pour eviter que la droite "depasse" l'image
                //std::cout<< (int)((i-p)/m) << " "<< ((i-p)/m)<< " " << Norme((int)((i-p)/m),((i-p)/m))*255<< " "<< (1-Norme((int)((i-p)/m),((i-p)/m)))*255<< " ";

                mat.mat[i][(int)((i-p)/m)] = 255-(1-Norme((int)((i-p)/m),((i-p)/m)))*255;
            }
            if (((int)((i-p)/m)+1<=colonnes-1)&&((int)((i-p)/m)+1>=0)){ // pour eviter que la droite "depasse" l'image
                    mat.mat[i][(int)((i-p)/m)+1] = 255-Norme((int)((i-p)/m),((i-p)/m))*255;                    
                }
        }
    }
    return mat;
}

int main ()
{
    Image A;
    A = lirefichier();
    //A.afficheImage();

    ecrire_fichier(A);
    Matrice mat2(A.ligne, A.colonne);
    mat2 = dessiner_ligne(mat2, 1.8, 3); 
    std::cout<<"\n";
    std::cout<<"\n";
    mat2.AfficheMatrice();

    
    int lignes = mat2.ligne;
    int colonnes = mat2.colonne;
        for(int i = 0; i < lignes; i++){
            for(int j = 0; j < colonnes; j++){
                if (mat2.mat[i][j]!=255){
                    A.image[i][j][0]=mat2.mat[i][j];
                    A.image[i][j][1]=mat2.mat[i][j];
                    A.image[i][j][2]=mat2.mat[i][j];
                }
            }
        }

    ecrire_fichier(A);
    A.afficheImage();
    return 0;
}
