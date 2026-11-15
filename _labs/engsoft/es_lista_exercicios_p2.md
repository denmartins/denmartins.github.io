---
title: "Engenharia de Software: Lista de Exercícios - Preparação para Prova P2"
collection: labs
type: "Lab"
permalink: /labs/es-lista-exercicios-p2
date: 2026-11-15
location: "Ribeirão Preto, Brazil"
---

## Caso de estudo: Sistema de Reserva de Salas

Uma universidade controla a utilização de salas de aula e laboratórios por planilhas mantidas pelas secretarias. Há registros duplicados, dificuldade para consultar horários livres e divergências sobre quem pode autorizar o uso de determinados espaços.

Uma equipe de **três profissionais** desenvolverá um **sistema web para uso em um campus**. A primeira versão deverá ficar disponível em **oito semanas**. O orçamento é limitado e o serviço institucional de autenticação deverá ser utilizado.

### Usuários e funcionalidades

- **Docentes e servidores técnicos:** consultar disponibilidade, solicitar reservas e cancelar suas próprias reservas nas condições permitidas.
- **Estudantes:** consultar disponibilidade, sem permissão para solicitar ou cancelar reservas.
- **Secretaria:** cadastrar salas, definir capacidade e tipo e decidir sobre solicitações de laboratórios.
- **Serviço institucional de autenticação:** verificar a identidade dos usuários. A aplicação usa o perfil institucional para autorizar as operações.

### Regras estabelecidas

1. Cada reserva está vinculada a **um solicitante e uma sala**.
2. Cada sala possui capacidade inteira positiva e é classificada como **sala comum** ou **laboratório**.
3. A duração solicitada é um número inteiro entre **30 e 180 minutos**, inclusive.
4. A quantidade de participantes é inteira, maior que zero e menor ou igual à capacidade da sala.
5. Salas comuns são confirmadas automaticamente quando as condições são atendidas.
6. Solicitações válidas de laboratório ficam **pendentes** até a decisão da secretaria. A secretaria pode confirmá-las ou rejeitá-las.
7. Somente reservas **confirmadas** bloqueiam o horário. Solicitações pendentes não bloqueiam e a disponibilidade deve ser novamente verificada ao confirmar um laboratório.
8. Duas reservas confirmadas da mesma sala não podem se sobrepor. Reservas consecutivas são permitidas: uma pode começar exatamente quando a outra termina.
9. O solicitante pode cancelar sua própria reserva pendente ou confirmada **somente antes do início**. Exatamente no horário de início, o cancelamento já não é permitido.
10. Os estados usados são **pendente, confirmada, rejeitada e cancelada**. Uma solicitação inválida de sala comum deve ser recusada sem criar uma reserva confirmada.
11. O sistema deve registrar quem realizou cada mudança de estado e quando ela ocorreu.
12. A indisponibilidade do serviço de autenticação impede novos acessos autenticados, mas não deve apagar ou modificar reservas existentes. O tratamento de sessões já abertas está fora do escopo desta lista.

---

### Questão 1

Ao preparar a estimativa do sistema, a equipe considerou apenas as horas necessárias para construir as telas de consulta e solicitação. O coordenador pretende usar a soma dessas horas como estimativa de todo o desenvolvimento.

Uma revisão identificou atividades ainda não consideradas: integração com a autenticação institucional, regras de conflito de horários, testes e preparação da implantação.

Qual decisão torna a estimativa mais adequada?

- (A) Manter o total inicial, pois atividades sem telas visíveis não ampliam o tamanho do trabalho.  
- (B) Duplicar o total como margem fixa, dispensando a análise das atividades identificadas.  
- (C) Decompor o trabalho incluindo as atividades omitidas, estimá-las com dados disponíveis e explicitar premissas e incertezas.  
- (D) Dividir o total inicial entre os três profissionais e adotar o resultado como duração garantida do projeto.  
- (E) Substituir a estimativa pelo prazo de oito semanas, pois a data de entrega determina o esforço necessário.

**Justifique sua escolha.**

### Questão 2

Em uma reunião, um docente pede confirmação imediata de qualquer espaço. A secretaria afirma que o uso de laboratórios depende de autorização. Alguns estudantes também solicitam permissão para efetuar reservas, embora essa possibilidade não faça parte das regras atuais.

Antes de alterar a especificação aprovada, a equipe deve:

- (A) Implementar a solicitação mais recente, pois ela representa a necessidade atual de todos os usuários.  
- (B) Adotar a proposta que exige menos código e comunicar a decisão após a implantação.  
- (C) Transferir a decisão ao serviço de autenticação, que deverá definir as regras de autorização.  
- (D) Registrar as três propostas como requisitos simultaneamente válidos, sem resolver as divergências.  
- (E) Identificar interesses e restrições, negociar prioridades e avaliar os impactos de eventuais mudanças nas regras e no escopo.

**Justifique sua escolha.**

### Questão 3

No projeto do sistema, uma reserva conhece seu início e término. O componente de consulta à agenda consegue obter as reservas confirmadas de uma sala. A interface gráfica foi encarregada de calcular durações e verificar conflitos, e outras partes começaram a repetir essas verificações.

