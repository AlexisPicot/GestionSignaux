#include <stdio.h>
#include <zconf.h>
#include <signal.h>
#include <stdbool.h>

int main() {
    printf("Pid : %d\n", getpid());
    signal(SIGINT, SIG_IGN);
    while (true) {
        pause();
    }

}

