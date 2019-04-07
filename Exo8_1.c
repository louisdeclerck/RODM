// pour compiler ce fichier executer gcc Exo8_1.c O9 -o Exo8_1 -std=c99

// pour executer faire : ./Exo8_1 Mon_Fichier.txt

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
	unsigned long *v=calloc(g->n,sizeof(unsigned long));

	for (i=0;i<g->e;i++) {

		v[g->edges[i].s]++;
		v[g->edges[i].t]++;

	}

	g->ka=malloc((g->n+1)*sizeof(unsigned long));
	g->ka[0]=0;

	for (i=1;i<g->n+1;i++) {

		g->ka[i]=g->ka[i-1]+v[i-1];
		v[i-1]=0;

	}

	g->adj=malloc(2*g->e*sizeof(unsigned long));


	for (i=0;i<g->e;i++) {

		beg=g->edges[i].s;
		fin=g->edges[i].t;
		g->adj[ g->ka[beg] + v[beg]++ ]=fin;
		g->adj[ g->ka[fin] + v[fin]++ ]=beg;

	}
	
	free(v);

}

unsigned *BFS(adjlist *g,unsigned long u) {

	unsigned long p=1;
	unsigned long i;
	unsigned long j;
	unsigned long l;
	
	static unsigned *d=NULL;
	static unsigned *liste=NULL;
	
	if (d==NULL){
		d=malloc((g->n)*sizeof(unsigned));
		liste=malloc((g->n)*sizeof(unsigned));
	}

	for (i=0;i<g->n;i++) {
		d[i]=-1;
	}

	liste[0]=u;
	
	d[u]=0;

	for (i=0;i<p;i++) {
		l=liste[i];
		for (j=g->ka[l];j<g->ka[l+1];j++) {
			if (d[g->adj[j]]==-1) {
				liste[p++]=g->adj[j];
				d[g->adj[j]]=d[l]+1;
			}
		}
	}

	return d;

}


int main(int argc,char** argv){
	
	//"algorithme pour afficher all connected components and their size"
	
}
