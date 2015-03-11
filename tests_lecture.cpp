#include <iostream>
#include <fstream>
#include "lecture.h"
#include "donnees.h"
#include "maillage_fr.h"
#include "ecriture.h"
#include "map.h"

using namespace std;
/*
int main()
{
    sommet som = sommet(1,2,0); //test pour le constructeur de la classe sommet -> ok
    som.print();

    arete a = arete(1,2,3); //test pour le constructeur de la classe arete -> ok
    a.print();

    donnees D = donnees("simple_geo2.empty.mesh","simple_geo.back.mesh","simple_geo.dist_wall.sol");
    bool b = compare(D.aretes_fr()[1], D.aretes_fr()[0]); //test de compare
    cout<<b<<endl; //--> ok

    triangle t = triangle(1,2,3,0); //test pour le constructeur et l'impression du triangle
    t.print(); //--> ok

    int* tailles;
    tailles = lecture_mesh_tailles("simple_geo.mesh"); //test pour lecture des tailles -> ok
    cout<<tailles[0]<<" "<<tailles[1]<<" "<<endl; //affichage pour test

    int* tailles_back;
    tailles_back = lecture_back_mesh_tailles("simple_geo.back.mesh"); //test pour lecture des tailles du fond -> ok
    cout<<tailles_back[0]<<" "<<tailles_back[1]<<" "<<tailles_back[2]<<endl; //affichage pour test

    float ** Sol = lecture_sol("simple_geo.dist_wall.sol"); //test pour la lecture du fichier de distance au sol -> ok

    int* tailles;
    tailles = lecture_mesh_tailles("simple_geo.empty.mesh");
    cout<<tailles[0]<<" "<<tailles[1]<<" "<<tailles[2]<<endl;
    sommet* Sommets = new sommet[tailles[0]];
    arete* Aretes = new arete[tailles[1]];
    triangle* Triangles = new triangle[tailles[2]];
    lecture_mesh("simple_geo.empty.mesh",Sommets,Aretes, Triangles); //test lecture du maillage -> ok
    for(int i=0;i<tailles[0];i++) {Sommets[i].print_sommet();}
    for(int i=0;i<tailles[1];i++) {Aretes[i].print();}
    for(int i=0;i<tailles[2];i++) {Triangles[i].print();}

    sommet* Sommets = new sommet[tailles_back[0]];
    arete* Aretes = new arete[tailles_back[1]];
    triangle* Triangles = new triangle[tailles_back[2]];
    lecture_back_mesh("simple_geo.back.mesh",Sommets,Aretes,Triangles); //test lecture du maillage -> ok
    for(int i=0;i<tailles_back[2];i++) {Triangles[i].print();}

    donnees tableaux = donnees("simple_geo.empty.mesh","simple_geo.back.mesh","simple_geo.dist_wall.sol");
    cout<<tableaux.tailles_bk()[1]<<endl; //test du constructeur de la classe donnees --> ok

    triangle T = triangle(1,2,3,0);
    arete a = arete(2,1,0);
    bool edge = T.have_edge(a); //test de l'appartenance d'une arete a un triangle --> ok
    cout<<edge;

    donnees D = donnees("simple_geo.empty.mesh","simple_geo.back.mesh","simple_geo.dist_wall.sol");
    cout<<D.tailles_fr()[0]<<" "<<D.tailles_fr()[1]<<" "<<D.tailles_fr()[2]<<endl; //--> ok
    cout<<D.tailles_bk()[0]<<" "<<D.tailles_bk()[1]<<" "<<D.tailles_bk()[2]<<endl; //--> ok
    for(int i=0;i<D.tailles_fr()[0];i++)
    {cout<<D.sommets_fr()[i].x()<<" "<<D.sommets_fr()[i].y()<<" "<<D.sommets_fr()[i].ref()<<endl;} --> ok
    create_text(D,"test.mesh"); --> ok

    donnees D = donnees("simple_geo.empty.mesh","simple_geo.back.mesh","simple_geo.dist_wall.sol");
    sommet I = sommet(15,15,0); //--> ok
    arete a = arete(1,5,0,D.sommets_fr()); // --> ok
    triangle t = triangle(4,3,2,0); // --> ok
    D.ajouter_sommet(I.x(), I.y()); //--> ok
    D.ajouter_arete(a); // --> ok
    D.ajouter_triangle(t); // --> ok
    create_text(D,"test.mesh"); // --> ok

    donnees D = donnees("simple_geo.empty.mesh","simple_geo.back.mesh","simple_geo.dist_wall.sol");
    sommet I = sommet(33,15,0);
    insert(D,I,"new.empty.mesh"); //--> ok

    donnees D = donnees("simple_geo2.empty.mesh","simple_geo.back.mesh","simple_geo.dist_wall.sol");
    cout<<D.reper_fr()[D.aretes_fr()[0]][0].sommet1()<<D.reper_fr()[D.aretes_fr()[0]][0].sommet2()<<endl;
    D.print_map_fr(); //--> ok
    construit2_map(D.aretes_fr(), D.triangles_fr(),D.tailles_fr()[1],D.tailles_fr()[2]);

    map<arete, triangle*> reper;
    donnees D = donnees("simple_geo.empty.mesh","simple_geo.back.mesh","simple_geo.dist_wall.sol");
    arete a = arete(1,2,0,D.sommets_fr());
    arete b = arete(6,8,0,D.sommets_fr());
    triangle t1 = triangle(1,2,3,4);
    triangle t2 = triangle(5,6,7,8);
    triangle * val1 = new triangle[2];
    val1[0] = t1; val1[1] = t2;
    triangle * val2 = new triangle[2];
    val2[0] = t2; val2[1] = t1;
    reper[a] = val1;
    reper[b] = val2;
    reper[a][0].print();
    reper[a][1].print();

    map<arete, triangle*> reper;
    donnees D = donnees("simple_geo.empty.mesh","simple_geo.back.mesh","simple_geo.dist_wall.sol");
    arete a = arete(1,2,0,D.sommets_fr());
    ajouter_entree(a,D.triangles_fr(),D.tailles_fr(),reper);
    reper[a][0].print();

    donnees D = donnees("simple_geo.empty.mesh","simple_geo.back.mesh","simple_geo.dist_wall.sol");
    D.inner_aretes_fr();
    D.inner_aretes_bk();
    create_text(D,"inner.mesh");


   return 0;
}
