#include <stdio.h>
#include <math.h>

//funcao que testa se os números são coprimos
int copri(int num1, int num2)
{
    int resto;

    if(num1 > num2)
    {
        resto = num1 % num2;

        if(resto == 0)
        {
            return num2;
        }
        else
        {
            copri(num2, resto);
        }
    }
    else
    {
        resto = num2 % num1;

        if(resto == 0)
        {
            return num1;
        }
        else
        {
            copri(num1, resto);
        }
    }
}

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

//funcao que checa o resto para ele ficar sempre positivo
int checagem(int st[], int tamanho, int num2, int num3, int multi, int resultado)
{
    if(resultado > 0)
    {
        return resultado;
    }
    else
    {
       resultado = (st[tamanho] * num3) + (num2 * multi);
       checagem( st, tamanho, num2, num3, (multi + 1), resultado);
    }
}

//funcao que resolve a congruência linear
int resolver_congruencia_linear(int num1, int num2, int num3)
{
    int MDC, contador, resultado; 
    int i, k, multi = 1;
    int divisor[15], cont[1] = {0}, st[2];
    int divisor2[15], cont2[1] = {0}, MDC2;


    MDC = euclides(num1, num2, divisor, 0, cont); // calculando o MDC e atribuindo os divisores à um vetor para nos ajudar no euclides reverso
    contador = cont[0];
    st[0] = MDC;
    comblinear(divisor, st, MDC, contador, 0, 0, num1, num2, contador); // realizando euclides reverso

    if(MDC == 1 && (num2 > 1 || num1 > 1))
    {
        if(num1 > num2)
        {
            if(st[0] < 0)
            {
                resultado = checagem(st, 0, num2, num3, 1, -1);
                return resultado;
            }
            else
            {
                resultado = (st[0] * num3) % num2;
                return resultado;
            }
        }
        else
        {
            if(st[1] < 0)
            {
                resultado = checagem(st, 1, num2, num3, 1, -1);
                return resultado;
            }
            else
            {
                resultado = (st[1] * num3) % num2;
                return resultado;
            }
        }
    }
}


int main()
{
    int num1, num2, num3;
    int num4, num5, num6;
    int num7, num8, num9;
    int coprimos, coprimos2, coprimos3, M, M1, M2, M3, s1, s2, s3, resultado, r1, r2, r3;

    printf("Digite os valores de a, b e m da congruência 1\nEX: ax ≡ b mod(m)\n");
    scanf("%d%d%d", &num1, &num3, &num2);
    printf("Digite os valores de a, b e m da congruência 2\nEX: ax ≡ b mod(m)\n");
    scanf("%d%d%d", &num4, &num6, &num5);
    printf("Digite os valores de a, b e m da congruência 3\nEX: ax ≡ b mod(m)\n");
    scanf("%d%d%d", &num7, &num9, &num8);

    printf("\n%dx ≡ %d mod(%d)\n", num1, num3, num2);
    printf("%dx ≡ %d mod(%d)\n", num4, num6, num5);
    printf("%dx ≡ %d mod(%d)\n", num7, num9, num8);

    coprimos = copri(num2, num5);
    coprimos2 = copri(num5, num8);
    coprimos3 = copri(num2, num8);

    if(coprimos == 1 && coprimos2 == 1 && coprimos3)
    {
        printf("\nComo os %d, %d e %d são coprimos, logo, podemos aplicar o teorema do resto chinês\n", num2, num5, num8);
        M = num2 * num5 * num8;
        printf("M = %d * %d * %d = %d\n", num2, num5, num8, M);
        M1 = M / num2;
        printf("M1 = %d / %d = %d\n", M, num2, M1);
        M2 = M / num5;
        printf("M2 = %d / %d = %d\n", M, num5, M2);
        M3 = M / num8;
        printf("M3 = %d / %d = %d\n", M, num8, M3);

        num1 = M1;
        r1 = num3;
        num3 = 1;

        num4 = M2;
        r2 = num6;
        num6 = 1;

        num7 = M3;
        r3 = num9;
        num9 = 1;

        s1 = resolver_congruencia_linear(num1, num2, num3);
        s2 = resolver_congruencia_linear(num4, num5, num6);
        s3 = resolver_congruencia_linear(num7, num8, num9);

        printf("\nr1: %d\n", r1);
        printf("r2: %d\n", r2);
        printf("r3: %d\n", r3);

        printf("\n%dx ≡ %d mod(%d)\n", num1, num3, num2);
        printf("%dx ≡ %d mod(%d)\n", num4, num6, num5);
        printf("%dx ≡ %d mod(%d)\n", num7, num9, num8);

        printf("\ns1: %d\n", s1);
        printf("s2: %d\n", s2);
        printf("s3: %d\n", s3);

        resultado = ((M1 * r1 * s1) + (M2 * r2 * s2) + (M3 * r3 * s3)) % M;
        printf("\nSolução = (%d * %d * %d) + (%d * %d * %d) + (%d * %d * %d) mod(%d) = %d\n", M1, r1, s1, M2, r2, s2, M3, r3, s3, M, resultado);
        printf("\nA solução única para 0 <= x < %d é %d\n", M, resultado);
    }
    else
    {
        printf("Não possuí solução\n");
    }
}