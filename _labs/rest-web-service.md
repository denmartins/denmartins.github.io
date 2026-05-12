---
title: "Sistemas Distribuídos - Lab Prático REST Web Service"
collection: labs
type: "Lab"
permalink: /labs/web-services-rest
date: 2026-05-13
location: "Ribeirão Preto, Brazil"
---

Neste laboratório, você irá construir uma REST API para gerenciamento de tarefas acadêmicas. A implementação será feita de forma incremental, em três partes:

1. **Parte 1:** CRUD de tarefas com banco SQLite
2. **Parte 2:** Assincronia e respostas parciais do servidor
3. **Parte 3:** Autenticação com JWT

A proposta é começar com uma API simples e funcional e, gradualmente, adicionar recursos mais avançados.

# Parte 1 — CRUD com SQLite

## 1. Objetivo da Parte 1

Nesta etapa, você irá criar uma API REST capaz de:

* cadastrar tarefas;
* listar tarefas;
* buscar tarefa por ID;
* atualizar tarefa;
* remover tarefa;
* armazenar dados em SQLite.



## 2. Estrutura Inicial do Projeto

Crie a seguinte estrutura:

```text
rest-api-lab/
├── main.py
├── requirements.txt
└── README.md
```



## 3. Instalação das Dependências

No arquivo `requirements.txt`, adicione:

```txt
fastapi
uvicorn
sqlmodel
```

Depois, no terminal:

```bash
python -m venv .venv
```

Ative o ambiente virtual.

No Windows:

```bash
.venv\Scripts\activate
```

No Linux/macOS:

```bash
source .venv/bin/activate
```

Instale as dependências:

```bash
pip install -r requirements.txt
```



## 4. Criando a Aplicação FastAPI

No arquivo `main.py`, comece com:

```python
from typing import Optional

from fastapi import FastAPI, HTTPException, status
from sqlmodel import Field, Session, SQLModel, create_engine, select

app = FastAPI(
    title="API de Tarefas Acadêmicas",
    description="REST API para gerenciamento de tarefas com FastAPI e SQLite.",
    version="1.0.0",
)
```

### Explicação

* `FastAPI` cria a aplicação web.
* `HTTPException` será usado para retornar erros HTTP.
* `SQLModel` será usado para definir modelos e interagir com o banco.
* `Session` representa uma conexão temporária com o banco.



## 5. Configurando o Banco SQLite

Ainda em `main.py`, adicione:

```python
DATABASE_URL = "sqlite:///database.db"

engine = create_engine(
    DATABASE_URL,
    echo=True,
    connect_args={"check_same_thread": False},
)
```

### Explicação

* `database.db` será o arquivo do banco SQLite.
* `echo=True` mostra no terminal os comandos SQL executados.
* `check_same_thread=False` é necessário para uso do SQLite com FastAPI em ambiente didático.



## 6. Criando o Modelo de Dados

Adicione o modelo `Task`:

```python
class Task(SQLModel, table=True):
    id: Optional[int] = Field(default=None, primary_key=True)
    title: str
    description: str
    completed: bool = False
```

### Explicação

Essa classe representa uma tabela no banco de dados.

Campos:

* `id`: identificador único da tarefa;
* `title`: título da tarefa;
* `description`: descrição;
* `completed`: indica se a tarefa foi concluída.



## 7. Criando Modelos de Entrada e Saída

Adicione:

```python
class TaskCreate(SQLModel):
    title: str
    description: str


class TaskUpdate(SQLModel):
    title: Optional[str] = None
    description: Optional[str] = None
    completed: Optional[bool] = None


class TaskRead(SQLModel):
    id: int
    title: str
    description: str
    completed: bool
```

### Explicação

Usamos modelos separados para diferentes finalidades:

* `TaskCreate`: dados necessários para criar uma tarefa;
* `TaskUpdate`: dados opcionais para atualizar uma tarefa;
* `TaskRead`: formato da resposta enviada ao cliente.

Essa separação evita expor campos internos desnecessários.



## 8. Criando as Tabelas no Banco

Adicione:

```python
def create_db_and_tables():
    SQLModel.metadata.create_all(engine)


@app.on_event("startup")
def on_startup():
    create_db_and_tables()
```

### Explicação

Quando a aplicação iniciar, o FastAPI executará `on_startup()` e criará as tabelas, caso ainda não existam.



## 9. Criando uma Sessão com o Banco

Adicione:

```python
def get_session():
    with Session(engine) as session:
        yield session
```

### Explicação

Cada requisição à API precisa acessar o banco. A função `get_session()` cria uma sessão temporária e a fecha automaticamente ao final da operação.



