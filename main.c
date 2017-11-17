#include <stdio.h>
#include <unistd.h>
#include "Djikstra.h"

#define CLEP1 1
#define CLEP2 2
#define CLEP3 3


void P1();

void P2();

void simulerProcessus(int sec) {
    static char bars[] = {'/', '-', '\\', '|'};
    static int nbars = sizeof(bars) / sizeof(char);
    static int pos = 0;
    for (int i = 0; i < sec * 2; ++i) {
        usleep(500000);
        printf("%c\r", bars[pos]);
        fflush(stdout);
        pos = (pos + 1) % nbars;
    }

}


int main() {
    printf("Creation du sémaphore d'identificateur %d\n", sem_create(CLEP1, 0));
    printf("Creation du sémaphore d'identificateur %d\n", sem_create(CLEP2, 0));
    printf("Creation du sémaphore d'identificateur %d\n", sem_create(CLEP3, 0));
    if (fork())
        if (fork() == 0) {
            if (fork())
                P2();
            else P3();
        } else {
            P1();
        }
    sem_delete(sem_create(CLEP1, 0));
    sem_delete(sem_create(CLEP2, 0));
    sem_delete(sem_create(CLEP3, 0));
}

void P3() {

    sleep(1);
    V(sem_create(CLEP3, 0));
    V(sem_create(CLEP3, 0));
    puts("J'attends que P1 & P2 soient pret");
    P(sem_create(CLEP1, 0));
    P(sem_create(CLEP2, 0));
    puts("P1 & P2 sont prêts ! Go !");
    simulerProcessus(4);
    exit(0);
}

void P2() {

    sleep(5);
    V(sem_create(CLEP2, 0));
    V(sem_create(CLEP2, 0));
    puts("J'attends que P1 & P3 soient pret");
    P(sem_create(CLEP1, 0));
    P(sem_create(CLEP3, 0));
    puts("P1 & P3 sont prêts ! Go !");
    simulerProcessus(4);
    exit(0);
}

void P1() {
    sleep(3);
    V(sem_create(CLEP1, 0));
    V(sem_create(CLEP1, 0));
    puts("J'attends que P2 & P3 soient pret");
    P(sem_create(CLEP2, 0));
    P(sem_create(CLEP3, 0));
    puts("P2 & P3 sont prêts ! Go !");
    simulerProcessus(4);


}






