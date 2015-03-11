#include <iostream>
#include <fstream>
#include <cmath>
#include "calcu_force.h"
#include "barycent.h"
#include "donnees.h"
typedef float T;


T* distance_wall(T x, T y, donnees Donnees, int depart)//shall give its original position
{
    //cout<<endl<<"In the function dist_wall "<<endl;
    map<int,int*> map_voisinT_bk = Donnees.map_voisinT_bk();
    T** Sol_distance = Donnees.sol();
    int now = mate_bk(x,y,Donnees, depart);// the point is in the nowth tri

    //cout<<"This position is in the "<<now<<"th triangle."<<endl;
    triangle tri = Donnees.triangles_bk()[now];

    //tri.print();
    //////////////////// now is to find the nearest sommet in the triangle //////////////////////////////
    sommet pt_a = Donnees.sommets_bk()[tri.sommet1()-1];
    //pt_a.print_sommet();
    sommet pt_b = Donnees.sommets_bk()[tri.sommet2()-1];
    //pt_b.print_sommet();
    sommet pt_c = Donnees.sommets_bk()[tri.sommet3()-1];
    //pt_c.print_sommet();

    T x_tri[3]; T y_tri[3];
    x_tri[0] = pt_a.x();x_tri[1] = pt_b.x();x_tri[2] = pt_c.x();
    y_tri[0] = pt_a.y();y_tri[1] = pt_b.y();y_tri[2] = pt_c.y();
    T dist_pt[3];
    dist_pt[0] = Sol_distance[tri.sommet1()-1][1];
    dist_pt[1] = Sol_distance[tri.sommet2()-1][1];
    dist_pt[2] = Sol_distance[tri.sommet3()-1][1];
    //cout<<"The distances of the 3 points of the triangle are:"<<endl;
    //cout<<dist_pt[0]<<"    "<<dist_pt[1]<<"    "<<dist_pt[2]<<"    "<<endl;

    T* lambda = barycent_bk(x,y,tri,Donnees);
    //cout<<"lambda verified"<<endl;
    T** grad_lambda = grad_barycent(x,y,tri,Donnees);
    //cout<<"grad_lambda verified"<<endl;

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

T* first_distance_wall(T x, T y,donnees Donnees)
{
    T** Sol_distance = Donnees.sol();
    int now = first_mate_bk(x,y,Donnees);// the point is in the nowth tri

    triangle tri = Donnees.triangles_bk()[now];
    //////////////////// now is to find the nearest sommet in the triangle //////////////////////////////
    sommet pt_a = Donnees.sommets_bk()[tri.sommet1()-1];
    sommet pt_b = Donnees.sommets_bk()[tri.sommet2()-1];
    sommet pt_c = Donnees.sommets_bk()[tri.sommet3()-1];

    T x_tri[3]; T y_tri[3];
    x_tri[0] = pt_a.x();x_tri[1] = pt_b.x();x_tri[2] = pt_c.x();
    y_tri[0] = pt_a.y();y_tri[1] = pt_b.y();y_tri[2] = pt_c.y();
    T dist_pt[3];
    dist_pt[0] = Sol_distance[tri.sommet1()-1][1];
    dist_pt[1] = Sol_distance[tri.sommet2()-1][1];
    dist_pt[2] = Sol_distance[tri.sommet3()-1][1];

    T* lambda = barycent_bk(x,y,tri,Donnees);
    T** grad_lambda = grad_barycent(x,y,tri,Donnees);

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

float* force_obj(individual* S)
{
    float* f_obj = new float[2];
    f_obj[0] = S->gw()*(S->objx() - S->x() - S->vx());
    f_obj[1] = S->gw()*(S->objy() - S->y() - S->vy());
    return f_obj;
}

float* force_col(float f_max, float vx,float vy,float x1,float y1,float r,float x2,float y2)
{
    float s_x = x2-x1;float s_y = y2-y1;
    float dist = s_x*s_x+s_y*s_y;dist = sqrt(dist);
    s_x = s_x/dist;s_y = s_y/dist;
    float rho = dist/r;
    float* f_col = new float[2];
    f_col[0] = -f_max*s_x/(1+rho*rho);f_col[1] = -f_max*s_y/(1+rho*rho);
    return f_col;
}

float* first_force_mur(individual* I, donnees Donnees)
{
    float* d_w = first_distance_wall(I->x(),I->y(),Donnees);
    float* f_mur = new float[2];
    f_mur[0] = -I->fmax()/(1+(d_w[0]/I->r())*(d_w[0]/I->r()))*d_w[1];
    f_mur[1] = -I->fmax()/(1+(d_w[0]/I->r())*(d_w[0]/I->r()))*d_w[2];
    return f_mur;
}

float* force_mur(individual* I, donnees Donnees)
{
    float* d_w = distance_wall(I->x(),I->y(),Donnees,I->his_tri());
    float* f_mur = new float[2];
    f_mur[0] = -I->fmax()/(1+(d_w[0]/I->r())*(d_w[0]/I->r()))*d_w[1];
    f_mur[1] = -I->fmax()/(1+(d_w[0]/I->r())*(d_w[0]/I->r()))*d_w[2];
    return f_mur;
}

