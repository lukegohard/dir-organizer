#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#include "src/helpers.h"

void organizer(const char *path);

int main(int argc, char *argv[]) {
	cleanConsole();

	// Il path può essere inserito tramite stringa quando viene lanciato il programma.
	// Se non viene inserito lì, verrà inserito tramite input a runtime.
	char *path;
	if (argc!=2) {
		static char buffer[256];
		printf(YEL "Enter the path to directory: " RESET);
		fgets(buffer, 256, stdin);
		buffer[strcspn(buffer, "\n")] = '\0';
		path = buffer;
	} else {
		path = argv[1];
	}
 	// Aggiungi lo slash se necessario per la directory
	if (path[strlen(path) - 1] != '/') strcat(path, "/");

	cleanConsole();

	// Se la directory inserita non esiste, ovviamente il programma non può andare avanti.
	if (!dirExists(path)) {
		printf(RED "[!] Directory does not exist!.\n" RESET);
		printf(RED "[!] Exit..\n" RESET);
		return 1;
	}

	organizer(path);

	printf(GRN "\n[+] Done.\n" RESET);
	return 0;
}

void organizer(const char *path) {
	
	struct dirent *entry;
	DIR *dir = opendir(path);
	if (dir == NULL) {
        printf(RED "[-] Cannot open directory: %s\n" RESET, path);
		return;
	}

	while((entry = readdir(dir)) != NULL) {

		const char *filename = entry->d_name;

		char fullPath[512];
        snprintf(fullPath, sizeof(fullPath), "%s%s", path, filename);

        // Salta le dir "." e ".."
        if (strcmp(filename, ".") == 0 || strcmp(filename, "..") == 0) continue;

		struct stat st;
		if (stat(fullPath, &st) == 0) {

			// se l'elemento che viene trovato è una directory, viene lanciata nuovamente la funzione,
			// in modo da organizzare anche le sottocartelle.
			if (S_ISDIR(st.st_mode)) { 

				printf(BLU "[+] Found directory: %s\n" RESET, fullPath);
				              
				// Aggiungi lo slash se necessario per la sottodirectory
                if (fullPath[strlen(fullPath) - 1] != '/') strcat(fullPath, "/");
				
				organizer(fullPath);

			} else if (S_ISREG(st.st_mode)) {
				
				/* 
					se invece l'elemento trovato è un file,
					viene spostato in una cartella(creata se non esiste) in base alla sua estensione.
					I file senza estensione rimarranno nella cartella principale.
				*/

				printf(CYN "[*] Processing file: %s\n" RESET, fullPath);

				const char *ext = strrchr(filename, '.');

				if (ext != NULL && strlen(ext) > 1) {

					char destDir[512];
					snprintf(destDir, sizeof(destDir), "%s%s/", path, ext+1);

					if (!dirExists(destDir)) {
						if (createDir(destDir) != 0) {
							printf(RED "[!] Error in createDir(%s).\n" RESET, destDir);
						}
					}

					char destFile[512];
					snprintf(destFile, sizeof(destFile), "%s%s", destDir, filename);

					if (moveFile(fullPath, destFile) != 0) {
						printf(RED "[!] Error moving file: %s\n" RESET, filename);
					}
				}

			} else { // file non regolare
            	printf(RED "[!] Not a regular file: %s\n" RESET, fullPath);
			}	 
		}
	}
	closedir(dir);
}