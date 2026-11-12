---
title: "Laboratório Prático: Princípios SOLID"
collection: labs
type: "Lab"
permalink: /labs/principios-solid
date: 2026-11-12
location: "Ribeirão Preto, Brazil"
---


## Como este tutorial funciona

Primeiro construiremos as classes básicas e uma implementação acoplada que funciona. Depois criaremos uma segunda versão, preservando a primeira para comparação. Cada etapa identifica os arquivos que devem ser criados, substituídos ou excluídos e inclui um checkpoint executável.

- Use uma pasta chamada `pokemon-solid` e mantenha todos os arquivos `.java` na sua raiz, sem declarações `package`.
- Cada classe ou interface pública fica em seu próprio arquivo, com o nome indicado.
- **Criar** significa adicionar um arquivo novo. **Substituir** significa apagar o conteúdo anterior daquele arquivo e copiar a nova versão completa.
- Execute o checkpoint somente depois de concluir todos os arquivos da etapa. Durante a troca de uma interface, é natural que os arquivos dependentes precisem ser atualizados antes de compilar.
- A pasta `out` contém apenas os arquivos compilados. Os comandos compilam todos os fontes atuais; não use a execução direta de `Main.java`, pois agora há várias classes em arquivos separados.
- Não antecipe as interfaces: elas serão introduzidas quando o problema correspondente aparecer.

>  **Nota**: Definições parafraseadas para uso didático. As regras Pokémon são adaptações pedagógicas.


## Objetivos

Construir um sistema pequeno desde o modelo de domínio; reconhecer os custos do acoplamento; refatorar em etapas executáveis; explicar e localizar os cinco princípios SOLID; comparar os resultados antes e depois da mudança de estrutura.

## Cenário e regras

O sistema simula a execução de ataques: recebe atacante, alvo e golpe, calcula o dano, monta uma descrição, registra um evento e apresenta o resultado.

| Elemento | Regra didática |
|---|---|
| Pokémon | Nome preenchido e defesa inteira não negativa |
| Dano | `Math.max(0, poder - defesa)` |
| Choque do Trovão | Poder 40 |
| Lança-Chamas | Poder 60 |
| Jato de Água | Poder 50, acrescentado durante a construção |
| Histórico | Lista de eventos em memória |
| Notificação inicial | Impressão no console |

A fórmula e os valores são simplificações pedagógicas, não uma reprodução das regras dos jogos. Não implementaremos pontos de vida, tipos, vantagens, precisão, cura, persistência ou uma batalha completa. O contrato de golpe que criaremos representa golpes de dano.

**Caso de referência:** Pikachu ataca Squirtle, defesa 20, com Choque do Trovão: `max(0, 40 - 20) = 20`.

# Parte I — Construção da versão acoplada

## Etapa 1 — Criar a classe básica `Pokemon`

Antes de falar em SOLID, precisamos representar os dados usados pelos ataques.

**Classe** define atributos e operações dos objetos. **Encapsulamento** protege o estado interno e oferece operações controladas para acessá-lo. 

O construtor impedirá nome vazio e defesa negativa. Os atributos serão privados e finais: depois da construção, seus valores não mudam neste exemplo.

#### Criar `Pokemon.java`

Copie o conteúdo completo abaixo para esse arquivo.

```java
public class Pokemon {
    private final String nome;
    private final int defesa;

    public Pokemon(String nome, int defesa) {
        if (nome == null || nome.trim().isEmpty() || defesa < 0) {
            throw new IllegalArgumentException("Nome ou defesa inválidos");
        }
        this.nome = nome;
        this.defesa = defesa;
    }

    public String getNome() { return nome; }
    public int getDefesa() { return defesa; }
}
```

**O que observar:** o construtor recebe os dados, valida e atribui os campos. Os getters expõem a leitura. Ainda não há ataque nem aplicação de SOLID sobre o fluxo de batalha.

## Etapa 2 — Criar a aplicação e instanciar os primeiros objetos

Agora podemos criar dois Pokémon e consultar seus atributos.

#### Criar `Main.java`

Copie o conteúdo completo abaixo para esse arquivo.

```java
public class Main {
    public static void main(String[] args) {
        Pokemon pikachu = new Pokemon("Pikachu", 10);
        Pokemon squirtle = new Pokemon("Squirtle", 20);
        System.out.println(pikachu.getNome() + ": defesa " + pikachu.getDefesa());
        System.out.println(squirtle.getNome() + ": defesa " + squirtle.getDefesa());
    }
}
```

#### Checkpoint: objetos básicos funcionando

Na pasta do projeto, execute:

```bash
javac -encoding UTF-8 -d out *.java
java -cp out Main
```

Saída esperada:

```text
Pikachu: defesa 10
Squirtle: defesa 20
```

**Verificação adicional:** tentar `new Pokemon("", 10)` deve produzir `IllegalArgumentException`. Essa validação pertence ao objeto de domínio e continuará presente nas duas versões.

## Etapa 3 — Implementar o ataque na classe acoplada

Vamos resolver a necessidade inicial diretamente: reconhecer dois golpes por nome, calcular, narrar, armazenar e imprimir na mesma classe.

Esta versão funciona, mas reúne decisões que podem mudar separadamente. Ainda não vamos extrair colaboradores nem criar interfaces.

#### Criar `BatalhaAcoplada.java`

Copie o conteúdo completo abaixo para esse arquivo.

```java
import java.util.ArrayList;
import java.util.List;

public class BatalhaAcoplada {
    private final List<String> eventos = new ArrayList<>();

    public int atacar(Pokemon atacante, Pokemon alvo, String golpe) {
        if (atacante == null || alvo == null) {
            throw new IllegalArgumentException("Pokémon obrigatório");
        }
        int poder;
        if ("Choque do Trovão".equals(golpe)) {
            poder = 40;
        } else if ("Lança-Chamas".equals(golpe)) {
            poder = 60;
        } else {
            throw new IllegalArgumentException("Golpe desconhecido");
        }
        int dano = Math.max(0, poder - alvo.getDefesa());
        String mensagem = atacante.getNome() + " usou " + golpe
                + " contra " + alvo.getNome() + ": " + dano + " de dano.";
        eventos.add(mensagem);
        System.out.println(mensagem);
        return dano;
    }

    public int getQuantidadeEventos() {
        return eventos.size();
    }
}
```

#### Substituir `Main.java`

Copie o conteúdo completo abaixo para esse arquivo.

