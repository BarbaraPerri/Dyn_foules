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
        int N=D.tailles_fr(0);
        fichier<<"Vertices"<<endl<<N<<endl;

        vector<sommet*> S=D.sommets_fr();
        for (int i=0; i<N; i++)
        {
            fichier<<S[i]->x()<<" "<<S[i]->y()<<" "<<S[i]->ref()<<endl;//revoir celon ce qui a été décidé dans la classe sommet
        }

        int M=D.tailles_fr(1);
        fichier<<endl<<"Edges"<<endl<<M<<endl;
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
        cerr<<"le fichier n'a pas pu être ouvert, rien n'a été écrit"<<endl;
    }
}