Avalie as afirmações:

**I.** A responsabilidade de calcular a duração pode ser atribuída à reserva, pois ela conhece os dados necessários.  
**II.** Conhecer o início e o término de uma reserva é suficiente, por si só, para verificar se ela conflita com todas as outras reservas da sala.  
**III.** Oferecer uma operação de consulta de conflitos sem expor a estrutura interna de armazenamento favorece o ocultamento de informação.

É correto o que se afirma em:

A) I e III, apenas.  
B) II, apenas.  
C) I e II, apenas.  
D) II e III, apenas.  
E) I, II e III.

**Justifique sua escolha.**

### Questão 4

Um teste confirma que o sistema rejeita solicitações com participantes acima da capacidade da sala. Em uma avaliação com docentes, porém, vários usuários interpretam o indicador “pendente” como se a reserva do laboratório já estivesse garantida.

Qual interpretação é mais adequada?

- (A) A aprovação no primeiro teste demonstra que a interface atende às necessidades dos docentes.  
- (B) O primeiro resultado fornece evidência de verificação da regra de capacidade; a avaliação com usuários revela uma necessidade de validação da comunicação dos estados.  
- (C) A dificuldade dos docentes invalida a necessidade de verificar regras de capacidade.  
- (D) A avaliação da interpretação dos usuários pertence exclusivamente à implantação e não deve influenciar o projeto.  
- (E) A situação exige aumentar a capacidade cadastrada, pois esse valor explica a confusão entre os estados.

**Justifique sua escolha.**

### Questão 5

A equipe mantém alterações de cada integrante isoladas durante duas semanas. Os conflitos só são encontrados na véspera da entrega. Existe uma ferramenta de automação, mas ela executa testes apenas no final desse período. A publicação em produção exige autorização da universidade.

Avalie as afirmações:

**I.** Integrações frequentes de mudanças menores, acompanhadas de verificações automáticas, podem antecipar a identificação de problemas.  
**II.** Instalar uma ferramenta de automação é suficiente para caracterizar integração contínua, mesmo mantendo o isolamento prolongado.  
**III.** A aprovação humana para produção pode coexistir com entrega contínua, desde que a versão permaneça pronta para liberação.

É correto o que se afirma em:

- (A) I, apenas.  
- (B) II e III, apenas.  
- (C) I e II, apenas.  
- (D) I e III, apenas.  
- (E) I, II e III.

**Justifique sua escolha.**

### Questão 6:

Para um incremento do sistema, a equipe estimou:

| Atividade | Esforço |
|---|---:|
| Consulta de disponibilidade e interface | 60 pessoa-horas |
| Regras de solicitação e aprovação | 90 pessoa-horas |
| Integração com autenticação | 30 pessoa-horas |
| Testes e correções previstas | 60 pessoa-horas |
| Documentação e preparação da implantação | 20 pessoa-horas |

Cada um dos três profissionais poderá dedicar **20 horas semanais** ao incremento. O custo médio é de **R$ 80 por pessoa-hora**. Considere somente o custo de trabalho da equipe.

**Tarefas:**

- (A) Calcule o esforço total e o custo estimado.  
- (B) Calcule a capacidade semanal da equipe e o limite inferior de duração obtido pela divisão esforço/capacidade, admitindo aproveitamento integral dessa capacidade.  
- (C) Explique por que esse resultado não garante uma data de conclusão. Apresente duas premissas da estimativa e dois fatores que podem aumentar sua duração.  
- (D) A integração passa a exigir 50 pessoa-horas. Recalcule o esforço e o custo e explique o que deve ser reavaliado no planejamento.

### Questão 7

Considere os riscos:

| Risco | Probabilidade | Perda se ocorrer |
|---|---:|---:|
| R1 — Alteração na interface do serviço de autenticação | 20% | R$ 15.000 |
| R2 — Indisponibilidade dos representantes da secretaria para esclarecer regras | 40% | R$ 10.000 |

O cronograma de um incremento contém:

| Atividade | Descrição | Predecessoras | Duração |
|---|---|---|---:|
| A | Esclarecer regras e critérios | — | 3 dias |
| B | Desenvolver o fluxo de reservas | A | 5 dias |
| C | Preparar os dados de salas | A | 2 dias |
| D | Testar o fluxo de reservas | B | 4 dias |
| E | Conferir os dados preparados | C | 3 dias |
| F | Homologar o incremento | D e E | 2 dias |

**Tarefas:**

- (a) Calcule a exposição financeira dos riscos e indique o de maior valor.  
- (b) Proponha uma ação preventiva para cada risco e um plano de contingência para R2.  
- (c) Desenhe a rede, encontre o caminho crítico e a duração mínima. Considere recursos suficientes para executar os ramos paralelos.  
- (d) Determine a folga total de E. Se E durar seis dias em vez de três, o incremento atrasará? E se durar oito dias? Justifique.

### Questão 8 

A secretaria informa: “O sistema precisa mostrar claramente se o laboratório foi autorizado. Não podemos confirmar uma solicitação se o horário já tiver sido ocupado”.

