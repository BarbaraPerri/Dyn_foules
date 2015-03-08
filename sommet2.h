#ifndef MAILLAGE_DYN_H_INCLUDED
#define MAILLAGE_DYN_H_INCLUDED
#include <iostream>
#include <list> //LIST des indiciduals

using namespace std;

typedef float T; // define T as floatclass sommet // means the dynamic mesh

class sommet // means the dynamic mesh
{
  protected:
  int reff;
  float xx,yy;

  public:
  sommet(); // non init par défaut
  void print_sommet();
  sommet(T abs, T ord, int refer){xx = abs; yy = ord; reff=refer;};
  float x()const{return xx;};
  float y()const{return yy;};
  int ref()const{return reff;};
  virtual T objx()const{return 0;};
  virtual void changer(float,float,int);
  virtual void masse(float);
  virtual void g(float);
  virtual void objectif(float, float);
  sommet & operator=(const sommet & S);

  sommet(const sommet &);
};


class individual:public sommet
{
  protected:
  int reff;//0 pour les individu
  T m,rr,f_max,gg;
  T v_x,v_y,xx,xy;// À calculer
  T obj_x, obj_y; // vd=obj-position
  sommet* voisins; //the table of pointer of voisins
  // on calcul rho dans les maillage.

  public:
  individual(); //constructeur par défault
  //individual(T x, T y, int ref):sommet(x,y,ref){ reff=0;};
  //voisin();// it calcul les voisins dans maillage dynamique
  //void allou_individual(T a,T b,T c,T d=9.8){m=a;r=b;f_max=c;g=d;cout<<"alloué"<<endl;};
  //T calcul_fmur(T* maillage_font,T* d_mur);//on trouve lindividual est ou dans le m_font donc sais d_mur
  //void operator ++();// returns arry of pointers of indi nearby
  void print_individual();
  //~individual(){delete voisins[];}
  //accesseur
  T r()const{return rr;};
  T fmax()const{return f_max;};
  T x()const{return xx;};
  T y()const{return yy;};
  T vx()const{return v_x;};
  T vy()const{return v_y;};
  T objx()const{return obj_x;};
  T objy()const{return obj_y;};
  T masse()const{return m;};
  T gw()const{return gg;};
  int ref()const{return reff;};
  sommet* vois()const{return voisins;};
  //operateurs/initialiseurs
  individual(const individual &);
  void masse(float);
  void g(float);
  void objectif(float, float);
  void changer(float, float, float, float, int);//position vitesse ref
};
#endif// MAILLAGE_DYN_H_INCLUDED
#ifndef SOMMET2_H_INCLUDED
#define SOMMET2_H_INCLUDED
#endif // SOMMET2_H_INCLUDED


