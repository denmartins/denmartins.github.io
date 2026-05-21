---
title: "Introdução ao Docker: Parte 2"
collection: labs
type: "Lab"
permalink: /labs/intro-docker-part2
date: 2026-04-30
location: "Ribeirão Preto, Brazil"
---


Em ambientes modernos, as aplicações raramente são monolíticas; elas são compostas por vários serviços interconectados (como um frontend, um backend de API e um banco de dados). O Docker Compose é o seu aliado para orquestrar esses sistemas multi-container de forma simples e reprodutível.

O Docker Compose é uma ferramenta projetada para **definir e executar aplicações multi-container** no Docker. Ele utiliza um arquivo de configuração (tipicamente `compose.yaml`) para gerenciar os serviços que compõem sua aplicação.

### Por Que Usar o Docker Compose?

O uso do Compose traz benefícios cruciais, especialmente em fluxos de trabalho de desenvolvimento rápido e testes automatizados:

1.  **Controle Simplificado:** Você define e gerencia toda a sua pilha de aplicações em um único arquivo YAML, simplificando a orquestração e replicação.
2.  **Ambiente Isolado e Reprodutível:** Permite que os serviços sejam executados juntos em um ambiente isolado. Ele documenta e configura todas as dependências da aplicação (como bancos de dados, filas e caches).
3.  **Desenvolvimento Rápido:** O Compose armazena em cache as configurações. Se um serviço não foi alterado, ele reutiliza os containers existentes, acelerando a iteração.
4.  **Colaboração Eficiente:** Arquivos YAML podem ser facilmente compartilhados, facilitando a colaboração entre equipes de desenvolvimento e operações, o que é o cerne do movimento DevOps.

### O Processo de Três Etapas do Docker Compose

Usar o Docker Compose é um processo rápido de três etapas:

1.  **Defina seu ambiente** com um `Dockerfile` (garantindo a reprodutibilidade em qualquer lugar).
2.  **Defina os serviços** que compõem sua aplicação no arquivo `compose.yaml`.
3.  **Execute** a aplicação com um único comando: `docker compose up`.


### Atividade 1: Aplicação Web Multi-Container

Vamos usar um exemplo prático de um contador de acessos simples, composto por um **serviço web Flask (Python)** e um **serviço de cache Redis**.

```
git clone https://github.com/docker/awesome-compose.git
cd awesome-compose
cd flask-redis
```

Então, siga os passos em: https://github.com/docker/awesome-compose/tree/master/flask-redis

### Atividade 2: Aplicação Nextcloud com Postgres

O Nextcloud é um software que permite criar e gerenciar seu próprio cloud storage sem depender de provedores externos como Google Drive ou Dropbox. Ele foi desenvolvido a partir do fork do ownCloud, mas evoluiu para se tornar uma solução robusta, segura e altamente extensível.

| Aspecto | O que é | Por que importa |
|---------|---------|-----------------|
| **Código aberto** | Todo o código fonte está disponível publicamente (licença AGPLv3). | Transparência, auditabilidade e liberdade de personalização. |
| **Privacidade & Segurança** | Criptografia ponta‑a‑ponta opcional, autenticação multifator, controle granular de permissões. | Protege dados sensíveis contra vazamentos e ataques. |
| **Escalabilidade** | Pode ser instalado em um servidor doméstico, em um datacenter corporativo ou na nuvem pública. | Flexível para qualquer tamanho de operação. |
| **Ecossistema de apps** | Mais de 200 plugins (agenda, chat, colaboração em documentos, OCR, etc.). | Amplia funcionalidades sem reescrever código. |
| **Integração** | Compatibilidade com WebDAV, CalDAV, CardDAV; APIs RESTful; integração com LDAP/Active Directory. | Facilita a adoção em ambientes já existentes. |

**Como funciona na prática**:

1. **Instalação** – Pode ser feita via Docker, Snap, ou manualmente em servidores Linux, Windows ou macOS.
2. **Armazenamento** – Os arquivos são armazenados no sistema de arquivos do servidor ou em back‑ends como S3, Ceph, etc.
3. **Acesso** – Usuários acessam via web (Nextcloud Web), clientes desktop (Windows/macOS/Linux) e apps móveis (iOS/Android).
4. **Colaboração** – O Nextcloud Talk permite videochamadas; o OnlyOffice ou Collabora Online possibilita edição simultânea de documentos.
5. **Automação & IA** – Plugins de OCR, reconhecimento de imagens, análise de dados e integração com ferramentas de ML podem ser adicionados.

**Por que se interessar?**

- **Controle total dos dados**: Ideal para projetos sensíveis onde a conformidade (GDPR, LGPD) é crucial.
- **Pipeline de dados integrado**: Arquivos de entrada/saída, logs e resultados podem ser armazenados na mesma plataforma, facilitando a reproducibilidade.
- **Integração com notebooks**: JupyterHub pode ser configurado para usar o Nextcloud como backend de arquivos, permitindo colaboração em tempo real.
- **Extensões de IA**: Existem apps que permitem treinar modelos diretamente no servidor ou enviar dados para serviços externos de forma segura.

Assim, o Nextcloud não é apenas um armazenamento – é uma plataforma completa que pode se transformar no backbone da sua infraestrutura de ciência de dados.

Para criar uma instância de Nextcloud usando docker (com banco de dados Postgres como armazenamento), volte ao diretório `awesome-compose` e navegue até o diretório `nextcloud-postgres` 

```
cd ..
cd nextcloud-postgres
```

Então, siga os passos em: https://github.com/docker/awesome-compose/tree/master/nextcloud-postgres


### Gerenciamento e Limpeza

Quando terminar, você pode parar os serviços. Se você executou o Compose no modo *foreground* (sem `-d`), pressione `CTRL+C` no terminal.

Para parar os serviços e remover os containers, use:

```bash
$ docker compose down
```
Se você desejar rodar em segundo plano (modo *detached*):

```bash
$ docker compose up -d
```
E para listar os serviços em execução:

```bash
$ docker compose ps
```

### Contexto Avançado: Modularização e Orquestração

Embora o Docker Compose seja excelente para desenvolvimento e implantações em *single host* (máquina única), para orquestração em larga escala e em ambientes de produção com múltiplos servidores, ferramentas mais robustas como o **Kubernetes (K8s)** são geralmente usadas. O Compose serve como um excelente trampolim para entender a lógica de orquestração declarativa que o Kubernetes utiliza (especificada em arquivos YAML).

Recomendo fortemente que vocês explorem o restante dos comandos do Compose (`docker compose --help`) e pratiquem a criação de serviços adicionais, como bancos de dados persistentes, utilizando **Volumes** (que armazenam dados persistentes além do ciclo de vida do container).
