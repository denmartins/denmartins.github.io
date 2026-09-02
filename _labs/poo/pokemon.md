## Objetivos de Aprendizagem

- Utilizar `Scanner` para obter dados durante a execução.
- Instanciar e manipular objetos da classe `Pokemon`.
- Diferenciar atributos de instância e campos `static`.
- Declarar e utilizar constantes com `static final`.
- Utilizar métodos para alterar e consultar o estado dos objetos.
- Compreender quais informações pertencem ao objeto e quais pertencem à classe.

## Enunciado

Você deverá desenvolver um pequeno **Centro de Treinamento Pokémon**.

O programa permitirá cadastrar três Pokémon informados pelo usuário. Cada Pokémon deverá possuir:

- nome;
- tipo;
- pontos de vida (`HP`);
- pontos de ataque (`ATK`).

Além dos dados individuais de cada Pokémon, a classe deverá armazenar a quantidade total de Pokémon criados.

O jogo também estabelecerá dois valores constantes:

```text
HP máximo = 200
ATK máximo = 150
````

Depois do cadastro, o usuário poderá escolher um Pokémon para realizar um treinamento.

Cada treinamento aumentará o ataque do Pokémon em **5 pontos**, respeitando o limite máximo permitido.

---

### Tarefa 1 — Implementar a classe `Pokemon`

Crie a classe `Pokemon` com os atributos:

```text
nome : String
tipo : String
hp   : int
atk  : int
```

Todos devem ser `private`.

Crie um construtor:

```java
Pokemon(String nome, String tipo, int hp, int atk)
```

Utilize `this` para inicializar os atributos.

O construtor deverá garantir que:

```text
hp <= HP_MAXIMO
atk <= ATK_MAXIMO
```

---

### Tarefa 2 — Criar constantes

Adicione à classe:

```java
public static final int HP_MAXIMO = 200;
public static final int ATK_MAXIMO = 150;
```

Esses valores pertencem à classe e não podem ser modificados durante a execução.

Teste criando um Pokémon com:

```text
HP = 250
ATK = 180
```

Verifique quais valores serão armazenados.

---

### Tarefa 3 — Contar objetos criados

Adicione o campo:

```java
private static int quantidadePokemons = 0;
```

Toda vez que um novo Pokémon for criado, incremente esse valor no construtor.

Implemente também:

```java
public static int getQuantidadePokemons()
```

Após cadastrar três Pokémon, o resultado esperado será:

```text
Quantidade de Pokémon criados: 3
```

---

### Tarefa 4 — Entrada de dados com `Scanner`

Na classe `Principal`, utilize `Scanner` para cadastrar três Pokémon.

Para cada objeto, solicite:

```text
Nome:
Tipo:
HP:
ATK:
```

Exemplo:

```text
=== Pokémon 1 ===

Nome: Pikachu
Tipo: Eletrico
HP: 100
ATK: 55
```

Depois, instancie:

```java
Pokemon pokemon1 = new Pokemon(nome, tipo, hp, atk);
```

Repita o processo para:

```text
pokemon1
pokemon2
pokemon3
```

---

### Tarefa 5 — Método `treinar()`

Implemente na classe `Pokemon`:

```java
public void treinar()
```

Cada chamada deve adicionar:

```text
ATK + 5
```

Porém, o ataque nunca poderá ultrapassar:

```java
Pokemon.ATK_MAXIMO
```

Exemplo:

```text
ATK antes: 55

Treinamento realizado!

ATK depois: 60
```

Se o Pokémon já estiver no limite:

```text
ATK antes: 150
ATK depois: 150
```

---

### Tarefa 6 — Escolher um Pokémon para treinar

Depois dos três cadastros, apresente:

```text
=== Centro de Treinamento ===

1 - Pikachu
2 - Charmander
3 - Squirtle

Escolha um Pokémon: 2
```

Utilize `switch/case` para escolher qual objeto será manipulado.

Depois:

1. exiba seu `ATK`;
2. execute `treinar()`;
3. exiba o novo `ATK`.

---

### Tarefa 7 — Desafio

Permita que o usuário escolha **quantas sessões de treinamento** deseja realizar.

Exemplo:

```text
Pokémon: Pikachu
ATK inicial: 55

Quantidade de treinamentos: 4

Treinamento 1 -> ATK: 60
Treinamento 2 -> ATK: 65
Treinamento 3 -> ATK: 70
Treinamento 4 -> ATK: 75
```

Utilize uma estrutura de repetição para realizar os treinamentos.

O `ATK` nunca poderá ultrapassar `ATK_MAXIMO`.

---

### Resultado esperado

Uma possível execução:

```text
=== CADASTRO POKÉMON ===

Pokémon 1
Nome: Pikachu
Tipo: Eletrico
HP: 100
ATK: 55

Pokémon 2
Nome: Charmander
Tipo: Fogo
HP: 95
ATK: 52

