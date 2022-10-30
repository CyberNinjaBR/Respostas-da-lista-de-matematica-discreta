#include <stdio.h>
#include <math.h>


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
void fatorar(int num, int divisor, long fator[], long tamanho)
{
    int resultado;
    if(num == 1)
    {
        fator[tamanho] = -1;
        return;
    }
    else
    { 
        if(primo(divisor) == 1 && (num % divisor == 0))
        {
            num = num / divisor;
            fator[tamanho] = divisor;
            fatorar(num, 2, fator, (tamanho + 1));
        }
        else
        {
            fatorar(num, (divisor + 1), fator, tamanho);
        }
    }
}


//Funcao que lê o vetor fator e organiza ele em um novo vetor resultado (mais curto) e vetor expoente
void ler_vetor_e_organizar_potencias(long fator[], long expoente[], long fatororg[], long tamanho, long expo, long tamanhoorg, long old_input)
{
    if(fator[tamanho] == -1)
    {
        fatororg[tamanhoorg] = -1;
        fatororg[tamanhoorg + 1] = -1;
        fatororg[tamanhoorg + 1] = -1;
        fatororg[tamanhoorg + 1] = -1;
        expoente[expo + 1] = -1;
        expoente[expo + 1] = -1;
        expoente[expo + 1] = -1;
        expoente[expo + 1] = -1;
        return;
    }
    else
    {
        if(tamanho == 0)
        {
            fatororg[tamanhoorg] = fator[tamanho];
            expoente[expo] = 0 + 1;
            old_input = fator[tamanho];
            ler_vetor_e_organizar_potencias(fator, expoente, fatororg, (tamanho + 1), expo, (tamanhoorg + 1), old_input);
        }
        else if(fator[tamanho] == old_input)
        {
            expoente[expo] += 1;
            old_input = fator[tamanho];
            ler_vetor_e_organizar_potencias(fator, expoente, fatororg, (tamanho + 1), expo, tamanhoorg, old_input);
        }
        else if(fator[tamanho] != old_input)
        {
            old_input = fator[tamanho];
            fatororg[tamanhoorg] = fator[tamanho];
            expoente[(expo + 1)] = 1;
            ler_vetor_e_organizar_potencias(fator, expoente, fatororg, (tamanho + 1), (expo + 1), (tamanhoorg + 1), old_input);
        }
    }
}


//Funcao que calcula o MMC de dois números
int mmc(long fator1org[], long fator2org[], long expoente1[], long expoente2[], long tamanho, long MMC)
{
    if((fator1org[tamanho] == -1) && (fator2org[tamanho] == -1))
    {
        return MMC;
    }
    else if((fator1org[tamanho] == -1) && (fator2org[tamanho] != -1))
    {
        MMC = MMC * pow(fator2org[tamanho], expoente2[tamanho]);
        mmc(fator1org, fator2org, expoente1, expoente2, (tamanho + 1), MMC);
    }
    else if((fator1org[tamanho] != -1) && (fator2org[tamanho] == -1))
    {
        MMC = MMC * pow(fator1org[tamanho], expoente1[tamanho]);
        mmc(fator1org, fator2org, expoente1, expoente2, (tamanho + 1), MMC);
    }
    else
    {
        if(fator1org[tamanho] == fator2org[tamanho]) //caso o numerador seja o mesmo
        {
            if(expoente1[tamanho] > expoente2[tamanho]) //se o expoente1 for maior
            {
                MMC = MMC * pow(fator1org[tamanho], expoente1[tamanho]);
            }
            else if(expoente1[tamanho] < expoente2[tamanho]) //se o expoente2 for maior
            {
                MMC = MMC * pow(fator1org[tamanho], expoente2[tamanho]);
            }
            else //se os expoentes forem iguais
            {
                MMC = MMC * pow(fator1org[tamanho], expoente1[tamanho]);
            }

            mmc(fator1org, fator2org, expoente1, expoente2, (tamanho + 1), MMC);
        }
        else if(fator1org[tamanho] != fator2org[tamanho]) //caso o numerador seja diferente
        {
            MMC = MMC * pow(fator1org[tamanho], expoente1[tamanho]);
            MMC = MMC * pow(fator2org[tamanho], expoente2[tamanho]);

            mmc(fator1org, fator2org, expoente1, expoente2, (tamanho + 1), MMC);
        }
    }
}


