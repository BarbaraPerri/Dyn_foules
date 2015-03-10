#include"lecture.h" //tout ce qu'il faut est inclus dans le .h

//using namespace std;

int* lecture_mesh_tailles(const char* file)
{
    ifstream fichier(file, ios::in); //ouverture du fichier en mode lecture
    int* tailles = new int[3];

    if(fichier) //s'il y a bien ouverture
    {
        //cout<<file<<"is opened.";
        string ligne; //chaine de caractere pour stocker les lignes

        while(ligne!="Vertices") {getline(fichier,ligne);} //on cherche le mot-clÃ© Vertices

        fichier >> tailles[0]; //on rÃ©cupÃ¨re en lecture la taille du tableau
        //cout<<tailles[0]<<endl; //on l'affiche pour tester

        while(ligne!="Edges") {getline(fichier,ligne);} //on cherche le mot-clÃ© Edges

        fichier >> tailles[1];
        //cout<<tailles[1]<<endl; //on l'affiche pour tester

        while(ligne!="Triangles") {getline(fichier,ligne);} //on cherche le mot-clÃ© Triangles

        fichier >> tailles[2]; //on rÃ©cupÃ¨re le nombre de triangles
        //cout<<tailles[2]<<endl; //affichage pour test

        return(tailles);
        delete [] tailles;

        fichier.close(); //on ferme le fichier
    }
    else //s'il y a eu un probleme a  l'ouverture du fichier
    cerr<< "Impossible d'ouvrir le fichier"<< endl; //message d'erreur
}

void lecture_mesh(const char* file, vector<sommet*> &Vertices, arete* Edges, triangle* Triangles)
{
    ifstream fichier(file, ios::in); //ouverture du fichier en mode lecture

    if(fichier) //s'il y a bien ouverture
    {
        string ligne; //chaine de caractere pour stocker les lignes

        while(ligne!="Vertices"){getline(fichier,ligne);} //on cherche le mot-cle Vertices

        int taille_vertices; //on initialise la taille du tableau des points
        fichier >> taille_vertices; //on recupere en lecture la taille du tableau
        //cout<<taille_vertices<<endl; //on l'affiche pour tester
        float x, y;
        int ref;
        for(int i=0;i<taille_vertices;i++)
        {
            fichier >> x >> y >> ref; //on rÃ©cupÃ¨re les valeurs dans le fichier
            //cout<<x<<" "<<y<<" "<<ref<<endl; //affichage pour test
            sommet *S= new sommet(x,y,ref);
              //cout<<"pour le sommet"<<i<<":"<<endl;
              //cout<<x<<" "<<y<<" "<<ref<<endl;
            Vertices.push_back(S); //on construit les sommets avec valeurs
              //cout<<"test de l'affichage :"<<endl;
              //cout<<Vertices[i]->x()<<" "<<Vertices[i]->y()<<" "<<Vertices[i]->ref()<<endl;
        }

        while(ligne!="Edges"){getline(fichier,ligne);}


        //cout<<Vertices[0]->x()<<" "<<Vertices[0]->y()<<" "<<Vertices[0]->ref()<<endl;
        //cout<<Vertices[11]->x()<<" "<<Vertices[11]->y()<<" "<<Vertices[11]->ref()<<endl;

        int taille_edge;
        fichier >> taille_edge;
        //cout<<taille_edge<<endl; //on l'affiche pour tester
        int val1, val2, refere;
        for(int i=0;i<taille_edge;i++)
        {
            fichier >> val1 >> val2 >> refere;
            //cout<<val1<<" "<<val2<<" "<<refere<<endl; //affichage pour test
            arete a = arete(val1, val2, refere, Vertices);
            Edges[i] = a;
        }

        while(ligne!="Triangles"){getline(fichier,ligne);}

        int taille_tri;
        fichier >> taille_tri;
        //cout<<taille_tri<<endl; //on l'affiche pour tester
        int v1, v2, v3, r;
        for(int i=0;i<taille_tri;i++)
        {
            fichier >> v1 >> v2 >> v3 >> r;
            //cout<<val1<<" "<<val2<<" "<<val3<<" "<<refere<<endl; //affichage pour test
            Triangles[i] = triangle(v1,v2,v3,r);
        }

        fichier.close(); //on ferme le fichier
    }
    else //s'il y a eu un probleme a  l'ouverture du fichier
    cerr<< "Impossible d'ouvrir le fichier"<< endl; //message d'erreur
}

