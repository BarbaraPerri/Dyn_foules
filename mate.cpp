#include "mate.h"
#include "barycent.h"

//extern donnees Donnees;

/*T* barycent(float x,float y,triangle A)//A B C sont 3 sommets des triangles
{
    //cout<<"In the barycent"<<endl;
    sommet pt_a = Donnees.sommets_bk()[A.sommet1()-1];
    //pt_a.print_sommet();
    sommet pt_b = Donnees.sommets_bk()[A.sommet2()-1];
    //pt_b.print_sommet();
    sommet pt_c = Donnees.sommets_bk()[A.sommet3()-1];
    //pt_c.print_sommet();

    T x_a = pt_a.x();
    T x_b = pt_b.x();
    T x_c = pt_c.x();
    T y_a = pt_a.y();
    T y_b = pt_b.y();
    T y_c = pt_c.y();
    T aire_abc = (x_b-x_c)*(y_c-y_a)-(x_c-x_a)*(y_b-y_c);
    T aire_pbc = (y_b-y_c)*(x-x_c)-(x_b-x_c)*(y-y_c);
    T aire_pca = (y_c-y_a)*(x-x_a)-(x_c-x_a)*(y-y_a);
    T aire_pab = (y_a-y_b)*(x-x_b)-(x_a-x_b)*(y-y_b);
    T lambda_A = aire_pbc/aire_abc;
    T lambda_B = aire_pca/aire_abc;
    T lambda_C = aire_pab/aire_abc;
    T* lambda = new float[3];
    lambda[0] = lambda_A;
    lambda[1] = lambda_B;
    lambda[2] = lambda_C;
    //cout<<lambda[0]<<" "<<lambda[1]<<" "<<lambda[2]<<" "<<endl;
    return lambda;//return un tableau de 3 elements
    //delete []lambda;Ne détuit pas
}*/

T** grad_barycent(float x,float y,triangle A, donnees Donnees)//A B C sont 3 sommets des triangles
{
    //cout<<"In the barycent"<<endl;
    sommet pt_a = Donnees.sommets_bk()[A.sommet1()-1];
    //pt_a.print_sommet();
    sommet pt_b = Donnees.sommets_bk()[A.sommet2()-1];
    //pt_b.print_sommet();
    sommet pt_c = Donnees.sommets_bk()[A.sommet3()-1];
    //pt_c.print_sommet();

    T x_a = pt_a.x();
    T x_b = pt_b.x();
    T x_c = pt_c.x();
    T y_a = pt_a.y();
    T y_b = pt_b.y();
    T y_c = pt_c.y();
    T aire_abc = (x_b-x_c)*(y_c-y_a)-(x_c-x_a)*(y_b-y_c);
    T grad_pbc_x = (y_b-y_c);T grad_pbc_y = -(x_b-x_c);
    T grad_pca_x = (y_c-y_a);T grad_pca_y = -(x_c-x_a);
    T grad_pab_x = (y_a-y_b);T grad_pab_y = -(x_a-x_b);

    T** grad = new float*[3];
    grad[0] = new float[2];
    grad[1] = new float[2];
    grad[2] = new float[2];

    grad[0][0] = grad_pbc_x/aire_abc;grad[0][1] = grad_pbc_y/aire_abc;
    grad[1][0] = grad_pca_x/aire_abc;grad[1][1] = grad_pca_y/aire_abc;
    grad[2][0] = grad_pab_x/aire_abc;grad[2][1] = grad_pab_y/aire_abc;


    //cout<<lambda[0]<<" "<<lambda[1]<<" "<<lambda[2]<<" "<<endl;
    return grad;//return un tableau de 3 elements
    //delete []lambda;Ne détuit pas
}

