#include <stdio.h>
#include <sys/stat.h>

#define RESET "\x1B[0m"
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"

int dirExists(const char *path);
int createDir(const char *path);
int moveFile(const char *src, const char *dest);

void cleanConsole();

// Verifica se una directory esiste o no
int dirExists(const char *path) {
    struct stat info;

    // Usare stat() per ottenere informazioni sul path
    if (stat(path, &info) != 0) {
        // Se stat fallisce, il path non esiste
        return 0;
    }
    // Controllare se è una directory
    return (info.st_mode & S_IFDIR) != 0;
}

// Crea una directory
int createDir(const char *path) {
    return mkdir(path, 0775);
}

// Sposta src in dest
int moveFile(const char *src, const char *dest) {
    return rename(src, dest);
}

void cleanConsole() {
    printf("\033[H\033[J");
}