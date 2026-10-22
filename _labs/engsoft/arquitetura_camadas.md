---
title: "Engenharia de Software: Arquitetura em Camadas em Python"
collection: labs
type: "Lab"
permalink: /labs/arquitetura-camadas
date: 2026-10-21
location: "Ribeirão Preto, Brazil"
---

## Sistema universitário de reservas de salas

Trabalhem em grupos de 3 ou 4 pessoas para construir e modificar um sistema em camadas. Ao final, a mesma lógica de reservas deverá funcionar com terminal ou navegador e com armazenamento em memória ou SQLite.

**Organização:** distribuam os papéis de implementação, revisão e execução dos testes; alternem os papéis a cada etapa. Antes de executar cada troca, registrem quais arquivos esperam modificar. Comparem a previsão com o resultado.

## 1. Preparação e escopo

Usem Python 3.10 ou superior e um editor de texto ou IDE. O projeto usa somente a biblioteca padrão; não há pacotes para instalar. Verifiquem a versão com `python --version`. Se necessário, substituam `python` por `python3` ou `py` nos comandos deste tutorial.

Extraiam a pasta do projeto e abram o terminal nessa pasta. Os comandos devem ser executados onde está `main.py`.

O sistema implementa criação e listagem de reservas, validação de campos, validação de horários e impedimento de sobreposição. Trata-se de um recorte do cenário universitário: autenticação, autorização, cancelamento, cadastro de salas e consulta de recursos ficam fora da implementação inicial. Não se exige cumprir todos os RFs e RNFs da atividade de projeto.

Todos os horários são locais da universidade, sem conversão de fuso. Para identificar uma sala, o sistema remove espaços nas extremidades e converte o nome para maiúsculas. Os dados ficam separados em cada processo: dois programas com armazenamento em memória não compartilham reservas.

## 2. Conheçam as camadas antes de programar

| Camada ou papel | Arquivos | Responsabilidade |
|---|---|---|
| Apresentação | `interface_terminal.py`, `interface_web.py` | Receber entradas e apresentar resultados |
| Aplicação | `aplicacao.py` | Coordenar o caso de uso de reserva |
| Domínio | `dominio.py` | Representar a reserva e definir validade e conflito |
| Contrato de persistência | `contratos.py` | Definir as operações esperadas de um repositório |
| Infraestrutura | `infraestrutura.py` | Implementar armazenamento em memória e SQLite |
| Composição | `main.py` | Escolher e conectar as implementações |

Fluxo de execução de uma reserva:

```text
Terminal ou navegador
        ↓
Interface de apresentação
        ↓
ServicoReservas → Reserva e regras do domínio
        ↓
RepositorioReservas (contrato)
        ↓
RepositorioMemoria ou RepositorioSQLite
```

O fluxo de execução passa pelo repositório concreto. Já a dependência do código da aplicação aponta para o contrato: `aplicacao.py` não importa `sqlite3` nem conhece a classe `RepositorioSQLite`. É uma arquitetura em camadas com inversão de dependência na fronteira de persistência. O arquivo de composição conhece as implementações para poder conectá-las.

**Dois significados de interface:** a interface de usuário é o terminal ou a página web; a interface de programação é o contrato `RepositorioReservas`, com os métodos `listar` e `adicionar`. Não são a mesma coisa.

**Conectores:** são os mecanismos pelos quais os componentes interagem. Neste laboratório, há chamadas de métodos entre a apresentação e a aplicação, chamadas pelo contrato do repositório, requisições HTTP entre navegador e servidor e acesso SQL por meio de `sqlite3` entre o repositório e o banco. As classes de repositório são adaptadores de armazenamento; o contrato define a comunicação esperada. Ter arquivos separados, por si só, não garante uma arquitetura bem definida.

## 3. Etapa A: Implementar terminal e memória

Tempo sugerido: 30 minutos.

Criem primeiro `dominio.py`, `contratos.py`, `aplicacao.py` e a classe `RepositorioMemoria` em `infraestrutura.py`. Leiam os códigos abaixo e expliquem entre si o propósito de cada classe antes de copiá-los.

### 3.1 Domínio

