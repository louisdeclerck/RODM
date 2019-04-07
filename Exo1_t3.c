// pour compiler ce fichier executer gcc Exo1_t3.c O9 -o Exo1_t3 -std=c99

// pour executer faire : ./Exo1_t3 

#include <stdio.h>
#include <stdlib.h>
#include "Exo1_t3.h"

pSommet* CreerGraphe(int taille){
  pSommet* Newgraphe = (pSommet*)malloc(taille*sizeof(pSommet));
  int i;
  for(i=0;i<100;i++){
    Newgraphe[i]=(pSommet)malloc(sizeof(struct Sommet));
    Newgraphe[i]->valeur=1;
    Newgraphe[i]->arc=NULL;
  }
  for(i=100;i<200;i++){
    Newgraphe[i]=(pSommet)malloc(sizeof(struct Sommet));
    Newgraphe[i]->valeur=2;
    Newgraphe[i]->arc=NULL;
  }
  
  for(i=200;i<300;i++){
    Newgraphe[i]=(pSommet)malloc(sizeof(struct Sommet));
    Newgraphe[i]->valeur=3;
    Newgraphe[i]->arc=NULL;
  }
  
  for(i=300;i<taille;i++){
    Newgraphe[i]=(pSommet)malloc(sizeof(struct Sommet));
    Newgraphe[i]->valeur=4;
    Newgraphe[i]->arc=NULL;
  }
  return Newgraphe;
}


pSommet* CreerArete(pSommet* graphe,int s1,int s2,int valeur){
  if(graphe[s1]->arc==NULL){
    pArc Newarc=(pArc)malloc(sizeof(struct Arc));
    Newarc->valeur=valeur;
    Newarc->sommet=s2;
    Newarc->arc_suivant=NULL;
    graphe[s1]->arc=Newarc;
    return graphe;
  }

  else{
    pArc temp=graphe[s1]->arc;
    while( !(temp->arc_suivant==NULL)){
    temp=temp->arc_suivant;
    }
     pArc Newarc=(pArc)malloc(sizeof(struct Arc));
     Newarc->valeur=valeur;
     Newarc->sommet=s2;
     Newarc->arc_suivant=NULL;

     if(temp->sommet>s2){
      Newarc->arc_suivant=temp->arc_suivant;
      Newarc->sommet=temp->sommet;
      temp->sommet=s2;
      temp->arc_suivant=Newarc;
      return graphe;
     }

     temp->arc_suivant=Newarc;
    return graphe;
    }
}

int N=10;


int main(int argc, char *argv[])
{
  pSommet* graphe=NULL;
  graphe=CreerGraphe(N);
  
  int p=0.5;
  int q=0.3;
  
  for(int i=0;i<N;i++){
	  
	  for(int j=0;j<N;j++){
		  
		  if (i!=j){
			  if(graphe[i]->valeur == graphe[j]->valeur){
				  int proba=(rand()%100)/100;
				  if (p>proba){
				    graphe=CreerArete(graphe,i,j,10); //10 poids de l'arete pas d'importance ici
			  }
			  }
			  
			  else{
				  int proba=(rand()%100)/100;
				  if (q>proba){
				    graphe=CreerArete(graphe,i,j,10); //10 poids de l'arete pas d'importance ici
			  }
			  }
		  }
  }
   
  }
  
  return 0;
}



