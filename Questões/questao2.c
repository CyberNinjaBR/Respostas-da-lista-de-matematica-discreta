#include <stdio.h>
#include <signal.h> // utilizada para as funções do signal
#include <stdlib.h>
#include <unistd.h>

void exitfunc(int sig) // função que recebe o sinal e sai do programa fazendo com que os imprima o máximo de números primos em 60s
{
    exit(0);
}


int chamada(int n, int primo)
{
    int i, cont = 0;

    for(i = 1; i<= n; i++)
    {
        if(n % i == 0)
        {
            cont++;
        }
    }
    
    if(cont == 2)
    {
        printf("%d\t", n);
        chamada(++n, ++primo);
    }
    else
    {
        chamada(++n, primo);
    }
}
int main()
{
    signal(SIGALRM, exitfunc);// recebe o sinal da função alarm após 60 segundos e manda para função exitfunc
    // a função signal signal () define a disposição do sinal signum para manipulador, que é SIG_IGN, SIG_DFL ou o endereço de uma função definida pelo programador (um "manipulador de sinal")
    alarm(60); // utilizado para definir um dispertador para a entrega de um sinal, no caso vamos entregar ele para essa função signal

    chamada(0, 0);

    return 0; 
}