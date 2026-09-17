---
title: "Engenharia de Software: Análise de Pontos de Função (APF/IFPUG)"
collection: labs
type: "Lab"
permalink: /labs/apf
date: 2026-09-17
location: "Ribeirão Preto, Brazil"
---

Neste tutorial simplificado, você aprenderá a realizar uma **contagem de Pontos de Função utilizando a abordagem IFPUG**, partindo dos requisitos funcionais de um sistema.

Ao final da atividade, você deverá ser capaz de:

1. identificar a **fronteira da aplicação**;
2. diferenciar **funções de dados** e **funções transacionais**;
3. classificar funções como **ALI, AIE, EE, SE ou CE**;
4. utilizar **DET, RET e FTR** para determinar a complexidade funcional;
5. calcular o **tamanho funcional em Pontos de Função**;
6. utilizar o tamanho funcional para estimar esforço e custo.

---

# 1. Antes de começar: o que são Pontos de Função?

Pontos de Função medem o **tamanho funcional do software**, isto é, o tamanho das funcionalidades que o software fornece aos seus usuários.

A ideia central é:

> **medir o que o software faz, e não como ele foi implementado.**

Assim, a contagem não depende diretamente de:

* linguagem de programação;
* framework;
* quantidade de linhas de código;
* banco de dados utilizado;
* arquitetura física da solução.

Na Engenharia de Software, Pressman & Maxim apresentam Pontos de Função como uma alternativa para dimensionamento utilizada na estimativa de projetos. Neste tutorial, as regras operacionais seguem a abordagem da **IFPUG — International Function Point Users Group**.

A IFPUG trabalha com cinco tipos principais de funções:

| Funções de Dados                   | Funções Transacionais |
| ---------------------------------- | --------------------- |
| ALI — Arquivo Lógico Interno       | EE — Entrada Externa  |
| AIE — Arquivo de Interface Externa | SE — Saída Externa    |
|                                    | CE — Consulta Externa |

---

# 2. O primeiro conceito: fronteira da aplicação

Antes de contar qualquer função, precisamos decidir:

> **O que pertence ao sistema que estamos medindo?**

A **fronteira da aplicação** separa o software analisado de seus usuários e de outras aplicações.

## Fronteira utilizada neste tutorial

Estamos dimensionando somente o:

> **Módulo do Aplicativo do Restaurante Universitário — RU**

Estão **dentro da fronteira**:

* cadastro e consulta de cardápios;
* conta e saldo do estudante;
* transações de créditos;
* avaliações das refeições.

Estão **fora da fronteira**:

* Sistema da Secretaria Acadêmica;
* Sistema Central de Infraestrutura da Universidade;
* serviço externo de pagamentos PIX/cartão;
* serviço externo de envio de e-mails.

### Por que isso importa?

Considere a Base de Matrículas.

O aplicativo do RU consulta essa base, mas quem a mantém é a Secretaria Acadêmica.

Portanto:

> os dados são utilizados pelo RU, mas pertencem funcionalmente a outra aplicação.

Essa informação será importante para decidir se temos um **ALI ou AIE**.

---

# 3. Funções de dados: ALI e AIE

Funções de dados representam grupos lógicos de informações reconhecíveis pelo usuário.

## ALI — Arquivo Lógico Interno

Um **ALI** é um grupo lógico de dados:

* reconhecido pelo usuário;
* localizado dentro da fronteira considerada;
* **mantido pela própria aplicação**.

### Regra prática

Pergunte:

> **O sistema que estou medindo é responsável por incluir, alterar ou excluir esses dados?**

Se sim, provavelmente estamos diante de um **ALI**.

### Exemplo

O aplicativo do RU mantém seu próprio cardápio semanal.

Logo:

> **Cardápio = candidato a ALI**

---

## AIE — Arquivo de Interface Externa

Um **AIE** também é um grupo lógico de dados reconhecível pelo usuário.

A diferença é que:

> o sistema consulta os dados, mas **outra aplicação é responsável por mantê-los**.

### Regra prática

Pergunte:

> **O meu sistema usa esses dados, mas eles são mantidos por outro sistema?**

Se sim, provavelmente estamos diante de um **AIE**.

### Exemplo

O RU consulta a situação de matrícula do aluno, mas quem mantém essas informações é o Sistema Acadêmico.

Logo:

> **Base de Matrículas = candidata a AIE**

---

# 4. Como medir a complexidade de ALI e AIE?

Depois de identificar uma função de dados, precisamos analisar dois elementos:

