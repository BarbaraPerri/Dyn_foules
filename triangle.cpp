#include "triangle.h"
#include <iostream>

using namespace std;

triangle::triangle()
{
    nb1 = 0;
    nb2 = 0;
    nb3 = 0;
    reference = 1;
    vivant = 1;
}

triangle::triangle(int sommet1, int sommet2, int sommet3, int refer)
{
    nb1 = sommet1;
    nb2 = sommet2;
    nb3 = sommet3;
    reference = refer;
    vivant = 1;
}

void triangle::print()
{
    cout<<nb1<<" "<<nb2<<" "<<nb3<<" "<<reference<<endl;
}

triangle & triangle::operator = (triangle t)
{
    nb1 = t.sommet1();
    nb2 = t.sommet2();
    nb3 = t.sommet3();
    reference = t.ref();
    return(*this);
}

bool triangle::have_edge(arete a)
{
    if(nb1 == a.sommet1())
    {
        if(nb2 == a.sommet2()) {return(true);}
        else
        {
            if(nb3 == a.sommet2()) {return(true);}
            else {return(false);}
        }
    }
    else if(nb1 == a.sommet2())
    {
        if(nb2 == a.sommet1()) {return(true);}
        else
        {
            if(nb3 == a.sommet1()) {return(true);}
            else {return(false);}
        }
    }
    else
    {
        if(nb2 == a.sommet1())
        {
            if(nb3 == a.sommet2()) {return(true);}
            else {return(false);}
        }
        else if(nb2 == a.sommet2())
        {
            if(nb3 == a.sommet1()) {return(true);}
            else {return(false);}
        }
        else {return(false);}
    }
}

bool operator == (triangle t1, triangle t2)
{
    if(t1.sommet1()==t2.sommet1() && t1.sommet2()==t2.sommet2() && t1.sommet3()==t2.sommet3() && t1.ref()==t2.ref())
    {
        return(true);
    }
    else {return(false);}
}

bool operator != (triangle t1, triangle t2)
{
    if(t1.sommet1()==t2.sommet1() && t1.sommet2()==t2.sommet2() && t1.sommet3()==t2.sommet3() && t1.ref()==t2.ref())
    {
        return(false);
    }
    else {return(true);}
}
