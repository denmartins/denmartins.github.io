---
title: "Lab Prático: Estruturas de Controle em Linguagem C"
collection: labs
type: "Lab"
permalink: /labs/estruturas-de-controle-C
date: 2026-05-05
location: "Ribeirão Preto, Brazil"
---

**Estruturas de Controle** são mecanismos pelos quais determinamos e orquestramos o fluxo de execução do programa em função de condições lógicas ou repetição iterativa. 

É imperativo que se compreenda como a lógica condicional (`if-else`, `switch`) e os mecanismos de iteração (`for`, `while`, `do-while`) devem ser empregados para modelar processos computacionais complexos da maneira robusta.

## Objetivo

Ao final deste laboratório, você será capaz de:
1.  Implementar lógica condicional (`if`, `else if`, `else`) para tomar decisões no programa.
2.  Utilizar estruturas de repetição (`for`, `while`, `do-while`) para automatizar tarefas repetitivas.
3.  Combinar diferentes estruturas de controle (condicionais e laços) em um único fluxo lógico complexo, simulando o comportamento de sistemas reais.

## Fase I
*(Foco: `if`, `else if`, `else`)*

**Objetivo:** Simular sistemas de validação que dependem de regras e condições específicas.

### Exercício 1.1: Verificador de Idade Legal
Crie um programa que receba a idade do usuário (um inteiro). O programa deve imprimir mensagens diferentes baseadas na idade, seguindo estas regras:
1.  Se a idade for menor que 0: Imprimir "Erro! Idade inválida."
2.  Se a idade estiver entre 0 e 17 anos: Imprimir "Menor de idade. Acesso restrito."
3.  Se a idade estiver entre 18 e 64 anos: Imprimir "Idade adulta. Acesso liberado."
4.  Se a idade for maior que 64 anos: Imprimir "Aposentado(a). Descontos especiais aplicáveis."

> **Ponto de Atenção:** Lembre-se da ordem das suas condições. O uso correto do `else if` garante que apenas um bloco de código seja executado.

### Exercício 1.2: Classificador de Paridade e Sinal
Crie um programa que receba um número inteiro $N$. O programa deve determinar duas coisas e imprimir as mensagens correspondentes:
1.  Se o número é par ou ímpar (Use o operador `%`).
2.  Se o número é positivo, negativo ou zero.

> **Dica:** Você precisará aninhar (ou encadear) suas condições para cobrir todos os cenários possíveis de um único número.

## Fase II
*(Foco: `for`, `while`, `do-while`)*

**Objetivo:** Entender como e quando usar diferentes tipos de laços para executar blocos de código sem reescrever o mesmo comando.

### Exercício 2.1: Contagem Regressiva com `for`
Escreva um programa que realize uma contagem regressiva do número 10 até 1, imprimindo "Contando... [Número]" em cada passo. Após chegar a 1, ele deve imprimir "Decolagem!".

> **Revisão Teórica:** O laço `for` é ideal quando você sabe *exatamente* quantas vezes o loop precisa rodar (iterações definidas).

### Exercício 2.2: Soma Acumulada com `while`
Crie um programa que peça ao usuário para digitar números inteiros, um por vez. O programa deve continuar pedindo entradas **enquanto** o número digitado for diferente de zero (0). Ao digitar 0, ele deve parar e imprimir a soma total de todos os números positivos digitados anteriormente.

> **Ponto de Atenção:** Este Exercício exige que você use uma variável acumuladora (ex: `soma`) inicializada em zero, fora do laço. O laço `while` é perfeito para situações onde o número de repetições *não* é conhecido antecipadamente.

### Exercício 2.3: Garantindo a Execução com `do-while`
Implemente um sistema simples de senha. Use o `do-while` para garantir que, **pelo menos uma vez**, o programa solicite a senha ao usuário e verifique se ela está correta (exemplo de senha: "1234").

> **Revisão Teórica:** O laço `do-while` executa o bloco de código *primeiro* (`do`) e só verifica a condição no final (`while`). É ideal para menus ou solicitações onde a ação deve ocorrer antes da verificação.


## Fase III
*(Foco: `switch-case` e Integração)*

**Objetivo:** Gerenciar múltiplos estados de forma limpa e combinar diferentes estruturas em um único sistema funcional.

