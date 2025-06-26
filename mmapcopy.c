#include <stdio.h>
#include <stdlib.h>     // for exit()
#include <unistd.h>     // for write(), close()
#include <fcntl.h>      // for open()
#include <sys/mman.h>   // for mmap()
#include <sys/stat.h>   // for fstat()
#include <sys/types.h>  // for off_t, struct stat

// Write a C program mmapcopy.c that uses mmap to copy an arbitrary-size disk file to stdout. The name of the input file should be passed as a command-line argument.
// 이 프로그램은 mmap을 사용하여 임의 크기의 디스크 파일을 stdout으로 복사합니다.
// 입력 파일의 이름은 **명령줄 인자(command-line argument)**로 전달됩니다.

/*
* mmapcopy - uses mmap to cpy file fd to stdout
*/

void mmapcopy(int fd, int size)
{
    char *bufp =mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0); // ptr to memory-mapped VM area
    write(1, bufp, size);

    munmap(bufp, size);
    return;
}

int main(int argc, char **argv)
{
    struct stat stat;
    int fd;

    if (argc != 2) {
        printf("usage: %s <filename>\n", argv[0]);
        exit(0);
    }

    fd = open(argv[1], O_RDONLY);
    if(fd < 0) {
        perror("open");
        exit(1);
    }

    if (fstat(fd, &stat) < 0) {
        perror("open");
        exit(1);
    }

    mmapcopy(fd, stat.st_size);
    close(fd);
    exit(0);
}