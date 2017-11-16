#include <stdio.h>
#include <zconf.h>
#include <signal.h>
#include <stdbool.h>

bool fin = false;

void sigchldHandler(int i) {
    puts("Signal SIGCHLD reçu !");
}

int main() {
    signal(SIGCHLD, sigchldHandler);

    printf("Pid : %d\n", getpid());
    int pidChild = fork();
    if (!pidChild) {
        while (true) {
            puts("Boucle infinie");
            sleep(1);
        }
    } else {
        sleep(3);
        execlp("kill", "kill", "-SIGKILL", pidChild);
    }
}