#ifndef AJOUTE_INDIVIDU_CALCU_FORCE_H_INCLUDED
#define AJOUTE_INDIVIDU_CALCU_FORCE_H_INCLUDED
#include <fstream>
#include <cmath>
#include "lecture.h"
#include "donnees.h"
#include "mate.h"
typedef float T;

T* distance_wall(T x, T y,donnees Donnees,int depart = 0);
T* first_distance_wall(T x, T y,donnees Donnees);
float* force_obj(individual*);
float* force_col(float f_max, float vx,float vy,float x1,float y1,float r,float x2,float y2);
float* first_force_mur(individual*, donnees);
float* force_mur(individual*, donnees);


#endif // AJOUTE_INDIVIDU_CALCU_FORCE_H_INCLUDED
