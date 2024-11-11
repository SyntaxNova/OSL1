#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define PIPE1 "/tmp/pipe1"  // FIFO for receiving data from process 1
#define PIPE2 "/tmp/pipe2"  // FIFO for sending data to process 1

void count_characters_words_lines(char *text, int *char_count, int *word_count, int *line_count) {
    *char_count = *word_count = *line_count = 0;
    int i = 0;

    while (text[i] != '\0') {
        (*char_count)++;
        if (text[i] == ' ' || text[i] == '\n' || text[i] == '\t') {
            (*word_count)++;
        }
        if (text[i] == '\n') {
            (*line_count)++;
        }
        i++;
    }
    if (text[i-1] != '\n') {
        (*line_count)++;  // Increment line count for the last line if it doesn't end with a newline
    }
    if (text[i-1] != ' ' && text[i-1] != '\n' && text[i-1] != '\t') {
        (*word_count)++;  // Increment word count for the last word if it doesn't end with a space
    }
}

int main() {
    char sentence[256];
    int char_count, word_count, line_count;
    int fd_read, fd_write;
    FILE *output_file;

    // Open FIFO to read sentence from process 1
    fd_read = open(PIPE1, O_RDONLY);
    read(fd_read, sentence, sizeof(sentence));
    close(fd_read);

    // Perform counting
    count_characters_words_lines(sentence, &char_count, &word_count, &line_count);

    // Write output to text file
    output_file = fopen("output.txt", "w");
    fprintf(output_file, "Characters: %d\nWords: %d\nLines: %d\n", char_count, word_count, line_count);
    fclose(output_file);

    // Read file content and send to PIPE2
    output_file = fopen("output.txt", "r");
    char output[512];
    fread(output, sizeof(char), sizeof(output), output_file);
    fclose(output_file);

    // Write output to PIPE2
    fd_write = open(PIPE2, O_WRONLY);
    write(fd_write, output, strlen(output) + 1);
    close(fd_write);

    return 0;
}

