---
title: "Programação Orientada a Objetos: Exercícios Preparação Prova P1"
collection: labs
type: "Lab"
permalink: /labs/poo-exercicios-preparacao-p1
date: 2026-09-26
location: "Ribeirão Preto, Brazil"
---

## Questão 1

Considere:

```java
public class Conta {
    private double saldo;
    private static int quantidade = 0;

    public Conta(double saldo) {
        this.saldo = saldo;
        quantidade++;
    }

    public void creditar(double valor) {
        if (valor > 0) {
            saldo += valor;
        }
    }

    public double getSaldo() {
        return saldo;
    }

    public static int getQuantidade() {
        return quantidade;
    }
}
```

E:

```java
Conta a = new Conta(100);
Conta b = new Conta(200);
Conta c = a;

c.creditar(50);

System.out.println(a.getSaldo());
System.out.println(b.getSaldo());
System.out.println(Conta.getQuantidade());
```

Assinale a alternativa que apresenta corretamente a saída:

A.

```text
100
200
3
```

B.

```text
150
200
3
```

C.

```text
150
250
2
```

D.

```text
150
200
2
```

E. O código não compila porque `c` e `a` não podem referenciar o mesmo objeto.

---

## Questão 2

Considere um sistema bancário no qual:

- `Cliente` recebe uma referência para uma `ContaBancaria` já criada;
- cada `ContaBancaria` cria seu próprio `HistoricoTransacoes` em seu construtor;
- `saldo` e `historico` são privados;
- a conta oferece métodos como `creditar()`, `debitar()` e `exibirExtrato()`.

Analise:

I. `Cliente` e `ContaBancaria` representam uma associação no modelo descrito.  
II. `ContaBancaria` e `HistoricoTransacoes` representam uma composição no modelo descrito.  
III. O encapsulamento é preservado quando o código externo altera diretamente `saldo`.  
IV. `exibirExtrato()` pode delegar ao histórico a responsabilidade de exibir suas transações sem expor diretamente o array interno.

Assinale a alternativa correta:

A. Apenas I e II.  
B. Apenas I, II e IV.  
C. Apenas II e III.  
D. Apenas I, III e IV.  
E. I, II, III e IV.

## Questão 3

Considere:

```java
int[][] matriz = {
    {2, 4, 6},
    {1, 3, 5}
};

int soma = 0;

for (int i = 0; i < matriz.length; i++) {
    for (int j = 0; j < matriz[i].length; j++) {
        if (matriz[i][j] % 2 == 0) {
            soma += matriz[i][j];
        }
    }
}

System.out.println(soma);
```

Assinale a alternativa correta.

A. O programa imprime `6`, pois apenas a primeira e a última posição da primeira linha são somadas.  
B. O programa imprime `12`, pois soma os valores pares `2`, `4` e `6`.  
C. O programa imprime `21`, pois percorre toda a matriz.  
D. O programa lança `ArrayIndexOutOfBoundsException`, pois `matriz[i].length` não pode ser usado em matrizes.  
E. O programa não compila porque `%` não pode ser aplicado a valores `int`.


## Questão 4

Explique a diferença entre **classe**, **objeto** e **variável de referência** em Java.

Depois, considere:

```java
ContaBancaria conta1 = new ContaBancaria("001", 500);
ContaBancaria conta2 = new ContaBancaria("001", 500);
ContaBancaria conta3 = conta1;
```

Responda:

1. `conta1` e `conta2` representam o mesmo objeto? Justifique.
2. `conta1` e `conta3` representam o mesmo objeto? Justifique.
3. Explique o significado de `this.saldo` dentro de um método ou construtor.

## Questão 5

Considere uma conta bancária com o atributo:

```java
private double saldo;
```

Compare as duas possibilidades:

```java
public void setSaldo(double saldo) {
    this.saldo = saldo;
}
```

E:

```java
public void creditar(double valor) {
    if (valor > 0) {
        saldo += valor;
    }
}

public void debitar(double valor) {
    if (valor > 0 && valor <= saldo) {
        saldo -= valor;
    }
}
```

Explique por que a segunda abordagem é mais adequada para proteger o estado do objeto. Em sua resposta, relacione **encapsulamento**, **responsabilidade do objeto** e **regras de negócio**.


## Questão 6

