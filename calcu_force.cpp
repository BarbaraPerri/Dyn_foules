#include <iostream>
#include <fstream>
#include <cmath>
#include "calcu_force.h"
#include "barycent.h"
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

T* distance_wall(T x, T y, donnees Donnees, int depart)//shall give its original position
{
    map<int,int*> map_voisinT_bk = Donnees.map_voisinT_bk();
    T** Sol_distance = Donnees.sol();
    int now = mate_bk(x,y,Donnees, depart);
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

float* force_obj(float vx,float vy,float obj_x,float obj_y,float g_w)
{
    float f_obj_x = g_w*(obj_x - vx);
    float f_obj_y = g_w*(obj_y - vy);
    float* f_obj = new float[2];
    f_obj[0] = f_obj_x;
    f_obj[1] = f_obj_y;
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

float* first_force_mur(float f_max, float x, float y,float r, donnees Donnees)
{
    float* d_w = first_distance_wall(x,y,Donnees);
    float f_mur_x = -f_max/(1+(d_w[0]/r)*(d_w[0]/r))*d_w[1];
    float f_mur_y = -f_max/(1+(d_w[0]/r)*(d_w[0]/r))*d_w[2];
    float* f_mur = new float[2];
    f_mur[0] = f_mur_x;
    f_mur[1] = f_mur_y;
    return f_mur;
}

float* force_mur(float f_max, float x, float y,float r, donnees Donnees, int depart)
{
    float* d_w = distance_wall(x,y,Donnees,depart);
    float f_mur_x = -f_max/(1+(d_w[0]/r)*(d_w[0]/r))*d_w[1];
    float f_mur_y = -f_max/(1+(d_w[0]/r)*(d_w[0]/r))*d_w[2];
    float* f_mur = new float[2];
    f_mur[0] = f_mur_x;
    f_mur[1] = f_mur_y;
    return f_mur;
}

