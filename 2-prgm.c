#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#define BUFFER_SIZE 4096
int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source_file> <destination_file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    int source_fd = open(argv[1], O_RDONLY);
    if (source_fd == -1) {
        perror("open source file");
        exit(EXIT_FAILURE);
    }
    int dest_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (dest_fd == -1) {
        perror("open destination file");
        close(source_fd);
        exit(EXIT_FAILURE);
    }
    char buffer[BUFFER_SIZE];
    ssize_t bytesRead, bytesWritten;
    while ((bytesRead = read(source_fd, buffer, BUFFER_SIZE)) > 0) {
        bytesWritten = write(dest_fd, buffer, bytesRead);
        if (bytesWritten != bytesRead) {
            perror("write error");
            close(source_fd);
            close(dest_fd);
            exit(EXIT_FAILURE);
        }
    }
    close(source_fd);
    close(dest_fd);
    printf("File copy successful.\n");
    return 0;
}