Analise as afirmações:

I. O compilador `javac` transforma o código-fonte Java em bytecode.  
II. O arquivo `.class` contém código intermediário que pode ser executado por uma JVM compatível com a plataforma.  
III. Para executar o mesmo programa em Windows e Linux, é obrigatório recompilar o código-fonte em uma versão diferente de bytecode para cada sistema operacional.  
IV. A JVM funciona como uma camada entre o bytecode e a plataforma onde o programa será executado.

Assinale a alternativa correta:

A. Apenas I e II.  
B. Apenas I, II e IV.  
C. Apenas II e III.  
D. Apenas I, III e IV.  
E. I, II, III e IV.


## Questão 7

Explique as diferenças entre:

- atributo de instância;
- campo `static`;
- método de instância;
- método `static`;
- constante `static final`.

Use como exemplo uma classe `Poupanca` que possua:

- saldo individual para cada conta;
- quantidade total de contas;
- limite máximo de operação igual a R$ 500,00.

Indique onde cada informação deve ser armazenada e justifique.

## Questão 8

Explique para que servem os pacotes em Java.

Considere a seguinte organização:

```text
src/
├── banco/
│   ├── ContaBancaria.java
│   └── Banco.java
└── cliente/
    └── Cliente.java
```

Em sua resposta, explique:

1. como os pacotes ajudam na organização das classes;
2. como ajudam a evitar conflitos de nomes;
3. por que uma classe de um pacote pode precisar importar uma classe de outro pacote.


## Questão 9

Considere:

```java
double[] notas = {
    7.5, 8.0, 5.5, 9.0, 6.0,
    8.5, 4.5, 7.0, 10.0, 6.5
};
```

Implemente um método Java:

```java
public static void analisarNotas(double[] notas)
```

O método deve:

1. calcular e exibir a média;
2. encontrar a maior e a menor nota;
3. contar quantos alunos possuem nota maior ou igual a `6.0`;
4. contar quantos possuem nota menor que `6.0`;
5. ordenar o array utilizando `Arrays.sort()`;
6. exibir o array ordenado utilizando `Arrays.toString()`.

Não calcule os resultados manualmente.

## Questão 10

Considere:

```java
public class Pokemon {
    private String nome;
    private String tipo;
    private int hp;
    private int atk;

    // construtor e getters
}
```

Implemente um programa que:

1. crie um array `Pokemon[]` com exatamente 6 posições;
2. leia, utilizando `Scanner`, nome, tipo, HP e ATK de cada Pokémon;
3. instancie os 6 objetos e armazene suas referências no array;
4. exiba o nome e o tipo de todos os Pokémon;
5. encontre e exiba o Pokémon com maior ATK;
6. calcule a média de ATK do time;
7. solicite ao usuário um tipo e exiba todos os Pokémon desse tipo.

Os atributos privados devem ser acessados por getters.


## Questão 11

Uma loja deseja modelar pedidos de clientes.

Considere:

- um `Cliente` possui nome e e-mail;
- um `Pedido` possui número e deve estar relacionado a um cliente;
- um pedido possui vários itens;
- cada `ItemPedido` possui nome do produto, quantidade e preço unitário;
- o cliente existe independentemente de um pedido;
- cada item pertence ao pedido no qual foi criado.

Proponha uma modelagem orientada a objetos simples.

Sua resposta deve:

1. identificar as classes;
2. indicar os principais atributos;
3. indicar quais referências entre objetos são necessárias;
4. classificar e justificar os relacionamentos como associação ou composição;
5. indicar métodos públicos importantes para preservar o encapsulamento.

## Questão 12

Crie um programa em Java que recebe por linha de comando uma sequência de números inteiros, armazena a sequência em um array de interios chamado `valores` e determina o tamanho da maior sequência de valores **estritamente positivos e consecutivos**. Implemente o método `public static int maiorSequenciaPositiva(int[] valores)` para retornar o resultado esperado.

### Exemplo 1

```text
Entrada: [2, 5, -1, 4, 8, 3, -2, 7]
Saída: 3
Explicação:

A maior sequência positiva é: [4, 8, 3]
```

### Exemplo 2

```text 
Entrada:
[-3, -1, 0, -8]

Saída: 0
```

> Assuma que o tamanho máximo do array será de 100.
