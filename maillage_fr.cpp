#include<iostream>
#include<fstream>
#include "maillage_fr.h"
#include "donnees.h"
#include "ecriture.h"
#include "barycent.h"
#include "map.h"

using namespace std;

void insert(donnees D, sommet I, const char* fichier)
{
    D.ajouter_sommet(I.x(), I.y());
    //on ajoute les coordonnees de l'individu dans le tableau des sommets front
    //le numero de l'individu est donc tailles_fr[0]

    float* coor_bar; //on cree le tableau des coordonnees barycentriques
    for(int i=0;i<D.tailles_fr(2);i++) //boucle sur les triangles du maillage front
    {
        coor_bar = barycent(I.x(), I.y(), D.triangles_fr()[i], D);
        //on recupere les coordonnees barycentriques de l'individu par rapport au triangle en cours
        if(coor_bar[0]>0 && coor_bar[1]>0 && coor_bar[2]>0) //on se place dans le triangle où est l'individu
        {
            triangle tr = D.triangles_fr()[i];
            arete a = arete(D.tailles_fr(0), tr.sommet1(),0, D.sommets_fr());
            arete b = arete(D.tailles_fr(0), tr.sommet2(),0, D.sommets_fr());
            arete c = arete(D.tailles_fr(0), tr.sommet3(),0, D.sommets_fr());
            //on cree les trois nouvelles aretes
            D.ajouter_arete_fr(a);
            D.ajouter_arete_fr(b);
            D.ajouter_arete_fr(c);
            //on les ajoute dans les donnees

            triangle t1 = triangle(D.tailles_fr(0), tr.sommet2(), tr.sommet3(), 1);
            triangle t2 = triangle(tr.sommet1(), D.tailles_fr(0), tr.sommet3(), 1);
            triangle t3 = triangle(tr.sommet1(), tr.sommet2(), D.tailles_fr(0), 1);
            //on cree les trois nouveaux triangles, orientes dans le bon sens (permutation)
            D.enlever_triangle(i);
            //D.triangles_fr()[i].vivant = 0; //on tue le triangle qui a disparu, remplace par les nouveaux triangles
            D.ajouter_triangle(t1);
            D.ajouter_triangle(t2);
            D.ajouter_triangle(t3);
            break; //on sort de la boucle for
            //on ajoute les triangles aux donnees

        } // end if
    } // for i
    map<arete, triangle*> reper = construit_map(D.aretes_fr(), D.triangles_fr(), D.tailles_fr(1), D.tailles_fr(2));
    D.update_map(reper);
    create_text(D,fichier); //on cree le fichier texte avec le nouveau maillage dynamique
} //fin de la fonction

arete other_edge(arete a, triangle t1, triangle t2, donnees D)
{
    int n1;
    int n2;

    //on cherche le premier sommet de l'autre arete dans t1
    if(t1.sommet1()==a.sommet1() || t1.sommet1()==a.sommet2())
    {
        if(t1.sommet2()==a.sommet1() || t1.sommet2()==a.sommet2())
        {
            n1 = t1.sommet3();
        }
        else
        {
            n1 = t1.sommet2();
        }
    }
    else
    {
        n1 = t1.sommet1();
    }

    //on cherche le second sommet de l'autre arete dans t2
    if(t2.sommet1()==a.sommet1() || t2.sommet1()==a.sommet2())
    {
        if(t2.sommet2()==a.sommet1() || t2.sommet2()==a.sommet2())
        {
            n2 = t2.sommet3();
        }
        else
        {
            n2 = t2.sommet2();
        }
    }
    else
    {
        n2 = t2.sommet1();
    }

    arete b = arete(n1, n2, 0, D.sommets_fr());
    cout<<"aretes complementaires"<<endl;
    a.print();
    b.print();
    return(b);
}

/*void swap(donnees D, const char* file)
{
    map<arete,triangle*> reper = D.reper_fr();
    for(int i=0;i<D.tailles_fr()[1];i++)
    {
        triangle t1 = reper[D.aretes_fr()[i]][0];
        triangle t2 = reper[D.aretes_fr()[i]][1];
        if(t2.sommet1()!=0 && t2.sommet2()!=0 && t2.sommet3()!=0)
        {
            arete a = other_edge(D.aretes_fr()[i], t1, t2, D);

        }
    }
}*/
