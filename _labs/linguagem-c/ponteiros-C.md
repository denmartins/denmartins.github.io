---
title: "Ponteiros em C"
collection: labs
type: "Lab"
permalink: /labs/linguagem-c/ponteiros-c
date: 2026-06-11
location: "Ribeirão Preto, Brazil"
---

## Exercício 1: Troca de Valores (Swap)
Implemente uma função chamada `swap_valores` que recebe dois ponteiros para inteiros (`int *a`, `int *b`). Esta função deve trocar os valores apontados por esses ponteiros, sem usar variáveis auxiliares além das necessárias para a troca em si.

**Dica:**
*   **Ponto de Atenção:** Lembre-se que você não está trocando o endereço armazenado nos ponteiros `a` e `b`. Você deve trocar os **valores** que estão localizados na memória, nos endereços apontados por eles (`*a` e `*b`).
*   **Raciocínio:** Pense em como faríamos a troca de variáveis normais. Agora, substitua cada variável pelo seu endereço de memória (usando o operador `&`) e depois acesse o conteúdo desse endereço (usando o operador `*`).

## Exercício 2: Cálculo de Mínimo/Máximo
Crie uma função `encontrar_extremos` que recebe dois ponteiros para inteiros (`int *a`, `int *b`). A função deve comparar os valores apontados por eles e, em seguida, usar um terceiro ponteiro (passado como argumento) para armazenar o endereço do valor mínimo encontrado.

**Dica:**
*   **Lógica de Comparação:** Comece assumindo que o primeiro valor é o mínimo. Em seguida, compare-o com o segundo valor. Se o segundo for menor, você deve atualizar o ponteiro de destino para apontar para a localização do segundo valor.
*   **Retorno:** O objetivo não é apenas retornar o número, mas sim o **endereço** onde esse número foi encontrado na memória (use `&` novamente!).


## Exercício 3: Soma de Elementos em um Array
Implemente uma função `somar_array` que recebe dois argumentos:
1.  Um ponteiro para o primeiro elemento de um array inteiro (`int *arr`).
2.  O tamanho total do array (`int tamanho`).

A função deve calcular e retornar a soma de todos os elementos do array, utilizando apenas aritmética de ponteiros (evite usar `arr[i]`, use `*(arr + i)` ou manipulação direta do ponteiro).

**Dica:**
*   **O Segredo da Aritmética:** Quando você usa `(ponteiro + N)`, o compilador não apenas soma números. Ele calcula: `endereço_inicial + (N * sizeof(tipo))`. Isso garante que, ao avançar de ponteiros em um array de inteiros, você sempre pule exatamente 4 bytes (ou o tamanho do seu `int`).
*   **Estrutura:** Use um laço `for` ou `while`, mas dentro dele, a progressão deve ser feita com `p++` (onde `p` é seu ponteiro auxiliar).

## Exercício 4: Inversão em Local (In-Place Reversal)
Crie uma função `inverter_array` que recebe um ponteiro para o início de um array (`int *arr`) e seu tamanho (`int tamanho`). A função deve reverter a ordem dos elementos do array diretamente na memória (sem criar um novo array).

**Dica:**
*   **Estratégia de Ponteiros Duplos:** Pense em dois ponteiros: um que aponta para o **início** (`p_inicio`) e outro que aponta para o **fim** (`p_fim`).
*   **Processo:** Enquanto `p_inicio` não passar de `p_fim`, você deve trocar os valores apontados por eles. Após a troca, avance `p_inicio` (para frente) e retroceda `p_fim` (para trás).


## Exercício 5: Contagem de Elementos Pares/Ímpares
Crie uma função `contar_pares` que recebe um ponteiro para o início de um array e seu tamanho. A função deve percorrer todo o array, contando quantos elementos são pares e retornando essa contagem.

**Dica:**
*   **Simplicidade Controlada:** Este exercício é ótimo para reforçar a estrutura `while` com controle manual de ponteiro. Comece um ponteiro auxiliar no início (`int *p = arr;`) e use o laço `while (p < end_do_array)` ou simplesmente `while (i < tamanho)`.