## 10. Endpoint Inicial

Adicione:

```python
@app.get("/")
def root():
    return {
        "message": "API de Tarefas Acadêmicas em execução.",
        "docs": "/docs",
    }
```

### Teste

Execute:

```bash
uvicorn main:app --reload
```

Acesse:

```text
http://127.0.0.1:8000
```



## 11. Criando Tarefas — POST

Adicione:

```python
@app.post("/tasks", response_model=TaskRead, status_code=status.HTTP_201_CREATED)
def create_task(task_create: TaskCreate):
    with Session(engine) as session:
        task = Task(
            title=task_create.title,
            description=task_create.description,
        )

        session.add(task)
        session.commit()
        session.refresh(task)

        return task
```

### Explicação

Esse endpoint cria uma nova tarefa.

Fluxo:

1. recebe os dados da tarefa;
2. cria um objeto `Task`;
3. salva no banco com `session.add()`;
4. confirma a operação com `session.commit()`;
5. atualiza o objeto com `session.refresh()` para obter o ID gerado.

### Teste no Swagger

Acesse:

```text
http://127.0.0.1:8000/docs
```

Teste o endpoint `POST /tasks` com:

```json
{
  "title": "Estudar REST",
  "description": "Revisar métodos HTTP e status codes."
}
```



## 12. Listando Tarefas — GET

Adicione:

```python
@app.get("/tasks", response_model=list[TaskRead])
def list_tasks():
    with Session(engine) as session:
        statement = select(Task)
        tasks = session.exec(statement).all()
        return tasks
```

### Explicação

Esse endpoint retorna todas as tarefas cadastradas.



## 13. Buscando Tarefa por ID — GET

Adicione:

```python
@app.get("/tasks/{task_id}", response_model=TaskRead)
def get_task(task_id: int):
    with Session(engine) as session:
        task = session.get(Task, task_id)

        if not task:
            raise HTTPException(
                status_code=status.HTTP_404_NOT_FOUND,
                detail="Tarefa não encontrada.",
            )

        return task
```

### Explicação

Se a tarefa existir, ela é retornada. Caso contrário, a API responde com erro `404 Not Found`.



## 14. Atualizando Tarefa — PUT

Adicione:

```python
@app.put("/tasks/{task_id}", response_model=TaskRead)
def update_task(task_id: int, task_update: TaskUpdate):
    with Session(engine) as session:
        task = session.get(Task, task_id)

        if not task:
            raise HTTPException(
                status_code=status.HTTP_404_NOT_FOUND,
                detail="Tarefa não encontrada.",
            )

        update_data = task_update.model_dump(exclude_unset=True)

        for key, value in update_data.items():
            setattr(task, key, value)

        session.add(task)
        session.commit()
        session.refresh(task)

        return task
```

### Explicação

`exclude_unset=True` garante que apenas os campos enviados na requisição sejam atualizados.

Exemplo:

```json
{
  "completed": true
}
```

Nesse caso, apenas o campo `completed` será alterado.



## 15. Removendo Tarefa — DELETE

Adicione:

```python
@app.delete("/tasks/{task_id}", status_code=status.HTTP_204_NO_CONTENT)
def delete_task(task_id: int):
    with Session(engine) as session:
        task = session.get(Task, task_id)

        if not task:
            raise HTTPException(
                status_code=status.HTTP_404_NOT_FOUND,
                detail="Tarefa não encontrada.",
            )

        session.delete(task)
        session.commit()

        return None
```

### Explicação

Esse endpoint remove uma tarefa existente. O status `204 No Content` indica que a operação foi realizada com sucesso, mas não há conteúdo para retornar.



## 16. Código Final da Parte 1

