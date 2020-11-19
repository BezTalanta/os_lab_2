/*
  Вариант 19:
  Родитель считывает строки и кидает в соотношении 80% на 20% в первого или второго ребенка соответственно.
  Дети выводят строку в два файла, введеных из родителя, убираю из каждой строки гласные.
*/

#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include "lab_2.h"

const int SIZE_OF_CHARS = 200;

int main(){
	srand(time(0));

	char path1[200] = "",path2[200] = "";

	char t[200] = "Введи в следующий двух строках - пути к файлам, куда я буду отправлять выходные данные ^_^\n";
	write(0,t,sizeof(char) * 200);

	read(0,path1,sizeof(char)*200);
	read(0,path2,sizeof(char)*200);

	int path1Len = strlen(path1);
	int path2Len = strlen(path2);

	path1[path1Len-1] = '\0';
	path2[path2Len-1] = '\0';

	int check = open(path1,O_CREAT,S_IRWXU);
	int check2 = open(path2,O_CREAT,S_IRWXU);

	if(check == -1 || check2 == -1){
		char k[200] = "Something wrong!\n";
		write(0,k,sizeof(char) * 200);
		return 1;
	}

	int ft1 = open(path1,O_WRONLY);
	int ft2 = open(path2,O_WRONLY);

	if(ft1 == -1 || ft2 == -1){
		char k[200] = "Something wrong!\n";
		write(0,k,sizeof(char) * 200);
		return 1;
	}

	int fd[2];
	int fd2[2];
	if(pipe(fd) < 0 || pipe(fd2) < 0){
		char a[50] = "Проблемы с пайпами\n";
		write(0,a,50*sizeof(char));
		return 1;
	}

	int id = fork();
	int id2 = fork();

	char in[SIZE_OF_CHARS];
	if(id != 0 && id2 != 0){
		char a[50] = "Введите свои строки\n";
		write(0,a,50*sizeof(char));
		while((scanf("%s",in)) == 1){
			fflush(stdout);
			if(rand() % 100 < 80){
				//printf("First - ");
				char a[50] = "First file\n";			
				write(0,a,50*sizeof(char));
				write(fd[1],in,SIZE_OF_CHARS * sizeof(char));
			}
			else{
				char a[50] = "Second file\n";			
				write(0,a,50*sizeof(char));
				write(fd2[1],in,SIZE_OF_CHARS * sizeof(char));
			}
		}
		
		char g = '*';
		write(fd[1],&g,sizeof(char));
		write(fd2[1],&g,sizeof(char));
	}
	else if(id2 == 0 && id != 0){
		while(1){
			fflush(stdout);
			char str[SIZE_OF_CHARS];
			read(fd2[0],str,SIZE_OF_CHARS * sizeof(char));
			if(str[0] == '*'){
				break;
			}
			write(ft2,Task(str),sizeof(char) * 200);
		}
	}
	else if(id == 0 && id2 != 0){
		while(1){
			fflush(stdout);
			char str[SIZE_OF_CHARS];
			read(fd[0],str,SIZE_OF_CHARS * sizeof(char));
			if(str[0] == '*'){
				break;
			}
			write(ft1,Task(str),sizeof(char) * 200);
		}
	}

	close(fd[0]);
	close(fd[1]);
	close(fd2[0]);
	close(fd2[1]);
	close(ft1);
	close(ft2);
	return 0;
}
