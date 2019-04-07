#include <stdio.h>
#include <stdlib.h>

struct Arc {
       int sommet;
       int valeur;
       struct Arc* arc_suivant;
};

struct Sommet{
       struct Arc* arc;
       int valeur;
};


typedef struct Arc* pArc;
typedef struct Sommet* pSommet;


pSommet* CreerGraphe(int taille);
pSommet* CreerArete(pSommet* graphe,int s1,int s2,int valeur);


