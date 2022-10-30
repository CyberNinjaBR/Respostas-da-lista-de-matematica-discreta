#include <stdio.h>

//funcao que calcula o MDC de dois numeros
int euclides(int num1, int num2)
{
    int a;

    if(num1 > num2)
    {
        a = num1 % num2;

        if(a == 0)
        {
            return num2;
        }
        else
        {
            euclides(num2, a);
        }
    }
    else
    {
        a = num2 % num1;

        if(a == 0)
        {
            return num1;
        }
        else
        {
            euclides(num1, a);
        }
    }
}


int main()
{
    int num1, num2;

    printf("Digite 2 números inteiros para o cálculo do MDC por algorítmo de euclides\n");
    scanf("%d%d", &num1, &num2);

    printf("%d\n", euclides(num1, num2));

    printf("resto: %d\n", 6%5);

    return 0;
}