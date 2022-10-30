#include <stdio.h>

//funcao que calcula o MDC de dois numeros
int euclides(int num1, int num2, int divisores[], int tamanho, int cont[])
{
    int resto;

    if(num1 > num2)
    {
        resto = num1 % num2;

        if(resto == 0)
        {
            divisores[tamanho] = -1;
            return num2;
        }
        else
        {
            cont[0] = cont[0] + 1;
            divisores[tamanho] = num1 / num2;
            euclides(num2, resto, divisores, (tamanho + 1), cont);
        }
    }
    else
    {
        resto = num2 % num1;

        if(resto == 0)
        {
            divisores[tamanho] = -1;
            return num1;
        }
        else
        {
            cont[0] = cont[0] + 1;
            divisores[tamanho] = num2 / num1;
            euclides(num1, resto, divisores, (tamanho + 1), cont);
        }
    }
}


//funcao que transforma o MDC em combinacao linar
//funcao que transforma o MDC em combinacao linar
void comblinear(int divisor[], int st[], int mdc, int contado, int old, int new, int num1, int num2, int tamanho)
{
    int intermed, i, k, multi;
    if(num1 % num2 == 0) // caso em que os números são multiplos e o num1 é maior que num2
    {
        for(i = 1; k != mdc; i++)
        {
            multi = i;
            k = num1 - (num2 * multi);
        }
        st[0] = 1;
        st[1] = - multi;
    }
    else if(num2 % num1 == 0) // caso em que os números são multiplos e o num2 é maior que o num1
    {
        for(i = 1; k != mdc; i++)
        {
            multi = i;
            k = num2 - (num1 * multi);
        }
        st[0] = 1;
        st[1] = -multi;
    }

    else if(contado < 0)
    {
        if(tamanho % 2 == 0)
        {
            st[0] = old * (-1);
            st[1] = new;
        }
        else
        {
            st[0] = old;
            st[1] = new * (-1);
        }
        
        return;
    }
    else if(divisor[contado + 1] == -1)
    {
        old = mdc;
        new = old * divisor[contado];
        comblinear(divisor, st, mdc, (contado - 1), old, new, num1, num2, tamanho);
    }
    else
    {
        intermed = old;
        old = new;
        new = (old * divisor[contado]) + intermed;
        comblinear(divisor, st, mdc, (contado - 1), old, new, num1, num2, tamanho);
    }
}


int main()
{
    int num1, num2, MDC, contador; 
    int divisor[30], cont[1] = {0}, st[2];

    printf("Digite os valores de a e b de a mod(b)\n");
    scanf("%d%d", &num1, &num2);

    MDC = euclides(num1, num2, divisor, 0, cont); // calculando o MDC e atribuindo os divisores à um vetor para nos ajudar no euclides reverso
    contador = cont[0];
    st[0] = MDC;
    comblinear(divisor, st, MDC, contador, 0, 0, num1, num2, contador); // realizando euclides reverso

    if(MDC == 1 && (num2 > 1 || num1 > 1))
    {
        if(num1 > num2)
        {
            printf("O inverso %d mod(%d) é %d\n", num1, num2, st[0]);    
        }
        else
        {
            printf("O inverso %d mod(%d) é %d\n", num1, num2, st[1]);
        }
    }
    else
    {
        printf("A expressão %d mod(%d) não possuí inverso\n", num1, num2);
    }

    return 0;
}