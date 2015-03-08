#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED
#include <map>
#include "arete.h"
#include "triangle.h"

std::map<arete, triangle*> create_map(arete*, triangle*, int*);

#endif // MAP_H_INCLUDED
