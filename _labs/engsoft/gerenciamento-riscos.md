---
title: "Engenharia de Software: Gerenciamento de Risco"
collection: labs
type: "Lab"
permalink: /labs/gerenciamento-risco
date: 2026-09-24
location: "Ribeirão Preto, Brazil"
---

Nesta atividade, você assumirá o papel de integrante da equipe responsável pelo planejamento de um projeto de software.

O objetivo é construir um **registro simplificado de riscos**, passando pelas principais etapas do gerenciamento de riscos:


> **Importante:** não existe uma única resposta correta. As decisões do grupo devem ser **coerentes com o cenário e justificadas**.

---

# 1. Cenário: Projeto UniAgenda

A universidade está desenvolvendo o **UniAgenda**, um novo sistema web para
agendamento de salas, laboratórios e equipamentos.

O sistema deverá permitir que professores, estudantes e funcionários consultem
a disponibilidade de recursos, realizem reservas e recebam notificações sobre
alterações ou cancelamentos.

O projeto possui:

- prazo previsto de **4 meses**;
- equipe com **6 desenvolvedores**;
- integração obrigatória com o sistema acadêmico legado;
- infraestrutura hospedada em nuvem;
- implantação prevista antes do início do próximo semestre.

Durante o planejamento do projeto, a equipe levantou as seguintes informações:

1. Apenas um desenvolvedor conhece profundamente o sistema acadêmico legado.
2. A API utilizada para integração com o sistema legado possui documentação incompleta.
3. O fornecedor de infraestrutura em nuvem anunciou que poderá alterar sua política de preços nos próximos meses.
4. Alguns departamentos ainda não chegaram a um acordo sobre as regras de prioridade para reserva de salas.
5. A equipe nunca utilizou o novo framework escolhido para o front-end.
6. O sistema deverá suportar aproximadamente **5.000 usuários simultâneos** nos períodos de maior utilização.
7. Um desenvolvedor informou que ficará afastado durante duas semanas no segundo mês do projeto.
8. Alguns plugins utilizados atualmente na pipeline de CI/CD deixarão de receber suporte.
9. A direção da universidade está considerando antecipar a implantação em duas semanas.
10. O servidor utilizado para testes está indisponível desde ontem.

---

# 2. Parte A: Risco ou problema?

Antes de iniciar o registro de riscos, analise as informações apresentadas no
cenário.

## Tarefa

Identifique:

- quais situações representam **riscos**;
- se existe alguma situação que já representa um **problema**.

Registre o problema identificado separadamente.

### Lembrete

**Risco**

Evento ou condição **futura e incerta**.

> Exemplo:  
> “O fornecedor pode aumentar o preço do serviço em nuvem.”

**Problema**

Situação indesejada que **já aconteceu**.

> Exemplo:  
> “O serviço em nuvem está indisponível.”

### Dica

Faça a pergunta:

> **“Isso ainda pode acontecer ou já está acontecendo?”**

Se ainda existe incerteza, provavelmente estamos diante de um **risco**.

---

# 3. Parte B: Identificação dos riscos

Identifique **pelo menos 6 riscos** presentes no cenário.

Escreva os riscos de forma clara e objetiva.

## Forma recomendada

Utilize a estrutura:

> **Existe a possibilidade de [EVENTO], podendo causar [CONSEQUÊNCIA].**

### Exemplo

Evite escrever:

> “Problemas com a API.”

Prefira:

> “Existe a possibilidade de a documentação incompleta da API provocar
> erros de integração e atrasar o desenvolvimento.”

---

## Classificação

Para cada risco identificado, indique sua principal categoria:

- **Estimativa**
- **Organizacional**
- **Pessoal**
- **Requisitos**
- **Tecnologia**
- **Ferramentas**

> **Dica:** não é necessário encontrar exatamente um risco de cada categoria.
> Um projeto pode apresentar vários riscos da mesma natureza.

