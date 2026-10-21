---
title: "Engenharia de Software: Arquitetura hexagonal em Python"
collection: labs
type: "Lab"
permalink: /labs/arquitetura-hexagonal
date: 2026-10-21
location: "Ribeirão Preto, Brazil"
---

## Sistema simplificado de reservas de salas

Neste tutorial, seu grupo construirá um sistema de reservas e trocará o armazenamento em memória por SQLite sem modificar as regras de negócio. O objetivo é compreender o núcleo, as portas, os adaptadores e a direção das dependências.

**Pré-requisito:** Python 3.10 ou superior. Nenhum pacote externo é necessário.

Distribuam os papéis de implementação, revisão e teste. Alternem os papéis ao trocar o adaptador de armazenamento.

## 1. O problema e o recorte da implementação

Uma universidade precisa registrar reservas de salas. Nesta versão, cada reserva contém sala, início e término. O programa deve:

- criar e listar reservas;
- rejeitar sala vazia e término anterior ou igual ao início;
- impedir sobreposição de horários na mesma sala;
- permitir reservas consecutivas e reservas simultâneas em salas diferentes;
- preservar os dados após encerrar o programa quando SQLite for selecionado.

Todos os horários serão locais da universidade, sem informação de fuso. Os nomes das salas serão normalizados pelo serviço, removendo espaços nas extremidades e convertendo letras para maiúsculas.

Autenticação, usuários, cancelamento e cadastro de salas ficam fora deste recorte. O exemplo não implementa todos os requisitos de um sistema universitário completo.

## 2. Entender a arquitetura

A arquitetura hexagonal coloca o negócio no núcleo e conecta tecnologias externas por meio de portas e adaptadores. O formato do hexágono é apenas uma representação: não exige seis componentes.

| Elemento | Neste exemplo | Função |
|---|---|---|
| Domínio | `Reserva` | Representar dados e regras de validade e conflito |
| Aplicação | `ServicoReservas` | Coordenar a criação e a consulta de reservas |
| Porta de entrada | Métodos públicos do serviço | Oferecer operações ao exterior |
| Porta de saída | `RepositorioReservas` | Definir o armazenamento de que o núcleo precisa |
| Adaptador de entrada | `executar_terminal` | Converter interação no terminal em chamadas ao núcleo |
| Adaptadores de saída | `RepositorioMemoria` e `RepositorioSQLite` | Implementar a porta de armazenamento |
| Composição | `main.py` | Instanciar e conectar as partes |

### Fluxo de uma operação

```text
Pessoa usando o terminal
          |
          v
Adaptador de terminal
          |
          | reservar(sala, inicio, fim)
          v
ServicoReservas + Reserva             NÚCLEO
          |
          | listar() e salvar() pela porta RepositorioReservas
          v
RepositorioMemoria OU RepositorioSQLite
                              |
                              | SQL por meio de sqlite3
                              v
                         reservas.db
```

O fluxo em execução chega ao adaptador concreto. As dependências do código têm outra orientação: os adaptadores importam tipos do núcleo, e o núcleo depende do contrato definido por ele próprio. O núcleo não importa os adaptadores nem `sqlite3`. O arquivo de composição conhece as implementações para conectá-las.

### Interface e conector

A interface de usuário é o terminal. A interface de programação é o contrato `RepositorioReservas`. Os conectores são os mecanismos de interação: chamadas de métodos entre adaptadores e núcleo, e execução de SQL entre o adaptador SQLite e o banco.

Neste exemplo, a porta de entrada é representada pelos próprios métodos do serviço, sem uma classe abstrata adicional. A porta de saída usa `Protocol`: uma classe é estruturalmente compatível quando oferece os métodos esperados. Isso não obriga herança e não garante, por si só, comportamento correto em tempo de execução. Os testes ajudam a verificar esse comportamento.

### Relação com arquitetura em camadas

