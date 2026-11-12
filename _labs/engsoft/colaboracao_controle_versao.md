---
title: "Engenharia de Software: Controle de Versão e Colaboração"
collection: labs
type: "Lab"
permalink: /labs/controle-versao-colaboracao
date: 2026-11-12
location: "Ribeirão Preto, Brazil"
---

## Objetivo

Construir um cadastro simulado de salas e praticar o ciclo de desenvolvimento: implementar, testar, versionar, revisar e integrar. Ao final, o grupo terá um repositório GitHub com código, quatro testes automatizados e um workflow de integração contínua (CI).

Usaremos `main` como linha principal e apenas um branch de curta duração, `feature/cadastro`, integrado por um Pull Request (PR) revisado por outro integrante. Esse fluxo é uma aproximação didática de Trunk-Based Development.

## Preparação

Conferir no terminal:

```bash
git --version
python3 --version
```

No Windows, conferir Python com `py -3.12 --version`. 

> **Importante**: Cada integrante deve criar uma conta GitHub.

Configurar a identidade de cada integrante com seus próprios dados:

```bash
git config --global user.name "Seu Nome"
git config --global user.email "seu-email-ou-noreply-do-github"
```

A identidade do commit não substitui a autenticação no GitHub. Deixar preparado o acesso por HTTPS com gerenciador de credenciais ou por SSH. Não usar a senha da conta como senha do Git.

## Papéis e dinâmica de colaboração

**Dinâmica principal: uma máquina por integrante.** Cada pessoa usa sua conta GitHub e um clone local do mesmo repositório. O grupo trabalha em um único branch remoto, `feature/cadastro`, e abre um único PR para `main`.

| Integrante | Responsabilidade |
|---|---|
| A | Criar o repositório, convidar colegas, publicar o cadastro e a configuração inicial; abrir e integrar o PR. |
| B | Sincronizar o cadastro, criar e executar os quatro testes; publicar os testes e revisar o PR em trio. |
| C | Sincronizar código e testes, publicar o workflow e conferir a CI. |
| D, se houver | Revisar o PR e organizar os links da entrega. |

**Ordem de publicação: A → B → C.** Cada responsável avisa ao grupo quando concluir seu push. O próximo só começa a editar os arquivos de sua etapa depois de atualizar o clone. Enquanto aguarda, pode ler os blocos do roteiro e preparar anotações fora do repositório. Não criar commits em paralelo nem editar os mesmos arquivos em máquinas diferentes.

O branch é compartilhado no GitHub, mas cada clone tem sua própria cópia local. A cria `feature/cadastro`; B e C passam a acompanhar esse mesmo branch com os comandos indicados adiante. Não criar branches individuais adicionais. Cada commit usa a identidade de quem o realiza.

**Plano B: computadores compartilhados.** Se não houver uma máquina para cada integrante, usar um clone por computador disponível e alternar quem opera o teclado. No mesmo clone, não recriar um branch que já existe: usar `git checkout feature/cadastro`. Antes do commit, conferir a identidade com `git config user.name` e `git config user.email`; se necessário, configurá-la apenas nesse repositório com `git config user.name "Seu Nome"` e `git config user.email "Seu Email"`. A revisão continua sendo enviada pela conta GitHub de outro integrante. Não é obrigatório um commit por pessoa nesse plano.

## Escopo do cadastro

Aqui, "mock" é um cadastro simulado em memória (tecnicamente, um *fake*), sem banco de dados, servidor ou interface gráfica. Os dados desaparecem quando o programa termina.

As três regras são:

1. **Cadastrar:** receber um código e uma capacidade e devolver os dados da sala cadastrada.
2. **Rejeitar duplicado:** impedir um segundo cadastro com o mesmo código, preservando a sala original.
3. **Exigir capacidade positiva:** rejeitar capacidade zero ou negativa.

Para manter o escopo curto, os exemplos pressupõem código textual não vazio e capacidade inteira. Os códigos são comparados exatamente como recebidos: `A101` e `a101` são diferentes. Normalização e validação de outros tipos ficam fora desta atividade.

## Etapa 1: Preparar o repositório e os clones (5 minutos)

1. A cria no GitHub o repositório público `lab-cadastro-salas`, marcando **Add a README file**. Conferir que a branch principal é `main`.
2. Em **Settings → Collaborators**, A convida os colegas; cada um aceita o convite usando sua própria conta.
3. Todos clonam o mesmo repositório em suas máquinas. Substituir `USUARIO` pelo proprietário, inclusive nos computadores dos colaboradores:

