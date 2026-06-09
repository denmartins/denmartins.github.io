---
title: "Lista de Exercícios de Preparação para Prova"
collection: labs
type: "Lab"
permalink: /labs/linguagem-c/lista-exercicios-c
date: 2026-06-09
location: "Ribeirão Preto, Brazil"
---

## Questão 1

Considere o código C: `int x = 5; int *p = &x;`. Qual é a função do operador `&` neste contexto?

- (A) Ele acessa o valor armazenado em `p`.
- (B) Ele incrementa o valor de `x` em um bloco de memória.
- (C) Ele retorna o endereço de memória da variável `x`, permitindo que `p` armazene essa localização.
- (D) Ele converte o tipo de dado de inteiro para ponteiro, sem alterar o valor.

## Questão 2

Explique detalhadamente o papel do caractere nulo (`\0`) em uma string em C. Por que é crucial que ele esteja presente para que funções como `strlen()` ou `strcpy()` funcionem corretamente?

## Questão 3

Se tivermos um array de inteiros `int arr[5];` e definirmos ponteiros `p1 = &arr[0]` e `p2 = arr + 3`, qual é a relação correta entre `p1` e `p2`?

- (A) Eles apontam para o mesmo endereço, pois são ambos ponteiros de inteiros.
- (B) `p1` aponta para o primeiro elemento, e `p2` aponta para o quarto elemento (índice 3). Ambos são endereços distintos.
- (C) `p2` é sempre igual a `p1 + 3`, independentemente do tamanho do array.
- (D) A relação entre eles depende da alocação dinâmica de memória, não sendo possível determinar sem compilar.

## Questão 4
Qual das seguintes operações é considerada altamente arriscada em C e pode levar a falhas de segmentação ou comportamento indefinido?

- (A) `int *p = malloc(sizeof(int));`
- (B) `*p = 10;` (onde `p` aponta para um endereço válido).
- (C) Acessar o conteúdo de um ponteiro após liberar sua memória (`free(p); *p = 5;`).
- (D) Inicializar um ponteiro com nulo: `int *p = NULL;`.

## Questão 5

Em C, qual é a principal diferença conceitual entre usar uma estrutura `struct` e utilizar um `union`? Dê um exemplo de cenário onde o uso de `union` seria mais eficiente em termos de memória.

## Questão 6

Em um contexto recursivo, qual é a função fundamental que deve ser implementada para evitar um *stack overflow* infinito?

- (A) A passagem correta dos ponteiros por referência (`&`).
- (B) O uso de `const` em todos os parâmetros.
- (C) O caso base (base case), onde a função determina quando parar de chamar a si mesma.
- (D) Garantir que o retorno da função seja sempre um valor inteiro.


## Questão 7

Escreva uma função chamada `calcularMedia` que receba um array de números inteiros (`int arr[]`) e seu tamanho (`int size`). A função deve calcular e retornar a média desses elementos, utilizando ponteiros para acessar os dados do array.

## Questão 8

O código abaixo possui um erro lógico grave relacionado à manipulação de memória. Identifique o erro e reescreva o trecho de código corretamente para que ele imprima o valor original da variável `valor` sem alterá-lo, mesmo após a função ser chamada.

```c
void modificar(int *p) {
    *p = 99; // ERRO: Modifica o valor apontado
}

// Código principal (main):
int valor = 10;
modificar(&valor);
printf("%d", valor); // Espera-se que imprima 10, mas imprime 99.
```

## Questão 9

Escreva um programa em C que receba uma string de entrada e utilize ponteiros para "reverter" o conteúdo dessa string *in place* (sem alocar nova memória). Exemplo: "CASA" deve virar "ASAC".

## Questão 10

O código abaixo tem um erro clássico de limites em arrays. Qual é o valor que será impresso e por quê? Corrija o loop para garantir que ele processe *todos* os elementos do array corretamente, sem acessar memória inválida.

```c
#define TAMANHO 5
int notas[TAMANHO] = {80, 75, 90, 60, 100};
// ... (Código de processamento)
for (int i = 0; i <= TAMANHO; i++) { // ERRO AQUI
    printf("%d ", notas[i]);
}
```

## Questão 11

Defina uma estrutura `Pessoa` contendo nome (string) e idade (int). Crie um array de duas pessoas. Em seguida, escreva um código que use ponteiros para acessar o endereço da *idade* da segunda pessoa e imprima esse valor.

## Questão 12

Escreva uma função recursiva chamada `fibonacci(int n)` que calcule e retorne o $n$-ésimo número de Fibonacci. Demonstre como ela deve ser chamada no `main`.

## Questão 13

Explique a diferença prática entre passar um array (`int arr[10]`) e um ponteiro (`int *p`) para uma função em C, focando na assinatura da função. Por que o compilador aceita ambas as formas?

## Questão 14

Escreva um programa utilizando `switch-case` que simule a conversão de um código de erro numérico (ex: 404, 200, 500) para uma mensagem descritiva em português. Lembre-se do uso obrigatório da cláusula `default`.

## Questão 15

Dada uma matriz $3 \times 3$ de inteiros, escreva um trecho de código que utilize aritmética de ponteiros para somar todos os elementos da primeira linha. Não use loops aninhados baseados em índices `[i][j]`.

## Questão 16

Qual é o valor impresso pelo seguinte bloco de código? Justifique sua resposta com base no escopo das variáveis em C.

```c
void funcao_externa(int x) {
    int y = 5; // Escopo local a função_externa
    printf("%d ", y);
}

int main() {
    int z = 10;
    // printf("%d", z); // Comentado para evitar erro de compilação
    funcao_externa(z);
    return 0;
}
```

## Questão 17

Escreva um programa que aloque dinamicamente na *heap* espaço suficiente para armazenar 5 números inteiros. Em seguida, preencha esses 5 espaços com valores aleatórios e, por fim, utilize `free()` para liberar a memória corretamente.


## Questão 18

Considere o programa:

```c
#include <stdio.h>

void altera(int *p)
{
    *p = *p + 5;
}

int main()
{
    int x = 10;

    altera(&x);

    printf("%d", x);

    return 0;
}
```

Responda:

1. Qual será a saída?
2. Desenhe o estado da memória antes da chamada da função.
3. Desenhe o estado da memória durante a execução da função.
4. Explique por que a variável `x` foi alterada.
5. Qual seria o resultado se a função recebesse `int p` em vez de `int *p`?


## Questão 19

Considere o programa:

```c
#include <stdio.h>

void altera(int x)
{
    x = 100;
}

int main()
{
    int valor = 10;

    altera(valor);

    printf("%d", valor);

    return 0;
}

```

A saída será:

- (A) 100
- (B) 10
- (C) Erro de compilação
- (D) Endereço de memória
- (E) Valor indefinido

## Questão 20

Implemente uma função:

```c
int contarVogais(char texto[])
```

que receba uma string e retorne a quantidade de vogais presentes.

O programa principal deve:

- Ler uma frase;
- Chamar a função;
- Exibir o resultado.