**Tarefas:**

- (a) Escreva dois requisitos funcionais para a decisão sobre solicitações de laboratório.  
- (b) Proponha um requisito não funcional mensurável relacionado à clareza da informação para o usuário. Indique como seria avaliado.  
- (c) Escreva dois critérios de aceitação: um para confirmar uma solicitação pendente sem conflito e outro para a tentativa de confirmar uma solicitação cujo horário já está ocupado.  
- (d) Desenhe um **diagrama de atividades** da análise pela secretaria. Considere uma solicitação pendente com duração e capacidade válidas. Represente decisão de rejeitar, decisão de aprovar e a nova verificação de disponibilidade. Se houver conflito, a tentativa de confirmação é recusada e a solicitação permanece pendente para posterior decisão da secretaria.

### Questão 9

A interface do usuário contém comandos para acessar o banco e também chamadas específicas ao serviço de autenticação. As regras de capacidade e de sobreposição são repetidas nas telas de solicitação e de aprovação.

**Tarefas:**

- (a) Proponha uma organização em **apresentação, aplicação/domínio e infraestrutura**, indicando as responsabilidades de cada parte.  
- (b) Desenhe um diagrama de blocos que mostre como uma solicitação percorre a solução. Identifique quais setas representam chamadas durante a execução.  
- (c) Explique como isolar os detalhes de autenticação e armazenamento por contratos, para que as regras não precisem conhecê-los diretamente.  
- (d) Explique como testar uma regra de capacidade sem interface gráfica e sem autenticação institucional real. Diferencie essa verificação de um teste da integração completa.

### Questão 10

Elabore **dez casos de teste** com identificador, regra avaliada, pré-condições, dados/ação e resultado esperado:

- Quatro de duração: valores nos dois limites e imediatamente fora deles.
- Dois de capacidade: número de participantes igual à capacidade e acima dela.
- Dois de disponibilidade: sobreposição e horários consecutivos.
- Dois de cancelamento: instante anterior ao início e instante exatamente igual ao início.

**Condições para isolar as regras:**

- Use sala comum e solicitante autorizado e autenticado nos testes de solicitação.
- Para duração e capacidade, considere um período livre.
- Para disponibilidade, use uma sala com reserva confirmada das **10h às 11h**.
- Para cancelamento, considere reserva própria confirmada com início às **14h**, um relógio de teste controlado e nenhuma mudança concorrente.
- Todos os testes são independentes. Mantenha as demais condições válidas.

Ao final, escolha um teste de **integração** e um de **aceitação** que complementariam esses casos e explique o objetivo de cada um.

### Questão 11

Após a especificação inicial, a universidade propõe permitir que estudantes solicitem salas comuns, desde que haja aprovação da secretaria.

Explique quais stakeholders devem participar da análise e como a mudança afeta autorização, requisitos, modelos, estimativas e testes. Apresente uma cadeia de rastreabilidade com pelo menos quatro elementos e explique por que alterar apenas a tela de solicitação seria insuficiente.

### Questão 12

Um grupo produziu um diagrama de classes com Usuário, Reserva e Sala e concluiu que ele demonstra como a secretaria aprova uma solicitação.

Explique a limitação dessa conclusão e o papel complementar de **casos de uso, atividades e sequência**. Indique as multiplicidades entre Usuário–Reserva e Sala–Reserva e descreva as mensagens essenciais da aprovação de um laboratório, incluindo a rechecagem de conflito.

### Questão 13

Um desenvolvedor extrai o cálculo de duração da tela para um elemento de domínio, preservando os resultados anteriores. No mesmo trabalho, altera a regra de cancelamento para permitir cancelar exatamente no horário de início.

Classifique separadamente as duas mudanças e explique suas consequências. Relacione sua análise a coesão, distribuição de responsabilidades e preservação do comportamento. Indique quais evidências seriam necessárias para aceitar cada mudança.

### Questão 14

A universidade percebe que o sistema funciona adequadamente em testes com poucas pessoas, mas apresenta lentidão no início do semestre. Além disso, novos usuários têm dificuldade para distinguir reserva pendente de confirmada.

Proponha ações que considerem **desempenho, usabilidade e confiabilidade**. Diferencie atividades de garantia da qualidade e de controle da qualidade e explique como um processo de revisão e medição poderia reduzir a repetição desses problemas.

### Questão 15

Uma liberação do sistema utiliza código atualizado, uma versão antiga da especificação das regras e um script de banco cuja origem ninguém consegue identificar. No ambiente de um desenvolvedor os testes passam; no ambiente de homologação, uma biblioteca diferente provoca falhas.

Explique:

- (a) Quais artefatos deveriam ser identificados e controlados como itens de configuração.  
- (b) Como estabelecer uma referência coerente para a liberação e o que uma auditoria deveria verificar.  
- (c) Como registrar e avaliar uma correção urgente sem perder o histórico.  
- (d) Como dependências identificadas e contêineres podem ajudar a reproduzir o ambiente, e quais problemas continuam exigindo testes e revisão.