```bash
git clone https://github.com/USUARIO/lab-cadastro-salas.git
cd lab-cadastro-salas
git status
```

Cada integrante cria e ativa seu ambiente na raiz do próprio clone.

**Linux/macOS:**

```bash
python3 -m venv .venv
source .venv/bin/activate
python -m pip install pytest==8.3.5
```

**Windows/PowerShell:**

```powershell
py -3.12 -m venv .venv
.\.venv\Scripts\Activate.ps1
python -m pip install pytest==8.3.5
```

Se não for possível ativar, usar `.venv/bin/python` no Linux/macOS ou `.\.venv\Scripts\python.exe` no Windows no lugar de `python` nos próximos comandos. Manter os terminais na raiz dos respectivos clones. Não criar arquivos pela interface web do GitHub em paralelo às alterações locais.

## Etapa 2: Implementar o cadastro (8 minutos)

**No computador de A**, criar e selecionar o branch antes de editar:

```bash
git checkout main
git pull --ff-only origin main
git checkout -b feature/cadastro
```

A cria `salas.py` com o código completo:

```python
"""Cadastro simulado: cada instância guarda suas salas em memória."""


class CadastroSalas:
    def __init__(self):
        self._salas = {}

    def cadastrar(self, codigo: str, capacidade: int) -> dict:
        if capacidade <= 0:
            raise ValueError("Capacidade deve ser positiva")
        if codigo in self._salas:
            raise ValueError("Sala já cadastrada")
        sala = {"codigo": codigo, "capacidade": capacidade}
        self._salas[codigo] = sala
        return sala.copy()


if __name__ == "__main__":
    cadastro = CadastroSalas()
    print(cadastro.cadastrar("A101", 30))
```

Executar:

```bash
python salas.py
```

Saída esperada:

```text
{'codigo': 'A101', 'capacidade': 30}
```

A cria também `requirements-dev.txt` na raiz:

```text
pytest==8.3.5
```

E `.gitignore` na raiz, para impedir que ambientes e caches sejam versionados:

```text
.venv/
venv/
__pycache__/
.pytest_cache/
*.py[cod]
.DS_Store
```

A explica onde o código impede duplicidade e capacidade inválida e publica os arquivos:

```bash
git status
git add salas.py requirements-dev.txt .gitignore
git diff --cached
git commit -m "feat: implementa cadastro de salas em memória"
git push -u origin feature/cadastro
```

A avisa: **cadastro publicado; B pode sincronizar**. A `main` ainda contém apenas o README. Não há testes nem workflow nesse primeiro push.

## Etapa 3: Criar e executar os testes (7 minutos)

**No computador de B**, após o aviso de A, obter o branch remoto:

```bash
git fetch origin
git checkout -b feature/cadastro --track origin/feature/cadastro
python -m pip install -r requirements-dev.txt
python salas.py
```

Esse `checkout -b` é usado apenas na primeira obtenção do branch nesse clone. Se o branch local já existir, usar `git checkout feature/cadastro` e `git pull --ff-only origin feature/cadastro`, com a árvore de trabalho limpa.

B cria a pasta `tests` pelo editor e o arquivo `tests/test_salas.py`:

```python
import pytest

from salas import CadastroSalas


def test_cadastra_sala():
    cadastro = CadastroSalas()
    assert cadastro.cadastrar("A101", 30) == {
        "codigo": "A101",
        "capacidade": 30,
    }


def test_rejeita_duplicado_e_preserva_original():
    cadastro = CadastroSalas()
    cadastro.cadastrar("A101", 30)
    with pytest.raises(ValueError, match="Sala já cadastrada"):
        cadastro.cadastrar("A101", 50)
    # A tentativa rejeitada não deve sobrescrever a capacidade original.
    assert cadastro._salas["A101"] == {"codigo": "A101", "capacidade": 30}


def test_rejeita_capacidade_zero():
    cadastro = CadastroSalas()
    with pytest.raises(ValueError, match="Capacidade deve ser positiva"):
        cadastro.cadastrar("A101", 0)
    # A tentativa rejeitada não deve reservar o código.
    assert cadastro.cadastrar("A101", 30)["capacidade"] == 30


def test_rejeita_capacidade_negativa():
    cadastro = CadastroSalas()
    with pytest.raises(ValueError, match="Capacidade deve ser positiva"):
        cadastro.cadastrar("A101", -1)
    assert cadastro.cadastrar("A101", 30)["capacidade"] == 30
```

