---
title: "Transações em Bancos de Dados"
collection: labs
type: "Lab"
permalink: /labs/bd-transactions
date: 2026-06-02
location: "Ribeirão Preto, Brazil"
---

Transações são um dos mecanismos mais importantes dos bancos de dados relacionais: elas garantem que um conjunto de operações seja executado de forma segura, consistente e recuperável mesmo diante de falhas ou erros inesperados. Os exercícios a seguir foram elaborados para que você coloque esse conceito em prática em situações próximas do mundo real. Ambos podem ser realizados em qualquer um dos três bancos de dados relacionais mais utilizados (SQLite, PostgreSQL ou MySQL), e os scripts de preparação já incluem as adaptações necessárias para cada um deles. Escolha o ambiente com o qual você tem mais familiaridade, ou aproveite a oportunidade para experimentar um novo.

## Exercício 1

Um banco digital mantém o saldo de seus clientes na tabela `contas`. Toda transferência entre contas deve ser **atômica**: ou o débito e o crédito acontecem juntos, ou nenhuma das duas operações é efetivada. Neste exercício você vai simular uma transferência e entender como o `ROLLBACK` protege a integridade dos dados.



### Preparação do ambiente

Execute o script abaixo para criar e popular as tabelas antes de iniciar o exercício.

```sql
-- Criação da tabela
CREATE TABLE contas (
    id          INTEGER PRIMARY KEY,
    titular     TEXT    NOT NULL,
    saldo       NUMERIC(12, 2) NOT NULL CHECK (saldo >= 0)
);

-- Dados iniciais
INSERT INTO contas (id, titular, saldo) VALUES
    (1, 'Alice', 1500.00),
    (2, 'Bob',    300.00);
```

> **Nota (SQLite):** O SQLite não executa a constraint `CHECK` em versões anteriores à 3.25. Nesses casos, a validação deverá ser feita manualmente na aplicação ou via trigger.



### Tarefas

**Parte A — Transferência bem-sucedida**

1. Abra uma transação explícita.
2. Debite **R$ 200,00** da conta de Alice (id = 1).
3. Credite **R$ 200,00** na conta de Bob (id = 2).
4. Confirme a transação.
5. Consulte as duas contas e verifique que os saldos foram atualizados corretamente.


**Parte B — Transferência que deve ser cancelada**

1. Abra uma nova transação.
2. Tente debitar **R$ 5.000,00** da conta de Alice.
3. Antes de confirmar, consulte o saldo de Alice **dentro da transação** e verifique que ele ficou negativo (ou que a constraint foi violada).
4. Cancele a transação com `ROLLBACK`.
5. Consulte novamente as contas **fora da transação** e confirme que nenhum dado foi alterado.



### Perguntas para reflexão

1. O que teria acontecido se o banco sofresse uma queda elétrica após o débito de Alice, mas antes do crédito de Bob, **sem** o uso de transação?
2. Qual propriedade ACID garante que os dois `UPDATE`s são tratados como uma única unidade de trabalho?
3. Por que consultar os dados *dentro* de uma transação não confirmada pode retornar valores diferentes do que outros usuários enxergam?



## Exercício 2

Uma loja online registra seus produtos e movimentações de estoque em duas tabelas. Ao processar um pedido com múltiplos itens, cada baixa no estoque deve ser registrada individualmente. Se **um item específico** estiver indisponível, apenas a baixa daquele item deve ser desfeita — os demais itens já processados com sucesso devem ser mantidos. Para isso, usaremos `SAVEPOINT`.



### Preparação do ambiente

```sql
-- Tabela de produtos
CREATE TABLE produtos (
    id          INTEGER PRIMARY KEY,
    nome        TEXT    NOT NULL,
    estoque     INTEGER NOT NULL CHECK (estoque >= 0)
);

-- Tabela de movimentações
CREATE TABLE movimentacoes (
    id          INTEGER PRIMARY KEY AUTOINCREMENT,  -- use SERIAL no PostgreSQL
    produto_id  INTEGER NOT NULL REFERENCES produtos(id),
    quantidade  INTEGER NOT NULL,
    tipo        TEXT    NOT NULL,  -- 'entrada' ou 'saida'
    registrado_em TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- Dados iniciais
INSERT INTO produtos (id, nome, estoque) VALUES
    (1, 'Notebook',   5),
    (2, 'Mouse',     12),
    (3, 'Teclado',    0);   -- produto sem estoque!
```

> **Nota (PostgreSQL):** Substitua `INTEGER PRIMARY KEY AUTOINCREMENT` por `SERIAL PRIMARY KEY` na tabela `movimentacoes`.



### Tarefas

Um pedido solicita a retirada de: **2 Notebooks**, **3 Mouses** e **1 Teclado**.

**Parte A — Processamento item a item com SAVEPOINT**

Para cada item do pedido, siga o roteiro abaixo dentro de **uma única transação**:

1. Crie um `SAVEPOINT` antes de tentar processar o item.
2. Atualize o estoque do produto (diminua a quantidade solicitada).
3. Insira um registro na tabela `movimentacoes` com `tipo = 'saida'`.
4. Verifique se o estoque resultante ficou negativo.
   - Se ficou negativo: execute `ROLLBACK TO SAVEPOINT` para desfazer apenas aquele item e registre (em comentário ou em uma variável de controle) que o item falhou.
   - Se ficou válido: execute `RELEASE SAVEPOINT` para confirmar aquele ponto.
5. Ao final, confirme a transação com `COMMIT`.


**Parte B — Verificação dos resultados**

Após o `COMMIT`, execute as consultas abaixo e registre os resultados obtidos:

```sql
-- Estoque atualizado
SELECT id, nome, estoque FROM produtos ORDER BY id;

-- Movimentações registradas
SELECT m.id, p.nome, m.quantidade, m.tipo, m.registrado_em
FROM movimentacoes m
JOIN produtos p ON p.id = m.produto_id
ORDER BY m.id;
```

Responda: quantas linhas aparecem em `movimentacoes`? Por quê?



### Perguntas para reflexão

1. Qual a diferença entre `ROLLBACK TO SAVEPOINT` e `ROLLBACK` completo? Em que cenários cada um é mais adequado?
2. Se você removesse os `SAVEPOINT`s e mantivesse apenas um `ROLLBACK` ao detectar qualquer erro, qual seria o impacto para o pedido?
3. A propriedade ACID de **isolamento** garante que outros usuários não vejam as alterações parciais desta transação antes do `COMMIT`. Como isso impacta a experiência de um usuário que consulta o estoque ao mesmo tempo que o pedido está sendo processado?


## Referência rápida: comandos de transação

| Comando | Descrição |
|||
| `BEGIN` | Inicia uma transação explícita |
| `COMMIT` | Confirma todas as alterações da transação |
| `ROLLBACK` | Cancela todas as alterações desde o `BEGIN` |
| `SAVEPOINT <nome>` | Cria um ponto de restauração dentro da transação |
| `ROLLBACK TO SAVEPOINT <nome>` | Desfaz alterações até o savepoint, mantendo a transação aberta |
| `RELEASE SAVEPOINT <nome>` | Remove o savepoint (sem desfazer nada) |

> **Dica:** No PostgreSQL, qualquer erro dentro de uma transação coloca-a em estado de **abortada**. É necessário executar `ROLLBACK` (ou `ROLLBACK TO SAVEPOINT`) antes de continuar. No MySQL (com InnoDB) e no SQLite, o comportamento pode variar. Verifique a documentação da versão utilizada.