#include "donnees.h"
#include "lecture.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include "map.h"
#include "barycent.h"
#include "ecriture.h"
#include "maillage_fr.h"
#include "mate.h"

using namespace std;

donnees::donnees(const char* mesh, const char* back_mesh, const char* sol)
{
  Tailles_fr = lecture_mesh_tailles(mesh);
  Aretes_fr = new arete[Tailles_fr[1]];
  Triangles_fr = new triangle[Tailles_fr[2]];
  lecture_mesh(mesh, Sommets_fr, Aretes_fr, Triangles_fr);
  Tailles_bk = lecture_mesh_tailles(back_mesh);
  Sommets_bk = new sommet[Tailles_bk[0]];
  Aretes_bk = new arete[Tailles_bk [1]];
  Triangles_bk = new triangle[Tailles_bk [2]];
  lecture_back_mesh(back_mesh, Sommets_bk , Aretes_bk, Triangles_bk);
  inner_aretes_fr();
  inner_aretes_bk();
  Map_voisinT_bk = construit3_map(Aretes_bk, Triangles_bk, Tailles_bk[1], Tailles_bk[2]);
  Sol = lecture_sol(sol);
  Reper_fr = construit_map(Aretes_fr, Triangles_fr, Tailles_fr[1], Tailles_fr[2]);
  //Reper_bk = construit_map(Aretes_bk, Triangles_bk, Tailles_bk[1], Tailles_bk[2]);
}


//accesseurs

int donnees::tailles_fr(int i)
{
  return Tailles_fr[i];
}

int donnees::tailles_bk(int i)
{
  return Tailles_bk[i];
}

sommet* donnees::sommets_fr(int i){
  return Sommets_fr[i];
}


//fonctions de modification

void donnees::sommets_fr(vector<sommet*> S){
  Sommets_fr=S;
}

void donnees::tailles_fr(int a, int b){
    Tailles_fr[b]=a;
}

void donnees::ajouter_sommet(sommet* S)
{
    //sommet* S = new sommet(x, y, ref);
    //S.changer(x,y,0);
    Sommets_fr.push_back(S);
    Tailles_fr[0]++;
}


void donnees::ajouter_individu(int i)
{
    Tailles_fr[0]++;
    individual *I = new individual;

    float x, y, objx, objy, gw, m;
    cout<<"Veuillez saisir l'abscisse de l'individu "<<i<<":"<<endl;
    cin>>x;
    cout<<"son ordonnée:"<<endl;
    cin>>y;
    cout<<"l'abscisse de son objectif:"<<endl;
    cin>>objx;
    cout<<"l'ordonnée de son objectif:"<<endl;
    cin>>objy;
    cout<<"sa masse:"<<endl;
    cin>>m;
    cout<<"son indice gw:"<<endl;
    cin>>gw;

    I->changer(x,y,(float)0,(float)0,0);
    I->objectif(objx,objy);
    I->g(gw);
    I->masse(m);
    int H_t = first_mate_bk(x, y, *this);
    I->his_tri(H_t);
    Sommets_fr.push_back(I);

}

void donnees::ajouter_individu(float x,float y,float objx, float objy, float m, float gw)
{
    Tailles_fr[0]++;
    individual *I = new individual;
    I->changer(x,y,(float)0,(float)0,0);
    I->objectif(objx,objy);
    I->g(gw);
    I->masse(m);
    int H_t = first_mate_bk(x, y, *this);
    I->his_tri(H_t);
    Sommets_fr.push_back(I);

}


void donnees::ajouter_arete_fr(arete a)
{
    Tailles_fr[1]++;
    arete * A = new arete[Tailles_fr[1]];

    for (int i=0; i<(Tailles_fr[1] -1); i++)
    {
    A[i]=Aretes_fr[i];
    }

    A[Tailles_fr[1]-1] = a;
    arete * tmp = Aretes_fr;
    Aretes_fr = A;
    delete [] tmp;
}

