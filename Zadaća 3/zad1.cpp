#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include "tgaimage.h"
using namespace std;


const int width  = 512;
const int height = 512;


const TGAColor green = TGAColor(0, 255, 0, 1);
const TGAColor red   = TGAColor(255, 0, 0, 1);
const TGAColor blue  = TGAColor(0, 0, 255, 1);
const TGAColor cyan = TGAColor(0, 255, 255,1);              


float fun(float xa,float ya,float xc,float yc,float x,float y) 
{
    return ((ya-yc)*x+(xc-xa)*y+xa*yc-xc*ya);
}


void draw_triangle_2d(float x0, float y0, float x1, float y1, float x2, float y2 ,TGAImage &image,TGAColor color) {   

    int maxX = ceil (max (max(x0,x1), x2));
    int minX = floor (min (min(x0,x1), x2));

    int maxY = ceil (max (max(y0,y1), y2));
    int minY = floor(min (min(y0,y1), y2));
   
    float alpha,beta,gama;

    for (int j =minY; j <= maxY ; ++j){
        for (int i = minX; i <= maxX; ++i){
            
            alpha = fun(x1,y1,x2,y2,i,j)/fun(x1,y1,x2,y2,x0,y0); 
            beta= fun(x2,y2,x0,y0,i,j)/fun(x2,y2,x0,y0,x1,y1);  
            gama= fun(x0,y0,x1,y1,i,j)/fun(x0,y0,x1,y1,x2,y2);  
             
            if (alpha >= 0 && alpha <= 1 && beta >= 0 && beta <= 1 && gama >= 0 && gama <= 1) 
            { 
                if (( alpha > 0 ||((fun(x1,y1,x2,y2,x0,y0))*(fun(x1,y1,x2,y2,-1,-1))) >= 0)
                 &&( beta > 0 || ((fun(x2,y2,x0,y0,x1,y1))*(fun(x2,y2,x0,y0,-1,-1))) >= 0)
                 &&( gama > 0 || (fun(x0,y0,x1,y1,x2,y2))*(fun(x0,y0,x1,y1,-1,-1))) >= 0)
                 {
                        image.set(i, j, color);
                }  
            }
        }
    } 
}


int main()
{

    TGAImage image(width, height, TGAImage::RGB);
    
    draw_triangle_2d(20, 40, 180, 160, 120,240,image, cyan);
    draw_triangle_2d(200, 200, 300, 250, 200, 340,image, red);
    
    image.flip_vertically();
    image.write_tga_file("zad1.tga");
}