//Funcao que calcula o MDC
int mdc(long fator1org[], long fator2org[], long expoente1[], long expoente2[], long tamanho, long MDC)
{
    if((fator1org[tamanho] == -1) && (fator2org[tamanho] == -1))
    {
        return MDC;
    }
    else if((fator1org[tamanho] == -1) && (fator2org[tamanho] != -1))
    {
        MDC = MDC * pow(fator2org[tamanho], expoente2[tamanho]);
        mdc(fator1org, fator2org, expoente1, expoente2, (tamanho + 1), MDC);
    }
    else if((fator1org[tamanho] != -1) && (fator2org[tamanho] == -1))
    {
        MDC = MDC * pow(fator1org[tamanho], expoente1[tamanho]);
        mdc(fator1org, fator2org, expoente1, expoente2, (tamanho + 1), MDC);
    }
    else
    {
        if(fator1org[tamanho] == fator2org[tamanho]) //caso o numerador seja o mesmo
        {
            if(expoente1[tamanho] < expoente2[tamanho]) //se o expoente1 for maior
            {
                MDC = MDC * pow(fator1org[tamanho], expoente1[tamanho]);
            }
            else if(expoente1[tamanho] > expoente2[tamanho]) //se o expoente2 for maior
            {
                MDC = MDC * pow(fator1org[tamanho], expoente2[tamanho]);
            }
            else //se os expoentes forem iguais
            {
                MDC = MDC * pow(fator1org[tamanho], expoente1[tamanho]);
            }

            mdc(fator1org, fator2org, expoente1, expoente2, (tamanho + 1), MDC);
        }
        else if(fator1org[tamanho] != fator2org[tamanho]) //caso o numerador seja diferente
        {
            MDC = MDC * pow(fator1org[tamanho], 0);
            MDC = MDC * pow(fator2org[tamanho], 0);

            mdc(fator1org, fator2org, expoente1, expoente2, (tamanho + 1), MDC);
        }
    }
}


int main()
{
    long num1, num2, MDC, MMC, i;
    long fator1[300], fator2[300];
    long fator1org[300], fator2org[300];
    long expoente1[300], expoente2[300];

    printf("Digite 2 números inteiros para o cálculo do MDC e MMC\n");
    scanf("%ld%ld", &num1, &num2);

    fatorar(num1, 2, fator1, 0);
    fatorar(num2, 2, fator2, 0);

    ler_vetor_e_organizar_potencias(fator1, expoente1, fator1org, 0, 0, 0, 0);
    ler_vetor_e_organizar_potencias(fator2, expoente2, fator2org, 0, 0, 0, 0);


    printf("\n%ld = ", num1);
    for(i = 0; fator1org[i] != -1; i++)
    {
        if(fator1org[i + 1] == -1)
        {
            printf("(%ld ^ %ld)\n", fator1org[i], expoente1[i]);    
        }
        else
        {
            printf("(%ld ^ %ld) * ", fator1org[i], expoente1[i]);    
        }
    }

    printf("%ld = ", num2);
    for(i = 0; fator1org[i] != -1; i++)
    {
        if(fator1org[i + 1] == -1)
        {
            printf("(%ld ^ %ld)\n", fator2org[i], expoente2[i]);    
        }
        else
        {
            printf("(%ld ^ %ld) * ", fator2org[i], expoente2[i]);    
        }
    }
    

    MMC = mmc(fator1org, fator2org, expoente1, expoente2, 0, 1);
    MDC = mdc(fator1org, fator2org, expoente1, expoente2, 0, 1);
    printf("\nMMC: %ld\nMDC: %ld\n", MMC, MDC);

    return 0;
}