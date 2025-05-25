---
title: "Sistemas Computacionais"
collection: teaching
type: "Undergraduate Program"
permalink: /teaching/2025-sistemas-computacionais
venue: "Pontifícia Universidade Católica de Campinas, Ciência de Dados e Inteligência Artificial"
date: 2025-10-02
location: "Campinas, Brazil"
---

O curso de Sistemas Computacionais tem como objetivo desenvolver a capacidade de idealizar e prototipar sistemas computacionais em diferentes níveis de abstração. 


# Objetivos de aprendizagem

- Entender e construir os componentes de um computador moderno.
- Explicar e escrever programas em linguagem assembly.
- Estudar e entender componentes e técnicas de gerenciamento de sistemas operacionais modernos.


# Bibliografia
 
 - NISAN, N.; SCHOCKEN, S.; The Elements of Computing Systems, Building a Modern Computer from First Principles, 2nd ed., MIT, 2005.
 - TOCCI, R.J.; WIDMER, N.S.; MOSS, G.; Sistemas digitais: princípios e aplicações, 12ª Ed., Pearson, 2019.
 - TANENBAUM, A.; Sistemas Operacionais Modernos. 4a ed. Pearson Brasil, 2010.  
 

# Slides de aula

- [Visão Geral do Curso](https://denmartins.github.io/files/lectures/01-SC-VisaoGeral.pdf)
- [Introdução à Linguagem de Montagem](https://denmartins.github.io/files/lectures/SC-Intro-Assembly.pdf)
- [Introdução aos Sistemas Operacionais](https://denmartins.github.io/files/lectures/03-SC-OS-Intro.pdf)
- [Multitarefa: Processos e Threads](https://denmartins.github.io/files/lectures/04-SC-OS-Multitarefa.pdf). Versão em [html](https://denmartins.github.io/files/lectures/04-SC-OS-Multitarefa.html)
- [Sincronização de Processos e Threads](https://denmartins.github.io/files/lectures/05-SC-OS-Sincronizacao.pdf)
- [Hierarquia de Memória](https://denmartins.github.io/files/lectures/06-SC-OS-Hierarquia-Memoria.pdf)


# Projeto Minishell

Uma aplicação shell é um interpretador de linguagem de comando que fornece uma interface de usuário baseada em texto para sistemas operacionais.

Para esta tarefa, você construirá uma aplicação shell semelhante a Bash com funcionalidades mínimas, como percorrer o sistema de arquivos e executar aplicações.

**Conceitos envolvidos**

* Programação em Python
* Chamadas de Sistema
* Criação e gerenciamento de processos

**Funcionalidades**

* Receber comandos, em um laço infinito.
* Interpretar e executar cada comando em um processo filho.
* Redirecionamento de saída: A saída dos comandos poderá ser redirecionada para um arquivo: `cat arquivo.txt > arquivo-saída`
* Comandos em paralelo: Vários comandos separados por um `&` deverão ser executados de forma concorrente, em processos separados: `cmd1 & cmd2 arg1 arg2 & cmd3 arg`
* Comandos em sequência: Vários comandos separados pelo operador `;` deverão ser executados em sequência, um após o outro. Exemplo: `cmd1; cmd2` deve garantir que o comando `cmd2` só será executado quando `cmd1` finalizar sua execução.

**Comandos internos**

* `exit` : Finaliza o Shell.
* `pwd` : Exibir o caminho do diretório atual.
* `cd <caminho>` : Muda o diretório de trabalho.
    > **AVISO:** Usar o comando `cd` sem argumentos ou com mais de um argumento não afeta o caminho do diretório atual. Certifique-se de tratar este caso limite de forma que evite travamentos (crashes).
* `cat <arquivo>` Lê o conteúdo do arquivo no argumento e o escreve na saída padrão.
* `ls`: Lista o conteúdo do diretório atual.
* `echo <texto>`: Imprime um texto na tela.

Exemplo: 

```bash
> pwd
/home/student
> cd operating-systems/assignments/
> pwd
/home/student/operating-systems/assignments/
> cd inexitent
no such file or directory
> cd /usr/lib
> pwd
/usr/lib
> echo "Hello"
Hello
> exit
```

**Tratamento de erro**: A aplicação deve tratar condições de erro e imprimir na tela mensagens amigáveis para elas.

**Argumentos**: Você pode assumir que argumentos de comandos são separados por espaços (um ou mais). Não é preciso se preocupar com caracteres de escape ou argumentos com espaços entre aspas.

**Entrega**: Código completo (.py) e instruções de uso (README).