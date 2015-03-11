#include <iostream>
#include <cmath>
#include <cstdlib>
#include "sommet2.h"

using namespace std;

typedef float T;

sommet::sommet(){xx=0;yy=0;reff=0;}

void sommet::print()
{
  cout<<"Position: "<<xx<<"\t"<<yy<<endl;
  cout<<"Reference: "<<reff<<endl;
  cout<<"Number: "<<num<<endl;
}

void individual::print()
{
  cout<<"m,r,fmax,g:"<<endl;
  cout<<m<<"\t"<<rr<<"\t"<<f_max<<"\t"<<gg<<endl;
  cout<<"ref = "<<reff<<endl;
}

sommet & sommet::operator=(const sommet & S){
  xx=S.x();
  yy=S.y();
  reff=S.ref();
  return *this;
}

void sommet::changer(float x,float y,int r){
  xx=x;
  yy=y;
  reff=r;
}

void sommet::masse(float ma){
}

void sommet::g(float gw){
}

void sommet::objectif(float x, float y){
}

sommet::sommet(const sommet & s){
  reff=s.ref();
  xx=s.x();
  yy=s.y();
}

void sommet::rayon(float r){
}

void sommet::fmax(float f){
}


individual::individual(){
  reff=0;
  m=0;
  rr=0;
  f_max=0;
  gg=0;
  v_x=0;
  v_y=0;
  xx=0;
  yy=0;
  obj_x=0;
  obj_y=0;
}

void individual::masse(float ma){
  m=ma;
}

void individual::g(float gw){
  gg=gw;
}

individual::individual(const individual & i){
  reff=i.ref();
  m=i.masse();
  rr=i.r();
  f_max=i.fmax();
  xx=i.x();
  yy=i.y();
  v_x=i.vx();
  v_y=i.vy();
  gg=i.gw();
  obj_x=i.objx();
  obj_y=i.objy();
  voisins=i.vois();
}

void individual::objectif(float x, float y){
  obj_x=x;
  obj_y=y;
}

void individual::changer(float x, float y, float vx, float vy, int r){
  //cout<<"x = "<<x<<endl;
  xx=x;
  //cout<<"xx= "<<xx<<endl;
  yy=y;
  v_x=vx;
  v_y=vy;
  reff=r;
}