---

# 4. Parte C: Avaliação dos riscos

Agora estime a **probabilidade** e o **impacto** de cada risco.

## Probabilidade

Utilize a seguinte escala:

| Probabilidade | Interpretação |
|---:|---|
| 0,1 | Muito baixa |
| 0,3 | Baixa |
| 0,5 | Média |
| 0,7 | Alta |
| 0,9 | Muito alta |

O grupo deve escolher um valor considerando as informações disponíveis no
cenário.

### Dica

Não escolha probabilidades apenas para fazer os cálculos.

Pergunte:

- Existem sinais de que o evento pode ocorrer?
- Existe dependência de terceiros?
- A equipe já possui experiência com a tecnologia?
- O evento já foi parcialmente anunciado?
- Existem fatores que aumentam ou reduzem sua ocorrência?

---

# 5. Estimativa do impacto

Para simplificar a atividade, utilize os seguintes valores de referência:

| Impacto | Consequência estimada |
|---|---:|
| Baixo | R$ 5.000 |
| Moderado | R$ 15.000 |
| Alto | R$ 30.000 |
| Crítico | R$ 50.000 |

O valor representa uma **estimativa didática da consequência para o projeto**,
considerando fatores como:

- retrabalho;
- horas adicionais;
- atraso;
- contratação;
- infraestrutura;
- perda de produtividade.

> Não estamos tentando calcular o custo real do projeto.  
> O objetivo é utilizar uma mesma escala para comparar os riscos.

---

# 6. Parte D: Calcule a Exposição ao Risco

Segundo **Pressman & Maxim**, uma forma de apoiar a priorização é calcular a
**Exposição ao Risco (Risk Exposure: RE)**:

$$
RE = P(R) \times C(R)
$$

onde:

- $P(R)$ = probabilidade de ocorrência;
- $C(R)$ = consequência estimada caso o risco ocorra.

---

## Exemplo

Considere:

- probabilidade = **0,7**
- impacto = **R$ 30.000**

Então:

$$
RE = 0,7 \times 30.000
$$

$$
RE = R\$21.000
$$

---

# 7. Construa o Registro de Riscos

Monte uma tabela como a seguinte:

| ID | Risco | Categoria | Probabilidade | Impacto | RE |
|---|---|---|---:|---:|---:|
| R1 | ... | Tecnologia | 0,7 | R$ 30.000 | R$ 21.000 |
| R2 | ... | Pessoal | ... | ... | ... |
| R3 | ... | ... | ... | ... | ... |
| R4 | ... | ... | ... | ... | ... |
| R5 | ... | ... | ... | ... | ... |
| R6 | ... | ... | ... | ... | ... |

## Em seguida

Ordene a tabela do **maior para o menor RE**.

Identifique os:

### **3 riscos prioritários do projeto**

---

## Atenção

Dois riscos podem possuir a mesma exposição:

$$
RE_1 = RE_2
$$

Isso **não significa necessariamente que sejam equivalentes**.

Considere também:

- natureza do risco;
- possibilidade de recuperação;
- momento em que pode ocorrer;
- dependências afetadas;
- disponibilidade de alternativas.

---

# 8. Parte E: Defina a resposta aos riscos

Para cada um dos **3 riscos prioritários**, escolha uma estratégia de resposta.

## Estratégias

### Evitar

Eliminar a causa ou modificar o projeto para que o risco deixe de existir.

### Mitigar

Reduzir a probabilidade ou o impacto do risco.

### Transferir

Compartilhar ou deslocar parte da responsabilidade para outra parte.

### Aceitar

Reconhecer conscientemente o risco sem realizar uma ação preventiva específica.

### Contingenciar

Preparar antecipadamente uma ação que será utilizada caso o risco se
materialize.

---

## Registre a decisão

| Risco | Estratégia | Ação proposta |
|---|---|---|
| R1 | Mitigar | ... |
| R2 | ... | ... |
| R3 | ... | ... |

