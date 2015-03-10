#ifndef MATE_H_INCLUDED
#define MATE_H_INCLUDED
#include <iostream>
#include "triangle.h"
#include "sommet2.h"
#include "lecture.h"
#include <map>
#include <stdlib.h>
#include <list>
#include "donnees.h"

using namespace std;
typedef float T; // define T as float

//////// On met le maillage au font et triangle les global

//T* barycent(float x,float y,triangle A);//A B C sont 3 sommets des triangles
T** grad_barycent(float x,float y,triangle A,donnees Donnees);

int mate_fr(T x, T y,map<int,int*> map_voisinT,donnees Donnees, int depart = 0);
int mate_bk(T x, T y,donnees Donnees, int depart = 0);
int first_mate_bk(T x, T y, donnees Donnees);

#endif // MATE_H_INCLUDED
