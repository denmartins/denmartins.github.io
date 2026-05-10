---
title: "Sistemas Distribuídos - Lab Prático SOAP Web Service"
collection: labs
type: "Lab"
permalink: /labs/web-services-soap
date: 2026-05-07
location: "Ribeirão Preto, Brazil"
---

Neste laboratório, você irá implementar um **serviço web SOAP em Python** para simular a consulta de dados de alunos em um sistema acadêmico.

Ao final da atividade, você deverá ser capaz de:

* Implementar um serviço SOAP simples em Python.
* Disponibilizar operações por meio de um serviço web.
* Acessar o documento **WSDL** gerado pelo serviço.
* Criar um cliente Python para consumir o serviço SOAP.
* Compreender, na prática, a relação entre **serviço**, **contrato**, **requisição** e **resposta**.

Neste laboratório, usaremos a biblioteca **Spyne** para criar o servidor SOAP e a biblioteca **Zeep** para consumir o serviço como cliente. O Spyne permite expor serviços com APIs bem definidas, enquanto o Zeep lê o WSDL e gera uma interface Python para consumir serviços SOAP.


## Cenário do laboratório

Imagine que uma universidade possui um sistema acadêmico interno com dados de alunos. Outros sistemas, como o portal do aluno ou o sistema da secretaria, precisam consultar essas informações.

Em vez de acessar diretamente o banco de dados, esses sistemas irão consumir um **serviço SOAP** com as seguintes operações:

| Operação | Descrição |
|:---- |:----|
| `consultar_aluno`| Consulta o nome e o curso de um aluno a partir do ID |
| `verificar_matricula_ativa` | Verifica se a matrícula do aluno está ativa |
| `listar_alunos`| Retorna uma lista simples com os alunos cadastrados  |


## Estrutura esperada do projeto

Crie uma pasta chamada `laboratorio-soap-python`.

Dentro dela, crie os seguintes arquivos:

```text
laboratorio-soap-python/
│
├── servidor.py
├── cliente.py
└── requirements.txt
```


## Passo 1 — Criar o ambiente virtual

Abra o terminal na pasta do projeto e execute:

```bash
python -m venv venv
```

Ative o ambiente virtual.

No Windows:

```bash
venv\Scripts\activate
```

No macOS ou Linux:

```bash
source venv/bin/activate
```



## Passo 2 — Criar o arquivo `requirements.txt`

Crie o arquivo `requirements.txt` com o seguinte conteúdo:

```txt
spyne
zeep
lxml
```

Instale as dependências:

```bash
pip install -r requirements.txt
```

A biblioteca Zeep é um cliente SOAP em Python que inspeciona o documento WSDL e cria uma interface programática para o serviço. A documentação também indica que sua instalação pode ser feita com `pip install zeep`. ([Zeep Documentation][2])



## Passo 3 — Implementar o servidor SOAP

Crie o arquivo `servidor.py` com o código abaixo:

```python
from spyne import Application, ServiceBase, rpc
from spyne import Integer, Unicode, Boolean, Iterable
from spyne.protocol.soap import Soap11
from spyne.server.wsgi import WsgiApplication

from wsgiref.simple_server import make_server


class ServicoAcademico(ServiceBase):
    """
    Serviço SOAP que simula operações básicas de um sistema acadêmico.
    """

    alunos = {
        101: {
            "nome": "Ana Souza",
            "curso": "Sistemas de Informação",
            "matricula_ativa": True
        },
        102: {
            "nome": "Bruno Lima",
            "curso": "Ciência da Computação",
            "matricula_ativa": True
        },
        103: {
            "nome": "Carla Mendes",
            "curso": "Engenharia de Software",
            "matricula_ativa": False
        }
    }

    @rpc(Integer, _returns=Unicode)
    def consultar_aluno(ctx, id_aluno):
        """
        Consulta os dados de um aluno pelo ID.

        Parâmetro:
            id_aluno: código numérico do aluno.

        Retorno:
            Texto com nome e curso do aluno.
        """

        aluno = ServicoAcademico.alunos.get(id_aluno)

        if aluno is None:
            return f"Aluno com ID {id_aluno} não encontrado."

        return f"{aluno['nome']} - {aluno['curso']}"

    @rpc(Integer, _returns=Boolean)
    def verificar_matricula_ativa(ctx, id_aluno):
        """
        Verifica se a matrícula do aluno está ativa.

        Parâmetro:
            id_aluno: código numérico do aluno.

        Retorno:
            True se a matrícula estiver ativa; False caso contrário.
        """

        aluno = ServicoAcademico.alunos.get(id_aluno)

        if aluno is None:
            return False

        return aluno["matricula_ativa"]

    @rpc(_returns=Iterable(Unicode))
    def listar_alunos(ctx):
        """
        Lista todos os alunos cadastrados.

        Retorno:
            Lista de textos contendo ID, nome e curso.
        """

        for id_aluno, dados in ServicoAcademico.alunos.items():
            yield f"{id_aluno} - {dados['nome']} - {dados['curso']}"


aplicacao = Application(
    [ServicoAcademico],
    tns="http://exemplo.com/servico-academico",
    in_protocol=Soap11(validator="lxml"),
    out_protocol=Soap11()
)

wsgi_app = WsgiApplication(aplicacao)


if __name__ == "__main__":
    servidor = make_server("127.0.0.1", 8000, wsgi_app)

    print("Servidor SOAP em execução.")
    print("Acesse o WSDL em: http://127.0.0.1:8000/?wsdl")
    print("Pressione CTRL+C para encerrar.")

    servidor.serve_forever()
```



## Entendendo o código do servidor

Observe os principais elementos do código:

| Parte do código | Função |
|:----|:-----|
| `ServiceBase`                   | Classe base para definir um serviço                       |
| `@rpc`                          | Decorador usado para expor métodos como operações remotas |
| `Integer`, `Unicode`, `Boolean` | Tipos de dados usados no contrato SOAP                    |
| `Application`                   | Define a aplicação SOAP                                   |
| `Soap11`                        | Define o uso do protocolo SOAP 1.1                        |
| `WsgiApplication`               | Permite executar o serviço como aplicação WSGI            |
| `make_server`                   | Cria um servidor HTTP simples para testes locais          |

O uso de `Application`, `rpc`, `ServiceBase`, `Soap11` e `WsgiApplication` é compatível com a estrutura apresentada na documentação e exemplos do Spyne para criação de serviços SOAP em Python.



## Passo 4 — Executar o servidor

No terminal, com o ambiente virtual ativado, execute:

```bash
python servidor.py
```

Se tudo estiver correto, você verá uma mensagem semelhante a:

```text
Servidor SOAP em execução.
Acesse o WSDL em: http://127.0.0.1:8000/?wsdl
Pressione CTRL+C para encerrar.
```



## Passo 5 — Acessar o WSDL

Abra o navegador e acesse:

```text
http://127.0.0.1:8000/?wsdl
```

Você deverá visualizar um documento XML descrevendo o serviço.

Esse documento é o **WSDL**. Ele funciona como o contrato do serviço, informando quais operações estão disponíveis, quais parâmetros são esperados e quais tipos de dados serão retornados.



## Questão para reflexão

Após abrir o WSDL no navegador, responda:

1. O WSDL é escrito em qual formato?
2. Quais operações aparecem no WSDL?
3. O que o WSDL permite que um cliente saiba antes de consumir o serviço?



## Passo 6 — Implementar o cliente SOAP

Agora crie o arquivo `cliente.py` com o código abaixo:

```python
from zeep import Client


URL_WSDL = "http://127.0.0.1:8000/?wsdl"


def main():
    cliente = Client(URL_WSDL)

    print("Cliente SOAP criado com sucesso.")
    print()

    print("1. Consultando aluno 101")
    resultado = cliente.service.consultar_aluno(101)
    print("Resultado:", resultado)
    print()

    print("2. Verificando matrícula do aluno 101")
    matricula_ativa = cliente.service.verificar_matricula_ativa(101)
    print("Matrícula ativa?", matricula_ativa)
    print()

    print("3. Verificando matrícula do aluno 103")
    matricula_ativa = cliente.service.verificar_matricula_ativa(103)
    print("Matrícula ativa?", matricula_ativa)
    print()

    print("4. Listando alunos cadastrados")
    alunos = cliente.service.listar_alunos()

    for aluno in alunos:
        print(aluno)
    print()

    print("5. Consultando aluno inexistente")
    resultado = cliente.service.consultar_aluno(999)
    print("Resultado:", resultado)


if __name__ == "__main__":
    main()
```