# DET e RET

---

## DET — Data Element Type

Um **DET** é, de forma simplificada, um campo de informação:

* único;
* reconhecível pelo usuário;
* relevante para a função analisada.

### Exemplo

Considere um cadastro de aluno contendo:

| Campo     |
| --------- |
| Matrícula |
| Nome      |
| Curso     |
| Situação  |
| E-mail    |

Nesse exemplo simplificado:

> **DET = 5**

Não devemos contar campos puramente técnicos que não sejam reconhecidos funcionalmente pelo usuário.

---

## RET — Record Element Type

Um **RET** representa um **subgrupo lógico de dados reconhecível pelo usuário dentro de um ALI ou AIE**.

Imagine um arquivo lógico chamado **Pedido** contendo:

* dados gerais do pedido;
* itens do pedido.

Temos dois grupos lógicos relacionados dentro da mesma função de dados.

Logo:

> **RET = 2**

Se não houver subgrupos identificáveis:

> considere **1 RET**.

---

# 5. Matriz de complexidade — ALI e AIE

Depois de encontrar DET e RET, utilize:

| RET \ DET         | 1–19 DET | 20–50 DET | 51 ou mais DET |
| ----------------- | -------- | --------- | -------------- |
| **1 RET**         | Baixa    | Baixa     | Média          |
| **2–5 RET**       | Baixa    | Média     | Alta           |
| **6 ou mais RET** | Média    | Alta      | Alta           |

Depois determine os PF:

| Tipo    | Baixa | Média | Alta |
| ------- | ----: | ----: | ---: |
| **ALI** |     7 |    10 |   15 |
| **AIE** |     5 |     7 |   10 |

---

# 6. Sua vez — identifique as funções de dados do RU

Analise os grupos de dados abaixo.

### D1 — Cardápio Semanal

O aplicativo do RU mantém os pratos oferecidos durante a semana.

A análise dos requisitos identificou:

* **12 DET**
* **2 RET**

Perguntas:

1. Quem mantém esses dados?
2. Trata-se de ALI ou AIE?
3. Qual é sua complexidade?
4. Quantos PF representa?

---

### D2 — Conta e Transações do Estudante

O aplicativo mantém saldo, créditos adicionados e movimentações decorrentes das refeições.

Foram identificados:

* **26 DET**
* **3 RET**

Classifique:

| Item             | Resposta |
| ---------------- | -------- |
| Tipo             |          |
| Complexidade     |          |
| Pontos de Função |          |

---

### D3 — Avaliações das Refeições

O aplicativo mantém as avaliações e comentários enviados pelos estudantes.

Foram identificados:

* **10 DET**
* **1 RET**

Classifique:

| Item             | Resposta |
| ---------------- | -------- |
| Tipo             |          |
| Complexidade     |          |
| Pontos de Função |          |

---

### D4 — Matrículas e Vínculos

Os dados pertencem ao Sistema da Secretaria Acadêmica. O aplicativo do RU apenas consulta essas informações.

Foram identificados:

* **22 DET**
* **2 RET**

Classifique:

| Item             | Resposta |
| ---------------- | -------- |
| Tipo             |          |
| Complexidade     |          |
| Pontos de Função |          |

---

### D5 — Catálogo de Unidades do RU

O Sistema Central de Infraestrutura mantém informações sobre unidades, localização, capacidade, horários e serviços oferecidos.

O aplicativo do RU apenas consulta essas informações.

Foram identificados:

* **24 DET**
* **6 RET**

Classifique:

| Item             | Resposta |
| ---------------- | -------- |
| Tipo             |          |
| Complexidade     |          |
| Pontos de Função |          |

---

# 7. Consolidando as funções de dados

Preencha:

| Função             | ALI/AIE | DET | RET | Complexidade |           PF |
| ------------------ | ------- | --: | --: | ------------ | -----------: |
| Cardápio           |         |  12 |   2 |              |              |
| Conta e Transações |         |  26 |   3 |              |              |
| Avaliações         |         |  10 |   1 |              |              |
| Matrículas         |         |  22 |   2 |              |              |
| Unidades do RU     |         |  24 |   6 |              |              |
| **Subtotal**       |         |     |     |              | **_____ PF** |

---

# 8. Agora vamos às funções transacionais

As funções transacionais representam processos que atravessam a fronteira da aplicação.

Utilizaremos:

* **EE — Entrada Externa**
* **SE — Saída Externa**
* **CE — Consulta Externa**

Antes disso, precisamos conhecer um novo conceito.

