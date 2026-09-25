---
title: "Programação Orientada a Objetos - Batalha Pokemon"
collection: labs
type: "Lab"
permalink: /labs/poo-batalha-pokemon
date: 2026-09-25
location: "Ribeirão Preto, Brazil"
---

# 1. Introdução

Você deverá implementar um **Sistema Simplificado de Batalha Pokémon** executado inteiramente no terminal.

Dois treinadores participarão da batalha:

```text
Treinador 1
      |
      └── Time com 6 Pokémon

Treinador 2
      |
      └── Time com 6 Pokémon
```

Cada treinador deverá possuir exatamente **6 Pokémon**.

Os Pokémon poderão ser apenas de três tipos:

```text
Água
Fogo
Grama
```

A batalha acontece em turnos. Em seu turno, cada treinador poderá escolher entre:

```text
1 - Atacar
2 - Trocar Pokémon
```

A batalha termina quando todos os 6 Pokémon de um treinador estiverem derrotados.

---

# 2. Regras de Tipos

O sistema deverá implementar as seguintes vantagens:

```text
Água  → dano dobrado contra Fogo
Fogo  → dano dobrado contra Grama
Grama → dano dobrado contra Água
```

Representação:

```text
        Água
       /    \
      ↓      ↑
    Fogo ← Grama
```

Mais precisamente:

| Atacante | Defensor | Multiplicador |
|---|---|---:|
| Água | Fogo | ×2 |
| Fogo | Grama | ×2 |
| Grama | Água | ×2 |
| Demais combinações | — | ×1 |

> **Importante:** neste laboratório não será utilizada resistência com dano reduzido. Quando não houver vantagem, o multiplicador será `1`.

---

# 3. Estrutura Sugerida do Sistema

Implemente pelo menos as seguintes classes:

```text
Pokemon
Time
Treinador
BatalhaPokemon
Principal
```

Uma organização possível:

```text
Treinador
    ◆
    |
    └── Time
          |
          └── Pokemon[6]

BatalhaPokemon
    |
    ├── Treinador 1
    └── Treinador 2
```

## Responsabilidades sugeridas

### `Pokemon`

Responsável por:

- armazenar seus próprios atributos;
- controlar seus pontos de vida;
- informar se está derrotado;
- receber dano;
- disponibilizar os dados necessários para o cálculo de ataque.

### `Time`

Responsável por:

- armazenar os 6 Pokémon;
- permitir alterar a ordem da equipe antes da batalha;
- retornar um Pokémon pela posição;
- verificar se ainda existem Pokémon disponíveis;
- informar quais Pokémon estão aptos para batalha.

### `Treinador`

Responsável por:

- armazenar o nome do treinador;
- possuir seu `Time`;
- manter qual Pokémon está atualmente em batalha;
- trocar o Pokémon ativo.

### `BatalhaPokemon`

Responsável por:

- controlar os turnos;
- solicitar as ações dos treinadores;
- executar ataques;
- controlar trocas;
- verificar Pokémon derrotados;
- verificar quando a batalha terminou.

### `Principal`

Responsável apenas por:

- criar os objetos principais;
- criar os Pokémon;
- montar os times;
- iniciar a configuração da ordem;
- iniciar a batalha.

> Evite colocar toda a lógica do jogo dentro do método `main()`.

---

# 4. Classe `Pokemon`

Cada Pokémon deverá possuir pelo menos os seguintes atributos:

```java
private String nome;
private String tipo;
private int hpMaximo;
private int hpAtual;
private int ataque;
private int defesa;
```

Exemplos válidos:

