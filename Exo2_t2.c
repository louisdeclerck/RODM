// pour compiler ce fichier executer gcc Exo2_t2.c O9 -o Exo2_t2 -std=c99

// pour executer faire : ./Exo1_t2 dirlink.txt pagerank.txt

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <strings.h>
#include <time.h>

#define alpha 0.15 
#define nbarete 100000000
#define nbiter 30 



typedef struct {

	unsigned long s;
	unsigned long t;

} arete;



typedef struct {

	unsigned long n;
	unsigned long e;
	arete *edges;
	unsigned long *dout;

} listarete;


inline unsigned long max3(unsigned long a,unsigned long b,unsigned long c){

	a=(a>b) ? a : b;

	return (a>c) ? a : c;

}

listarete* lirelistarete(char* el){

	unsigned long i, k=nbarete;
	
	listarete *g=malloc(sizeof(listarete));

	g->edges=malloc(k*sizeof(arete));

	FILE *file;

	g->n=0;
	g->e=0;

	file=fopen(el,"r");

	
	while (fscanf(file,"%lu %lu\n", &(g->edges[g->e].s), &(g->edges[g->e].t))==2) {
		
		
		g->n=max3(g->n,g->edges[g->e].s,g->edges[g->e].t);

		if (g->e++==k) {

			k+=nbarete;

			g->edges=realloc(g->edges,k*sizeof(arete));

		}

	}

	fclose(file);

	g->n++;

	g->edges=realloc(g->edges,g->e*sizeof(arete));


	g->dout=calloc(g->n,sizeof(unsigned long));
	
	int c=0;
	
	for (int i=0; i< g->n; i++)
	{
		for (int j=0; j< g->e; j++)
			{

				if (g->edges[j].s == i)
				{
					c=c+1;
				}
			}
			g->dout[i]=c;
			c=1;
		}


	return g;

}


void ch_one(listarete* g, double* u, double* v){

	unsigned long i;
	bzero(v,sizeof(double)*g->n);

	for (i=0;i<g->e;i++){
		if (g->dout[g->edges[i].s]>0){
			v[g->edges[i].t]+=u[g->edges[i].s]/((double)(g->dout[g->edges[i].s]));//
		}
	}
} 

double* pagerank(listarete* g, double a, unsigned char p){

	double *u;
	double *v;
	double *w;
	double z;

	unsigned char i;
	unsigned long j;
	unsigned long n=g->n;

	u=malloc(n*sizeof(double));

	for (j=0;j<n;j++){
		u[j]=1./((double)n);
	}

	v=malloc(n*sizeof(double));

	for (i=0;i<p;i++){

		ch_one(g,u,v);
		z=0;

		for (j=0;j<g->n;j++){

			v[j]=v[j]*(1.-a)+a/((double)n);
			z+=v[j];

		}
		printf("%le\n",z);
		z=(1-z)/((double)n);

		for (j=0;j<n;j++){
			v[j]+=z;
		}
		w=v,v=u,u=w;
	}

	free(v);
	return u;

}



int main(int argc,char** argv){

	listarete* g;
	double* pr;
	
	FILE* file=fopen(argv[2],"w+");
	
	time_t t1,t2;
	t1=time(NULL);
	
	printf("Lecture liste d'arete du fichier %s\n",argv[1]);

	g=lirelistarete(argv[1]);
	printf("Calcul pagerank\n");
	pr=pagerank(g,alpha,nbiter);
	
	unsigned long k;
	for (k=0;k<g->n;k++){

		fprintf(file,"%d %10le\n",k,pr[k]);

	}

	fclose(file);
	file=fopen("degree-out.txt","w");

	unsigned long i;

	for (i=0;i<g->n;i++){

		fprintf(file,"%d %d\n",i,g->dout[i]);

	}

	fclose(file);

	unsigned long *degrein=calloc(g->n,sizeof(unsigned long));
	unsigned long j;

	for (j=0;j<g->e;j++){

		degrein[g->edges[j].t]++;

	}

	file=fopen("degree-in.txt","w");

	for (j=0;j<g->n;j++){

		fprintf(file,"%d %d\n",j,degrein[j]);

	}

	fclose(file);
	
	free(degrein);
	free(g->edges);
	free(g->dout);
	free(g);

	t2=time(NULL);

	printf("Temps d'execution = %d h %d m %d s\n",(t2-t1)/3600,((t2-t1)%3600)/60,((t2-t1)%60));

	return 0;

}