void donnees::enlever_arete(arete a)
{
    int i=0;
    while(Aretes_fr[i]!=a)
    {
        i=i+1;
    }

    Tailles_fr[1]--;
    arete* A = new arete[Tailles_fr[1]];
    for (int j=0; j<i; j++)
    {
    A[j]=Aretes_fr[j];
    }
    for (int j=i+1; j<=Tailles_fr[1]; j++)
    {
    A[j-1]=Aretes_fr[j];
    }
    arete * tmp = Aretes_fr;
    Aretes_fr = A;
    delete [] tmp;
}

void donnees::ajouter_arete_bk(arete a)
{
    Tailles_bk[1]++;
    arete * A = new arete[Tailles_bk[1]];

    for (int i=0; i<(Tailles_bk[1] -1); i++)
    {
    A[i]=Aretes_bk[i];
    }

    A[Tailles_bk[1]-1] = a;
    arete * tmp = Aretes_bk;
    Aretes_bk = A;
    delete [] tmp;
}


void donnees::ajouter_triangle(triangle t)
{
    Tailles_fr[2]++;
    triangle * T = new triangle[Tailles_fr[2]];

    for (int i=0; i<(Tailles_fr[2] -1); i++)
    {
    T[i]=Triangles_fr[i];
    }

    T[Tailles_fr[2]-1] = t;
    triangle * tmp = Triangles_fr;
    Triangles_fr = T;
    delete [] tmp;
}

void donnees::enlever_triangle(int i)
{
    Tailles_fr[2]--;
    triangle* T = new triangle[Tailles_fr[2]];
    for (int j=0; j<i; j++)
    {
    T[j]=Triangles_fr[j];
    }
    for (int j=i+1; j<=Tailles_fr[2]; j++)
    {
    T[j-1]=Triangles_fr[j];
    }
    triangle * tmp = Triangles_fr;
    Triangles_fr = T;
    delete [] tmp;
}
void donnees::enlever_triangle(triangle t)
{
    int i=0;
    while(Triangles_fr[i]!=t)
    {
        i=i+1;
    }

    Tailles_fr[2]--;
    triangle* T = new triangle[Tailles_fr[2]];
    for (int j=0; j<i; j++)
    {
    T[j]=Triangles_fr[j];
    }
    for (int j=i+1; j<=Tailles_fr[2]; j++)
    {
    T[j-1]=Triangles_fr[j];
    }
    triangle * tmp = Triangles_fr;
    Triangles_fr = T;
    delete [] tmp;
}

void donnees::update_map(map<arete, triangle*> reper)
{
    Reper_fr = reper;
}

void donnees::print_map_fr()
{
    cout<<"APPEL A L IMPRESSION DE MAP"<<endl;
    triangle* val = new triangle[2];
    for (int i=0;i<Tailles_fr[1]; i++)

    {
        cout<<"impression de l'arete"<<endl;
        Aretes_fr[i].print();

        cout<<"impression du premier triangle"<<endl;
        Reper_fr[Aretes_fr[i]][0].print();
        cout<<"impression du second triangle"<<endl;
        Reper_fr[Aretes_fr[i]][1].print();
    }
    cout<<"FIN DE L APPEL A L IMPRESSION DE MAP"<<endl;
}

