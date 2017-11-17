#include <stdio.h>
#include <unistd.h>
#include "Djikstra.h"

#define CLE 1


void advance_spinner() {
    static char bars[] = {'/', '-', '\\', '|'};
    static int nbars = sizeof(bars) / sizeof(char);
    static int pos = 0;

    printf("%c\r", bars[pos]);
    fflush(stdout);
    pos = (pos + 1) % nbars;
}


int main() {
    int sem;
    sem = sem_create(CLE, 0);
    printf("Creation du sémaphore d'identificateur %d\n", sem);
    if (fork() == 0) {
        puts("Je suis le fils, j'effectue un traitement.");
        for (int i = 0; i < 15; ++i) {
            usleep(300000);
            advance_spinner();
        }
        puts("J'ai fini !");
        V(sem);
        exit(0);
    } else {
        puts("Je suis le père et j'attends que mon fils ait fini son traitement");
        P(sem);
        puts("Je suis le père, j'effectue un traitement.");
        for (int i = 0; i < 15; ++i) {
            usleep(300000);
            advance_spinner();
        }
        puts("J'ai fini !");
        sem_delete(sem);
    }
}






