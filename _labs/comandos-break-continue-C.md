---
title: "Exercícios Práticos: Uso de `break` e `continue` em loops"
collection: labs
type: "Lab"
permalink: /labs/comandos-break-continue-C
date: 2026-05-14
location: "Ribeirão Preto, Brazil"
---

Nos exercícios a seguir, vamos utilizar os comandos `break` e `continue`. Revise o papel desses comandos:

**`break`:**

*   **Função:** Interrompe *imediatamente* a execução do loop mais interno ao qual pertence.
*   **Efeito:** O controle salta para o código que vem logo após o bloco `switch` ou `for`/`while`.

**`continue`:**
*   **Função:** Pula a execução do restante do código dentro da iteração atual e passa diretamente para a próxima iteração (ou seja, executa o incremento/decremento e verifica a condição novamente).
*   **Efeito:** O loop continua rodando, mas ignora o processamento específico daquela volta.

## Exercício P1: Impressão Condicional
 Escreva um programa que utilize um loop `for` para iterar sobre os números de 1 a 20. Utilize o comando `continue` para garantir que apenas os **números ímpares** sejam impressos na tela.

## Exercício P2: Soma até Condição
Escreva um programa que utilize um loop `while` para somar números inteiros positivos. A soma deve parar *assim que* o número lido for zero ou negativo. Use a estrutura do loop e demonstre como o controle de fluxo é gerenciado pela condição de parada, sem precisar de um contador externo complexo.

## Exercício P3: Menu de Opções com Loop Infinito Controlado
Crie um programa que simule um menu interativo (ex: 1-Opção A, 2-Opção B, 3-Sair). Use um loop `do-while` ou `while(1)` para manter o menu ativo. Quando o usuário escolher a opção "Sair", utilize o comando `break` para encerrar completamente o loop e finalizar o programa de forma limpa.

## Exercício P4: Detecção de Sequência Máxima
Escreva um programa que leia uma sequência de números inteiros até encontrar um valor negativo (este valor negativo será o sinal de parada). O objetivo é contar quantos números consecutivos *positivos* existem na sequência. Se um número for zero, ele deve ser ignorado (`continue`). Se a contagem de positivos atingir 5, você deve parar imediatamente e reportar que a sequência foi interrompida por limite máximo (`break`).

Dicas:
1.  Loop principal `while` (para leitura).
2.  Uso de `continue` para pular zeros.
3.  Um contador interno para positivos.
4.  Verificação do limite de 5, acionando o `break`.