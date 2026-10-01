---
title: "Engenharia de Software: Engenharia de Requisitos"
collection: labs
type: "Lab"
permalink: /labs/engenharia-requisitos
date: 2026-09-30
location: "Ribeirão Preto, Brazil"
---

# 1. Cenário

A universidade deseja desenvolver um **Sistema de Reserva de Recursos**.

O sistema deverá apoiar a reserva de:

- salas de aula;
- laboratórios;
- outros recursos institucionais.

Neste momento, **não existe uma especificação pronta**.

A universidade conhece o problema geral, mas várias regras, restrições e necessidades ainda precisam ser descobertas.

Durante a atividade, o professor atuará como **stakeholder** do sistema.

> **Importante:** nem todas as informações serão fornecidas espontaneamente.  
> Vocês precisarão perguntar, interpretar e registrar.

---

# 2. Organização da atividade

Cada grupo deverá produzir **um único documento final**, com aproximadamente **2–3 páginas, além do diagrama de casos de uso**, contendo os artefatos solicitados nas missões.

A atividade será realizada em etapas.

> **Não avancem para a próxima missão antes da orientação do professor.**

---

# 3. Missão 1:  Preparar a elicitação

Antes de escrever qualquer requisito, elaborem **5 perguntas** que ajudem a descobrir como o sistema deve funcionar.

As perguntas podem explorar temas como:

- quem pode reservar;
- quais recursos podem ser reservados;
- regras de aprovação;
- cancelamentos;
- conflitos de horário;
- reservas recorrentes;
- autenticação;
- restrições de uso;
- autorizações;
- indisponibilidades;
- desempenho;
- segurança.

## Regra

> **Não escrevam requisitos ainda.**

O objetivo desta etapa é perceber que:

```text
ELICITAR ≠ ESPECIFICAR
```

## Registro

Incluam no documento:

```text
Perguntas de elicitação

1.
2.
3.
4.
5.
```

---

# 4. Missão 2:  Entrevista coletiva

O professor assumirá o papel de stakeholder.

A entrevista será realizada coletivamente com toda a turma.

## Rodada estruturada

Cada grupo poderá fazer **uma pergunta que ainda não tenha sido feita**.

## Perguntas complementares

Depois da primeira rodada, serão permitidas perguntas de aprofundamento.

Todos os grupos deverão registrar as informações consideradas relevantes.

## Durante a entrevista

Procurem identificar:

| Categoria | O que observar |
|---|---|
| Usuários | Quem utiliza ou administra o sistema |
| Recursos | O que pode ser reservado |
| Regras | Condições para reserva, cancelamento e aprovação |
| Exceções | Situações especiais |
| Restrições | Limitações técnicas, institucionais ou operacionais |

### Atenção

Não assumam que uma informação “óbvia” é verdadeira.

Se algo não estiver claro:

> **Perguntem.**

---

# 5. Missão 3:  Especificação inicial

Agora transformem as informações obtidas durante a elicitação em requisitos.

## Produzam exatamente 6 requisitos

- **3 Requisitos Funcionais (RF)**
- **3 Requisitos Não Funcionais (RNF)**

## Template

| ID | Requisito | Tipo | Origem |
|---|---|---|---|
| RF01 | ... | RF | ... |
| RF02 | ... | RF | ... |
| RF03 | ... | RF | ... |
| RNF01 | ... | RNF | ... |
| RNF02 | ... | RNF | ... |
| RNF03 | ... | RNF | ... |

A coluna **Origem** deve indicar de onde surgiu a necessidade.

Exemplos:

- professor;
- aluno;
- secretaria;
- equipe de TI;
- regra de domínio;
- política institucional;
- restrição técnica.

---

# 6. Como escrever bons requisitos

Antes de registrar cada requisito, verifiquem se ele é:

- **claro**;
- **não ambíguo**;
- **necessário**;
- **viável**;
- **verificável**;
- **rastreável**.

## Exemplo inadequado

