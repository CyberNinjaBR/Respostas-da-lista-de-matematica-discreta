#include <stdio.h>
#include <math.h>

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


void demais_resultados(int num1, int num2, int num3, int resultado, int mdc, int multi)
{
    int result;
    if(mdc == 0)
    {
        printf("Esse são todos os resultados para %dx ≡ %d mod(%d), que também são os resultados da primeira congruência\n", num1, num3, num2);
        return;
    }
    else
    {
        result = resultado + num2 * multi;
        printf("%d + %d * (%d) = %d\n", resultado, num2, multi, result);
        demais_resultados(num1, num2, num3, resultado, (mdc - 1), (multi + 1));
    }
}

int main()
{
    int num1, num2, num3, MDC, contador, resultado; 
    int i, k, multi = 1;
    int divisor[15], cont[1] = {0}, st[2];
    int divisor2[15], cont2[1] = {0}, MDC2;

    printf("Digite os valores inteiros de a, b e m da congruencia linar que você deseja resolver\nEX: ax ≡ b mod(m)\n");
    scanf("%d%d%d", &num1, &num3, &num2);

    MDC = euclides(num1, num2, divisor, 0, cont); // calculando o MDC e atribuindo os divisores à um vetor para nos ajudar no euclides reverso

    if(MDC == 1 && (num2 > 1 || num1 > 1))
    {
        contador = cont[0];
        st[0] = MDC;
        comblinear(divisor, st, MDC, contador, 0, 0, num1, num2, contador); // realizando euclides reverso

        if(num1 > num2)
        {
            if(st[0] < 0)
            {
                resultado = checagem(st, 0, num2, num3, 1, -1);
                printf("O resultado único para 0 <= x < %d é: %d\n", num2, resultado);
                printf("Seu resultado de forma genérica é %d + %dk, com K inteiro\n", resultado, num2);
            }
            else
            {
                resultado = (st[0] * num3) % num2;
                printf("O resultado único para 0 <= x < %d é: %d\n", num2, resultado);
                printf("Seu resultado de forma genérica é %d + %dk, com K inteiro\n", resultado, num2);
            }
        }
        else
        {
            if(st[1] < 0)
            {
                resultado = checagem(st, 1, num2, num3, 1, -1);
                printf("O resultado único para 0 <= x < %d é: %d\n", num2, resultado);
                printf("Seu resultado de forma genérica é %d + %dk, com K inteiro\n", resultado, num2);
            }
            else
            {
                resultado = (st[1] * num3) % num2;
                printf("O resultado único para 0 <= x < %d é: %d\n", num2, resultado);
                printf("Seu resultado de forma genérica é %d + %dk, com K inteiro\n", resultado, num2);
            }
        }
    }

    else
    {
        if(num3 % MDC == 0)
        {
            printf("Como MDC (%d, %d) = %d e %d divide %d, então, essa congruência possuí %d soluções\n", num1, num2, MDC, MDC, num3, MDC);
            num1 = num1 / MDC;
            num2 = num2 / MDC;
            num3 = num3 / MDC;
            printf("Essas soluções são todas congruentes a %dx ≡ %d mod(%d)\n", num1, num3, num2);
            MDC2 = euclides(num1, num2, divisor2, 0, cont2); // calculando o MDC e atribuindo os divisores à um vetor para nos ajudar no euclides reverso
            contador = cont2[0];
            st[0] = MDC2;
            comblinear(divisor2, st, MDC2, contador, 0, 0, num1, num2, contador); // realizando euclides reverso

            if(MDC2 == 1 && (num2 > 1 || num1 > 1))
            {
                if(num1 > num2)
                {
                    if(st[0] < 0)
                    {
                        resultado = checagem(st, 0, num2, num3, 1, -1);
                        printf("O resultado único para 0 <= x < %d é: %d\n", num2, resultado);
                        printf("%d é um dos %d resultados. Para sabermos os demais, basta pegarmos multiplos de %d\n", resultado, MDC, num2);
                        demais_resultados(num1, num2, num3, resultado, (MDC - 1), 1);
                    }
                    else
                    {
                        resultado = (st[0] * num3) % num2;
                        printf("O resultado único para 0 <= x < %d é: %d\n", num2, resultado);
                        printf("%d é um dos %d resultados. Para sabermos os demais, basta pegarmos multiplos de %d\n", resultado, MDC, num2);
                        demais_resultados(num1, num2, num3, resultado, (MDC - 1), 1);
                    }
                }
                else if(num1 < num2)
                {
                    if(st[1] < 0)
                    {
                        resultado = checagem(st, 1, num2, num3, 1, -1);
                        printf("O resultado único para 0 <= x < %d é: %d\n", num2, resultado);
                        printf("%d é um dos %d resultados. Para sabermos os demais, basta pegarmos multiplos de %d\n", resultado, MDC, num2);
                        demais_resultados(num1, num2, num3, resultado, (MDC - 1), 1);
                    }
                    else
                    {
                        resultado = (st[1] * num3) % num2;
                        printf("O resultado único para 0 <= x < %d é: %d\n", num2, resultado);
                        printf("%d é um dos %d resultados. Para sabermos os demais, basta pegarmos multiplos de %d\n", resultado, MDC, num2);
                        demais_resultados(num1, num2, num3, resultado, (MDC - 1), 1);
                    }
                }
                else
                {
                    printf("Essa congruência não possuí solução");
                }
            }
        }
        else
        {
            printf("Como MDC (%d, %d) = %d e %d não divide %d, então, essa congruência não possuí solução\n", num1, num2, MDC, MDC, num3);
        }
    }
    return 0;
}