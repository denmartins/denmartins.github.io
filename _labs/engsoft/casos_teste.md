---
title: "Engenharia de Software: Casos de Teste"
collection: labs
type: "Lab"
permalink: /labs/casos-de-teste
date: 2026-11-04
location: "Ribeirão Preto, Brazil"
---

## 1. Objetivos

Vocês são responsáveis pela qualidade dos testes de um sistema universitário de reservas de salas. Um modelo de IA (LLM) será usado para implementar os testes, mas **o grupo deverá definir o que testar e verificar se o código gerado atende ao que foi especificado**.

Ao final, vocês deverão conseguir:

- Transformar requisitos em casos de teste com resultados esperados verificáveis.
- Comunicar à IA o contexto, os dados e as restrições de implementação.
- Relacionar cada teste gerado ao seu caso de origem.
- Examinar asserções, dependências e isolamento dos testes.
- Verificar se a suíte detecta um defeito introduzido de propósito.

**Regra da atividade:** escrevam e salvem a primeira versão dos casos **antes** de solicitar código à IA. Depois, podem revisar a especificação, desde que registrem o que mudou e por quê. Um teste aprovado não é, por si só, evidência de que o caso foi implementado corretamente.

**Pré-requisitos:** reconhecer variáveis, funções, listas e condições; ter Python 3.10 ou superior e acesso a um LLM já disponíveis. O código completo está na seção 3: não é necessário reconstruir o sistema a partir de outro material. A cópia do código é uma preparação guiada; o trabalho avaliado é a especificação e a auditoria.

## 2. Contexto: o sistema em camadas

A arquitetura separa responsabilidades para facilitar compreensão, mudança e teste. O serviço recebe o repositório no construtor, permitindo conectar memória, SQLite ou um mock. 

| Parte | Arquivo | Responsabilidade |
|---|---|---|
| Domínio | `dominio.py` | `Reserva`: validar dados e identificar conflitos |
| Aplicação | `aplicacao.py` | `ServicoReservas`: normalizar dados, converter datas e coordenar a reserva |
| Infraestrutura | `infraestrutura.py` | Armazenar em memória ou SQLite |
| Apresentação e composição | `main.py` | Conectar os componentes e apresentar a demonstração |

O serviço usa somente `listar()` e `adicionar()` do objeto recebido. Ele não conhece SQL. **Testar o serviço com um mock é possível antes de existir SQLite**; testar persistência exige usar a implementação e o banco reais. Nesta atividade, ambos os repositórios já são fornecidos para permitir a auditoria completa em 45 minutos.

### Requisitos que definem os resultados esperados

| ID | Requisito |
|---|---|
| R1 | Sala e responsável não podem ser vazios nem conter somente espaços. |
| R2 | O término deve ser posterior ao início. |
| R3 | Reservas da mesma sala não podem se sobrepor; reservas consecutivas são permitidas. |
| R4 | O serviço remove espaços nas extremidades e converte o nome da sala para maiúsculas antes de verificar conflitos e gravar. |
| R5 | Com SQLite, uma reserva gravada deve ser recuperável por outro repositório conectado ao mesmo arquivo, preservando sala, responsável, início e fim. |

Usem datas fixas e horários locais sem fuso. O recorte não implementa autenticação, capacidade, cancelamento ou duração máxima. Não inventem esses requisitos.

### 2.1 Guia rápido para ler o código

| Elemento | Significado |
|---|---|
| `class Reserva:` | Define o tipo dos objetos de reserva. |
| `__init__(self, ...)` | Prepara o objeto quando chamamos `Reserva(...)`. |
| `self.sala` | Campo que guarda a sala daquele objeto. |
| Método | Operação de um objeto, como `conflita_com()`. |
| `raise ValueError(...)` | Sinaliza que uma operação recebeu dados inválidos. |
| `datetime.fromisoformat(texto)` | Converte um texto de data/hora em objeto de data/hora. |
| `for item in lista:` | Percorre os elementos de uma lista. |
| `from arquivo import Classe` | Usa uma classe definida em outro arquivo da pasta. |