A regra de conflito usa intervalos com término exclusivo: duas reservas se sobrepõem quando o início de cada uma é anterior ao fim da outra. Assim, 09h–10h e 10h–11h são compatíveis. O teste de sala deve fazer parte da regra.


```python
from dataclasses import dataclass
from datetime import datetime


@dataclass(frozen=True)
class Reserva:
    sala: str
    responsavel: str
    inicio: datetime
    fim: datetime

    def __post_init__(self):
        if not self.sala.strip() or not self.responsavel.strip():
            raise ValueError('Informe sala e responsável.')
        if self.inicio.tzinfo is not None or self.fim.tzinfo is not None:
            raise ValueError('Use os horários locais da universidade, sem fuso.')
        if self.fim <= self.inicio:
            raise ValueError('O término deve ser posterior ao início.')

    def conflita_com(self, outra: 'Reserva') -> bool:
        return (self.sala == outra.sala
                and self.inicio < outra.fim
                and outra.inicio < self.fim)
```

### 3.2 Interface de persistência

`Protocol` descreve um contrato estrutural. Uma classe compatível deve oferecer os métodos com os tipos indicados, mas não precisa herdar de `RepositorioReservas`. O Python não valida esse contrato automaticamente em tempo de execução; as anotações ajudam ferramentas de análise e os testes verificam o comportamento.

```python
from typing import Protocol
from dominio import Reserva


class RepositorioReservas(Protocol):
    def listar(self) -> list[Reserva]: ...
    def adicionar(self, reserva: Reserva) -> None: ...
```

### 3.3 Serviço de aplicação

A apresentação entrega strings ao serviço. Ele converte as datas, normaliza a identificação da sala, cria a entidade e consulta o repositório antes de salvar. Regras não devem ser copiadas para o terminal ou para a página web.

```python
from datetime import datetime
from contratos import RepositorioReservas
from dominio import Reserva


class ServicoReservas:
    def __init__(self, repositorio: RepositorioReservas):
        self.repositorio = repositorio

    def listar(self) -> list[Reserva]:
        return sorted(self.repositorio.listar(), key=lambda r: (r.inicio, r.sala))

    def reservar(self, sala: str, responsavel: str,
                 inicio: str, fim: str) -> Reserva:
        try:
            data_inicio = datetime.fromisoformat(inicio)
            data_fim = datetime.fromisoformat(fim)
        except ValueError as erro:
            raise ValueError('Use data e hora no formato AAAA-MM-DDTHH:MM.') from erro
        reserva = Reserva(sala.strip().upper(), responsavel.strip(), data_inicio, data_fim)
        if any(reserva.conflita_com(existente) for existente in self.repositorio.listar()):
            raise ValueError('A sala já está reservada nesse intervalo.')
        self.repositorio.adicionar(reserva)
        return reserva
```

### 3.4 Armazenamento

Na primeira execução, copiem somente `RepositorioMemoria` e os imports necessários. A versão completa abaixo também contém `RepositorioSQLite`, que será estudado na etapa C. `listar` devolve uma cópia da lista para que quem a recebe não altere diretamente a coleção interna.

```python
import sqlite3
from datetime import datetime
from pathlib import Path
from dominio import Reserva


class RepositorioMemoria:
    def __init__(self):
        self._reservas: list[Reserva] = []

    def listar(self) -> list[Reserva]:
        return list(self._reservas)

    def adicionar(self, reserva: Reserva) -> None:
        self._reservas.append(reserva)


class RepositorioSQLite:
    def __init__(self, arquivo: Path):
        self.arquivo = arquivo
        with sqlite3.connect(self.arquivo) as conexao:
            conexao.execute('''
                CREATE TABLE IF NOT EXISTS reservas (
                    id INTEGER PRIMARY KEY,
                    sala TEXT NOT NULL,
                    responsavel TEXT NOT NULL,
                    inicio TEXT NOT NULL,
                    fim TEXT NOT NULL
                )
            ''')

    def listar(self) -> list[Reserva]:
        with sqlite3.connect(self.arquivo) as conexao:
            registros = conexao.execute(
                'SELECT sala, responsavel, inicio, fim FROM reservas'
            ).fetchall()
        return [Reserva(sala, pessoa, datetime.fromisoformat(inicio),
                        datetime.fromisoformat(fim))
                for sala, pessoa, inicio, fim in registros]

    def adicionar(self, reserva: Reserva) -> None:
        with sqlite3.connect(self.arquivo) as conexao:
            conexao.execute(
                'INSERT INTO reservas (sala, responsavel, inicio, fim) VALUES (?, ?, ?, ?)',
                (reserva.sala, reserva.responsavel,
                 reserva.inicio.isoformat(), reserva.fim.isoformat())
            )
```