```java
public class Main {
    public static void main(String[] args) {
        Pokemon pikachu = new Pokemon("Pikachu", 10);
        Pokemon squirtle = new Pokemon("Squirtle", 20);
        BatalhaAcoplada batalha = new BatalhaAcoplada();
        int dano = batalha.atacar(pikachu, squirtle, "Choque do Trovão");
        System.out.println("Dano devolvido: " + dano);
        System.out.println("Eventos: " + batalha.getQuantidadeEventos());
    }
}
```

#### Checkpoint: primeiro ataque da versão acoplada

Na pasta do projeto, execute:

```bash
javac -encoding UTF-8 -d out *.java
java -cp out Main
```

Saída esperada:

```text
Pikachu usou Choque do Trovão contra Squirtle: 20 de dano.
Dano devolvido: 20
Eventos: 1
```

### Percurso do método

1. Verifica atacante e alvo.
2. Usa o nome do golpe para escolher o poder.
3. Aplica a fórmula de dano.
4. Monta a mensagem.
5. Acrescenta a mensagem à lista.
6. Imprime no console.
7. Devolve o dano.

O método `getQuantidadeEventos` permite observar que o registro ocorreu. Ele não é uma interface de consulta segregada; estamos apenas construindo a versão inicial.

## Etapa 4 — Evoluir a versão acoplada com um novo golpe

**Nova demanda:** Squirtle deve usar Jato de Água, com poder didático 50.

Para atender à demanda atual, precisamos editar `BatalhaAcoplada.atacar` e acrescentar um ramo ao condicional. Faça isso agora para observar o efeito da escolha inicial.

#### Substituir `BatalhaAcoplada.java`

Copie o conteúdo completo abaixo para esse arquivo.

```java
import java.util.ArrayList;
import java.util.List;

public class BatalhaAcoplada {
    private final List<String> eventos = new ArrayList<>();

    public int atacar(Pokemon atacante, Pokemon alvo, String golpe) {
        if (atacante == null || alvo == null) {
            throw new IllegalArgumentException("Pokémon obrigatório");
        }
        int poder;
        if ("Choque do Trovão".equals(golpe)) {
            poder = 40;
        } else if ("Lança-Chamas".equals(golpe)) {
            poder = 60;
        } else if ("Jato de Água".equals(golpe)) {
            poder = 50;
        } else {
            throw new IllegalArgumentException("Golpe desconhecido");
        }
        int dano = Math.max(0, poder - alvo.getDefesa());
        String mensagem = atacante.getNome() + " usou " + golpe
                + " contra " + alvo.getNome() + ": " + dano + " de dano.";
        eventos.add(mensagem);
        System.out.println(mensagem);
        return dano;
    }

    public int getQuantidadeEventos() {
        return eventos.size();
    }
}
```

#### Substituir `Main.java`

Copie o conteúdo completo abaixo para esse arquivo.

```java
public class Main {
    public static void main(String[] args) {
        Pokemon pikachu = new Pokemon("Pikachu", 10);
        Pokemon charmander = new Pokemon("Charmander", 15);
        Pokemon squirtle = new Pokemon("Squirtle", 20);
        BatalhaAcoplada batalha = new BatalhaAcoplada();
        batalha.atacar(pikachu, squirtle, "Choque do Trovão");
        batalha.atacar(charmander, pikachu, "Lança-Chamas");
        batalha.atacar(squirtle, charmander, "Jato de Água");
        System.out.println("Eventos: " + batalha.getQuantidadeEventos());
    }
}
```

#### Checkpoint: três golpes na versão acoplada

Na pasta do projeto, execute:

```bash
javac -encoding UTF-8 -d out *.java
java -cp out Main
```

Saída esperada:

```text
Pikachu usou Choque do Trovão contra Squirtle: 20 de dano.
Charmander usou Lança-Chamas contra Pikachu: 50 de dano.
Squirtle usou Jato de Água contra Charmander: 35 de dano.
Eventos: 3
```

### Diagnóstico antes da refatoração

**Coesão** expressa a relação entre elementos de um módulo. **Acoplamento** expressa a interdependência entre módulos. **Refatoração** reorganiza a estrutura interna preservando o comportamento observável previsto.

| Mudança solicitada | Trecho que precisaríamos editar |
|---|---|
| Novo golpe | Condicional dentro de `atacar` |
| Nova fórmula | `Math.max(...)` no mesmo método |
| Novo texto | Concatenação no mesmo método |
| Outro armazenamento | Lista e chamada `eventos.add` |
| Outro destino | `System.out.println` |

Adicionar um golpe, como acabamos de fazer, é uma extensão de funcionalidade. Na próxima parte vamos refatorar a estrutura, preservando as mensagens e os danos já obtidos.

**Preserve `BatalhaAcoplada.java` a partir deste ponto.** Ela não será mais alterada e servirá como referência de comparação. A nova versão terá o nome `Batalha`.

# Parte II — Construção incremental da versão com SOLID

## Etapa 5 — S: separar responsabilidades

### Definição e fundamento

O **Princípio da Responsabilidade Única (SRP)** orienta uma classe a reunir uma responsabilidade coesa, associada a um motivo principal para mudar. Vários métodos podem pertencer à mesma responsabilidade.

A matemática do dano, a descrição textual, o armazenamento e o destino da mensagem respondem a necessidades diferentes. Vamos extrair colaboradores para essas decisões.

### 5.1 Extrair cálculo e catálogo

O catálogo ainda usará condicionais. Primeiro separaremos responsabilidades; só depois resolveremos a extensão por golpes polimórficos. Não precisamos corrigir todos os problemas na mesma mudança.

#### Criar `CalculadoraDano.java`

Copie o conteúdo completo abaixo para esse arquivo.

```java
public class CalculadoraDano {
    public int calcular(int poder, int defesa) {
        if (poder < 0 || defesa < 0) {
            throw new IllegalArgumentException("Poder e defesa devem ser não negativos");
        }
        return Math.max(0, poder - defesa);
    }
}
```

#### Criar `CatalogoGolpes.java`

Copie o conteúdo completo abaixo para esse arquivo.

```java
public class CatalogoGolpes {
    public int obterPoder(String nome) {
        if ("Choque do Trovão".equals(nome)) return 40;
        if ("Lança-Chamas".equals(nome)) return 60;
        if ("Jato de Água".equals(nome)) return 50;
        throw new IllegalArgumentException("Golpe desconhecido");
    }
}
```

