#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>

int my_read(int fd,char *buffer, int count)
{
	int n_read;
	int read_count=0;
	int offset=0;

	while (read_count<count)
	{
		n_read=read(fd,buffer+offset,1000);
		read_count+=n_read;
		offset+=n_read;
		printf("n_from=%d errno=%d ",n_read,errno);
		printf("read_count=%d offset=%d\n",read_count,offset);
	}
	
}

int main(int argc, char **argv)
{
	char buffer[20000];
	int n_from;
	int n_to;

	int from_fd=open(argv[1],O_RDONLY,0);
	int to_fd=open(argv[2],O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

	printf("from_fd=%d to_fd=%d\n",from_fd,to_fd);

	do
	{
		//n_from=read(from_fd,buffer,10000);
		n_from=my_read(from_fd,buffer,10000);
		printf("n_from=%d errno=%d\n",n_from,errno);
		n_to=write(to_fd,buffer,n_from);
		printf("n_to=%d errno=%d\n",n_to,errno);
	} while (n_from>0);
 
	close(from_fd);
	close(to_fd);

	return 0;
}
