---
title: "Tutorial: Interação com o Usuário em Linguagem C"
collection: labs
type: "Lab"
permalink: /labs/interacao-usuario-C
date: 2026-05-05
location: "Ribeirão Preto, Brazil"
---

## A Biblioteca de Entrada/Saída (`stdio.h`)

Para que nosso programa possa "conversar" com o mundo exterior (o console), ele precisa acessar um conjunto de ferramentas pré-definidas pela linguagem C. Essas ferramentas são agrupadas na biblioteca **Standard Input/Output** (`stdio`).

*   **O que é `stdio.h`?** É um arquivo de cabeçalho (`header file`) que contém as declarações das funções necessárias para operações básicas de I/O, como imprimir e ler dados.
*  Qualquer código que use `printf()` ou `scanf()` **DEVE** começar com: `#include <stdio.h>`.

A função `printf()` (Print Formatted) é nossa ferramenta de saída. Ela permite que imprimamos texto e variáveis formatadas no console, garantindo clareza e organização na apresentação dos dados. `printf` usa **Especificadores de Formato** (Format Specifiers) como "tradutores" que dizem ao compilador *qual tipo* de dado está vindo e *como* ele deve ser exibido.

| Tipo de Dado | Especificador | Exemplo de Uso |
| :---: | :---: | :---: |
| Inteiro (`int`) | `%d` ou `%i` | `printf("Idade: %d anos\n", idade);` |
| Ponto Flutuante (`float`) | `%f` | `printf("Altura: %.2f m\n", altura);` |
| Ponto Flutuante Duplo (`double`) | `%lf` (em teoria) ou `%f` | `printf("Preço: %f\n", preco);` |
| Caractere Único (`char`) | `%c` | `printf("Inicial: %c\n", inicial);` |
| String (Array de char) | `%s` | `printf("Nome: %s\n", nome);` |

> O uso de `%.2f` não só especifica o tipo (`%f`), mas também limita a precisão para duas casas decimais, tornando a saída mais limpa e profissional.

**Exemplo Prático de `printf()`**

```c
#include <stdio.h>

int main() {
    // Declaração das variáveis
    char nome[] = "Alice";
    int idade = 25;
    float media = 8.75f;

    // Uso do printf para exibir dados formatados
    printf("==============================\n");
    printf("Relatório de Dados Pessoais:\n");
    
    // Imprimindo String e Inteiro juntos
    printf("Nome: %s\n", nome); 
    
    // Imprimindo um valor com formatação específica (2 casas decimais)
    printf("Idade: %d anos.\n", idade);
    printf("Média Semestral: %.2f\n", media);

    return 0;
}
```

Já a função `scanf()` (Scan Formatted) é nossa ferramenta de entrada. Ela lê dados do fluxo padrão de entrada (o teclado) e os armazena nas variáveis que definirmos. `scanf()` não espera apenas o *valor* da variável. Ela precisa saber **onde na memória** deve armazenar esse valor. É aqui que entra o operador de endereço-de, representado pelo símbolo `&`.

*   **Sem `&`:** Você passa o *valor* do tipo (ex: 0 para um inteiro), e nada acontece com a variável real.
*   **Com `&`:** Você passa o *endereço de memória* da variável (`&variavel`), permitindo que `scanf()` escreva o dado lido naquele local específico.

> Para mais detalhes, leia: https://homepages.dcc.ufmg.br/~rodolfo/aedsi-2-10/printf_scanf/printfscanf.html

Assim como em `printf()`, usamos especificadores de formato em `scanf()`. **A regra é absoluta:** o especificador deve corresponder exatamente ao tipo de variável que está recebendo o valor.

| Tipo de Dado | Especificador | Variável (Exemplo) | Uso Correto |
| :---: | :---: | :---: | :---: |
| Inteiro (`int`) | `%d` | `idade` | `scanf("%d", &idade);` |
| Ponto Flutuante (`float`) | `%f` | `altura` | `scanf("%f", &altura);` |
| String (Array de char) | `%s` | `nome` | `scanf("%s", nome);` **(ATENÇÃO: Não usa `&`)** |


Quando lemos uma string (um array de caracteres), o nome do array *já é* um ponteiro para seu primeiro elemento. Portanto, você **NÃO** deve usar o operador `&` antes do nome do array ao usar `%s`.

**Exemplo Prático de `scanf()`**

```c
#include <stdio.h>
// ... (restante do código)

int main() {
    char nome[50]; // Array para armazenar o nome
    int idade;      // Variável inteira
    float media;    // Variável float
    
    printf("Por favor, digite seu nome: ");
    // 1. String (%s) - NÃO usa &
    scanf("%s", nome); 

    printf("Digite sua idade (ex: 30): ");
    // 2. Inteiro (%d) - USA &
    scanf("%d", &idade); 

    printf("Digite sua média (ex: 7.5): ");
    // 3. Float (%f) - USA &
    scanf("%f", &media); 

    // Confirmação da leitura e exibição dos dados recebidos
    printf("\n==============================\n");
    printf("Dados Recebidos:\n");
    printf("Nome: %s\n", nome);
    printf("Idade: %d anos.\n", idade);
    printf("Média: %.2f\n", media);

    return 0;
}
```

## Boas Práticas

### 1. Prevenção de Buffer Overflow em `scanf()`
**Problema:** Se você usa `%s` e o usuário digitar um nome muito longo (excedendo o tamanho do array), o `scanf()` continuará escrevendo dados na memória além dos limites alocados para `nome`, corrompendo outras variáveis. Isso é um *Buffer Overflow* e causa falhas de segurança graves.

**Solução:** Sempre limite a leitura com um número máximo de caracteres no especificador:

```c
// Limita o nome lido a, no máximo, 49 caracteres (deixando espaço para o '\0')
scanf("%49s", nome); 
```

> Mais informações em https://www.youtube.com/watch?v=JzI6T9-nPK0

### 2. Tratamento de Erros em `scanf()`
`scanf()` retorna um valor inteiro que indica **quantos itens foram lidos com sucesso**. É uma boa prática verificar esse retorno:

```c
int resultado = scanf("%d", &idade);

if (resultado != 1) {
    printf("ERRO: Por favor, insira apenas números inteiros.\n");
    // Aqui você deve implementar um loop para pedir o dado novamente.
}
```

### 3. Separando Entrada de Texto com Espaços
Lembre-se que `%s` lê até encontrar o primeiro espaço em branco. Se você quiser ler uma frase completa (com espaços), não use `scanf()`. Use funções mais avançadas como `fgets()` (que é um tópico futuro, mas essencial para a robustez).


## Exercícios Teóricos

1. Qual é a diferença fundamental no uso do operador `&` entre `printf()` e `scanf()`?
    *   *(Dica: Pense no que cada função precisa saber sobre o dado.)*
2. Por que usar apenas `%s` em um array de caracteres pode causar um *Buffer Overflow*, e qual é a forma correta de mitigar esse risco usando `scanf()`?
    
## Exercício Prático 

**Objetivo:** Criar um programa que simule o cadastro de um produto em uma loja virtual.

1.  O programa deve solicitar, via usuário, os seguintes dados:
    *   Nome do Produto (String).
    *   Preço Unitário (Float).
    *   Quantidade em Estoque (Integer).
2.  Após a leitura dos três valores, o programa deve calcular e exibir:
    *   O Valor Total do Estoque (`Preço * Quantidade`).
3.  **Requisito de Código:** Utilize `printf()` para estruturar a saída de forma clara e utilize `scanf()` com os operadores corretos (incluindo formatação de segurança).