| Pokémon | Tipo | HP | ATK | DEF |
|---|---|---:|---:|---:|
| Squirtle | Água | 105 | 48 | 65 |
| Psyduck | Água | 100 | 52 | 48 |
| Totodile | Água | 108 | 55 | 52 |
| Mudkip | Água | 110 | 50 | 55 |
| Charmander | Fogo | 95 | 52 | 43 |
| Vulpix | Fogo | 98 | 50 | 45 |
| Cyndaquil | Fogo | 100 | 52 | 44 |
| Torchic | Fogo | 96 | 55 | 42 |
| Bulbasaur | Grama | 110 | 49 | 49 |
| Chikorita | Grama | 112 | 48 | 55 |
| Treecko | Grama | 95 | 55 | 40 |
| Turtwig | Grama | 115 | 50 | 60 |

Os valores acima são didáticos. Não precisam corresponder aos valores oficiais dos jogos.

---

# 5. Encapsulamento do Pokémon

Os atributos devem ser `private`.

Não permita:

```java
pokemon.hpAtual = -1000;
```

Crie métodos que controlem as alterações, por exemplo:

```java
public void receberDano(int dano) {
    // TODO
}
```

A implementação deverá garantir:

```text
hpAtual nunca < 0
```

Também implemente:

```java
public boolean estaDerrotado()
```

Resultado esperado:

```text
true  → HP atual == 0
false → HP atual > 0
```

---

# 6. Constantes para os Tipos

Evite repetir Strings arbitrárias ao longo do código.

Uma possibilidade é declarar constantes na classe `Pokemon`:

```java
public static final String TIPO_AGUA = "Agua";
public static final String TIPO_FOGO = "Fogo";
public static final String TIPO_GRAMA = "Grama";
```

Assim:

```java
Pokemon.TIPO_AGUA
```

é preferível a repetir:

```java
"Agua"
```

em vários pontos do programa.

---

# 7. Cálculo do Dano

Utilize a seguinte fórmula simplificada.

## Passo 1 — Dano base

```text
danoBase = ataqueAtacante - (defesaDefensor / 2)
```

O dano base nunca poderá ser menor que `1`.

```java
int danoBase =
    atacante.getAtaque()
    - defensor.getDefesa() / 2;

if (danoBase < 1) {
    danoBase = 1;
}
```

### Exemplo

```text
Squirtle (Água)
ATK = 48

Charmander (Fogo)
DEF = 43
```

Dano base:

```text
48 - (43 / 2)
48 - 21
27
```

Como Água possui vantagem sobre Fogo:

```text
27 × 2 = 54
```

---

# 8. Vantagem de Tipo

Se houver vantagem:

```text
multiplicadorTipo = 2
```

Caso contrário:

```text
multiplicadorTipo = 1
```

Casos de vantagem:

```text
Água  → Fogo
Fogo  → Grama
Grama → Água
```

Uma assinatura possível:

```java
private int calcularMultiplicadorTipo(
        Pokemon atacante,
        Pokemon defensor) {

    // TODO
    return 1;
}
```

### Dica

Compare Strings com `.equals()`:

```java
atacante.getTipo().equals(Pokemon.TIPO_AGUA)
```

> Não utilize `==` para comparar o conteúdo de `String`.

---

# 9. Dano Crítico e Falha Crítica

Utilize:

```java
import java.util.Random;
```

O sistema deverá possuir uma pequena chance de:

```text
5%  → Falha crítica
10% → Ataque crítico
85% → Ataque normal
```

Uma implementação possível começa com:

```java
Random random = new Random();
int sorteio = random.nextInt(100);
```

O resultado estará entre `0` e `99`.

Use:

```text
0  até 4   → falha crítica
5  até 14  → ataque crítico
15 até 99  → ataque normal
```

## Falha crítica

Em uma falha crítica:

```text
dano = 0
```

Exiba:

```text
Falha crítica! O ataque não acertou.
```

## Ataque crítico

Em um ataque crítico, dobre o dano depois de aplicar a vantagem de tipo:

```text
danoCritico = danoNormal × 2
```

Exemplo:

```text
Dano base:          27
Vantagem de tipo:  ×2
Dano normal:        54
Crítico:            ×2

Dano final:        108
```

