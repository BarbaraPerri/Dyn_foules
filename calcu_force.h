#ifndef AJOUTE_INDIVIDU_CALCU_FORCE_H_INCLUDED
#define AJOUTE_INDIVIDU_CALCU_FORCE_H_INCLUDED
#include <fstream>
#include <cmath>
#include "lecture.h"
#include "donnees.h"
#include "mate.h"
typedef float T;

void force_individu(class individual & , float );
T* distance_wall(T x, T y,donnees Donnees,int depart = 0);
T* first_distance_wall(T x, T y,donnees Donnees);
float* force_obj(float vx,float vy,float obj_x,float obj_y,float g_w);
float* force_col(float f_max, float vx,float vy,float x1,float y1,float r,float x2,float y2);
float* first_force_mur(float f_max, float x, float y,float r, donnees Donnees);
float* force_mur(float f_max, float x, float y,float r, donnees Donnees, int depart);


#endif // AJOUTE_INDIVIDU_CALCU_FORCE_H_INCLUDED
