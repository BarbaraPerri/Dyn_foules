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
T** grad_barycent(float x,float y,triangle A);

int mate_fr(T x, T y,map<int,int*> map_voisinT, int depart = 0);

int mate_bk(T x, T y, int depart = 0);

#endif // MATE_H_INCLUDED
