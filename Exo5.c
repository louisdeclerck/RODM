// pour compiler ce fichier executer gcc Exo5.c O9 -o Exo5 -std=c99

// pour executer faire : ./Exo5 Mon_Fichier.txt degreMon_fichier.txt



#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <strings.h>
#include <time.h>



#define nbarete 1000000000 //a adapter au fichier


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


listarete* lirelistarete(char* input){

	unsigned long k=nbarete;
	listarete *g=malloc(sizeof(listarete));
	FILE *file;


	g->n=0;
	g->e=0;
	
	file=fopen(input,"r");
	g->edges=malloc(k*sizeof(arete));

	while (fscanf(file,"%d %d", &(g->edges[g->e].s), &(g->edges[g->e].t))==2) {
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
	listarete* g1;

	printf("Lecture à partir du fichier %s\n",argv[1]);
	
	time_t t1, t2;

	
	t1=time(NULL);
	

	g=lirelistarete(argv[1]);
	
	g1=lirelistarete(argv[2]);

	

	int qg=0;
	
	for (int i=0; i< g->e; i++)
	{
		qg=qg+((g1->edges[g->edges[i].s].t)*(g1->edges[g->edges[i].t].t));
	}
	
	t2=time(NULL);
	
	printf("Qg pour le fichier %s égale %d \n",argv[1],qg);
	printf("Temps d'execution pour Qg : %ld h %ld m %ld s \n",(t2-t1)/3600,((t2-t1)%3600)/60,((t2-t1)%60));
	
	return 0;
}
