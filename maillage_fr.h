#ifndef MAILLAGE_FR_H_INCLUDED
#define MAILLAGE_FR_H_INCLUDED
#include "donnees.h"
#include "sommet2.h"

//void insert(donnees, float,float,float,float,float,float, const char*);
arete other_edge(arete a, triangle t1, triangle t2, donnees D);
triangle other_tri(triangle t, arete a);
//void swap(donnees, const char*);

#endif // MAILLAGE_FR_H_INCLUDED
