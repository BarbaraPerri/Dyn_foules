#include<iostream>
#include<fstream>
#include "maillage_fr.h"
#include "donnees.h"
#include "ecriture.h"
#include "barycent.h"
#include "map.h"

using namespace std;

/*void insert(donnees D,float x, float y, float objx, float objy, float m, float gw, const char* fichier)
{
    //individual* I = new individual();
    D.ajouter_individu(x,y,objx,objy,m,gw);
    //cout<<D.sommets_fr(12)->x()<<endl;
    //I.print_sommet();
    //on ajoute les coordonnees de l'individu dans le tableau des sommets front
    //le numero de l'individu est donc tailles_fr[0]

    float* coor_bar; //on cree le tableau des coordonnees barycentriques
    for(int i=0;i<D.tailles_fr(2);i++) //boucle sur les triangles du maillage front
    {
        coor_bar = barycent_fr(x, y, D.triangles_fr()[i], D);
        //cout<<coor_bar[0]<<" "<<coor_bar[1]<<" "<<coor_bar[2]<<endl;
        //on recupere les coordonnees barycentriques de l'individu par rapport au triangle en cours
        if(coor_bar[0]>0 && coor_bar[1]>0 && coor_bar[2]>0) //on se place dans le triangle où est l'individu
        {
            triangle tr = D.triangles_fr()[i];
            arete a = arete(D.tailles_fr(0), tr.sommet1(),0, D.sommets_fr());
            //a.print();
            //cout<<"arete a creee"<<endl;
            arete b = arete(D.tailles_fr(0), tr.sommet2(),0, D.sommets_fr());
            //b.print();
            //cout<<"arete b creee"<<endl;
            arete c = arete(D.tailles_fr(0), tr.sommet3(),0, D.sommets_fr());
            //c.print();
            //cout<<"arete c creee"<<endl;
            //on cree les trois nouvelles aretes
            D.ajouter_arete_fr(a);
            //D.aretes_fr()[21].print();
            //cout<<"ajout de a"<<endl;
            D.ajouter_arete_fr(b);
            //cout<<"ajout de b"<<endl;
            D.ajouter_arete_fr(c);
            //cout<<"ajout de c"<<endl;
            //on les ajoute dans les donnees

            triangle t1 = triangle(D.tailles_fr(0), tr.sommet2(), tr.sommet3(), 1);
            //cout<<"t1 cree"<<endl;
            triangle t2 = triangle(tr.sommet1(), D.tailles_fr(0), tr.sommet3(), 1);
            //cout<<"t2 cree"<<endl;
            triangle t3 = triangle(tr.sommet1(), tr.sommet2(), D.tailles_fr(0), 1);
            //cout<<"t3 cree"<<endl;
            //on cree les trois nouveaux triangles, orientes dans le bon sens (permutation)
            D.enlever_triangle(i);
            //cout<<"triangle enleve"<<endl;
            //D.triangles_fr()[i].vivant = 0; //on tue le triangle qui a disparu, remplace par les nouveaux triangles
            D.ajouter_triangle(t1);
            //cout<<"triangle t1 ajoute"<<endl;
            D.ajouter_triangle(t2);
            //cout<<"triangle t2 ajoute"<<endl;
            D.ajouter_triangle(t3);
            //cout<<"triangle t3 ajoute"<<endl;
            break; //on sort de la boucle for
            //on ajoute les triangles aux donnees

        } // end if
    } // for i
    map<arete, triangle*> reper = construit_map(D.aretes_fr(), D.triangles_fr(), D.tailles_fr(1), D.tailles_fr(2));
    //cout<<"map construite"<<endl;
    D.update_map(reper);
    create_text(D,fichier); //on cree le fichier texte avec le nouveau maillage dynamique
    //D.sommets_fr()[12]->print_sommet();
    //cout<<D.sommets_fr().size()<<endl;
} //fin de la fonction*/

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
    /*cout<<"aretes complementaires"<<endl;
    a.print();
    b.print();*/
    return(b);
}