O acesso a `_salas` no teste de duplicidade é uma simplificação didática para conferir a preservação dos dados sem acrescentar uma operação de consulta ao exercício.

Instalar as dependências declaradas e executar:

```bash
python -m pip install -r requirements-dev.txt
python -m pytest -q
```

Resultado esperado: **`4 passed`**. São quatro funções de teste, sem parametrização: um cadastro válido, uma duplicidade, capacidade zero e capacidade negativa. Cada teste cria um cadastro independente.

## Etapa 4: Conferir e publicar os testes (5 minutos)

**B continua no próprio computador**, no branch `feature/cadastro` obtido na etapa 3. Enquanto B trabalha, A e C não enviam commits para esse branch.

```bash
git branch --show-current
python -m pytest -q
git status
git add tests/test_salas.py
git diff --cached
git commit -m "test: cobre cadastro duplicidade e capacidade positiva"
git push origin feature/cadastro
```

Conferir `feature/cadastro`, `4 passed` e apenas os arquivos previstos no commit. B avisa: **testes publicados; C pode sincronizar**.

`add` prepara arquivos; `commit` registra uma versão local; `push` publica essa versão no branch remoto. Não usar `git add .` indiscriminadamente nem `push --force`. O `-u` usado na criação do branch local configura seu acompanhamento remoto.

## Etapa 5: Configurar a CI (7 minutos)

**No computador de C**, após o aviso de B, obter código e testes:

```bash
git fetch origin
git checkout -b feature/cadastro --track origin/feature/cadastro
python -m pip install -r requirements-dev.txt
python -m pytest -q
```

Se o branch já existir nesse clone, substituir os dois primeiros comandos por `git checkout feature/cadastro` e `git pull --ff-only origin feature/cadastro`, com a árvore de trabalho limpa. Conferir **4 passed** antes de criar o workflow.

C cria, pelo editor, as pastas `.github/workflows` e o arquivo `.github/workflows/ci.yml`. Manter espaços na indentação, sem tabulações:

```yaml
name: CI Python

on:
  push:
  pull_request:

permissions:
  contents: read

jobs:
  testes:
    runs-on: ubuntu-latest
    timeout-minutes: 5
    steps:
      - name: Obter código
        uses: actions/checkout@v6
      - name: Preparar Python
        uses: actions/setup-python@v6
        with:
          python-version: "3.12"
      - name: Instalar dependências
        run: python -m pip install -r requirements-dev.txt
      - name: Executar testes
        run: python -m pytest -q
```

Ainda no mesmo branch `feature/cadastro`, executar:

```bash
python -m pytest -q
git add .github/workflows/ci.yml
git diff --cached
git commit -m "ci: executa pytest em push e pull request"
git push origin feature/cadastro
```

1. Abrir a aba **Actions** do repositório.
2. Abrir a execução **CI Python** do último push em `feature/cadastro`.
3. Abrir o job **testes** e o passo **Executar testes**. Conferir `4 passed` e conclusão verde.

A CI instala as dependências em um ambiente novo e executa o mesmo comando usado localmente. Os pushes das etapas 2 e 4 não tinham workflow; é esperado que eles não tenham execução de CI. O push desta etapa já inclui código, testes e workflow.

Enquanto a CI executa, preparar o título e a descrição do PR da próxima etapa.

## Etapa 6: Revisar e integrar um único PR (5 minutos)

1. A abre **Pull requests → New pull request** com **base `main`** e **compare `feature/cadastro`**.
2. Usar o título `Adiciona cadastro de salas com testes e CI` e a descrição:

```text
Implementa cadastro em memória, rejeição de duplicidade e capacidade positiva.
Inclui quatro testes pytest e CI em push e pull_request.
Validação local: python -m pytest -q → 4 passed.
```

3. D (ou C no trio), autenticado com sua própria conta e com acesso de colaborador, abre **Files changed**. Confere as três regras, os quatro testes e o comando do workflow. Registra um comentário técnico, por exemplo: “Conferi que a tentativa de cadastro duplicado preserva a capacidade original”. Usa **Review changes → Approve → Submit review**, se estiver correto.
4. Na página do PR, aguardar os checks do **commit mais recente** ficarem verdes. Abrir o check de CI e confirmar `4 passed`. A abertura do PR dispara outra execução por `pull_request`.
5. Após revisão e CI verde, A usa **Merge pull request → Confirm merge**. Conferir o estado **Merged**. Se houver opção, usar **Create a merge commit**.