As classes são simples: não há `Protocol`, `dataclass`, `__post_init__` ou anotações de tipo. A tarefa é especificar e verificar testes; não é necessário reimplementar a aplicação.

### 2.2 Preparem uma pasta vazia

No terminal, executem:

```sh
mkdir atividade_testes_ia
cd atividade_testes_ia
python --version
python -c "import sqlite3; print('SQLite disponível')"
```

Se a pasta já existir, escolham outro nome para uma nova pasta vazia. Se necessário, substituam `python` por `python3` ou `py` em todos os comandos.

Na seção 3, copiem cada bloco para seu próprio arquivo, salvo em UTF-8. Todos devem ficar diretamente na mesma pasta:

| Arquivo | Origem | Finalidade |
|---|---|---|
| `dominio.py` | Código completo da seção 3.1 | Regras da entidade |
| `aplicacao.py` | Código completo da seção 3.2 | Coordenação das reservas |
| `infraestrutura.py` | Código completo da seção 3.3 | Memória e SQLite |
| `main.py` | Código completo da seção 3.4 | Demonstração no terminal |
| `test_ia.py` | Será implementado pelo LLM na seção 5 | Testes a auditar |

Não juntem os quatro primeiros blocos em um único arquivo. Não chamem arquivos de `unittest.py`, `sqlite3.py` ou `datetime.py`.

### 2.3 Usem somente unittest

A atividade usa apenas a biblioteca padrão do Python. Não é necessário instalar pacotes ou escolher um framework. Confiram o ambiente:

```sh
python -c "import unittest, sqlite3; from unittest.mock import Mock; print('Ambiente pronto')"
```

O LLM deverá gerar um único arquivo `test_ia.py`, com classes de teste que herdam de `unittest.TestCase`. Usem sempre este comando, na pasta do projeto:

```sh
python -m unittest -v test_ia
```

O comando funcionará depois que `test_ia.py` tiver sido gerado e salvo. Não criem uma implementação de testes vazia apenas para obter um resultado aprovado: o relatório deve indicar que os casos foram executados.

### 2.4 Referência rápida para auditar o código gerado

| Elemento | O que verificar |
|---|---|
| `class Teste...(unittest.TestCase):` | Agrupa os métodos de teste |
| Método `def test_...(self):` | É reconhecido pelo executor como um teste |
| `setUp()` | Quando usado, prepara dados antes de cada método |
| `self.assertTrue(x)` / `self.assertFalse(x)` | Verifica resultado verdadeiro ou falso |
| `self.assertEqual(observado, esperado)` | Compara valores, incluindo os campos das reservas |
| `with self.assertRaises(ValueError):` | Verifica se a operação rejeita o caso com a exceção esperada |
| `Mock()` | Simula o repositório e registra suas chamadas |
| `mock.adicionar.assert_not_called()` | Confirma que não foi solicitada gravação |
| `self.addCleanup(acao)` | Agenda uma ação de limpeza, como fechar uma conexão |

Nos testes com SQLite, o código pode usar `tempfile.TemporaryDirectory()` para criar uma pasta própria. Se usar `addCleanup()`, as ações são executadas na ordem inversa do registro: fechem as conexões antes de apagar a pasta. Não é necessário pedir à IA recursos mais elaborados.

## 3. Código completo da arquitetura em camadas

Copiem os quatro blocos abaixo para arquivos separados na pasta criada na seção 2.2. O código usa classes simples, sem anotações de tipo ou geração automática de métodos. `__init__` prepara cada objeto; `self` representa o próprio objeto. Não é necessário alterar o código-base para o LLM conseguir implementar os testes.

### 3.1 Arquivo `dominio.py`

A entidade guarda os quatro campos da reserva e valida os dados no construtor. `conflita_com()` compara salas e horários; reservas adjacentes são permitidas porque as comparações são estritas.