void lecture_back_mesh(const char* file, sommet* Vertices, arete* Edges, triangle* Triangles)
{
    ifstream fichier(file, ios::in); //ouverture du fichier en mode lecture

    if(fichier) //s'il y a bien ouverture
    {
        string ligne; //chaine de caractere pour stocker les lignes

        while(ligne!="Vertices"){getline(fichier,ligne);} //on cherche le mot-cle Vertices

        int taille_vertices; //on initialise la taille du tableau des points
        fichier >> taille_vertices; //on recupere en lecture la taille du tableau
        //cout<<taille_vertices<<endl; //on l'affiche pour tester
        float x, y;
        int ref;
        for(int i=0;i<taille_vertices;i++)
        {
            fichier >> x >> y >> ref; //on rÃ©cupÃ¨re les valeurs dans le fichier
            //cout<<x<<" "<<y<<" "<<ref<<endl; //affichage pour test
            sommet S = sommet(x,y,ref);
              //cout<<"pour le sommet"<<i<<":"<<endl;
              //cout<<x<<" "<<y<<" "<<ref<<endl;
            Vertices[i] = S;; //on construit les sommets avec valeurs
            Vertices[i].Num(i);
            //cout<<Vertices[i].Num()<<" ";
              //cout<<"test de l'affichage :"<<endl;
              //cout<<Vertices[i]->x()<<" "<<Vertices[i]->y()<<" "<<Vertices[i]->ref()<<endl;
        }

        while(ligne!="Edges"){getline(fichier,ligne);}


        //cout<<Vertices[0].x()<<" "<<Vertices[0].y()<<" "<<Vertices[0].ref()<<endl;
        //cout<<Vertices[11].x()<<" "<<Vertices[11].y()<<" "<<Vertices[11].ref()<<endl;

        int taille_edge;
        fichier >> taille_edge;
        //cout<<taille_edge<<endl; //on l'affiche pour tester
        int val1, val2, refere;
        for(int i=0;i<taille_edge;i++)
        {
            fichier >> val1 >> val2 >> refere;
            //cout<<val1<<" "<<val2<<" "<<refere<<endl; //affichage pour test
            arete a = arete(val1,val2,refere,Vertices);
            a.Num(i);
            Edges[i] = a;
            //Edges[i].Num[i];
        }

        while(ligne!="Triangles"){getline(fichier,ligne);}

        int taille_tri;
        fichier >> taille_tri;
        //cout<<taille_tri<<endl; //on l'affiche pour tester
        int v1, v2, v3, r;
        for(int i=0;i<taille_tri;i++)
        {
            fichier >> v1 >> v2 >> v3 >> r;
            //cout<<val1<<" "<<val2<<" "<<val3<<" "<<refere<<endl; //affichage pour test
            Triangles[i] = triangle(v1,v2,v3,r);
        }

        fichier.close(); //on ferme le fichier
    }
    else //s'il y a eu un probleme a  l'ouverture du fichier
    cerr<< "Impossible d'ouvrir le fichier"<< endl; //message d'erreur
}


float** lecture_sol(const char* file)
{
    ifstream fichier(file, ios::in); //ouverture du fichier en mode lecture

    if(fichier) //s'il y a bien ouverture
    {
        string ligne; //chaine de caractere pour stocker les lignes

        while(ligne!="SolAtVertices"){getline(fichier,ligne);} //on cherche le mot-clÃ© SolAtVertices

        int taille_sol; //on initialise la taille du tableau
        fichier >> taille_sol; //on la rÃ©cupÃ¨re depuis le fichier

        getline(fichier,ligne);
        getline(fichier,ligne);

        float ** Sol = new float*[taille_sol]; //on cree une matrice avec taille_sol lignes et 2 colonnes
        for(int i=0;i<taille_sol;i++)
        {
            Sol[i] = new float[2];
            fichier >> Sol[i][1] >> Sol[i][2]; //on rÃ©cupÃ¨re les donnÃ©es depuis le fichier
            //cout<< Sol[i][1] << " "<< Sol[i][2]<<endl;
        }

        fichier.close(); //on ferme le fichier
        return(Sol); //on renvoie la matrice
        delete [] Sol; //on supprime la matrice
    }
    else //s'il y a eu un problÃ¨me Ã  l'ouverture du fichier
    cerr<< "Impossible d'ouvrir le fichier"<< endl; //message d'erreur
}

/*donnees lecture(const char* mesh, const char* back_mesh, const char* sol)
{
    int* tailles_fr;
    tailles_fr = lecture_mesh_tailles(mesh);
    sommet* Sommets_fr = new sommet[tailles_fr[0]];
    arete* Aretes_fr = new arete[tailles_fr[1]];
    triangle* Triangles_fr = new triangle[tailles_fr[2]];
    lecture_mesh(mesh, Sommets_fr, Aretes_fr, Triangles_fr);

    int* tailles_back = lecture_mesh_tailles(back_mesh);
    sommet* Sommets_bk = new sommet[tailles_back[0]];
    arete* Aretes_bk = new arete[tailles_back[1]];
    triangle* Triangles_bk = new triangle[tailles_back[2]];
    lecture_mesh(back_mesh, Sommets_bk, Aretes_bk, Triangles_bk);

    float** Sol = lecture_sol(sol);

    donnees tableaux;
    tableaux.tailles_fr = tailles_fr;
    tableaux.Sommets_fr = Sommets_fr;
    tableaux.Aretes_fr = Aretes_fr;
    tableaux.Triangles_fr = Triangles_fr;

    tableaux.tailles_bk = tailles_back;
    tableaux.Sommets_bk = Sommets_bk;
    tableaux.Aretes_bk = Aretes_bk;
    tableaux.Triangles_bk = Triangles_bk;

    tableaux.Sol = Sol;

    return(tableaux);

    delete [] Sommets_fr;
    delete [] Aretes_fr;
    delete [] Sommets_bk;
    delete [] Aretes_bk;
    delete [] Triangles_bk;
    delete [] Triangles_fr;
}*/
