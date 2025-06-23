#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

volatile sig_atomic_t paused = 0;

void handle_pause(int sig) {
    paused = 1;
    printf("[+] Received SIGUSR1 — Pausing...\n");
    // fflush(stdout);  
}

void handle_resume(int sig) {
    paused = 0;
    printf("[+] Received SIGUSR2 — Resuming...\n");
    // fflush(stdout);  
}

int main(void) {
    signal(SIGUSR1, handle_pause);
    signal(SIGUSR2, handle_resume);

    int i = 0;
    while (1) {
        if (!paused) {
            printf("Running... %d\n", i++);
        } else {
            printf("Paused...\n");
        }
        // fflush(stdout);  
        sleep(1);
    }
    return 0;
}

// By default in c, stdout is line-buffured when connected to a terminal.
// printf("Running..."); does not immediately print unless : It contains a newline \n or The buffer is flushed manually using fflush(stdout)
// why we use the fflush(stdout)

// When we use the printf, then string format is stored in the buffer that is temporary storage to store string
// and If you don't add the new line character then, can't recognize that the string is done so, prevent error from this situation we need to use fflush(stdout)
// means that remove all buffer with print all string format