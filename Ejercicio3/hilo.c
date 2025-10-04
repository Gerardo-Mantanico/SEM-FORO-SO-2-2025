#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX 5  

sem_t semA, semB;

void *escribirA(void *nada) {
    for (int i = 0; i < MAX; i++) {
        sem_wait(&semA);     // Espera que B termine
        printf("A");
        fflush(stdout);
        sem_post(&semB);     
    }
    pthread_exit(NULL);
}

void *escribirB(void *nada) {
    for (int i = 0; i < MAX; i++) {
        sem_wait(&semB);     // Empieza primero
        printf("B");
        fflush(stdout);
        sem_post(&semA);    
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t thA, thB;

    sem_init(&semA, 0, 0);  // A comienza esperando
    sem_init(&semB, 0, 1);  // B comienza activo

    pthread_create(&thA, NULL, escribirA, NULL);
    pthread_create(&thB, NULL, escribirB, NULL);

    pthread_join(thA, NULL);
    pthread_join(thB, NULL);

    sem_destroy(&semA);
    sem_destroy(&semB);

    printf("\n");
    return 0;
}
