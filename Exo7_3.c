// pour compiler ce fichier executer gcc Exo7_3.c O9 -o Exo7_3 -std=c99

// pour executer faire : ./Exo7_3 Mon_Fichier.txt

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
	unsigned long *ka;
	unsigned long *adj;
} adjlist;



inline unsigned long max3(unsigned long a,unsigned long b,unsigned long c){

	a=(a>b) ? a : b;
	return (a>c) ? a : c;

}



adjlist* lirelistarete(char* input){

	unsigned long k=nbarete;
	adjlist *g=malloc(sizeof(adjlist));
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



void chadjlist(adjlist* g){
	
	unsigned long i;
	unsigned long beg;
	unsigned long fin;
	unsigned long *p=calloc(g->n,sizeof(unsigned long));

	for (i=0;i<g->e;i++) {

		p[g->edges[i].s]++;
		p[g->edges[i].t]++;

	}

	g->ka=malloc((g->n+1)*sizeof(unsigned long));
	g->ka[0]=0;

	for (i=1;i<g->n+1;i++) {

		g->ka[i]=g->ka[i-1]+p[i-1];
		p[i-1]=0;

	}

	g->adj=malloc(2*g->e*sizeof(unsigned long));


	for (i=0;i<g->e;i++) {

		beg=g->edges[i].s;
		fin=g->edges[i].t;
		g->adj[ g->ka[beg] + p[beg]++ ]=fin;
		g->adj[ g->ka[fin] + p[fin]++ ]=beg;

	}
	
	free(p);

}




int main(int argc,char** argv){

	adjlist* g;
	time_t t1,t2;

	t1=time(NULL);

	printf("Lecture de la liste d'arete du fichier %s\n",argv[1]);

	g=lirelistarete(argv[1]);

	printf("construction liste d'adjacence\n");

	chadjlist(g);

	free(g->edges);
	free(g->ka);
	free(g->adj);
	free(g);

	t2=time(NULL);

	printf("Temps d'execution = %d h %d m %d s\n",(t2-t1)/3600,((t2-t1)%3600)/60,((t2-t1)%60));

	return 0;

}