**Responsabilidades:** `CalculadoraDano` implementa a fórmula; `CatalogoGolpes` relaciona nomes aos poderes conhecidos. O catálogo ainda muda quando novos golpes aparecem.

### 5.2 Extrair apresentação, histórico e saída

O narrador recebe o nome como texto. Não depende de uma interface que ainda não foi criada.

#### Criar `NarradorBatalha.java`

Copie o conteúdo completo abaixo para esse arquivo.

```java
public class NarradorBatalha {
    public String descrever(Pokemon atacante, Pokemon alvo, String golpe, int dano) {
        return atacante.getNome() + " usou " + golpe
                + " contra " + alvo.getNome() + ": " + dano + " de dano.";
    }
}
```

#### Criar `HistoricoMemoria.java`

Copie o conteúdo completo abaixo para esse arquivo.

```java
import java.util.ArrayList;
import java.util.List;

public class HistoricoMemoria {
    private final List<String> eventos = new ArrayList<>();

    public void registrar(String evento) {
        eventos.add(evento);
    }

    public List<String> listar() {
        return new ArrayList<>(eventos);
    }
}
```

#### Criar `NotificadorConsole.java`

Copie o conteúdo completo abaixo para esse arquivo.

```java
public class NotificadorConsole {
    public void enviar(String mensagem) {
        System.out.println(mensagem);
    }
}
```

`listar` devolve uma cópia: alterar a lista retornada não modifica o estado interno do histórico. Essa proteção está ligada ao encapsulamento.

### 5.3 Construir a nova coordenação

O serviço delega as decisões extraídas. Ele ainda conhece colaboradores concretos; isso será retomado em D. O histórico é recebido no construtor para que a aplicação possa observar os mesmos eventos. Receber uma classe concreta pelo construtor ainda não demonstra inversão de dependência.

#### Criar `Batalha.java`

Copie o conteúdo completo abaixo para esse arquivo.

```java
public class Batalha {
    private final NarradorBatalha narrador = new NarradorBatalha();
    private final CatalogoGolpes catalogo = new CatalogoGolpes();
    private final CalculadoraDano calculadora = new CalculadoraDano();
    private final HistoricoMemoria historico;
    private final NotificadorConsole notificador = new NotificadorConsole();

    public Batalha(HistoricoMemoria historico) {
        if (historico == null) {
            throw new IllegalArgumentException("Histórico obrigatório");
        }
        this.historico = historico;
    }

    public int atacar(Pokemon atacante, Pokemon alvo, String golpe) {
        if (atacante == null || alvo == null || golpe == null) {
            throw new IllegalArgumentException("Pokémon e golpe obrigatórios");
        }
        int poder = catalogo.obterPoder(golpe);
        int dano = calculadora.calcular(poder, alvo.getDefesa());
        String mensagem = narrador.descrever(atacante, alvo, golpe, dano);
        historico.registrar(mensagem);
        notificador.enviar(mensagem);
        return dano;
    }
}
```

#### Substituir `Main.java`

Copie o conteúdo completo abaixo para esse arquivo.

```java
public class Main {
    public static void main(String[] args) {
        Pokemon pikachu = new Pokemon("Pikachu", 10);
        Pokemon charmander = new Pokemon("Charmander", 15);
        Pokemon squirtle = new Pokemon("Squirtle", 20);

        System.out.println("=== ORIGINAL ACOPLADA ===");
        BatalhaAcoplada original = new BatalhaAcoplada();
        original.atacar(pikachu, squirtle, "Choque do Trovão");
        original.atacar(charmander, pikachu, "Lança-Chamas");
        original.atacar(squirtle, charmander, "Jato de Água");
        System.out.println("Eventos: " + original.getQuantidadeEventos());

        System.out.println("\n=== REFATORADA ===");
        HistoricoMemoria historico = new HistoricoMemoria();
        Batalha refatorada = new Batalha(historico);
        refatorada.atacar(pikachu, squirtle, "Choque do Trovão");
        refatorada.atacar(charmander, pikachu, "Lança-Chamas");
        refatorada.atacar(squirtle, charmander, "Jato de Água");
        System.out.println("Eventos: " + historico.listar().size());
    }
}
```

#### Checkpoint: SRP com as duas versões executáveis

Na pasta do projeto, execute:

```bash
javac -encoding UTF-8 -d out *.java
java -cp out Main
```

Saída esperada:

```text
=== ORIGINAL ACOPLADA ===
Pikachu usou Choque do Trovão contra Squirtle: 20 de dano.
Charmander usou Lança-Chamas contra Pikachu: 50 de dano.
Squirtle usou Jato de Água contra Charmander: 35 de dano.
Eventos: 3

=== REFATORADA ===
Pikachu usou Choque do Trovão contra Squirtle: 20 de dano.
Charmander usou Lança-Chamas contra Pikachu: 50 de dano.
Squirtle usou Jato de Água contra Charmander: 35 de dano.
Eventos: 3
```

### Onde SRP aparece?

| Classe | Motivo principal de mudança |
|---|---|
| `CalculadoraDano` | Regra matemática |
| `CatalogoGolpes` | Relação entre nome e poder |
| `NarradorBatalha` | Apresentação do texto |
| `HistoricoMemoria` | Armazenamento dos eventos |
| `NotificadorConsole` | Forma de apresentar a notificação |
| `Batalha` | Coordenação do ataque |

**O que conferir:** original e refatorada imprimem os mesmos três ataques e registram três eventos. Coordenar várias chamadas é uma responsabilidade válida; o serviço não precisa implementar o detalhe de cada chamada.

**Miniatividade S:** qual arquivo deve mudar para acrescentar “pontos” a “20 de dano”? Resposta: `NarradorBatalha.java`. Para continuar com as saídas do tutorial, mantenha o texto original até o exercício final.

## Etapa 6 — O: substituir o catálogo por comportamentos extensíveis

### Definição e fundamento

O **Princípio Aberto/Fechado (OCP)** orienta permitir extensão de comportamento, protegendo a lógica estável das modificações recorrentes escolhidas no projeto.

Agora o ponto de variação será o golpe. A introdução da interface exige uma refatoração inicial. Depois dela, acrescentar outro golpe não exige editar a coordenação.

> **Relembre**: Uma **interface** declara operações que implementações oferecem. O **polimorfismo** permite usar o mesmo contrato com implementações diferentes.

