---
title: "Introdução ao Docker"
collection: labs
type: "Lab"
permalink: /labs/intro-docker
date: 2026-04-30
location: "Ribeirão Preto, Brazil"
---

## O conceito de Contêiner

Basicamente, um contêiner é apenas um processo (ou conjunto de processos) especialmente restrito, sob o controle do gerenciador de contêineres. O gerenciador de contêineres em si é apenas um processo (ou conjunto de processos), sob o controle do Sistema Operacional. Embora não haja Sistemas Operacionais convidados com a virtualização de contêineres, o único Sistema Operacional pode ainda ser chamado de "Sistema Operacional hospedeiro".

Sendo processos, todos os contêineres compartilham o mesmo kernel do Sistema Operacional, o que induz uma sobrecarga menor do que o uso de um SO separado por VM. Assim, os contêineres são geralmente mais eficientes do que as VMs.

![](https://oer.gitlab.io/oer-courses/it-systems/figures/OS/containers.png)

Em particular, podemos esperar que um novo contêiner, como processo, possa ser iniciado muito mais rápido do que uma nova VM, que essencialmente inicializa um novo SO.


Nota: Se você não está familiarizado(a) com o conceito de contêiner (ex.: nunca usou a ferramenta Docker), leia o artigo da [IBM](https://www.ibm.com/br-pt/think/topics/containers) sobre contêiner *antes* de continuar esta atividade.

Para isolar diferentes contêineres uns dos outros, múltiplos mecanismos de restrição são aplicados. Primeiramente, diferentes contêineres são gerenciados como processos distintos com espaços de endereço virtuais isolados. Adicionalmente, no caso do kernel Linux, namespaces limitam o que é visível dentro dos contêineres. Grupos de controle limitam os recursos disponíveis dentro dos contêineres. O sistema de arquivos dentro de um contêiner é amplamente independente do sistema de arquivos do hospedeiro, pode consistir em múltiplas camadas, que são sobrepostas umas sobre as outras, com um mecanismo de cópia na gravação que evita a cópia de todos os arquivos para novos contêineres enquanto nenhuma operação de gravação ocorrer.

Com Docker, e outras tecnologias de containerização, imagens servem como plantas para ambientes de execução virtualizados.

Para uso em produção, ambientes de execução virtualizados devem ser implantáveis de forma reproduzível para garantir que o software seja sempre executado em seu ambiente necessário. Em particular, a síndrome "funciona na minha máquina" precisa ser evitada, onde um desenvolvedor instala todos os tipos de bibliotecas e dependências na máquina de desenvolvimento, mas esquece de documentar as peças necessárias. Mais tarde, no ambiente de produção, dependências podem estar faltando ou serem instaladas em versões incompatíveis, potencialmente levando a bugs sutis ou falhas.

Para prevenir tais falhas, cada imagem é descrita por um **Dockerfile**, que é uma receita de construção em um formato de texto simples. Ele começa com uma imagem base, por exemplo, uma variante do SO, e descreve quais componentes devem ser instalados.

Termos principais:

- **Container**: Instância em execução de uma imagem; possui namespace isolado (cgroup, PID, UTS) mas compartilha kernel do host.
- **Imagem**: Camada imutável e portátil que descreve a aplicação + dependências. Cada camada é armazenada em formato tarball com metadados. 
- **Dockerfile**: Arquivo de texto contendo instruções (`FROM`, `RUN`, `COPY`, `CMD`…) que definem como construir uma imagem.
- **Registry**: Repositório remoto que armazena e distribui imagens. Pode ser público (DockerHub) ou privado (Harbor, GitLab Container Registry).
- **DockerHub** (https://hub.docker.com/): Registro público oficial da Docker Inc.; hospeda milhares de imagens oficiais e de terceiros, além de suporte a organizações e repositórios privados.
- **Volume**: Persistência de dados fora do ciclo de vida do container; mapeamento de diretórios do host para o container.

**Referências adicionais**:
- Artigo: https://www.datacamp.com/pt/blog/learn-docker
- Vídeo: [Aprenda Docker do Zero, por Fernanda Kipper](https://youtu.be/DdoncfOdru8?si=ZaWT9vtlchMFFZd9)
- Ferramenta: https://labex.io/


## Instalação Docker

Siga as instruções em https://docs.docker.com/get-started/get-docker/ ou https://douglasnickson.com.br/2023/05/06/guia-completo-de-instalacao-do-docker/

Usando o terminal:

1. **Windows / macOS** – Baixe e instale o Docker Desktop a partir do site oficial:  
   `https://www.docker.com/products/docker-desktop`
2. **Linux (Ubuntu/Debian)** – Execute:
   ```bash
   sudo apt-get update
   sudo apt-get install -y docker.io
   sudo systemctl enable --now docker
   ```
3. Verifique a instalação:  
   ```bash
   docker --version
   ```

Verifique se a instalação funcionou utilizando `docker run hello-world`

## Comandos Essenciais

| Categoria | Comando | Descrição |
|-----------|---------|-----------|
| **Imagem** | `docker pull <imagem>` | Baixa uma imagem do registry. |
| | `docker build -t <nome:tag> .` | Constrói uma imagem a partir de um Dockerfile no diretório atual. |
| | `docker images` | Lista imagens locais. |
| | `docker rmi <id/imagem>` | Remove uma imagem local. |
| **Container** | `docker run -d --name <nome> <imagem>` | Cria e inicia um container em modo *detached*. |
| | `docker ps` | Lista containers ativos. |
| | `docker ps -a` | Lista todos os containers (ativos + parados). |
| | `docker stop <id/nome>` | Para a execução de um container. |
| | `docker rm <id/nome>` | Remove um container parado. |
| **Logs** | `docker logs <nome/id>` | Exibe o output do container. |
| **Exec** | `docker exec -it <container> /bin/bash` | Abre shell interativo dentro de um container em execução. |
| **Volumes** | `docker volume create <nome>` | Cria volume persistente. |
| | `docker run -v <volume>:<caminho/destino> ...` | Monta volume no container. |
| **Redes** | `docker network ls` | Lista redes existentes. |
| | `docker network create <rede>` | Cria nova rede. |

## Exercício 1: Servidor Web

Crie um contêiner com [Nginx](https://hub.docker.com/_/nginx) que sirva uma página HTML customizada (index.html). Monte um volume local com esse arquivo para que ele apareça na raiz do site (/usr/share/nginx/html). Acesse a página via http://localhost.

## Exercício 2: Variáveis de ambiente

Construa um container para o banco de dados postgres (https://hub.docker.com/_/postgres). O container deve receber, por meio de variáveis de ambiente:

- `PGUSER` – usuário do banco;
- `PGPASSWORD` – senha desse usuário.

Execute o container em modo interativo (como na Atividade 1) e execute o comando psql para criar um executar comandos no banco de dados (ex.: `show databases;`)

## Exercício 3: Container Interativo

Objetivo: Iniciar um container a partir da imagem oficial *Ubuntu 22.04*, explorar sua estrutura de diretórios e instalar o utilitário `curl` via `apt`, confirmando que a instalação ocorreu com sucesso.

### 1. Criação do Container Interativo 

```bash
docker run -it --name ubuntu-ex03 ubuntu:22.04 bash
```

| Flag | Significado |
|------|-------------|
| `-i`  | Mantém o *STDIN* aberto (interatividade) |
| `-t`  | Aloca um terminal pseudo‑TTY |
| `--name ubuntu-ex03` | Nome que identificará o container no Docker Hub local |
| `ubuntu:22.04` | Imagem oficial do Ubuntu, versão 22.04 LTS |
| `bash` | Comando a ser executado (abre o shell Bash) |

> **Obs.:** Ao executar o comando acima você será direcionado para um prompt de *shell* dentro do container.


### 2. Navegação pelo Sistema de Arquivos

No terminal do container, realize as seguintes operações:

```bash
# Visualizar arquivos e diretórios no diretório atual
ls

# Mudar para a pasta /etc
cd /etc

# Listar conteúdo da nova localização
ls

# Voltar ao diretório anterior
cd ..
```

> **Explicação**:  
> - `ls` exibe o conteúdo do diretório corrente.  
> - `cd <caminho>` altera o diretório de trabalho para `<caminho>`.  
> - `cd ..` volta um nível acima na hierarquia.

### 3. Atualização dos Índices e Instalação do `curl`

```bash
# Atualizar a lista de pacotes disponíveis nos repositórios
apt update

# Instalar o pacote curl, aceitando automaticamente todas as solicitações interativas
apt install curl -y
```

> **Detalhes**  
> - `apt update` baixa os *indices* dos repositórios configurados.  
> - `-y` evita que o processo de instalação pause para confirmação manual.


### 4. Validação da Instalação

```bash
curl --version
```

A saída deve apresentar a versão do `curl`, algo similar a:

```
curl 7.xx.x (x86_64-pc-linux-gnu) libcurl/7.xx.x OpenSSL/1.1.1z zlib/1.2.11 ...
```

> Se o comando retornar a versão, a instalação foi concluída com êxito.

### 5. Encerramento

Para sair do container e removê‑lo da memória:

```bash
exit          # encerra a sessão Bash
docker rm -f ubuntu-ex03   # remove o container criado
```

> **Dica**: Se desejar manter o container em execução após fechar o terminal, utilize `docker run -d` ou acione `docker attach`.

## Exercício 4

Suba um conteiner do [EmulatorJS](https://hub.docker.com/r/linuxserver/emulatorjs) para jogar algum jogo feito pela comunidade (escolha o jogo em https://nes-open-db.github.io/roms/).