Portanto, um ataque com vantagem de tipo e crítico poderá causar:

```text
4 × danoBase
```

---

# 10. Algoritmo Completo do Dano

```text
1. Calcular danoBase
          ↓
2. Verificar vantagem de tipo
          ↓
3. Aplicar multiplicador de tipo
          ↓
4. Sortear evento aleatório
          ↓
      ┌───────────────┐
      │               │
Falha crítica      Crítico
 dano = 0          dano × 2
      │               │
      └───────┬───────┘
              ↓
5. Aplicar dano no defensor
```

### Pseudocódigo

```java
danoBase = ataque - defesa / 2;

if (danoBase < 1)
    danoBase = 1;

multiplicadorTipo = obterMultiplicador(...);

dano = danoBase * multiplicadorTipo;

sorteio = random.nextInt(100);

if (sorteio < 5)
    dano = 0;
else if (sorteio < 15)
    dano = dano * 2;

defensor.receberDano(dano);
```

---

# 11. Classe `Time`

Cada treinador possui exatamente 6 Pokémon.

Utilize:

```java
private Pokemon[] pokemons;
```

No construtor:

```java
pokemons = new Pokemon[6];
```

Uma possível estrutura:

```java
public class Time {

    public static final int TAMANHO_TIME = 6;

    private Pokemon[] pokemons;
    private int quantidade;

    public Time() {
        pokemons = new Pokemon[TAMANHO_TIME];
        quantidade = 0;
    }

    public void adicionarPokemon(Pokemon pokemon) {
        // TODO
    }
}
```

---

# 12. Seleção da Ordem do Time

Antes da batalha, cada treinador deverá escolher a ordem dos seus Pokémon.

Exemplo inicial:

```text
Time disponível:

1 - Squirtle
2 - Bulbasaur
3 - Charmander
4 - Psyduck
5 - Vulpix
6 - Treecko
```

O programa deverá pedir:

```text
Escolha o Pokémon para a posição 1: 3
Escolha o Pokémon para a posição 2: 1
Escolha o Pokémon para a posição 3: 6
...
```

Resultado:

```text
=== ORDEM DO TIME ===

1 - Charmander
2 - Squirtle
3 - Treecko
4 - ...
```

Cada Pokémon só poderá ser selecionado **uma vez**.

## Dica de implementação

Uma estratégia simples é criar:

```java
boolean[] selecionados = new boolean[6];
Pokemon[] timeOrdenado = new Pokemon[6];
```

Quando o usuário escolher uma posição, marque o índice correspondente:

```java
selecionados[indice] = true;
```

Antes de aceitar uma nova escolha:

```java
if (selecionados[indice]) {
    System.out.println(
        "Esse Pokémon já foi selecionado."
    );
}
```

Ao final, o array ordenado deverá substituir a ordem anterior.

---

# 13. Pokémon Ativo

O primeiro Pokémon do time será o Pokémon inicial da batalha.

Por exemplo:

```text
Time:
[Charmander, Squirtle, Bulbasaur, ...]
```

Então:

```text
Pokémon ativo = Charmander
```

O `Treinador` deverá manter qual posição do time está atualmente ativa.

Uma possibilidade:

```java
private int indicePokemonAtivo;
```

Inicialmente:

```java
indicePokemonAtivo = 0;
```

---

# 14. Classe `Treinador`

Estrutura sugerida:

```java
public class Treinador {

    private String nome;
    private Time time;
    private int indicePokemonAtivo;

    public Treinador(String nome) {
        this.nome = nome;
        this.time = new Time();
        this.indicePokemonAtivo = 0;
    }

    public Pokemon getPokemonAtivo() {
        // TODO
        return null;
    }

    public void trocarPokemon(int indice) {
        // TODO
    }
}
```

Neste modelo:

```text
Treinador ◆── Time
```

é uma **composição**, pois o treinador cria e controla seu time.

Enquanto:

```text
Time ─── Pokemon
```