---

# 9. Processo elementar

Um **processo elementar** é, simplificadamente:

> a menor atividade funcional significativa para o usuário que constitui uma transação completa.

Exemplos:

* registrar uma avaliação;
* consultar o saldo;
* gerar um extrato.

Não devemos contar separadamente cada clique, tela ou instrução técnica.

---

# 10. EE — Entrada Externa

Uma **Entrada Externa (EE)** ocorre quando dados ou informações de controle entram pela fronteira da aplicação e o principal objetivo da transação é, por exemplo:

* manter dados internos;
* alterar informações de um ALI;
* alterar o comportamento da aplicação.

### Exemplo

O aluno envia uma avaliação:

> nota + comentário → aplicativo

A avaliação é armazenada.

Temos um forte candidato a:

> **EE**

---

# 11. CE — Consulta Externa

Uma **Consulta Externa (CE)** recupera e apresenta informações sem produzir dados derivados ou cálculos significativos e sem manter um ALI.

### Exemplo

> “Qual é meu saldo atual?”

O sistema apenas recupera o saldo existente e o apresenta.

Logo:

> **Consultar saldo = candidata a CE**

---

# 12. SE — Saída Externa

Uma **Saída Externa (SE)** também envia informações para fora da fronteira, mas envolve processamento adicional, como:

* cálculo;
* geração de dados derivados;
* agregação;
* transformação significativa da informação.

### Compare

**Consultar saldo**

> recupera `R$ 42,00`

→ **CE**

**Emitir total gasto no mês**

> consulta diversas transações e calcula `R$ 186,50`

→ **SE**

Essa diferença será importante na atividade.

---

# 13. DET nas funções transacionais

Nas funções transacionais, os DET representam os elementos de dados reconhecidos pelo usuário que **cruzam a fronteira da aplicação** como entrada ou saída.

Exemplo:

Uma consulta recebe:

* matrícula;

e retorna:

* saldo;
* situação da conta;
* data da última atualização.

Os elementos relevantes que cruzam a fronteira entram na análise dos DET.

---

# 14. FTR — File Type Referenced

O **FTR** representa uma função de dados — ALI ou AIE — que é:

* consultada pelo processo; e/ou
* mantida pelo processo.

### Exemplo

Para validar a entrada de um estudante, o aplicativo:

1. consulta **Matrículas e Vínculos**;
2. atualiza **Conta e Transações**.

Portanto:

> **FTR = 2**

### Atenção

Se o mesmo arquivo for lido e atualizado pela mesma transação:

> conte o arquivo apenas uma vez como FTR.

---

# 15. Matriz de complexidade — EE

Para **Entradas Externas**:

| FTR \ DET         | 1–4 DET | 5–15 DET | 16 ou mais DET |
| ----------------- | ------- | -------- | -------------- |
| **0–1 FTR**       | Baixa   | Baixa    | Média          |
| **2 FTR**         | Baixa   | Média    | Alta           |
| **3 ou mais FTR** | Média   | Alta     | Alta           |

Pesos:

| Complexidade | PF |
| ------------ | -: |
| Baixa        |  3 |
| Média        |  4 |
| Alta         |  6 |

---

# 16. Matriz de complexidade — SE e CE

Para **Saídas Externas e Consultas Externas**:

| FTR \ DET         | 1–5 DET | 6–19 DET | 20 ou mais DET |
| ----------------- | ------- | -------- | -------------- |
| **0–1 FTR**       | Baixa   | Baixa    | Média          |
| **2–3 FTR**       | Baixa   | Média    | Alta           |
| **4 ou mais FTR** | Média   | Alta     | Alta           |

Pesos:

| Tipo   | Baixa | Média | Alta |
| ------ | ----: | ----: | ---: |
| **SE** |     4 |     5 |    7 |
| **CE** |     3 |     4 |    6 |

---

# 17. Como decidir entre EE, SE e CE?

Use este roteiro:

### Pergunta 1

**Dados entram na aplicação com o objetivo de registrar ou alterar informações?**

→ considere **EE**

### Pergunta 2

**O objetivo é apenas recuperar e apresentar dados existentes, sem cálculos ou dados derivados relevantes?**

→ considere **CE**

### Pergunta 3

**A informação sai da aplicação após cálculo, agregação ou geração de dados derivados?**

→ considere **SE**

---

# 18. Sua vez — funções transacionais do RU

Analise cada processo.

---

## T1 — Manter Cardápio Semanal

