#include <iostream>
#include "donnees.h"
#include <vector>
#include "ecriture.h"
#include "mate.h"
#include "calcu_force.h"
#include "maillage_fr.h"
#include "lecture.h"

#include "map.h"

using namespace std;

#define test_vector 0
#define test_donnees 0
#define test_sommets 0
#define test_ecriture 0

int main()
{
    //test pour comprendre vector --> ok
    if (test_vector==1)
    {
      cout<<"test vector"<<endl;
      vector<int> V;
      V.push_back(1);
      V.push_back(2);
      cout<<"premier élément de V : "<<V[0]<<endl;
      cout<<"premier élément de V : "<<V[1]<<endl<<endl;
    }


    donnees D=donnees("simple_geo.empty.mesh","simple_geo.back.mesh", "simple_geo.dist_wall.sol");

    //test des differents accesseurs. --> ok
    if (test_donnees==1)
    {
      cout<<"test donnees::tailles_fr"<<endl;
      cout<<"tailles_fr(0) renvoi: "<<D.tailles_fr(0)<<endl;
      cout<<"tailles_fr(1) renvoi: "<<D.tailles_fr(1)<<endl;
      cout<<"tailles_fr(2) renvoi: "<<D.tailles_fr(2)<<endl;

      cout<<"test donnees::tailles_bk"<<endl;
      cout<<"tailles_bk(0) renvoi: "<<D.tailles_bk(0)<<endl;
      cout<<"tailles_bk(1) renvoi: "<<D.tailles_bk(1)<<endl;
      cout<<"tailles_bk(2) renvoi: "<<D.tailles_bk(2)<<endl;

      cout<<"test de la liste de Sommets_fr:"<<endl;
    }

    int N=D.tailles_fr(0);

    if (test_sommets==1)
    {
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
       }
    }


    //tests d'ecriture --> ok
    if (test_ecriture==1)
    {
      create_text(D,"test1.mesh");
      D.ajouter_individu(15,15,30,30,70,0.5);
      create_text(D,"test2.mesh");
      distance_wall(15,15,D);
    }

    //sommet* S = new sommet(15,15,1);
    //D.ajouter_sommet(S);
    D.insert(60,2,70,0,2,3,"test_insert.mesh");
    //D.ajouter_sommet(15,15,0);
    create_text(D,"test_ajouter.mesh");
    //D.sommets_fr()[12]->print_sommet();
    //cout<<D.sommets_fr().size()<<endl;
    //D.aretes_fr()[23].print();
    D.swap("test_swap.mesh");
    //D.sommets_fr()[12]->print_sommet();
    //create_text(D,"test.mesh");


    //vector<sommet *> S=D.sommets_fr();
    //cout<< S[1]->x()<<" "<<S[1]->y()<<endl;

    return 0;
}
