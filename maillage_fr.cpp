#include<iostream>
#include<fstream>
#include "maillage_fr.h"
#include "ajouter_individu.h"
#include "ecriture.h"

/*using namespace std;

void insert(struct donnees tableaux, individual I, const char* fichier)
{
    ajouter_individu(I.x(), I.y(), tableaux);
    //on ajoute les coordonnees de l'individu dans le tableau des sommets front

    float* coor_bar; //on cree le tableau des coordonnees barycentriques
    for(int i=0;i<tableaux.tailles_fr[2];i++) //boucle sur les triangles du maillage front
    {
        coor_bar = barycent(I.x(), I.y(), tableaux.Triangles_fr[i], tableaux);
        //on recupere les coordonnees barycentriques de l'individu par rapport au triangle en cours
        if(coor_bar[0]>0 && coor_bar[1]>0 && coor_bar[2]>0) //on se place dans le triangle où est l'individu
        {
            arete a = arete(tableaux.tailles_fr[0], tableaux.Triangles_fr[i].sommet1(),0);
            arete b = arete(tableaux.tailles_fr[0], tableaux.Triangles_fr[i].sommet2(),0);
            arete c = arete(tableaux.tailles_fr[0], tableaux.Triangles_fr[i].sommet3(),0);
            //on cree les trois nouvelles aretes

            triangle t1 = triangle(tableaux.tailles_fr[0], tableaux.Triangles_fr[i].sommet2(), tableaux.Triangles_fr[i].sommet3(), 0);
            triangle t2 = triangle(tableaux.Triangles_fr[i].sommet1(), tableaux.tailles_fr[0], tableaux.Triangles_fr[i].sommet3(), 0);
            triangle t3 = triangle(tableaux.Triangles_fr[i].sommet1(), tableaux.Triangles_fr[i].sommet2(),tableaux.tailles_fr[0], 0);
            //on cree les trois nouveaux triangles, orientes dans le bon sens (permutation)

            tableaux.Triangles_fr[i].vivant = 0; //on tue le triangle qui a disparu, remplace par les nouveaux triangles
        } // end if
    } // for i

    create_text(tableaux,fichier); //on cree le fichier texte avec le nouveau maillage dynamique
} //fin de la fonction*/
