#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>  
#include <time.h>

#define REPETICIONES 5

// Función para simular retardo aleatorio (entre 100ms y 500ms)
void retardo_aleatorio() {
    usleep((rand() % 400 + 100) * 1000);  
}

// Funciones para cada bloque que imprime y duerme 5 veces
void bloque(const char* nombre) {
    for (int i = 0; i < REPETICIONES; i++) {
        printf("%s: iteracion %d\n", nombre, i+1);
        fflush(stdout);
        retardo_aleatorio();
    }
}

void *hiloA(void *arg) {
    bloque("a1");
    bloque("a2");
    bloque("a3");
    pthread_exit(NULL);
}

void *hiloB(void *arg) {
    bloque("b1");
    bloque("b2");
    bloque("b3");
    bloque("b4");
    pthread_exit(NULL);
}

void *hiloC(void *arg) {
    bloque("c1");
    bloque("c2");
    bloque("c3");
    pthread_exit(NULL);
}

int main() {
    srand(time(NULL));

    pthread_t A, B, C;

    pthread_create(&A, NULL, hiloA, NULL);
    pthread_create(&B, NULL, hiloB, NULL);
    pthread_create(&C, NULL, hiloC, NULL);

    pthread_join(A, NULL);
    pthread_join(B, NULL);
    pthread_join(C, NULL);

    return 0;
}
