---
title: "Laboratório Prático: Github Actions"
collection: labs
type: "Lab"
permalink: /labs/github-actions
date: 2026-05-27
location: "Ribeirão Preto, Brazil"
---

## Seção 1: Introdução às GitHub Actions

### Conceitos Fundamentais

**CI/CD (Continuous Integration / Continuous Delivery)** são práticas que automatizam a integração de código, testes e entrega de software.
As **GitHub Actions** permitem definir fluxos automatizados (*workflows*) diretamente no repositório.

### Componentes Principais

| Termo            | Definição                                                    |
| ---------------- | ------------------------------------------------------------ |
| **Workflow**     | Conjunto de automações definido em YAML.                     |
| **Job**          | Conjunto de *steps* executados em um mesmo ambiente.         |
| **Step**         | Ação individual (ex.: executar script, instalar pacote).     |
| **Runner**       | Máquina virtual onde o workflow é executado.                 |
| **Trigger (on)** | Evento que dispara o workflow (ex.: `push`, `pull_request`). |
| **Secrets**      | Variáveis seguras armazenadas no repositório.                |
| **Permissions**  | Controle de acesso para execução e escrita em branches.      |

### Anatomia de um Workflow YAML

```yaml
# .github/workflows/hello.yml
name: Hello World Workflow

on: [push]  # Dispara sempre que um push é realizado

jobs:
  greet:
    runs-on: ubuntu-latest  # Runner do GitHub
    steps:
      - name: Checkout do código
        uses: actions/checkout@v4

      - name: Exibir mensagem de boas-vindas
        run: echo "👋 Hello, GitHub Actions!"
```

### Demonstração “Hello World”

1. Crie um repositório no Github com o nome HelloActions.
1. Crie o diretório `.github/workflows/` no repositório.
2. Adicione o arquivo `hello.yml` conforme o exemplo acima.
3. Faça um `git add`, `commit` e `push`.
4. Acesse a aba **Actions** no GitHub e observe a execução.

---

## Dicas