é uma **associação**, pois os objetos `Pokemon` podem ser criados independentemente e depois adicionados ao time.

---

# 15. Fluxo da Batalha

Depois que os times estiverem configurados:

```text
=== INÍCIO DA BATALHA ===

Ash
Pokémon ativo: Charmander

Misty
Pokémon ativo: Squirtle
```

A batalha deve acontecer em turnos alternados:

```text
Turno 1 → Treinador 1
Turno 2 → Treinador 2
Turno 3 → Treinador 1
Turno 4 → Treinador 2
...
```

---

# 16. Menu de Ações

Em cada turno:

```text
=== TURNO DE ASH ===

Pokémon ativo:
Charmander
HP: 95 / 95

Oponente:
Squirtle
HP: 105 / 105

Escolha uma ação:

1 - Atacar
2 - Trocar Pokémon
```

Utilize `Scanner` para ler a escolha.

---

# 17. Ação: Atacar

Caso o jogador selecione:

```text
1 - Atacar
```

o Pokémon ativo deve atacar o Pokémon ativo do adversário.

Exemplo:

```text
Charmander atacou Bulbasaur!

Dano base: 28
Vantagem de tipo: Fogo > Grama (x2)

Dano causado: 56

Bulbasaur
HP: 54 / 110
```

Caso ocorra crítico:

```text
ATAQUE CRÍTICO!

Dano causado: 112
```

Caso ocorra falha crítica:

```text
FALHA CRÍTICA!

Charmander errou completamente o ataque.
Dano causado: 0
```

---

# 18. Ação: Trocar Pokémon

Caso seja selecionado:

```text
2 - Trocar Pokémon
```

exiba:

```text
=== SELECIONE UM POKÉMON ===

1 - Charmander    HP: 70/95    [ATIVO]
2 - Squirtle      HP: 105/105
3 - Bulbasaur     HP: 0/110    [DERROTADO]
4 - Psyduck       HP: 100/100
5 - Vulpix        HP: 98/98
6 - Treecko       HP: 95/95
```

Não permita:

- escolher o Pokémon que já está ativo;
- escolher um Pokémon derrotado;
- escolher posição inválida.

Uma troca válida **consome o turno**.

Exemplo:

```text
Ash trocou Charmander por Squirtle.
```

Depois disso, o turno passa para o adversário.

---

# 19. Pokémon Derrotado

Quando:

```text
hpAtual == 0
```

o Pokémon está derrotado.

Exemplo:

```text
Bulbasaur recebeu 54 de dano.

HP: 0 / 110

Bulbasaur foi derrotado!
```

Se ainda existirem Pokémon disponíveis, o treinador deve obrigatoriamente selecionar outro.

```text
Escolha o próximo Pokémon:
```

Essa troca obrigatória **não** deve ser considerada uma ação adicional de turno.

---

# 20. Fim da Batalha

A batalha termina quando um treinador não possui mais Pokémon disponíveis.

Implemente algo semelhante a:

```java
public boolean possuiPokemonDisponivel()
```

O método deverá percorrer o array e verificar se existe pelo menos um Pokémon com:

```text
HP > 0
```

Quando não houver:

```text
================================
         FIM DA BATALHA
================================

Todos os Pokémon de Misty foram derrotados.

Vencedor: Ash!
```

---

# 21. Estrutura do Loop Principal

Uma estrutura possível:

```text
enquanto os dois treinadores possuírem Pokémon disponíveis:

    exibir situação atual

    executar turno do treinador atual

    se Pokémon defensor foi derrotado:
        verificar se existem Pokémon disponíveis

        se não existem:
            encerrar batalha

        caso contrário:
            solicitar troca obrigatória

    alternar treinador
```

Em Java:

```java
while (treinador1.possuiPokemonDisponivel()
        && treinador2.possuiPokemonDisponivel()) {

    // TODO
}
```

---

# 22. Classes e Relacionamentos Esperados

