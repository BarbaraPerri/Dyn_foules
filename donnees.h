#ifndef DONNEES_H_INCLUDED
#define DONNEES_H_INCLUDED
#include "sommet2.h"
#include "arete.h"
#include "triangle.h"
#include <vector>
#include <map>

class donnees
{
  private:
  int* Tailles_fr;
  vector<sommet*> Sommets_fr;
  arete* Aretes_fr;
  triangle* Triangles_fr;
  int* Tailles_bk;
  sommet* Sommets_bk;
  arete* Aretes_bk;
  triangle* Triangles_bk;
  float** Sol;
  map<arete, triangle*> Reper_fr;
  map<int,int*> Map_voisinT_bk;

  public:

  //constructeur
  donnees(const char*, const char*, const char*);


  //accesseurs
  int tailles_fr(int);
  int tailles_bk(int);

  sommet* sommets_fr(int);
  vector<sommet*> sommets_fr()const {return(Sommets_fr);}
  sommet* sommets_bk()const {return(Sommets_bk);}

  arete* aretes_fr() const{return(Aretes_fr);}
  arete* aretes_bk() const{return(Aretes_bk);}
  triangle* triangles_fr()const {return(Triangles_fr);}
  triangle* triangles_bk() const{return(Triangles_bk);}

  float** sol()const {return(Sol);}

  map<arete, triangle*> reper_fr()const {return(Reper_fr);}
  map<int, int*> map_voisinT_bk() const{return(Map_voisinT_bk);}

  //fonctions de modification
  void sommets_fr(vector<sommet*>);
  void tailles_fr(int,int); //tailles_fr(a,b) met a dans Tailles_fr[b].
  //void ajouter_sommet(float, float, int);
  void ajouter_sommet(sommet*);
  void ajouter_individu(float, float,float, float, float, float);
  void ajouter_arete_fr(arete);
  void enlever_arete(arete);
  void ajouter_arete_bk(arete);
  void ajouter_triangle(triangle);
  void enlever_triangle(int);
  void enlever_triangle(triangle);
  void update_map(map<arete, triangle*>);
  void inner_aretes_fr();
  void inner_aretes_bk();
  void insert(float x, float y, float objx, float objy, float m, float gw, const char* fichier);
  void swap(const char* file);

  //fonctions d'impression
  void print_map_fr();

};
#endif // DONNEES_H_INCLUDED#include "sommet2.h"



