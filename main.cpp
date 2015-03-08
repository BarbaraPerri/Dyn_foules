#include <iostream>
#include "donnees.h"
#include "ajouter_individu.h"
#include <vector>
#include "ecriture.h"

using namespace std;

int main()
{
    donnees D= donnees("simple_geo.empty.mesh","simple_geo.back.mesh", "simple_geo.dist_wall.sol");
    D.ajouter_individu(15,15,30,30,70,0.5);
    //create_text(D,"test.mesh" );
    vector<sommet *> S=D.sommets_fr();
    cout<< S[1]->x()<<" "<<S[1]->y()<<endl;

    return 0;
}
