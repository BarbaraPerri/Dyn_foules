#include <iostream>
#include <cmath>
#include <cstdlib>
#include "sommet2.h"
using namespace std;
typedef float T;
sommet::sommet(){xx=0;yy=0;reff=0;}
void sommet::print_sommet()
{
cout<<"Position: "<<xx<<"\t"<<yy<<endl;
cout<<"Reference: "<<reff<<endl;
}
void individual::print_individual()
{
cout<<"m,r,f_max,g:"<<endl<<m<<"\t"<<r<<"\t"<<f_max<<"\t"<<g<<endl;
cout<<"ref = "<<reff<<endl;
}
sommet & sommet::operator=(const sommet & S){
  xx=S.x();
  yy=S.y();
  reff=S.ref();
  return *this;
}

void sommet::changer(float x,float y,int r){
  xx=x;
  yy=y;
  reff=r;
}

//T individual::calcul_fmur(T* maillage_font,T* d_mur);//on trouve lindividual est ou dans le m_font donc sais d_mur
//{
//
//}
//
//void individual<T>::operator ++(individual* voisins);
//{
// if(voisins == NULL){cout<<'ERROR::The voisins point to 0.'<<endl;return 0;}
// int n = sizeof(voisins);
// T fobj_x=0,fobj_y=0,fcol_x=0,fcol_y=0,fmur_x=0,fmur_y=0;
// for(int i=0;i<n;i++)
// {
// individual& P = voisin(i); // P signify person
//
// //calcul d,rho,s_x,s_y
// d = sqrt((x_x- P.x_x)*(x_x- P.x_x) + (x_y- P.x_y)*(x_y- P.x_y));
// rho = d/r;
// s_x = (x_x-P.x_x)/d;
// s_y = (x_y-P.x_y)/d;
// // start to calculate f
// fobj_x += g*(vd_x - v); fobj_y += g*(vd_y - v);
// fcol_x = -f_max/(1+rho*rho)*s_x; fcol_y = -f_max/(1+rho*rho)*s_y;
// fmur_x =
// }
//}