```python
from typing import Optional

from fastapi import FastAPI, HTTPException, status
from sqlmodel import Field, Session, SQLModel, create_engine, select

app = FastAPI(
    title="API de Tarefas Acadêmicas",
    description="REST API para gerenciamento de tarefas com FastAPI e SQLite.",
    version="1.0.0",
)

DATABASE_URL = "sqlite:///database.db"

engine = create_engine(
    DATABASE_URL,
    echo=True,
    connect_args={"check_same_thread": False},
)


class Task(SQLModel, table=True):
    id: Optional[int] = Field(default=None, primary_key=True)
    title: str
    description: str
    completed: bool = False


class TaskCreate(SQLModel):
    title: str
    description: str


class TaskUpdate(SQLModel):
    title: Optional[str] = None
    description: Optional[str] = None
    completed: Optional[bool] = None


class TaskRead(SQLModel):
    id: int
    title: str
    description: str
    completed: bool


def create_db_and_tables():
    SQLModel.metadata.create_all(engine)


@app.on_event("startup")
def on_startup():
    create_db_and_tables()


@app.get("/")
def root():
    return {
        "message": "API de Tarefas Acadêmicas em execução.",
        "docs": "/docs",
    }


@app.post("/tasks", response_model=TaskRead, status_code=status.HTTP_201_CREATED)
def create_task(task_create: TaskCreate):
    with Session(engine) as session:
        task = Task(
            title=task_create.title,
            description=task_create.description,
        )

        session.add(task)
        session.commit()
        session.refresh(task)

        return task


@app.get("/tasks", response_model=list[TaskRead])
def list_tasks():
    with Session(engine) as session:
        statement = select(Task)
        tasks = session.exec(statement).all()
        return tasks


@app.get("/tasks/{task_id}", response_model=TaskRead)
def get_task(task_id: int):
    with Session(engine) as session:
        task = session.get(Task, task_id)

        if not task:
            raise HTTPException(
                status_code=status.HTTP_404_NOT_FOUND,
                detail="Tarefa não encontrada.",
            )

        return task


@app.put("/tasks/{task_id}", response_model=TaskRead)
def update_task(task_id: int, task_update: TaskUpdate):
    with Session(engine) as session:
        task = session.get(Task, task_id)

        if not task:
            raise HTTPException(
                status_code=status.HTTP_404_NOT_FOUND,
                detail="Tarefa não encontrada.",
            )

        update_data = task_update.model_dump(exclude_unset=True)

        for key, value in update_data.items():
            setattr(task, key, value)

        session.add(task)
        session.commit()
        session.refresh(task)

        return task


@app.delete("/tasks/{task_id}", status_code=status.HTTP_204_NO_CONTENT)
def delete_task(task_id: int):
    with Session(engine) as session:
        task = session.get(Task, task_id)

        if not task:
            raise HTTPException(
                status_code=status.HTTP_404_NOT_FOUND,
                detail="Tarefa não encontrada.",
            )

        session.delete(task)
        session.commit()

        return None
```



# Parte 2 — Assincronia e Respostas Parciais

## 17. Objetivo da Parte 2

Nesta etapa, você irá:

* transformar endpoints em funções assíncronas;
* entender o uso de `async def`;
* implementar uma resposta parcial com `StreamingResponse`.

A ideia é simular um relatório de tarefas enviado aos poucos pelo servidor.



## 18. Atualizando as Dependências

No `requirements.txt`, mantenha:

```txt
fastapi
uvicorn
sqlmodel
```

Não é necessário instalar bibliotecas adicionais para esta etapa.



## 19. Importando Recursos para Streaming

No topo do arquivo, adicione:

```python
import asyncio
from typing import AsyncGenerator

from fastapi.responses import StreamingResponse
```

O bloco de imports ficará assim:

```python
import asyncio
from typing import Optional, AsyncGenerator

from fastapi import FastAPI, HTTPException, status
from fastapi.responses import StreamingResponse
from sqlmodel import Field, Session, SQLModel, create_engine, select
```



## 20. Transformando Endpoints em Assíncronos

Altere os endpoints de:

```python
def root():
```

para:

```python
async def root():
```

Faça o mesmo nos demais endpoints.

Exemplo:

```python
@app.get("/tasks", response_model=list[TaskRead])
async def list_tasks():
    with Session(engine) as session:
        statement = select(Task)
        tasks = session.exec(statement).all()
        return tasks
```

### Explicação

`async def` permite que uma função trabalhe com operações assíncronas. Neste laboratório, isso será usado principalmente no endpoint de streaming.

Observação importante: o SQLite usado neste exemplo ainda é acessado de forma síncrona. Para fins didáticos, manteremos essa abordagem. Em sistemas mais avançados, seria possível utilizar bibliotecas assíncronas de banco de dados.



## 21. Criando um Gerador Assíncrono

Adicione a função abaixo:

```python
async def task_stream(tasks: list[Task]) -> AsyncGenerator[str, None]:
    yield "Relatório parcial de tarefas\n"
    yield "============================\n\n"

    for task in tasks:
        status_text = "concluída" if task.completed else "pendente"
        yield f"Tarefa {task.id}: {task.title} - {status_text}\n"

        await asyncio.sleep(0.5)

    yield "\nFim do relatório.\n"
```

### Explicação

Essa função envia partes do relatório progressivamente.

* `yield` devolve uma parte da resposta.
* `await asyncio.sleep(0.5)` simula um pequeno atraso.
* O cliente começa a receber dados antes de toda a resposta estar pronta.



## 22. Criando o Endpoint de Streaming

Adicione:

