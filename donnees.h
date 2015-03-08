#ifndef DONNEES_H_INCLUDED
#define DONNEES_H_INCLUDED
#include "sommet2.h"
#include "arete.h"
#include "triangle.h"
#include <vector>

class donnees
{
  private:
  int* Tailles_fr;
  vector<sommet*> Sommets_fr;
  arete* Aretes_fr;
  triangle* Triangles_fr;
  int* Tailles_bk;
  vector<sommet*> Sommets_bk;
  arete* Aretes_bk;
  triangle* Triangles_bk;
  float** Sol;

  public:

  //constructeur
  donnees(const char*, const char*, const char*);

  //accesseurs
  int tailles_fr(int);
  vector<sommet*> sommets_fr() {return(Sommets_fr);}
  arete* aretes_fr() {return(Aretes_fr);}
  triangle* triangles_fr() {return(Triangles_fr);}
  int* tailles_bk() {return(Tailles_bk);}
  vector<sommet*> sommets_bk() {return(Sommets_bk);}
  arete* aretes_bk() {return(Aretes_bk);}
  triangle* triangles_bk() {return(Triangles_bk);}
  float** sol() {return(Sol);}
  sommet* sommets_fr(int);
  void sommets_fr(vector<sommet*>);

  //fonctions de modification
  void tailles_fr(int,int); //tailles_fr(a,b) met a dans Tailles_fr[b].
  void ajouter_sommet(float, float);
  void ajouter_arete(arete);
  void ajouter_triangle(triangle);
  void ajouter_individu(float, float,float, float, float, float);
};
#endif // DONNEES_H_INCLUDED#include "sommet2.h"



