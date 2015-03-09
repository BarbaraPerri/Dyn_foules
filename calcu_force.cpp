#include <iostream>
#include <fstream>
#include <cmath>
#include "calcu_force.h"
#include "barycent.h"
//#include "ecriture.h"
extern donnees Donnees;

typedef float T;

void force_individu(class individual & S, float Dt)
{
    if (S.ref()==0)
    {
        float f_obj_x = S.gw()*( S.objx() - S.x() - S.vx() );
        float f_obj_y = S.gw()*( S.objy() - S.y() - S.vy() );
        float M = S.masse();
        float VX = S.vx() + (Dt/M)*f_obj_x;
        float VY = S.vy() + (Dt/M)*f_obj_y;
        float X = S.x() + Dt*VX;
        float Y = S.y() + Dt*VY;
        S.changer(X,Y,VX,VY,0);
    }
}

T* distance_wall(T x, T y, int depart, donnees Donnees)//shall give its original position
{
    cout<<endl<<"In the function dist_wall "<<endl;
    map<int,int*> map_voisinT_bk = Donnees.map_voisinT_bk();
    T** Sol_distance = Donnees.sol();
    int now = mate_bk(x,y, depart);// the point is in the nowth tri

    cout<<"This position is in the "<<now<<"th triangle."<<endl;
    triangle tri = Donnees.triangles_bk()[now];

    tri.print();
    //////////////////// now is to find the nearest sommet in the triangle //////////////////////////////
    sommet pt_a = Donnees.sommets_bk()[tri.sommet1()-1];
    sommet pt_b = Donnees.sommets_bk()[tri.sommet2()-1];
    sommet pt_c = Donnees.sommets_bk()[tri.sommet3()-1];
    T x_tri[3]; T y_tri[3];
    x_tri[0] = pt_a.x();x_tri[1] = pt_b.x();x_tri[2] = pt_c.x();
    y_tri[0] = pt_a.y();y_tri[1] = pt_b.y();y_tri[2] = pt_c.y();
    T dist_pt[3];
    dist_pt[0] = Sol_distance[pt_a.Num()][1];
    dist_pt[1] = Sol_distance[pt_b.Num()][1];
    dist_pt[2] = Sol_distance[pt_c.Num()][1];
    cout<<"The distances of the 3 points of the triangle are:"<<endl;
    cout<<dist_pt[0]<<"    "<<dist_pt[1]<<"    "<<dist_pt[2]<<"    "<<endl;

    T* lambda = barycent(x,y,tri,Donnees);
    cout<<"lambda verified"<<endl;
    T** grad_lambda = grad_barycent(x,y,tri);
    cout<<"grad_lambda verified"<<endl;

    T dist=0;T grad_d_x=0;T grad_d_y=0;
    for(int i=0;i<3;i++)
    {
        dist+=lambda[i]*dist_pt[i];
    }

    for(int i=0;i<3;i++)
    {
        grad_d_x+=grad_lambda[0][i]*dist_pt[i];
        grad_d_y+=grad_lambda[1][i]*dist_pt[i];
    }

    T* dist_grad_d = new T[3]; dist_grad_d[0] = dist; dist_grad_d[1] = grad_d_x; dist_grad_d[2] = grad_d_y;

    cout<<"The distance from ("<<x<<","<<y<<") to wall is: "<<dist_grad_d[0]<<"    "<<dist_grad_d[1]<<"    "<<dist_grad_d[2]<<endl;
    return dist_grad_d;
}


