#include <stdio.h>

int primo(int num, int divisor)
{
    if(num > 1)
    {
        if(num <= divisor)
        {
            return 1;
        }

        else if(num % divisor == 0)
        {
            return 1 + primo(num, divisor + 1);
        }

        else
        {
            return 0 + primo(num, divisor + 1);
        }
    }
    else
    {
        return 3;
    }
}

int main()
{
    int num, resultado;

    printf("Digite o valor a ser testado:\n");
    scanf("%d", &num);

    resultado = primo(num, 1);

    if(resultado == 2)
    {
        printf("O valor %d é primo\n", num);    
    }
    else
    {
        printf("O valor %d não é primo\n", num);
    }

    return 0;
}