#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int g;

int main(int argc, char **argv)
{
	printf("pid=%d\n",getpid());

	pid_t pid=fork();

	if (pid<0)
	{
		printf("erreur\n");
	}

	if (pid==0) // Je suis le fils
	{
		// Boulot de fils

		g=42;
		sleep(1);

		printf("Je suis %d et g=%d\n", (int)getpid(),g);
		printf("Mon pere est %d\n", (int)getppid());

		// faire du boulot prend du temps.

		// while (1);

		exit(0);

		// Je deviens un zombie
	}
	else if (pid>0)
	{
		g=21;
		sleep(200);
		printf("g=%d\n",21);
		sleep(200);

		wait(NULL);

		sleep(1);

		// Boulot de père
		// pid identifie le processus fils

		printf("Je suis %d (%d)\n", (int)getpid(),(int)pid);
	}

	return 0;
}