> - Antes de Prosseguir, siga o tutorial introdutório em https://learn.microsoft.com/pt-br/training/modules/introduction-to-github-actions/
> - **Leia também**: https://docs.github.com/pt/actions/get-started
> - **Vídeo no YouTube**: [O que é CI e CD? Pra vc aprender e nunca mais esquecer! | Como usar GitHub Actions?](https://youtu.be/IKjcdYQvcDo?si=9vIHSSJDI-31mBaq)

---

## Preparação para os exercícios

Para cada uma das atividades abaixo, crie um arquivo `requirements.txt` correspondente. Você pode seguir o exemplo abaixo:

```
pytest>=7.0
pytest-cov>=4.0
pandas>=2.0
numpy>=1.24
scikit-learn>=1.4
pypandoc>=1.13
```
---

## Seção 2: Executando Testes Unitários em uma Aplicação Python Simples

### Introdução ao `pytest`

O **`pytest`** é um dos frameworks mais populares e poderosos para **testes automatizados em Python**, amplamente utilizado tanto em projetos de software quanto em pipelines de **Ciência de Dados e Machine Learning**.
Ele permite escrever **testes simples e legíveis**, automatizar a execução em múltiplos ambientes e integrar-se facilmente a ferramentas de **Integração Contínua (CI)**, como o GitHub Actions.

Principais vantagens do `pytest`:

* **Sintaxe enxuta:** testes são funções Python comuns cujo nome começa com `test_`.
* **Mensagens de erro detalhadas:** relatórios claros sem necessidade de `assertEquals` ou classes de teste.
* **Detecção automática:** o `pytest` encontra e executa todos os arquivos que seguem o padrão `test_*.py`.
* **Integração fácil com CI/CD:** basta chamar `pytest` em um *workflow* para automatizar a verificação da qualidade do código.
* **Extensibilidade:** suporte a *plugins* (como `pytest-cov` para cobertura de testes).

Exemplo mínimo de teste com `pytest`:

```python
def soma(a, b):
    return a + b

def test_soma():
    assert soma(2, 3) == 5
```

Ao executar `pytest` no terminal, o resultado esperado é semelhante a:

```
$ pytest
===================== test session starts =====================
collected 1 item
test_example.py .                                         [100%]
====================== 1 passed in 0.01s ======================
```

### Estrutura de Repositório Recomendada


Crie um novo repositório no Github com a seguinte estrutura:

```
myapp/
│
├── app/
│   └── calculator.py
├── tests/
│   └── test_calculator.py
├── requirements.txt
└── .github/workflows/tests.yml
```

### Código de Exemplo

```python
# app/calculator.py
def soma(a, b):
    """Retorna a soma entre a e b."""
    return a + b
```

```python
# tests/test_calculator.py
from app.calculator import soma

def test_soma():
    """Verifica se a função soma retorna o valor correto."""
    assert soma(2, 3) == 5
```

### Workflow de Teste Automatizado

```yaml
# .github/workflows/tests.yml
name: Testes Unitários Python

on: [push, pull_request]

jobs:
  test:
    runs-on: ubuntu-latest

    steps:
      - uses: actions/checkout@v4

      - name: Configurar Python
        uses: actions/setup-python@v5
        with:
          python-version: "3.11"

      - name: Instalar dependências
        run: |
          python -m pip install --upgrade pip
          pip install -r requirements.txt
          pip install pytest

      - name: Executar testes
        run: pytest --maxfail=1 --disable-warnings -q
```

### Boas Práticas

* Utilize **nomes descritivos** para as funções de teste e adicione **docstrings**.
* Use **cache** de dependências com `actions/cache` para reduzir o tempo de build.
* Armazene **artefatos** (logs, relatórios) com `actions/upload-artifact` para auditoria posterior.

---

## Exercício 1 – Action da Pipeline de Machine Learning

Desenvolva um **workflow automatizado** que, a cada *push* no repositório, execute um script de Machine Learning e gere um **relatório de classificação**.
O relatório deve conter **acurácia, precisão, recall e F1-score**, sendo salvo como `report.txt` e disponibilizado como artefato no GitHub.

### Estrutura Esperada

```
ml-pipeline/
├── data/sample.csv
├── train.py
├── requirements.txt
└── .github/workflows/ml.yml
```

### Código-esqueleto `train.py`

```python
# train.py
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LogisticRegression
from sklearn.metrics import classification_report

# 1. Leitura dos dados
df = pd.read_csv("data/sample.csv")

X = df.drop("target", axis=1)
y = df["target"]

# 2. Divisão dos dados
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# 3. Treinamento do modelo
model = LogisticRegression()
model.fit(X_train, y_train)

# 4. Avaliação
y_pred = model.predict(X_test)
report = classification_report(y_test, y_pred)

# 5. Salvamento do relatório
with open("report.txt", "w") as f:
    f.write(report)
```

### Template do Workflow

```yaml
# .github/workflows/ml.yml
name: ML Pipeline

on: [push]

jobs:
  train-model:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v4
      - name: Configurar Python
        uses: actions/setup-python@v5
        with:
          python-version: "3.11"

      - name: Instalar dependências
        run: |
          pip install -r requirements.txt

      - name: Executar treinamento
        run: python train.py

      - name: Upload do relatório
        uses: actions/upload-artifact@v4
        with:
          name: classification-report
          path: report.txt
```

---

## Exercício 2 – Action Pandoc Markdown → PDF Slides

Implemente um **workflow GitHub Actions** que monitore a pasta `docs/` e converta automaticamente arquivos Markdown em **PDF de slides** usando **Pandoc**.
O PDF deve ser publicado como artefato ou enviado a uma branch `slides-output`.

### Estrutura Esperada

```
docs/
├── presentation.md
└── pandoc.yaml
.github/
└── workflows/
    └── slides.yml
```

### Exemplo de `presentation.md`

```markdown
# Introdução à Automação
## O que é CI/CD?
- Integração Contínua
- Entrega Contínua

## Por que usar GitHub Actions?
- Automatização
- Reprodutibilidade
```

### Exemplo de Workflow

```yaml
# .github/workflows/slides.yml
name: Gerar Slides PDF

on:
  push:
    paths:
      - "docs/*.md"

jobs:
  build-slides:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v4

      - name: Instalar Pandoc
        run: sudo apt-get update && sudo apt-get install -y pandoc texlive

      - name: Converter Markdown em PDF
        run: |
          pandoc docs/presentation.md -o slides.pdf --slide-level=2 --pdf-engine=xelatex

      - name: Publicar Artefato
        uses: actions/upload-artifact@v4
        with:
          name: slides-pdf
          path: slides.pdf
```

### Observações

* **Dependências:** a instalação do LaTeX pode ser demorada; use runners Ubuntu-latest.
* **Erros comuns:** arquivos ausentes, encoding incorreto e versões antigas do Pandoc.
* **Extensão:** configure `gh-pages` para publicação automática.

---

## Referências & Leitura Adicional

* **GitHub Docs – Actions:** [https://docs.github.com/actions](https://docs.github.com/actions)
* **Continuous Integration for Data Science Projects** – Towards Data Science, 2024.
* **scikit-learn – Classification Metrics:** [https://scikit-learn.org/stable/modules/model_evaluation.html](https://scikit-learn.org/stable/modules/model_evaluation.html)
* **Pandoc User Guide:** [https://pandoc.org/MANUAL.html](https://pandoc.org/MANUAL.html)
* **PyTest Documentation:** [https://docs.pytest.org/en/stable/](https://docs.pytest.org/en/stable/)