### 6.1 Criar o contrato e os golpes existentes

O contrato já documenta garantias de comportamento. Em L, vamos verificar por que respeitá-las é essencial.

#### Criar `Golpe.java`

Copie o conteúdo completo abaixo para esse arquivo.

```java
/**
 * Golpe que causa dano.
 * getNome: nome não nulo e não vazio.
 * calcularDano: para defesa >= 0, retorna inteiro >= 0 sem exceção.
 * Para defesa < 0, lança IllegalArgumentException.
 * As operações não registram eventos nem enviam notificações.
 */
public interface Golpe {
    String getNome();
    int calcularDano(int defesa);
}
```

#### Criar `ChoqueDoTrovao.java`

Copie o conteúdo completo abaixo para esse arquivo.

```java
public class ChoqueDoTrovao implements Golpe {
    private final CalculadoraDano calculadora = new CalculadoraDano();

    @Override
    public String getNome() { return "Choque do Trovão"; }

    @Override
    public int calcularDano(int defesa) {
        return calculadora.calcular(40, defesa);
    }
}
```

#### Criar `LancaChamas.java`

Copie o conteúdo completo abaixo para esse arquivo.

```java
public class LancaChamas implements Golpe {
    private final CalculadoraDano calculadora = new CalculadoraDano();

    @Override
    public String getNome() { return "Lança-Chamas"; }

    @Override
    public int calcularDano(int defesa) {
        return calculadora.calcular(60, defesa);
    }
}
```

#### Criar `JatoDeAgua.java`

Copie o conteúdo completo abaixo para esse arquivo.

```java
public class JatoDeAgua implements Golpe {
    private final CalculadoraDano calculadora = new CalculadoraDano();

    @Override
    public String getNome() { return "Jato de Água"; }

    @Override
    public int calcularDano(int defesa) {
        return calculadora.calcular(50, defesa);
    }
}
```

Cada golpe associa seu nome ao comportamento de cálculo. A fórmula continua na calculadora. São responsabilidades complementares: definir o comportamento de um golpe e implementar a regra matemática reutilizável.

### 6.2 Alterar somente a versão refatorada

Substitua `Batalha` para receber `Golpe`, em vez de um texto. O narrador permanece igual, pois continua recebendo o nome da operação.

#### Substituir `Batalha.java`

Copie o conteúdo completo abaixo para esse arquivo.

```java
public class Batalha {
    private final NarradorBatalha narrador = new NarradorBatalha();
    private final HistoricoMemoria historico;
    private final NotificadorConsole notificador = new NotificadorConsole();

    public Batalha(HistoricoMemoria historico) {
        if (historico == null) {
            throw new IllegalArgumentException("Histórico obrigatório");
        }
        this.historico = historico;
    }

    public int atacar(Pokemon atacante, Pokemon alvo, Golpe golpe) {
        if (atacante == null || alvo == null || golpe == null) {
            throw new IllegalArgumentException("Pokémon e golpe obrigatórios");
        }
        int dano = golpe.calcularDano(alvo.getDefesa());
        String mensagem = narrador.descrever(atacante, alvo, golpe.getNome(), dano);
        historico.registrar(mensagem);
        notificador.enviar(mensagem);
        return dano;
    }
}
```

**Excluir `CatalogoGolpes.java`:** ele deixou de ser usado. Não mantenha a versão antiga desse contrato no projeto.

#### Substituir `Main.java`

Copie o conteúdo completo abaixo para esse arquivo.

```java
public class Main {
    public static void main(String[] args) {
        Pokemon pikachu = new Pokemon("Pikachu", 10);
        Pokemon charmander = new Pokemon("Charmander", 15);
        Pokemon squirtle = new Pokemon("Squirtle", 20);

        System.out.println("=== ORIGINAL ACOPLADA ===");
        BatalhaAcoplada original = new BatalhaAcoplada();
        original.atacar(pikachu, squirtle, "Choque do Trovão");
        original.atacar(charmander, pikachu, "Lança-Chamas");
        original.atacar(squirtle, charmander, "Jato de Água");
        System.out.println("Eventos: " + original.getQuantidadeEventos());

        System.out.println("\n=== REFATORADA ===");
        HistoricoMemoria historico = new HistoricoMemoria();
        Batalha refatorada = new Batalha(historico);
        refatorada.atacar(pikachu, squirtle, new ChoqueDoTrovao());
        refatorada.atacar(charmander, pikachu, new LancaChamas());
        refatorada.atacar(squirtle, charmander, new JatoDeAgua());
        System.out.println("Eventos: " + historico.listar().size());
    }
}
```

#### Checkpoint: golpes polimórficos preservando o resultado

Na pasta do projeto, execute:

```bash
javac -encoding UTF-8 -d out *.java
java -cp out Main
```

Saída esperada:

```text
=== ORIGINAL ACOPLADA ===
Pikachu usou Choque do Trovão contra Squirtle: 20 de dano.
Charmander usou Lança-Chamas contra Pikachu: 50 de dano.
Squirtle usou Jato de Água contra Charmander: 35 de dano.
Eventos: 3

=== REFATORADA ===
Pikachu usou Choque do Trovão contra Squirtle: 20 de dano.
Charmander usou Lança-Chamas contra Pikachu: 50 de dano.
Squirtle usou Jato de Água contra Charmander: 35 de dano.
Eventos: 3
```

### Onde OCP aparece?

A linha `golpe.calcularDano(alvo.getDefesa())` substituiu a escolha por condicionais na versão refatorada. A aplicação seleciona o objeto concreto ao passar, por exemplo, `new JatoDeAgua()`.

`BatalhaAcoplada` continua usando os nomes de golpes por texto. Isso é intencional: preservamos o antes e o depois para comparação.

**Miniatividade O:** para acrescentar `Investida`, com poder didático 25, crie outra implementação e selecione-a no `Main`. Não acrescente um `if` a `Batalha`. A alteração da aplicação é esperada: a escolha do comportamento continua existindo.

## Etapa 7 — L: observar uma quebra de contrato

### Definição e fundamento

O **Princípio da Substituição de Liskov (LSP)** exige que uma implementação possa substituir outra preservando as propriedades prometidas pelo contrato aos clientes.

> **Importante**: O termo cliente aqui identifica um componente consumidor, como o painel.


**Contrato comportamental** define condições de uso e garantias de uma operação. Uma implementação não deve exigir condições adicionais nem reduzir as garantias previstas. 