int mate_fr(T x, T y,map<int,int*> map_voisinT,donnees Donnees, int depart)
//entré x,y; sortie num triangle; donné le depart, par défaut 0, N_T le taille des triangles
//ici on met normalmant depart le triangle dans t eme temp
{
    int N_T = Donnees.tailles_fr(2);//The size of triangles
    triangle* Tri = Donnees.triangles_fr();
    arete* A = Donnees.aretes_fr();
    int N_A = Donnees.tailles_fr(1);
    //cout<<"In the function mate:"<<endl;
    if(depart>N_T){cerr<<"Start with a number surpass the size."<<endl;return -1;}
    else if (depart<0){cerr<<"Start with a number inferier to 0."<<endl;return -1;}
    int now = depart;// int now means now I am in triangle[now]
    triangle Tri_now = Tri[now];
    T* lambda = barycent_bk(x,y,Tri_now,Donnees);//appel barycent
    int num_in_table;// in this period the most important is to find the num_in_table
    map<int,int*>::iterator it;//with constructor 3

    list<int> chemin;
    list<int>::iterator lit;

    while ((lambda[0]<0)||(lambda[1]<0)||(lambda[2]<0)) //When the point is not in the triangle
    {
        cout<<"Now I am in the "<<now<<"th triangle"<<endl;
        //cout<<lambda[0]<<" "<<lambda[1]<<" "<<lambda[2]<<" "<<endl;
        triangle Tri_now = Tri[now];
        chemin.push_back(now);
        int t;
        //////////////////// the modification of bords ///////////////////////
        arete bord1(Tri_now.sommet2(),Tri_now.sommet3(),3,Donnees.sommets_bk());
            int num_bord1 = find_arete(bord1, A, N_A);
            int ref_bord1 = Donnees.aretes_fr()[num_bord1].ref();
            it = map_voisinT.find(num_bord1);int* array = it->second;
            if(array[0]==now) t=array[1];else t = array[0];
            for(lit = chemin.begin();lit!=chemin.end();lit++)
            {
                if(t==*lit)ref_bord1=0;
            }
        arete bord2(Tri_now.sommet3(),Tri_now.sommet1(),3, Donnees.sommets_bk());
            int num_bord2 = find_arete(bord2, A, N_A);
            int ref_bord2 = Donnees.aretes_fr()[num_bord2].ref();
            it = map_voisinT.find(num_bord2);array = it->second;
            if(array[0]==now) t=array[1];else t = array[0];
            for(lit = chemin.begin();lit!=chemin.end();lit++)
            {
                if(t==*lit)ref_bord2=0;
            }
        arete bord3(Tri_now.sommet1(),Tri_now.sommet2(),3, Donnees.sommets_bk());
            int num_bord3 = find_arete(bord3, A, N_A);
            int ref_bord3 = Donnees.aretes_fr()[num_bord3].ref();
            it = map_voisinT.find(num_bord3);array = it->second;
            if(array[0]==now) t=array[1];else t = array[0];
            for(lit = chemin.begin();lit!=chemin.end();lit++)
            {
                if(t==*lit)ref_bord3=0;
            }

        //////////////for finding the direction////////////////
        if((lambda[0]<0)&&(ref_bord1=3))//Test bord 1
        {
            num_in_table = num_bord1;
            if(ref_bord1!=3){cerr<<"Surpass the edges!"<<endl;break;}
        }
        else if((lambda[1]<0)&&(ref_bord2=3))
        {
            num_in_table = num_bord2;
            if(ref_bord2!=3){cerr<<"Surpass the edges!"<<endl;break;}
        }
        else//cest frocement(lambda[2]<0)
        {
            num_in_table = num_bord3;
            if(ref_bord3!=3){cerr<<"Surpass the edges!"<<endl;break;}
        }
        ////////////// the initialization of the next triangle ////////////////
        it = map_voisinT.find(num_in_table);
        array = it->second;
        //cout<<"    The bord1 has 2 voisins"<<array[0]<<" "<<array[1]<<endl;
        if(array[0]==now) now=array[1];
        else now = array[0];
        //cout<<"    Index now change to "<<now<<endl;
        Tri_now = Tri[now];
        lambda = barycent_bk(x,y,Tri_now, Donnees);
    }
    cout<<"The point is in the "<<now<<" th triangle"<<endl;
    Tri_now = Tri[now];
    Tri_now.print();
    cout<<endl;
    return now;
}


