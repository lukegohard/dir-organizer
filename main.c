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
					
					// Videos extensions
					if (strcmp(ext, ".mp4") == 0 || strcmp(ext, ".mkv") == 0 || strcmp(ext, ".avi") == 0 || 
						strcmp(ext, ".mov") == 0 || strcmp(ext, ".wmv") == 0 || strcmp(ext, ".flv") == 0) {
						snprintf(destDir, sizeof(destDir), "%s%s/", path, "Videos");
					
					// Images extensions
					} else if (strcmp(ext, ".jpg") == 0 || strcmp(ext, ".jpeg") == 0 || strcmp(ext, ".png") == 0 || 
							strcmp(ext, ".gif") == 0 || strcmp(ext, ".bmp") == 0 || strcmp(ext, ".tiff") == 0 || 
							strcmp(ext, ".svg") == 0 || strcmp(ext, ".ico") == 0) {
						snprintf(destDir, sizeof(destDir), "%s%s/", path, "Images");

					// Audio extensions
					} else if (strcmp(ext, ".mp3") == 0 || strcmp(ext, ".wav") == 0 || strcmp(ext, ".flac") == 0 || 
							strcmp(ext, ".aac") == 0 || strcmp(ext, ".ogg") == 0 || strcmp(ext, ".m4a") == 0) {
						snprintf(destDir, sizeof(destDir), "%s%s/", path, "Audio");
					
					// Archives extensions
					} else if (strcmp(ext, ".zip") == 0 || strcmp(ext, ".rar") == 0 || strcmp(ext, ".7z") == 0 || 
							strcmp(ext, ".tar") == 0 || strcmp(ext, ".gz") == 0 || strcmp(ext, ".iso") == 0) {
						snprintf(destDir, sizeof(destDir), "%s%s/", path, "Archives");

					// Documents extensions
					} else if (strcmp(ext, ".pdf") == 0 || strcmp(ext, ".doc") == 0 || strcmp(ext, ".docx") == 0 || 
							strcmp(ext, ".txt") == 0 || strcmp(ext, ".rtf") == 0 || strcmp(ext, ".odt") == 0 || 
							strcmp(ext, ".xls") == 0 || strcmp(ext, ".xlsx") == 0 || strcmp(ext, ".ppt") == 0 || 
							strcmp(ext, ".pptx") == 0) {
						snprintf(destDir, sizeof(destDir), "%s%s/", path, "Documents");

					// Data extensions
					} else if (strcmp(ext, ".csv") == 0 || strcmp(ext, ".json") == 0 || strcmp(ext, ".xml") == 0 || 
							strcmp(ext, ".sql") == 0) {
						snprintf(destDir, sizeof(destDir), "%s%s/", path, "Data");

					// Code extensions
					} else if (strcmp(ext, ".c") == 0 || strcmp(ext, ".cpp") == 0 || strcmp(ext, ".h") == 0 || 
							strcmp(ext, ".java") == 0 || strcmp(ext, ".py") == 0 || strcmp(ext, ".js") == 0 || 
							strcmp(ext, ".html") == 0 || strcmp(ext, ".css") == 0 || strcmp(ext, ".php") == 0) {
						snprintf(destDir, sizeof(destDir), "%s%s/", path, "Code");

					// Executables extensions
					} else if (strcmp(ext, ".exe") == 0 || strcmp(ext, ".bat") == 0 || strcmp(ext, ".sh") == 0 || 
							strcmp(ext, ".msi") == 0 || strcmp(ext, ".apk") == 0 || strcmp(ext, ".jar") == 0) {
						snprintf(destDir, sizeof(destDir), "%s%s/", path, "Executables");

					// Config extensions
					} else if (strcmp(ext, ".ini") == 0) {
						snprintf(destDir, sizeof(destDir), "%s%s/", path, "Config");
					
					// Logs extensions
					} else if (strcmp(ext, ".log") == 0) {
						snprintf(destDir, sizeof(destDir), "%s%s/", path, "Logs");

					// Default ('.aaa' => aaa/)
					} else {
						snprintf(destDir, sizeof(destDir), "%s%s/", path, "Others"); // Nome cartella in base all'estensione
					}

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