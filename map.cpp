#include "map.h"

using namespace std;

map<arete,triangle*> create_map(arete* Aretes, triangle* Triangles, int* tailles) //constructeur de la map pour reperer les individus
{
    map<arete,triangle*> reperage; //ceation de la map vide
    triangle* val = new triangle[2]; //tableau pour stocker les triangles qui iront dans la map
    for (int i=0;i<tailles[1];i++) //boucle sur les aretes
    {
        int nb = 0; //nombre de fois qu'on trouve un triangle possedant l'arete
        for (int j=0;j<tailles[2];j++) //boucle sur les triangles
        {
            if (Triangles[j].have_edge(Aretes[i])==true) //si le triangle possede bien l'arete
            {
                val[nb] = Triangles[j]; //on stocke le triangle dans val dans la case associee
                nb += 1; //on prend en compte le fait qu'on a vu un triangle
            } //fin du if
        } // for j
        //reperage[Aretes[i]] = val; //pour chaque arete, on rentre la paire de triangles correspondante
    } //for i
    return(reperage); //on renvoie la map
    delete [] val; //on desalloue le tableau dynamique
} //fin de la fonction