```text
+----------------+
|   Treinador    |
+----------------+
| nome           |
| time           |
| pokemonAtivo   |
+----------------+
        ◆
        |
        |
+----------------+
|      Time      |
+----------------+
| Pokemon[6]     |
+----------------+
        |
        | associação
        |
        +-----------> Pokemon
        +-----------> Pokemon
        +-----------> Pokemon
        +-----------> ...
```

E:

```text
BatalhaPokemon
      |
      +── Treinador 1
      |
      └── Treinador 2
```

---

# 23. Código Inicial Sugerido — `Pokemon.java`

```java
public class Pokemon {

    public static final String TIPO_AGUA = "Agua";
    public static final String TIPO_FOGO = "Fogo";
    public static final String TIPO_GRAMA = "Grama";

    private String nome;
    private String tipo;

    private int hpMaximo;
    private int hpAtual;

    private int ataque;
    private int defesa;

    public Pokemon(
            String nome,
            String tipo,
            int hpMaximo,
            int ataque,
            int defesa) {

        // TODO
    }

    public void receberDano(int dano) {
        // TODO
    }

    public boolean estaDerrotado() {
        // TODO
        return false;
    }

    public String getNome() {
        return nome;
    }

    public String getTipo() {
        return tipo;
    }

    public int getHpMaximo() {
        return hpMaximo;
    }

    public int getHpAtual() {
        return hpAtual;
    }

    public int getAtaque() {
        return ataque;
    }

    public int getDefesa() {
        return defesa;
    }
}
```

---

# 24. Código Inicial Sugerido — `Time.java`

```java
public class Time {

    public static final int TAMANHO_TIME = 6;

    private Pokemon[] pokemons;
    private int quantidade;

    public Time() {
        pokemons = new Pokemon[TAMANHO_TIME];
        quantidade = 0;
    }

    public void adicionarPokemon(Pokemon pokemon) {
        // TODO
    }

    public Pokemon getPokemon(int indice) {
        // TODO
        return null;
    }

    public boolean possuiPokemonDisponivel() {
        // TODO
        return false;
    }

    public void exibirTime() {
        // TODO
    }

    public void definirOrdem() {
        // TODO
    }
}
```

> Você pode passar um objeto `Scanner` como parâmetro para `definirOrdem()` em vez de criar vários objetos `Scanner`.

---

# 25. Código Inicial Sugerido — `Treinador.java`

```java
public class Treinador {

    private String nome;
    private Time time;
    private int indicePokemonAtivo;

    public Treinador(String nome) {
        this.nome = nome;
        this.time = new Time();
        indicePokemonAtivo = 0;
    }

    public Pokemon getPokemonAtivo() {
        // TODO
        return null;
    }

    public void trocarPokemon(int indice) {
        // TODO
    }

    public boolean possuiPokemonDisponivel() {
        // TODO
        return false;
    }

    public String getNome() {
        return nome;
    }

    public Time getTime() {
        return time;
    }
}
```

---

# 26. Código Inicial Sugerido — `BatalhaPokemon.java`

```java
import java.util.Random;
import java.util.Scanner;

public class BatalhaPokemon {

    private Treinador treinador1;
    private Treinador treinador2;

    private Random random;
    private Scanner scanner;

    public BatalhaPokemon(
            Treinador treinador1,
            Treinador treinador2,
            Scanner scanner) {

        this.treinador1 = treinador1;
        this.treinador2 = treinador2;

        this.scanner = scanner;
        this.random = new Random();
    }

    public void iniciar() {
        // TODO
    }

    private void executarTurno(
            Treinador atual,
            Treinador adversario) {

        // TODO
    }

    private int calcularDano(
            Pokemon atacante,
            Pokemon defensor) {

        // TODO
        return 0;
    }

    private int calcularMultiplicadorTipo(
            Pokemon atacante,
            Pokemon defensor) {

        // TODO
        return 1;
    }
}
```

---