Se a revisão encontrar um erro, o grupo escolhe um responsável pela correção. Esse integrante seleciona `feature/cadastro`, atualiza com `git pull --ff-only origin feature/cadastro` antes de editar, corrige, executa os testes, faz novo commit e push. Os demais aguardam o aviso de conclusão. O PR é atualizado automaticamente; aguardar a nova CI e nova conferência do revisor. Não criar outro PR para a correção.

## Etapa 7: Sincronizar e entregar (3 minutos)

Após o merge, **cada integrante**, em seu próprio clone e com a árvore de trabalho limpa, sincroniza a `main`:

```bash
git checkout main
git pull --ff-only origin main
python -m pytest -q
git status
```

Resultado esperado: `4 passed` e árvore de trabalho limpa. Na aba **Actions**, conferir também a execução disparada por **push na `main`** após o merge; ela deve terminar verde com quatro testes aprovados.

Um integrante envia no campo de texto da atividade do e-disciplinas (Moodle):

```text
Equipe: NOME (USUARIO_GITHUB), NOME (USUARIO_GITHUB), ...
Repositório: https://github.com/USUARIO/lab-cadastro-salas
PR revisado e integrado: https://github.com/USUARIO/lab-cadastro-salas/pull/NUMERO
CI verde da main após o merge: https://github.com/USUARIO/lab-cadastro-salas/actions/runs/ID
```

Copiar os endereços reais do navegador. O link de CI deve abrir uma **execução específica**, associada ao merge entregue, e não apenas a aba Actions. **Não entregar PDF, capturas de tela ou relatório adicional.**

## Conferência da entrega

- Repositório público com `salas.py`, quatro testes, dependências e workflow.
- Um PR de `feature/cadastro` para `main`, com revisão de outro integrante e estado **Merged**.
- Execução verde de CI na `main`, após o merge, com **quatro testes aprovados**.

Estrutura final esperada:

```text
lab-cadastro-salas/
├── README.md
├── .gitignore
├── requirements-dev.txt
├── salas.py
├── tests/
│   └── test_salas.py
└── .github/
    └── workflows/
        └── ci.yml
```

O README é o arquivo criado inicialmente pelo GitHub. Não é necessário ampliá-lo nesta atividade.

## Notas rápidas: sincronização e CI

- **Sincronização entre máquinas:** um push não atualiza os outros clones. Antes de editar, selecionar o branch correto e executar `git pull --ff-only origin feature/cadastro` com a árvore de trabalho limpa. Respeitar a ordem A → B → C. Depois do merge, todos atualizam `main`.
- **Push rejeitado:** não usar `--force`. Ler `git status` e avisar o grupo. Com a árvore de trabalho limpa, tentar `git pull --ff-only origin feature/cadastro`. Se houver divergência de commits ou alterações locais pendentes, interromper os envios e pedir orientação ao professor para integrar as alterações; não apagar trabalho para liberar o push.
- **Plano B:** em um mesmo clone, o branch já selecionado e os arquivos são compartilhados pelos operadores. Não repetir `checkout -b` para um branch existente. Em computadores diferentes, cada clone precisa buscar as alterações remotas.
- **Duas execuções podem aparecer:** com `push` e `pull_request` ativos, um push em branch com PR aberto pode disparar ambos os eventos. Conferir branch, evento e commit para não usar um resultado antigo como evidência.
- **CI vermelha:** abrir o primeiro passo com falha. Conferir caminho de `requirements-dev.txt`, indentação do YAML, localização dos testes e erros nos logs. Corrigir no branch do PR e enviar novo commit. Não integrar com falha conhecida.
- **CI em fila:** enquanto aguarda, realizar a revisão e organizar os links. A fila do GitHub pode ultrapassar o tempo planejado. Se houver indisponibilidade, avisar o professor e registrar a execução pendente; completar a evidência no prazo que ele definir. Teste local aprovado não significa CI verde.
- **Regra de merge:** neste laboratório, o grupo aguarda revisão e CI verde. O GitHub só impede tecnicamente o merge por falha quando há regra de proteção com check obrigatório; essa configuração não faz parte dos 40 minutos.
- **Escopo da automação:** o workflow executa integração contínua; não publica nem implanta o programa. A versão direta do pytest está fixada, mas o arquivo de dependências não é um lock completo de dependências transitivas.

## Referências de apoio

- [Ação oficial actions/checkout](https://github.com/actions/checkout/tree/releases/v6)
- [Ação oficial actions/setup-python](https://github.com/actions/setup-python/tree/v6)
- [Eventos que iniciam workflows](https://docs.github.com/en/actions/reference/workflows-and-actions/events-that-trigger-workflows)
