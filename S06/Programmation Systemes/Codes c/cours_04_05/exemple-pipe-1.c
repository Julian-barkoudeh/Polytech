// ------------------------------------------------------------------
// exemple-pipe-1.c
// Fichier d'exemple du livre "Developpement Systeme sous Linux"
// (C) 2000-2019 - Christophe BLAESS <christophe@blaess.fr>
// https://www.blaess.fr/christophe/
// ------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (void)
{
	int pipe_fd[2];
	unsigned char buffer[256];
	int i;

	// 0 stdin indice d'un descripteur de fichier  dans la table des descripteurs	NE PAS CONFONDRE avec le fichier lui-même  terminal
	// 1 stdout 														terminal
	// 2 stderr														terminal

	fprintf(stdout, "Creation du pipe\n");
	// 3 entree du pipe
	// 4 sortie du pipe 
	if (pipe(pipe_fd) != 0) {
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	for (i = 0; i < 256; i ++)
		buffer[i] = i;
	fprintf(stdout, "Ecriture dans le pipe\n");
	if (write(pipe_fd[1], buffer, 256) != 256) {
		perror("write");
		exit(EXIT_FAILURE);
	}
	fprintf(stdout, "Lecture depuis le pipe\n");
	if (read(pipe_fd[0], buffer, 256) != 256) {
		perror("read");
		exit(EXIT_FAILURE);
	}
	fprintf(stdout, "Verification...");
	for (i = 0; i < 256; i ++)
		if (buffer[i] != i) {
			fprintf(stdout, "Erreur : i=%d buffer[i]=%d\n",
				i, buffer[i]);
			exit(EXIT_FAILURE);
		}
	fprintf(stdout, "Ok\n");

	return EXIT_SUCCESS;
}

