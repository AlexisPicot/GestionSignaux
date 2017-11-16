#include <stdio.h>
#include <zconf.h>
#include <signal.h>
#include <stdlib.h>
#include <stdbool.h>

void sigintHandler(int i) {
    puts("Signal SIGINT reçu, interruption du programme");
    exit(1);
}

int main() {
    printf("Pid : %d\n", getpid());
    signal(SIGINT, sigintHandler);
    while (true) {
        pause();
    }

}