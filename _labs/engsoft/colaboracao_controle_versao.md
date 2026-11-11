---
title: "Engenharia de Software: Controle de Versão e Colaboração com Git e Github"
collection: labs
type: "Lab"
permalink: /labs/controle-versao-github
date: 2026-09-12
location: "Ribeirão Preto, Brazil"
---

**Entrega:** três links no e-disciplinas.

## Objetivo

Construir um cadastro simulado de salas e praticar o ciclo de desenvolvimento: implementar, testar, versionar, revisar e integrar. Ao final, o grupo terá um repositório GitHub com código, quatro testes automatizados e um workflow de integração contínua (CI).

Usaremos `main` como linha principal e apenas um branch de curta duração, `feature/cadastro`, integrado por um Pull Request (PR) revisado por outro integrante. Esse fluxo é uma aproximação didática de Trunk-Based Development.

## Preparação

Em um terminal, conferir:

```bash
git --version
python3 --version
```

Se necessário, configurar a identidade do Git com seus próprios dados:

```bash
git config --global user.name "Seu Nome"
git config --global user.email "seu-email-ou-noreply-do-github"
```

A identidade do commit não substitui a autenticação no GitHub. Não usar a senha da conta como senha do Git: deixar o acesso por HTTPS com gerenciador de credenciais ou por SSH preparado antes da aula.

Para antecipar o download das dependências, criar um ambiente fora do futuro repositório e mantê-lo ativo no terminal da atividade:

**Linux/macOS:**

```bash
python3 -m venv ../venv-lab-salas
source ../venv-lab-salas/bin/activate
python -m pip install pytest==8.3.5
python -m pytest --version
```

**Windows/PowerShell:**

```powershell
py -3.12 -m venv ..\venv-lab-salas
..\venv-lab-salas\Scripts\Activate.ps1
python -m pip install pytest==8.3.5
python -m pytest --version
```

Se a ativação estiver indisponível, usar o executável do ambiente no lugar de `python`: `../venv-lab-salas/bin/python` no Linux/macOS ou `..\venv-lab-salas\Scripts\python.exe` no Windows, considerando o caminho relativo à pasta atual. 

## Papéis e dinâmica

Trabalhar em **um único clone compartilhado**, em um computador, alternando quem opera o teclado. Todos acompanham as decisões. Não é necessário que cada integrante faça um commit ou crie um branch.

| Integrante | Responsabilidade |
|---|---|
| A | Criar e clonar o repositório; implementar o cadastro; abrir o PR. |
| B | Criar e executar os testes; relacionar cada teste às regras. |
| C | Configurar o GitHub Actions e acompanhar os logs. |
| D, se houver | Revisar o PR e organizar os links da entrega. |

Em trio, C também revisa o PR. A revisão deve ocorrer **pela conta de outro integrante**, em seu próprio navegador; o autor não aprova o próprio PR. Enquanto A e B trabalham no clone, C pode ler o workflow e D pode preparar a revisão, sem editar cópias concorrentes.

Copiar os blocos fornecidos e conferir os caminhos dos arquivos. Não é necessário digitá-los integralmente. Não há demonstração obrigatória de falha, criação de tags ou PRs adicionais.

## Escopo do cadastro

Aqui, “mock” é um cadastro simulado em memória (tecnicamente, um *fake*), sem banco de dados, servidor ou interface gráfica. Os dados desaparecem quando o programa termina.

As três regras são:

1. **Cadastrar:** receber um código e uma capacidade e devolver os dados da sala cadastrada.
2. **Rejeitar duplicado:** impedir um segundo cadastro com o mesmo código, preservando a sala original.
3. **Exigir capacidade positiva:** rejeitar capacidade zero ou negativa.

Para manter o escopo curto, os exemplos pressupõem código textual não vazio e capacidade inteira. Os códigos são comparados exatamente como recebidos: `A101` e `a101` são diferentes. Normalização e validação de outros tipos ficam fora desta atividade.

## Etapa 1: Preparar o repositório (5 minutos)

1. A cria no GitHub o repositório público `lab-cadastro-salas`, marcando **Add a README file**. Conferir que a branch principal se chama `main`.
2. Em **Settings → Collaborators**, convidar os colegas, que devem aceitar o convite.
3. Clonar e entrar na pasta. Substituir `USUARIO` pelo proprietário do repositório:

```bash
git clone https://github.com/USUARIO/lab-cadastro-salas.git
cd lab-cadastro-salas
git status
```

Manter o ambiente Python preparado antes da aula ativo. Os comandos seguintes são executados **na raiz do repositório**. Não criar os arquivos pela interface web do GitHub em paralelo ao clone.

