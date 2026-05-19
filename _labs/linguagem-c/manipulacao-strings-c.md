---
title: "Laboratório Prático: Manipulação básica de strings em C"
collection: labs
type: "Lab"
permalink: /labs/linguagem-c/manipulacao-strings-c
date: 2026-05-19
location: "Ribeirão Preto, Brazil"
---

## Parte 1: Tutorial Prático Passo a Passo

Vamos criar um programa simples para cadastrar o nome de um paciente e realizar algumas análises básicas sobre esse nome.

O programa deverá:

* Ler o nome completo do paciente;
* Exibir o nome digitado;
* Contar quantos caracteres o nome possui;
* Mostrar a primeira letra do nome;
* Percorrer e exibir cada caractere em uma linha.



### Passo 1: Criando a estrutura básica do programa

```c
##include <stdio.h>

int main() {

    return 0;
}
```

Todo programa em C começa pela função `main`.



### Passo 2: Declarando uma string

Em C, uma string é um vetor de caracteres.

```c
char nome[50];
```

Isso significa que a variável `nome` pode armazenar até 49 caracteres, pois uma posição é reservada para o caractere final `\0`.

Programa até aqui:

```c
##include <stdio.h>

int main() {

    char nome[50];

    return 0;
}
```



### Passo 3: Lendo uma string com `fgets`

Para ler textos com espaços, usamos `fgets`.

```c
fgets(nome, 50, stdin);
```

Código:

```c
##include <stdio.h>

int main() {

    char nome[50];

    printf("Digite o nome do paciente: ");
    fgets(nome, 50, stdin);

    return 0;
}
```



### Passo 4: Exibindo a string

Para imprimir uma string, usamos `%s`.

```c
printf("Paciente: %s", nome);
```

Código:

```c
##include <stdio.h>

int main() {

    char nome[50];

    printf("Digite o nome do paciente: ");
    fgets(nome, 50, stdin);

    printf("Paciente: %s", nome);

    return 0;
}
```



### Passo 5: Usando a biblioteca `string.h`

Para usar funções de strings, precisamos incluir:

```c
##include <string.h>
```

A função `strlen` retorna a quantidade de caracteres da string.

```c
int tamanho = strlen(nome);
```

Código:

```c
##include <stdio.h>
##include <string.h>

int main() {

    char nome[50];
    int tamanho;

    printf("Digite o nome do paciente: ");
    fgets(nome, 50, stdin);

    tamanho = strlen(nome);

    printf("Paciente: %s", nome);
    printf("Quantidade de caracteres: %d\n", tamanho);

    return 0;
}
```



### Passo 6: Cuidado com o `\n` do `fgets`

Quando usamos `fgets`, a tecla Enter também pode ser armazenada como `\n`.

Por isso, o tamanho pode parecer maior do que o esperado.

Podemos remover esse `\n` assim:

```c
nome[strcspn(nome, "\n")] = '\0';
```

Código ajustado:

```c
##include <stdio.h>
##include <string.h>

int main() {

    char nome[50];
    int tamanho;

    printf("Digite o nome do paciente: ");
    fgets(nome, 50, stdin);

    nome[strcspn(nome, "\n")] = '\0';

    tamanho = strlen(nome);

    printf("Paciente: %s\n", nome);
    printf("Quantidade de caracteres: %d\n", tamanho);

    return 0;
}
```



### Passo 7: Mostrando a primeira letra

Como uma string é um vetor, podemos acessar posições específicas.

```c
printf("Primeira letra: %c\n", nome[0]);
```

Código:

```c
##include <stdio.h>
##include <string.h>

int main() {

    char nome[50];
    int tamanho;

    printf("Digite o nome do paciente: ");
    fgets(nome, 50, stdin);

    nome[strcspn(nome, "\n")] = '\0';

    tamanho = strlen(nome);

    printf("Paciente: %s\n", nome);
    printf("Quantidade de caracteres: %d\n", tamanho);
    printf("Primeira letra: %c\n", nome[0]);

    return 0;
}
```



### Passo 8: Percorrendo a string

Podemos usar um `for` para visitar cada caractere.

```c
for(int i = 0; nome[i] != '\0'; i++) {
    printf("%c\n", nome[i]);
}
```

Código final do tutorial:

```c
##include <stdio.h>
##include <string.h>

int main() {

    char nome[50];
    int tamanho;

    printf("Digite o nome do paciente: ");
    fgets(nome, 50, stdin);

    nome[strcspn(nome, "\n")] = '\0';

    tamanho = strlen(nome);

    printf("\n Dados do paciente \n");
    printf("Paciente: %s\n", nome);
    printf("Quantidade de caracteres: %d\n", tamanho);
    printf("Primeira letra: %c\n", nome[0]);

    printf("\nCaracteres do nome:\n");

    for(int i = 0; nome[i] != '\0'; i++) {
        printf("%c\n", nome[i]);
    }

    return 0;
}
```



## Parte 2: Exercícios Práticos

### Exercício 1: Nome do equipamento

Crie um programa que leia o nome de um equipamento e exiba:

* o nome digitado;
* a quantidade de caracteres;
* a primeira letra;
* a última letra.

Exemplo de equipamentos:

* Tomógrafo
* Ressonância
* Mamógrafo
* Ultrassom

##### Dicas

* Use `char equipamento[50];`
* Use `fgets` para ler o texto.
* Remova o `\n` com `strcspn`.
* Use `strlen` para descobrir o tamanho.
* A última letra está na posição `tamanho - 1`.



### Exercício 2: Comparação de códigos de pacientes

Em um sistema hospitalar, cada paciente possui um código de identificação.

Crie um programa que leia dois códigos de pacientes e informe se eles são iguais ou diferentes.

##### Dicas

* Use duas strings, por exemplo:

```c
char codigo1[20];
char codigo2[20];
```

* Use `strcmp` para comparar.
* Se `strcmp(codigo1, codigo2) == 0`, os códigos são iguais.



### Exercício 3: Contagem de espaços em um nome completo

Crie um programa que leia o nome completo de um paciente e conte quantos espaços existem no texto.

Exemplo:

```text
Maria Clara Santos
```

Quantidade de espaços:

```text
2
```

##### Dicas

* Percorra a string com `for`.
* Verifique se cada caractere é igual a `' '`.
* Use uma variável contadora.



### Exercício 4: Contagem de vogais em uma descrição de exame

Crie um programa que leia uma breve descrição de exame e conte quantas vogais aparecem no texto.

Exemplo:

```text
Exame de tomografia
```

##### Dicas

* Percorra a string caractere por caractere.
* Compare cada caractere com:

```c
'a', 'e', 'i', 'o', 'u'
```

* Considere também letras maiúsculas:

```c
'A', 'E', 'I', 'O', 'U'
```



### Exercício 5: Montagem de identificação completa

Crie um programa que leia:

* nome do paciente;
* sobrenome do paciente;
* código do exame.

Depois, o programa deve montar uma identificação completa no formato:

```text
Nome Sobrenome - Código do Exame
```

Exemplo:

```text
Ana Silva - RX102
```

##### Dicas

* Use três strings para leitura.
* Use uma quarta string para guardar o resultado final.
* Use `strcpy` para copiar o primeiro texto.
* Use `strcat` para concatenar os demais textos.
* Lembre-se de reservar espaço suficiente para a string final.

Exemplo:

```c
char identificacao[100];
```
