#ifndef ARETE_H_INCLUDED
#define ARETE_H_INCLUDED
#include "sommet2.h"
using namespace std;
class arete
{
private:
//premier point
int nb1;
int abs1;
int ord1;
//second point
int nb2;
int abs2;
int ord2;
//reference
int reference;
int num=-1;// signifie il est dans quel numéro de tableau
public:
//constructeurs
arete();
arete(int sommet1,int sommet2,int refer, sommet* Sommets);
//accesseurs
int sommet1() const {return(nb1);}
int x1() const {return(abs1);}
int y1() const {return(ord1);}
int sommet2() const {return(nb2);}
int x2() const {return(abs2);}
int y2() const {return(ord2);}
int ref() const {return(reference);}
int Num()const{return num;}
//fonctions membres
void print() const;
arete & operator =(arete &);
void Num(int number){num = number;}
};
bool operator == (arete,arete);
bool operator < (arete, arete);
bool compare (arete, arete);
#endif // ARETE_H_INCLUDED
