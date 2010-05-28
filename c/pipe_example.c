#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void writer(FILE* stream)
{
	char a[20];
	int i;
	for (i=0;i<5;i++)
	{
		printf("introduceti un mesaj in pipe");
		gets(a);
		fprintf(stream,"%s\n",a);
		fflush(stream);
	}
}
void reader(FILE* stream)
{
	char buffer[100];
	while (!feof(stream) && fgets(buffer,sizeof(buffer),stream) !=NULL)
	{
		printf("%s\n",buffer);
	}
}
int main (void)
{
	pid_t pid;
	int fds[2];
	
	int pipe_fds[2];
	pipe (pipe_fds);
	
	pipe (fds);
	
	pid=fork();
	
	if (pid == (pid_t) 0) 
	{
		FILE* stream;
		printf("Process  F \n");
		close (fds[1]);
		stream = fdopen (fds[0],"r");
		reader(stream);
		
	}
	else
	{
		printf("Proces P\n");
		FILE* stream;
		close(fds[0]);
		stream=fdopen(fds[1],"w");
		writer(stream);
		close (fds[1]);
	}
}
