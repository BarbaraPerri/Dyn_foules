#include <iostream>
#include "donnees.h"
#include <vector>
#include "ecriture.h"

using namespace std;

int main()
{
    donnees D=donnees("simple_geo.empty.mesh","simple_geo.back.mesh", "simple_geo.dist_wall.sol");

    //test des differents accesseurs.
    cout<<"test donnees::tailles_fr"<<endl;
    cout<<"tailles_fr(0) renvoi: "<<D.tailles_fr(0)<<endl;
    cout<<"tailles_fr(1) renvoi: "<<D.tailles_fr(1)<<endl;
    cout<<"tailles_fr(2) renvoi: "<<D.tailles_fr(2)<<endl;

    cout<<"test donnees::tailles_bk"<<endl;
    cout<<"tailles_bk(0) renvoi: "<<D.tailles_bk(0)<<endl;
    cout<<"tailles_bk(1) renvoi: "<<D.tailles_bk(1)<<endl;
    cout<<"tailles_bk(2) renvoi: "<<D.tailles_bk(2)<<endl;

    cout<<"test de la liste de Sommets_fr:"<<endl;

    //cette partie cause une erreur de segmentation, on ne peut acceder a aucun élément de vector<sommet *> Sommets_fr via les deux acceseurs que l'on a
    /*
    int N=D.tailles_fr(0);
    cout<<"liste Sommets_fr:"<<endl;
    for (int i=0; i<N; i++)
    {
      cout<<D.sommets_fr(i)->x()<<" "<<D.sommets_fr(i)->y()<<" "<<D.sommets_fr(i)->ref();
      if (D.sommets_fr(i)->ref()==0)
      {
        cout<<" vitesse: "<<D.sommets_fr(i)->vx()<<" "<<D.sommets_fr(i)->vy();
        cout<<" objectif: "<<D.sommets_fr(i)->objx()<<" "<<D.sommets_fr(i)->objy();
        cout<<" masse: "<<D.sommets_fr(i)->masse();
        cout<<" g: "<<D.sommets_fr(i)->gw();
      }
      cout<<endl;
    }*/

    //D.ajouter_individu(15,15,30,30,70,0.5);
    //create_text(D,"test.mesh" );
    //vector<sommet *> S=D.sommets_fr();
    //cout<< S[1]->x()<<" "<<S[1]->y()<<endl;

    return 0;
}
