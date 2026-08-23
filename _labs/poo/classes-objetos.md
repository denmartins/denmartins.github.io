---
title: "Programação Orientada a Objetos - Classe e Objetos em Java"
collection: labs
type: "Lab"
permalink: /labs/poo-classes-objetos
date: 2026-08-24
location: "Ribeirão Preto, Brazil"
---

Neste laboratório, você desenvolverá um programa simples para representar duas contas bancárias.

Serão criados dois objetos da classe `ContaBancaria`:

- `bobConta`
- `adaConta`

Cada conta deverá possuir seu próprio número e saldo e deverá permitir operações de crédito e débito.

Ao longo das tarefas, o programa será evoluído para permitir a escolha da conta e da operação por meio de **argumentos de linha de comando**.

### Tarefa 1: Criando e instanciando contas

Implemente a classe `ContaBancaria` contendo:

**Atributos:**

- `numero`: número da conta;
- `saldo`: saldo atual.

**Métodos:**

- `creditar(float valor)`;
- `debitar(float valor)`;
- `getNumero()`;
- `getSaldo()`.

Crie um construtor que receba o número da conta e inicialize seu saldo com `0.0f`.

Na classe `Principal`, instancie:

```java
ContaBancaria bobConta = new ContaBancaria("001");
ContaBancaria adaConta = new ContaBancaria("002");
````

Exiba os dados das duas contas.

Em seguida, compare as referências:

```java
System.out.println(bobConta == adaConta);
```

Responda:

1. Qual foi o resultado da comparação?
2. `bobConta` e `adaConta` pertencem à mesma classe?
3. Se pertencem à mesma classe, por que `bobConta == adaConta` resulta em `false`?
4. O operador `==` está comparando o conteúdo das contas ou suas referências?

> **Importante:** duas variáveis podem referenciar objetos da mesma classe e, ainda assim, representar objetos completamente independentes.


### Tarefa 2: Operações usando argumentos de linha de comando

Modifique a classe `Principal` para permitir que o usuário escolha:

1. a conta;
2. a operação;
3. o valor.

A execução deverá seguir este formato:

```bash
java Principal bob creditar 500
```

ou:

```bash
java Principal ada debitar 100
```

Os argumentos estarão disponíveis em:

```java
args[0] // conta
args[1] // operação
args[2] // valor
```

Converta o terceiro argumento para `float`:

```java
float valor = Float.parseFloat(args[2]);
```

Utilize `switch/case` para selecionar primeiro a conta e depois a operação.

Exemplo de estrutura:

```text
Conta escolhida
│
├── bob
│   ├── creditar
│   └── debitar
│
└── ada
    ├── creditar
    └── debitar
```

Depois de executar a operação, exiba:

* número da conta;
* operação realizada;
* valor da operação;
* saldo atualizado.

Teste pelo menos quatro comandos diferentes:

```bash
java Principal bob creditar 500
java Principal bob debitar 100
java Principal ada creditar 1000
java Principal ada debitar 250
```


### Tarefa 3: Modificando o estado inicial

Até este momento, o construtor define:

```java
saldo = 0.0f;
```

Modifique o construtor para que o saldo inicial também seja informado durante a criação do objeto:

```java
ContaBancaria(String numero, float saldo)
```

Depois, instancie as contas com valores iniciais diferentes:

```java
ContaBancaria bobConta = new ContaBancaria("001", 100.0f);
ContaBancaria adaConta = new ContaBancaria("002", 500.0f);
```

Responda:

1. Qual é o saldo de cada objeto imediatamente após sua criação?
2. O que mudou em relação à versão anterior?
3. Qual é o papel do construtor na definição do estado inicial do objeto?
4. Alterar `bobConta` modifica o saldo de `adaConta`? Explique.


### Tarefa 4: Transferência entre contas

Agora implemente uma operação mais completa: **transferência entre as duas contas**.

O programa deverá aceitar:

```bash
java Principal transferir bob ada 200
```

Nesse exemplo:

* `bob` é a conta de origem;
* `ada` é a conta de destino;
* `200` é o valor transferido.

Para realizar a transferência:

1. verifique se o valor é positivo;
2. verifique se a conta de origem possui saldo suficiente;
3. debite o valor da conta de origem;
4. credite o mesmo valor na conta de destino;
5. exiba o saldo das duas contas após a transferência.

Exemplo esperado:

```text
Transferência realizada!