A equipe do RU envia os dados do cardápio e o aplicativo grava as alterações.

Dados fornecidos para a análise:

* DET = 8
* FTR = 1 — Cardápio

Perguntas:

1. Os dados estão entrando ou saindo?
2. Há manutenção de um ALI?
3. É EE, SE ou CE?
4. Qual a complexidade?
5. Quantos PF?

---

## T2 — Adicionar Créditos

O aluno informa um valor e seleciona a forma de pagamento. Após a confirmação do serviço externo de pagamento, o aplicativo atualiza a conta.

* DET = 7
* FTR = 1 — Conta e Transações

| Item         | Resposta |
| ------------ | -------- |
| EE / SE / CE |          |
| Complexidade |          |
| PF           |          |

---

## T3 — Consultar Saldo

O aluno solicita o saldo atual. O sistema apenas recupera e apresenta a informação existente.

* DET = 4
* FTR = 1 — Conta e Transações

| Item         | Resposta |
| ------------ | -------- |
| EE / SE / CE |          |
| Complexidade |          |
| PF           |          |

---

## T4 — Avaliar uma Refeição

O estudante seleciona a refeição consumida, atribui uma nota e envia um comentário.

A transação consulta o Cardápio e grava a nova Avaliação.

* DET = 7
* FTR = 2 — Cardápio + Avaliações

| Item         | Resposta |
| ------------ | -------- |
| EE / SE / CE |          |
| Complexidade |          |
| PF           |          |

---

## T5 — Validar Entrada na Catraca

Ao ler o QR Code:

1. o sistema consulta o vínculo acadêmico;
2. verifica se o estudante pode utilizar o RU;
3. debita o valor da refeição de sua conta.

* DET = 6
* FTR = 2 — Matrículas + Conta e Transações

| Item         | Resposta |
| ------------ | -------- |
| EE / SE / CE |          |
| Complexidade |          |
| PF           |          |

---

## T6 — Consultar Horário do RU

O estudante seleciona uma unidade e o aplicativo apresenta seus horários.

Não ocorre cálculo ou geração de informação derivada.

* DET = 5
* FTR = 1 — Unidades do RU

| Item         | Resposta |
| ------------ | -------- |
| EE / SE / CE |          |
| Complexidade |          |
| PF           |          |

---

## T7 — Emitir Extrato Mensal

O aplicativo recupera as transações realizadas no período e **calcula o total gasto durante o mês**.

* DET = 8
* FTR = 1 — Conta e Transações

### Pense antes de responder

> Esta função simplesmente consulta um valor existente ou produz uma informação calculada?

| Item         | Resposta |
| ------------ | -------- |
| EE / SE / CE |          |
| Complexidade |          |
| PF           |          |

---

## T8 — Enviar Resumo Semanal por E-mail

O aplicativo recupera os pratos e informações das unidades, organiza os dados por dia e unidade e gera um resumo semanal enviado ao estudante.

* DET = 10
* FTR = 2 — Cardápio + Unidades do RU

| Item         | Resposta |
| ------------ | -------- |
| EE / SE / CE |          |
| Complexidade |          |
| PF           |          |

---

## T9 — Consultar Cardápio Semanal

O estudante seleciona uma unidade e visualiza os pratos cadastrados para a semana.

Não existem cálculos ou dados derivados.

* DET = 7
* FTR = 1 — Cardápio

| Item         | Resposta |
| ------------ | -------- |
| EE / SE / CE |          |
| Complexidade |          |
| PF           |          |

---

# 19. Consolide a contagem transacional

| Processo              | Tipo | DET | FTR | Complexidade |           PF |
| --------------------- | ---- | --: | --: | ------------ | -----------: |
| Manter cardápio       |      |   8 |   1 |              |              |
| Adicionar créditos    |      |   7 |   1 |              |              |
| Consultar saldo       |      |   4 |   1 |              |              |
| Avaliar refeição      |      |   7 |   2 |              |              |
| Validar entrada       |      |   6 |   2 |              |              |
| Consultar horário     |      |   5 |   1 |              |              |
| Emitir extrato        |      |   8 |   1 |              |              |
| Enviar resumo semanal |      |  10 |   2 |              |              |
| Consultar cardápio    |      |   7 |   1 |              |              |
| **Subtotal**          |      |     |     |              | **_____ PF** |

---

# 20. Calcule o tamanho funcional

Agora some:

$$
PF_{Total}
=
PF_{Dados}
+
PF_{Transações}
$$

### Funções de dados

$$
PF_{Dados}=\_\_\_\_\_
$$