O núcleo reúne aplicação e domínio; apresentação e persistência ficam nas bordas. A diferença importante é a direção das dependências na fronteira de persistência: o serviço depende de um contrato do núcleo, não da implementação do banco. Separar código em arquivos, por si só, não garante essa propriedade.

## 3. Preparar os arquivos

Verifiquem a versão:

```sh
python --version
```

Se o computador usar outro comando, substituam `python` por `python3` ou `py` ao longo do tutorial. Criem uma pasta com esta estrutura:

```text
reservas_hexagonal/
    nucleo.py
    adaptador_memoria.py
    adaptador_terminal.py
    adaptador_sqlite.py
    main.py
    test_reservas.py
```

Executem os comandos dentro dessa pasta. O arquivo `reservas.db` será criado automaticamente quando usarem SQLite.

## 4. Implementar o núcleo

O núcleo recebe dados Python, sem ler entradas do terminal. A entidade valida a reserva e sabe reconhecer conflito; o serviço consulta o repositório antes de salvar.

Duas reservas da mesma sala entram em conflito quando o início de cada uma é anterior ao fim da outra. O término é exclusivo: 09h–10h e 10h–11h não se sobrepõem.

### Arquivo `nucleo.py`

```python
from dataclasses import dataclass
from datetime import datetime
from typing import Protocol


@dataclass(frozen=True)
class Reserva:
    sala: str
    inicio: datetime
    fim: datetime

    def __post_init__(self):
        if not self.sala.strip():
            raise ValueError("Informe a sala.")
        if self.inicio.tzinfo is not None or self.fim.tzinfo is not None:
            raise ValueError("Use horários locais, sem informação de fuso.")
        if self.fim <= self.inicio:
            raise ValueError("O término deve ser posterior ao início.")

    def conflita_com(self, outra: "Reserva") -> bool:
        return (
            self.sala == outra.sala
            and self.inicio < outra.fim
            and outra.inicio < self.fim
        )


# Porta de saída: operações de armazenamento exigidas pelo núcleo.
class RepositorioReservas(Protocol):
    def listar(self) -> list[Reserva]: ...

    def salvar(self, reserva: Reserva) -> None: ...


class ServicoReservas:
    def __init__(self, repositorio: RepositorioReservas):
        self._repositorio = repositorio

    # Operação da porta de entrada do núcleo.
    def reservar(self, sala: str, inicio: datetime, fim: datetime) -> Reserva:
        reserva = Reserva(sala.strip().upper(), inicio, fim)
        for existente in self._repositorio.listar():
            if reserva.conflita_com(existente):
                raise ValueError("A sala já está reservada nesse horário.")
        self._repositorio.salvar(reserva)
        return reserva

    def listar(self) -> list[Reserva]:
        return sorted(
            self._repositorio.listar(),
            key=lambda reserva: (reserva.inicio, reserva.sala),
        )
```

**Conversem no grupo:** por que `input()`, `print()` e SQL não aparecem aqui? Como executar o serviço sem uma interface de usuário?

## 5. Implementar o adaptador em memória

Esse adaptador implementa os métodos da porta de saída. Ele devolve uma cópia da lista para impedir a alteração direta da coleção interna por quem a consulta. Como `Reserva` é imutável, seus atributos também não podem ser modificados após a criação.

### Arquivo `adaptador_memoria.py`

```python
from nucleo import Reserva


class RepositorioMemoria:
    def __init__(self):
        self._reservas: list[Reserva] = []

    def listar(self) -> list[Reserva]:
        return list(self._reservas)

    def salvar(self, reserva: Reserva) -> None:
        self._reservas.append(reserva)
```

## 6. Implementar o adaptador de terminal

O terminal transforma texto em datas e apresenta mensagens. A regra de sobreposição continua no núcleo. Uma interface web futura deverá fazer uma conversão semelhante antes de chamar o mesmo serviço.

### Arquivo `adaptador_terminal.py`

