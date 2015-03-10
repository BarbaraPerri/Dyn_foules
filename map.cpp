#include "map.h"
#include <iostream>

using namespace std;


map<arete,triangle*> construit_map(arete* A,triangle*T, int T_arete, int T_tri)
{
    //cout<<"In the function construit_map."<<endl;
    map<arete,triangle*> map_voisinT;//the cle is the number of 2 sommets, return int* the number of 2 triangle
    triangle* array = new triangle[2]; //allocation dynamique d'un array.

    for(int i=0;i<T_arete;i++)
    {

        triangle* array = new triangle[2]; //allocation dynamique d'un array.
        //array[1] = -1;//give some strange int, because folloing some arete have only one tri
        int k = 0; //means the number of tri in the array.
        for(int j=0;j<T_tri;j++)
        {
            //cout<<"The "<<i<<" th arete is the edge of "<<j<<" th triangle?"<<T[j].have_edge(A[i])<<endl;
            if(T[j].have_edge(A[i])) //if the arete i is the edge of A
            {
                array[k] = T[j];
                k++;
            }
        }
        triangle* t = array;
        map_voisinT[A[i]]=t;
        //cout<<"Arete "<<endl;
        //A[i].print();
        //cout<<" have the triangles "<<endl;
        //map_voisinT[A[i]][0].print();
        //map_voisinT[A[i]][1].print();


     }//fin de la routine;

    //cout<<"Arete "<<endl;
    //A[0].print();
    //cout<<" have the triangles "<<endl;
    //map_voisinT[A[0]][0].print();
    //map_voisinT[A[0]][1].print();
    return(map_voisinT);
    delete []array;//delocaliser le tableau
}

void construit2_map(arete* A,triangle*T, int T_arete, int T_tri)
{
    //cout<<"In the function construit_map."<<endl;
    map<arete,int*> map_voisinT;//the cle is the number of 2 sommets, return int* the number of 2 triangle
    int* array = new int[2]; //allocation dynamique d'un array.
    for(int i=0;i<T_arete;i++)
    {

        int* array = new int[2]; //allocation dynamique d'un array.
        array[1] = -1;//give some strange int, because folloing some arete have only one tri
        int k = 0; //means the number of tri in the array.
        for(int j=0;j<T_tri;j++)
        {
            //cout<<"The "<<i<<" th arete is the edge of "<<j<<" th triangle?"<<T[j].have_edge(A[i])<<endl;
            if(T[j].have_edge(A[i])) //if the arete i is the edge of A
            {
                array[k] = j;
                k++;
            }
        }
        int* a = array;
        map_voisinT[A[i]]=a;
        //cout<<"Arete "<<endl;
        //A[i].print();
        //cout<<" have the triangles "<<array[0]<<" "<<array[1]<<endl;

    }//fin de la routine;
    //cout<<"Arete "<<0<<" have the triangles "<<map_voisinT[A[0]][0]<<" "<<map_voisinT[A[0]][1]<<endl;
    //cout<<"Arete "<<2<<" have the triangles "<<map_voisinT[A[2]][0]<<" "<<map_voisinT[A[2]][1]<<endl;

    delete []array;//delocaliser le tableau
}

map<int,int*> construit3_map(arete* A,triangle*T, int T_arete, int T_tri)
{
    //cout<<"In the function construit_map."<<endl;
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
            //cout<<"The "<<i<<" th arete is the edge of "<<j<<" th triangle?"<<T[j].have_edge(A[i])<<endl;
            if(T[j].have_edge(A[i])) //if the arete i is the edge of A
            {
                array[k] = j;
                k++;
            }
        }
        int* a = array;
        //int* b = new int[2];

        map_voisinT[i]=a;
//        cout<<"Arete "<<endl;
//        A[i].print();
//        cout<<" have the triangles "<<map_voisinT[i][0]<<" "<<map_voisinT[i][1]<<endl;

    }//fin de la routine;
    //cout<<"Fin de la routine."<<endl;
    //cout<<b[0]<<" "<<b[1]<<endl;
    //cout<<"Arete "<<0<<" have the triangles "<<map_voisinT[0][0]<<" "<<map_voisinT[0][1]<<endl;
//    int c[2] = {A[2].sommet1(),A[2].sommet2()};
    //cout<<"Arete "<<2<<" have the triangles "<<map_voisinT[2][0]<<" "<<map_voisinT[2][1]<<endl;

    delete []array;//delocaliser le tableau
    //delete []b;
    return map_voisinT;
}

