#include "map.h"
#include <iostream>

using namespace std;


map<arete,triangle*> construit_map(arete* A,triangle*T, int T_arete, int T_tri)
{

    map<arete,triangle*> map_voisinT;//the cle is the number of 2 sommets, return int* the number of 2 triangle
    triangle* array = new triangle[2]; //allocation dynamique d'un array.

    for(int i=0;i<T_arete;i++)
    {

        triangle* array = new triangle[2]; //allocation dynamique d'un array.
        //array[1] = -1;//give some strange int, because folloing some arete have only one tri
        int k = 0; //means the number of tri in the array.
        for(int j=0;j<T_tri;j++)
        {
            if(T[j].have_edge(A[i])) //if the arete i is the edge of A
            {
                array[k] = T[j];
                k++;
            }
        }
        triangle* t = array;
        map_voisinT[A[i]]=t;
     }

    return(map_voisinT);
    delete []array;//delocaliser le tableau
}

void construit2_map(arete* A,triangle*T, int T_arete, int T_tri)
{
    map<arete,int*> map_voisinT;//the cle is the number of 2 sommets, return int* the number of 2 triangle
    int* array = new int[2]; //allocation dynamique d'un array.
    for(int i=0;i<T_arete;i++)
    {

        int* array = new int[2]; //allocation dynamique d'un array.
        array[1] = -1;//give some strange int, because folloing some arete have only one tri
        int k = 0; //means the number of tri in the array.
        for(int j=0;j<T_tri;j++)
        {
            if(T[j].have_edge(A[i])) //if the arete i is the edge of A
            {
                array[k] = j;
                k++;
            }
        }
        int* a = array;
        map_voisinT[A[i]]=a;

    }

    delete []array;//delocaliser le tableau
}

map<int,int*> construit3_map(arete* A,triangle*T, int T_arete, int T_tri)
{
    map<int,int*> map_voisinT;//the cle is the number of 2 sommets, return int* the number of 2 triangle
    int* array = new int[2]; //allocation dynamique d'un array.
    //int* b = new int[2];
    for(int i=0;i<T_arete;i++)
    {

        int* array = new int[2]; //allocation dynamique d'un array.
        array[1] = -1;//give some strange int, because folloing some arete have only one tri
        int k = 0; //means the number of tri in the array.
        for(int j=0;j<T_tri;j++)
        {
            if(T[j].have_edge(A[i])) //if the arete i is the edge of A
            {
                array[k] = j;
                k++;
            }
        }
        int* a = array;
        //int* b = new int[2];

        map_voisinT[i]=a;
    }
    delete []array;

    return map_voisinT;
}

