#include <stdio.h>
#include <zconf.h>
#include <signal.h>
#include <stdbool.h>
#include <stdlib.h>

bool fin = false;

void sigchldHandler(int i) {
    puts("Signal SIGCHLD reçu !");
}

int main() {
    signal(SIGCHLD, sigchldHandler);

    printf("Pid : %d\n", getpid());
    if (!fork()) {
        sleep(3);
        exit(0);
    } else {
        pause();
        puts("Action executée après le wait");
    }
}