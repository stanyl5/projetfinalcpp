#include <iostream>
#include <cmath>
#include<fstream>
#include<vector>
#include<string>
#include<sstream>

#include "Image.hpp"
#include "Matrice.hpp"

#include "Point.hpp"





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


std::vector<Point> donnerpoints (Image image)
{
    std::vector<Point> pntdroites;

    for (int i=0; i<image.ligne ; i++) 
    {
        for (int j=0;j<image.colonne; j++) 
        {
             if (((image.image[i][j][0]==image.image[i][j][1])&&(image.image[i][j][1]==image.image[i][j][2]))&&(image.image[i][j][0]==0|| image.image[i][j][0]==255))
            {
                // On se trouve dans le fond
            }
            else
            {
                Point P{-i,j};
                pntdroites.push_back(P);
                
            }
                
        }
    }
    return pntdroites;
}


std ::vector<Point> Houghnormale(std ::vector<Point> vecpoints)
{
    int N = 30;
    Matrice buffer(N,N);
    for (unsigned int i= 0; i< vecpoints.size(); i++) // On boucle sur tous les points différents du fond, ceux qu'on nous a transmis
    {
        for ( int j=0; j<N; j++) // On boucle sur une fenetre près établie
        {
                
            if (vecpoints[i].x * j + vecpoints[i].y>0 && vecpoints[i].x * j + vecpoints[i].y<N) // on trace la droite et on s'intéresse aux points dans la fenetre
            {
                buffer.mat[j][vecpoints[i].x * j + vecpoints[i].y] ++; // On incrémente chaque point sur une droite
            }
        }
    }
    float min = 0;
    std ::vector<Point> vec;
    Point coormax;
    for (int i=0 ; i<N; i++)
    {
        for (int j=0;j<N;j++)
        {
            //std :: cout << "coordonnées : ("<<i << ","<<j<<") : " << buffer.mat[i][j]<< std :: endl ;
                
            if (min<buffer.mat[i][j])
            {
                
                coormax.x = i;
                coormax.y = j;
                vec.push_back(coormax);
            }
        }
    }
    return vec;
}

void ecrire_fichier(Image A){
    
    std::ofstream fichier("image.ppm", std::ios::binary);

    // En-tête de l'image
    fichier << A.qualite;
    fichier << "\n# resolution\n";
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

int main ()
{
    Image A;    
    A = lirefichier();
    std :: vector<Point> vec;
    vec = donnerpoints(A);
    
    std :: vector<Point> res;
    res = Houghnormale(vec);


    

    for (int i=0 ; i<res.size(); i++)//res.size()
    {   
        std::cout<<"res ";
        res[i].AffichePoint();
        std::vector<Point> vec_doublons;
        if (res[i].x == 0)
        {
            do 
            {
                std::cout<<"cas1 ";
                res[i].AffichePoint();
                vec_doublons.push_back(res[i]);
                i ++;

            }while (res[i].y+1 == res[i+1].y);
        }
        else
        {
            do 
            {
                std::cout<<"cas2 ";
                res[i].AffichePoint();
                vec_doublons.push_back(res[i]);
                i ++;

            }while (res[i].y+1 == res[i+1].y || res[i].x+1 == res[i+1].x);
        }

        float somme_x = 0.0;
        float somme_y = 0.0;
        for (int j = 0 ; j<vec_doublons.size(); j++){
            somme_x = somme_x + vec_doublons[j].x;
            somme_y = somme_y + vec_doublons[j].y;
        }
        
        float point_x = somme_x / vec_doublons.size();
        float point_y = somme_y / vec_doublons.size();

        Point point;
        point.x = point_x;
        point.y = point_y;

        std::cout<<"Point final " ;
        point.AffichePoint();
        //std::cout<<res[i].x;
        A.dessiner_ligne(point);
    }
    
    

    ecrire_fichier(A);

    return 0;
}