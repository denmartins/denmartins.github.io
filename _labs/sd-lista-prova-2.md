---
title: "Sistemas Distribuídos - Lista de Preparação para Prova 2"
collection: labs
type: "Lab"
permalink: /labs/sd-lista-prova-2.md
date: 2026-06-27
location: "Ribeirão Preto, Brazil"
---

## Questão 1 

Em sistemas distribuídos, a criptografia é utilizada para proteger mensagens trocadas entre entidades. Sobre criptografia simétrica e assimétrica, assinale a alternativa correta.

- (A) Na criptografia simétrica, cada entidade possui uma chave pública e uma chave privada.
- (B) Na criptografia assimétrica, a mesma chave é usada para criptografar e decriptografar mensagens.
- (C) A criptografia simétrica exige que as partes compartilhem previamente uma mesma chave secreta.
- (D) A criptografia assimétrica elimina completamente a necessidade de autenticação entre as partes.
- (E) Funções de hash são usadas para decriptografar mensagens criptografadas.

## Questão 2 

Considere um sistema distribuído com `N` entidades que utilizam autenticação baseada em chaves secretas compartilhadas. Para que qualquer par de entidades possa se autenticar diretamente, cada par precisa compartilhar uma chave exclusiva.

Avalie as afirmações a seguir.

- I. O número total de chaves secretas necessárias no sistema é dado por `N(N - 1)/2`.
- II. Cada entidade precisa armazenar `N - 1` chaves secretas.
- III. O uso de um Centro de Distribuição de Chaves, ou KDC, elimina a necessidade de qualquer chave secreta no sistema.
- IV. O KDC melhora a escalabilidade porque cada entidade precisa compartilhar uma chave apenas com o KDC.

É correto apenas o que se afirma em:

- (A) I e II.
- (B) II e III.
- (C) III e IV.
- (D) I, II e IV.
- (E) I, III e IV.


## Questão 3 

Julgue as afirmações a seguir como verdadeiras ou falsas.

- I. Uma função de hash criptográfica recebe uma entrada de tamanho variável e produz uma saída de tamanho fixo.
- II. Uma função de hash segura deve permitir recuperar facilmente a mensagem original a partir do resumo.
- III. Uma propriedade desejável de uma função de hash é dificultar a obtenção de duas mensagens diferentes com o mesmo valor de hash.
- IV. Funções de hash podem ser usadas para apoiar mecanismos de integridade de dados.

Assinale a alternativa correta.

- (A) V, V, F, F
- (B) F, V, V, F
- (C) V, F, F, V
- (D) F, F, V, V
- (E) V, F, V, V


## Questão 4 

Considere o seguinte protocolo simplificado de autenticação entre duas entidades, A e B:

1. A envia sua identidade para B.
2. B envia um desafio aleatório para A.
3. A criptografa o desafio com uma chave secreta compartilhada e envia a resposta para B.
4. B verifica a resposta e, se estiver correta, aceita a identidade de A.

Sobre esse protocolo, assinale a alternativa correta.

- (A) O protocolo é vulnerável porque a identidade de A é enviada em texto claro, tornando impossível qualquer autenticação.
- (B) O protocolo usa o princípio de desafio-resposta para reduzir o risco de que uma senha seja capturada diretamente na rede.
- (C) O protocolo é equivalente ao uso de criptografia assimétrica, pois utiliza duas chaves diferentes.
- (D) O protocolo não depende de segredo compartilhado entre A e B.
- (E) O protocolo impede todos os ataques possíveis, inclusive ataques de reflexão e ataques de repetição em qualquer cenário.


## Questão 5 

Explique por que a criação de um canal seguro em sistemas distribuídos depende tanto de criptografia quanto de autenticação. Em sua resposta, aborde:

-  a diferença entre confidencialidade e autenticação;
-  o papel das chaves criptográficas;
-  o problema de escalabilidade no gerenciamento de chaves secretas compartilhadas;
-  como KDCs ou chaves públicas podem ajudar nesse processo.


## Questão 6

Uma empresa de comércio eletrônico mantém réplicas de seu banco de dados em três regiões geográficas: América do Sul, Europa e Ásia. Durante uma falha de comunicação entre as regiões, os usuários continuam acessando o sistema e realizando compras. A equipe técnica precisa decidir se mantém todas as regiões aceitando novas compras ou se bloqueia temporariamente algumas operações até que a comunicação seja restabelecida.

Com base no **Teorema CAP**, avalie as afirmativas a seguir.

- I. Em caso de partição de rede, se o sistema continuar aceitando escritas em todas as regiões, ele prioriza disponibilidade e tolerância a partições, mas pode comprometer a consistência forte temporariamente.
- II. Em caso de partição de rede, se o sistema bloquear escritas em algumas regiões para evitar divergência entre réplicas, ele prioriza consistência forte e tolerância a partições, sacrificando disponibilidade.
- III. O Teorema CAP afirma que sistemas distribuídos não podem oferecer consistência, disponibilidade e tolerância a partições simultaneamente, mesmo em condições normais sem falha de rede.
- IV. A consistência eventual pode permitir que réplicas fiquem temporariamente diferentes, desde que o sistema possua mecanismos para convergir posteriormente para um estado consistente.
- V. A tolerância a partições pode ser descartada em sistemas distribuídos globais, pois falhas de rede são eventos raros e não precisam ser consideradas no projeto.

