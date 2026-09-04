---
title: "Programação Orientada a Objetos: Exercícios Práticos 1"
collection: labs
type: "Lab"
permalink: /labs/poo-exercicios-praticos-01
date: 2026-09-04
location: "Ribeirão Preto, Brazil"
---

# Introdução

Resolva as questões a seguir. **Entregue no e-disciplinas um arquivo pdf incluindo**:
- o código-fonte de cada exercício prático e um screenshot do resultado no terminal;
- as respostas dos exercícios teóricos.


# Questão: 01

Dado um inteiro `num`, retorne o *número de passos* necessários para reduzi-lo à zero. Se em um passo o número atual for par, você deve dividi-lo por `2`, caso contrário deve decrementá-lo em `1`.

## Entrada
1. `num`: Um inteiro

## Saída

* O número de passos necessários para reduzir `num` a `0`.

## Restrições
* 0 <= `num` <= $10^6$  

## Exemplos

### Exemplo 1

> Entrada: `num` = `14`
> Saída: 6


**Explicação**:
1) 14 é par, dividimos por 2 e obtemos 7.
2) 7 é impar, subtraímos 1 e obtemos 6.
3) 6 é par, dividimos por 2 e obtemos 3.
4) 3 é impar, subtraímos 1 e obtemos 2.
5) 2 é par, dividimos por 2 e obtemos 1.
6) 1 é impar, subtraímos 1 obtemos 0.

### Exemplo 2

> Entrada: `num` = `8`
> Saída: 4

**Explicação**:
1) 8 é par, dividimos por 2 e obtemos 4.
2) 4 é par, dividimos por 2 e obtemos 2.
3) 2 é par, dividimos por 2 e obtemos 1.
4) 1 é impar, subtraímos 1 obtemos 0.


# Questão: 02

Dado um inteiro `num`, repetidamente some os dígitos que o compõe até que o resultado tenha um único dígito.

## Entrada

`num`: Um inteiro

# Questão: Saída

A soma recursiva dos dígitos de `num`.

## Restrições

0 <= `num` <= $2^{31}-1$ 

## Exemplos

### Exemplo 1

> Entrada: `num` = `38`
> Saída: 2

**Explicação**:
1) 38 -> 3 + 8 = 11
2) 11 -> 1 + 1 = 2

### Exemplo 2

> Entrada: `num` = `0`
> Saída: 0

**Explicação**: Somente tem um dígito, retorne imediatamente.


# Questão: 03

Projete um sistema para um estacionamento. O estacionamento possui três
tipos de vagas: grandes, médias e pequenas, com uma quantidade fixa de
vagas para cada tamanho.

Implemente a classe `ParkingSystem`:

-   `ParkingSystem(int big, int medium, int small)`

    Inicializa um objeto da classe `ParkingSystem`. As quantidades de
    vagas grandes, médias e pequenas são fornecidas ao construtor.

-   `boolean addCar(int carType)`

    Verifica se existe uma vaga disponível para o carro que deseja
    entrar no estacionamento. O parâmetro `carType` representa o tipo do
    carro: grande, médio ou pequeno, identificados respectivamente pelos
    valores `1`, `2` e `3`.

    Um carro somente pode ocupar uma vaga correspondente ao seu tipo.
    Caso não exista uma vaga disponível, o método deve retornar `false`.
    Caso contrário, deve estacionar o carro na vaga correspondente,
    ocupando ela, e retornar `true`.

**Exemplo 1**

**Entrada**

A entrada abaixo possuí duas linhas, a primeira mostra o
construtor/método chamado e a segunda os parâmetros da chamada.

```
["ParkingSystem", "addCar", "addCar", "addCar", "addCar"]
[[1, 1, 0], [1], [2], [3], [1]]
```

**Saída**

Para cada um dos pares (construtor/método, parâmetros) acima, esse foi o
valor retornado, em ordem.

```
[null, true, true, false, false]
```

> **Observação:** os colchetes acima são apenas usados para representar a sequência de criação do objeto e de chamadas
aos métodos. Não é necessário criar ou manipular arrays para resolver este exercício (ou qualquer outro nesse arquivo).

**Explicação**:

```java
ParkingSystem parkingSystem = new ParkingSystem(1, 1, 0);

parkingSystem.addCar(1);
// true: ocupa a única vaga disponível para um carro grande.

parkingSystem.addCar(2);
// true: ocupa a única vaga disponível para um carro médio.

parkingSystem.addCar(3);
// false: não existe vaga disponível para um carro pequeno.

parkingSystem.addCar(1);
// false: a única vaga para carro grande já está ocupada.
```