O contrato de `Golpe` aceita toda defesa não negativa e garante dano não negativo. Diferentes golpes podem causar danos diferentes. A propriedade compartilhada não é a igualdade dos valores.

### 7.1 Acrescentar uma implementação experimental defeituosa

Este defeito é proposital e ficará em uma demonstração separada. O fluxo principal e seus golpes corretos permanecem disponíveis.

#### Criar `GolpeExperimental.java`

Copie o conteúdo completo abaixo para esse arquivo.

```java
public class GolpeExperimental implements Golpe {
    @Override
    public String getNome() { return "Golpe experimental"; }

    @Override
    public int calcularDano(int defesa) {
        if (defesa < 0) {
            throw new IllegalArgumentException("Defesa inválida");
        }
        return 40 - defesa; // Defeito proposital: pode devolver dano negativo.
    }
}
```

#### Criar `DemoContrato.java`

Copie o conteúdo completo abaixo para esse arquivo.

```java
public class DemoContrato {
    public static void main(String[] args) {
        Golpe[] golpes = {
            new ChoqueDoTrovao(), new LancaChamas(),
            new JatoDeAgua(), new GolpeExperimental()
        };
        for (Golpe golpe : golpes) {
            System.out.println(golpe.getNome()
                    + ", defesa 100: " + golpe.calcularDano(100));
        }
    }
}
```

#### Checkpoint: violação proposital de LSP

Na pasta do projeto, execute:

```bash
javac -encoding UTF-8 -d out *.java
java -cp out DemoContrato
```

Saída esperada:

```text
Choque do Trovão, defesa 100: 0
Lança-Chamas, defesa 100: 0
Jato de Água, defesa 100: 0
Golpe experimental, defesa 100: -60
```

O código compila, mas o último retorno é -60. Uma entrada válida produziu resultado fora do contrato. O problema pertence à implementação; adicionar uma verificação de classe na batalha não restaura a substituição.

## Etapa 8 — L: corrigir e executar o mesmo cliente

Vamos corrigir a implementação, sem alterar `Golpe`, `DemoContrato` ou `Batalha`.

#### Substituir `GolpeExperimental.java`

Copie o conteúdo completo abaixo para esse arquivo.

```java
public class GolpeExperimental implements Golpe {
    private final CalculadoraDano calculadora = new CalculadoraDano();

    @Override
    public String getNome() { return "Golpe experimental"; }

    @Override
    public int calcularDano(int defesa) {
        return calculadora.calcular(40, defesa);
    }
}
```

#### Checkpoint: substituição após a correção

Na pasta do projeto, execute:

```bash
javac -encoding UTF-8 -d out *.java
java -cp out DemoContrato
```

Saída esperada:

```text
Choque do Trovão, defesa 100: 0
Lança-Chamas, defesa 100: 0
Jato de Água, defesa 100: 0
Golpe experimental, defesa 100: 0
```

### Onde LSP aparece?

O mesmo `for (Golpe golpe : golpes)` passa a receber valores adequados de todas as implementações. A calculadora preserva o retorno mínimo zero e a rejeição de defesa negativa.

Uma exceção para defesa negativa atende ao contrato. Uma exceção para defesa 100 o violaria, porque 100 pertence ao domínio permitido. Retornar zero é uma resposta válida.

`GolpeExperimental` permanece no projeto em sua forma corrigida, como demonstração do contrato, sem ser necessário ao `Main` principal.

**Miniatividade L:** suponha que um golpe passe a aceitar somente defesa de 0 a 50. Ele fortalece a condição de entrada e não atende ao contrato atual. O cliente não deve precisar descobrir essa restrição pelo tipo concreto.

## Etapa 9 — Introduzir o cliente de consulta e observar uma interface ampla

**Nova demanda:** consultar o histórico por um painel. Primeiro criaremos uma solução que funciona, mas faz os clientes dependerem de um contrato mais amplo que suas necessidades.

Esta etapa prepara a comparação de ISP. Ainda não é a solução final.

#### Criar `GestaoHistorico.java`

Copie o conteúdo completo abaixo para esse arquivo.

```java
import java.util.List;

public interface GestaoHistorico {
    void registrar(String evento);
    List<String> listar();
}
```

#### Substituir `HistoricoMemoria.java`

Copie o conteúdo completo abaixo para esse arquivo.

```java
import java.util.ArrayList;
import java.util.List;

public class HistoricoMemoria implements GestaoHistorico {
    private final List<String> eventos = new ArrayList<>();

    public void registrar(String evento) {
        eventos.add(evento);
    }

    public List<String> listar() {
        return new ArrayList<>(eventos);
    }
}
```

#### Criar `PainelHistorico.java`

Copie o conteúdo completo abaixo para esse arquivo.

```java
import java.util.List;

public class PainelHistorico {
    private final GestaoHistorico consulta;

    public PainelHistorico(GestaoHistorico consulta) {
        this.consulta = consulta;
    }

    public List<String> listarEventos() {
        return consulta.listar();
    }
}
```

#### Substituir `Batalha.java`

Copie o conteúdo completo abaixo para esse arquivo.

```java
public class Batalha {
    private final NarradorBatalha narrador = new NarradorBatalha();
    private final GestaoHistorico historico;
    private final NotificadorConsole notificador = new NotificadorConsole();

    public Batalha(GestaoHistorico historico) {
        if (historico == null) {
            throw new IllegalArgumentException("Histórico obrigatório");
        }
        this.historico = historico;
    }

    public int atacar(Pokemon atacante, Pokemon alvo, Golpe golpe) {
        if (atacante == null || alvo == null || golpe == null) {
            throw new IllegalArgumentException("Pokémon e golpe obrigatórios");
        }
        int dano = golpe.calcularDano(alvo.getDefesa());
        String mensagem = narrador.descrever(atacante, alvo, golpe.getNome(), dano);
        historico.registrar(mensagem);
        notificador.enviar(mensagem);
        return dano;
    }
}
```

#### Substituir `Main.java`

Copie o conteúdo completo abaixo para esse arquivo.

