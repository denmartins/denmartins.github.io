---
title: "Engenharia de Software: Tutorial básico de Controle de Versão de Software"
collection: labs
type: "Lab"
permalink: /labs/tutorial-vcs
date: 2026-11-12
location: "Ribeirão Preto, Brazil"
---

Ao final, você conseguirá registrar versões de arquivos, publicar alterações no GitHub e colaborar por meio de branches e Pull Requests. Usaremos apenas arquivos de texto.

## 1. Criar sua conta no GitHub

1. Abra [github.com/signup](https://github.com/signup).
2. Siga o cadastro, escolha seu nome de usuário e conclua as verificações solicitadas.
3. Confirme seu endereço de email pela mensagem enviada pelo GitHub.
4. Entre na conta e confira seu perfil. Anote seu nome de usuário: ele aparecerá nos endereços dos seus repositórios.
5. Use a conta gratuita para esta atividade. Configure a autenticação de dois fatores nas configurações de segurança e guarde seus códigos de recuperação em local seguro.

Cada estudante deve usar sua própria conta. Não compartilhe senhas com colegas. A documentação oficial explica o [cadastro e a verificação do email](https://docs.github.com/en/account-and-profile/how-tos/account-management/creating-an-account-on-github).

## 2. Instalar o Git e abrir o terminal

**Git** é a ferramenta que registra o histórico de versões na sua máquina. **GitHub** é o serviço que hospeda repositórios e oferece recursos de colaboração, como revisão de alterações. É possível usar Git localmente, sem estar conectado ao GitHub.

- **Windows:** instale o Git pelo [site oficial](https://git-scm.com/install/windows). Depois, abra o **Git Bash**. Os comandos deste tutorial podem ser executados nele.
- **macOS:** abra o Terminal e execute `git --version`. Se o sistema solicitar a instalação das ferramentas de linha de comando, conclua-a. Outras opções estão na [página de instalação](https://git-scm.com/install/mac).
- **Linux:** instale pelo gerenciador de pacotes da distribuição. Em Ubuntu/Debian, use os comandos abaixo. Consulte as [opções oficiais](https://git-scm.com/install/linux) para outras distribuições.

```bash
sudo apt update
sudo apt install git
```

Os comandos com `sudo` são apenas para instalação no Linux; não os use para os exercícios seguintes. Em computadores institucionais, a instalação pode depender do suporte técnico.

Em qualquer sistema, confira:

```bash
git --version
```

Deve aparecer uma versão, como `git version ...`. Se o comando não for reconhecido após a instalação, feche e reabra o terminal.

### Localizar-se no terminal

Execute uma linha por vez e pressione Enter. Não copie símbolos de prompt, como `$`, se eles aparecerem em outros materiais.

```bash
pwd
mkdir pratica-git
cd pratica-git
```

`pwd` mostra a pasta atual; `mkdir` cria uma pasta; `cd` entra nela. Usaremos `pratica-git` para organizar os exercícios. Para subir uma pasta, use `cd ..`. Caminhos com espaços devem ficar entre aspas, por exemplo `cd "Minha Pasta"`.

## 3. Configurar a identidade dos commits

Um **commit** registra uma versão de arquivos, com mensagem, autoria e identificador. Configure seus próprios dados:

```bash
git config --global user.name "Seu Nome"
git config --global user.email "seu-email@example.com"
```

Substitua os exemplos. Use um email verificado na sua conta GitHub ou copie o endereço privado `noreply` mostrado em **Settings → Emails**. Não invente um endereço `noreply`.

Confira:

```bash
git config --global user.name
git config --global user.email
```

`--global` aplica a configuração aos repositórios desse usuário do computador. Em uma conta de sistema compartilhada, configure por repositório, sem `--global`, depois de criá-lo. A configuração identifica a autoria; ela **não faz login no GitHub**.

## 4. Praticar Git localmente: criar, editar e registrar

Na pasta `pratica-git`, crie um projeto local:

```bash
mkdir historico-local
cd historico-local
git init -b main
git status
```

`git init` transforma a pasta em um repositório. A opção `-b main` dá o nome `main` ao branch inicial. Um **branch** é uma linha de desenvolvimento. A pasta oculta `.git` contém os dados do histórico; não a apague nem edite seus arquivos manualmente.

### Criar a primeira versão

Abra essa pasta no editor de sua preferência. Crie `anotacoes.md` com o texto:

```markdown
# Minhas anotações

Git registra versões do projeto.
```

Salve o arquivo e execute:

```bash
git status
git add anotacoes.md
git diff --cached
git commit -m "docs: registra primeiras anotações"
git log --oneline
```

Observe a sequência:

| Ação | O que acontece |
|---|---|
| Salvar no editor | Altera o arquivo na pasta de trabalho. |
| `git add` | Seleciona o conteúdo atual do arquivo para o próximo commit. |
| `git diff --cached` | Mostra o que foi selecionado. |
| `git commit` | Registra a versão selecionada no histórico local. |

Salvar um arquivo não cria um commit. Fazer commit também não publica arquivos na internet. O identificador exibido por `git log` representa aquele commit; o seu será diferente do dos colegas.

### Registrar uma segunda versão

Acrescente ao final de `anotacoes.md` e salve:

```text
GitHub facilita a colaboração entre pessoas.
```

Execute:

```bash
git diff
git add anotacoes.md
git diff --cached
git commit -m "docs: acrescenta o papel do GitHub"
git log --oneline
git status
```

`git diff` mostra alterações ainda não selecionadas. No diff, linhas com `+` foram adicionadas e com `-` foram removidas. Ao final, o histórico deve conter dois commits e `git status` deve indicar que a árvore de trabalho está limpa.

Se você editar um arquivo depois de executar `git add`, execute `git add` novamente para incluir a edição mais recente. Se um histórico longo abrir em um visualizador no terminal, pressione `q` para sair.

## 5. Preparar a autenticação com o GitHub

Para enviar commits, você precisa autenticar sua conta. A senha usada no site não é aceita como senha de operações Git por HTTPS. O GitHub orienta usar GitHub CLI ou Git Credential Manager para esse acesso. [Documentação de autenticação](https://docs.github.com/en/get-started/git-basics/caching-your-github-credentials-in-git).

Neste tutorial, usaremos **GitHub CLI**, uma ferramenta adicional cujo comando é `gh`. O Git continua sendo usado para versionar; `gh` ajudará no login.

1. Instale o GitHub CLI seguindo as instruções para seu sistema em [cli.github.com](https://cli.github.com/).
2. Feche e reabra o terminal, se necessário.
3. Execute:

```bash
gh --version
gh auth login
```

No assistente, escolha:

- Conta no **GitHub.com**.
- Protocolo **HTTPS** para operações Git.
- Autenticar o Git com suas credenciais do GitHub, respondendo **Yes**, quando perguntado.
- Login por navegador, seguindo o código e as instruções mostrados no terminal.

Conclua o login na sua própria conta e confira:

```bash
gh auth status
```

Se necessário, configure a integração após o login:

```bash
gh auth setup-git
```

Não cole senhas, tokens ou códigos de autenticação no repositório ou em mensagens para colegas. Em máquina compartilhada, encerre a sessão com `gh auth logout` e saia também da conta no navegador ao terminar.

Se o computador já tiver Git Credential Manager configurado e o acesso por navegador estiver funcionando, você pode usar esse mecanismo sem instalar `gh`. Não altere uma configuração institucional sem orientação. [Referência de `gh auth login`](https://cli.github.com/manual/gh_auth_login).

## 6. Criar um repositório no GitHub e cloná-lo

Agora começaremos um **segundo projeto**, destinado à colaboração. O exercício local anterior permanece separado; não copie sua pasta `.git` para o novo projeto.

1. No GitHub, selecione **New repository**.
2. Informe o nome `tutorial-colaboracao`.
3. Escolha **Public**, para facilitar a conferência pelo professor. Não inclua dados pessoais sensíveis.
4. Marque a opção de adicionar um **README** e crie o repositório.
5. Confira que o branch principal é `main`.
6. No botão **Code**, copie o endereço **HTTPS**.

O `README.md` apresenta o projeto e pode conter instruções de uso. Como o GitHub o criou, o repositório remoto já tem um commit inicial.

Se você ainda está em `pratica-git/historico-local`, volte à pasta `pratica-git`:

```bash
cd ..
```

Substitua `PROPRIETARIO` pelo usuário que criou o repositório e execute:

```bash
git clone https://github.com/PROPRIETARIO/tutorial-colaboracao.git
cd tutorial-colaboracao
git status
git remote -v
git branch --show-current
```

**Clone** é uma cópia local do repositório, incluindo seu histórico. `origin` é o nome atribuído por padrão ao remoto de onde você clonou. Cada máquina terá uma cópia independente; alterações não aparecem automaticamente nos outros computadores.

Não use `git init` dentro da pasta clonada: ela já é um repositório. A partir daqui, execute os comandos na raiz de `tutorial-colaboracao`.

## 7. Criar um branch, fazer commit e publicar

Antes de iniciar, atualize a linha principal com a árvore de trabalho limpa:

```bash
git checkout main
git pull --ff-only origin main
git checkout -b feature/apresentacao
git branch --show-current
```

`checkout -b` cria e seleciona um branch. O nome exibido deve ser `feature/apresentacao`. O branch permite preparar uma mudança antes de integrá-la à `main`.

Crie `apresentacao.md` no editor:

```markdown
# Apresentação da equipe

Estamos aprendendo controle de versão e colaboração.

## Objetivo

Registrar alterações e revisar o trabalho em equipe.
```

Salve e publique:

```bash
git status
git add apresentacao.md
git diff --cached
git commit -m "docs: adiciona apresentação da equipe"
git push -u origin feature/apresentacao
```

`push` envia os commits locais para o remoto. `-u` configura o acompanhamento entre o branch local e o remoto. No GitHub, selecione `feature/apresentacao` para conferir o arquivo. Ele ainda não está na `main`.

Use mensagens que expliquem a alteração. Evite mensagens como `coisas` ou `atualização`. O prefixo `docs:` é apenas uma convenção adotada nos exemplos.

## 8. Colaborar em dupla: convidar, revisar e integrar

Nesta etapa, **A** é quem criou o repositório e publicou `feature/apresentacao`. **B** será o revisor, usando outra máquina e sua própria conta.

### A convida B

1. A abre **Settings → Collaborators** no repositório e convida B pelo nome de usuário.
2. B aceita o convite antes de tentar publicar ou aprovar alterações.
3. B clona o mesmo endereço HTTPS em seu computador e entra na pasta:

```bash
git clone https://github.com/PROPRIETARIO/tutorial-colaboracao.git
cd tutorial-colaboracao
```

B usa o usuário de **A** em `PROPRIETARIO`, pois ambos trabalham no mesmo repositório. Se já o tiver clonado, não repete o clone.

### A abre um Pull Request

1. A abre **Pull requests → New pull request**.
2. Seleciona **base: `main`** e **compare: `feature/apresentacao`**.
3. Confere o diff e cria o PR com o título `Adiciona apresentação da equipe`.
4. Na descrição, explica o que mudou e como conferiu o resultado.

Um **Pull Request (PR)** é uma proposta de integração e um espaço para discutir e revisar alterações. Abrir o PR não faz o merge automaticamente. Um PR também não é o comando `git pull`.

### B revisa e A integra

1. B abre o PR no navegador e consulta **Files changed**.
2. Confere o conteúdo, a clareza e se foram incluídos somente os arquivos previstos.
3. Deixa um comentário específico, por exemplo: “O objetivo está claro; sugiro explicar quem faz a revisão”.
4. Se estiver correto, usa **Review changes → Approve → Submit review**. O autor não aprova o próprio PR.
5. Se precisar de ajuste, A edita no branch `feature/apresentacao`, faz novo commit e push. O mesmo PR será atualizado; B confere novamente.
6. Após a aprovação, A usa **Merge pull request → Confirm merge**. Se disponível, escolhe **Create a merge commit** para este exercício.

Neste tutorial não configuramos testes automatizados nem CI. A revisão confere os arquivos. No laboratório de cadastro de salas, a revisão será acompanhada pelos testes e pelo GitHub Actions.

### Todos sincronizam depois do merge

Com as alterações locais registradas e a árvore de trabalho limpa, A e B executam em suas respectivas máquinas:

```bash
git checkout main
git pull --ff-only origin main
git log --oneline --graph --all -10
git status
```

Ambos devem encontrar `apresentacao.md` na `main`. O merge no GitHub não atualiza sozinho os clones locais.

## 9. Exercício de fixação: inverter os papéis

Agora B será o autor e A fará a revisão. No computador de B, após sincronizar a `main`:

```bash
git checkout -b docs/participantes
```

B acrescenta ao arquivo `apresentacao.md` uma seção com os nomes ou usuários da dupla. Salva, confere e publica:

```bash
git diff
git add apresentacao.md
git diff --cached
git commit -m "docs: identifica participantes da equipe"
git push -u origin docs/participantes
```

B abre um PR de `docs/participantes` para `main`; A revisa. Depois do merge, ambos atualizam a `main`. Ao final, cada pessoa terá praticado autoria e revisão.

Essa atividade usa um branch para cada mudança. No laboratório de 40 minutos, o grupo usará um único branch compartilhado, conforme a próxima seção.

## 10. Conexão com o laboratório: compartilhar um branch entre máquinas

No laboratório, A, B e C usarão `feature/cadastro`, com publicações na ordem **A → B → C**. Cada um continua com sua própria conta e seu clone. O branch remoto é o mesmo; os branches locais são cópias em máquinas distintas.

Depois que A criar e publicar o branch, B e C o obtêm, cada um no seu turno:

```bash
git fetch origin
git checkout -b feature/cadastro --track origin/feature/cadastro
```

`fetch` atualiza as referências do remoto sem incorporar automaticamente as mudanças aos arquivos de trabalho. O segundo comando cria o branch local acompanhando o remoto. Ele só é usado na primeira obtenção desse branch no clone.

Se o branch local já existir, antes de começar a editar e com a árvore de trabalho limpa:

```bash
git checkout feature/cadastro
git pull --ff-only origin feature/cadastro
```

Depois de editar e validar, cada responsável faz commit de seus arquivos, envia com `git push origin feature/cadastro` e avisa ao próximo. Não devem existir commits concorrentes nesse exercício. `--ff-only` permite a atualização direta e recusa uma integração automática quando os históricos divergem.

Não execute comandos com `feature/cadastro` no repositório deste tutorial: eles são uma preparação para o repositório do laboratório.

## 11. Arquivos que não devem ser versionados

Crie um arquivo chamado `.gitignore` na raiz do projeto para indicar arquivos gerados ou específicos da máquina. Em um projeto Python, por exemplo:

```text
.venv/
__pycache__/
.pytest_cache/
*.py[cod]
.DS_Store
```

O `.gitignore` deve ser versionado. Ele não remove do histórico arquivos que já tenham sido registrados. Não publique senhas, tokens ou arquivos com credenciais; se ocorrer uma exposição, avise o professor e revogue a credencial, pois apagar o arquivo depois não apaga as versões anteriores.

## 12. Resolver dúvidas e erros comuns

| Situação | Como proceder |
|---|---|
| `git` não reconhecido | Conferir a instalação e reabrir o terminal. |
| `not a git repository` | Usar `pwd` e entrar na pasta clonada com `cd`. |
| Git pede nome ou email | Configurar `user.name` e `user.email` e repetir o commit. |
| `nothing to commit` | Conferir se o arquivo foi salvo, se está na pasta correta e se já foi registrado. |
| `Authentication failed` ou acesso negado | Conferir conta, autenticação, endereço do remoto e convite de colaborador. |
| `Repository not found` | Conferir a URL e o acesso à conta/repositório. |
| Branch local já existe | Usar `git checkout NOME`, sem `-b`, e conferir o estado antes de atualizar. |
| Push rejeitado por atualização remota | Não usar `--force`; seguir a orientação abaixo. |

**Se o push for rejeitado:** execute `git status` e avise a equipe. Se você não criou commits locais divergentes e a árvore estiver limpa, `git pull --ff-only origin NOME_DO_BRANCH` pode atualizar sua cópia. Se você e o colega fizeram commits diferentes, o comando recusará a atualização. Nesse caso, peça orientação para integrar os históricos; não apague commits nem force o envio.

**Se aparecer conflito:** o Git precisa de uma decisão sobre alterações incompatíveis. Use `git status` para localizar os arquivos, combine a solução com o colega, edite o resultado e remova os marcadores `<<<<<<<`, `=======` e `>>>>>>>`. Em um merge em andamento, revise o arquivo, execute `git add ARQUIVO` e finalize com `git commit`. Peça acompanhamento do professor na primeira ocorrência; não resolva escolhendo uma versão sem ler o conteúdo.

## 13. Consulta rápida de comandos

Nos exemplos abaixo, substitua nomes como `ARQUIVO`, `BRANCH` e `URL`; não os copie literalmente.

| Comando | Finalidade |
|---|---|
| `git init -b main` | Iniciar um repositório local novo. |
| `git clone URL` | Obter uma cópia de um repositório existente. |
| `git status` | Conferir branch e estado dos arquivos. |
| `git diff` | Ver alterações ainda não selecionadas. |
| `git add ARQUIVO` | Selecionar conteúdo para o próximo commit. |
| `git diff --cached` | Conferir conteúdo selecionado. |
| `git commit -m "Mensagem"` | Registrar uma versão local. |
| `git log --oneline` | Consultar o histórico resumido. |
| `git checkout -b BRANCH` | Criar e selecionar um branch. |
| `git checkout BRANCH` | Selecionar um branch já existente. |
| `git fetch origin` | Buscar referências e objetos do remoto. |
| `git pull --ff-only origin BRANCH` | Buscar e atualizar diretamente o branch atual, quando possível. |
| `git push -u origin BRANCH` | Publicar e configurar acompanhamento remoto. |
| `git push origin BRANCH` | Enviar os commits do branch ao remoto. |
| `git remote -v` | Conferir endereços dos remotos. |

O Git também oferece `git switch main` para selecionar um branch e `git switch -c BRANCH` para criar e selecionar. Neste tutorial usamos `checkout` para manter consistência com o laboratório.

## 14. Conferência de aprendizagem

Antes de iniciar o laboratório, verifique se você consegue:

- Entrar na sua conta GitHub e autenticar operações na linha de comando.
- Distinguir salvar, selecionar com `add`, registrar com `commit` e publicar com `push`.
- Clonar um repositório e identificar a pasta em que está trabalhando.
- Consultar o histórico e reconhecer o branch atual.
- Criar um branch, publicar uma alteração e abrir um PR.
- Revisar uma mudança de colega e atualizar seu clone após o merge.
- Explicar por que é necessário sincronizar antes de editar em um branch compartilhado.

**Perguntas para discussão:** um commit já está no GitHub antes do push? O merge realizado no navegador atualiza seu computador? Qual a diferença entre `git pull` e um Pull Request?

## Referências oficiais

- [Cadastro no GitHub](https://docs.github.com/en/account-and-profile/how-tos/account-management/creating-an-account-on-github).
- [Instalação do Git](https://git-scm.com/book/en/v2/Getting-Started-Installing-Git).
- [Configuração inicial do Git](https://git-scm.com/book/en/v2/Getting-Started-First-Time-Git-Setup).
- [Fundamentos de branches e merges](https://git-scm.com/book/en/v2/Git-Branching-Basic-Branching-and-Merging).
- [Autenticação HTTPS e armazenamento de credenciais](https://docs.github.com/en/get-started/git-basics/caching-your-github-credentials-in-git).
- [GitHub CLI: login](https://cli.github.com/manual/gh_auth_login).
