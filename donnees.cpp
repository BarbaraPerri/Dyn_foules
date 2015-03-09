#include "donnees.h"
#include "lecture.h"
#include <iostream>
#include <vector>

using namespace std;

donnees::donnees(const char* mesh, const char* back_mesh, const char* sol)
{
  Tailles_fr = lecture_mesh_tailles(mesh);
  Aretes_fr = new arete[Tailles_fr[1]];
  Triangles_fr = new triangle[Tailles_fr[2]];
  lecture_mesh(mesh, Sommets_fr, Aretes_fr, Triangles_fr);
   //cout<<"fin lecture mesh size sommets "<<Sommets_fr.size()<<endl;
   //cout<<" Initialisation du maillage back "<<endl;
  Tailles_bk = lecture_mesh_tailles(back_mesh);
   //cout<<" lecture tailles "<<Tailles_bk[0] << " "<<Tailles_bk[1] << " " <<Tailles_bk[2]<<endl;
  vector<sommet *> Sommets_bk;
   //cout<< " alloc sommet back ok "<<endl;
  Aretes_bk = new arete[Tailles_bk [1]];
   //cout<< " alloc aretes back ok "<<endl;
  Triangles_bk = new triangle[Tailles_bk [2]];
   //cout<< " alloc triangles back ok "<<endl;
  //lecture_mesh(back_mesh, Sommets_bk , Aretes_bk, Triangles_bk);
   //cout<< " lecture mesh back ok "<<endl;
   //cout<< " premier sommet "<<endl;
   //cout<< " dernier sommet "<<endl;
   //cout<< " premiere arete "<<endl;
   //cout<< " derniere arete "<<endl;
   //cout<< " premier triangle "<<endl;
   //cout<< " dernier triangle "<<endl;//*/
  Sol = lecture_sol(sol);
  //cout<<" **** FIN CONSTRUCTEUR DONNEES PB "<<endl;
}


//accesseurs

int donnees::tailles_fr(int i)
{
  return Tailles_fr[i];
}

int donnees::tailles_bk(int i)
{
  return Tailles_bk[i];
}

sommet* donnees::sommets_fr(int i){
  return Sommets_fr[i];
}


//fonctions de modification

void donnees::sommets_fr(vector<sommet*> S){
  Sommets_fr=S;
}

void donnees::tailles_fr(int a, int b){
    Tailles_fr[b]=a;
}

void donnees::ajouter_sommet(float x, float y)
{
    sommet S;
    S.changer(x,y,0);
    Sommets_fr.push_back(&S);
}

void donnees::ajouter_individu(float x,float y,float objx, float objy, float m, float gw){

    individual I;
    I.changer((float)x,(float)y,(float)0,(float)0,0);
    I.objectif(objx,objy);
    I.g(gw);
    I.masse(m);
    Sommets_fr.push_back(&I);

}


void donnees::ajouter_arete(arete a)
{
  Tailles_fr[1]++;
  arete * A = new arete[Tailles_fr[1]];
  for (int i=0; i<(Tailles_fr[1] -1); i++)
  {
    A[i]=Aretes_fr[i];
  }
  A[Tailles_fr[1]] = a;
  arete * tmp = Aretes_fr;
  Aretes_fr = A;
  delete [] tmp;
}


void donnees::ajouter_triangle(triangle t)
{
  Tailles_fr[2]++;
  triangle * T = new triangle[Tailles_fr[2]];
  for (int i=0; i<(Tailles_fr[2] -1); i++)
  {
    T[i]=Triangles_fr[i];
  }
  T[Tailles_fr[2]] = t;
  triangle * tmp = Triangles_fr;
  Triangles_fr = T;
  delete [] tmp;
}





