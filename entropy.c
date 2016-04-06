#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char* argv[]) {
    long size = 0;
    double entropy = 0;
    const int BUFSIZE = 65536;
    unsigned char buf[BUFSIZE];
    ssize_t read_bytes = 0;
    int bytes[256];
    int filemode = 0;
    int fd = STDIN_FILENO;
    if (argc > 1) {
        const char* filename = argv[1];
        if ((fd = open(filename, O_RDONLY)) == -1) {
            printf("error while opening file\n");
            exit errno;
        }
        filemode = 1;
    }
    for (int i = 0; i < 256; i++) {
        bytes[i]=0;
    }
    do {
        read_bytes = read(fd, buf, BUFSIZE);
        size += read_bytes;
        for (int i = 0; i < read_bytes; i++) {
            bytes[buf[i]]++;
        }
    } while (read_bytes > 0);
    if (filemode) {
        close(fd);
    }
    for (int i = 0; i < 256; i++) {
        double p = (double)bytes[i]/size;
        if (p>0) {
            entropy -= p*log2(p);
        }
    }
    printf("%f\n", entropy);
    return 0;
}