int mate_bk(T x, T y,donnees Donnees, int depart)
//entré x,y; sortie num triangle; donné le depart, par défaut 0, N_T le taille des triangles
//ici on met normalmant depart le triangle dans t eme temp
{
    int N_T = Donnees.tailles_bk(2);//The size of triangles
    triangle* Tri = Donnees.triangles_bk();
    arete* A = Donnees.aretes_bk();
    int N_A = Donnees.tailles_bk(1);
    map<int,int*> map_voisinT = Donnees.map_voisinT_bk();
    //cout<<"In the function mate:"<<endl;
    if(depart>N_T){cerr<<"Start with a number surpass the size."<<endl;return -1;}
    else if (depart<0){cerr<<"Start with a number inferier to 0."<<endl;return -1;}
    int now = depart;// int now means now I am in triangle[now]
    triangle Tri_now = Tri[now];
    T* lambda = barycent_bk(x,y,Tri_now, Donnees);//appel barycent
    int num_in_table;// in this period the most important is to find the num_in_table
    map<int,int*>::iterator it;//with constructor 3

    list<int> chemin;
    list<int>::iterator lit;

    while ((lambda[0]<0)||(lambda[1]<0)||(lambda[2]<0)) //When the point is not in the triangle
    {
        //cout<<"In the "<<now<<"th triangle"<<endl;
        //cout<<lambda[0]<<" "<<lambda[1]<<" "<<lambda[2]<<" "<<endl;
        triangle Tri_now = Tri[now];
        //chemin.push_back(now);
        int t;
        //////////////////// the modification of bords ///////////////////////
        arete bord1(Tri_now.sommet2(),Tri_now.sommet3(),3, Donnees.sommets_bk());
            int num_bord1 = find_arete(bord1, A, N_A);
            int ref_bord1 = Donnees.aretes_bk()[num_bord1].ref();
            it = map_voisinT.find(num_bord1);int* array = it->second;
            if(array[0]==now) t=array[1];else t = array[0];
//            for(lit = chemin.begin();lit!=chemin.end();lit++)
//            {
//                if(t==*lit)ref_bord1=0;
//            }
        arete bord2(Tri_now.sommet3(),Tri_now.sommet1(),3, Donnees.sommets_bk());
            int num_bord2 = find_arete(bord2, A, N_A);
            int ref_bord2 = Donnees.aretes_bk()[num_bord2].ref();
            it = map_voisinT.find(num_bord2);array = it->second;
            if(array[0]==now) t=array[1];else t = array[0];
            for(lit = chemin.begin();lit!=chemin.end();lit++)
            {
                if(t==*lit)ref_bord2=0;
            }
        arete bord3(Tri_now.sommet1(),Tri_now.sommet2(),3, Donnees.sommets_bk());
            int num_bord3 = find_arete(bord3, A, N_A);
            int ref_bord3 = Donnees.aretes_bk()[num_bord3].ref();
            it = map_voisinT.find(num_bord3);array = it->second;
            if(array[0]==now) t=array[1];else t = array[0];
            for(lit = chemin.begin();lit!=chemin.end();lit++)
            {
                if(t==*lit)ref_bord3=0;
            }

        //////////////for finding the direction////////////////
        if((lambda[0]<0)&&(ref_bord1=3))//Test bord 1
        {
            if(ref_bord1!=3){cerr<<"The individual try to pass the wall."<<endl;return now;}
            num_in_table = num_bord1;
            if(ref_bord1!=3){cerr<<"Surpass the edges!"<<endl;break;}
        }
        else if((lambda[1]<0)&&(ref_bord2=3))
        {
            if(ref_bord2!=3){cerr<<"The individual try to pass the wall."<<endl;return now;}
            num_in_table = num_bord2;
            if(ref_bord2!=3){cerr<<"Surpass the edges!"<<endl;break;}
        }
        else//cest frocement(lambda[2]<0)
        {
            if(ref_bord3!=3){cerr<<"The individual try to pass the wall."<<endl;return now;}
            num_in_table = num_bord3;
            if(ref_bord3!=3){cerr<<"Surpass the edges!"<<endl;break;}
        }
        ////////////// the initialization of the next triangle ////////////////
        it = map_voisinT.find(num_in_table);
        array = it->second;
        //cout<<"    The bord1 has 2 voisins"<<array[0]<<" "<<array[1]<<endl;
        if(array[0]==now) now=array[1];
        else now = array[0];
        //cout<<"    Index now change to "<<now<<endl;
        Tri_now = Tri[now];
        lambda = barycent_bk(x,y,Tri_now, Donnees);
    }
    //cout<<"The point is in the "<<now<<" th triangle"<<endl;
    Tri_now = Tri[now];
//    Tri_now.print();
//    Donnees.sommets_bk()[Tri_now.sommet1()-1].print_sommet();
//    Donnees.sommets_bk()[Tri_now.sommet2()-1].print_sommet();
//    Donnees.sommets_bk()[Tri_now.sommet3()-1].print_sommet();

//    cout<<endl<<"The finding chemin is:"<<endl;
//    for(lit = chemin.begin();lit!=chemin.end();lit++)
//    {
//        cout<<*lit<<"    ";
//    }
//    cout<<endl;
    return now;
}

int first_mate_bk(T x, T y, donnees Donnees)//Use methode research allover
{
    int N_tri = Donnees.tailles_bk(2);
    triangle* table_tri = Donnees.triangles_bk();
    T* lambda;//appel barycent
    int now;
    for(int i=0; i<N_tri; i++)
    {
        lambda = barycent_bk(x,y, table_tri[i],Donnees);//appel barycent
        if((lambda[0]>=0)&&(lambda[1]>=0)&&(lambda[2]>0)) {now = i;break;}//if this condition is fulfilled, we've found it;
    }
}
