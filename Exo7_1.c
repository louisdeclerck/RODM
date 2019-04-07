// pour compiler ce fichier executer gcc Exo7_1.c O9 -o Exo7_1 -std=c99

// pour executer faire : ./Exo7_1 Mon_Fichier.txt


#include <stdlib.h>
#include <stdio.h>
#include <time.h>


#define nbarete 100000000


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
	time_t t1,t2;
	t1=time(NULL);

	printf("Lecture de la liste d'arete du fichier %s\n",argv[1]);

	g=lirelistarete(argv[1]);

	printf("Nombre de noeuds: %d\n",g->n);
	printf("Nombre d'aretes: %d\n",g->e);

	free(g->edges);
	free(g);

	t2=time(NULL);

	printf("- Temps d'execution = %d h %d m %d s\n",(t2-t1)/3600,((t2-t1)%3600)/60,((t2-t1)%60));

	return 0;

}