```python
from datetime import datetime
from nucleo import ServicoReservas


def executar_terminal(servico: ServicoReservas):
    while True:
        opcao = input("\n1 - Reservar | 2 - Listar | 0 - Sair: ").strip()
        if opcao == "0":
            return
        if opcao == "1":
            try:
                sala = input("Sala: ")
                inicio = datetime.strptime(
                    input("Início (AAAA-MM-DD HH:MM): "), "%Y-%m-%d %H:%M"
                )
                fim = datetime.strptime(
                    input("Fim (AAAA-MM-DD HH:MM): "), "%Y-%m-%d %H:%M"
                )
                servico.reservar(sala, inicio, fim)
                print("Reserva criada.")
            except ValueError as erro:
                print(f"Não foi possível reservar: {erro}")
        elif opcao == "2":
            reservas = servico.listar()
            if not reservas:
                print("Nenhuma reserva cadastrada.")
            for reserva in reservas:
                print(
                    f"{reserva.sala}: {reserva.inicio:%d/%m/%Y %H:%M} "
                    f"até {reserva.fim:%d/%m/%Y %H:%M}"
                )
        else:
            print("Opção inválida.")
```

## 7. Fazer a primeira composição

Neste momento, usem este conteúdo provisório em `main.py`:

```python
from adaptador_memoria import RepositorioMemoria
from adaptador_terminal import executar_terminal
from nucleo import ServicoReservas


def main():
    repositorio = RepositorioMemoria()
    servico = ServicoReservas(repositorio)
    executar_terminal(servico)


if __name__ == "__main__":
    main()
```

Executem:

```sh
python main.py
```

O serviço recebe o repositório pronto. Isso é injeção de dependência: o serviço não decide qual implementação de armazenamento construir.

### Experimento com memória

Cadastrem a sala `A101`, início `2026-11-03 09:00` e término `2026-11-03 10:00`. Listem as reservas, saiam pela opção `0` e iniciem novamente. A lista estará vazia, pois cada execução cria um novo repositório em memória.

Antes da próxima etapa, anotem quais arquivos acreditam que precisarão mudar para persistir os dados.

## 8. Evoluir para o adaptador SQLite

O novo adaptador transforma objetos em registros SQL e registros em objetos. Datas são armazenadas como texto ISO. O `id` é interno ao banco e ainda não é usado pelo domínio.

### Arquivo `adaptador_sqlite.py`

```python
import sqlite3
from contextlib import closing
from datetime import datetime
from pathlib import Path
from nucleo import Reserva


class RepositorioSQLite:
    def __init__(self, arquivo: str | Path):
        self._arquivo = str(arquivo)
        with closing(sqlite3.connect(self._arquivo)) as conexao, conexao:
            conexao.execute("""
                CREATE TABLE IF NOT EXISTS reservas (
                    id INTEGER PRIMARY KEY,
                    sala TEXT NOT NULL,
                    inicio TEXT NOT NULL,
                    fim TEXT NOT NULL
                )
            """)

    def listar(self) -> list[Reserva]:
        with closing(sqlite3.connect(self._arquivo)) as conexao, conexao:
            registros = conexao.execute("""
                SELECT sala, inicio, fim FROM reservas ORDER BY inicio, sala
            """).fetchall()
        return [
            Reserva(sala, datetime.fromisoformat(inicio), datetime.fromisoformat(fim))
            for sala, inicio, fim in registros
        ]

    def salvar(self, reserva: Reserva) -> None:
        with closing(sqlite3.connect(self._arquivo)) as conexao, conexao:
            conexao.execute(
                "INSERT INTO reservas (sala, inicio, fim) VALUES (?, ?, ?)",
                (reserva.sala, reserva.inicio.isoformat(), reserva.fim.isoformat()),
            )
```

Os parâmetros `?` mantêm os valores separados do texto SQL. O gerenciador de contexto da conexão confirma a transação quando a operação termina com sucesso e a desfaz em caso de erro. O `closing` fecha a conexão ao sair do bloco; o contexto da conexão, sozinho, gerencia a transação sem fechá-la.

