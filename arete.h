#ifndef ARETE_H_INCLUDED
#define ARETE_H_INCLUDED

using namespace std;

class arete
{
    private:

    int nb1;
    int nb2;
    int reference;

    public:

    arete();
    arete(int sommet1,int sommet2,int refer);
    int sommet1() const {return(nb1);}
    int sommet2() const {return(nb2);}
    int ref() const {return(reference);}
    void print();
};

#endif // ARETE_H_INCLUDED
