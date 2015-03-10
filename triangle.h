#ifndef TRIANGLE_H_INCLUDED
#define TRIANGLE_H_INCLUDED
#include "arete.h"

class triangle
{
    private:

    int nb1;
    int nb2;
    int nb3;
    int reference;

    public:

    int vivant;
    triangle();
    triangle(int val1, int val2, int val3, int ref);
    void print();
    int sommet1() const {return(nb1);}
    int sommet2() const {return(nb2);}
    int sommet3() const {return(nb3);}
    int ref() const {return(reference);}
    triangle & operator = (triangle);
    bool have_edge(arete);
};
bool operator == (triangle, triangle);
bool operator != (triangle, triangle);

#endif // TRIANGLE_H_INCLUDED