void donnees::inner_aretes_fr()
{
    int T_arete = Tailles_fr[1];
    int T_tri = Tailles_fr[2];
    arete* A = Aretes_fr;
    triangle* T = Triangles_fr;
    for(int i=0;i<T_tri;i++)
    {
        int array[2] = {-1,-1}; //array stores the edge that is contour of triangle.
        arete bord1(T[i].sommet1(),T[i].sommet2(),3, Sommets_fr);
        arete bord2(T[i].sommet2(),T[i].sommet3(),3, Sommets_fr);
        arete bord3(T[i].sommet3(),T[i].sommet1(),3, Sommets_fr);


        ////////////////// for construction the array in which the bord of contour is included //////////////////////

        int k = 0;
        for(int j=0;j<T_arete;j++)
        {
            if(T[i].have_edge(A[j]))
            {
                array[k]=j;
                k++;
            }
        }

        ///////////////// end of construction the array in which the bord of contour is included ///////////////////
        ///////////////// begin adding the aretes into the table arete* //////////////////////
        int a = array[0]; int b = array[1];
        if((a>=0)&&(b>=0))
        {

            if((!(bord1==A[a]))&&(!(bord1==A[b]))&&(!(existed_arete(bord1,Aretes_fr,Tailles_fr[1]))))
                {ajouter_arete_fr(bord1);
                }
            else if((!(bord2==A[a]))&&(!(bord2==A[b]))&&(!(existed_arete(bord2,Aretes_fr,Tailles_fr[1]))))
                {
                 ajouter_arete_fr(bord2);
                 }
            else if((!(bord3==A[a]))&&(!(bord3==A[b]))&&(!(existed_arete(bord3,Aretes_fr,Tailles_fr[1]))))
                {
                 ajouter_arete_fr(bord3);
                 }

        //////////////////////////// here we shall add the construction map //////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        }
        else if(a>0)
        {
            if(bord1==A[a])
                {
                    if(!existed_arete(bord2,Aretes_fr,Tailles_fr[1]))ajouter_arete_fr(bord2);
                    if(!existed_arete(bord3,Aretes_fr,Tailles_fr[1]))ajouter_arete_fr(bord3);
                 }
            else if((bord2==A[a])&&(!existed_arete(bord2,Aretes_fr,Tailles_fr[1])))
                {
                    if(!existed_arete(bord3,Aretes_fr,Tailles_fr[1]))ajouter_arete_fr(bord3);
                    if(!existed_arete(bord1,Aretes_fr,Tailles_fr[1]))ajouter_arete_fr(bord1);
                }
            else if((bord3==A[a])&&(!existed_arete(bord3,Aretes_fr,Tailles_fr[1])))
                {
                    if(!existed_arete(bord1,Aretes_fr,Tailles_fr[1]))ajouter_arete_fr(bord1);
                    if(!existed_arete(bord2,Aretes_fr,Tailles_fr[1]))ajouter_arete_fr(bord2);
                 }
        }
        else
        {
            if(!existed_arete(bord1,Aretes_fr,Tailles_fr[1]))ajouter_arete_fr(bord1);
            if(!existed_arete(bord2,Aretes_fr,Tailles_fr[1]))ajouter_arete_fr(bord2);
            if(!existed_arete(bord3,Aretes_fr,Tailles_fr[1]))ajouter_arete_fr(bord3);
        }
    }
}

void donnees::inner_aretes_bk()
{
    int T_arete = Tailles_bk[1];
    int T_tri = Tailles_bk[2];
    arete* A=Aretes_bk;
    triangle* T=triangles_bk();
    //cout<<"In the function inner_arete:"<<endl;
    //int array[2] = {-1,-1}; //array stores the edge that is contour of triangle.
    for(int i=0;i<T_tri;i++)
    {
        //cout<<"Check the "<<i<<"th triangle"<<endl;
        int array[2] = {-1,-1}; //array stores the edge that is contour of triangle.
        //cout<<"The first arete:"<<endl;
        arete bord1(T[i].sommet1(),T[i].sommet2(),3, Sommets_bk);//bord1.print();
        //cout<<"The second arete:"<<endl;
        arete bord2(T[i].sommet2(),T[i].sommet3(),3, Sommets_bk);//bord2.print();
        //cout<<"The third arete:"<<endl;
        arete bord3(T[i].sommet3(),T[i].sommet1(),3, Sommets_bk);//bord3.print();


        ////////////////// for construction the array in which the bord of contour is included //////////////////////

        int k = 0;
        for(int j=0;j<T_arete;j++)
        {
            if(T[i].have_edge(A[j]))
            {
                array[k]=j;//the ith arete is the contour and is the edge of T[j]
                //cout<<"Edge "<<array[k]<<" is the bord of trianglr "<<i<<endl;
                k++;
                //if(k=3) cerr<<"The 3 edge of the triangle are all contours."<<endl;
            }
        }
        //cout<<"Edges of triangle "<<i<<" which have bords"<<array[0]<<" "<<array[1]<<endl;

        ///////////////// end of construction the array in which the bord of contour is included ///////////////////
        ///////////////// begin adding the aretes into the table arete* //////////////////////
        int a = array[0]; int b = array[1];
        if((a>=0)&&(b>=0))
        {
            //cout<<"Triangle "<<i<<" has 2 bords of contours."<<endl;

            if((!(bord1==A[a]))&&(!(bord1==A[b]))&&(!(existed_arete(bord1,Aretes_bk,Tailles_bk[1]))))//If we have found the answer
                {ajouter_arete_bk(bord1);
                //cout<<"Now the size of aretes are "<<Donnees.Tailles_bk[1]<<endl;
                }
            else if((!(bord2==A[a]))&&(!(bord2==A[b]))&&(!(existed_arete(bord2,Aretes_bk,Tailles_bk[1]))))
                {//cout<<"Bord2 of triangle "<<i<<" is the inner arete, added in arete*"<<endl;
                 ajouter_arete_bk(bord2);//cout<<"Now the size of aretes are "<<Donnees.Tailles_bk[1]<<endl;
                 }
            else if((!(bord3==A[a]))&&(!(bord3==A[b]))&&(!(existed_arete(bord3,Aretes_bk,Tailles_bk[1]))))
                {//cout<<"Bord3 of triangle "<<i<<" is the inner arete, added in arete*"<<endl;
                 ajouter_arete_bk(bord3);//cout<<"Now the size of aretes are "<<Donnees.Tailles_bk[1]<<endl;
                 }
        }
        else if(a>0)
        {
            //cout<<"Triangle "<<i<<" has 1 bords of contours."<<endl;
            if(bord1==A[a])//We have found the answer
                {
                    if(!existed_arete(bord2,Aretes_bk,Tailles_bk[1]))ajouter_arete_bk(bord2);//cout<<"Now the size of aretes are "<<Donnees.Tailles_bk[1]<<endl;
                    if(!existed_arete(bord3,Aretes_bk,Tailles_bk[1]))ajouter_arete_bk(bord3);//cout<<"Now the size of aretes are "<<Donnees.Tailles_bk[1]<<endl;
                 //cout<<"Bord2,3 of triangle "<<i<<" is the inner arete, added in arete*"<<endl;
                 }
            else if((bord2==A[a])&&(!existed_arete(bord2,Aretes_bk,Tailles_bk[1])))
                {
                    if(!existed_arete(bord3,Aretes_bk,Tailles_bk[1]))ajouter_arete_bk(bord3);//cout<<"Now the size of aretes are "<<Donnees.Tailles_bk[1]<<endl;
                    if(!existed_arete(bord1,Aretes_bk,Tailles_bk[1]))ajouter_arete_bk(bord1);//cout<<"Now the size of aretes are "<<Donnees.Tailles_bk[1]<<endl;
                //cout<<"Bord3,1 of triangle "<<i<<" is the inner arete, added in arete*"<<endl;
                }
            else if((bord3==A[a])&&(!existed_arete(bord3,Aretes_bk,Tailles_bk[1])))
                {
                    if(!existed_arete(bord1,Aretes_bk,Tailles_bk[1]))ajouter_arete_bk(bord1);//cout<<"Now the size of aretes are "<<Donnees.Tailles_bk[1]<<endl;
                 //if(Donnees.Aretes_bk[0].Num()>0){cout<<"It's bord1 who makes fault."<<endl;break;}
                    if(!existed_arete(bord2,Aretes_bk,Tailles_bk[1]))ajouter_arete_bk(bord2);//cout<<"Now the size of aretes are "<<Donnees.Tailles_bk[1]<<endl;
                 //cout<<"Bord1,2 of triangle "<<i<<" is the inner arete, added in arete*"<<endl;
                 }
        }
        else //the triangle is totally inner
        {
            if(!existed_arete(bord1,Aretes_bk,Tailles_bk[1]))ajouter_arete_bk(bord1);//cout<<"Now the size of aretes are "<<Donnees.Tailles_bk[1]<<endl;
            if(!existed_arete(bord2,Aretes_bk,Tailles_bk[1]))ajouter_arete_bk(bord2);//cout<<"Now the size of aretes are "<<Donnees.Tailles_bk[1]<<endl;
            if(!existed_arete(bord3,Aretes_bk,Tailles_bk[1]))ajouter_arete_bk(bord3);//cout<<"Now the size of aretes are "<<Donnees.Tailles_bk[1]<<endl;
            //cout<<"Bord1,2,3 of triangle "<<i<<" is the inner arete, added in arete*"<<endl;
        }
    }
    //cout<<"The end of inner_aretes "<<endl<<endl;
}

void donnees::insert(int i/*, const char* fichier*/)
{

    float x, y, objx, objy, gw, m;
    cout<<"Veuillez saisir l'abscisse de l'individu "<<i<<":"<<endl;
    cin>>x;
    cout<<"son ordonnée:"<<endl;
    cin>>y;
    cout<<"l'abscisse de son objectif:"<<endl;
    cin>>objx;
    cout<<"l'ordonnée de son objectif:"<<endl;
    cin>>objy;
    cout<<"sa masse:"<<endl;
    cin>>m;
    cout<<"son indice gw:"<<endl;
    cin>>gw;
    ajouter_individu(x,y,objx,objy,m,gw);
    //on ajoute les coordonnees de l'individu dans le tableau des sommets front
    //le numero de l'individu est donc tailles_fr[0]

    float* coor_bar; //on cree le tableau des coordonnees barycentriques
    for(int i=0;i<Tailles_fr[2];i++) //boucle sur les triangles du maillage front
    {
        coor_bar = barycent_fr(x, y, Triangles_fr[i],*this);
        //on recupere les coordonnees barycentriques de l'individu par rapport au triangle en cours
        if(coor_bar[0]>0 && coor_bar[1]>0 && coor_bar[2]>0) //on se place dans le triangle où est l'individu
        {
            triangle tr = Triangles_fr[i];
            arete a = arete(Tailles_fr[0], tr.sommet1(),0, Sommets_fr);
            arete b = arete(Tailles_fr[0], tr.sommet2(),0, Sommets_fr);
            arete c = arete(Tailles_fr[0], tr.sommet3(),0, Sommets_fr);
            //on cree les trois nouvelles aretes
            ajouter_arete_fr(a);
            ajouter_arete_fr(b);
            ajouter_arete_fr(c);
            //on les ajoute dans les donnees
            triangle t1 = triangle(Tailles_fr[0], tr.sommet2(), tr.sommet3(), 1);
            triangle t2 = triangle(tr.sommet1(), Tailles_fr[0], tr.sommet3(), 1);
            triangle t3 = triangle(tr.sommet1(), tr.sommet2(), Tailles_fr[0], 1);
            //on cree les trois nouveaux triangles, orientes dans le bon sens (permutation)
            enlever_triangle(i);
            //D.triangles_fr()[i].vivant = 0; //on tue le triangle qui a disparu, remplace par les nouveaux triangles
            ajouter_triangle(t1);
            ajouter_triangle(t2);
            ajouter_triangle(t3);
            break; //on sort de la boucle for
            //on ajoute les triangles aux donnees

        }
    }
    map<arete, triangle*> reper = construit_map(Aretes_fr, Triangles_fr, Tailles_fr[1], Tailles_fr[2]);
    update_map(reper);
    //create_text(*this, fichier); //on cree le fichier texte avec le nouveau maillage dynamique
}

void donnees::insert(float x, float y, float objx, float objy, float m, float gw, const char* fichier)
{
    ajouter_individu(x,y,objx,objy,m,gw);
    //on ajoute les coordonnees de l'individu dans le tableau des sommets front
    //le numero de l'individu est donc tailles_fr[0]

    float* coor_bar; //on cree le tableau des coordonnees barycentriques
    for(int i=0;i<Tailles_fr[2];i++) //boucle sur les triangles du maillage front
    {
        coor_bar = barycent_fr(x, y, Triangles_fr[i],*this);
        //on recupere les coordonnees barycentriques de l'individu par rapport au triangle en cours
        if(coor_bar[0]>0 && coor_bar[1]>0 && coor_bar[2]>0) //on se place dans le triangle où est l'individu
        {
            triangle tr = Triangles_fr[i];
            arete a = arete(Tailles_fr[0], tr.sommet1(),0, Sommets_fr);
            arete b = arete(Tailles_fr[0], tr.sommet2(),0, Sommets_fr);
            arete c = arete(Tailles_fr[0], tr.sommet3(),0, Sommets_fr);
            //on cree les trois nouvelles aretes
            ajouter_arete_fr(a);
            ajouter_arete_fr(b);
            ajouter_arete_fr(c);
            //on les ajoute dans les donnees
            triangle t1 = triangle(Tailles_fr[0], tr.sommet2(), tr.sommet3(), 1);
            triangle t2 = triangle(tr.sommet1(), Tailles_fr[0], tr.sommet3(), 1);
            triangle t3 = triangle(tr.sommet1(), tr.sommet2(), Tailles_fr[0], 1);
            //on cree les trois nouveaux triangles, orientes dans le bon sens (permutation)
            enlever_triangle(i);
            //D.triangles_fr()[i].vivant = 0; //on tue le triangle qui a disparu, remplace par les nouveaux triangles
            ajouter_triangle(t1);
            ajouter_triangle(t2);
            ajouter_triangle(t3);
            break; //on sort de la boucle for
            //on ajoute les triangles aux donnees

        }
    }
    map<arete, triangle*> reper = construit_map(Aretes_fr, Triangles_fr, Tailles_fr[1], Tailles_fr[2]);
    update_map(reper);
    create_text(*this, fichier); //on cree le fichier texte avec le nouveau maillage dynamique
}

void donnees::swap(const char * file)
{
    map<arete,triangle*> reper = Reper_fr;//on recupere Reper_fr
    map<arete,triangle*> reper2;
    map<arete, triangle*>::iterator it;
    for (it = reper.begin();it!=reper.end();it++)
    {
        arete b = it->first;
        triangle t1 = it->second[0];
        triangle t2 = it->second[1];
        if(t2.sommet1()!=0 && t2.sommet2()!=0 && t2.sommet3()!=0) //si l'arete n'est pas frontiere
        {
            arete a = other_edge(b, t1, t2, *this); //on trouve l'arete complementaire
            if(compare(b, a)==false && b.x1()-b.x2()>0.001 && b.y1()-b.y2()>0.001) //si l'arete en place est la plus longue
            {
                enlever_arete(it->first);
                cout<<"arete enlevee"<<endl;
                ajouter_arete_fr(a); //on ajoute l'arete plus courte
                triangle t3 = other_tri(t1,a); //on cree les deux nouveaux triangles
                triangle t4 = other_tri(t2,a);
                enlever_triangle(t1); //on enleve les deux anciens triangles
                enlever_triangle(t2);
                ajouter_triangle(t3); //on rajoute les deux nouveaux triangles
                ajouter_triangle(t4);
                reper2 = construit_map(Aretes_fr, Triangles_fr, Tailles_fr[1], Tailles_fr[2]);
                update_map(reper2);
            }
        }
    }
    create_text(*this, file);
}
