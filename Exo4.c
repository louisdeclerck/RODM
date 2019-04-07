// pour compiler ce fichier executer gcc Exo4.c O9 -o Exo4 -std=c99

// pour executer faire : ./Exo4 Mon_Fichier.txt


#include <stdlib.h>
#include <stdio.h>
#include <time.h>


#define nbarete 1000000 //a adapter au fichier

//j'ai repris seulement en parti de la structure fourni car j'avais deja commencé avec mon code
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

	printf("Lecture à partir du fichier %s\n",argv[1]);

	g=lirelistarete(argv[1]);

	g->dout=calloc(g->n,sizeof(unsigned long));

	int c=0;
	
	FILE* fichier = NULL;
	
	fichier= fopen("degrelj.txt","w+");
	
	for (int i=0; i< g->n; i++)
	{
		for (int j=0; j< g->e; j++)
			{

				if (g->edges[j].s == i)
				{
					c=c+1;
				}
			}
		
		

			printf("degre de %d est %d\n",i,c);
			fprintf(fichier,"%d %d\n",i,c);
			g->dout[i]=c;
			c=1;
		}
	
	

	return 0;
}


