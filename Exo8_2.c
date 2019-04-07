// pour compiler ce fichier executer gcc Exo8_1.c O9 -o Exo8_2 -std=c99

// pour executer faire : ./Exo8_2 Mon_Fichier.txt


#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
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



inline unsigned long maximum(unsigned long a,unsigned long b,unsigned long c){

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
		g->n=maximum(g->n,g->edges[g->e].s,g->edges[g->e].t);

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

unsigned *BFS(adjlist *g,unsigned long u) {
	unsigned long n=g->n;
	unsigned long l=1;
	unsigned long i;
	unsigned long j;
	unsigned long v;
	
	static unsigned *d=NULL;
	static unsigned *liste=NULL;
	
	if (d==NULL){
		d=malloc(n*sizeof(unsigned));
		liste=malloc(n*sizeof(unsigned));
	}

	for (i=0;i<n;i++) {
		d[i]=-1;
	}

	liste[0]=u;
	
	d[u]=0;

	for (i=0;i<l;i++) {
		v=liste[i];
		for (j=g->ka[v];j<g->ka[v+1];j++) {
			if (d[g->adj[j]]==-1) {
				liste[l++]=g->adj[j];
				d[g->adj[j]]=d[v]+1;
			}
		}
	}

	return d;

}


unsigned long maximum_of_vect(unsigned long n, unsigned* vect){

	unsigned long i;
	unsigned long I;
	unsigned M=0;

	for (i=0;i<n;i++){
		if ((vect[i]!=-1) && (vect[i]>=M)){
			I=i;
			M=vect[i];
		}
	}

	return I;

}


int main(int argc,char** argv){

	adjlist* g;
	unsigned *d;
	unsigned D=0;
	unsigned long i;
	unsigned long v=0;
	
	bool *b;

	FILE* file;
	time_t t1,t2;

	t1=time(NULL);

	printf("Lecture liste d'arete du fichier %s\n",argv[1]);
	g=lirelistarete(argv[1]);

	printf("Construction liste d'adjacence\n");

	chadjlist(g);

	b=calloc(g->n,sizeof(bool));

	for (i=0;i<g->n;i++) {
		if (b[v]==0){
			i=i-1;}
		else {
			v=i;
			if (b[v]==1){
				continue;
			}
		}

		b[v]=1;
		printf("On affiche la distance des noeuds du graphe par rapport au noeud %lu\n",v);
		d=BFS(g,v);
		
		unsigned long k;
		unsigned long I;
		unsigned M=0;

		for (k=0;k<g->n;k++){
			if ((d[k]!=-1) && (d[k]>=M)){
				I=k;
				M=d[k];
			}
		}

		v=I;

		D=(D>d[v])?D:d[v];

		printf("lower bound diametre = %u\n",D);

	}

	printf("diametre = %u\n",D);

	free(g->ka);
	free(g->adj);
	free(g);

	t2=time(NULL);

	printf(" Temps d'execution = %d h %d m %d s\n",(t2-t1)/3600,((t2-t1)%3600)/60,((t2-t1)%60));

	return 0;

}