```python
class Reserva:
    def __init__(self, sala, responsavel, inicio, fim):
        if sala.strip() == '' or responsavel.strip() == '':
            raise ValueError('Informe sala e responsável.')
        if fim <= inicio:
            raise ValueError('O término deve ser posterior ao início.')
        self.sala = sala
        self.responsavel = responsavel
        self.inicio = inicio
        self.fim = fim
    def conflita_com(self, outra):
        mesma_sala = self.sala == outra.sala
        horarios_sobrepostos = (
            self.inicio < outra.fim and outra.inicio < self.fim
        )
        return mesma_sala and horarios_sobrepostos
```

### 3.2 Arquivo `aplicacao.py`

O serviço recebe o repositório no construtor. Ele limpa os textos, converte as datas, cria a entidade e consulta conflitos antes de solicitar a gravação. Ele não contém SQL.

```python
from datetime import datetime
from dominio import Reserva
class ServicoReservas:
    def __init__(self, repositorio):
        self.repositorio = repositorio
    def listar(self):
        return self.repositorio.listar()
    def reservar(self, sala, responsavel, inicio, fim):
        sala = sala.strip().upper()
        responsavel = responsavel.strip()
        data_inicio = datetime.fromisoformat(inicio)
        data_fim = datetime.fromisoformat(fim)
        reserva = Reserva(sala, responsavel, data_inicio, data_fim)
        reservas_existentes = self.repositorio.listar()
        for existente in reservas_existentes:
            if reserva.conflita_com(existente):
                raise ValueError('A sala já está reservada nesse intervalo.')
        self.repositorio.adicionar(reserva)
        return reserva
```

### 3.3 Arquivo `infraestrutura.py`

Os dois repositórios oferecem `listar()` e `adicionar()`. SQLite é fornecido completo para permitir executar a integração nesta atividade. O mock permite isolar o serviço; os testes de integração usam o repositório real.

```python
import sqlite3
from datetime import datetime
from dominio import Reserva
class RepositorioMemoria:
    def __init__(self):
        self.reservas = []
    def listar(self):
        return self.reservas.copy()
    def adicionar(self, reserva):
        self.reservas.append(reserva)
class RepositorioSQLite:
    def __init__(self, arquivo):
        self.conexao = sqlite3.connect(arquivo)
        self.conexao.execute("""
            CREATE TABLE IF NOT EXISTS reservas (
                id INTEGER PRIMARY KEY,
                sala TEXT NOT NULL,
                responsavel TEXT NOT NULL,
                inicio TEXT NOT NULL,
                fim TEXT NOT NULL
            )
        """)
        self.conexao.commit()
    def adicionar(self, reserva):
        self.conexao.execute(
            'INSERT INTO reservas '
            '(sala, responsavel, inicio, fim) VALUES (?, ?, ?, ?)',
            (reserva.sala, reserva.responsavel,
             reserva.inicio.isoformat(), reserva.fim.isoformat()),
        )
        self.conexao.commit()
    def listar(self):
        registros = self.conexao.execute(
            'SELECT sala, responsavel, inicio, fim FROM reservas ORDER BY id'
        ).fetchall()
        reservas = []
        for registro in registros:
            sala, responsavel, inicio, fim = registro
            reserva = Reserva(
                sala, responsavel,
                datetime.fromisoformat(inicio),
                datetime.fromisoformat(fim),
            )
            reservas.append(reserva)
        return reservas
    def fechar(self):
        self.conexao.close()
```

### 3.4 Arquivo `main.py`

A composição conecta serviço e repositório em memória. A função de apresentação apenas mostra os dados. A entrada fixa evita construir menus durante a atividade.

```python
from aplicacao import ServicoReservas
from infraestrutura import RepositorioMemoria
def apresentar_reservas(servico):
    reservas = servico.listar()
    for reserva in reservas:
        print(
            f'{reserva.sala} | {reserva.responsavel} | '
            f'{reserva.inicio:%H:%M}–{reserva.fim:%H:%M}'
        )
def main():
    repositorio = RepositorioMemoria()
    servico = ServicoReservas(repositorio)
    servico.reservar(
        ' a101 ', ' Ana ',
        '2026-11-03T09:00', '2026-11-03T10:00',
    )
    apresentar_reservas(servico)
if __name__ == '__main__':
    main()
```

