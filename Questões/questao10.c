#include <stdio.h>
#include <math.h>

//funcao auxiliar que juda a testar se os números são coprimos
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

// testa se os valores de m das congruências são coprimos
int testar_coprimos(int num2[], int tamanho, int tamanho2, int cont, int resultado)
{
    int i, coprimos, k = 0, j = 0;
    if(cont == 1)
    {
        if(resultado == 0)
        {
            return 1;    
        }
        else
        {
            return 0;
        }
    }
    else
    {
        for(i = tamanho2; i < cont; i++)
        {
            coprimos = copri(num2[tamanho], num2[i]);
            if(coprimos != 1)
            {
                ++k;
            }
        }

        resultado = resultado + k;
        testar_coprimos(num2, (tamanho + 1), (tamanho2 + 1), (cont - 1), resultado);
    }
}


int main()
{
    int coprimos, M = 1, resultado = 0, tamanho;
    int num1[50], num2[50], num3[50], Ms[30], s[30], r[30], i, k = 1, cont = 0, j = 1;

    //controle de quantas congruências vão ser utilizadas
    printf("Insira a quantidade de congruências que você deseja resolver:\n");
    scanf("%d", &tamanho);

    //guarda os valores da congruência
    for(i = 0; i < tamanho; i++)
    {
        printf("Digite os valores de a, b e m da congruência %d\nEX: ax ≡ b mod(m)\n", k);
        scanf("%d%d%d", &num1[i], &num3[i], &num2[i]);
        ++cont;
        ++k;
    }  
    printf("\n");

    //mostra as congruências inseridas para o usuário
    for(i = 0; i < tamanho; i++)
    {
        printf("%dx ≡ %d mod(%d)\n", num1[i], num3[i], num2[i]);
    }

    //testando se os valores de m das congruências inseridas são coprimos
    coprimos = testar_coprimos(num2, 0, 1, cont, 0);

    if(coprimos == 1)
    {
        //informando ao usário que são coprimos
        printf("\nComo os valores");
        for(i = 0; i < cont; i++)
        {
            if(i + 1 == cont)
            {
                printf(" %d ", num2[i]);
            }
            else
            {
                printf(" %d,", num2[i]);
            }
        }
        printf("são coprimos, logo, podemos aplicar o teorema do resto chinês\n");

        //calculando o valor de M e printando para o usuário
        for(i = 0; i < cont; i++)
        {
            M = M * num2[i];
        }
        printf("M = ");
        for(i = 0; i < cont; i++)
        {
            if(i + 1 == cont)
            {
                printf(" %d ", num2[i]);
            }
            else
            {
                printf(" %d *", num2[i]);
            }
        }
        printf("= %d\n", M);

        //calculo dos valores dos demais M's
        for(i = 0; i < cont; i++)
        {
            Ms[i] = M / num2[i];
            printf("M%d = %d / %d = %d\n", j, M, num2[i], Ms[i]);
            ++j;
        }
        j = 1;

        //construindo as novas congruências
        for(i = 0; i < cont; i++)
        {
            num1[i] = Ms[i];
            r[i] = num3[i];
            num3[i] = 1;    
        }

        //encontrando a solução das novas congruências
        printf("\n");
        for(i = 0; i < cont; i++)
        {
           s[i] = resolver_congruencia_linear(num1[i], num2[i], num3[i]);
        }

        //Mostrando os valores de r para o usuário
        for(i = 0; i < cont; i++)
        {
            printf("r%d: %d\n", j, r[i]);
            ++j;
        }
        j = 1;
        printf("\n");

        //Mostando a nova congruência para o usuário
        for(i = 0; i < cont; i++)
        {
            printf("%dx ≡ %d mod(%d)\n", num1[i], num3[i], num2[i]);
        }
         printf("\n");

        //Mostrando os valores dos M's e s para o usuário
        for(i = 0; i < cont; i++)
        {
            printf("s%d: %d\n", j, s[i]);
            ++j;
        }
        printf("\n");

        //Calcula o resutlado
        for(i = 0; i < cont; i++)
        {
            resultado = resultado + Ms[i] * r[i] * s[i];
        }
        resultado = resultado % M;

        //Mostra o cálculo do resultado para o usuário
        printf("resultado = (");
        for(i = 0; i < cont; i++)
        {
            if(i + 1 == cont)
            {
                printf(" (%d * %d * %d)", Ms[i], r[i], s[i]);
            }
            else
            {
                printf("(%d * %d * %d) + ", Ms[i], r[i], s[i]);
            }
        }
        printf(") %% %d = (%d)\n", M, resultado);

        printf("\nA solução única para 0 <= x < %d é %d\n", M, resultado); 
    }
    else
    {
        printf("Não possuí solução\n");
    }
    return 0;
}
