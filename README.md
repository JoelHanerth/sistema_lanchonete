

# 🍔 Sistema de Lanchonete — C

Este programa gerencia **lanches** e **pedidos** utilizando vetores de structs e arquivos binários para salvar e carregar os dados automaticamente.

---

## 📌 Funcionalidades

### ✔️ **1. Cadastro de Lanches**

Cada lanche possui:

* `id`
* `nome`
* `ingredientes`
* `preço`

Os lanches são armazenados em `Lanches.vetorLanches`.

---

### ✔️ **2. Cadastro de Pedidos**

Cada pedido possui:

* número do pedido (`id`)
* quantidade
* tipo do lanche (id do lanche)
* nome do cliente
* valor total calculado

Os pedidos ficam em `Pedidos.vetorPedidos`.

---

### ✔️ **3. Ações disponíveis no menu**

1. Inserir lanche
2. Inserir pedido
3. Pesquisar pedido por número
4. Pesquisar pedido por nome do cliente
5. Atualizar quantidade
6. Mostrar maior pedido
7. Excluir pedido
8. Listar todos os pedidos

---

## 💾 Salvamento Automático

Ao iniciar o programa:

* Carrega dados de `lanches.bin` e `pedidos.bin`.

Ao sair:

* Salva tudo novamente nesses arquivos.

Assim, nada é perdido entre execuções.

---

## ▶️ Como compilar

Windows (MinGW):

```bash
gcc main.c -o lanchonete
```

Executar:

```bash
./lanchonete
```

---

## 🧱 Organização do Código

* **Structs principais:**

  * `Lanche` / `Lanches`
  * `Pedido` / `Pedidos`

* **Funções importantes:**

  * Inserção (`inserirLanche`, `inserirPedido`)
  * Pesquisa (`pesquisarPedidosID`, `pesquisarLancheID`, `pesquisarPedidosNome`)
  * Atualização (`atualizarQuantidade`)
  * Exclusão (`excluir`)
  * Impressão (`imprimirPedido`, `listar`)
  * Arquivos (`carregarArquivos...`, `salvarArquivos`)

---

## 📁 Arquivos gerados

* `lanches.bin`
* `pedidos.bin`

Usados para guardar todos os dados.