Pokémon 3
Nome: Squirtle
Tipo: Agua
HP: 105
ATK: 48

Pokémon cadastrados: 3
HP máximo permitido: 200
ATK máximo permitido: 150

=== CENTRO DE TREINAMENTO ===

1 - Pikachu
2 - Charmander
3 - Squirtle

Escolha: 1
Quantidade de treinamentos: 3

Pikachu treinou!
ATK: 60

Pikachu treinou!
ATK: 65

Pikachu treinou!
ATK: 70
```

### Diagrama UML

```text
+--------------------------------------+
|               Pokemon                |
+--------------------------------------+
| - nome : String                      |
| - tipo : String                      |
| - hp : int                           |
| - atk : int                          |
| - quantidadePokemons : int {static}  |
| + HP_MAXIMO : int {static, final}    |
| + ATK_MAXIMO : int {static, final}   |
+--------------------------------------+
| + Pokemon(nome, tipo, hp, atk)       |
| + treinar() : void                   |
| + getNome() : String                 |
| + getTipo() : String                 |
| + getHp() : int                      |
| + getAtk() : int                     |
| + getQuantidadePokemons() : int      |
+--------------------------------------+

                  utilizada por

+--------------------------------------+
|              Principal               |
+--------------------------------------+
| + main(args : String[]) : void       |
+--------------------------------------+
```

## Requisitos Técnicos

1. Criar os arquivos `Pokemon.java` e `Principal.java`.
2. Declarar os atributos dos Pokémon como `private`.
3. Utilizar um construtor para inicializar os objetos.
4. Utilizar `this` dentro do construtor.
5. Criar exatamente três objetos `Pokemon`.
6. Utilizar `Scanner` para obter os dados.
7. Declarar `quantidadePokemons` como `static`.
8. Incrementar `quantidadePokemons` no construtor.
9. Criar `getQuantidadePokemons()` como método `static`.
10. Declarar `HP_MAXIMO` utilizando `public static final`.
11. Declarar `ATK_MAXIMO` utilizando `public static final`.
12. Impedir que `HP` ultrapasse `HP_MAXIMO`.
13. Impedir que `ATK` ultrapasse `ATK_MAXIMO`.
14. Implementar o método `treinar()`.
15. Utilizar `switch/case` para selecionar o Pokémon.
16. Utilizar uma estrutura de repetição no desafio.
17. Fechar o objeto `Scanner` ao final do programa.

## Código Inicial (esqueleto)

```java
/**
 * Representa um Pokémon.
 */
public class Pokemon {

    private String nome;
    private String tipo;
    private int hp;
    private int atk;

    private static int quantidadePokemons = 0;

    public static final int HP_MAXIMO = 200;
    public static final int ATK_MAXIMO = 150;

    /**
     * Inicializa um Pokémon.
     *
     * @param nome nome do Pokémon
     * @param tipo tipo do Pokémon
     * @param hp pontos de vida
     * @param atk pontos de ataque
     */
    public Pokemon(String nome, String tipo, int hp, int atk) {
        // TODO: inicializar nome e tipo

        // TODO: validar HP_MAXIMO

        // TODO: validar ATK_MAXIMO

        // TODO: incrementar quantidadePokemons
    }

    /**
     * Realiza uma sessão de treinamento.
     */
    public void treinar() {
        // TODO: adicionar 5 ao ATK
        // TODO: respeitar ATK_MAXIMO
    }

    /**
     * Retorna a quantidade de Pokémon criados.
     *
     * @return quantidade de objetos Pokemon criados
     */
    public static int getQuantidadePokemons() {
        // TODO
        return 0;
    }

    /**
     * Retorna o nome.
     *
     * @return nome do Pokémon
     */
    public String getNome() {
        return nome;
    }

    /**
     * Retorna o tipo.
     *
     * @return tipo do Pokémon
     */
    public String getTipo() {
        return tipo;
    }

    /**
     * Retorna o HP.
     *
     * @return pontos de vida
     */
    public int getHp() {
        return hp;
    }

    /**
     * Retorna o ATK.
     *
     * @return pontos de ataque
     */
    public int getAtk() {
        return atk;
    }
}
```

```java
import java.util.Scanner;

/**
 * Executa o Centro de Treinamento Pokémon.
 */
public class Principal {

    /**
     * Executa o programa.
     *
     * @param args argumentos de linha de comando
     */
    public static void main(String[] args) {

        Scanner scanner = new Scanner(System.in);

        // TODO: cadastrar pokemon1

        // TODO: cadastrar pokemon2

        // TODO: cadastrar pokemon3

        // TODO: exibir quantidade de Pokémon

        // TODO: exibir HP_MAXIMO e ATK_MAXIMO

        // TODO: apresentar os três Pokémon

        // TODO: solicitar a escolha

        // TODO: selecionar o objeto com switch/case

        // TODO: solicitar quantidade de treinamentos

        // TODO: executar os treinamentos

        scanner.close();
    }
}
```