É correto apenas o que se afirma em:

- (A) I, II e IV.
- (B) I, III e V.
- (C) II, III e IV.
- (D) I, II, IV e V.
- (E) I, II, III, IV e V.

## Questão 7

Explique como um sistema distribuído pode garantir o término consistente de uma transação distribuída.

Em sua resposta, discuta o papel de mecanismos de coordenação entre os participantes da transação, como protocolos de comprometimento distribuído, e explique por que todos os participantes devem chegar a uma decisão global consistente de commit ou abort.

## Questão 8

Em um ambiente ACID, um protocolo clássico de controle de concorrência é o Two-Phase Locking (2PL).

Explique como o protocolo 2PL funciona, descrevendo suas duas fases principais. Em seguida, apresente um exemplo curto envolvendo duas transações concorrentes acessando o mesmo item de dado, mostrando como o uso de bloqueios pode evitar inconsistências.


## Questão 9

Apresente exemplos de aplicações nas quais o modelo ACID é preferível ao modelo BASE, e exemplos de aplicações nas quais o modelo BASE é mais adequado que o modelo ACID.

Em sua resposta, explique por que cada modelo é mais apropriado para os exemplos escolhidos, considerando aspectos como consistência, disponibilidade, desempenho, escalabilidade e tolerância a falhas.


## Questão 10

Um sistema de gerenciamento de dados possui duas cargas de trabalho distintas. A primeira é composta majoritariamente por consultas de leitura, com poucas atualizações sobre os mesmos registros. A segunda envolve muitas transações concorrentes tentando atualizar os mesmos itens de estoque em horários de pico.

Com base em **controle de concorrência otimista e pessimista**, avalie as afirmativas a seguir.

- I. O controle pessimista tende a ser mais adequado quando há alta probabilidade de conflitos, pois bloqueia recursos antes que operações conflitantes ocorram.
- II. O controle otimista tende a ser mais adequado quando conflitos são raros, pois permite que transações avancem sem bloqueios longos e verifica conflitos posteriormente.
- III. No controle otimista, uma transação nunca precisa ser abortada, pois conflitos são prevenidos antes da execução das operações.
- IV. No controle pessimista, o uso de bloqueios pode reduzir a concorrência e introduzir risco de deadlocks.
- V. No controle otimista, conflitos podem ser detectados na fase de validação, o que pode levar ao abort e reinício de transações que já executaram parte de seu trabalho.

É correto apenas o que se afirma em:

- (A) I, II, IV e V.
- (B) I, II e III.
- (C) II, III e IV.
- (D) I, III, IV e V.
- (E) I, II, III, IV e V.

## Questão 11

Considere um sistema distribuído com três processos, **P1**, **P2** e **P3**, localizados em três sites diferentes. A exclusão mútua é implementada usando o algoritmo de **Ricart-Agrawala**.

Considere o seguinte cenário:

* **P1** e **P2** solicitam a entrada na seção crítica.
* **P3** não deseja entrar na seção crítica nesse momento.
* O timestamp da requisição de **P1** é `47`.
* O timestamp da requisição de **P2** é `32`.

Liste, em detalhes, todos os eventos que ocorrem até que ambos os processos concluam suas seções críticas.

Em sua resposta, explique:

* quais mensagens de requisição são enviadas;
* quais respostas são concedidas imediatamente;
* quais respostas são adiadas;
* qual processo entra primeiro na seção crítica;
* quando o segundo processo recebe permissão para entrar;
* como os timestamps determinam a prioridade entre P1 e P2.

## Questão 12

Um servidor gerencia os objetos `a1`, `a2`,... `an`. O servidor fornece duas operações para seus clientes:
- `read(i)` retorna o valor de `ai`;
- `write(i, value)` atribui `value` a `ai`.

As transações `T` e `U` são definidas como segue:

```text
T: x = read(j); y = read (i); write(j, 44); write(i, 33);

U: x = read(k); write(i, 55); y = read(j); write(k, 66);
```

Forneça três interposições serialmente equivalentes das transações `T` e `U`.

## Questão 13

Elabore um protocolo de autenticação simples que usa assinaturas em um sistema criptográfico de chaves públicas.


## Questão 14

Por que não é recomendado implementar um **nonce** como um timestamp?

## Questão 15

Considere a figura que introduz o KDC no slide 22 da aula 13b (<a href="https://denmartins.github.io/files/lectures/distributedsystems/13b-SD-Seguranca.pdf" target="_blank">Segurança - Parte 2</a>). Explique o motivo pelo qual não é necessário ao KDC saber com certeza que está falando com Alice quando ele recebe a requisição de uma chave secreta que Alice pode compartilhar com Bob?