```java
public class Main {
    public static void main(String[] args) {
        Pokemon pikachu = new Pokemon("Pikachu", 10);
        Pokemon charmander = new Pokemon("Charmander", 15);
        Pokemon squirtle = new Pokemon("Squirtle", 20);

        System.out.println("=== ORIGINAL ACOPLADA ===");
        BatalhaAcoplada original = new BatalhaAcoplada();
        original.atacar(pikachu, squirtle, "Choque do Trovão");
        original.atacar(charmander, pikachu, "Lança-Chamas");
        original.atacar(squirtle, charmander, "Jato de Água");
        System.out.println("Eventos: " + original.getQuantidadeEventos());

        System.out.println("\n=== REFATORADA ===");
        HistoricoMemoria historico = new HistoricoMemoria();
        Batalha refatorada = new Batalha(historico);
        refatorada.atacar(pikachu, squirtle, new ChoqueDoTrovao());
        refatorada.atacar(charmander, pikachu, new LancaChamas());
        refatorada.atacar(squirtle, charmander, new JatoDeAgua());
        System.out.println("Eventos: " + historico.listar().size());

        PainelHistorico painel = new PainelHistorico(historico);
        System.out.println("Consulta pelo painel:");
        for (String evento : painel.listarEventos()) {
            System.out.println(evento);
        }
    }
}
```

#### Checkpoint: painel usando o contrato amplo

Na pasta do projeto, execute:

```bash
javac -encoding UTF-8 -d out *.java
java -cp out Main
```

Saída esperada:

```text
=== ORIGINAL ACOPLADA ===
Pikachu usou Choque do Trovão contra Squirtle: 20 de dano.
Charmander usou Lança-Chamas contra Pikachu: 50 de dano.
Squirtle usou Jato de Água contra Charmander: 35 de dano.
Eventos: 3

=== REFATORADA ===
Pikachu usou Choque do Trovão contra Squirtle: 20 de dano.
Charmander usou Lança-Chamas contra Pikachu: 50 de dano.
Squirtle usou Jato de Água contra Charmander: 35 de dano.
Eventos: 3
Consulta pelo painel:
Pikachu usou Choque do Trovão contra Squirtle: 20 de dano.
Charmander usou Lança-Chamas contra Pikachu: 50 de dano.
Squirtle usou Jato de Água contra Charmander: 35 de dano.
```

**Diagnóstico:** `Batalha` utiliza `registrar`, mas depende também de `listar`. O painel utiliza `listar`, mas depende também de `registrar`. Ambos funcionam e compartilham dados; agora vamos restringir as dependências aos papéis de cada cliente.

## Etapa 10 — I: segregar as interfaces do histórico

### Definição e fundamento

O **Princípio da Segregação de Interfaces (ISP)** orienta que clientes não sejam obrigados a depender de operações que não utilizam.

O termo cliente aqui identifica um componente consumidor, como o painel.

### 10.1 Criar contratos específicos

#### Criar `RegistroEvento.java`

Copie o conteúdo completo abaixo para esse arquivo.

```java
public interface RegistroEvento {
    void registrar(String evento);
}
```

#### Criar `ConsultaHistorico.java`

Copie o conteúdo completo abaixo para esse arquivo.

```java
import java.util.List;

public interface ConsultaHistorico {
    List<String> listar();
}
```

#### Substituir `HistoricoMemoria.java`

Copie o conteúdo completo abaixo para esse arquivo.

```java
import java.util.ArrayList;
import java.util.List;

public class HistoricoMemoria implements RegistroEvento, ConsultaHistorico {
    private final List<String> eventos = new ArrayList<>();

    public void registrar(String evento) {
        eventos.add(evento);
    }

    public List<String> listar() {
        return new ArrayList<>(eventos);
    }
}
```

#### Substituir `PainelHistorico.java`

Copie o conteúdo completo abaixo para esse arquivo.

```java
import java.util.List;

public class PainelHistorico {
    private final ConsultaHistorico consulta;

    public PainelHistorico(ConsultaHistorico consulta) {
        this.consulta = consulta;
    }

    public List<String> listarEventos() {
        return consulta.listar();
    }
}
```

#### Substituir `Batalha.java`

Copie o conteúdo completo abaixo para esse arquivo.

```java
public class Batalha {
    private final NarradorBatalha narrador = new NarradorBatalha();
    private final RegistroEvento historico;
    private final NotificadorConsole notificador = new NotificadorConsole();

    public Batalha(RegistroEvento historico) {
        if (historico == null) {
            throw new IllegalArgumentException("Histórico obrigatório");
        }
        this.historico = historico;
    }

    public int atacar(Pokemon atacante, Pokemon alvo, Golpe golpe) {
        if (atacante == null || alvo == null || golpe == null) {
            throw new IllegalArgumentException("Pokémon e golpe obrigatórios");
        }
        int dano = golpe.calcularDano(alvo.getDefesa());
        String mensagem = narrador.descrever(atacante, alvo, golpe.getNome(), dano);
        historico.registrar(mensagem);
        notificador.enviar(mensagem);
        return dano;
    }
}
```

**Excluir `GestaoHistorico.java`:** ele deixou de ser usado. Não mantenha a versão antiga desse contrato no projeto.

**Manter `Main.java` exatamente como está.** A mesma instância de `HistoricoMemoria` satisfaz os contratos específicos recebidos pelos clientes.

#### Checkpoint: interfaces segregadas com a mesma composição

Na pasta do projeto, execute:

```bash
javac -encoding UTF-8 -d out *.java
java -cp out Main
```

Saída esperada:

```text
=== ORIGINAL ACOPLADA ===
Pikachu usou Choque do Trovão contra Squirtle: 20 de dano.
Charmander usou Lança-Chamas contra Pikachu: 50 de dano.
Squirtle usou Jato de Água contra Charmander: 35 de dano.
Eventos: 3

=== REFATORADA ===
Pikachu usou Choque do Trovão contra Squirtle: 20 de dano.
Charmander usou Lança-Chamas contra Pikachu: 50 de dano.
Squirtle usou Jato de Água contra Charmander: 35 de dano.
Eventos: 3
Consulta pelo painel:
Pikachu usou Choque do Trovão contra Squirtle: 20 de dano.
Charmander usou Lança-Chamas contra Pikachu: 50 de dano.
Squirtle usou Jato de Água contra Charmander: 35 de dano.
```

### Onde ISP aparece?

- Campo e construtor de `Batalha`: `RegistroEvento`.
- Campo e construtor de `PainelHistorico`: `ConsultaHistorico`.
- Declaração de `HistoricoMemoria`: implementa os dois contratos.

O painel não pode chamar `registrar` por sua referência de consulta. Não é necessário criar um segundo armazenamento. A mesma instância permite que o painel veja os eventos registrados pela batalha.

