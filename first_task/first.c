#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
int main(int argc, char **argv){
int BLOCK_SIZE = 4096;    
char block[BLOCK_SIZE];
int fd1 = 0;
int fd2 = 1;
if (argc > 2){
	fd1 = open(argv[1],O_RDONLY);
	fd2 = open(argv[2],O_WRONLY | O_CREAT,775);

	if (argc == 4)
		BLOCK_SIZE = atoi(argv[3]);
	}
    else fd2 = open(argv[1],O_WRONLY | O_CREAT,775);
    if (errno)
        {printf("Ошибка открытия файла");
        return 1;}
while(BLOCK_SIZE = read(fd1,block,BLOCK_SIZE)){
    if (errno)
        {printf("Ошибка чтения файла");
        return 1;}
    if (check_zero_block(block,BLOCK_SIZE)){
        lseek(fd2,BLOCK_SIZE,SEEK_CUR);}
    else{
        if (errno)
        {printf("Ошибка записи в файл");
        return 1;}
        write(fd2,block,BLOCK_SIZE);}}
close(fd2);

}

int check_zero_block(char *block,int size){
    for (int i = 0;i<size;i++){
        if (block[i] != 0){
            return 0;}}
    return 1;   

    }