## Passo 7 — Executar o cliente

Mantenha o servidor em execução em um terminal.

Abra outro terminal na mesma pasta do projeto, ative o ambiente virtual e execute:

```bash
python cliente.py
```

Saída esperada:

```text
Cliente SOAP criado com sucesso.

1. Consultando aluno 101
Resultado: Ana Souza - Sistemas de Informação

2. Verificando matrícula do aluno 101
Matrícula ativa? True

3. Verificando matrícula do aluno 103
Matrícula ativa? False

4. Listando alunos cadastrados
101 - Ana Souza - Sistemas de Informação
102 - Bruno Lima - Ciência da Computação
103 - Carla Mendes - Engenharia de Software

5. Consultando aluno inexistente
Resultado: Aluno com ID 999 não encontrado.
```



## Entendendo o código do cliente

No cliente, a linha abaixo cria um consumidor SOAP a partir do WSDL:

```python
cliente = Client(URL_WSDL)
```

A partir disso, é possível chamar as operações como se fossem métodos Python:

```python
cliente.service.consultar_aluno(101)
```

O Zeep recupera o WSDL informado e usa esse contrato para permitir chamadas ao serviço SOAP.


# Atividade prática

Agora modifique o serviço para incluir uma nova operação chamada:

```python
consultar_curso
```

Essa operação deve:

* Receber o ID de um aluno.
* Retornar apenas o curso do aluno.
* Retornar a mensagem `"Aluno não encontrado."` caso o ID não exista.



## Orientação para implementação

No arquivo `servidor.py`, adicione o seguinte método dentro da classe `ServicoAcademico`:

```python
@rpc(Integer, _returns=Unicode)
def consultar_curso(ctx, id_aluno):
    aluno = ServicoAcademico.alunos.get(id_aluno)

    if aluno is None:
        return "Aluno não encontrado."

    return aluno["curso"]
```

Depois, reinicie o servidor:

```bash
python servidor.py
```

No arquivo `cliente.py`, adicione uma chamada para testar a nova operação:

```python
print("6. Consultando curso do aluno 102")
curso = cliente.service.consultar_curso(102)
print("Curso:", curso)
```



## Resultado esperado da nova operação

Ao executar o cliente, você deverá obter algo semelhante a:

```text
6. Consultando curso do aluno 102
Curso: Ciência da Computação
```

Teste também com um aluno inexistente:

```python
curso = cliente.service.consultar_curso(999)
print("Curso:", curso)
```

Resultado esperado:

```text
Curso: Aluno não encontrado.
```



# Desafio extra

Implemente uma nova operação chamada:

```python
calcular_media
```

A operação deve:

* Receber três notas do aluno.
* Calcular a média aritmética.
* Retornar a média como texto.
* Se alguma nota for menor que 0 ou maior que 10, retornar a mensagem `"Nota inválida."`.

Como o foco deste laboratório é SOAP e não validação avançada, utilize tipos simples.

Sugestão de assinatura:

```python
@rpc(Float, Float, Float, _returns=Unicode)
def calcular_media(ctx, nota1, nota2, nota3):
    ...
```

Para isso, será necessário importar `Float`:

```python
from spyne import Float
```



## Exemplo de comportamento esperado

Chamada no cliente:

```python
media = cliente.service.calcular_media(8.0, 7.5, 9.0)
print(media)
```

Saída esperada:

```text
Média: 8.17
```

Chamada com nota inválida:

```python
media = cliente.service.calcular_media(8.0, 11.0, 9.0)
print(media)
```

Saída esperada:

```text
Nota inválida.
```
