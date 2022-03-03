// ------------------------------------------------------------------
// exemple-pipe-3.c
// Fichier d'exemple du livre "Developpement Systeme sous Linux"
// (C) 2000-2019 - Christophe BLAESS <christophe@blaess.fr>
// https://www.blaess.fr/christophe/
// ------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>

// Descripteur de fichier (partie du process)	Fichier (ne fait pas partie du process)

// Le pere
// 0 stdin					terminal, vers l'entree du pipe
// 1 stdout					terminal
// 2 stderr					terminal
// 3 pipe_fd[0] 3 est recopié dans 0		entree du pipe dans le noyau
// 4 pipe_fd[1] 				sortie du pipe dans le noyau ferme par le pere

// le fils
// 0' stdin					terminal
// 1' stdout					terminal, vers la sortie du pipe
// 2' stderr					terminal
// 3' pipe_fd[0]				entree du pipe dans le noyau ferme par le fils
// 4' pipe_fd[1] 4' est recopie dans 1'		sortie du pipe dans le noyau

// Le fils exécute la commande argv[1] et envoie le résultat comme entrée de la commande argv[2], confiee au père
// Le pipe est l'intermédiaire

int main (int argc, char * argv[])
{
	int	pipe_fd[2];

	if (argc != 3) {
		fprintf(stderr, "Syntaxe : %s commande_1 commande_2\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	//int osef_fd=open("ei2i3.txt",O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

	if (pipe(pipe_fd) != 0) {
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	switch (fork()) {
		case -1 :
			perror("fork()");
			exit(EXIT_FAILURE);
			break;
		case 0 :
			// Le fils ferme l'entree du pipe, car il ne fait qu'écrire dedans
			close(pipe_fd[0]);
			dup2(pipe_fd[1], STDOUT_FILENO);
			system(argv[1]);
			break;
		default :
			// Le pere ferme la sortie du pipe, car il ne fait que lire dedans
			close(pipe_fd[1]);
			dup2(pipe_fd[0], STDIN_FILENO);
			system(argv[2]);
			break;
	}

	//close(osef_fd);

	return EXIT_SUCCESS;
}

