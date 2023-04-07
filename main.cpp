#include "Image.hpp"
#include "Matrice.hpp"
#include "Point.hpp"

std::vector<Point> donnerpoints (Image image)
{
    std::vector<Point> pntdroites;
    int cpt=0;
    for (int i=0; i<30; i++) //changer le 30
    {
        for (int j=0;j<30; j++) //changer le 30
        {
             if (((image.image[i][j][0]==image.image[i][j][1])&&(image.image[i][j][1]==image.image[i][j][2]))&&(image.image[i][j][0]==0|| image.image[i][j][0]==255))
            {
                std::cout<<"fond"<<std::endl;
            }else{
                std :: cout << i<<j << std :: endl;
                Point P{-i,j};
                pntdroites[cpt]=P;
                cpt=cpt+1; 
            }
                
        }
    }
    return pntdroites;
}



int main(){
    res= donnerpoints(Image)
    
    return 0;
}