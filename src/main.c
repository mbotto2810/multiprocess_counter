#include <stdio.h>
#include <stdlib.h> /* exit() */
#include <sys/types.h> /* define pid_t */
#include <unistd.h> /* fork() */
#include <sys/wait.h>
#include <sys/mman.h>

int primo(int n) {
	int i, flag = 1;

	for (i = 2; i <= n / 2; ++i) {
	if (n % i == 0) {
	    flag = 0;
	    break;
	}
	}
	return flag;
}

int main() {
	int vet[100];
	int k, n , i=0;
	char c;
	pid_t pid[3];

	int protection = PROT_READ | PROT_WRITE;
	int visibility = MAP_SHARED | MAP_ANON;

	//no b armazeno primos
	int *b;
	b = (int*) mmap(NULL, sizeof(int), protection, visibility, 0, 0);
	if ((long int)b==-1) printf("Erro de alocacao!\n");
	(*b)=0;

	do {
		scanf("%d", &n);
		vet[i] = n;
		i++;
	} while (c = getchar() != '\n');

	switch (i) {
		case 1:
			*b += primo(vet[0]);
			break;
		case 2:
			*b += primo(vet[0]);
			pid[0] = fork();
			//Chamada de fork processo filho
			if (pid[0]==0) {
				*b += primo(vet[1]);
				printf("Estou no filho\n");
				exit(0);
			}
			break;
		case 3:
			*b += primo(vet[0]);
			pid[0] = fork();
			pid[1] = fork();
			//Chamada de fork processo filho
			if (pid[0]==0) {
				*b += primo(vet[1]);
				printf("Estou no filho\n");
				exit(0);
			}
			if (pid[1]==0) {
				*b += primo(vet[2]);
				printf("Estou no filho 2\n");
				exit(0);
			}
			break;
		default:
			printf("s");
			break;
	}

	for (int k=0; k<2; k++)
		waitpid(pid[k], NULL, 0);
	printf("%d\n",*b);
	return 0;
}
