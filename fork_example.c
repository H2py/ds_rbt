#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(void)
{
    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork failed");
        return 1;
    }
    else if(pid == 0)
    {
        printf("Child Process pid : %d\n", getpid());
    }
    else
    {
        printf("Parent Process PID : %d, Child Process PID : %d\n", getpid(), pid);
    }
    return 0;
}