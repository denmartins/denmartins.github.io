---
title: "Prática: Linha de Comando"
collection: labs
type: "Lab"
permalink: /labs/cmdline
date: 2026-08-07
location: "Ribeirão Preto, Brazil"
---

Nesta atividade, você atuará como um detetive digital, utilizando comandos de terminal no Linux para investigar um assassinato na cidade fictícia de "Terminal City". Seu desafio será seguir as pistas disponíveis nos arquivos do jogo *Command Line Murders* e identificar o culpado.

## O Jogo
*   ***Command Line Murders*** é um jogo interativo onde os jogadores resolvem um mistério de assassinato utilizando apenas comandos de terminal.
*   Criado por Noah Veltman, disponível no GitHub: [https://github.com/veltman/clmystery](https://github.com/veltman/clmystery).

### Objetivo do Jogo
*   Investigar um assassinato em "Terminal City" analisando arquivos de texto.
*   Utilizar comandos de terminal como `grep`, `cat`, `head` e `tail` para encontrar pistas.
*   Identificar o culpado com base nas evidências encontradas.

### Por que jogar?
*   Excelente para aprimorar habilidades no uso do terminal Linux.
*   Jogo divertido para desenvolver pensamento lógico e análise de dados.


## Como Começar a Investigação

1.  **Download do Jogo:**
    *   Faça o download do jogo em [https://github.com/veltman/clmystery/archive/master.zip](https://github.com/veltman/clmystery/archive/master.zip).
    *   Ou acesse o terminal Linux e clone o repositório do jogo:

    ```bash
    git clone https://github.com/veltman/clmystery.git
    cd clmystery
    ```

2.  **Leia o README:** Leia atentamente o arquivo [README](https://github.com/veltman/clmystery/blob/master/README.md).

*   Leia as instruções disponíveis no arquivo de texto:
    ```bash
    cat instructions
    ```
*   O arquivo [cheatsheet](https://github.com/veltman/clmystery/blob/master/cheatsheet.md) inclui informações essenciais para o início do jogo.

*   Utilize comandos de terminal para explorar os arquivos disponíveis e encontrar pistas sobre o crime.
*   Alguns comandos úteis incluem:

    ```bash
    ls -R        # Lista todos os arquivos e diretórios
    cat           # Exibe o conteúdo de arquivos
    grep          # Busca palavras-chave em arquivos
    head/tail     # Mostra as primeiras/últimas linhas de um arquivo
    ```


**Boa investigação, detetive!**