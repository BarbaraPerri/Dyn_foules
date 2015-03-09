#include "arete.h"
#include <iostream>
#include <math.h>

using namespace std;

arete::arete()
{
    nb1 = 0;
    nb2 = 0;
    reference = 0;
}

arete::arete(int sommet1, int sommet2, int refer, sommet* Sommets)
{
    nb1 = sommet1;
    abs1 = Sommets[nb1-1].x();
    ord1 = Sommets[nb1-1].y();
    nb2 = sommet2;
    abs2 = Sommets[nb2-1].x();
    ord2 = Sommets[nb2-1].y();
    reference = refer;
}

void arete::print() const
{
    cout<<nb1<<" "<<nb2<<" "<<reference<<endl;
}

arete & arete::operator = (arete & a)
{
    nb1 = a.sommet1();
    nb2 = a.sommet2();
    reference = a.ref();
    return (*this);
}

bool operator == (arete a,arete b)
{
    if(((a.sommet1()==b.sommet1())&&(a.sommet2()==b.sommet2()))||((a.sommet1()==b.sommet2())&&(a.sommet2()==b.sommet1())))
       {return true;}
    else {return false;}
}

bool operator < (arete a, arete b)
{
    if(a.sommet1() < b.sommet1()) {return(true);}
    else if(a.sommet1() == b.sommet1())
    {
        if(a.sommet2()<b.sommet2()) {return(true);}
        else {return(false);}
    }
    else {return(false);}
}

bool compare (arete a, arete b)
{
    int d_a = sqrt((a.x2()-a.x1())*(a.x2()-a.x1())+(a.y2()-a.y1())*(a.y2()-a.y1()));
    int d_b = sqrt((b.x2()-b.x1())*(b.x2()-b.x1())+(b.y2()-b.y1())*(b.y2()-b.y1()));
    if(d_a<d_b) {return(true);}
    else {return(false);}
}
