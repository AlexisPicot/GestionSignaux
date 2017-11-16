#include <stdio.h>
#include <zconf.h>
#include <signal.h>
#include <stdbool.h>
#include <stdlib.h>


void sigusrHandler(int i) {
    switch (i) {
        case SIGUSR1: {
            puts("Signal SIGUSR1 reçu ! Execution de la boucle infinie");
            break;
        }
        case SIGUSR2: {
            puts("Signal SIGUSR2 reçu ! On arrete le programme fils");
            exit(i);
        }
    }
}


int main() {

    signal(SIGUSR1, sigusrHandler);
    signal(SIGUSR2, sigusrHandler);

    printf("Pid : %d\n", getpid());
    int pidChild = fork();
    if (!pidChild) {
        printf("Pid : %d\n", getpid());
        while (true) {
            pause();
            puts("Boucle infinie");
            sleep(1);
        }


    } else {
        for (int i = 0; i < 5; ++i) {
            sleep(1);
            //kill(pidChild,SIGUSR1);
            switch (i) {
                case 2:
                case 4:
                    kill(pidChild, SIGUSR1);
                    break;
            }

        }
        kill(pidChild, SIGUSR2);
    }
}