#include <stdio.h>
#include <zconf.h>
#include <signal.h>
#include <stdbool.h>
#include <stdlib.h>

bool fini = false;

void sigchildHandler(int i) {
    puts("TIMEOUT !");
    fini = true;
}


int main() {
    signal(SIGCHLD, sigchildHandler);


    printf("Pid : %d\n", getpid());
    int pidChild = fork();
    if (!pidChild) {

        sleep(5);
        exit(0);
    } else {
        char number[4];
        while (!fini) {
            printf("Entrez un entier mais pas 0 : ");

            scanf("%s", &number);
            if (atoi(number) && !fini) puts("Bravo !");
        }

    }
}