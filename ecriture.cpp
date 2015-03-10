#include <iostream>
#include <fstream>
#include"ecriture.h"
#include "donnees.h"

using namespace std;

void create_text(donnees D,const char * fichiertxt)
{
ofstream fichier(fichiertxt, ios::out | ios::trunc );
    if (fichier)
    {
        fichier<<"MeshVersionFormatted 1"<<endl<<endl;
        fichier<<"Dimension"<<endl<<2<<endl<<endl;
        //cout<<"trucs chiants ecrits"<<endl;
        int N = D.tailles_fr(0);
        //cout<<"taille des sommets"<<endl;
        fichier<<"Vertices"<<endl<<N<<endl;
        //D.sommets_fr()[12]->print_sommet();
        for (int i=0; i<N; i++)
        {
            fichier<<D.sommets_fr(i)->x()<<" "<<D.sommets_fr(i)->y()<<" "<<D.sommets_fr(i)->ref()<<endl;//revoir celon ce qui a été décidé dans la classe sommet
            //cout<<"sommet "<<i<<" ok"<<endl;
        }
        //cout<<"fin des sommets"<<endl;
        int M = D.tailles_fr(1);
        //cout<<"taille allouee"<<endl;
        fichier<<endl<<"Edges"<<endl<<M<<endl;
        //cout<<"edge ecrit"<<endl;
        for (int i=0; i<M; i++)
        {
            fichier<<D.aretes_fr()[i].sommet1()<<" "<<D.aretes_fr()[i].sommet2()<<" "<<D.aretes_fr()[i].ref()<<endl;//revoir celon ce qui a été décidé dans la classe arrete
        }
        int O=D.tailles_fr(2);
        fichier<<endl<<"Triangles"<<endl<<O<<endl;
        for (int i=0; i<O; i++)
        {
            fichier<<D.triangles_fr()[i].sommet1()<<" "<<D.triangles_fr()[i].sommet2()<<" "<<D.triangles_fr()[i].sommet3()<<" "<<D.triangles_fr()[i].ref()<<endl;//revoir celon ce qui a été décidé dans la classe triangle
        }
        fichier<<endl<<"End"<<endl;
        fichier.close();
    }
    else
    {
        cout<<"le fichier n'a pas pu être ouvert, rien n'a été écrit"<<endl;
    }
}