```python
@app.get("/tasks-stream")
async def stream_tasks():
    with Session(engine) as session:
        statement = select(Task)
        tasks = list(session.exec(statement).all())

    return StreamingResponse(
        task_stream(tasks),
        media_type="text/plain",
    )
```

### Explicação

Esse endpoint retorna uma resposta textual em partes. Em vez de montar todo o relatório antes de responder, o servidor envia cada linha progressivamente.



## 23. Testando a Resposta Parcial

Crie algumas tarefas e execute:

```bash
curl -N http://127.0.0.1:8000/tasks-stream
```

### Resultado esperado

```text
Relatório parcial de tarefas
============================

Tarefa 1: Estudar REST - pendente
Tarefa 2: Fazer laboratório - concluída
Tarefa 3: Revisar FastAPI - pendente

Fim do relatório.
```

A opção `-N` do `curl` ajuda a visualizar a resposta sem buffering.



## 24. Código Final da Parte 2

A Parte 2 corresponde ao código da Parte 1 com as seguintes adições:

```python
import asyncio
from typing import Optional, AsyncGenerator

from fastapi import FastAPI, HTTPException, status
from fastapi.responses import StreamingResponse
from sqlmodel import Field, Session, SQLModel, create_engine, select
```

E o endpoint:

```python
async def task_stream(tasks: list[Task]) -> AsyncGenerator[str, None]:
    yield "Relatório parcial de tarefas\n"
    yield "============================\n\n"

    for task in tasks:
        status_text = "concluída" if task.completed else "pendente"
        yield f"Tarefa {task.id}: {task.title} - {status_text}\n"

        await asyncio.sleep(0.5)

    yield "\nFim do relatório.\n"


@app.get("/tasks-stream")
async def stream_tasks():
    with Session(engine) as session:
        statement = select(Task)
        tasks = list(session.exec(statement).all())

    return StreamingResponse(
        task_stream(tasks),
        media_type="text/plain",
    )
```



# Parte 3 — Autenticação com JWT

## 25. Objetivo da Parte 3

Nesta etapa, você irá adicionar autenticação à API.

Ao final, o sistema deverá permitir:

* criar usuários;
* fazer login;
* gerar token JWT;
* proteger endpoints;
* associar tarefas ao usuário autenticado.



## 26. Atualizando o `requirements.txt`

Substitua o conteúdo do arquivo por:

```txt
fastapi
uvicorn
sqlmodel
passlib[bcrypt]
python-jose[cryptography]
python-multipart
```

Instale novamente:

```bash
pip install -r requirements.txt
```

### Explicação

* `passlib[bcrypt]`: permite gerar hash seguro de senhas;
* `python-jose[cryptography]`: permite gerar e validar tokens JWT;
* `python-multipart`: necessário para processar dados do formulário de login OAuth2.



## 27. Atualizando os Imports

Atualize o início do arquivo:

```python
import asyncio
from datetime import datetime, timedelta
from typing import Optional, AsyncGenerator, Annotated

from fastapi import Depends, FastAPI, HTTPException, status
from fastapi.responses import StreamingResponse
from fastapi.security import OAuth2PasswordBearer, OAuth2PasswordRequestForm
from jose import JWTError, jwt
from passlib.context import CryptContext
from sqlmodel import Field, Session, SQLModel, create_engine, select
```



## 28. Configurando JWT e Hash de Senha

Abaixo da criação do `app`, adicione:

```python
SECRET_KEY = "troque-esta-chave-em-producao"
ALGORITHM = "HS256"
ACCESS_TOKEN_EXPIRE_MINUTES = 30

pwd_context = CryptContext(schemes=["bcrypt"], deprecated="auto")
oauth2_scheme = OAuth2PasswordBearer(tokenUrl="login")
```

### Explicação

* `SECRET_KEY` é usada para assinar o token.
* `ALGORITHM` define o algoritmo usado no JWT.
* `pwd_context` será usado para gerar e verificar hashes de senha.
* `oauth2_scheme` indica que a API espera um token Bearer.

Em uma aplicação real, a chave secreta não deve ficar escrita diretamente no código.



## 29. Criando o Modelo de Usuário

Adicione antes do modelo `Task`:

```python
class User(SQLModel, table=True):
    id: Optional[int] = Field(default=None, primary_key=True)
    username: str = Field(index=True, unique=True)
    hashed_password: str
```

### Explicação

Esse modelo representa os usuários no banco.

A senha não será salva em texto puro. Em vez disso, salvaremos apenas o hash da senha.



## 30. Atualizando o Modelo de Tarefa

Substitua o modelo `Task` por:

```python
class Task(SQLModel, table=True):
    id: Optional[int] = Field(default=None, primary_key=True)
    title: str
    description: str
    completed: bool = False
    owner_id: int = Field(foreign_key="user.id")
```

### Explicação

Agora cada tarefa pertence a um usuário. O campo `owner_id` guarda o ID do usuário dono da tarefa.



## 31. Criando Modelos de Usuário e Token

Adicione:

```python
class UserCreate(SQLModel):
    username: str
    password: str


class UserRead(SQLModel):
    id: int
    username: str


class Token(SQLModel):
    access_token: str
    token_type: str
```

### Explicação

* `UserCreate`: usado para cadastro;
* `UserRead`: usado na resposta, sem expor senha;
* `Token`: formato da resposta do login.



## 32. Atualizando `TaskRead`

Como a tarefa agora tem dono, atualize:

```python
class TaskRead(SQLModel):
    id: int
    title: str
    description: str
    completed: bool
    owner_id: int
```



## 33. Criando Dependência de Sessão

Substitua o acesso direto ao banco por uma dependência:

```python
def get_session():
    with Session(engine) as session:
        yield session


SessionDep = Annotated[Session, Depends(get_session)]
```

### Explicação

Isso evita repetir `with Session(engine)` em todos os endpoints.



## 34. Funções para Senha

Adicione:

```python
def verify_password(plain_password: str, hashed_password: str) -> bool:
    return pwd_context.verify(plain_password, hashed_password)


def hash_password(password: str) -> str:
    return pwd_context.hash(password)
```

### Explicação

Essas funções evitam armazenar senhas em texto puro.



## 35. Buscando Usuário no Banco

Adicione:

```python
def get_user_by_username(session: Session, username: str) -> Optional[User]:
    statement = select(User).where(User.username == username)
    return session.exec(statement).first()
```



## 36. Autenticando Usuário

Adicione:

```python
def authenticate_user(session: Session, username: str, password: str) -> Optional[User]:
    user = get_user_by_username(session, username)

    if not user:
        return None

    if not verify_password(password, user.hashed_password):
        return None

    return user
```

### Explicação

A autenticação verifica duas coisas:

1. se o usuário existe;
2. se a senha informada corresponde ao hash armazenado.



## 37. Criando Token JWT

Adicione:

```python
def create_access_token(data: dict, expires_delta: Optional[timedelta] = None) -> str:
    to_encode = data.copy()

    expire = datetime.utcnow() + (
        expires_delta if expires_delta else timedelta(minutes=ACCESS_TOKEN_EXPIRE_MINUTES)
    )

    to_encode.update({"exp": expire})
    encoded_jwt = jwt.encode(to_encode, SECRET_KEY, algorithm=ALGORITHM)

    return encoded_jwt
```

### Explicação

O token contém:

* o identificador do usuário no campo `sub`;
* a data de expiração no campo `exp`.



## 38. Obtendo o Usuário Atual

Adicione:

```python
async def get_current_user(
    token: Annotated[str, Depends(oauth2_scheme)],
    session: SessionDep,
) -> User:
    credentials_exception = HTTPException(
        status_code=status.HTTP_401_UNAUTHORIZED,
        detail="Não foi possível validar as credenciais.",
        headers={"WWW-Authenticate": "Bearer"},
    )

    try:
        payload = jwt.decode(token, SECRET_KEY, algorithms=[ALGORITHM])
        username = payload.get("sub")

        if username is None:
            raise credentials_exception

    except JWTError:
        raise credentials_exception

    user = get_user_by_username(session, username=username)

    if user is None:
        raise credentials_exception

    return user


CurrentUserDep = Annotated[User, Depends(get_current_user)]
```

### Explicação

Essa função:

1. recebe o token enviado pelo cliente;
2. decodifica o token;
3. busca o usuário no banco;
4. retorna o usuário autenticado.

Se algo falhar, retorna erro `401 Unauthorized`.



## 39. Endpoint para Criar Usuário

Adicione:

```python
@app.post("/users", response_model=UserRead, status_code=status.HTTP_201_CREATED)
async def create_user(user_create: UserCreate, session: SessionDep):
    existing_user = get_user_by_username(session, user_create.username)

    if existing_user:
        raise HTTPException(
            status_code=status.HTTP_400_BAD_REQUEST,
            detail="Nome de usuário já cadastrado.",
        )

    user = User(
        username=user_create.username,
        hashed_password=hash_password(user_create.password),
    )

    session.add(user)
    session.commit()
    session.refresh(user)

    return user
```



## 40. Endpoint de Login

Adicione:

```python
@app.post("/login", response_model=Token)
async def login(
    form_data: Annotated[OAuth2PasswordRequestForm, Depends()],
    session: SessionDep,
):
    user = authenticate_user(session, form_data.username, form_data.password)

    if not user:
        raise HTTPException(
            status_code=status.HTTP_401_UNAUTHORIZED,
            detail="Usuário ou senha inválidos.",
            headers={"WWW-Authenticate": "Bearer"},
        )

    access_token = create_access_token(data={"sub": user.username})

    return {
        "access_token": access_token,
        "token_type": "bearer",
    }
```

### Explicação

O endpoint `/login` recebe usuário e senha no formato de formulário. Se as credenciais estiverem corretas, ele devolve um token JWT.



## 41. Endpoint para Ver Usuário Atual

Adicione:

```python
@app.get("/me", response_model=UserRead)
async def read_me(current_user: CurrentUserDep):
    return current_user
```



## 42. Protegendo o CRUD de Tarefas

Agora atualize os endpoints de tarefas.

### Criar tarefa

```python
@app.post("/tasks", response_model=TaskRead, status_code=status.HTTP_201_CREATED)
async def create_task(
    task_create: TaskCreate,
    session: SessionDep,
    current_user: CurrentUserDep,
):
    task = Task(
        title=task_create.title,
        description=task_create.description,
        owner_id=current_user.id,
    )

    session.add(task)
    session.commit()
    session.refresh(task)

    return task
```

### Listar tarefas

```python
@app.get("/tasks", response_model=list[TaskRead])
async def list_tasks(
    session: SessionDep,
    current_user: CurrentUserDep,
):
    statement = select(Task).where(Task.owner_id == current_user.id)
    tasks = session.exec(statement).all()

    return tasks
```

### Buscar tarefa por ID

```python
@app.get("/tasks/{task_id}", response_model=TaskRead)
async def get_task(
    task_id: int,
    session: SessionDep,
    current_user: CurrentUserDep,
):
    task = session.get(Task, task_id)

    if not task or task.owner_id != current_user.id:
        raise HTTPException(
            status_code=status.HTTP_404_NOT_FOUND,
            detail="Tarefa não encontrada.",
        )

    return task
```

### Atualizar tarefa

```python
@app.put("/tasks/{task_id}", response_model=TaskRead)
async def update_task(
    task_id: int,
    task_update: TaskUpdate,
    session: SessionDep,
    current_user: CurrentUserDep,
):
    task = session.get(Task, task_id)

    if not task or task.owner_id != current_user.id:
        raise HTTPException(
            status_code=status.HTTP_404_NOT_FOUND,
            detail="Tarefa não encontrada.",
        )

    update_data = task_update.model_dump(exclude_unset=True)

    for key, value in update_data.items():
        setattr(task, key, value)

    session.add(task)
    session.commit()
    session.refresh(task)

    return task
```

### Remover tarefa

```python
@app.delete("/tasks/{task_id}", status_code=status.HTTP_204_NO_CONTENT)
async def delete_task(
    task_id: int,
    session: SessionDep,
    current_user: CurrentUserDep,
):
    task = session.get(Task, task_id)

    if not task or task.owner_id != current_user.id:
        raise HTTPException(
            status_code=status.HTTP_404_NOT_FOUND,
            detail="Tarefa não encontrada.",
        )

    session.delete(task)
    session.commit()

    return None
```

### Explicação

Agora, cada usuário só acessa suas próprias tarefas.

O endpoint verifica:

* se a tarefa existe;
* se a tarefa pertence ao usuário autenticado.



## 43. Protegendo o Streaming

Atualize o endpoint `/tasks-stream`:

```python
@app.get("/tasks-stream")
async def stream_tasks(
    session: SessionDep,
    current_user: CurrentUserDep,
):
    statement = select(Task).where(Task.owner_id == current_user.id)
    tasks = list(session.exec(statement).all())

    return StreamingResponse(
        task_stream(tasks),
        media_type="text/plain",
    )
```



## 44. Testando a Parte 3

Execute:

```bash
uvicorn main:app --reload
```

Acesse:

```text
http://127.0.0.1:8000/docs
```

### Passo 1 — Criar usuário

```json
{
  "username": "ana",
  "password": "123456"
}
```

### Passo 2 — Fazer login

Use o endpoint `/login`.

Campos:

```text
username: ana
password: 123456
```

### Passo 3 — Autorizar

Clique em **Authorize** no Swagger e informe:

```text
Bearer SEU_TOKEN
```

### Passo 4 — Testar endpoints protegidos

Agora teste:

* `POST /tasks`
* `GET /tasks`
* `GET /tasks/{task_id}`
* `PUT /tasks/{task_id}`
* `DELETE /tasks/{task_id}`
* `GET /tasks-stream`