### Funções transacionais

$$
PF_{Transações}=\_\_\_\_\_
$$

### Tamanho funcional

$$
\boxed{PF_{Total}=\_\_\_\_\_}
$$

---

# 21. Pontos de Função não são esforço

Neste momento sabemos o:

> **tamanho funcional do software**

Mas ainda não sabemos diretamente seu esforço.

Para transformar tamanho em esforço precisamos utilizar informações de produtividade.

Suponha que os projetos anteriores da empresa apresentem:

$$
Produtividade =
8\ PF/pessoa\text{-}mês
$$

Calcule:

$$
Esforço=
\frac{PF_{Total}}{8}
$$

### Esforço estimado

$$
\boxed{\_\_\_\_\_\ pessoa\text{-}mês}
$$

---

# 22. Estimativa de custo

Os dados históricos também indicam:

$$
Custo\ médio=R\$400/PF
$$

Logo:

$$
Custo=
PF_{Total}\times400
$$

### Custo estimado

$$
\boxed{R\$\ \_\_\_\_\_\_\_\_\_\_}
$$

---

# 23. Interprete antes de confiar no resultado

Discuta com seu grupo:

### Questão 1

Qual função foi mais difícil de classificar entre ALI, AIE, EE, SE e CE?

Por quê?

### Questão 2

Por que **Consultar Saldo** e **Emitir Extrato Mensal** não pertencem necessariamente à mesma categoria, mesmo que ambas apresentem informações ao usuário?

### Questão 3

O número final de Pontos de Função indica diretamente quantos meses o projeto levará?

Explique.

### Questão 4

Vocês utilizariam imediatamente o custo calculado para assinar um contrato com o cliente?

Que informações adicionais gostariam de possuir?

---

# 24. O que este tutorial está ensinando?

A sequência utilizada foi:

$$
\text{Requisitos}
$$

$$
\downarrow
$$

$$
\text{Fronteira da aplicação}
$$

$$
\downarrow
$$

$$
\text{Funções de dados + funções transacionais}
$$

$$
\downarrow
$$

$$
\text{DET / RET / FTR}
$$

$$
\downarrow
$$

$$
\text{Complexidade funcional}
$$

$$
\downarrow
$$

$$
\boxed{\text{Pontos de Função}}
$$

Somente depois utilizamos dados históricos para obter:

$$
\text{PF}
\rightarrow
\text{Esforço}
\rightarrow
\text{Custo}
$$

---

# 25. Importante: por que não calculamos VAF?

Neste tutorial, estamos interessados no **tamanho funcional**.

Não utilizaremos a fórmula clássica:

$$
VAF=0,65+0,01\sum F_i
$$

O CPM 4.3 separou as General System Characteristics e o VAF do método normativo de medição do tamanho funcional, mantendo-os como material opcional. Portanto, nossa contagem termina com o tamanho funcional obtido pelas funções de dados e transacionais.

Características não funcionais, como desempenho, segurança e determinadas restrições técnicas, não devem simplesmente ser misturadas ao tamanho funcional.

---

# Resumo de referência rápida

## Tipos funcionais

| Sigla   | Significado                  | Pergunta principal                                       |
| ------- | ---------------------------- | -------------------------------------------------------- |
| **ALI** | Arquivo Lógico Interno       | Meu sistema mantém esses dados?                          |
| **AIE** | Arquivo de Interface Externa | Meu sistema consulta dados mantidos por outro sistema?   |
| **EE**  | Entrada Externa              | Dados entram para manter dados ou alterar comportamento? |
| **CE**  | Consulta Externa             | Apenas recupera e apresenta informação?                  |
| **SE**  | Saída Externa                | Produz saída com cálculo, agregação ou dado derivado?    |

## Elementos usados para complexidade

| Sigla   | Utilizada em       | Significado                                      |
| ------- | ------------------ | ------------------------------------------------ |
| **DET** | Dados e transações | Elemento de dado único reconhecível pelo usuário |
| **RET** | ALI/AIE            | Subgrupo lógico dentro de uma função de dados    |
| **FTR** | EE/SE/CE           | ALI ou AIE lido e/ou mantido pela transação      |

---

# Referências

PRESSMAN, Roger S.; MAXIM, Bruce R. **Engenharia de Software: Uma Abordagem Profissional.**

SOMMERVILLE, Ian. **Engenharia de Software.**

IFPUG — International Function Point Users Group. **Function Point Analysis (FPA) / Counting Practices Manual.**
