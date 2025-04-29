# Polling Rangers
## Entendendo o mecanismo de Polling de I/O

Engenharia de Computação
Pontifícia Universidade Católica de Campinas

Prof. Dr. Denis M. L. Martins

## Objetivos

- Simular o funcionamento de **polling**.
- Compreender as **ineficiências** no gerenciamento de I/O.
- Fixar o conceito de maneira prática e divertida.

## Materiais e Organização

- Dividir a turma em dois grupos:
  - **Grupo 1:** CPU (1 aluno).
  - **Grupo 2:** Dispositivos de I/O (4 a 5 alunos).
- Cada dispositivo recebe uma **folha** com "PRONTO" ou "OCUPADO" (inicialmente escondida).

## Como Funciona

1. **CPU** vai de aluno em aluno perguntando:
   > "Está pronto?"
2. Cada **Dispositivo** responde:
   - "Não, ainda ocupado." ou
   - "Sim, pronto!"
3. A CPU continua perguntando **em looping**.
4. Quando um dispositivo diz "pronto", a CPU interage (ex.: anota o nome).
5. Reiniciar para nova rodada.

Duração: 3 a 5 minutos por rodada.<style scoped>
pre{font-size:23px;text-align:center;}
</style># Representação Visual

```text
┌──────────┐      pergunta      ┌───────────────┐
│   CPU    │ ─────────────────> │ Dispositivo 1 │
└──────────┘                    └───────────────┘
┌──────────┐      pergunta      ┌───────────────┐
│   CPU    │ ─────────────────> │ Dispositivo 2 │
└──────────┘                    └───────────────┘
...
    Pergunta para o próximo dispositivo...
```

Loop até encontrar dispositivo "pronto"

## Discussão Após a Dinâmica

- A CPU estava realizando trabalho útil?
- O que acontece com o desempenho quando todos estão ocupados?
- Como **interrupções** poderiam melhorar esse cenário?
- Quais são as vantagens e desvantagens do polling?

## Fechamento

- **Polling** = CPU constantemente verifica o estado dos dispositivos.
- Ineficiente quando dispositivos demoram.
- **Interrupções** notificam a CPU apenas **quando necessário**.
- Sistemas modernos tendem a evitar polling em favor de interrupções.


# Interruptors  
## Entendendo interrupções de I/O

## Objetivo
- Simular o conceito de **interrupções** em I/O.
- Mostrar como a CPU **não precisa perguntar o tempo todo**, sendo **notificada** apenas quando necessário.
- Fixar a diferença entre **Polling** e **Interrupções** de maneira prática.


## Materiais e Organização
- **Turma dividida** em dois grupos:
  - **Grupo 1:** CPU (1 aluno).
  - **Grupo 2:** Dispositivos de I/O (4 a 5 alunos).
- Cada dispositivo deve ter uma **folha em branco** e uma **campainha**, palmas, ou um sinal combinado (para \"gerar uma interrupção\").



## Como Funciona

1. A **CPU** pode realizar outras tarefas simuladas (ex.: resolver um mini quebra-cabeça ou montar peças de lego).
2. Enquanto isso, cada **Dispositivo de I/O** deve simular que está trabalhando em uma operação (ex.: carregando, processando...).
3. Quando um dispositivo **estiver pronto**, ele deve **emitir o sinal de interrupção** (bater palmas, soar uma campainha, levantar a mão etc.).
4. Ao ouvir o sinal de interrupção:
   - A **CPU para sua atividade**.
   - A **CPU atende o dispositivo** (ex.: registrar o nome do dispositivo ou coletar uma \"mensagem\" escrita pelo aluno).
5. Após o atendimento, a CPU volta à sua tarefa anterior até a próxima interrupção.

## Duração
- Cada rodada de interrupções deve durar cerca de **5 a 8 minutos**.
- Depois, realizar a **discussão crítica**.

## Discussão guiada pós-dinâmica
- A CPU ficou o tempo todo perguntando como no polling?
- A CPU conseguiu realizar tarefas enquanto aguardava?
- Quais são as vantagens das interrupções em termos de eficiência?
- Em que situações, mesmo assim, interrupções podem ser problemáticas?

## Fechamento
- **Interrupções** permitem que a CPU **não desperdice tempo** perguntando constantemente.
- **Eficiência**: CPU foca em outras tarefas e apenas responde quando necessário.
- **Contexto real**: discos, teclados, redes — quase tudo hoje é baseado em interrupções!