A separação atende às necessidades destes clientes; ISP não exige um método por interface. `Golpe`, por exemplo, mantém duas operações coesas. Também não se trata de um mecanismo de autorização.

**Miniatividade I:** alterar a lista recebida pelo painel deveria alterar o histórico? Não: a cópia devolvida por `listar` protege o estado interno. Isso demonstra encapsulamento, complementar à segregação das interfaces.

## Etapa 11 — D: inverter a dependência de notificação

### Definição e fundamento

O **Princípio da Inversão de Dependência (DIP)** orienta que módulos de alto nível e detalhes de implementação dependam de abstrações. Os detalhes se adequam aos contratos necessários à aplicação.

A batalha já utiliza abstrações para golpe e registro. Os princípios se complementam: O e I prepararam parte da solução. Porém, a batalha ainda possui `new NotificadorConsole()` e conhece a tecnologia de saída.

**Injeção de dependência** é a técnica de fornecer uma dependência ao objeto, por exemplo pelo construtor. Sua presença isolada não comprova DIP: na etapa S, o histórico já era recebido, mas seu tipo ainda era concreto.

### 11.1 Criar o contrato e adaptar o console

#### Criar `Notificador.java`

Copie o conteúdo completo abaixo para esse arquivo.

```java
public interface Notificador {
    void enviar(String mensagem);
}
```

#### Substituir `NotificadorConsole.java`

Copie o conteúdo completo abaixo para esse arquivo.

```java
public class NotificadorConsole implements Notificador {
    @Override
    public void enviar(String mensagem) {
        System.out.println(mensagem);
    }
}
```

#### Criar `NotificadorMemoria.java`

Copie o conteúdo completo abaixo para esse arquivo.

```java
import java.util.ArrayList;
import java.util.List;

public class NotificadorMemoria implements Notificador {
    private final List<String> mensagens = new ArrayList<>();

    @Override
    public void enviar(String mensagem) {
        mensagens.add(mensagem);
    }

    public List<String> listarMensagens() {
        return new ArrayList<>(mensagens);
    }
}
```

### 11.2 Receber a abstração no construtor

A alteração está no tipo do campo e na composição. O fluxo do ataque permanece igual ao da etapa anterior.

#### Substituir `Batalha.java`

Copie o conteúdo completo abaixo para esse arquivo.

```java
public class Batalha {
    private final NarradorBatalha narrador = new NarradorBatalha();
    private final RegistroEvento historico;
    private final Notificador notificador;

    public Batalha(RegistroEvento historico, Notificador notificador) {
        if (historico == null || notificador == null) {
            throw new IllegalArgumentException("Dependências obrigatórias");
        }
        this.historico = historico;
        this.notificador = notificador;
    }

    public int atacar(Pokemon atacante, Pokemon alvo, Golpe golpe) {
        if (atacante == null || alvo == null || golpe == null) {
            throw new IllegalArgumentException("Pokémon e golpe obrigatórios");
        }
        int dano = golpe.calcularDano(alvo.getDefesa());
        String mensagem = narrador.descrever(atacante, alvo, golpe.getNome(), dano);
        historico.registrar(mensagem);
        notificador.enviar(mensagem);
        return dano;
    }
}
```

#### Substituir `Main.java`

Copie o conteúdo completo abaixo para esse arquivo.

```java
public class Main {
    public static void main(String[] args) {
        Pokemon pikachu = new Pokemon("Pikachu", 10);
        Pokemon charmander = new Pokemon("Charmander", 15);
        Pokemon squirtle = new Pokemon("Squirtle", 20);

        System.out.println("=== ORIGINAL ACOPLADA ===");
        BatalhaAcoplada original = new BatalhaAcoplada();
        original.atacar(pikachu, squirtle, "Choque do Trovão");
        original.atacar(charmander, pikachu, "Lança-Chamas");
        original.atacar(squirtle, charmander, "Jato de Água");
        System.out.println("Eventos: " + original.getQuantidadeEventos());

        System.out.println("\n=== REFATORADA ===");
        HistoricoMemoria historico = new HistoricoMemoria();
        Batalha refatorada = new Batalha(historico, new NotificadorConsole());
        refatorada.atacar(pikachu, squirtle, new ChoqueDoTrovao());
        refatorada.atacar(charmander, pikachu, new LancaChamas());
        refatorada.atacar(squirtle, charmander, new JatoDeAgua());
        System.out.println("Eventos: " + historico.listar().size());

        PainelHistorico painel = new PainelHistorico(historico);
        System.out.println("Consulta pelo painel:");
        for (String evento : painel.listarEventos()) {
            System.out.println(evento);
        }

        System.out.println("\n=== OUTRO CANAL ===");
        NotificadorMemoria canal = new NotificadorMemoria();
        Batalha outroCanal = new Batalha(historico, canal);
        outroCanal.atacar(pikachu, charmander, new ChoqueDoTrovao());
        System.out.println("Mensagens no canal: " + canal.listarMensagens().size());
        System.out.println("Eventos no histórico: " + painel.listarEventos().size());
    }
}
```

#### Checkpoint: versão final com dois canais

Na pasta do projeto, execute:

```bash
javac -encoding UTF-8 -d out *.java
java -cp out Main
```

Saída esperada:

```text
=== ORIGINAL ACOPLADA ===
Pikachu usou Choque do Trovão contra Squirtle: 20 de dano.
Charmander usou Lança-Chamas contra Pikachu: 50 de dano.
Squirtle usou Jato de Água contra Charmander: 35 de dano.
Eventos: 3

=== REFATORADA ===
Pikachu usou Choque do Trovão contra Squirtle: 20 de dano.
Charmander usou Lança-Chamas contra Pikachu: 50 de dano.
Squirtle usou Jato de Água contra Charmander: 35 de dano.
Eventos: 3
Consulta pelo painel:
Pikachu usou Choque do Trovão contra Squirtle: 20 de dano.
Charmander usou Lança-Chamas contra Pikachu: 50 de dano.
Squirtle usou Jato de Água contra Charmander: 35 de dano.

=== OUTRO CANAL ===
Mensagens no canal: 1
Eventos no histórico: 4
```

### Onde DIP aparece?

Os campos `RegistroEvento historico` e `Notificador notificador` expressam as capacidades exigidas pela batalha. O `Main` conhece as implementações e decide quais fornecer.

