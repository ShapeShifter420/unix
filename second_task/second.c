#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <signal.h>


int locks = 0;

int get_size(int value){
	int size = 0;
	do{
		size++;
		value = value / 10;
	}
	while(value>0);
	return size;
}
void handler(int n)
{ 	
	int fd = -1;
	while (fd == -1)
		{
			fd = open("stat_file", O_CREAT | O_APPEND| O_RDWR, S_IRWXU);
		}
	errno = 0;
	int size = get_size(locks);
	char* s = malloc(size + 2);
	snprintf(s, size + 2, "%d\n", locks);
	write(fd, s, size+1);
	if (errno){printf("Ошибка записи в файл\n");exit(1);}
	close(fd);
	exit(0);
}


int main(int argc, char *argv[])
{	
	int pid = getpid();
	signal(SIGINT, handler);
	if (errno){printf("Ошибка установки обработчика\n");return 1;}

	char* fileLock = "file.lck";
	double offset_time = (pid % 10)/100;
	while (1)
	{
		int fd = -1;
		while (fd == -1)
		{
			fd = open(fileLock,O_RDWR | O_EXCL | O_CREAT , S_IRWXU);
			sleep(0.1 + offset_time);
		}
		errno = 0;
		
		locks++;
		
		
		int size = get_size(pid);
		char* ps = malloc(size + 1);
		snprintf(ps, size + 1, "%d", pid);

		write(fd, ps, size);
		if (errno){printf("Ошибка записи в файл\n");return 1;}


		int ffd = open("file", O_WRONLY);		
		if (errno){printf("Ошибка открытия файла\n");return 1;}
		sleep(1);
		close(ffd);
		if (errno){printf("Ошибка закрытия файла\n");return 1;}
		
		lseek(fd, 0, SEEK_SET);
		read(fd, ps, size + 1);
		if (errno){printf("Ошибка чтения файла\n");free(ps);return 1;}
		
		int read_pid = atoi(ps);
		if (read_pid != pid){printf("pid не совпали\n");free(ps);return 1;}
		free(ps);
		close(fd);

		if (errno){printf("Ошибка закрытия файла\n");return 1;}
		unlink(fileLock);
		if (errno){printf("Ошибка удаления файла\n");return 1;}
	}
	return 0;
}

