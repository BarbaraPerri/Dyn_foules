#include "lecture.h"
#include "sommet2.h"
#include "triangle.h"
#include "donnees.h"
#include "barycent.h"

extern donnees Donnees;

float* barycent(float x,float y,triangle A, donnees Donnees)//A B C sont 3 sommets des triangles
{
    //cout<<"In the barycent"<<endl;
    sommet pt_a = Donnees.sommets_bk()[A.sommet1()-1];
    //pt_a.print_sommet();
    sommet pt_b = Donnees.sommets_bk()[A.sommet2()-1];
    //pt_b.print_sommet();
    sommet pt_c = Donnees.sommets_bk()[A.sommet3()-1];
    //pt_c.print_sommet();

    float x_a = pt_a.x();
    float x_b = pt_b.x();
    float x_c = pt_c.x();
    float y_a = pt_a.y();
    float y_b = pt_b.y();
    float y_c = pt_c.y();
    float aire_abc = (x_b-x_c)*(y_c-y_a)-(x_c-x_a)*(y_b-y_c);
    float aire_pbc = (y_b-y_c)*(x-x_c)-(x_b-x_c)*(y-y_c);
    float aire_pca = (y_c-y_a)*(x-x_a)-(x_c-x_a)*(y-y_a);
    float aire_pab = (y_a-y_b)*(x-x_b)-(x_a-x_b)*(y-y_b);
    float lambda_A = aire_pbc/aire_abc;
    float lambda_B = aire_pca/aire_abc;
    float lambda_C = aire_pab/aire_abc;
    float* lambda = new float[3];
    lambda[0] = lambda_A;
    lambda[1] = lambda_B;
    lambda[2] = lambda_C;
    //cout<<lambda[0]<<" "<<lambda[1]<<" "<<lambda[2]<<" "<<endl;
    return lambda;//return un tableau de 3 elements
    //delete []lambda;Ne détuit pas
}