# 27. Código Inicial Sugerido — `Principal.java`

```java
import java.util.Scanner;

public class Principal {

    public static void main(String[] args) {

        Scanner scanner = new Scanner(System.in);

        Treinador treinador1 =
            new Treinador("Ash");

        Treinador treinador2 =
            new Treinador("Misty");

        // TODO: criar os 12 Pokemon

        // TODO: adicionar 6 Pokemon a cada time

        // TODO: permitir aos treinadores
        // escolherem a ordem dos times

        BatalhaPokemon batalha =
            new BatalhaPokemon(
                treinador1,
                treinador2,
                scanner
            );

        batalha.iniciar();

        scanner.close();
    }
}
```

---

# 28. Sequência Recomendada de Implementação

Não tente implementar toda a batalha de uma única vez.

## Etapa 1 — Pokémon

Implemente e teste:

```text
Pokemon
getters
receberDano()
estaDerrotado()
```

## Etapa 2 — Time

Implemente:

```text
adicionarPokemon()
getPokemon()
exibirTime()
possuiPokemonDisponivel()
```

Teste com 6 objetos.

## Etapa 3 — Ordenação do time

Implemente a seleção da ordem utilizando:

```text
Pokemon[]
boolean[]
Scanner
```

Teste se:

- nenhum Pokémon pode aparecer duas vezes;
- todos aparecem exatamente uma vez.

## Etapa 4 — Treinador

Implemente:

```text
getPokemonAtivo()
trocarPokemon()
possuiPokemonDisponivel()
```

## Etapa 5 — Dano

Teste separadamente:

```text
Água × Fogo
Fogo × Grama
Grama × Água
Água × Água
```

Antes de adicionar críticos.

## Etapa 6 — Crítico e falha crítica

Adicione:

```text
Random
5% falha
10% crítico
```

Execute vários ataques e observe os resultados.

## Etapa 7 — Um único turno

Faça primeiro:

```text
Treinador 1 ataca Treinador 2
```

sem loop.

Quando funcionar, adicione a alternância de turnos.

## Etapa 8 — Batalha completa

Somente então implemente:

```text
while (...)
```

até que um treinador não tenha Pokémon disponíveis.

---

# 29. Testes Mínimos Obrigatórios

Antes da entrega, teste pelo menos os seguintes cenários.

### Teste 1 — Vantagem Água → Fogo

```text
Squirtle ataca Charmander
```

O dano deve possuir multiplicador `2`.

### Teste 2 — Vantagem Fogo → Grama

```text
Charmander ataca Bulbasaur
```

Multiplicador `2`.

### Teste 3 — Vantagem Grama → Água

```text
Bulbasaur ataca Squirtle
```

Multiplicador `2`.

### Teste 4 — Sem vantagem

```text
Squirtle ataca Psyduck
```

Multiplicador `1`.

### Teste 5 — Troca

Troque um Pokémon ativo por outro disponível. O turno deverá terminar.

### Teste 6 — Troca inválida

Tente selecionar um Pokémon derrotado. O sistema deve recusar.

### Teste 7 — Pokémon derrotado

Reduza o HP até `0`. O sistema deve impedir que esse Pokémon continue lutando.

### Teste 8 — Fim de batalha

Quando todos os Pokémon de um treinador chegarem a `0 HP`, a batalha deverá terminar.

---

# 30. Exemplo Resumido de Execução

```text
=================================
       BATALHA POKÉMON
=================================

Ash vs Misty

=== TURNO DE ASH ===

Ativo:
Charmander [Fogo]
HP: 95/95

Adversário:
Bulbasaur [Grama]
HP: 110/110

1 - Atacar
2 - Trocar Pokémon

Escolha: 1

Charmander atacou Bulbasaur!

Dano base: 28
Vantagem: Fogo > Grama
Multiplicador: x2

ATAQUE CRÍTICO!

Dano final: 112

Bulbasaur recebeu 112 de dano.
HP: 0/110

Bulbasaur foi derrotado!

Misty, escolha o próximo Pokémon:

1 - Squirtle  HP: 105/105
2 - Psyduck   HP: 100/100
3 - Vulpix    HP: 98/98
...
```

