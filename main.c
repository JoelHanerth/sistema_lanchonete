#include <stdio.h>
#include <string.h>
#include <windows.h>

// STRUCTS
struct Lanche {
    char nome[50];
    char ingredientes[300];
    double preco;
    int id;
};
typedef struct Lanche Lanche;

struct Lanches {
    Lanche lanche;
    int quant;
};
typedef struct Lanches Lanches;

struct Pedido {
    int id;
    int quant;
    int tipoLanche;
    char nomeCliente[100];
    float valorPedido;
};
typedef struct Pedido Pedido;

struct Pedidos {
    Pedido pedido;
    int quant;
};
typedef struct Pedidos Pedidos;

// PESQUISAR
int pesquisarLancheID(Lanches vetorLanches[], int pesq) {
    for (int i = 0; i < vetorLanches->quant; i++) {
        if (vetorLanches[i].lanche.id == pesq) {
            return i;
        }
    }
    return -1;
}

int pesquisarPedidosID(Pedidos vetorPedidos[], int pesq) {
    for (int i = 0; i < vetorPedidos->quant; i++) {
        if (vetorPedidos[i].pedido.id == pesq) {
            return i;
        }
    }
    return -1;
}

int pesquisarPedidosNome(Pedidos vetorPedidos[], char *nome) {
    for (int i = 0; i < vetorPedidos->quant; i++) {
        if (strcmp(vetorPedidos[i].pedido.nomeCliente, nome) == 0) {
            return i;
        }
    }
    return -1;
}

// IMPRIMIR
void imprimirPedido(Pedidos vetorPedidos[], Lanches vetorLanches[], int id) {
    int pesq1, pesq2;
    printf("\n");

    pesq1 = pesquisarPedidosID(vetorPedidos, id);
    if (pesq1 != -1) {
        // pra achar o endereço do lanche correspondente ao pedido
        pesq2 = pesquisarLancheID(vetorLanches, (vetorPedidos[pesq1].pedido.tipoLanche));

        printf("Número do pedido: %d\n", vetorPedidos[pesq1].pedido.id);
        printf("ID %d: %s\n", vetorLanches[pesq2].lanche.id, vetorLanches[pesq2].lanche.nome);
        printf("Ingredientes: %s\n", vetorLanches[pesq2].lanche.ingredientes);
        printf("Preço unitário: R$%lf\n", vetorLanches[pesq2].lanche.preco);
        printf("Quantidade: %d\n", vetorPedidos[pesq1].pedido.quant);
        printf("Preço final do pedido: R$%lf\n", vetorPedidos[pesq1].pedido.valorPedido);
        printf("Nome do Cliente: %s\n\n", vetorPedidos[pesq1].pedido.nomeCliente);
    } else {
        printf("PEDIDO NÃO ENCONTRADO\n\n");
    }
}

void imprimirLanches(Lanches vetorLanches[]) {
    printf("\nLANCHES DISPONÍVEIS:\n");
    for (int i = 0; i < vetorLanches->quant; i++) {
        printf("ID %d - %s ---- R$%lf\n", vetorLanches[i].lanche.id, vetorLanches[i].lanche.nome, vetorLanches[i].lanche.preco);
    }
    printf("\n");
}

void listar(Pedidos vetorPedidos[], Lanches vetorLanches[]) {
    for (int i = 0; i < vetorPedidos->quant; i++) {
        imprimirPedido(vetorPedidos, vetorLanches, vetorPedidos[i].pedido.id);
    }
}

// VERIFICAO DE VALORES
double verificarPreco() {
    double aux;
    do {
        printf("Informe o preço: ");
        scanf("%lf", &aux);
        if (aux <= 0) {
            printf("\nValor inválido\n");
        }
    } while (aux <= 0);
    return aux;
}

int obterNumIntPositivo(char *mensagem) {
    int num;
    do {
        printf("%s", mensagem);
        scanf("%d", &num);
        if (num <= 0) {
            printf("\nNúmero Inválido\n");
        }
    } while (num <= 0);
    return num;
}

// INSERIR DADOS
void inserirLanche(Lanches lista_lanches[]) {
    int aux, pesq;

    // numero do pedido
    do {
        aux = obterNumIntPositivo("\nInforme o id do lanche: ");
        pesq = pesquisarLancheID(lista_lanches, aux);
        if (pesq != -1) {
            printf("ID JÁ CADASTRADO\n");
        }
    } while (pesq != -1);

    // adiciona o id no vetor
    lista_lanches[lista_lanches->quant].lanche.id = aux;

    // nome do lanche
    printf("Informe o nome do lanche: ");
    scanf(" %49[^\n]s", lista_lanches[lista_lanches->quant].lanche.nome);

    // ingredientes do lanche
    printf("Informe os ingredientes do lanche: ");
    scanf(" %299[^\n]s", lista_lanches[lista_lanches->quant].lanche.ingredientes);

    // preco do lanche
    lista_lanches[lista_lanches->quant].lanche.preco = verificarPreco();

    lista_lanches->quant += 1;
}