## 45. Código Final Consolidado

```python
import asyncio
from datetime import datetime, timedelta
from typing import Optional, AsyncGenerator, Annotated

from fastapi import Depends, FastAPI, HTTPException, status
from fastapi.responses import StreamingResponse
from fastapi.security import OAuth2PasswordBearer, OAuth2PasswordRequestForm
from jose import JWTError, jwt
from passlib.context import CryptContext
from sqlmodel import Field, Session, SQLModel, create_engine, select


app = FastAPI(
    title="API de Tarefas Acadêmicas",
    description="REST API com FastAPI, SQLite, CRUD, assincronia, streaming e JWT.",
    version="1.0.0",
)

DATABASE_URL = "sqlite:///database.db"

engine = create_engine(
    DATABASE_URL,
    echo=True,
    connect_args={"check_same_thread": False},
)

SECRET_KEY = "troque-esta-chave-em-producao"
ALGORITHM = "HS256"
ACCESS_TOKEN_EXPIRE_MINUTES = 30

pwd_context = CryptContext(schemes=["bcrypt"], deprecated="auto")
oauth2_scheme = OAuth2PasswordBearer(tokenUrl="login")


class User(SQLModel, table=True):
    id: Optional[int] = Field(default=None, primary_key=True)
    username: str = Field(index=True, unique=True)
    hashed_password: str


class UserCreate(SQLModel):
    username: str
    password: str


class UserRead(SQLModel):
    id: int
    username: str


class Token(SQLModel):
    access_token: str
    token_type: str


class Task(SQLModel, table=True):
    id: Optional[int] = Field(default=None, primary_key=True)
    title: str
    description: str
    completed: bool = False
    owner_id: int = Field(foreign_key="user.id")


class TaskCreate(SQLModel):
    title: str
    description: str


class TaskUpdate(SQLModel):
    title: Optional[str] = None
    description: Optional[str] = None
    completed: Optional[bool] = None


class TaskRead(SQLModel):
    id: int
    title: str
    description: str
    completed: bool
    owner_id: int


def create_db_and_tables():
    SQLModel.metadata.create_all(engine)


@app.on_event("startup")
def on_startup():
    create_db_and_tables()


def get_session():
    with Session(engine) as session:
        yield session


SessionDep = Annotated[Session, Depends(get_session)]


def verify_password(plain_password: str, hashed_password: str) -> bool:
    return pwd_context.verify(plain_password, hashed_password)


def hash_password(password: str) -> str:
    return pwd_context.hash(password)


def get_user_by_username(session: Session, username: str) -> Optional[User]:
    statement = select(User).where(User.username == username)
    return session.exec(statement).first()


def authenticate_user(session: Session, username: str, password: str) -> Optional[User]:
    user = get_user_by_username(session, username)

    if not user:
        return None

    if not verify_password(password, user.hashed_password):
        return None

    return user


def create_access_token(data: dict, expires_delta: Optional[timedelta] = None) -> str:
    to_encode = data.copy()

    expire = datetime.utcnow() + (
        expires_delta if expires_delta else timedelta(minutes=ACCESS_TOKEN_EXPIRE_MINUTES)
    )

    to_encode.update({"exp": expire})
    encoded_jwt = jwt.encode(to_encode, SECRET_KEY, algorithm=ALGORITHM)

    return encoded_jwt


async def get_current_user(
    token: Annotated[str, Depends(oauth2_scheme)],
    session: SessionDep,
) -> User:
    credentials_exception = HTTPException(
        status_code=status.HTTP_401_UNAUTHORIZED,
        detail="Não foi possível validar as credenciais.",
        headers={"WWW-Authenticate": "Bearer"},
    )

    try:
        payload = jwt.decode(token, SECRET_KEY, algorithms=[ALGORITHM])
        username = payload.get("sub")

        if username is None:
            raise credentials_exception

    except JWTError:
        raise credentials_exception

    user = get_user_by_username(session, username=username)

    if user is None:
        raise credentials_exception

    return user


CurrentUserDep = Annotated[User, Depends(get_current_user)]


@app.get("/")
async def root():
    return {
        "message": "API de Tarefas Acadêmicas em execução.",
        "docs": "/docs",
    }


@app.post("/users", response_model=UserRead, status_code=status.HTTP_201_CREATED)
async def create_user(user_create: UserCreate, session: SessionDep):
    existing_user = get_user_by_username(session, user_create.username)

    if existing_user:
        raise HTTPException(
            status_code=status.HTTP_400_BAD_REQUEST,
            detail="Nome de usuário já cadastrado.",
        )

    user = User(
        username=user_create.username,
        hashed_password=hash_password(user_create.password),
    )

    session.add(user)
    session.commit()
    session.refresh(user)

    return user


@app.post("/login", response_model=Token)
async def login(
    form_data: Annotated[OAuth2PasswordRequestForm, Depends()],
    session: SessionDep,
):
    user = authenticate_user(session, form_data.username, form_data.password)

    if not user:
        raise HTTPException(
            status_code=status.HTTP_401_UNAUTHORIZED,
            detail="Usuário ou senha inválidos.",
            headers={"WWW-Authenticate": "Bearer"},
        )

    access_token = create_access_token(data={"sub": user.username})

    return {
        "access_token": access_token,
        "token_type": "bearer",
    }


@app.get("/me", response_model=UserRead)
async def read_me(current_user: CurrentUserDep):
    return current_user


@app.post("/tasks", response_model=TaskRead, status_code=status.HTTP_201_CREATED)
async def create_task(
    task_create: TaskCreate,
    session: SessionDep,
    current_user: CurrentUserDep,
):
    task = Task(
        title=task_create.title,
        description=task_create.description,
        owner_id=current_user.id,
    )

    session.add(task)
    session.commit()
    session.refresh(task)

    return task


@app.get("/tasks", response_model=list[TaskRead])
async def list_tasks(
    session: SessionDep,
    current_user: CurrentUserDep,
):
    statement = select(Task).where(Task.owner_id == current_user.id)
    tasks = session.exec(statement).all()

    return tasks


@app.get("/tasks/{task_id}", response_model=TaskRead)
async def get_task(
    task_id: int,
    session: SessionDep,
    current_user: CurrentUserDep,
):
    task = session.get(Task, task_id)

    if not task or task.owner_id != current_user.id:
        raise HTTPException(
            status_code=status.HTTP_404_NOT_FOUND,
            detail="Tarefa não encontrada.",
        )

    return task


@app.put("/tasks/{task_id}", response_model=TaskRead)
async def update_task(
    task_id: int,
    task_update: TaskUpdate,
    session: SessionDep,
    current_user: CurrentUserDep,
):
    task = session.get(Task, task_id)

    if not task or task.owner_id != current_user.id:
        raise HTTPException(
            status_code=status.HTTP_404_NOT_FOUND,
            detail="Tarefa não encontrada.",
        )

    update_data = task_update.model_dump(exclude_unset=True)

    for key, value in update_data.items():
        setattr(task, key, value)

    session.add(task)
    session.commit()
    session.refresh(task)

    return task


@app.delete("/tasks/{task_id}", status_code=status.HTTP_204_NO_CONTENT)
async def delete_task(
    task_id: int,
    session: SessionDep,
    current_user: CurrentUserDep,
):
    task = session.get(Task, task_id)

    if not task or task.owner_id != current_user.id:
        raise HTTPException(
            status_code=status.HTTP_404_NOT_FOUND,
            detail="Tarefa não encontrada.",
        )

    session.delete(task)
    session.commit()

    return None


async def task_stream(tasks: list[Task]) -> AsyncGenerator[str, None]:
    yield "Relatório parcial de tarefas\n"
    yield "============================\n\n"

    for task in tasks:
        status_text = "concluída" if task.completed else "pendente"
        yield f"Tarefa {task.id}: {task.title} - {status_text}\n"

        await asyncio.sleep(0.5)

    yield "\nFim do relatório.\n"


@app.get("/tasks-stream")
async def stream_tasks(
    session: SessionDep,
    current_user: CurrentUserDep,
):
    statement = select(Task).where(Task.owner_id == current_user.id)
    tasks = list(session.exec(statement).all())

    return StreamingResponse(
        task_stream(tasks),
        media_type="text/plain",
    )
```


## 46. Desafio Extra

Implemente pelo as melhorias:

* filtro por tarefas concluídas e pendentes;
* campo de prazo da tarefa;
* paginação em `GET /tasks`;
* endpoint `PATCH /tasks/{task_id}/complete`;
* validação para impedir título vazio;
* alteração de senha;
* endpoint para listar estatísticas do usuário.


> Considere também consumir a API em uma interface HTML + Javascript. Note que este exercício pode auxiliar no desenvolvimento do projeto da disciplina.  


## 47. Resultado Esperado

Ao final do laboratório, a API deverá permitir:

* criar usuários;
* autenticar usuários;
* gerar token JWT;
* criar, listar, buscar, atualizar e remover tarefas;
* impedir que um usuário acesse tarefas de outro;
* gerar um relatório parcial de tarefas via streaming.

