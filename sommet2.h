#ifndef MAILLAGE_DYN_H_INCLUDED
#define MAILLAGE_DYN_H_INCLUDED
#include <iostream>
#include <list> //LIST des indiciduals

using namespace std;


class sommet // means the dynamic mesh
{
  protected:
  int reff;
  float xx,yy;
  int num = -1;


  public:

  //constructeurs
  sommet(); // non init par défaut
  sommet(const sommet &);
  sommet(float abs, float ord, int refer){xx = abs; yy = ord; reff=refer;};


  //accesseurs
  float x()const{return xx;};
  float y()const{return yy;};
  int ref()const{return reff;};
  int Num()const{return num;}

  virtual float masse()const{return 0;};
  virtual float r()const{return 0;};
  virtual float fmax()const{return 0;};
  virtual float gw()const{return 0;};
  virtual float vx()const{return 0;};
  virtual float vy()const{return 0;};
  virtual float objx()const{return 0;};
  virtual float objy()const{return 0;};
  virtual sommet* vois()const{return NULL;};


  //opérateurs
  sommet & operator=(const sommet & S);

  //affichage
  virtual void print();

  //fonctions de modification
  void Num(int number){num = number;}
  virtual void changer(float,float,int);
  virtual void masse(float);
  virtual void g(float);
  virtual void objectif(float, float);

};


class individual:public sommet
{
  protected:
  //int reff;//0 pour les individu
  float m,rr,f_max,gg;
  float v_x,v_y/*,xx,xy*/;// À calculer
  float obj_x, obj_y; // vd=obj-position
  int His_tri = -1;
  sommet* voisins; //the table of pointer of voisins
  // on calcul rho dans les maillage.

  public:

  //constructeurs
  individual();
  individual(const individual &);
  //individual(T x, T y, int ref):sommet(x,y,ref){ reff=0;};
  //voisin();// it calcul les voisins dans maillage dynamique
  //void allou_individual(T a,T b,T c,T d=9.8){m=a;r=b;f_max=c;g=d;cout<<"alloué"<<endl;};
  //T calcul_fmur(T* maillage_font,T* d_mur);//on trouve lindividual est ou dans le m_font donc sais d_mur
  //void operator ++();// returns arry of pointers of indi nearby
  //~individual(){delete voisins[];}

  //accesseurs
  float x()const{return xx;};
  float y()const{return yy;};
  int ref()const{return reff;};

  float masse()const{return m;};
  float r()const{return rr;};
  float fmax()const{return f_max;};
  float gw()const{return gg;};
  float vx()const{return v_x;};
  float vy()const{return v_y;};
  float objx()const{return obj_x;};
  float objy()const{return obj_y;};
  sommet* vois()const{return voisins;};
  int his_tri() const{return His_tri;}

  //affichage
  void print();

  //fonctions de modifications
  void masse(float);
  void g(float);
  void objectif(float, float);
  void changer(float, float, float, float, int);//position vitesse ref
  void his_tri(int num_tri){His_tri = num_tri;}
};
#endif
#ifndef SOMMET2_H_INCLUDED
#define SOMMET2_H_INCLUDED
#endif


