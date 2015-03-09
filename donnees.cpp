#include "donnees.h"
#include "lecture.h"
#include <iostream>
#include <vector>
#include "map.h"

using namespace std;

donnees::donnees(const char* mesh, const char* back_mesh, const char* sol)
{
  Tailles_fr = lecture_mesh_tailles(mesh);
  Aretes_fr = new arete[Tailles_fr[1]];
  Triangles_fr = new triangle[Tailles_fr[2]];
  lecture_mesh(mesh, Sommets_fr, Aretes_fr, Triangles_fr);
   //cout<<"fin lecture mesh size sommets "<<Sommets_fr.size()<<endl;
   //cout<<" Initialisation du maillage back "<<endl;
  Tailles_bk = lecture_mesh_tailles(back_mesh);
   //cout<<" lecture tailles "<<Tailles_bk[0] << " "<<Tailles_bk[1] << " " <<Tailles_bk[2]<<endl;
  Sommets_bk = new sommet[Tailles_bk[0]];
   //cout<< " alloc sommet back ok "<<endl;
  Aretes_bk = new arete[Tailles_bk [1]];
   //cout<< " alloc aretes back ok "<<endl;
  Triangles_bk = new triangle[Tailles_bk [2]];
   //cout<< " alloc triangles back ok "<<endl;
  lecture_back_mesh(back_mesh, Sommets_bk , Aretes_bk, Triangles_bk);
  inner_aretes_bk();
  Map_voisinT_bk = construit3_map(Aretes_bk, Triangles_bk, Tailles_bk[1], Tailles_bk[2]);
   //cout<< " lecture mesh back ok "<<endl;
   //cout<< " premier sommet "<<endl;
   //cout<< " dernier sommet "<<endl;
   //cout<< " premiere arete "<<endl;
   //cout<< " derniere arete "<<endl;
   //cout<< " premier triangle "<<endl;
   //cout<< " dernier triangle "<<endl;//*/
  Sol = lecture_sol(sol);
  Reper_fr = construit_map(Aretes_fr, Triangles_fr, Tailles_fr[1], Tailles_fr[2]);
  //Reper_bk = construit_map(Aretes_bk, Triangles_bk, Tailles_bk[1], Tailles_bk[2]);
  //cout<<" **** FIN CONSTRUCTEUR DONNEES PB "<<endl;
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

void donnees::ajouter_sommet(float x, float y)
{
    sommet S;
    S.changer(x,y,0);
    Sommets_fr.push_back(&S);
}

void donnees::ajouter_individu(float x,float y,float objx, float objy, float m, float gw)
{
    Tailles_fr[0]++;
    individual *I=new individual;
    I->changer((float)x,(float)y,(float)0,(float)0,0);
    I->objectif(objx,objy);
    I->g(gw);
    I->masse(m);
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
    //cout<<"  APPEL AJOUT TRIANGLE "<<endl;
    Tailles_fr[2]++;
    triangle * T = new triangle[Tailles_fr[2]];
    //cout<<"allocation du tableau de triangles ok"<<endl;

    for (int i=0; i<(Tailles_fr[2] -1); i++)
    {
    T[i]=Triangles_fr[i];
    }
    //cout<<"recopie des triangles ok 1 "<<endl;

    T[Tailles_fr[2]-1] = t;
    triangle * tmp = Triangles_fr;
    Triangles_fr = T;
    delete [] tmp;
}

void donnees::enlever_triangle(int i)
{
    //cout<<i<<endl;
    //cout<<Tailles_fr[2]<<endl;
    Tailles_fr[2]--;
    //cout<<Tailles_fr[2]<<endl;
    triangle* T = new triangle[Tailles_fr[2]];
    for (int j=0; j<i; j++)
    {
    T[j]=Triangles_fr[j];
    //Triangles_fr[j].print();
    }
    for (int j=i+1; j<=Tailles_fr[2]; j++)
    {
    T[j-1]=Triangles_fr[j];
    //Triangles_fr[j].print();
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
    //int i=0;
    //cout<<"alloc de val ok"<<endl;
    for (int i=0;i<Tailles_fr[1]; i++)
    //map<arete, triangle*>::iterator it;
    //for (it = Reper_fr.begin(); it != Reper_fr.end(); it++)
    {
        cout<<"impression de l'arete"<<endl;
        Aretes_fr[i].print();
        //it->first.print();
        //i = i+1;
        //cout<<i<<endl;
        //val = Reper_fr[Aretes_fr[i]];

        cout<<"impression du premier triangle"<<endl;
        //val = it->second;
        //val[0].print();
        Reper_fr[Aretes_fr[i]][0].print();
        cout<<"impression du second triangle"<<endl;
        //val = it->second;
        //val[1].print();
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
    //cout<<"In the function inner_arete:"<<endl;
    //int array[2] = {-1,-1}; //array stores the edge that is contour of triangle.
    for(int i=0;i<T_tri;i++)
    {
        //cout<<"Check the "<<i<<"th triangle"<<endl;
        int array[2] = {-1,-1}; //array stores the edge that is contour of triangle.
        //cout<<"The first arete:"<<endl;
        arete bord1(T[i].sommet1(),T[i].sommet2(),3, Sommets_fr);//bord1.print();
        //cout<<"The second arete:"<<endl;
        arete bord2(T[i].sommet2(),T[i].sommet3(),3, Sommets_fr);//bord2.print();
        //cout<<"The third arete:"<<endl;
        arete bord3(T[i].sommet3(),T[i].sommet1(),3, Sommets_fr);//bord3.print();


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

            if((!(bord1==A[a]))&&(!(bord1==A[b]))&&(!(existed_arete(bord1,Aretes_fr,Tailles_fr[1]))))//If we have found the answer
                {ajouter_arete_fr(bord1);
                //cout<<"Now the size of aretes are "<<Donnees.tailles_fr()[1]<<endl;
                }
            else if((!(bord2==A[a]))&&(!(bord2==A[b]))&&(!(existed_arete(bord2,Aretes_fr,Tailles_fr[1]))))
                {//cout<<"Bord2 of triangle "<<i<<" is the inner arete, added in arete*"<<endl;
                 ajouter_arete_fr(bord2);//cout<<"Now the size of aretes are "<<Donnees.tailles_fr()[1]<<endl;
                 }
            else if((!(bord3==A[a]))&&(!(bord3==A[b]))&&(!(existed_arete(bord3,Aretes_fr,Tailles_fr[1]))))
                {//cout<<"Bord3 of triangle "<<i<<" is the inner arete, added in arete*"<<endl;
                 ajouter_arete_fr(bord3);//cout<<"Now the size of aretes are "<<Donnees.tailles_fr()[1]<<endl;
                 }

        //////////////////////////// here we shall add the construction map //////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        }
        else if(a>0)
        {
            //cout<<"Triangle "<<i<<" has 1 bords of contours."<<endl;
            if(bord1==A[a])//We have found the answer
                {
                    if(!existed_arete(bord2,Aretes_fr,Tailles_fr[1]))ajouter_arete_fr(bord2);//cout<<"Now the size of aretes are "<<Donnees.tailles_fr()[1]<<endl;
                    if(!existed_arete(bord3,Aretes_fr,Tailles_fr[1]))ajouter_arete_fr(bord3);//cout<<"Now the size of aretes are "<<Donnees.tailles_fr()[1]<<endl;
                 //cout<<"Bord2,3 of triangle "<<i<<" is the inner arete, added in arete*"<<endl;
                 }
            else if((bord2==A[a])&&(!existed_arete(bord2,Aretes_fr,Tailles_fr[1])))
                {
                    if(!existed_arete(bord3,Aretes_fr,Tailles_fr[1]))ajouter_arete_fr(bord3);//cout<<"Now the size of aretes are "<<Donnees.Tailles_fr[1]<<endl;
                    if(!existed_arete(bord1,Aretes_fr,Tailles_fr[1]))ajouter_arete_fr(bord1);//cout<<"Now the size of aretes are "<<Donnees.Tailles_fr[1]<<endl;
                //cout<<"Bord3,1 of triangle "<<i<<" is the inner arete, added in arete*"<<endl;
                }
            else if((bord3==A[a])&&(!existed_arete(bord3,Aretes_fr,Tailles_fr[1])))
                {
                    if(!existed_arete(bord1,Aretes_fr,Tailles_fr[1]))ajouter_arete_fr(bord1);//cout<<"Now the size of aretes are "<<Donnees.Tailles_fr[1]<<endl;
                 //if(Donnees.Aretes_fr[0].Num()>0){cout<<"It's bord1 who makes fault."<<endl;break;}
                    if(!existed_arete(bord2,Aretes_fr,Tailles_fr[1]))ajouter_arete_fr(bord2);//cout<<"Now the size of aretes are "<<Donnees.Tailles_fr[1]<<endl;
                 //cout<<"Bord1,2 of triangle "<<i<<" is the inner arete, added in arete*"<<endl;
                 }
        }
        else //the triangle is totally inner
        {
            if(!existed_arete(bord1,Aretes_fr,Tailles_fr[1]))ajouter_arete_fr(bord1);//cout<<"Now the size of aretes are "<<Donnees.Tailles_fr[1]<<endl;
            if(!existed_arete(bord2,Aretes_fr,Tailles_fr[1]))ajouter_arete_fr(bord2);//cout<<"Now the size of aretes are "<<Donnees.Tailles_fr[1]<<endl;
            if(!existed_arete(bord3,Aretes_fr,Tailles_fr[1]))ajouter_arete_fr(bord3);//cout<<"Now the size of aretes are "<<Donnees.Tailles_fr[1]<<endl;
            //cout<<"Bord1,2,3 of triangle "<<i<<" is the inner arete, added in arete*"<<endl;
        }
    }
    //cout<<"The end of inner_aretes "<<endl<<endl;
}

void donnees::inner_aretes_bk()
{
    int T_arete = Tailles_bk[1];
    int T_tri = Tailles_bk[2];
    arete* A=Aretes_bk;
    triangle* T=triangles_bk();
    cout<<"In the function inner_arete:"<<endl;
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
    cout<<"The end of inner_aretes "<<endl<<endl;
}
