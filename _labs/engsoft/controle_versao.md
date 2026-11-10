---
title: "Engenharia de Software: Controle de Versões e Colaboração com Git"
collection: labs
type: "Lab"
permalink: /labs/controle-versao
date: 2026-11-12
location: "Ribeirão Preto, Brazil"
---

## Cenário

Cada grupo será responsável pelo desenvolvimento colaborativo de um pequeno projeto denominado **Sistema de Reserva de Salas**.

O projeto será representado inicialmente por arquivos Markdown. O objetivo não é programar um sistema completo, mas praticar o fluxo de trabalho colaborativo com Git e GitHub.

## Pré-requisitos

- Computador com Git instalado.
- Conta no [GitHub](https://github.com).
- Editor de texto ou VS Code.
- Terminal de comandos.
- Acesso à internet.

Verifique a instalação do Git:

```bash
git --version
```

Caso seja a primeira utilização do Git, configure sua identidade:

```bash
git config --global user.name "Seu Nome"
git config --global user.email "seu-email@exemplo.com"
```

Utilize um e-mail associado à sua conta do GitHub, preferencialmente o endereço privado disponibilizado pela plataforma.

## Organização dos grupos

Cada grupo deverá ter de 3 a 4 estudantes.

| Papel | Responsabilidade |
|---|---|
| Integrante 1 | Criar o repositório e adicionar colaboradores |
| Integrante 2 | Criar uma branch e desenvolver uma alteração |
| Integrante 3 | Criar outra branch e desenvolver outra alteração |
| Integrante 4 (se houver) | Revisar os Pull Requests e apoiar a integração |

Todos os integrantes devem participar das operações de Git. Os papéis podem ser alternados.

## Etapa 1: Criando um repositório no GitHub

**Objetivo:** criar um repositório remoto compartilhado.

### Passo 1: Criar o repositório

Acesse:

https://github.com/new

Configure:

- **Repository name:** `reserva-salas-grupo-X`
- **Description:** `Projeto colaborativo para prática de Git e GitHub`
- **Visibility:** Public
- **Add README:** habilitado

Substitua `X` pelo número do grupo.

Clique em **Create repository**.

> **Atenção:** como o repositório será público, não inclua senhas, tokens, dados pessoais ou informações confidenciais.

### Passo 2: Adicionar colaboradores

O responsável pelo repositório deverá acessar:

`Settings → Collaborators → Add people`

Convide os demais integrantes do grupo.

Cada integrante deverá aceitar o convite antes de tentar enviar alterações.

### Resultado esperado

Um repositório GitHub contendo o arquivo `README.md` e com acesso para todos os integrantes.

## Etapa 2: Clone, commit e push

**Objetivo:** copiar o repositório para o computador e registrar a primeira alteração.

### Passo 1: Clonar o repositório

Cada integrante deverá executar:

```bash
git clone https://github.com/USUARIO/reserva-salas-grupo-X.git
```

Substitua `USUARIO` pelo proprietário real do repositório e `X` pelo número do grupo.

**O que faz `git clone`?**

Cria uma cópia local de um repositório remoto, incluindo seus arquivos e histórico de versões.

### Passo 2: Acessar a pasta

```bash
cd reserva-salas-grupo-X
```

### Passo 3: Consultar o estado do repositório

```bash
git status
```

O comando informa a branch atual e identifica arquivos modificados, novos ou preparados para commit.

### Passo 4: Modificar o README

Um integrante deverá abrir o arquivo `README.md` e substituir seu conteúdo por:

```markdown
# Sistema de Reserva de Salas

## Descrição

Sistema para gerenciamento de reservas
de salas em uma universidade.

## Equipe

- Integrante 1
- Integrante 2
- Integrante 3

## Funcionalidades planejadas

- Cadastrar salas
- Solicitar reservas
- Cancelar reservas
```

Salve o arquivo.

### Passo 5: Registrar a alteração

Execute:

```bash
git add README.md
git commit -m "docs: adiciona descricao do projeto"
```

**O que fazem esses comandos?**

- `git add`: seleciona alterações para o próximo commit.
- `git commit`: registra as alterações selecionadas no histórico local do repositório.
- `-m`: define a mensagem que descreve o commit.

### Passo 6: Enviar ao GitHub

```bash
git push origin main
```

O comando envia os commits da branch local `main` para o repositório remoto `origin`.

> **Observação:** se o GitHub solicitar autenticação, utilize o mecanismo configurado em seu computador. Senhas comuns da conta não são aceitas para operações Git via HTTPS.

### Passo 7: Atualizar os demais computadores

Os outros integrantes deverão executar:

```bash
git pull origin main
```

Esse comando busca e integra as alterações da branch `main` remota na branch local atual.

### Resultado esperado

Todos os integrantes devem visualizar o mesmo arquivo `README.md` atualizado.

### Conceitos importantes

| Comando | Finalidade |
|:---|:---|
| `git clone` | Criar uma cópia local do repositório |
| `git status` | Verificar o estado dos arquivos |
| `git add` | Preparar alterações para commit |
| `git commit` | Registrar alterações localmente |
| `git push` | Enviar commits ao repositório remoto |
| `git pull` | Buscar e integrar alterações remotas |


## Etapa 3: Criando branches e utilizando checkout (20–30 min)

**Objetivo:** permitir que diferentes integrantes trabalhem simultaneamente sem modificar diretamente a branch principal.

### O que é uma branch?

Uma **branch** representa uma linha de desenvolvimento independente dentro de um repositório Git.

Branches permitem desenvolver funcionalidades, corrigir defeitos ou realizar experimentos sem alterar imediatamente a branch principal.

Neste tutorial, utilizaremos:

- `main`: branch principal do projeto.
- `feature/cadastro-salas`: desenvolvimento da funcionalidade de cadastro.
- `feature/cancelamento`: desenvolvimento da funcionalidade de cancelamento.

### Passo 1: Criar a primeira branch

O integrante 2 deverá executar:

```bash
git checkout -b feature/cadastro-salas
```

O comando cria uma nova branch e alterna para ela.

### Passo 2: Criar a segunda branch

O integrante 3 deverá executar, em seu próprio computador:

```bash
git checkout -b feature/cancelamento
```

### Passo 3: Verificar a branch ativa

```bash
git branch
```

O Git apresenta as branches locais. Um asterisco (`*`) indica a branch atual.

### Passo 4: Alternar entre branches

No computador do integrante 2:

```bash
git checkout main
git checkout feature/cadastro-salas
```

O primeiro comando retorna à branch principal.

O segundo retorna à branch de desenvolvimento.

> **Atenção:** o comando `git checkout` sem `-b` exige que a branch já exista localmente. Antes de alternar, salve ou registre alterações pendentes para evitar problemas.

### Resultado esperado

Os integrantes 2 e 3 devem estar trabalhando em branches diferentes.

### Conceitos importantes

| Comando | Finalidade |
|:---|:---|
| `git branch` | Listar branches locais |
| `git checkout -b nome` | Criar uma branch e alternar para ela |
| `git checkout nome` | Alternar para uma branch existente |


## Etapa 4: Commit e push nas branches

**Objetivo:** desenvolver alterações independentes e enviá-las ao GitHub.

### Integrante 2: Cadastro de salas

Na branch `feature/cadastro-salas`, crie o arquivo:

`cadastro-salas.md`

Adicione o conteúdo:

```markdown
# Cadastro de Salas

## Requisitos

- O administrador pode cadastrar uma sala.
- Cada sala deve possuir um identificador único.
- Cada sala deve informar sua capacidade.
- O sistema deve impedir salas duplicadas.
```

Salve e execute:

```bash
git add cadastro-salas.md
git commit -m "docs: especifica cadastro de salas"
git push -u origin feature/cadastro-salas
```

### Integrante 3: Cancelamento de reservas

Na branch `feature/cancelamento`, crie o arquivo:

`cancelamento.md`

Adicione:

```markdown
# Cancelamento de Reservas

## Requisitos

- O usuário pode cancelar suas reservas.
- O sistema registra a data do cancelamento.
- Reservas canceladas liberam o horário.
- O usuário recebe confirmação.
```

Salve e execute:

```bash
git add cancelamento.md
git commit -m "docs: especifica cancelamento"
git push -u origin feature/cancelamento
```

### O que significa `git push -u`?

A opção `-u` configura a associação entre a branch local e sua correspondente remota.

Após essa configuração, futuros envios podem ser realizados simplesmente com:

```bash
git push
```

### Passo de verificação

Acesse o repositório no GitHub.

Abra a lista de branches e confirme que existem:

- `main`
- `feature/cadastro-salas`
- `feature/cancelamento`

### Resultado esperado

Duas branches remotas contendo alterações independentes.


## Etapa 5: Pull Request, revisão e merge

**Objetivo:** integrar alterações de maneira controlada.

### O que é um Pull Request?

Um **Pull Request (PR)** é uma solicitação de integração de alterações de uma branch em outra.

No GitHub, o Pull Request permite:

- Visualizar as modificações propostas.
- Discutir decisões de implementação.
- Revisar o código ou os documentos.
- Solicitar correções.
- Integrar as alterações após a revisão.

### Passo 1: Criar um Pull Request

Acesse o repositório no GitHub.

Selecione:

`Pull requests → New pull request`

### Passo 2: Selecionar as branches

Configure:

- **Base:** `main`
- **Compare:** `feature/cadastro-salas`

Isso significa que as alterações da branch `feature/cadastro-salas` serão propostas para integração à `main`.

### Passo 3: Descrever o Pull Request

Utilize:

**Título:**

`Adiciona especificação de cadastro de salas`

**Descrição:**

```markdown
## Objetivo

Documentar os requisitos da funcionalidade
de cadastro de salas.

## Alterações

- Criação do arquivo cadastro-salas.md
- Definição dos requisitos de cadastro

## Verificação

- [x] Arquivo criado
- [x] Requisitos revisados
```

Clique em **Create pull request**.

### Passo 4: Revisar as alterações

Outro integrante deverá:

1. Abrir o Pull Request.
2. Acessar a aba `Files changed`.
3. Verificar as alterações realizadas.
4. Registrar um comentário de revisão.

Exemplo de comentário:

> Os requisitos estão claros. Sugiro que, futuramente, seja especificada uma regra para impedir o cadastro de salas com capacidade igual a zero.

### Passo 5: Realizar o merge

Após a revisão, o responsável deverá selecionar:

`Merge pull request → Confirm merge`

O GitHub integrará as alterações à branch principal, desde que não existam impedimentos à integração.

### Passo 6: Repetir o processo

Crie outro Pull Request:

- **Base:** `main`
- **Compare:** `feature/cancelamento`

Realize a revisão e o merge.

### Passo 7: Atualizar a branch principal local

Todos os integrantes deverão executar:

```bash
git checkout main
git pull origin main
```

### Resultado esperado

A branch `main` deverá conter:

```text
reserva-salas-grupo-X/
├── README.md
├── cadastro-salas.md
└── cancelamento.md
```

O GitHub deverá apresentar dois Pull Requests integrados.

### Reflexão

**Por que utilizar Pull Requests em vez de permitir que todos modifiquem diretamente a branch `main`?**

Pull Requests facilitam a revisão, a discussão, a rastreabilidade e a integração controlada das alterações.


## Exercícios avaliativos

Cada grupo deverá responder aos cinco exercícios.

As evidências e respostas deverão ser reunidas em **um único documento PDF**, acompanhado do link do repositório GitHub.

### Exercício 1: Repositório e colaboração

Apresente o link do repositório criado pelo grupo.

Identifique os integrantes e explique a diferença entre um repositório local e um repositório remoto.

**Evidência:** link e captura de tela do repositório no GitHub.

### Exercício 2: Histórico de commits

Identifique dois commits realizados durante o laboratório.

Para cada commit, informe:

1. Autor.
2. Mensagem.
3. Alteração realizada.

**Evidência:** captura de tela do histórico de commits e breve explicação.

### Exercício 3: Branches

Explique a finalidade das branches criadas durante o laboratório.

Responda:

1. Quais branches foram criadas?
2. Por que utilizar branches diferentes?
3. Qual é a diferença entre `git checkout -b` e `git checkout`?

**Evidência:** captura de tela das branches no GitHub e respostas.

### Exercício 4: Pull Request

Escolha um dos Pull Requests realizados pelo grupo.

Identifique:

1. Branch de origem.
2. Branch de destino.
3. Alterações propostas.
4. Revisão realizada.
5. Resultado do merge.

Explique brevemente o que acontece quando um Pull Request é integrado.

**Evidência:** link do Pull Request e captura de tela mostrando sua situação final.

## Instruções para entrega

**Formato:** um único arquivo PDF por grupo.

O documento deverá conter:

- Identificação dos integrantes.
- Link do repositório GitHub.
- Respostas dos cinco exercícios.
- Capturas de tela solicitadas.

**Nome do arquivo:**

`Grupo_X_Git_GitHub.pdf`

**Pontuação total:** 10 pontos.


## Encerramento

Ao concluir o laboratório, os estudantes deverão reconhecer que Git e GitHub apoiam a Gestão de Configuração de Software ao permitir:

- Controle de versões.
- Histórico e rastreabilidade de alterações.
- Desenvolvimento paralelo por meio de branches.
- Colaboração e revisão por Pull Requests.
- Integração controlada de mudanças.

O fluxo praticado foi:

```text
Criar repositório
       |
       v
     Clone
       |
       v
 Commit e Push
       |
       v
 Criar Branch
       |
       v
 Commit e Push
       |
       v
  Pull Request
       |
       v
  Revisão e Merge
       |
       v
 Branch principal atualizada
```

## Conexão com DevOps

O repositório Git pode servir como ponto de partida para pipelines de Integração Contínua (CI), que executam automaticamente testes e verificações sempre que alterações são enviadas ao GitHub.

Esse processo estabelece uma base para a automação da entrega de software.