Usem um caminho de arquivo, como no exemplo. Não substituam por `":memory:"` nesta implementação: cada método abre uma conexão nova, e um banco SQLite em memória seria diferente em cada conexão.

## 9. Selecionar o adaptador na composição

Agora substituam o `main.py` provisório pela versão completa:

### Arquivo `main.py`

```python
import argparse
from pathlib import Path
from adaptador_memoria import RepositorioMemoria
from adaptador_sqlite import RepositorioSQLite
from adaptador_terminal import executar_terminal
from nucleo import ServicoReservas


def main():
    parser = argparse.ArgumentParser(description="Reservas com arquitetura hexagonal")
    parser.add_argument("--armazenamento", choices=["memoria", "sqlite"], default="memoria")
    opcoes = parser.parse_args()
    if opcoes.armazenamento == "sqlite":
        arquivo = Path(__file__).with_name("reservas.db")
        repositorio = RepositorioSQLite(arquivo)
    else:
        repositorio = RepositorioMemoria()
    servico = ServicoReservas(repositorio)
    executar_terminal(servico)


if __name__ == "__main__":
    main()
```

Para usar memória:

```sh
python main.py --armazenamento memoria
```

Para usar SQLite:

```sh
python main.py --armazenamento sqlite
```

O arquivo `reservas.db` fica ao lado de `main.py`, mesmo se o programa for iniciado a partir de outro diretório. O núcleo e o adaptador de terminal permanecem iguais na troca de persistência.

### Experimento com persistência

1. Iniciem o programa com SQLite e cadastrem uma reserva.
2. Saiam e iniciem novamente com SQLite. Confirmem que a reserva permanece.
3. Tentem cadastrar uma reserva sobreposta. Confirmem a rejeição.
4. Iniciem com memória. Confirmem que essa lista é independente do banco.
5. Voltem para SQLite. Os dados anteriores devem continuar disponíveis.

## 10. Verificar as regras com os dois adaptadores

Os mesmos cenários devem funcionar com memória e SQLite. O banco usado nos testes é temporário e não altera `reservas.db`.

### Arquivo `test_reservas.py`

```python
import tempfile
import unittest
from datetime import datetime
from pathlib import Path
from adaptador_memoria import RepositorioMemoria
from adaptador_sqlite import RepositorioSQLite
from nucleo import ServicoReservas


def horario(hora, minuto=0):
    return datetime(2026, 11, 3, hora, minuto)


# Os mesmos cenários devem funcionar com os dois adaptadores.
class CenariosReservas:
    def test_cria_e_normaliza_sala(self):
        self.servico.reservar(" a101 ", horario(9), horario(10))
        self.assertEqual(self.servico.listar()[0].sala, "A101")

    def test_rejeita_sobreposicoes(self):
        self.servico.reservar("A101", horario(9), horario(10))
        intervalos = [
            (horario(9, 30), horario(10, 30)),
            (horario(8, 30), horario(9, 30)),
            (horario(9, 15), horario(9, 45)),
            (horario(8), horario(11)),
            (horario(9), horario(10)),
        ]
        for inicio, fim in intervalos:
            with self.subTest(inicio=inicio), self.assertRaises(ValueError):
                self.servico.reservar("a101", inicio, fim)
        self.assertEqual(len(self.servico.listar()), 1)

    def test_permite_consecutivas_e_salas_distintas(self):
        self.servico.reservar("A101", horario(9), horario(10))
        self.servico.reservar("A101", horario(10), horario(11))
        self.servico.reservar("A102", horario(9), horario(10))
        self.assertEqual(len(self.servico.listar()), 3)

    def test_rejeita_dados_invalidos(self):
        for sala, inicio, fim in [
            (" ", horario(9), horario(10)),
            ("A101", horario(10), horario(9)),
            ("A101", horario(9), horario(9)),
        ]:
            with self.subTest(sala=sala, inicio=inicio), self.assertRaises(ValueError):
                self.servico.reservar(sala, inicio, fim)


class TesteMemoria(CenariosReservas, unittest.TestCase):
    def setUp(self):
        self.servico = ServicoReservas(RepositorioMemoria())


class TesteSQLite(CenariosReservas, unittest.TestCase):
    def setUp(self):
        pasta = tempfile.TemporaryDirectory()
        self.addCleanup(pasta.cleanup)
        self.arquivo = Path(pasta.name) / "teste.db"
        self.servico = ServicoReservas(RepositorioSQLite(self.arquivo))

    def test_persiste_ao_reabrir(self):
        self.servico.reservar("A101", horario(9), horario(10))
        outro_servico = ServicoReservas(RepositorioSQLite(self.arquivo))
        self.assertEqual(len(outro_servico.listar()), 1)


if __name__ == "__main__":
    unittest.main()
```

