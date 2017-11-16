#include <stdio.h>
#include <zconf.h>
#include <signal.h>
#include <stdbool.h>

bool fin = false;

void sigintHandler(int i) {
    puts("Signal SIGINT reçu, mise à vrai du booléen FIN");
    fin = true;
}

int main() {
    printf("Pid : %d\n", getpid());
    signal(SIGINT, sigintHandler);
    while (!fin) {
        pause();
    }
    puts("Fin de la boucle, interruption du programme");

}