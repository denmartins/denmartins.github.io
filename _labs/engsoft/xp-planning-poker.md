---
title: "XP: Planning Poker"
collection: labs
type: "Lab"
permalink: /labs/xp-planning-poker
date: 2026-08-19
location: "Ribeirão Preto, Brazil"
---

# Cenário

## Sistema de Agendamento de Atendimento Acadêmico

A universidade deseja desenvolver um sistema para permitir que estudantes:

- consultem professores;
- visualizem horários disponíveis;
- realizem agendamentos;
- cancelem ou remarquem atendimentos;
- recebam notificações.

Vocês são a equipe responsável por **estimar Histórias de Usuário**.

---

# Histórias de Usuário

- **Consultar professores**
- **Consultar horários disponíveis**
- **Realizar agendamento**
- **Cancelar agendamento**
- **Enviar lembrete por e-mail**
- **Remarcar atendimento**
- **Gerar relatório mensal**

### Consultar professores

> Como estudante, quero visualizar os professores disponíveis para escolher com quem desejo agendar um atendimento.

### Consultar horários

> Como estudante, quero visualizar os horários livres de um professor para escolher um período.

### Realizar agendamento

> Como estudante, quero reservar um horário disponível para garantir meu atendimento.

### Cancelar agendamento

> Como estudante, quero cancelar um agendamento para liberar o horário quando não puder comparecer.

### Enviar lembrete

> Como estudante, quero receber um lembrete antes do atendimento para reduzir o risco de esquecimento.

### Remarcar atendimento

> Como estudante, quero alterar o horário de um agendamento existente sem precisar cancelar e criar outro.

---

# Story Points

Story Points representam uma **estimativa relativa** do tamanho de uma história.

Considerem:

- quantidade de trabalho;
- complexidade;
- incerteza;
- dependências;
- risco técnico.

> **Story Points não representam diretamente horas de trabalho.**

---

# Escala de Estimativas

Utilizaremos:

## 1 — 2 — 3 — 5 — 8 — 13 — ?

### `?`

Significa:

> **Não temos informação suficiente para estimar.**

Quanto maior o número, maior o tamanho percebido da história em relação às demais.

---

# História de Referência

Para iniciar, adotaremos:

## Consultar professores = 2 Story Points

Utilizem essa história como referência.

Para cada nova história, perguntem:

> É menor, semelhante ou maior do que **Consultar professores**?

---

# Como funciona o Planning Poker?

### Para cada história:

1. Leiam a história.
2. Discutam dúvidas rapidamente.
3. Cada integrante escolhe uma estimativa **individualmente**.
4. Todos revelam os cartões **ao mesmo tempo**.
5. Comparem as estimativas.
6. Discutam as diferenças.
7. Façam uma nova rodada.

---

# Regra importante

## Não revelem as estimativas antes da hora!

Todos devem revelar os cartões simultaneamente.

### Por quê?

Evita que a primeira opinião apresentada:

- influencie os demais;
- gere ancoragem;
- reduza a diversidade das estimativas.

---

# Quando as estimativas forem diferentes

Exemplo:

| Integrante | Estimativa |
|---|---:|
| A | 3 |
| B | 5 |
| C | 5 |
| D | 8 |

Não calculem simplesmente a média.

Primeiro, ouçam:

### Menor estimativa

> Por que você considera essa história mais simples?

### Maior estimativa

> Que complexidade, risco ou dificuldade você identificou?

Depois:

- discutam as diferentes interpretações;
- esclareçam dúvidas;
- façam uma **nova votação**.

---

# Primeira Rodada

## História: Realizar agendamento

> Como estudante, quero reservar um horário disponível para garantir meu atendimento.

### Discutam rapidamente:

- O que precisa acontecer para um agendamento ser realizado?
- Existem regras de negócio?
- Há dependências?
- O que pode tornar essa funcionalidade complexa?

Depois:

## Escolham seus Story Points!

---

# Segunda Rodada

Após a discussão:

1. escolha novamente um cartão;
2. revelem simultaneamente;
3. comparem as novas estimativas;
4. registrem a estimativa final do grupo.

### Importante

O objetivo não é apenas chegar a um número.

> O objetivo é construir um **entendimento compartilhado** sobre a história.

---

# Agora é com vocês!

Estimem as seguintes histórias:

2. **Consultar horários disponíveis**
3. **Cancelar agendamento**
4. **Enviar lembrete por e-mail**
5. **Gerar relatório mensal**

Utilizem o Planning Poker para cada uma.

---

# Registro das Estimativas

Preencham:

| História | 1ª rodada | Principal divergência | Estimativa final |
|---|---:|---|---:|
| Login institucional | | | |
| Consultar horários | | | |
| Cancelar agendamento | | | |
| Enviar lembrete | | | |
| Gerar relatório | | | |

---

# Mudança de Requisito!

O cliente traz uma nova informação:

> O lembrete não deverá mais ser enviado apenas por e-mail.

## Agora ele também deverá ser enviado por WhatsApp.

Para isso, será necessário utilizar um **serviço externo que a equipe nunca utilizou**.

---

# Reestimem!

Retornem à história:

## Enviar lembrete

Perguntas:

- A estimativa anterior continua válida?
- O que mudou?
- Surgiram novas dependências?
- A incerteza técnica aumentou?
- Precisamos de mais informações?

### Façam uma nova rodada de Planning Poker.

---

# O que Story Points estão capturando?

A mudança mostrou que uma estimativa pode ser influenciada por:

### Esforço
Quanto trabalho parece ser necessário?

### Complexidade
Quão difícil é implementar?

### Incerteza
Quanto ainda não sabemos?

### Risco
O que pode dar errado?

---

# Produto da Atividade

Cada grupo deverá entregar:

### 1. Tabela de estimativas

- primeira rodada;
- divergências;
- estimativa final.

### 2. Reestimativa da história de lembrete

Antes e depois da mudança para WhatsApp.

### 3. Breve justificativa

Escolham a história com **maior divergência de estimativas** e expliquem:

> Por que os integrantes do grupo inicialmente discordaram?

---

# Discussão Final

## Conversem no grupo

1. Por que pessoas diferentes estimaram a mesma história de formas diferentes?
2. O que vocês descobriram durante as discussões?
3. Por que revelar os cartões simultaneamente?
4. Story Points podem ser convertidos diretamente em horas?
5. Quando utilizar `?` é uma boa decisão?

---

# O principal aprendizado

Planning Poker ajuda a equipe a:

- revelar diferentes interpretações;
- identificar dúvidas;
- descobrir riscos;
- discutir complexidade;
- compartilhar conhecimento;
- construir entendimento comum.

> **A discussão gerada pela estimativa pode ser mais valiosa que a própria estimativa.**