---
title: "Sistemas Distribuídos - Tutorial REST API"
collection: labs
type: "Lab"
permalink: /labs/rest-api-tutorial
date: 2026-05-13
location: "Ribeirão Preto, Brazil"
---

Vamos criar uma API simples com **FastAPI** e, em seguida, consumir essa API usando uma página **HTML com JavaScript**.

# Parte 1 — Criando a API com FastAPI

## 1. Instalação

No terminal, instale o FastAPI:

```bash
pip install "fastapi[standard]"
```


## 2. Criar o arquivo da API

Crie um arquivo chamado:

```bash
main.py
```



## 3. Código completo da API

```python
from fastapi import FastAPI
from pydantic import BaseModel

app = FastAPI()


class Produto(BaseModel):
    nome: str
    preco: float


produtos = []


@app.post("/produtos")
def criar_produto(produto: Produto):
    produtos.append(produto)
    return produto


@app.get("/produtos")
def listar_produtos():
    return produtos
```



## 4. Explicação didática

### Aplicação FastAPI

```python
app = FastAPI()
```

Cria a aplicação web.



### Modelo de dados

```python
class Produto(BaseModel):
    nome: str
    preco: float
```

Define o formato dos dados que a API vai receber.

Cada produto possui:

* `nome`: texto;
* `preco`: número decimal.

Exemplo de produto em JSON:

```json
{
  "nome": "Caneta",
  "preco": 2.5
}
```



### Armazenamento em memória

```python
produtos = []
```

Neste exemplo, os produtos serão armazenados apenas em uma lista.

Isso significa que, se a aplicação for reiniciada, os dados serão apagados.



### Rota para criar produto

```python
@app.post("/produtos")
def criar_produto(produto: Produto):
    produtos.append(produto)
    return produto
```

Essa rota recebe um produto e o adiciona à lista.



### Rota para listar produtos

```python
@app.get("/produtos")
def listar_produtos():
    return produtos
```

Essa rota retorna todos os produtos cadastrados.



## 5. Executar a API

No terminal, execute:

```bash
fastapi dev main.py
```



## 6. Testar no Swagger

Abra o navegador e acesse:

```text
http://127.0.0.1:8000/docs
```



## 7. Testar `GET /produtos`

1. Clique em `GET /produtos`.
2. Clique em **Try it out**.
3. Clique em **Execute**.

Resultado esperado:

```json
[]
```



## 8. Testar `POST /produtos`

1. Clique em `POST /produtos`.
2. Clique em **Try it out**.
3. Use o seguinte corpo da requisição:

```json
{
  "nome": "Caneta",
  "preco": 2.5
}
```

4. Clique em **Execute**.

Resultado esperado:

```json
{
  "nome": "Caneta",
  "preco": 2.5
}
```



## 9. Testar novamente `GET /produtos`

Resultado esperado:

```json
[
  {
    "nome": "Caneta",
    "preco": 2.5
  }
]
```



# Parte 2 — Consumindo a API com HTML e JavaScript

## 1. Objetivo da segunda parte

Agora que a API está funcionando, vamos criar uma página web simples para:

* cadastrar produtos usando um formulário HTML;
* enviar os dados para a API usando JavaScript;
* buscar a lista de produtos cadastrados;
* exibir os produtos na página.



## 2. Conceito importante

Na Parte 1, usamos o Swagger para testar a API.

Na Parte 2, vamos criar nosso próprio cliente web.

A comunicação será assim:

```text
Página HTML + JavaScript  >  API FastAPI
        Cliente                  Servidor
```

O JavaScript fará requisições HTTP para a API usando `fetch()`.



## 3. Criar o arquivo HTML

Na mesma pasta do projeto, crie um arquivo chamado:

```bash
index.html
```

A estrutura ficará assim:

```text
projeto/
├── main.py
└── index.html
```



## 4. Código completo do cliente HTML

```html
<!DOCTYPE html>
<html lang="pt-BR">
<head>
  <meta charset="UTF-8">
  <title>Produtos</title>
</head>
<body>

  <h1>Cadastro de Produtos</h1>

  <h2>Novo Produto</h2>

  <form id="form-produto">
    <label for="nome">Nome:</label>
    <input type="text" id="nome" required>

    <br><br>

    <label for="preco">Preço:</label>
    <input type="number" id="preco" step="0.01" required>

    <br><br>

    <button type="submit">Cadastrar</button>
  </form>

  <h2>Produtos Cadastrados</h2>

  <button onclick="carregarProdutos()">Atualizar lista</button>

  <ul id="lista-produtos"></ul>

  <script>
    const API_URL = "http://127.0.0.1:8000/produtos";

    const form = document.getElementById("form-produto");

    form.addEventListener("submit", async function(event) {
      event.preventDefault();

      const nome = document.getElementById("nome").value;
      const preco = parseFloat(document.getElementById("preco").value);

      const produto = {
        nome: nome,
        preco: preco
      };

      await fetch(API_URL, {
        method: "POST",
        headers: {
          "Content-Type": "application/json"
        },
        body: JSON.stringify(produto)
      });

      form.reset();

      carregarProdutos();
    });

    async function carregarProdutos() {
      const resposta = await fetch(API_URL);
      const produtos = await resposta.json();

      const lista = document.getElementById("lista-produtos");
      lista.innerHTML = "";

      produtos.forEach(function(produto) {
        const item = document.createElement("li");
        item.textContent = produto.nome + " - R$ " + produto.preco;
        lista.appendChild(item);
      });
    }
  </script>

</body>
</html>
```



