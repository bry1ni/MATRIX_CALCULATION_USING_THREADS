#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NB_MAX  90
#define NB_MIN  10

static pthread_mutex_t my_mutex;

/* calcul de la somme de deux matrice en utilisant les threads */
/* chaque thread travaille sur meme indice de ligne entre les deux matrices */

int M1[3][3],M2[3][3],Mres[3][3];
int i,j,N;

/* generation de la matrice 1 et 2 + affichage */
void affM1(){
    pthread_mutex_lock (&my_mutex);
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<3; j++)
            //M1[i][j]=(1+i*2)+j;
			M1[i][j] = rand()%(NB_MAX-NB_MIN)+NB_MIN;
			printf("| %d |", M1[i][j]);
			printf("| %d |", M1[i][j]);
			printf("| %d |", M1[i][j]);
		printf("\n");
	}
	pthread_mutex_unlock (&my_mutex);
	printf("\n");
  	pthread_exit (0);
}

void affM2(){
    pthread_mutex_lock (&my_mutex);
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<3; j++)
            //M2[i][j]=2+i+(j*2);
			M2[i][j] = rand()%(NB_MAX-NB_MIN)+NB_MIN;
			printf("| %d |", M2[i][j]);
			printf("| %d |", M2[i][j]);
			printf("| %d |", M2[i][j]);
		printf("\n");
	}
	pthread_mutex_unlock (&my_mutex);

  	pthread_exit (0);
}

/* traitement des lignes */
void ligne1(){
    pthread_mutex_lock (&my_mutex);
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<3; j++)
            Mres[0][j]=M1[0][j]+M2[0][j];
	}
	pthread_mutex_unlock (&my_mutex);

  	pthread_exit (0);
}

void ligne2(){
    pthread_mutex_lock (&my_mutex);
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<3; j++)
            Mres[1][j]=M1[1][j]+M2[1][j];
	}
	pthread_mutex_unlock (&my_mutex);

  	pthread_exit (0);
}

void ligne3(){
    pthread_mutex_lock (&my_mutex);
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<3; j++)
            Mres[2][j]=M1[2][j]+M2[2][j];
	}
	pthread_mutex_unlock (&my_mutex);

  	pthread_exit (0);
}

/* remplissage de la matrice résultat */
void rempMres(){
    pthread_mutex_lock (&my_mutex);
    printf("\n");
    printf("Debut du thread d'affichage.\n");
    sleep(2);
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<3; j++)
            Mres[i][j]=M1[i][j]+M2[i][j];
			printf("| %d |", Mres[i][j]);
			printf("| %d |", Mres[i][j]);
			printf("| %d |", Mres[i][j]);
		printf("\n");
	}
	printf("Fin.\n");
	pthread_mutex_unlock (&my_mutex);

  	pthread_exit (0);
}


int main()
{
	pthread_t th3 ,th4,th5,th6,th7,th8;
	void *ret;
   	pthread_mutex_init (&my_mutex, NULL);

	/* creation des threads et affectation */
   	pthread_create (&th3, NULL, affM1, NULL);
   	printf("\n");
   	pthread_create (&th4, NULL, affM2, NULL);
   	printf("\n");
   	pthread_create (&th5, NULL, ligne1, NULL);
   	pthread_create (&th6, NULL, ligne2, NULL);
   	pthread_create (&th7, NULL, ligne3, NULL);
   	pthread_create (&th8, NULL, rempMres, NULL);

	/* jointure des threads */
  	(void)pthread_join (th3, &ret);
  	(void)pthread_join (th4, &ret);
  	(void)pthread_join (th5, &ret);
  	(void)pthread_join (th6, &ret);
  	(void)pthread_join (th7, &ret);
  	(void)pthread_join (th8, &ret);
}