triangle other_tri(triangle t, arete a)
{
    triangle t_res;
    if(t.sommet1()==a.sommet1()) //si le premier sommet du triangle est un de l'arete
    {
        t_res = triangle(t.sommet1(), a.sommet2(), t.sommet3(),0); //on place l'autre sommet de l'arete juste apres
    }
    else if(t.sommet1()==a.sommet2())
    {
        t_res = triangle(t.sommet1(), a.sommet1(), t.sommet3(),0);
    }
    else
    {
        if(t.sommet2()==a.sommet1())
        {
            t_res = triangle(t.sommet1(), t.sommet2(), a.sommet2(),0);
        }
        else if(t.sommet2()==a.sommet2())
        {
            t_res = triangle(t.sommet1(), t.sommet2(), a.sommet1(),0);
        }
        else
        {
            if(t.sommet3()==a.sommet1())
            {
                t_res = triangle(a.sommet2(), t.sommet2(), t.sommet3(),0);
            }
            else if(t.sommet2()==a.sommet2())
            {
                t_res = triangle(a.sommet1(), t.sommet2(), t.sommet3(),0);
            }
        }
    }
    return(t_res);
}

/*void swap(donnees D, const char* file)
{
    //cout<<D.sommets_fr().size()<<endl;
    //D.sommets_fr(12)->print_sommet();
    map<arete,triangle*> reper = D.reper_fr();//on recupere Reper_fr
    map<arete,triangle*> reper2;
    //cout<<"map recuperee"<<endl;
    //for(int i=0;i<D.tailles_fr()[1];i++)
    map<arete, triangle*>::iterator it;
    for (it = reper.begin();it!=reper.end();it++)
    {
        //arete b = D.aretes_fr()[i];//l'arete sur laquelle on est
        arete b = it->first;
        //triangle t1 = reper[b][0];//le premier triangle dans la map
        triangle t1 = it->second[0];
        //cout<<"triangle t1 recupere"<<endl;
        //triangle t2 = reper[b][1];//le second triangle dans la map
        triangle t2 = it->second[1];
        //cout<<"triangle t2 recupere"<<endl;
        if(t2.sommet1()!=0 && t2.sommet2()!=0 && t2.sommet3()!=0) //si l'arete n'est pas frontiere
        {
            arete a = other_edge(b, t1, t2, D); //on trouve l'arete complementaire
            if(compare(b, a)==false && b.x1()-b.x2()>0.001 && b.y1()-b.y2()>0.001) //si l'arete en place est la plus longue
            {
                //reper[b] = NULL; //on la retire de la map
                //D.enlever_arete_fr(i); //on retire l'arete longue
                D.enlever_arete(it->first);
                cout<<"arete enlevee"<<endl;
                D.ajouter_arete_fr(a); //on ajoute l'arete plus courte
                triangle t3 = other_tri(t1,a); //on cree les deux nouveaux triangles
                triangle t4 = other_tri(t2,a);
                D.enlever_triangle(t1); //on enleve les deux anciens triangles
                D.enlever_triangle(t2);
                D.ajouter_triangle(t3); //on rajoute les deux nouveaux triangles
                D.ajouter_triangle(t4);
                reper2 = construit_map(D.aretes_fr(), D.triangles_fr(), D.tailles_fr(1), D.tailles_fr(2));
                D.update_map(reper2);
                /*cout<<"L'arete"<<endl;
                b.print();
                cout<<"a ete remplacee par l'arete"<<endl;
                a.print();
            }// fin des modifs si l'arete doit etre changee
        }//fin du test de comparaison
    }//for i
    //D.sommets_fr(12)->print_sommet();
    //cout<<"avant d'ecrire le fichier"<<endl;
    //cout<<D.sommets_fr().size()<<endl;
    create_text(D, file);
}
*/