> O sistema deve ser rápido.

Problema:

- “rápido” não define uma condição objetiva.

## Exemplo melhor

> 95% das consultas de disponibilidade devem responder em até 2 segundos.

Lembrem-se:

> **Verificável não significa automaticamente válido.**

Um requisito pode ser fácil de testar e, ainda assim, não representar corretamente a necessidade do stakeholder.

---

# 7. Critérios de aceitação

Ainda na Missão 3, selecionem:

- **1 requisito funcional**;
- **1 requisito não funcional**.

Para cada um, escrevam **um critério de aceitação**.

## Template

| Requisito | Critério de aceitação |
|---|---|
| RF__ | CA01:  ... |
| RNF__ | CA02:  ... |

## Pergunta orientadora

> **Como saberemos objetivamente que este requisito foi atendido?**

---

# 8. Missão 4:  Modelagem com Casos de Uso

Agora representem parte dos requisitos funcionais por meio de casos de uso.

## Parte A:  Diagrama de Casos de Uso

Produzam um diagrama contendo:

- atores relevantes;
- pelo menos **2 casos de uso**;
- associações coerentes;
- limite do sistema.

## Lembrete

- **Ator:** papel externo que interage com o sistema.
- **Caso de uso:** objetivo ou serviço oferecido pelo sistema.
- **Associação:** relação entre ator e caso de uso.
- **Limite do sistema:** delimita o que pertence ao sistema.

### Dica de nomenclatura

Nomeiem os casos de uso com:

```text
VERBO + OBJETO
```

Exemplos:

```text
Reservar recurso
Cancelar reserva
Consultar disponibilidade
Aprovar reserva
```

Evitem nomes vagos como:

```text
Reserva
Sistema
Gerenciamento
Tela de recursos
```

---

## Parte B:  Descrição textual

Escolham **um dos casos de uso** e produzam uma descrição curta.

```text
UC01:  Nome do Caso de Uso

Ator principal:
...

Pré-condição:
...

Fluxo principal:
1.
2.
3.
4.
5.

Fluxo alternativo:
1.

Pós-condição:
...
```

O objetivo não é produzir uma especificação completa do caso de uso, mas representar de forma clara o cenário principal e uma situação alternativa relevante.

---

# 9. Missão 5:  Revisão por pares

Troquem o documento com outro grupo.

O grupo revisor deverá analisar o material **sem pedir explicações aos autores inicialmente**.

O objetivo é verificar se o documento consegue ser compreendido por outra equipe.

## Identifiquem pelo menos 2 problemas

Procurem responder:

1. Existe algum requisito que não conseguimos interpretar de forma única?
2. Existe algum requisito que não conseguimos verificar?
3. Falta alguma condição importante?
4. Existe alguma contradição?
5. O caso de uso está coerente com os requisitos?

## Classificação

Usem, quando aplicável:

```text
[A] Ambíguo
[I] Incompleto
[C] Conflitante
[V] Não verificável
[D] Duplicado
```

## Registro

| Problema encontrado | Tipo | Sugestão |
|---|---|---|
| ... | [A]/[I]/[C]/[V]/[D] | ... |
| ... | ... | ... |

---

# 10. Correção rápida

Recebam novamente o documento do grupo.

Analise os dois problemas apontados e corrijam aqueles que considerarem válidos.

Registrem:

| Problema encontrado | Correção realizada |
|---|---|
| ... | ... |
| ... | ... |

Se discordarem de uma observação, registrem brevemente a justificativa.

> Não é necessário reescrever toda a especificação.

---

# 11. Missão 6:  Change Request (CR) e análise de impacto

Durante um projeto, requisitos podem mudar.

Agora o cliente apresenta uma nova necessidade:

> **CR-01:  A partir de agora, alunos também podem reservar salas, mas somente com antecedência máxima de 7 dias.**

## Desafio

Analise o que precisa mudar no trabalho do grupo.

Identifiquem:

1. quais requisitos existentes são afetados;
2. quais requisitos precisam ser alterados;
3. se algum novo requisito deve ser criado;
4. quais casos de uso são afetados;
5. quais critérios de aceitação precisam ser revisados.

## Registro da análise de impacto

| Artefato | Item afetado | Ação necessária |
|---|---|---|
| Requisito | RF__ | Alterar |
| Requisito |:  | Criar novo requisito |
| Caso de uso | UC__ | Alterar |
| Critério de aceitação | CA__ | Revisar |

---

# 12. Rastreabilidade

Ainda na Missão 6, construam uma pequena matriz relacionando os artefatos produzidos.

Não é necessário representar todos os requisitos.

Incluam pelo menos os requisitos relacionados ao **Change Request** e os requisitos para os quais foram criados critérios de aceitação.

## Template

| Origem | Requisito | Caso de Uso | Critério de Aceitação |
|---|---|---|---|
| ... | RF01 | UC01 | CA01 |
| ... | RF02 | UC01 |:  |
| ... | RNF01 |:  | CA02 |

## Pergunta orientadora

> **Se um requisito mudar, onde mais precisamos olhar?**

A rastreabilidade ajuda a relacionar:

```text
ORIGEM
   ↓
REQUISITO
   ↓
MODELO
   ↓
CRITÉRIO DE ACEITAÇÃO
```

Em projetos reais, essa relação pode continuar até projeto, implementação e testes.

---

# 13. Consolidação do documento

Organizem o documento final.

Ele deverá conter:

## 1. Elicitação

- 5 perguntas preparadas pelo grupo;
- principais informações obtidas na entrevista.

## 2. Especificação

- 3 RF;
- 3 RNF;
- origem de cada requisito.

## 3. Critérios de aceitação

- 1 critério para um RF;
- 1 critério para um RNF.

## 4. Casos de uso

- 1 diagrama com pelo menos 2 casos de uso;
- descrição textual de 1 caso de uso.

## 5. Revisão por pares

- 2 problemas identificados;
- correções realizadas ou justificativa de não alteração.

## 6. Change Request e rastreabilidade

- tabela de análise de impacto;
- matriz de rastreabilidade.

---

# 14. Checklist antes da entrega

## Elicitação

- [ ] Elaboramos 5 perguntas.
- [ ] Registramos as principais respostas.
- [ ] Não inventamos regras que não foram descobertas ou justificadas.

## Requisitos

- [ ] Temos exatamente 3 RF.
- [ ] Temos exatamente 3 RNF.
- [ ] Todos possuem ID.
- [ ] Todos possuem origem.
- [ ] Evitamos termos vagos sem critérios objetivos.

## Critérios de aceitação

- [ ] Criamos 1 critério para um RF.
- [ ] Criamos 1 critério para um RNF.
- [ ] Os critérios são verificáveis.

## Casos de uso

- [ ] O diagrama possui atores.
- [ ] O diagrama possui pelo menos 2 casos de uso.
- [ ] Os casos de uso representam objetivos dos atores.
- [ ] Produzimos uma descrição textual curta.

## Revisão

- [ ] Recebemos a revisão de outro grupo.
- [ ] Registramos 2 problemas.
- [ ] Corrigimos ou justificamos os comentários recebidos.

## Mudança e rastreabilidade

- [ ] Identificamos os itens afetados pelo CR-01.
- [ ] Atualizamos ou indicamos os requisitos necessários.
- [ ] Construímos a matriz de rastreabilidade.
- [ ] Os IDs utilizados são consistentes.

---

# 15. Entregável final

Cada grupo deverá entregar **um único arquivo** com aproximadamente **2–3 páginas, além do diagrama de casos de uso**, contendo todos os itens solicitados.

O documento não será avaliado pela quantidade de texto.

O foco é a **coerência entre os artefatos** e a qualidade das decisões tomadas durante o processo.

> **Requisitos não são apenas texto: são uma ponte entre necessidades do mundo real e o software que será desenvolvido.**
