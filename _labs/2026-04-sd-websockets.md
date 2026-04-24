---
title: "Sistemas Distribuídos - Lab Prático WebSocket"
collection: labs
type: "Lab"
permalink: /labs/2026-04-23-sd-websockets
date: 2026-04-23
location: "Ribeirão Preto, Brazil"
---

# Lab Prático: Comunicação WebSocket Cliente-Servidor (Python)

## 1. Objetivo do laboratório
Implementar um canal de comunicação persistente, simulando um servidor que recebe mensagens e as ecoa de volta para o cliente.

## 2. Pré-requisitos & Configuração do Ambiente Virtual

**Por que usar `venv`?**
Um ambiente virtual cria uma cópia isolada do Python no seu projeto. Isso garante que todas as bibliotecas instaladas (`websockets`, por exemplo) só existam para este laboratório e não interfiram em outros projetos ou na instalação global do sistema.

### Passo 2.1: Criação do Ambiente Virtual
Abra o terminal no diretório onde você salvará os arquivos `server.py` e `client.py`.

**Comando Universal:**
```bash
python3 -m venv venv
```

### Passo 2.2: Ativação do Ambiente Virtual
Você deve *ativar* o ambiente para que os comandos subsequentes usem as bibliotecas isoladas.

```bash
source venv/bin/activate
```

> Após a ativação, você verá `(venv)` no início da linha de comando, indicando que está isolado.

#### Passo 2.3: Instalação das Dependências
Agora que o ambiente está ativo, instalamos as bibliotecas necessárias *dentro* dele.

```bash
pip install websockets
```
## 3. Conceitos Envolvidos
*   **Programação Assíncrona (`async`/`await`):** Em vez de esperar que uma tarefa termine antes de começar a próxima (síncrono), o código assíncrono permite que o programa "pause" em um ponto e execute outras tarefas enquanto espera por I/O (Input/Output), como receber dados da rede. Isso é vital para servidores que precisam gerenciar milhares de conexões simultaneamente.
*   **Servidor WebSocket:** É a aplicação que fica rodando, escutando continuamente uma porta específica (`localhost:8765`). Ele deve estar sempre pronto para aceitar novas conexões e processar os dados recebidos em tempo real.
*   **Cliente WebSocket:** É o script que inicia a conexão com o servidor, envia um dado e espera receber a resposta no mesmo canal.

## 4. Passo a passo (Implementação)

Este laboratório requer dois arquivos separados: `server.py` e `client.py`.

### Parte A: O Servidor (`server.py`)
O servidor deve ser o primeiro a rodar, pois ele é quem "abre as portas". Ele usará um *handler* que será chamado toda vez que um cliente se conectar.

```python
# server.py
import asyncio
import websockets

async def echo(websocket, web_context):
    """Função de tratamento (handler) chamada para cada novo cliente."""
    print("Novo cliente conectado!")
    try:
        # Loop infinito que espera por mensagens do cliente
        async for message in websocket:
            print(f"Servidor recebeu: {message}")
            
            # Ação de Echo: O servidor simplesmente envia o que recebeu de volta.
            response = f"Servidor confirmou recebimento: {message}"
            await websocket.send(response)
            print("Mensagem ecoada com sucesso.")

    except websockets.exceptions.ConnectionClosedOK:
        # Captura quando o cliente se desconecta normalmente
        print("Cliente desconectado de forma limpa.")
    finally:
        # Garante que a mensagem de despedida seja enviada
        pass 

async def main():
    # Inicia o servidor na porta 8765
    async with websockets.serve(echo, "localhost", 8765):
        print("=============================================")
        print("Servidor WebSocket rodando em ws://localhost:8765")
        print("Pressione Ctrl+C para parar o servidor.")
        await asyncio.Future()  # Mantém o servidor rodando indefinidamente

if __name__ == "__main__":
    asyncio.run(main())
```

### Parte B: O Cliente (`client.py`)
O cliente é quem inicia a comunicação e testa se o ciclo de vida funciona.

```python
# client.py
import asyncio
import websockets

async def run_client():
    uri = "ws://localhost:8765"
    print(f"Tentando conectar ao servidor em {uri}...")
    try:
        # 1. Conecta-se ao servidor
        async with websockets.connect(uri) as websocket:
            print("Conexão estabelecida com sucesso!")

            # 2. Envia a primeira mensagem (Teste de envio)
            mensagem_enviada = "Olá, este é o cliente testando a conexão!"
            await websocket.send(mensagem_enviada)
            print(f"\n>>> Cliente enviou: '{mensagem_enviada}'")

            # 3. Espera e recebe a resposta do servidor (Teste de recebimento)
            resposta = await websocket.recv()
            print("\nCliente recebeu o eco do Servidor:")
            print(f"   <<< {resposta}")

    except ConnectionRefusedError:
        print("ERRO: Não foi possível conectar. Certifique-se de que 'server.py' está rodando primeiro!")
    except Exception as e:
        print(f"Um erro ocorreu no cliente: {e}")


if __name__ == "__main__":
    asyncio.run(run_client())
```

## 5. Demonstração Prática (Passos de Execução)

1.  **Terminal 1:** Execute o servidor primeiro.
    ```bash
    python server.py
    # Saída esperada: Servidor WebSocket rodando em ws://localhost:8765
    ```
2.  **Terminal 2:** Execute o cliente.
    ```bash
    python client.py
    ```

## 6. Resultado Esperado (Output)

**No Terminal 1 (Servidor):**
```
=============================================
Servidor WebSocket rodando em ws://localhost:8765
Pressione Ctrl+C para parar o servidor.
Novo cliente conectado!
Servidor recebeu: Olá, este é o cliente testando a conexão!
Mensagem ecoada com sucesso.
```

**No Terminal 2 (Cliente):**
```
Tentando conectar ao servidor em ws://localhost:8765...
Conexão estabelecida com sucesso!

Cliente enviou: 'Olá, este é o cliente testando a conexão!'

Cliente recebeu o eco do Servidor:
   >>> Servidor confirmou recebimento: Olá, este é o cliente testando a conexão!
```

## 7. Atividade Extra (Para Aprofundamento)
Modifique o `server.py` para que ele não apenas "ecoar" a mensagem, mas também **identifique** quem enviou e registre isso em um arquivo de log (`log.txt`).

> **Dica:** Adicione uma lógica no servidor para verificar se a mensagem recebida contém um identificador (ex: `[USER_ID]`) e use esse ID na resposta ecoada, simulando que o servidor está processando dados de diferentes fontes.