## Etapa 2: Implementar o cadastro (8 minutos)

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

A explica ao grupo onde o código impede duplicidade e capacidade inválida. Os arquivos ainda estão sem commit; serão registrados juntos no branch da etapa 4.

## Etapa 3: Criar e executar os testes (7 minutos)

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

Criar também `requirements-dev.txt` na raiz:

```text
pytest==8.3.5
```

E `.gitignore` na raiz:

```text
.venv/
venv/
__pycache__/
.pytest_cache/
*.py[cod]
.DS_Store
```

Instalar as dependências declaradas e executar:

```bash
python -m pip install -r requirements-dev.txt
python -m pytest -q
```

Resultado esperado: **`4 passed`**. São quatro funções de teste, sem parametrização: um cadastro válido, uma duplicidade, capacidade zero e capacidade negativa. Cada teste cria um cadastro independente.

## Etapa 4: Versionar no branch da funcionalidade (5 minutos)

A cria o branch **antes do primeiro commit dos arquivos novos**. Como eles ainda não foram registrados, permanecem disponíveis no branch criado:

```bash
git checkout -b feature/cadastro
git status
git add salas.py tests/test_salas.py requirements-dev.txt .gitignore
git diff --cached
git commit -m "feat: adiciona cadastro de salas e quatro testes"
git push -u origin feature/cadastro
```

`checkout -b` cria e seleciona o branch; `add` prepara os arquivos; `commit` registra uma versão local; `push` publica essa versão. Conferir no GitHub que os arquivos estão em `feature/cadastro`. A `main` ainda contém apenas o README inicial.

## Etapa 5: Configurar a CI (7 minutos)

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

A CI instala as dependências em um ambiente novo e executa o mesmo comando usado localmente. O primeiro push da etapa 4 não tinha workflow; é esperado que ele não tenha execução de CI. O push desta etapa já inclui código, testes e workflow.

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

Se a revisão encontrar um erro, corrigir no mesmo clone e no mesmo branch, executar os testes, fazer novo commit e push. O PR é atualizado automaticamente; aguardar a nova CI e nova conferência do revisor. Não criar outro PR para a correção.

## Etapa 7: Sincronizar e entregar (3 minutos)

Após o merge, sincronizar o clone compartilhado:

```bash
git checkout main
git pull --ff-only origin main
python -m pytest -q
git status
```

Resultado esperado: `4 passed` e árvore de trabalho limpa. Na aba **Actions**, conferir também a execução disparada por **push na `main`** após o merge; ela deve terminar verde com quatro testes aprovados.

Um integrante envia no campo de texto da atividade do Moodle:

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

- **Um clone, um branch de trabalho:** os responsáveis alternam o teclado. A revisão ocorre por outra conta no GitHub. Não é preciso sincronizar três implementações nem abrir PRs separados para código, testes e CI.
- **Outros clones:** quem quiser conferir em seu próprio computador deve aguardar o merge, clonar o repositório ou executar `git checkout main` e `git pull --ff-only origin main` com a árvore de trabalho limpa. Preparar seu ambiente Python antes de testar. Não executar `pull` sobre alterações locais pendentes; usar `git status` e pedir orientação.
- **Duas execuções podem aparecer:** com `push` e `pull_request` ativos, um push em branch com PR aberto pode disparar ambos os eventos. Conferir branch, evento e commit para não usar um resultado antigo como evidência.
- **CI vermelha:** abrir o primeiro passo com falha. Conferir caminho de `requirements-dev.txt`, indentação do YAML, localização dos testes e erros nos logs. Corrigir no branch do PR e enviar novo commit. Não integrar com falha conhecida.
- **CI em fila:** enquanto aguarda, realizar a revisão e organizar os links. A fila do GitHub pode ultrapassar o tempo planejado. Se houver indisponibilidade, avisar o professor e registrar a execução pendente; completar a evidência no prazo que ele definir. Teste local aprovado não significa CI verde.
- **Regra de merge:** neste laboratório, o grupo aguarda revisão e CI verde. O GitHub só impede tecnicamente o merge por falha quando há regra de proteção com check obrigatório; essa configuração não faz parte dos 40 minutos.
- **Escopo da automação:** o workflow executa integração contínua; não publica nem implanta o programa. A versão direta do pytest está fixada, mas o arquivo de dependências não é um lock completo de dependências transitivas.

## Referências de apoio

- [Ação oficial actions/checkout](https://github.com/actions/checkout/tree/releases/v6)
- [Ação oficial actions/setup-python](https://github.com/actions/setup-python/tree/v6)
- [Eventos que iniciam workflows](https://docs.github.com/en/actions/reference/workflows-and-actions/events-that-trigger-workflows)