---

# 31. Dicas Importantes

## Dica 1 — Uma classe, uma responsabilidade principal

Pergunte:

```text
Quem deveria saber isso?
```

Exemplos:

```text
Quem controla o HP?
→ Pokemon

Quem conhece os 6 Pokémon?
→ Time

Quem sabe qual Pokémon está ativo?
→ Treinador

Quem controla o turno?
→ BatalhaPokemon
```

## Dica 2 — Proteja os arrays

Evite expor livremente o array interno:

```java
public Pokemon[] getPokemons() {
    return pokemons;
}
```

Prefira operações específicas:

```java
getPokemon(indice)
adicionarPokemon(...)
exibirTime()
```

## Dica 3 — Não use números mágicos

Evite:

```java
if (quantidade < 6)
```

Prefira:

```java
public static final int TAMANHO_TIME = 6;
```

Para probabilidades:

```java
public static final int CHANCE_FALHA_CRITICA = 5;
public static final int CHANCE_CRITICO = 10;
```

## Dica 4 — Valide todas as entradas

Ao escolher uma posição, verifique:

```text
índice válido?
Pokémon existe?
Pokémon está derrotado?
Pokémon já está ativo?
```

## Dica 5 — Use métodos auxiliares

Se um método estiver muito grande, divida-o:

```java
exibirStatusBatalha()
selecionarAcao()
executarAtaque()
selecionarTroca()
calcularDano()
calcularMultiplicadorTipo()
```

---

# 32. Requisitos Técnicos Obrigatórios

A solução deverá:

- utilizar Java;
- funcionar em linha de comando;
- criar exatamente 2 treinadores;
- criar exatamente 6 Pokémon para cada treinador;
- utilizar apenas os tipos Água, Fogo e Grama;
- utilizar `Pokemon[]` para representar o time;
- permitir escolher a ordem dos 6 Pokémon antes da batalha;
- impedir repetição de Pokémon durante a escolha da ordem;
- manter um Pokémon ativo por treinador;
- permitir as ações `Atacar` e `Trocar Pokémon`;
- fazer a troca consumir o turno;
- impedir a seleção de Pokémon derrotados;
- implementar vantagens de tipo com dano ×2;
- utilizar a fórmula de dano definida neste enunciado;
- implementar 5% de falha crítica;
- implementar 10% de dano crítico;
- utilizar `Random`;
- utilizar `Scanner`;
- impedir HP negativo;
- detectar Pokémon derrotados;
- exigir troca quando o Pokémon ativo for derrotado;
- encerrar a partida quando um time inteiro estiver derrotado;
- utilizar encapsulamento;
- separar a solução em múltiplas classes.

---


# Desafios Opcionais

Após finalizar todos os requisitos obrigatórios, escolha uma extensão:

1. Exibir uma barra de HP:

```text
Charmander [██████----] 60/95
```

2. Permitir que os treinadores informem seus nomes.
3. Sortear quem inicia a batalha.
4. Registrar um histórico textual da batalha em um array.
5. Exibir ao final:

```text
Total de turnos
Quantidade de críticos
Quantidade de falhas críticas
Pokémon que mais causou dano
```

6. Permitir iniciar uma nova batalha sem reiniciar o programa.

---

## Resultado Esperado

Ao concluir o laboratório, sua aplicação deverá demonstrar na prática como diferentes objetos podem colaborar:

```text
Treinador
    ↓
Time
    ↓
Pokemon
    ↓
estado e comportamento

BatalhaPokemon
    ↓
coordena a interação entre os objetos
```

A solução deve priorizar **responsabilidades claras, estado protegido e colaboração entre objetos**, em vez de concentrar toda a lógica em uma única classe.
