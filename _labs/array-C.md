---
title: "Exercícios Práticos: Arrays e Matrizes em C"
collection: labs
type: "Lab"
permalink: /labs/arrays-matrizes-C
date: 2026-05-19
location: "Ribeirão Preto, Brazil"
---

## Parte 1: Revisão Conceitual

Um *Array* é uma estrutura de dados que permite armazenar um conjunto fixo de elementos do **mesmo tipo** em posições de memória **contíguas**.

-  **Homogeneidade:** Todos os elementos devem ter o mesmo `tipo` (ex: todos `int`, todas `float`).
-  **Contiguidade:** Os elementos são armazenados um após o outro na memória RAM, sem lacunas. Esta característica é vital para a eficiência do acesso e manipulação por ponteiros.
-  **Indexação Zero-Base:** O primeiro elemento sempre recebe o índice `0`, e o último elemento recebe o índice N-1 (onde N é o tamanho total).

**Sintaxe de Declaração:**
```c
tipo nome_do_array[tamanho];
// Exemplo: Um array de 10 inteiros.
int notas[10];
```

Por outro lado, uma Matriz é, conceitualmente, um *Array* de *Arrays*. Ela representa uma grade retangular de valores e é utilizada para modelar dados bidimensionais (linhas e colunas).

-  **Dimensões:** São definidas por duas dimensões: `[LINHAS][COLUNAS]`.
-  **Memória Contígua:** Apesar de parecerem "duas dimensões", em termos de memória física, a matriz é tratada pelo compilador como um único bloco linear e contíguo. O acesso aos elementos (ex: `M[i][j]`) é resolvido através de cálculos de deslocamento de ponteiro.
-  **Acesso:** O primeiro índice (`i`) geralmente representa a linha, e o segundo (`j`) representa a coluna.

**Sintaxe de Declaração:**
```c
tipo nome_da_matriz[num_linhas][num_colunas];
// Exemplo: Uma matriz 3x4 (3 linhas, 4 colunas).
float grade[3][4];
```

> **Observação**: Entender profundamente *Arrays* significa dominar o conceito de endereçamento linear na memória. Cada índice é um cálculo preciso de deslocamento a partir do endereço base. Este entendimento é o que diferencia C de linguagens de mais alto nível. Para mais informações veja: https://wiki.inf.ufpr.br/maziero/doku.php?id=c:vetores


## Parte 2: Arrays Unidimensionais

### Exercício 1: Registro de doses de radiação

Durante uma rotina de controle de qualidade, um físico médico registrou a dose de radiação medida em 5 pontos de uma sala.

Escreva um programa em C que:

* Leia 5 valores de dose;
* Armazene os valores em um vetor;
* Exiba todas as doses registradas.



### Exercício 2: Dose total acumulada

Em um procedimento simulado, foram registradas 6 doses parciais recebidas por um detector.

Escreva um programa em C que:

* Leia 6 valores de dose;
* Armazene os valores em um vetor;
* Calcule a dose total acumulada;
* Exiba o resultado.



### Exercício 3: Média de radiação de fundo

Um laboratório realizou 8 medições de radiação de fundo em uma sala.

Escreva um programa em C que:

* Leia 8 medições;
* Armazene os valores em um vetor;
* Calcule a média das medições;
* Exiba a média final.



### Exercício 4: Leituras acima do limite

Um equipamento registrou 10 leituras de dose. O limite recomendado é de `2.0 mSv`.

Escreva um programa em C que:

* Leia 10 valores de dose;
* Armazene os valores em um vetor;
* Conte quantas leituras estão acima de `2.0`;
* Exiba essa quantidade.



### Exercício 5: Maior e menor dose registrada

Durante um teste de blindagem, foram coletadas 10 leituras de dose.

Escreva um programa em C que:

* Leia 10 valores de dose;
* Armazene-os em um vetor;
* Determine a maior dose registrada;
* Determine a menor dose registrada;
* Exiba os dois valores.



## Parte 3: Matrizes Bidimensionais

### Exercício 6: Mapa de radiação de uma sala

Uma sala foi dividida em uma grade de 3 linhas por 3 colunas. Em cada ponto da grade, foi medida uma dose de radiação.

Escreva um programa em C que:

* Leia os valores de uma matriz `3x3`;
* Armazene as doses medidas;
* Exiba a matriz formatada na tela.



### Exercício 7: Soma total de doses em uma grade

Considerando uma grade de medição `3x3`, escreva um programa em C que:

* Leia 9 valores de dose;
* Armazene-os em uma matriz `3x3`;
* Calcule a soma total das doses;
* Exiba o resultado.



### Exercício 8: Maior dose em uma imagem médica

Uma pequena imagem médica em tons de cinza pode ser representada por uma matriz `4x4`, em que cada valor representa a intensidade de um pixel.

Escreva um programa em C que:

* Leia os valores de uma matriz `4x4`;
* Determine o maior valor de intensidade;
* Exiba esse valor.



### Exercício 9: Contagem de pixels escuros

Em uma imagem médica representada por uma matriz `4x4`, valores menores que `50` indicam pixels escuros.

Escreva um programa em C que:

* Leia os valores inteiros de uma matriz `4x4`;
* Conte quantos pixels possuem intensidade menor que `50`;
* Exiba a quantidade encontrada.



### Exercício 10: Média de dose por linha

Uma sala foi dividida em uma matriz `3x4`, representando 3 regiões com 4 pontos de medição em cada região.

Escreva um programa em C que:

* Leia os valores de dose de uma matriz `3x4`;
* Calcule a média de dose de cada linha;
* Exiba a média de cada região.