### 3.5 Interface de terminal

```python
from aplicacao import ServicoReservas


def executar_terminal(servico: ServicoReservas) -> None:
    while True:
        print('\n1 - Reservar | 2 - Listar | 0 - Sair')
        opcao = input('Opção: ').strip()
        if opcao == '0':
            return
        if opcao == '1':
            try:
                servico.reservar(
                    input('Sala: '), input('Responsável: '),
                    input('Início (AAAA-MM-DDTHH:MM): '),
                    input('Fim (AAAA-MM-DDTHH:MM): ')
                )
                print('Reserva criada.')
            except ValueError as erro:
                print(f'Não foi possível reservar: {erro}')
        elif opcao == '2':
            reservas = servico.listar()
            if not reservas:
                print('Nenhuma reserva.')
            for r in reservas:
                print(f'{r.sala} | {r.responsavel} | '
                      f'{r.inicio:%d/%m/%Y %H:%M} até {r.fim:%d/%m/%Y %H:%M}')
        else:
            print('Opção inválida.')
```

### 3.6 Primeira composição

Para começar sem depender da interface web, criem este `main.py` provisório:

```python
from aplicacao import ServicoReservas
from infraestrutura import RepositorioMemoria
from interface_terminal import executar_terminal

if __name__ == '__main__':
    repositorio = RepositorioMemoria()
    servico = ServicoReservas(repositorio)
    executar_terminal(servico)
```

Executem:

```sh
python main.py
```

Criem uma reserva para A101, de `2026-11-03T09:00` a `2026-11-03T10:00`. Tentem reservar a mesma sala de 09h30 a 10h30. Depois tentem uma sala diferente no mesmo horário e uma reserva consecutiva na A101, de 10h a 11h.

Saiam pela opção 0 e iniciem novamente. A lista fica vazia: esse é o comportamento esperado do armazenamento em memória.

**Registro do grupo:** onde está a regra de conflito? Por que a interface de terminal não acessa `_reservas` diretamente?

## 4. Etapa B: Trocar terminal por web

Tempo sugerido: 25 minutos.

Criem `interface_web.py` com o código abaixo. O servidor recebe HTTP, extrai campos do formulário e chama o mesmo serviço. Ele não calcula conflitos e não executa SQL. Os valores apresentados no HTML passam por `escape`, para que dados digitados não sejam interpretados como marcação.

