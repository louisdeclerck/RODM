// pour compiler ce fichier executer gcc Exo7_2.c O9 -o Exo7_2 -std=c99

// pour executer faire : ./Exo7_2 Mon_Fichier.txt

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>


#define nbarete 34681189


typedef struct {

	unsigned long s;
	unsigned long t;
	
} arete;



typedef struct {

	unsigned long n;
	unsigned long e;
	arete *edges;
	bool *mat;

} adjmatrice;



inline unsigned long max3(unsigned long a,unsigned long b,unsigned long c){

	a=(a>b) ? a : b;
	return (a>c) ? a : c;

}


adjmatrice* lirelistarete(char* input){

	unsigned long k=nbarete;
	adjmatrice *g=malloc(sizeof(adjmatrice));
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



void chmatrice(adjmatrice* g){


	unsigned long beg;
	unsigned long fin;

	g->mat=calloc(g->n*g->n,sizeof(bool));

	for (int i=0;i<g->e;i++){
		beg=g->edges[i].s;
		fin=g->edges[i].t;
		g->mat[beg+g->n*fin]=1;
		g->mat[fin+g->n*beg]=1;
		//printf("%d\n",i);

	}

}





int main(int argc,char** argv){

	adjmatrice* g;
	time_t t1,t2;
	t1=time(NULL);

	printf("Lecture de la liste d'arete du fichier %s\n",argv[1]);

	g=lirelistarete(argv[1]);

	printf("Construction matrice d'adjacence\n");

	chmatrice(g);

	free(g->edges);
	free(g->mat);
	free(g);

	t2=time(NULL);

	printf(" Temps d'execution = %d h %d m %d s\n",(t2-t1)/3600,((t2-t1)%3600)/60,((t2-t1)%60));

	return 0;

}
