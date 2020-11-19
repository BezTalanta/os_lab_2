#include "lab_2.h"
#include "malloc.h"

char * Task(char * l){
	char * res = malloc(sizeof(char) * 200);
	int curId = 0;
	for (int i = 0; i < strlen(l); i++)
	{
		char cur = l[i];
		if(!(cur == 'a' || cur == 'A' || cur == 'u' || cur == 'U' || cur == 'y' || cur == 'Y' || cur == 'o' || cur == 'O' || cur == 'i' || cur == 'I' || cur == 'e' || cur == 'E')){
			res[curId] = cur;
			curId++;
		}
	}
	
	int resL = strlen(res);
	res[resL] = '\n';
	return res;
}
