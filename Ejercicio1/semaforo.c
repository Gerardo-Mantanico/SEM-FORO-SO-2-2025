#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <time.h>

#define REPETICIONES 5

sem_t sem_a1_done;
sem_t sem_b1_done;
sem_t sem_b2_done;
sem_t sem_a2_done;
sem_t sem_c2_done;
sem_t sem_b4_done; 

void retardo_aleatorio() {
    usleep((rand() % 400 + 100) * 1000);
}

void bloque(const char* nombre) {
    for (int i = 0; i < REPETICIONES; i++) {
        printf("%s: iteracion %d\n", nombre, i+1);
        fflush(stdout);
        retardo_aleatorio();
    }
}

void *hiloA(void *arg) {
   
    bloque("a1");
    sem_post(&sem_a1_done); 
    sem_wait(&sem_b1_done);
    bloque("a2");
    sem_post(&sem_a2_done); 
    sem_wait(&sem_c2_done);
    bloque("a3");

    pthread_exit(NULL);
}

void *hiloB(void *arg) {
    bloque("b1");
    sem_post(&sem_b1_done); 
    bloque("b2");
    sem_post(&sem_b2_done);

    sem_wait(&sem_a2_done);
    bloque("b3");


    bloque("b4");

    sem_post(&sem_b4_done); 
    pthread_exit(NULL);
}

void *hiloC(void *arg) {
    sem_wait(&sem_a1_done);
    bloque("c1");

    sem_wait(&sem_b2_done);
    bloque("c2");
    sem_post(&sem_c2_done);  
   
    bloque("c3");

    pthread_exit(NULL);
}

int main() {
    srand(time(NULL));

    pthread_t A, B, C;

    // Inicializar semáforos en 0 para esperar
    sem_init(&sem_a1_done, 0, 0);
    sem_init(&sem_b1_done, 0, 0);
    sem_init(&sem_b2_done, 0, 0);
    sem_init(&sem_a2_done, 0, 0);
    sem_init(&sem_c2_done, 0, 0);
    sem_init(&sem_b4_done, 0, 0);

    pthread_create(&A, NULL, hiloA, NULL);
    pthread_create(&B, NULL, hiloB, NULL);
    pthread_create(&C, NULL, hiloC, NULL);

    sem_wait(&sem_b4_done);

    pthread_join(A, NULL);
    pthread_join(B, NULL);
    pthread_join(C, NULL);

    // Destruir semáforos
    sem_destroy(&sem_a1_done);
    sem_destroy(&sem_b1_done);
    sem_destroy(&sem_b2_done);
    sem_destroy(&sem_a2_done);
    sem_destroy(&sem_c2_done);
    sem_destroy(&sem_b4_done);

    return 0;
}