# Questão: 04

Para um fluxo de inteiros, implemente uma estrutura de dados que
verifique se os últimos `k` inteiros recebidos pelo fluxo são iguais ao
valor `value`.

Implemente a classe `DataStream`:

-   `DataStream(int value, int k)`

    Inicializa um objeto da classe `DataStream` com um fluxo de inteiros
    vazio e armazena os valores `value` e `k`.

-   `boolean consec(int num)`

    Adiciona o inteiro `num` ao fluxo. O método deve retornar `true`
    quando os últimos `k` inteiros recebidos forem iguais a `value`.
    Caso contrário, deve retornar `false`.

    Se o fluxo ainda tiver recebido menos de `k` inteiros, a condição
    não poderá ser satisfeita e o método deverá retornar `false`.

**Exemplo 1**

**Entrada**

A entrada abaixo possui duas linhas: a primeira mostra o construtor ou
método chamado e a segunda mostra os parâmetros de cada chamada.

```
["DataStream", "consec", "consec", "consec", "consec"]
[[4, 3], [4], [4], [4], [3]]
```

**Saída**

Para cada par formado por uma chamada e seus parâmetros, a saída
apresenta o valor retornado, seguindo a mesma ordem.

```
[null, false, false, true, false]
```

> **Observação:** os colchetes acima são apenas usados para representar a sequência de criação do objeto e de chamadas aos métodos. Não é necessário criar ou manipular arrays para resolver este exercício (ou qualquer outro nessa lista).

**Explicação**:

```java
DataStream dataStream = new DataStream(4, 3);
// value = 4, k = 3 e o fluxo começa vazio.

dataStream.consec(4);
// false: apenas 1 inteiro foi recebido.

dataStream.consec(4);
// false: apenas 2 inteiros foram recebidos.
// Essa quantidade ainda é menor que k.

dataStream.consec(4);
// true: os 3 últimos inteiros são iguais a value.

dataStream.consec(3);
// false: os 3 últimos inteiros são [4, 4, 3].
// Nem todos são iguais a value.
```

# Questão: 05

Escreva uma classe `StringUtils.java` com um método chamado `center()` que recebe uma `String` como argumento e exiba o caractere ou os caracteres localizados no centro da `String`.

Considere:

* se o comprimento da `String` for **ímpar**, existe **um caractere central**;
* se o comprimento da `String` for **par**, existem **dois caracteres centrais**.

Exemplos:

```text
"Java"  → "av"
"POO"   → "O"
```

# Questão: 06

Uma aplicação bancária possui a seguinte classe:

```java
public class ContaBancaria {
    private String numero;
    private float saldo;

    public ContaBancaria(String numero, float saldo) {
        this.numero = numero;
        this.saldo = saldo;
    }
}
```

No programa principal são executadas as instruções:

```java
ContaBancaria bobConta =
    new ContaBancaria("001", 500.0f);

ContaBancaria adaConta =
    new ContaBancaria("002", 800.0f);
```

Considerando os conceitos de classes e objetos, avalie as afirmações:

I. `bobConta` e `adaConta` são objetos criados a partir da mesma classe.

II. Cada objeto possui seu próprio estado.

III. A alteração do saldo de `bobConta` altera automaticamente o saldo de `adaConta`.

IV. `bobConta == adaConta` resulta em `false`, pois as variáveis referenciam objetos distintos.

Assinale a alternativa correta:

- (A) Apenas I e II.
- (B) Apenas I, II e III.
- (C) Apenas I, II e IV.
- (D) Apenas III e IV.
- (E) I, II, III e IV.

Justifique sua resposta.

# Questão: 07

Considere duas versões de uma classe `Pokemon`.

**Versão A:**

```java
public class Pokemon {
    public int hp;
}
```

**Versão B:**

```java
public class Pokemon {
    private int hp;

    public int getHp() {
        return hp;
    }

    public void setHp(int hp) {
        if (hp >= 0) {
            this.hp = hp;
        }
    }
}
```

A respeito das duas implementações, assinale a alternativa correta:

- (A) A versão A apresenta maior encapsulamento porque o atributo pode ser acessado diretamente.
- (B) A versão B permite controlar alterações realizadas no estado do objeto.
- (C) Getters e setters tornam obrigatoriamente todos os atributos públicos.
- (D) Um atributo `private` não pode ser utilizado pelos métodos da própria classe.
- (E) Encapsulamento significa apenas ocultar completamente os dados, sem permitir sua consulta.

Justifique sua resposta.