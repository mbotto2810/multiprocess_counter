#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>

#define max_filhos 3
#define max_num 100

int primo(int n) {
	int i, flag = 1;
    if ( n==0 || n==1 ) {
        return 0;
    }

	for (i = 2; i <= n / 2; ++i) {
	if (n % i == 0) {
	    flag = 0;
	    break;
	    }
	}
	return flag;
}

int main() {
	int vet[max_num];
	int n,i=0;
	char c;
	pid_t filhos[max_filhos];

	int protection = PROT_READ | PROT_WRITE;
	int visibility = MAP_SHARED | MAP_ANON;

	int *b;
	b = (int*) mmap(NULL, sizeof(int), protection, visibility, 0, 0);
	if ((long int)b==-1) printf("Erro de alocacao!\n");
	(*b)=0;

	do {
		scanf("%d", &n);
		vet[i] = n;
		i++;
	} while (c = getchar() != '\n');

    for (int y=i ; y<max_num ; y++){
        vet[y] = 0;
    }




    filhos[0] = fork();

    if (filhos[0] == 0) {
        /* Child A code */
         for (int k=0 ; k < 100 ; k++) {
                if ( k % 4 == 1) {
                     *b += primo(vet[k]);
                       // printf("Estou no filho 1 com indice %d e valor %d\n",k,vet[k]);
                    }
            }
         exit(0);
    } else {
        filhos[1] = fork();

        if (filhos[1] == 0) {
            /* Child B code */
         for (int k=0 ; k < 100 ; k++) {
                if ( k % 4 == 2) {
                    *b += primo(vet[k]);
                       // printf("Estou no filho 1 com indice %d e valor %d\n",k,vet[k]);
                    }
            }
         exit(0);
        } else {
           filhos[2] = fork();

            if (filhos[2] == 0 ) {
            /* Child C code */
             for (int k=0 ; k < 100 ; k++) {
                if ( k % 4 == 3) {
                    *b += primo(vet[k]);
                       // printf("Estou no filho 1 com indice %d e valor %d\n",k,vet[k]);
                    }
             }
         exit(0);

            } else {
            /* Parent code */
            for (int k=0 ; k<100 ;k++ ){
                if ( k % 4 == 0) {
                        //printf("Estou no pai com indice %d e valor %d\n",k,vet[k]);
                        *b += primo(vet[k]);
                    }
            }
        }
    }
}


	for (int x=0; x<max_filhos; x++) {
		waitpid(filhos[x], NULL, 0);
    }

	printf("%d\n",*b);
	return 0;
}
