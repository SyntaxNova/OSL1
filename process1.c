#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define PIPE1 "/tmp/pipe1"  // FIFO for sending data from process 1 to process 2
#define PIPE2 "/tmp/pipe2"  // FIFO for sending data from process 2 to process 1

int main() {
    char sentence[256];
    char output[512];
    int fd_write, fd_read;

    // Create FIFOs
    mkfifo(PIPE1, 0666);
    mkfifo(PIPE2, 0666);

    // Get input from user
    printf("Enter a sentence: ");
    fgets(sentence, 256, stdin);

    // Write sentence to PIPE1
    fd_write = open(PIPE1, O_WRONLY);
    write(fd_write, sentence, strlen(sentence) + 1);
    close(fd_write);

    // Read output from PIPE2
    fd_read = open(PIPE2, O_RDONLY);
    read(fd_read, output, sizeof(output));
    printf("Received output:\n%s", output);
    close(fd_read);

    // Remove FIFOs after use
    unlink(PIPE1);
    unlink(PIPE2);

    return 0;
}

