#include <stdio.h>

//Fun??o que checa se os n?meros s?o primos
int primo(int num)
{
    int contador = 0, i;

    for (i = 1; i <= num; i++)
    {
        if(num % i == 0)
        {
            ++contador;
        }
    }

    if(contador == 2)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


//Funcao que fatora qualquer numero
void fatorar(int num, int divisor)
{
    int resultado;
    if(num == 1)
    {
        return;
    }
    else
    { 
        if(primo(divisor) == 1 && (num % divisor == 0))
        {
            num = num / divisor;
            if(num == 1)
            {
                printf("%d\n", divisor);
            }
            else
            {
                printf("%d * ", divisor);
            }
            fatorar(num, 2);
        }
        else
        {
            fatorar(num, (divisor + 1));
        }
    }
}


int main()
{
    int num, primos;

    printf("Digite o valor a ser fatorado:\n");
    scanf("%d", &num);
    
    fatorar(num, 2);
    
    return 0;
}