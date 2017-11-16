#include <stdio.h>
#include <zconf.h>
#include <signal.h>
#include <stdbool.h>
#include <stdlib.h>

bool fin = false;

void sigintHandler(int i) {
    puts("Signal SIGINT reçu !");
    exit(i);
}
void sigchldHandler(int i) {
    puts("Signal SIGCHLD reçu, le fils est mort \\o/ !");
}

int main() {
    signal(SIGINT, sigintHandler);

    printf("Pid : %d\n", getpid());
    int pidChild = fork();
    if (!pidChild) {
        printf("Pid : %d\n", getpid());
        while (true) {
            puts("Boucle infinie");
            sleep(1);
        }
    } else {
        signal(SIGCHLD, sigchldHandler);
        pause();

    }
}