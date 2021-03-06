// pour compiler ce fichier executer gcc Exo1_t2.c O9 -o Exo1_t2 -std=c99

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
	listarete* g1;
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

	free(g->edges);
	free(g->dout);
	free(g);

	t2=time(NULL);

	printf("Temps d'execution = %d h %d m %d s\n",(t2-t1)/3600,((t2-t1)%3600)/60,((t2-t1)%60));

	fclose(file);
	//affichage des pages
	
	g1=lirelistarete(argv[2]);
	
	int a=0;
	int b=0;
	int c=0;
	int d=0;
	int e=0;
	
	int a1=0;
	int b1=0;
	int c1=0;
	int d1=0;
	int e1=0;

	
	for (int i=0;i<g1->n;i++){
		if (g1->edges[i].t>a)
		{
			b=a;
			c=b;
			d=c;
			e=d;
			a=g1->edges[i].t;

			b1=a1;
			c1=b1;
			d1=c1;
			e1=d1;
			a1=i;
		}
		
		else{
			if (g1->edges[i].t>b)
		{
			c=b;
			d=c;
			e=d;
			b=g1->edges[i].t;
			c1=b1;
			d1=c1;
			e1=d1;
			b1=i;
		}
		
		else{
			if (g1->edges[i].t>c)
		{

			d=c;
			e=d;
			c=g1->edges[i].t;
			d1=c1;
			e1=d1;
			c1=i;
			
		}
		
		else{
			if (g1->edges[i].t>d)
		{


			e=d;
			d=g1->edges[i].t;
			e1=d1;
			d1=i;
		}
		
		else{
			if (g1->edges[i].t>e)
		{
			e=g1->edges[i].t;
			e1=i;
		}
		}
	}
}
}
}

printf("les %d pages avec le plus grand pagerank sont\n",5);

printf("%d \n",a1);
printf("%d \n",b1);
printf("%d \n",c1);
printf("%d \n",d1);
printf("%d \n",e1);


//5  plus bas
	int z=1000000;
	int y=1000000;
	int x=1000000;
	int w=1000000;
	int v=1000000;
	
	int z1=0;
	int y1=0;
	int x1=0;
	int w1=0;
	int v1=0;

	
	for (int i=0;i<g1->n;i++){
		if (g1->edges[i].t<z)
		{
			y=z;
			x=y;
			w=x;
			v=w;
			z=g1->edges[i].t;

			y1=z1;
			x1=y1;
			w1=x1;
			v1=w1;
			z1=i;
		}
		
		else{
			if (g1->edges[i].t<y)
		{

			x=y;
			w=x;
			v=w;
			y=g1->edges[i].t;


			x1=y1;
			w1=x1;
			v1=w1;
			y1=i;
		}
		
		else{
			if (g1->edges[i].t<x)
		{

			w=x;
			v=w;
			x=g1->edges[i].t;


			w1=x1;
			v1=w1;
			x1=i;
			
		}
		
		else{
			if (g1->edges[i].t<w)
		{


			v=w;
			w=g1->edges[i].t;

			v1=w1;
			w1=i;
		}
		
		else{
			if (g1->edges[i].t<v)
		{

			v=g1->edges[i].t;

			v1=i;
		}
		}
	}
}
}
}

printf("les %d pages avec le plus faible pagerank sont\n",5);

printf("%d \n",z1);
printf("%d \n",y1);
printf("%d \n",x1);
printf("%d \n",w1);
printf("%d \n",v1);

	return 0;
	
}