```python
from html import escape
from http.server import BaseHTTPRequestHandler, HTTPServer
from urllib.parse import parse_qs
from aplicacao import ServicoReservas


def executar_web(servico: ServicoReservas, porta: int = 8000) -> None:
    class Manipulador(BaseHTTPRequestHandler):
        def pagina(self, mensagem: str = '', status: int = 200) -> None:
            linhas = ''.join(
                '<tr>' + ''.join(f'<td>{escape(valor)}</td>' for valor in (
                    r.sala, r.responsavel,
                    r.inicio.strftime('%d/%m/%Y %H:%M'),
                    r.fim.strftime('%d/%m/%Y %H:%M'))) + '</tr>'
                for r in servico.listar()
            )
            html = f'''<!doctype html>
<html lang="pt-BR"><meta charset="utf-8">
<title>Reservas de salas</title>
<style>
body {{font-family: sans-serif; max-width: 900px; margin: 2rem auto; padding: 1rem;}}
label {{display: block; margin: .8rem 0;}}
table {{border-collapse: collapse; width: 100%;}}
th, td {{border: 1px solid #ccc; padding: .6rem; text-align: left;}}
</style>
<h1>Reservas de salas</h1><p role="status">{escape(mensagem)}</p>
<form method="post" action="/reservar">
<label>Sala <input name="sala" required maxlength="80"></label>
<label>Responsável <input name="responsavel" required maxlength="120"></label>
<label>Início <input name="inicio" type="datetime-local" required></label>
<label>Fim <input name="fim" type="datetime-local" required></label>
<button>Reservar</button></form>
<h2>Reservas cadastradas</h2>
<table><thead><tr><th>Sala</th><th>Responsável</th><th>Início</th><th>Fim</th></tr></thead>
<tbody>{linhas or '<tr><td colspan="4">Nenhuma reserva.</td></tr>'}</tbody></table></html>'''
            corpo = html.encode('utf-8')
            self.send_response(status)
            self.send_header('Content-Type', 'text/html; charset=utf-8')
            self.send_header('Content-Length', str(len(corpo)))
            self.end_headers()
            self.wfile.write(corpo)

        def do_GET(self):
            if self.path != '/':
                self.send_error(404)
                return
            self.pagina()

        def do_POST(self):
            if self.path != '/reservar':
                self.send_error(404)
                return
            try:
                tamanho = int(self.headers.get('Content-Length', '0'))
                if not 0 < tamanho <= 8192:
                    raise ValueError('Tamanho de formulário inválido.')
                dados = parse_qs(self.rfile.read(tamanho).decode('utf-8'),
                                 keep_blank_values=True)
                campos = {nome: dados.get(nome, [''])[0]
                          for nome in ('sala', 'responsavel', 'inicio', 'fim')}
                servico.reservar(**campos)
            except (ValueError, UnicodeError) as erro:
                self.pagina(str(erro), 400)
                return
            # Redirecionar evita reenviar o formulário ao atualizar a página.
            self.send_response(303)
            self.send_header('Location', '/')
            self.send_header('Content-Length', '0')
            self.end_headers()

    servidor = HTTPServer(('127.0.0.1', porta), Manipulador)
    print(f'Acesse http://127.0.0.1:{porta} — Ctrl+C para encerrar.')
    try:
        servidor.serve_forever()
    except KeyboardInterrupt:
        print('\nServidor encerrado.')
    finally:
        servidor.server_close()
```

Substituam o `main.py` provisório pela versão configurável abaixo. Para executá-la, `infraestrutura.py` deve conter também a classe `RepositorioSQLite`, mesmo quando a opção escolhida é memória, pois as duas classes são importadas no início.

```python
import argparse
from pathlib import Path
from aplicacao import ServicoReservas
from infraestrutura import RepositorioMemoria, RepositorioSQLite
from interface_terminal import executar_terminal
from interface_web import executar_web


def main():
    parser = argparse.ArgumentParser(description='Laboratório de arquitetura em camadas')
    parser.add_argument('--interface', choices=['terminal', 'web'], default='terminal')
    parser.add_argument('--armazenamento', choices=['memoria', 'sqlite'], default='memoria')
    parser.add_argument('--porta', type=int, default=8000)
    opcoes = parser.parse_args()
    repositorio = (RepositorioMemoria() if opcoes.armazenamento == 'memoria'
                   else RepositorioSQLite(Path(__file__).with_name('reservas.db')))
    servico = ServicoReservas(repositorio)
    if opcoes.interface == 'terminal':
        executar_terminal(servico)
    else:
        executar_web(servico, opcoes.porta)


if __name__ == '__main__':
    main()
```

Executem:

```sh
python main.py --interface web --armazenamento memoria
```

Abram **http://127.0.0.1:8000** no navegador e repitam os cenários da etapa A. Para encerrar, voltem ao terminal e pressionem Ctrl+C. O endereço de escuta é local: esta atividade é para execução na própria máquina. Se a porta estiver ocupada, acrescentem `--porta 8001` e acessem a nova porta.

**Observem o conector HTTP:** nas ferramentas de desenvolvimento do navegador, aba Rede/Network, criem uma reserva. Identifiquem o `POST /reservar`, o redirecionamento 303 após sucesso e o `GET /` seguinte. Um erro de validação devolve status 400 com a mensagem na página.

**Registro do grupo:** quais arquivos mudaram ao trocar a apresentação? A regra de sobreposição precisou ser reescrita? Expliquem o caminho de uma requisição até o repositório.

## 5. Etapa C: Trocar memória por SQLite