void inserirPedido(Pedidos vetorPedidos[], Lanches vetorLanches[]) {
    int aux, pesq;
    double preco;

    if (vetorLanches->quant > 0) {
        // numero do pedido
        do {
            printf("Informe o número do pedido: ");
            scanf("%d", &aux);
            pesq = pesquisarPedidosID(vetorPedidos, aux);
            if (pesq != -1) {
                printf("\nPEDIDO JÁ EXISTENTE\n");
            }
        } while (pesq != -1);

        // salva o numero do pedido
        vetorPedidos[vetorPedidos->quant].pedido.id = aux;

        // pega id de lanche
        do {
            imprimirLanches(vetorLanches);

            printf("Informe o id do lanche: ");
            scanf("%d", &aux);
            pesq = pesquisarLancheID(vetorLanches, aux);
            if (pesq == -1) {
                printf("\nID inexistente\n");
            }
        } while (pesq == -1);

        // salva o id
        vetorPedidos[vetorPedidos->quant].pedido.tipoLanche = aux;

        // obtem o preco do lanche
        preco = vetorLanches[pesq].lanche.preco;

        // quantidade de lanche
        aux = obterNumIntPositivo("Informe a quantidade de lanche: ");
        // salva a quantidade do pedido
        vetorPedidos[vetorPedidos->quant].pedido.quant = aux;

        // calcula o valor TOTAL do pedido
        vetorPedidos[vetorPedidos->quant].pedido.valorPedido = aux * preco;

        // nome do cliente
        printf("Informe o nome do cliente: ");
        scanf(" %49[^\n]s", vetorPedidos[vetorPedidos->quant].pedido.nomeCliente);

        vetorPedidos->quant += 1;
    } else {
        printf("\nVocê precisa cadastrar ao menos 1 lanche\n");
    }
}

int maiorPedido(Pedidos vetorPedidos[]) {
    int maior = -1;
    int id = -1;
    for (int i = 0; i < vetorPedidos->quant; i++) {
        if (vetorPedidos[i].pedido.valorPedido > maior) {
            maior = vetorPedidos[i].pedido.valorPedido;
            id = vetorPedidos[i].pedido.id;
        }
    }
    return id;
}

void atualizarQuantidade(Pedidos vetorPedidos[], Lanches vetorLanches[]) {
    int id = obterNumIntPositivo("\nInforme o número do pedido: ");
    int pesq1 = pesquisarPedidosID(vetorPedidos, id);
    
    if (pesq1 != -1) {
        int quant = obterNumIntPositivo("\n\nInforme a nova quantidade do pedido: ");
        // atualiza a quantidade
        vetorPedidos[pesq1].pedido.quant = quant;

        // procura o endereço do vetor onde o ID do lanche do pedido está armazenado
        int pesq2 = pesquisarLancheID(vetorLanches, vetorPedidos[pesq1].pedido.tipoLanche);

        // atualiza o valor TOTAL do pedido
        vetorPedidos[pesq1].pedido.valorPedido = quant * (vetorLanches[pesq2].lanche.preco);

        printf("\nQuantidade Atualizada\n");
    } else {
        printf("\nPedido inválido\n");
    }
}

// EXCLUIR
void excluir(Pedidos vetorPedido[], int pos) {
    if ((pos >= 0) && (pos < vetorPedido->quant)) {
        for (int i = pos + 1; i < vetorPedido->quant; i++) {
            // DESLOCAR
            vetorPedido[i - 1] = vetorPedido[i];
        }
        (vetorPedido->quant)--;
        printf("\nDado Excluído\n\n");
    } else {
        printf("\nPosição inválida!\n\n");
    }
}

// MENU
int menu() {
    int op;
    // system("@cls||clear");  // LIMPA A TELA
    printf("\n\nSISTEMA XXYYZZ\n\n");
    printf("1 - Inserir Lanche\n");
    printf("2 - Inserir Pedido\n");
    printf("3 - Pesquisar por número\n");
    printf("4 - Pesquisar por nome\n");
    printf("5 - Atualizar\n");
    printf("6 - Maior\n");
    printf("7 - Excluir\n");
    printf("8 - Listar\n");
    printf("0 - Sair\n");
    do {
        printf("Escolha sua opção: ");
        scanf(" %d", &op);
    } while (op < 0 || op > 8);
    return op;
}

// MAIN
int main() {
    SetConsoleOutputCP(65001);
    Pedidos vetorPedidos[100];
    Lanches vetorLanches[100];
    vetorLanches->quant = 0;
    vetorPedidos->quant = 0;

    int op, num;
    char nome[50];

    do {
        op = menu();
        switch (op) {
            case 0:
                break;
            case 1:
                inserirLanche(vetorLanches);
                break;
            case 2:
                inserirPedido(vetorPedidos, vetorLanches);
                break;
            case 3:
                num = obterNumIntPositivo("\n\nInforme o número do pedido: ");
                imprimirPedido(vetorPedidos, vetorLanches, num);
                break;
            case 4:
                // PESQUISAR POR NOME
                printf("Informe o nome do cliente: ");
                scanf(" %49[^\n]s", nome);
                // retorna a posição do vetor em que está o nome
                num = pesquisarPedidosNome(vetorPedidos, nome);
                imprimirPedido(vetorPedidos, vetorLanches, vetorPedidos[num].pedido.id);
                break;
            case 5:
                atualizarQuantidade(vetorPedidos, vetorLanches);
                break;
            case 6:
                // MAIOR
                if (vetorPedidos->quant > 0) {
                    imprimirPedido(vetorPedidos, vetorLanches, maiorPedido(vetorPedidos));
                } else {
                    printf("\nNenhum pedido encontrado\n");
                }
                break;
            case 7:
                num = obterNumIntPositivo("\nInforme o ID do pedido a ser excluído: ");
                num = pesquisarPedidosID(vetorPedidos, num);
                excluir(vetorPedidos, num);
                break;
            case 8:
                listar(vetorPedidos, vetorLanches);
                break;
            default:
                printf("\n\nOpção inválida!\n\n");
        }
        system("PAUSE");  // Windows
    } while (op != 0);

    return 0;
}