Conta Bob
Saldo: 300.0

Conta Ada
Saldo: 700.0
```

Caso o saldo seja insuficiente:

```text
Transferência não realizada: saldo insuficiente.
```

Ao finalizar, responda:

> Durante a transferência, quantos objetos `ContaBancaria` participaram da operação? Como o estado de cada objeto foi alterado?

### Diagrama UML

```text
+--------------------------------+
|        ContaBancaria           |
+--------------------------------+
| - numero : String              |
| - saldo : float                |
+--------------------------------+
| + ContaBancaria(numero)        |
| + creditar(valor) : void       |
| + debitar(valor) : void        |
| + getNumero() : String         |
| + getSaldo() : float           |
+--------------------------------+

             utilizada por

+--------------------------------+
|           Principal            |
+--------------------------------+
| + main(args : String[]) : void |
+--------------------------------+
```

## Requisitos Técnicos

1. Crie os arquivos `ContaBancaria.java` e `Principal.java`.
2. Os atributos `numero` e `saldo` devem ser `private`.
3. Utilize um construtor para inicializar os objetos.
4. Utilize `this` quando parâmetro e atributo tiverem o mesmo nome.
5. Implemente `creditar()` e `debitar()`.
6. Não permita crédito ou débito de valores negativos.
7. Não permita que o saldo fique negativo.
8. Instancie obrigatoriamente `bobConta` e `adaConta`.
9. Compare `bobConta == adaConta`.
10. Utilize argumentos de linha de comando na Tarefa 2.
11. Utilize `switch/case` para selecionar contas e operações.
12. Na Tarefa 3, modifique o construtor para receber o saldo inicial.
13. Na Tarefa 4, implemente a transferência entre as duas contas.
14. Exiba mensagens claras para cada operação realizada.

## Código Inicial (esqueleto)

```java
/**
 * Representa uma conta bancária.
 */
public class ContaBancaria {
    private String numero;
    private float saldo;

    /**
     * Cria uma conta com saldo inicial igual a zero.
     *
     * @param numero número da conta
     */
    public ContaBancaria(String numero) {
        // TODO: inicializar numero
        // TODO: inicializar saldo
    }

    /**
     * Adiciona um valor ao saldo.
     *
     * @param valor valor a ser creditado
     */
    public void creditar(float valor) {
        // TODO: validar e creditar
    }

    /**
     * Retira um valor do saldo.
     *
     * @param valor valor a ser debitado
     */
    public void debitar(float valor) {
        // TODO: validar e debitar
    }

    /**
     * Retorna o número da conta.
     *
     * @return número da conta
     */
    public String getNumero() {
        return numero;
    }

    /**
     * Retorna o saldo atual.
     *
     * @return saldo da conta
     */
    public float getSaldo() {
        return saldo;
    }
}
```

```java
/**
 * Programa para manipular duas contas bancárias.
 */
public class Principal {

    /**
     * Executa o programa.
     *
     * @param args argumentos de linha de comando
     */
    public static void main(String[] args) {

        ContaBancaria bobConta =
            new ContaBancaria("001");

        ContaBancaria adaConta =
            new ContaBancaria("002");

        System.out.println(
            "Mesma referência? " + (bobConta == adaConta)
        );

        // TODO: verificar os argumentos recebidos

        // TODO: identificar a conta com switch/case

        // TODO: identificar a operação com switch/case

        // TODO: realizar crédito ou débito

        // TODO: exibir o saldo atualizado
    }
}
```