# 5. Ajuste necessário na API: permitir acesso do navegador

Para que a página HTML consiga acessar a API, precisamos habilitar o **CORS**.

## Explicação didática

Por segurança, o navegador pode bloquear requisições feitas de uma página HTML para outro endereço.

Mesmo que ambos estejam no mesmo computador, o navegador entende que:

```text
index.html
```

e

```text
http://127.0.0.1:8000
```

são origens diferentes.

Por isso, precisamos permitir que o cliente HTML acesse a API.



## Código atualizado da API

Substitua o conteúdo de `main.py` por esta versão:

```python
from fastapi import FastAPI
from fastapi.middleware.cors import CORSMiddleware
from pydantic import BaseModel

app = FastAPI()

app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)


class Produto(BaseModel):
    nome: str
    preco: float


produtos = []


@app.post("/produtos")
def criar_produto(produto: Produto):
    produtos.append(produto)
    return produto


@app.get("/produtos")
def listar_produtos():
    return produtos
```



## Observação importante para os alunos

Nesta aula, usamos:

```python
allow_origins=["*"]
```

Isso permite acesso de qualquer origem.

Para uma aplicação real, o ideal é especificar quais endereços podem acessar a API, por exemplo:

```python
allow_origins=["http://127.0.0.1:5500"]
```



# 6. Executar a API

No terminal, execute:

```bash
fastapi dev main.py
```

A API ficará disponível em:

```text
http://127.0.0.1:8000
```



# 7. Abrir o arquivo HTML

Abra o arquivo `index.html` no navegador.

O professor pode fazer isso de duas formas simples:

## Opção 1 — Abrir diretamente

Clique duas vezes no arquivo `index.html`.

## Opção 2 — Usar a extensão Live Server

Se estiver usando VS Code, clique com o botão direito em `index.html` e selecione:

```text
Open with Live Server
```



# 8. Testar a página

Na página HTML:

1. Digite o nome do produto:

```text
Caneta
```

2. Digite o preço:

```text
2.5
```

3. Clique em **Cadastrar**.

Resultado esperado na página:

```text
Caneta - R$ 2.5
```

Depois cadastre outro produto:

```text
Caderno
18.9
```

Resultado esperado:

```text
Caneta - R$ 2.5
Caderno - R$ 18.9
```



# 9. Explicação do JavaScript

## Endereço da API

```javascript
const API_URL = "http://127.0.0.1:8000/produtos";
```

Essa constante guarda o endereço da rota da API.



## Captura do formulário

```javascript
const form = document.getElementById("form-produto");
```

Seleciona o formulário da página.



## Evento de envio

```javascript
form.addEventListener("submit", async function(event) {
  event.preventDefault();
```

Essa parte executa uma função quando o usuário clica em **Cadastrar**.

O comando:

```javascript
event.preventDefault();
```

impede que a página seja recarregada automaticamente.



## Criando o objeto produto

```javascript
const produto = {
  nome: nome,
  preco: preco
};
```

Aqui criamos um objeto JavaScript com os dados digitados pelo usuário.

Esse objeto tem a mesma estrutura esperada pela API:

```json
{
  "nome": "Caneta",
  "preco": 2.5
}
```

## Enviando dados para a API

```javascript
await fetch(API_URL, {
  method: "POST",
  headers: {
    "Content-Type": "application/json"
  },
  body: JSON.stringify(produto)
});
```

Essa parte envia o produto para a API.

* `method: "POST"` indica que estamos criando um novo produto.
* `Content-Type: application/json` informa que os dados estão em JSON.
* `JSON.stringify(produto)` transforma o objeto JavaScript em texto JSON.



## Buscando produtos da API

```javascript
const resposta = await fetch(API_URL);
const produtos = await resposta.json();
```

Aqui o JavaScript faz uma requisição `GET` para buscar os produtos cadastrados.

## Exibindo os produtos na página

```javascript
produtos.forEach(function(produto) {
  const item = document.createElement("li");
  item.textContent = produto.nome + " - R$ " + produto.preco;
  lista.appendChild(item);
});
```

Para cada produto recebido da API, criamos um item `<li>` e adicionamos esse item à lista da página.


# 10. Atividade Extra

Modificar o exemplo para cadastrar **alunos**.

Cada aluno deve ter:

```python
class Aluno(BaseModel):
    nome: str
    curso: str
```

A API deverá ter:

| Método | Rota      | Função          |
|  |  |  |
| `POST` | `/alunos` | Cadastrar aluno |
| `GET`  | `/alunos` | Listar alunos   |

A página HTML deverá permitir:

* digitar nome do aluno;
* digitar curso;
* cadastrar o aluno;
* listar os alunos cadastrados.

> Considere implementar os demais métodos de uma aplicação CRUD (Create, Read, Update, Delete).
