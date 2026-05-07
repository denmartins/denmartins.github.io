---
title: "Landing page Bootstrap em Django"
collection: labs
type: "Lab"
permalink: /labs/django-bootstrap
date: 2026-05-06
location: "Ribeirão Preto, Brazil"
---

## Objetivo

Criar uma página inicial simples em Django utilizando **Bootstrap 5.3**, com:

* Navbar
* Seção principal
* Botão de chamada para ação
* Cards informativos
* Rodapé

## Estrutura esperada

```text
meuprojeto/
│
├── manage.py
├── meuprojeto/
│   ├── settings.py
│   └── urls.py
│
└── siteapp/
    ├── views.py
    ├── urls.py
    └── templates/
        └── index.html
```

## Criar o projeto Django

```bash
django-admin startproject meuprojeto
cd meuprojeto
python manage.py startapp siteapp
```

## Registrar a aplicação

No arquivo `meuprojeto/settings.py`, adicione a app:

```python
INSTALLED_APPS = [
    'django.contrib.admin',
    'django.contrib.auth',
    'django.contrib.contenttypes',
    'django.contrib.sessions',
    'django.contrib.messages',
    'django.contrib.staticfiles',
    'siteapp',
]
```

## Criar a view da landing page

Arquivo `siteapp/views.py`:

```python
from django.shortcuts import render

def index(request):
    return render(request, 'index.html')
```

## Criar as rotas da aplicação

Crie o arquivo `siteapp/urls.py`:

```python
from django.urls import path
from . import views

urlpatterns = [
    path('', views.index, name='index'),
]
```

Agora, no arquivo `meuprojeto/urls.py`, conecte as URLs da app:

```python
from django.contrib import admin
from django.urls import path, include

urlpatterns = [
    path('admin/', admin.site.urls),
    path('', include('siteapp.urls')),
]
```

## Criar o template com Bootstrap 5.3

Crie a pasta:

```text
siteapp/templates/
```

Dentro dela, crie o arquivo `index.html`:

```html
<!DOCTYPE html>
<html lang="pt-br">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Minha Landing Page</title>

    <!-- Bootstrap 5.3 via CDN -->
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/css/bootstrap.min.css" rel="stylesheet">
</head>

<body>

    <!-- Navbar -->
    <nav class="navbar navbar-expand-lg bg-dark navbar-dark">
        <div class="container">
            <a class="navbar-brand" href="#">Minha Empresa</a>
        </div>
    </nav>

    <!-- Seção principal -->
    <section class="bg-light text-center py-5">
        <div class="container">
            <h1 class="display-4 fw-bold">Bem-vindo à nossa aplicação</h1>
            <p class="lead mt-3">
                Esta é uma landing page simples criada com Django e Bootstrap 5.3.
            </p>
            <a href="#" class="btn btn-primary btn-lg mt-3">Começar agora</a>
        </div>
    </section>

    <!-- Cards -->
    <section class="py-5">
        <div class="container">
            <div class="row g-4">

                <div class="col-md-4">
                    <div class="card h-100">
                        <div class="card-body">
                            <h5 class="card-title">Rápido</h5>
                            <p class="card-text">
                                Django permite desenvolver aplicações web de forma ágil e organizada.
                            </p>
                        </div>
                    </div>
                </div>

                <div class="col-md-4">
                    <div class="card h-100">
                        <div class="card-body">
                            <h5 class="card-title">Responsivo</h5>
                            <p class="card-text">
                                Bootstrap facilita a criação de páginas adaptadas a diferentes telas.
                            </p>
                        </div>
                    </div>
                </div>

                <div class="col-md-4">
                    <div class="card h-100">
                        <div class="card-body">
                            <h5 class="card-title">Organizado</h5>
                            <p class="card-text">
                                A separação entre views, templates e rotas melhora a manutenção do sistema.
                            </p>
                        </div>
                    </div>
                </div>

            </div>
        </div>
    </section>

    <!-- Rodapé -->
    <footer class="bg-dark text-white text-center py-3">
        <p class="mb-0">© 2026 Minha Empresa. Todos os direitos reservados.</p>
    </footer>

    <!-- Bootstrap JS -->
    <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/js/bootstrap.bundle.min.js"></script>

</body>
</html>
```

## Executar o servidor

```bash
python manage.py runserver
```

Acesse no navegador:

```text
http://127.0.0.1:8000/
```

## Resultado esperado

A aplicação deve exibir uma landing page com:

* Barra de navegação escura
* Título principal centralizado
* Botão azul
* Três cards informativos
* Rodapé escuro
