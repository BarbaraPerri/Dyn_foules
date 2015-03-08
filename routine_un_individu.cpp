#include <iostream>
#include <fstream>
#include"lecture.h"
#include"ecriture.h"
#include "routine_un_individu.h"

void force_individu(struct donnees & D, char * nomfichier, float Dt){
  int N=D.tailles_fr(0);
  for (int i=0; i<N; i++){
    if (D.sommets_fr()[i]->ref()==0){
/*      float f_obj_1=D.Sommets_fr[i].gw()*(D.Sommets_fr[i].vdx() - D.Sommets_fr[i].vx());
      float f_obj_2=D.Sommets_fr[i].gw()*(D.Sommets_fr[i].vdy() - D.Sommets_fr[i].vy());
      float M=D.Sommets_fr[i].m();
      D.Sommets_fr[i].vx((Dt/M)*f_obj_1);//vx() agit comme vx+=
      D.Sommets_fr[i].vy((Dt/M)*f_obj_2);
      float X=D.Sommets_fr[i].x() + Dt*D.Sommets_fr[i].vx();//x() accesseur
      float Y=D.Sommets_fr[i].y() + Dt*D.Sommets_fr[i].vy();
      D.Sommets_fr[i].changer(X,Y,0);
*/
      //mise a jour de vd
    }
  }
  create_text(D,nomfichier);
}