Tempo sugerido: 20 minutos.

Se ainda não fizeram, completem `infraestrutura.py` com `RepositorioSQLite`, mostrado na etapa A. Não alterem `ServicoReservas`, `Reserva` nem os arquivos de apresentação.

O construtor cria a tabela se ela não existir. Cada operação abre e fecha uma conexão. O bloco `with` controla confirmação ou reversão da transação. As consultas transformam os registros em entidades `Reserva`. O `INSERT` usa parâmetros `?`, mantendo os valores separados do texto SQL.

Executem:

```sh
python main.py --interface web --armazenamento sqlite
```

Cadastrem uma reserva, encerrem o servidor e iniciem novamente com o mesmo comando. A reserva deve continuar na lista. O arquivo `reservas.db` é criado ao lado de `main.py`.

Agora encerrem o servidor e executem:

```sh
python main.py --interface terminal --armazenamento sqlite
```

Consultem as reservas. A interface de terminal deve mostrar os mesmos dados salvos pela web. Criem outra reserva, saiam e voltem à interface web com SQLite.

**Registro do grupo:** qual contrato permitiu trocar o armazenamento? Onde os dados são convertidos entre objetos e registros SQL? A persistência exige que a apresentação conheça o nome da tabela?

## 6. Etapa D: Verificar o contrato e a regra de negócio

Tempo sugerido: 15 minutos.

Criem `test_reservas.py` e executem:

```sh
python -m unittest -v
```

Os mesmos testes de negócio são executados com os dois repositórios. Um teste adicional verifica persistência ao recriar o repositório SQLite. Os testes usam um banco temporário, sem alterar `reservas.db`.

```python
import tempfile
import unittest
from pathlib import Path
from aplicacao import ServicoReservas
from infraestrutura import RepositorioMemoria, RepositorioSQLite


class ContratoReservas:
    def test_reserva_valida(self):
        self.servico.reservar(' a101 ', 'Ana', '2026-11-03T09:00', '2026-11-03T10:00')
        reservas = self.servico.listar()
        self.assertEqual(len(reservas), 1)
        self.assertEqual(reservas[0].sala, 'A101')

    def test_rejeita_sobreposicoes(self):
        self.servico.reservar('A101', 'Ana', '2026-11-03T09:00', '2026-11-03T10:00')
        for inicio, fim in [('09:30', '10:30'), ('08:30', '09:30'),
                            ('09:15', '09:45'), ('08:00', '11:00'), ('09:00', '10:00')]:
            with self.subTest(inicio=inicio, fim=fim), self.assertRaises(ValueError):
                self.servico.reservar('a101', 'Bia', f'2026-11-03T{inicio}', f'2026-11-03T{fim}')
        self.assertEqual(len(self.servico.listar()), 1)

    def test_permite_consecutivas_e_salas_distintas(self):
        self.servico.reservar('A101', 'Ana', '2026-11-03T09:00', '2026-11-03T10:00')
        self.servico.reservar('A101', 'Bia', '2026-11-03T10:00', '2026-11-03T11:00')
        self.servico.reservar('A102', 'Caio', '2026-11-03T09:00', '2026-11-03T10:00')
        self.assertEqual(len(self.servico.listar()), 3)

    def test_rejeita_dados_invalidos(self):
        for sala, pessoa, inicio, fim in [
            (' ', 'Ana', '2026-11-03T09:00', '2026-11-03T10:00'),
            ('A101', ' ', '2026-11-03T09:00', '2026-11-03T10:00'),
            ('A101', 'Ana', 'data inválida', '2026-11-03T10:00'),
            ('A101', 'Ana', '2026-11-03T10:00', '2026-11-03T09:00'),
            ('A101', 'Ana', '2026-11-03T09:00', '2026-11-03T09:00')]:
            with self.subTest(sala=sala, inicio=inicio), self.assertRaises(ValueError):
                self.servico.reservar(sala, pessoa, inicio, fim)


class TesteMemoria(ContratoReservas, unittest.TestCase):
    def setUp(self):
        self.servico = ServicoReservas(RepositorioMemoria())


class TesteSQLite(ContratoReservas, unittest.TestCase):
    def setUp(self):
        self.pasta = tempfile.TemporaryDirectory()
        self.addCleanup(self.pasta.cleanup)
        self.arquivo = Path(self.pasta.name) / 'teste.db'
        self.servico = ServicoReservas(RepositorioSQLite(self.arquivo))

    def test_persiste_apos_recriar_repositorio(self):
        self.servico.reservar('A101', 'Ana', '2026-11-03T09:00', '2026-11-03T10:00')
        outro = ServicoReservas(RepositorioSQLite(self.arquivo))
        self.assertEqual(len(outro.listar()), 1)


if __name__ == '__main__':
    unittest.main()
```

