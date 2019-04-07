//Pour compiler ce fichier faire : gcc Exo2.c -O9 -o Exo2 -std=c99

//pour l'executer ./Exo2 Mon_Fichier.txt

#include <stdlib.h>
#include <stdio.h>
#include <time.h>


#define nbarete 10000000000


typedef struct {

	unsigned long s;
	unsigned long t;
	
} arete;



typedef struct {

	unsigned long n;
	unsigned long e;
	arete *edges;

} listarete;



inline unsigned long max3(unsigned long a,unsigned long b,unsigned long c){

	a=(a>b) ? a : b;
	return (a>c) ? a : c;

}


listarete* lirelistarete(char* input){

	unsigned long k=nbarete;
	listarete *g=malloc(sizeof(listarete));
	FILE *file;


	g->n=0;
	g->e=0;
	
	file=fopen(input,"r");
	g->edges=malloc(k*sizeof(arete));

	while (fscanf(file,"%lu %lu", &(g->edges[g->e].s), &(g->edges[g->e].t))==2) {
		g->n=max3(g->n,g->edges[g->e].s,g->edges[g->e].t);

		if (g->e++==k) {

			k+=nbarete;
			g->edges=realloc(g->edges,k*sizeof(arete));

		}

	}

	fclose(file);
	
	g->n++;

	g->edges=realloc(g->edges,g->e*sizeof(arete));




	return g;

}




int main(int argc,char** argv){
	listarete* g;

	printf("Lecture à partir du fichier %s\n",argv[1]);

	g=lirelistarete(argv[1]);

	printf("Nombre de noeud = %d\n",g->n);
	printf("Nombre d'arete = %d\n",g->e);

	return 0;
}