### 3.5 Executem a aplicação-base

Na pasta onde estão os quatro arquivos, executem:

```sh
python main.py
```

**Resultado esperado:**

```text
A101 | Ana | 09:00–10:00
```

A demonstração usa memória e começa vazia em cada execução. O teste de integração criará seu próprio arquivo SQLite temporário.

Se aparecer `ModuleNotFoundError`, confiram a pasta atual, os quatro nomes de arquivo e se todos foram salvos. Não peçam à IA para corrigir imports inventando uma estrutura de projeto diferente da fornecida.

### 3.6 Observações para compreender o código

- `Reserva` recebe objetos `datetime`; o serviço recebe textos e faz a conversão.
- O serviço normaliza a sala antes de consultar conflitos. No teste direto do domínio, usem nomes de sala já normalizados.
- `listar()` do repositório SQLite reconstrói novos objetos. Comparem seus campos, não a identidade dos objetos.
- `commit()` confirma a gravação. `fechar()` encerra a conexão; os testes devem chamá-lo também quando falharem.
- SQLite é um banco real mesmo quando seu arquivo está em uma pasta temporária.
- Não há proteção transacional da sequência completa “consultar conflito e inserir” contra concorrência entre processos; essa característica não é avaliada nesta atividade.

## 4. Primeiro: especifiquem quatro casos

Um **caso de teste** descreve condições, dados, ações e resultados esperados. **Rastreabilidade** é a relação entre requisitos, casos e testes implementados. 
Especifiquem os quatro casos abaixo. Vocês devem escolher os dados concretos e escrever as expectativas antes de pedir código à IA.

| ID | Caso obrigatório | Unidade ou integração avaliada |
|---|---|---|
| CT-01 | Rejeitar uma reserva cujo término é igual ao início | Construção de `Reserva`, sem repositório |
| CT-02 | Avaliar duas reservas consecutivas da mesma sala, verificando o conflito nos dois sentidos | `Reserva.conflita_com()`, sem banco |
| CT-03 | Tentar uma reserva sobreposta à existente, usando nome de sala com espaços e minúsculas | `ServicoReservas` com repositório mockado; observar rejeição e tentativa de gravação |
| CT-04 | Gravar uma reserva pelo serviço e recuperá-la com outro repositório SQLite | Integração real, em arquivo temporário |

Para CT-03, a reserva existente deve usar o nome de sala já normalizado. Definam o retorno de `listar()` do mock e o que deve acontecer com `adicionar()`. Não basta especificar que “deve dar erro”.

Para CT-04, definam todos os campos esperados, não apenas a quantidade de registros. Não usem o banco da demonstração ou dados deixados por outro teste.

### Modelo de especificação: preencham uma cópia por caso

| Campo | Preenchimento |
|---|---|
| ID e título | CT-… |
| Requisito(s) | R… |
| Objetivo | Qual comportamento será verificado? |
| Nível e alvo | Domínio, serviço isolado ou integração; classe/método |
| Pré-condições | Objetos e estado necessários |
| Dados concretos | Sala, responsável, data, início e fim |
| Passos | Operações e ordem de execução |
| Resultado esperado | Retorno, exceção, campos, estado ou chamadas esperadas |
| Dependências | Quais são reais e quais serão simuladas? |
| Isolamento e limpeza | Como evitar dependência de outros testes e fechar o banco? |

**Exemplo de precisão, fora dos casos obrigatórios:** em um teste para salas diferentes, escrever “A101 e A102, ambas em 03/11/2026 das 9h às 10h; `conflita_com()` deve devolver falso” é mais verificável do que “testar horários”. Não copiem esse exemplo como um dos quatro casos pedidos.

## 5. Solicitem a implementação à IA

Enviem ao LLM o código da seção 3 e a especificação produzida pelo grupo. Solicitem somente testes com `unittest`. Não enviem apenas o nome das classes: o modelo precisa conhecer suas assinaturas e comportamentos reais.

Usem o prompt abaixo, preenchendo os campos. A IA deve implementar os casos de vocês, sem inventar o resultado esperado.

