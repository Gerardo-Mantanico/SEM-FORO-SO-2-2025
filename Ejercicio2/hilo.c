#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX 6

sem_t semA, semB, semC;

void *escribirA(void *nada) {
    for (int i = 0; i < MAX; i++) {
        sem_wait(&semA);      // Espera su turno
        printf("A");
        fflush(stdout);
        sem_post(&semB);     
    }
    pthread_exit(NULL);
}

void *escribirB(void *nada) {
    for (int i = 0; i < MAX; i++) {
        sem_wait(&semB);      // Espera a que A termine
        printf("B");
        fflush(stdout);
        sem_post(&semC);      
    }
    pthread_exit(NULL);
}

void *escribirC(void *nada) {
    for (int i = 0; i < MAX; i++) {
        sem_wait(&semC);      // Espera a que B termine
        printf("C");
        fflush(stdout);
        sem_post(&semA);     
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t th1, th2, th3;

    // Inicialización de los semáforos
    sem_init(&semA, 0, 1);  
    sem_init(&semB, 0, 0);  
    sem_init(&semC, 0, 0); 

    pthread_create(&th1, NULL, escribirA, NULL);
    pthread_create(&th2, NULL, escribirB, NULL);
    pthread_create(&th3, NULL, escribirC, NULL);

    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
    pthread_join(th3, NULL);

    // Destruir semáforos
    sem_destroy(&semA);
    sem_destroy(&semB);
    sem_destroy(&semC);

    printf("\n");
    return 0;
}