Executem:

```sh
python -m unittest -v
```

O resultado esperado é **9 testes aprovados**. Alguns testes contêm vários cenários, como conflito parcial, intervalo contido e intervalos idênticos.

| Experimento | Resultado esperado |
|---|---|
| A101 das 09h às 10h e depois das 09h30 às 10h30 | Segunda reserva rejeitada |
| A101 das 09h às 10h e depois das 10h às 11h | Ambas aceitas |
| A101 e A102 no mesmo horário | Ambas aceitas |
| Término igual ou anterior ao início | Reserva rejeitada |
| Nome da sala contendo apenas espaços | Reserva rejeitada |
| Reiniciar com memória | Reservas perdidas |
| Reiniciar com SQLite | Reservas preservadas |

## 11. Modificação

Escolham pelo menos uma modificação e acrescentem testes.

### Desafio A: Limitar a duração

Permitam reservas de no máximo duas horas. Identifiquem a camada responsável. Verifiquem uma reserva de exatamente duas horas e outra que exceda o limite. A regra deve funcionar com os dois adaptadores sem duplicação.

### Desafio B: Consultar por sala

Acrescentem uma operação de consulta por sala no serviço e uma opção no terminal. Decidam se o filtro pode usar `listar()` ou se vale ampliar a porta de saída com uma consulta específica. Expliquem a escolha considerando volume de dados.

### Desafio C: Acrescentar outra entrada

Criem um pequeno script que instancie o serviço e registre uma reserva diretamente com objetos `datetime`, sem usar o terminal interativo. Expliquem por que esse script também é um adaptador de entrada.

### Desafio D: Planejar a interface web

Descrevam como uma requisição HTTP seria traduzida em uma chamada a `reservar`. Identifiquem onde converter datas, onde decidir se há conflito e onde transformar a resposta em HTML. A implementação web é uma extensão; não faz parte do código deste tutorial.

## 12 Discutir os limites arquiteturais

**Manutenibilidade:** a troca de persistência preserva o núcleo. Relacionem isso à facilidade de mudar tecnologia sem reescrever regras de negócio. O custo é manter contratos, adaptadores e código de composição.

**Desempenho:** a criação de cada reserva consulta todos os registros. Isso simplifica o exemplo, mas pode ficar caro com muitos dados. Proponham uma consulta por sala e intervalo na porta de saída, sem expor SQL ao serviço.

**Concorrência:** a leitura de conflitos e a gravação são operações separadas. Dois processos podem ler os mesmos dados e aceitar reservas incompatíveis. As transações individuais do adaptador não tornam o caso de uso inteiro atômico. Uma evolução deve coordenar verificação e gravação na mesma transação, com bloqueio ou estratégia apropriada. Discutam como o contrato poderia expressar essa garantia e como testá-la.

**Escopo:** persistência não equivale a segurança ou disponibilidade. Este exemplo não possui autenticação, autorização ou controle de acesso por usuário e não demonstra atendimento aos RNFs de um sistema completo.