### Prompt de implementação

```text
Você implementará testes para um sistema Python de reservas em camadas.
Use somente unittest, com classes que herdam de unittest.TestCase.

A seguir estão o código-base e os quatro casos especificados por nosso grupo.
Não altere o código de produção nem as regras para fazer testes passarem.
Se faltar informação para implementar um caso, identifique a dúvida.

Restrições:
1. Produza um único arquivo test_ia.py e informe este comando:
   python -m unittest -v test_ia
2. Identifique CT-01, CT-02, CT-03 e CT-04 em comentários e nomes dos testes
   (por exemplo, test_ct01_...). Relacione cada caso ao código gerado.
3. Nos testes do domínio, use Reserva real; não simule o método testado.
4. No CT-03, simule somente o repositório com unittest.mock.Mock.
   Use ServicoReservas e Reserva reais. Verifique a exceção esperada
   e a interação com adicionar, conforme nossa especificação.
5. No CT-04, use ServicoReservas e RepositorioSQLite reais, arquivo
   temporário exclusivo e nova instância de repositório para leitura.
   Feche todas as conexões, inclusive se o teste falhar.
6. Use datas fixas e resultados esperados da especificação.
   Não use print como substituto de asserção nem capture e ignore erros.
7. Use somente a biblioteca padrão: unittest, unittest.mock, tempfile
   e os demais módulos necessários, além dos arquivos-base fornecidos.
   Não use dataclass, Protocol, classes abstratas ou pacotes adicionais.
   Use assertTrue/assertFalse/assertEqual/assertRaises de unittest.TestCase.
   Para verificar as interações do mock, use os métodos do próprio Mock.
8. Não substitua a chamada ao código de produção por um retorno constante,
   não calcule o esperado copiando a regra de conflito e não ignore testes com skip ou expectedFailure.

CÓDIGO-BASE:
[cole os quatro arquivos completos da seção 3, identificados por nome]

ESPECIFICAÇÃO:
[cole os quatro casos preenchidos]
```

Salvem a primeira resposta em `test_ia.py` e guardem uma cópia como `primeira_resposta.txt` para comparar as revisões. A cópia em `.txt` evita executar testes duplicados por engano. Registrem o modelo utilizado e o prompt enviado.

O `Mock` será importado de `unittest.mock`. Tanto os testes quanto a simulação do repositório usam a biblioteca padrão. Prefiram código direto, sem classes auxiliares ou hierarquias desnecessárias além de `unittest.TestCase`.

## 6. Executem e auditem os testes

Primeiro, executem:

```sh
python -m unittest -v test_ia
```

Confirmem que o relatório apresenta os métodos executados e termina com `Ran N tests` e `OK`, com `N` maior que zero. `N` não é um texto a copiar: é a quantidade real de testes. `Ran 0 tests` não demonstra que a atividade foi implementada.

Não avaliem a qualidade pelo número bruto de testes: um caso pode exigir mais de um método de teste. Todos os quatro IDs precisam estar cobertos e todas as verificações especificadas precisam existir.

### Checklist de auditoria

| Verificação | O que procurar no código |
|---|---|
| Rastreabilidade | Cada caso está identificado e associado ao requisito correto? |
| Dados e preparação | São os mesmos dados e pré-condições especificados? |
| Alvo real | O teste chama o método real que deveria avaliar? |
| Asserções | Comparam retorno, exceção, chamadas ou campos com a expectativa definida pelo grupo? |
| CT-03 | Verifica normalização/conflito com repositório simulado e se a gravação indevida foi evitada? |
| CT-04 | Realmente usa SQLite, outra instância e comparação dos quatro campos? |
| Isolamento | Cada teste prepara seus dados e não depende da ordem de execução? |
| Limpeza | As conexões são fechadas mesmo se houver falha? |
| Aprovação legítima | Não há `pass` como solução, teste ignorado, condição que evita a asserção ou exceção engolida? |

Leiam os trechos de código, mesmo quando tudo estiver aprovado. Um teste que só contém `assert True`, ou que simula o próprio `conflita_com()`, pode passar sem avaliar a regra.