---

## Importante

A estratégia sozinha não é suficiente.

### Resposta inadequada

> **Estratégia:** Mitigar  
> **Ação:** Melhorar a situação.

### Resposta adequada

> **Estratégia:** Mitigar  
> **Ação:** Desenvolver, já na primeira semana, um protótipo de integração
> com os principais endpoints da API legada.

A ação deve indicar **o que efetivamente será feito**.

---

# 9. Parte F: Como monitorar o risco?

Um risco não deixa de existir apenas porque uma resposta foi planejada.

Para cada um dos **3 riscos prioritários**, estabeleça:

1. **Indicador**: o que será observado?
2. **Gatilho**: qual situação exige ação?
3. **Responsável**: quem acompanhará esse risco?

---

## Exemplo

### Risco

A integração com a API legada pode atrasar o desenvolvimento.

### Indicador

Percentual de endpoints críticos integrados.

### Gatilho

Menos de 50% dos endpoints integrados até o final da terceira semana.

### Responsável

Líder técnico.

---

## Complete a tabela

| Risco | Indicador | Gatilho | Responsável |
|---|---|---|---|
| R1 | ... | ... | ... |
| R2 | ... | ... | ... |
| R3 | ... | ... | ... |

---

# 10. Entregável

Cada grupo deverá enviar ao Moodle:

## **1 arquivo PDF: máximo de 2 páginas**

O documento deve conter somente:

### Parte 1: Registro dos riscos

Apresente os riscos identificados e avaliados:

| ID | Risco | Categoria | P | Impacto | RE |
|---|---|---|---:|---:|---:|

Destaque visualmente os **3 riscos prioritários**.

---

### Parte 2: Plano de resposta e monitoramento

Para os três riscos prioritários:

| Risco | Estratégia | Ação | Indicador / Gatilho |
|---|---|---|---|

---

### Parte 3: Decisão do grupo

Responda em **no máximo três linhas**:

> **Qual é o risco que mais preocupa o grupo? Por quê?**

---

# 11. Dicas para realizar a atividade

## Dica 1: Não confunda causa, risco e consequência

Uma forma útil de pensar é:

**Causa → Evento incerto → Consequência**

Exemplo:

> Documentação incompleta  
> → erros de integração podem ocorrer  
> → atraso e retrabalho.

O **risco** está relacionado ao evento incerto e às suas consequências.

---

## Dica 2: Não transforme tudo em risco

A frase:

> “O projeto pode dar errado.”

é genérica demais para ser gerenciada.

Prefira riscos específicos:

> “A equipe pode não conseguir integrar a API legada dentro do prazo,
> causando atraso no desenvolvimento.”

---

## Dica 3: Evite respostas genéricas

Evite:

- “ter cuidado”;
- “acompanhar”;
- “resolver rapidamente”;
- “fazer reuniões”.

Prefira ações observáveis:

- criar um protótipo;
- designar um desenvolvedor backup;
- executar teste de carga;
- realizar treinamento;
- revisar contrato com fornecedor;
- validar requisitos com os departamentos.

---

## Dica 4: Um risco prioritário precisa ser monitorável

Pergunte:

> **“Como perceberemos que esse risco está ficando mais perigoso?”**

A resposta ajuda a criar o **indicador**.

Depois pergunte:

> **“Em que ponto deixaremos de apenas observar e começaremos a agir?”**

A resposta ajuda a criar o **gatilho**.

---

## Dica 5: O maior RE não decide tudo sozinho

A Exposição ao Risco é um instrumento de apoio à decisão.

O grupo deve também considerar:

- urgência;
- possibilidade de mitigação;
- dependências;
- momento de ocorrência;
- efeitos sobre outras atividades.

---

> **Pergunta final:**  
> Um risco com baixa probabilidade deve sempre receber menos atenção que um isco com alta probabilidade?