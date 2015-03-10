#include <iostream>
#include <fstream>
#include"lecture.h"
#include"ecriture.h"
//#include "routine_un_individu.h"

/*void force_individu(class individual & S, float Dt){

 if (S.ref()==0){

      float f_obj_x = S.gw()*( S.objx() - S.x() - S.vx() );
      float f_obj_y = S.gw()*( S.objy() - S.y() - S.vy() );

      float M = S.masse();

      float VX = S.vx() + (Dt/M)*f_obj_x;
      float VY = S.vy() + (Dt/M)*f_obj_y;
      float X = S.x() + Dt*VX;
      float Y = S.y() + Dt*VY;

      S.changer(X,Y,VX,VY,0);

 }

}*/

#include"calcu_force.h"

void force_individu(class individual* S, float Dt,donnees Donnees)
{
    if (S->ref()!=0)cerr<<"The sommet is not an individual."<<endl;

      float* f_obj=force_obj(S->vx(),S->vy(),S->objx(),S->objy(),S->gw());
      //float* f_col=force_col(S->fmax(),S->vx(),S->vy(),S->x(),S->y(),S->r(),float x2,float y2);
      float* f_mur=force_mur(S->fmax(), S->x(), S->y(),S->r(),Donnees,S->his_tri());
      float f_x = f_obj[0]+f_mur[0]; float f_y = f_obj[1]+f_mur[1];

      float M = S->masse();

      float VX = S->vx() + (Dt/M)*f_x;
      float VY = S->vy() + (Dt/M)*f_y;
      float X = S->x() + Dt*VX;
      float Y = S->y() + Dt*VY;

      S->changer(X,Y,VX,VY,0);
      int H_t=mate_bk(X,Y,Donnees,S->his_tri());
      S->his_tri(H_t);
}