O narrador continua concreto. Não há exigência de criar uma interface para toda classe. Nesta evolução, escolhemos abstrair os golpes, o armazenamento e os canais, cujas variações apareceram no problema.

**Interpretação da última saída:** o canal em memória recebe uma mensagem, mas não a imprime. A batalha registra um quarto evento no mesmo histórico. O painel encontra quatro eventos porque compartilha essa instância com ambas as composições.

**Miniatividade D:** para acrescentar um canal `[ARENA]`, implemente `Notificador` e mude a composição no `Main`, preservando o corpo de `Batalha.atacar`.

# Parte III — Revisão, execução e continuidade

## Etapa 12 — Conferir o projeto final

Os arquivos listados abaixo formam a versão final. Todos foram apresentados integralmente nas etapas de criação ou substituição. `Pokemon`, `BatalhaAcoplada`, `CalculadoraDano` e `NarradorBatalha` continuam nas últimas versões publicadas; os demais seguem suas substituições mais recentes.

| Arquivo | Papel |
|---|---|
| `Pokemon.java` | Modelo de dados |
| `Main.java` | Composição e comparação das versões |
| `BatalhaAcoplada.java` | Referência original preservada |
| `CalculadoraDano.java` | Regra matemática |
| `NarradorBatalha.java` | Apresentação |
| `HistoricoMemoria.java` | Armazenamento |
| `NotificadorConsole.java` | Canal de console |
| `Batalha.java` | Coordenação refatorada |
| `Golpe.java` | Contrato dos golpes |
| `ChoqueDoTrovao.java` | Golpe de poder 40 |
| `LancaChamas.java` | Golpe de poder 60 |
| `JatoDeAgua.java` | Golpe de poder 50 |
| `GolpeExperimental.java` | Exemplo de contrato já corrigido |
| `DemoContrato.java` | Demonstração de substituição |
| `PainelHistorico.java` | Cliente de leitura |
| `RegistroEvento.java` | Contrato de escrita |
| `ConsultaHistorico.java` | Contrato de consulta |
| `Notificador.java` | Contrato de comunicação |
| `NotificadorMemoria.java` | Canal em memória |

**Arquivos excluídos durante a evolução:** `CatalogoGolpes.java` e `GestaoHistorico.java`. Não os recrie para executar a versão final.

### Executar os dois pontos de entrada

```bash
javac -encoding UTF-8 -d out *.java
java -cp out Main
java -cp out DemoContrato
```

`Main` compara original e refatorada e mostra os canais. `DemoContrato` demonstra que todos os golpes, incluindo o experimental corrigido, retornam zero para defesa 100.

Se a IDE mantiver resultados antigos depois de uma exclusão, use sua opção de limpar/recompilar o projeto. Mantenha somente os fontes correspondentes à etapa atual.

### Percurso de um ataque na versão final

| Passo | Trecho | Resultado no caso Pikachu contra Squirtle |
|---|---|---|
| 1 | Verificação de argumentos em `atacar` | Exige Pokémon e golpe não nulos |
| 2 | `alvo.getDefesa()` | Obtém 20 |
| 3 | `golpe.calcularDano(20)` | Delega ao golpe escolhido |
| 4 | `calculadora.calcular(40, 20)` | Retorna 20 |
| 5 | `narrador.descrever(...)` | Produz a mensagem |
| 6 | `historico.registrar(mensagem)` | Armazena o evento |
| 7 | `notificador.enviar(mensagem)` | Usa o canal fornecido |
| 8 | `return dano` | Devolve 20 |

A abstração muda as dependências de código sem inverter a ordem do processo. Não há transação entre registro e envio: uma falha futura no canal pode acontecer depois de o evento já ter sido armazenado.

## Síntese: o que mudou e o que foi preservado?

| Princípio | Decisão aplicada | Trecho para localizar |
|---|---|---|
| S | Separar cálculo, catálogo inicial, apresentação, armazenamento e saída | Colaboradores extraídos na etapa 5 |
| O | Substituir o catálogo condicional por comportamentos | `Golpe` e `golpe.calcularDano(...)` |
| L | Preservar entrada permitida e garantias de retorno | Correção de `GolpeExperimental` |
| I | Separar os papéis de escrita e leitura | `RegistroEvento` e `ConsultaHistorico` |
| D | Deixar a aplicação escolher o canal | Construtor de `Batalha` e composição no `Main` |

Os três ataques de referência produzem danos 20, 50 e 35 e as mesmas mensagens nas duas versões. A estrutura muda; o comportamento comparado é preservado. A consulta por painel e o segundo canal são extensões explicitamente introduzidas durante o tutorial.

Uma classe possuir uma interface não comprova, isoladamente, aplicação de SOLID. Avalie responsabilidade, ponto de variação, contrato e necessidade dos clientes. O número de classes não mede a qualidade do projeto.

## Exercício integrador

Continue a versão final:

1. Crie `Investida`, com poder didático 25, implementando `Golpe`.
2. Acrescente “pontos” à mensagem por alteração no narrador.
3. Crie `NotificadorArena`, que imprime com prefixo `[ARENA]`.
4. Crie um cliente de contagem de eventos recebendo apenas `ConsultaHistorico`.
5. No `Main`, use o novo golpe e o novo canal e compartilhe o histórico com o cliente de contagem.

**Restrições:** não alterar o corpo de `Batalha.atacar`; preservar o contrato dos golpes; não fazer o cliente de consulta depender de registro. A versão original permanece como referência.

**Critérios de aceite:** Investida contra defesa 10 retorna 15; contra defesa 100 retorna zero; defesa negativa gera `IllegalArgumentException`; o novo canal recebe a mesma descrição produzida pelo narrador; a contagem encontra o evento recém-registrado.

**Entrega sugerida:** arquivos Java e um README com comandos de execução, resultados e cinco justificativas, uma por princípio. As miniatividades anteriores são opcionais; seus resultados não foram incorporados às saídas de referência.

## Referências

- PRESSMAN, Roger S.; MAXIM, Bruce R. *Engenharia de Software: Uma Abordagem Profissional*.
- SOMMERVILLE, Ian. *Engenharia de Software*.
- MARTIN, Robert C. *Agile Software Development: Principles, Patterns, and Practices*. Prentice Hall, 2002.
- LISKOV, Barbara H.; WING, Jeannette M. A Behavioral Notion of Subtyping. *ACM Transactions on Programming Languages and Systems*, v. 16, n. 6, p. 1811–1841, 1994.