### Matriz de conformidade: preenchimento obrigatório

| Caso | Classe e método gerado | Evidência no código: trecho da chamada e da asserção | Atende / parcial / não atende | Correção necessária |
|---|---|---|---|---|
| CT-01 | | | | |
| CT-02 | | | | |
| CT-03 | | | | |
| CT-04 | | | | |

**Exijam evidência:** “atende porque passou” não basta. Para CT-01, por exemplo, a evidência precisa mostrar a construção da reserva e a verificação da exceção correspondente.

Se encontrarem um problema, corrijam diretamente ou peçam revisão à IA. Usem um pedido específico:

```text
No caso [ID], nossa especificação exige [expectativa].
O teste gerado atualmente faz [comportamento observado no código].
Isso não atende porque [motivo].
Revise somente os testes necessários, mantendo o código de produção.
Explique a mudança e preserve os demais casos.
```

Se todos os critérios forem atendidos na primeira resposta, registrem isso com evidências. Não inventem falhas para preencher o relatório. A declaração da própria IA de que cumpriu os requisitos não substitui a auditoria do grupo.

## 7. Verifiquem se o teste detecta um defeito

Vamos introduzir um defeito controlado na regra de sobreposição. Essa experiência dá uma evidência adicional: o teste pode distinguir um comportamento correto de um comportamento deliberadamente incorreto.

1. Executem os testes com a implementação original. Eles devem passar antes da alteração. Se houver falhas, resolvam-nas primeiro; se não conseguirem, registrem a limitação e não atribuam a falha ao defeito controlado.
2. Criem uma cópia de segurança de `dominio.py`, por exemplo `dominio_original.txt`. Não modifiquem os testes durante a experiência.
3. **Somente para esta verificação**, em `conflita_com()`, troquem as duas comparações estritas por comparações inclusivas:

**Trecho original:**

```python
self.inicio < outra.fim and outra.inicio < self.fim
```

**Trecho com defeito proposital:**

```python
self.inicio <= outra.fim and outra.inicio <= self.fim
```

4. Salvem e executem a mesma suíte em um novo comando no terminal. O teste de **CT-02 deve falhar**, pois a implementação alterada passa a tratar horários consecutivos como conflito.
5. Copiem o resultado. Se CT-02 continuar aprovado, examinem os dados, a chamada real e as asserções. Confiram também se o arquivo alterado é o importado pelos testes.
6. Se a implementação do teste não cumprir o caso, restaurem primeiro o código original, revisem o teste e repitam a experiência. Se precisarem mudar a especificação, guardem a versão anterior e justifiquem a alteração.
7. **Restaurem `dominio.py` a partir da cópia de segurança** e executem novamente. Os testes devem voltar a passar. A única alteração de código de produção autorizada nesta etapa é o defeito temporário, seguido da restauração.

| Execução | Resultado observado | Evidência a registrar |
|---|---|---|
| Código original | | Resumo da suíte |
| Comparações alteradas | | Nome do teste de CT-02 e motivo da falha |
| Código restaurado | | Resumo final da suíte |

Esperamos uma falha por **asserção de comportamento**, não por erro de sintaxe, importação ou instalação. Se vários testes de CT-02 falharem, registrem quais. Detectar este defeito não demonstra que todos os defeitos possíveis serão detectados.

## 8. Entrega

Submetam **um PDF**, com identificação dos integrantes, contendo:

1. Os quatro casos especificados antes da geração.
2. Nome do modelo de IA, prompt enviado e código final de `test_ia.py`, como texto legível.
3. Matriz de conformidade com os trechos que sustentam cada avaliação.
4. Evidências das três execuções: original, defeito proposital e restauração.
5. Registro breve das revisões: problema encontrado, correção e motivo. Se não foram necessárias, declarem isso e justifiquem com a auditoria.

>  Não é obrigatório que a IA erre. A avaliação considera a qualidade da especificação e da verificação, não a quantidade de defeitos encontrados. Se algo continuar falhando, registrem o estado real e a causa investigada.