### Exercício 3.1: Menu Interativo com `switch-case`
Crie um programa que simule um pequeno menu de serviços (como uma caixa eletrônica simplificada). O usuário deve digitar um código de serviço (exemplo: 1, 2 ou 3). Use a estrutura `switch-case` para processar o pedido.

**Requisitos:**
*   Caso 1: Consultar Saldo. Peça um valor e imprima "Saldo consultado com sucesso."
*   Caso 2: Saque. Peça um valor e verifique se ele é positivo. Se for, imprima "Saque realizado." Caso contrário, use o `default` para avisar que o valor é inválido.
*   Caso 3: Ajuda. Imprimir uma mensagem de boas-vindas.
*   Qualquer outro número digitado deve cair no bloco `default`.

> Quando você tem um único tipo de variável (como um inteiro) e precisa testá-lo contra vários valores discretos, o `switch` é mais legível e eficiente que longas cadeias de `if-else if`.

### Exercício 3.2: Jogo Simples
Crie um programa que simule a jogada de um dado virtual (número entre 1 e 6). Este programa deve combinar todas as estruturas aprendidas:

1.  **Geração:** Use `rand()` para gerar o número aleatório (simulando o lançamento do dado). *Lembre-se de incluir `<stdlib.h>` e usar `srand(time(NULL))` no início.*
2.  **Decisão (`if`/`else if`):** Verifique se o número gerado é um número primo (números primos são 2, 3, 5). Se for, imprima "Excelente jogada! Número Primo detectado." Caso contrário, continue.
3.  **Repetição (`while` ou `do-while`):** Peça ao usuário para tentar adivinhar o número sorteado (o dado). Use um laço de repetição que só pare quando a tentativa for igual ao número do dado OU após 5 tentativas.


## Fase IV
*(Foco: Controle avançado de laços (`break`, `continue`) e lógica aninhada)*

**Objetivo:** Aplicar o raciocínio computacional para resolver problemas que exigem controle preciso do fluxo de execução, simulando a robustez necessária em sistemas reais.

### Exercício 4.1: Validação de Entrada
Em um sistema real, o usuário pode digitar dados inválidos (letras onde se espera números, ou valores fora do intervalo permitido). Você deve criar um programa que solicita ao usuário que insira uma idade válida.

**Requisitos:**
1.  Use um laço `do-while` para garantir que a solicitação seja feita pelo menos uma vez.
2.  Dentro do laço, você deve verificar se o valor digitado é realmente um número inteiro (simule esta verificação com lógica de tipo ou validação de faixa).
3.  Se o usuário digitar um valor negativo OU um valor maior que 150, o programa **NÃO** deve processar esse dado e deve pular imediatamente para a próxima iteração do laço, solicitando o número novamente. Use o comando `continue` para isso.
4.  O laço só deve terminar quando for fornecido um valor entre 0 e 150 (inclusive).

> **Dica**: Pense no `do-while` como uma "garantia". Você *tem* que pedir a informação pelo menos uma vez. O `continue` é o seu mecanismo de "descarte" de dados inválidos, permitindo que o loop avance sem processar o erro.

### Exercício 4.2: Simulador de Quiz
Crie um mini-quiz que consiste em três perguntas de múltipla escolha (simuladas por números). O programa deve guiar o usuário através das perguntas e, ao final, calcular a pontuação total.

**Requisitos:**
1.  Use um laço `for` para iterar exatamente 3 vezes (uma vez para cada pergunta).
2.  Dentro do loop, peça uma resposta e verifique se ela é correta (Exemplo: P1=2, P2=1, P3=3). Se estiver certa, incremente a pontuação; caso contrário, não faça nada.
3.  Após o término do laço, use uma série de estruturas `if-else if-else` aninhadas para determinar e imprimir um **nível de proficiência** com base na pontuação final:
    *   0 pontos: "Iniciante. Sugerimos revisar os fundamentos."
    *   1 ponto: "Básico. Bom começo, mas há espaço para crescimento."
    *   2 pontos: "Intermediário. Demonstra bom domínio do conteúdo."
    *   3 pontos: "Mestre! Seu raciocínio lógico é impecável."

> **Dica**: A variável de pontuação deve ser inicializada em zero *antes* do laço (`for`). O `if/else if` final não pode depender apenas da contagem de perguntas, mas sim do valor acumulado na variável de pontuação.