Resultado esperado: **9 testes aprovados**. Alguns testes contêm vários cenários, como sobreposição parcial, intervalo contido e horários idênticos.

Verifiquem também manualmente as quatro combinações:

| Apresentação | Persistência | Comando | Após reiniciar |
|---|---|---|---|
| Terminal | Memória | `python main.py --interface terminal --armazenamento memoria` | Reservas são perdidas |
| Web | Memória | `python main.py --interface web --armazenamento memoria` | Reservas são perdidas |
| Terminal | SQLite | `python main.py --interface terminal --armazenamento sqlite` | Reservas permanecem |
| Web | SQLite | `python main.py --interface web --armazenamento sqlite` | Reservas permanecem |

Façam uma execução por vez. O projeto distribuído já contém a versão final de `main.py`; a versão provisória serve para estudar a evolução da composição.

## 7. Modificações propostas aos grupos

Escolham uma modificação funcional e uma atividade de análise. Acrescentem os testes necessários antes de demonstrar a alteração.

1. **Consultar por sala:** acrescentem um caso de uso de filtro e disponibilizem-no nas duas apresentações. Decidam se o filtro fica no serviço ou exige ampliar o contrato do repositório; justifiquem.
2. **Limitar duração:** permitam reservas de no máximo duas horas. A regra deve funcionar nas duas apresentações e com os dois armazenamentos. Identifiquem a camada apropriada e testem o limite exato e seu excesso.
3. **Cancelar reservas:** definam uma identificação estável para cada reserva e uma operação de remoção no contrato. Expliquem por que essa mudança alcança mais camadas que uma nova regra de duração.
4. **Mapear conectores:** desenhem o fluxo de criação de uma reserva, rotulando HTTP, chamada de método e SQL. Separem o fluxo em execução das dependências de importação.
5. **Avaliar dependências:** procurem imports de `sqlite3` nas camadas de aplicação e domínio. Discutam o impacto de colocar SQL em `interface_web.py`.
6. **Adicionar um repositório de teste:** criem um objeto com `listar` e `adicionar` que registre as chamadas recebidas. Injetem-no no serviço e verifiquem que uma tentativa inválida não é adicionada.

## 8. Discussão arquitetural e limites

**Manutenibilidade:** a troca de apresentação e persistência preserva o serviço e as regras de domínio. Relacionem esse resultado ao RNF de alterar regras sem modificar a interface de usuário. Essa separação facilita mudanças, mas não significa que toda nova funcionalidade afete uma única camada.

**Persistência e integridade:** SQLite mantém os dados após encerrar o processo. Isso não torna atômica a sequência “consultar conflitos e inserir”. A verificação no serviço e a gravação são operações separadas. Dois processos podem consultar simultaneamente e aceitar reservas incompatíveis. O servidor usado neste tutorial atende requisições sequencialmente em um único processo, mas o desenho não resolve a concorrência entre processos. Discutam como uma operação transacional de reserva no contrato poderia proteger a verificação e a inserção juntas.

**Trade-off:** o contrato atual é simples, mas a cada reserva carrega todos os registros para verificar conflitos. Isso facilita o estudo e limita o desempenho com uma base grande. Projetem uma alternativa de consulta por sala e intervalo e discutam como mantê-la independente de SQL.

**Escopo da interface web:** o servidor HTTP da biblioteca padrão foi escolhido para um laboratório local e evita dependências adicionais. O projeto não implementa autenticação, autorização, HTTPS, disponibilidade elevada ou validação de desempenho. Não coloquem dados pessoais reais. A arquitetura é um ponto de partida para discutir esses requisitos, não uma demonstração de atendimento a eles.
