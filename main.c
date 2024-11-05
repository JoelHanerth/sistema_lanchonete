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
    Lanche vetorLanches[100];
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
    // Pedido pedido;
	Pedido vetorPedidos[100];
    int quant;
};
typedef struct Pedidos Pedidos;

// PESQUISAR
int pesquisarLancheID(Lanches lanches, int pesq) {
	int i;
    for (i = 0; i < lanches.quant; i++) {
        if (lanches.vetorLanches[i].id == pesq) {
            return i;
        }
    }
    return -1;
}

int pesquisarPedidosID(Pedidos pedidos, int pesq) {
	int i;
	// printf("TAMANHO %d",pedidos.quant);
    for (i = 0; i < pedidos.quant; i++) {
        if (pedidos.vetorPedidos[i].id == pesq) {
            return i;
        }
    }
    return -1;
}

int pesquisarPedidosNome(Pedidos pedidos, char *nome) {
	int i;
    for (i = 0; i < pedidos.quant; i++) {
        if (strcmp(pedidos.vetorPedidos[i].nomeCliente, nome) == 0) {
            return i;
        }
    }
    return -1;
}

// IMPRIMIR
void imprimirPedido(Pedidos pedidos, Lanches lanches, int id) {
    int pesq1, pesq2;
    printf("\n");

    pesq1 = pesquisarPedidosID(pedidos, id);
    if (pesq1 != -1) {
        // pra achar o endereço do lanche correspondente ao pedido
        pesq2 = pesquisarLancheID(lanches, (pedidos.vetorPedidos[pesq1].tipoLanche));

        printf("Número do pedido: %d\n", pedidos.vetorPedidos[pesq1].id);
        printf("ID %d: %s\n", lanches.vetorLanches[pesq2].id, lanches.vetorLanches[pesq2].nome);
        printf("Ingredientes: %s\n", lanches.vetorLanches[pesq2].ingredientes);
        printf("Preço unitário: R$%.2lf\n", lanches.vetorLanches[pesq2].preco);
        printf("Quantidade: %d\n", pedidos.vetorPedidos[pesq1].quant);
        printf("Preço final do pedido: R$%.2lf\n", pedidos.vetorPedidos[pesq1].valorPedido);
        printf("Nome do Cliente: %s\n\n", pedidos.vetorPedidos[pesq1].nomeCliente);
    } else {
        printf("PEDIDO NÃO ENCONTRADO\n\n");
    }
}

void imprimirLanches(Lanches lanches) {
	int i;
    printf("\nLANCHES DISPONÍVEIS:\n");
    for (i = 0; i < lanches.quant; i++) {
        printf("ID %d - %s ---- R$%.2lf\n", lanches.vetorLanches[i].id, lanches.vetorLanches[i].nome, lanches.vetorLanches[i].preco);
    }
    printf("\n");
}

void listar(Pedidos pedidos, Lanches lanches) {
	int i;
    for (i = 0; i < pedidos.quant; i++) {
        imprimirPedido(pedidos, lanches, pedidos.vetorPedidos[i].id);
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
void inserirLanche(Lanches *lanches) {
    int aux, pesq;

    // numero do pedido
    do {
        aux = obterNumIntPositivo("\nInforme o id do lanche: ");
        pesq = pesquisarLancheID(*lanches, aux);
        if (pesq != -1) {
            printf("ID JÁ CADASTRADO\n");
        }
    } while (pesq != -1);

    // adiciona o id no vetor
    lanches->vetorLanches[lanches->quant].id = aux;

    // nome do lanche
    printf("Informe o nome do lanche: ");
    scanf(" %49[^\n]s", lanches->vetorLanches[lanches->quant].nome);

    // ingredientes do lanche
    printf("Informe os ingredientes do lanche: ");
    scanf(" %299[^\n]s", lanches->vetorLanches[lanches->quant].ingredientes);

    // preco do lanche
    lanches->vetorLanches[lanches->quant].preco = verificarPreco();

    lanches->quant += 1;
}

void inserirPedido(Pedidos *pedidos, Lanches *lanches) {
    int aux, pesq;
    double preco;

    if (lanches->quant > 0) {
        // numero do pedido
        do {
            printf("Informe o número do pedido: ");
            scanf("%d", &aux);
            pesq = pesquisarPedidosID(*pedidos, aux);
            if (pesq != -1) {
    			printf("\nPEDIDO JÁ EXISTENTE. Informe um número diferente.\n");
            }
        } while (pesq != -1);

        // salva o numero do pedido
		pedidos->vetorPedidos[pedidos->quant].id = (aux);

        // pega id de lanche
        do {
            imprimirLanches(*lanches);

            printf("Informe o id do lanche: ");
            scanf("%d", &aux);
            pesq = pesquisarLancheID(*lanches, aux);
            if (pesq == -1) {
                printf("\nID inexistente\n");
            }
        } while (pesq == -1);

        // salva o id
		pedidos->vetorPedidos[pedidos->quant].tipoLanche = aux;

        // obtem o preco do lanche
        preco = lanches->vetorLanches[pesq].preco;

        // quantidade de lanche
        aux = obterNumIntPositivo("Informe a quantidade de lanche: ");
        // salva a quantidade do pedido
		pedidos->vetorPedidos[pedidos->quant].quant = aux;

        // calcula o valor TOTAL do pedido
		pedidos->vetorPedidos[pedidos->quant].valorPedido = aux * preco;

        // nome do cliente
        printf("Informe o nome do cliente: ");
        scanf(" %49[^\n]s", pedidos->vetorPedidos[pedidos->quant].nomeCliente);

		pedidos->quant +=1;
    } else {
        printf("\nVocê precisa cadastrar ao menos 1 lanche\n");
    }
}

int maiorPedido(Pedidos pedidos) {
    int maior = -1;
    int id = -1;
	int i;
    for (i = 0; i < pedidos.quant; i++) {
        if (pedidos.vetorPedidos[i].valorPedido > maior) {
            maior = pedidos.vetorPedidos[i].valorPedido;
            id = pedidos.vetorPedidos[i].id;
        }
    }
    return id;
}

void atualizarQuantidade(Pedidos *pedidos, Lanches *lanches) {
    int id = obterNumIntPositivo("\nInforme o número do pedido: ");
    int pesq1 = pesquisarPedidosID(*pedidos, id);
    
    if (pesq1 != -1) {
        int quant = obterNumIntPositivo("\n\nInforme a nova quantidade do pedido: ");
        // atualiza a quantidade
		pedidos->vetorPedidos[pesq1].quant = quant;

        // procura o endereço do vetor onde o ID do lanche do pedido está armazenado
        int pesq2 = pesquisarLancheID(*lanches, pedidos->vetorPedidos[pesq1].tipoLanche);

        // atualiza o valor TOTAL do pedido
		pedidos->vetorPedidos[pesq1].valorPedido = quant * (lanches->vetorLanches[pesq2].preco);

        printf("\nQuantidade Atualizada\n");
    } else {
        printf("\nPedido inválido\n");
    }
}

// EXCLUIR
void excluir(Pedidos *pedidos, int pos) {
    int tamanho = pedidos->quant;
    int i;

    if (pos != -1 && pos < tamanho) {
        // Excluir o pedido deslocando os itens subsequentes para a esquerda
        for (i = pos + 1; i < tamanho; i++) {
            pedidos->vetorPedidos[i - 1] = pedidos->vetorPedidos[i];
        }
        // Atualizar a quantidade
        pedidos->quant -= 1;
        printf("\nDado Excluído.\n\n");
    } else {
        printf("\nPosição inválida ou pedido não encontrado!\n\n");
    }
}

FILE *abrirArquivo(char *endereco, char *modo) {
    FILE *arq = fopen(endereco, modo);
    if (arq == NULL) {
        printf("Aviso: Não foi possível abrir o arquivo %s. Continuando com lista vazia.\n", endereco);
    }
    return arq;
}

void salvarArquivos(Pedidos pedidos, Lanches lanches) {
    FILE *arq;
    
    arq = abrirArquivo("../pedidos.bin","wb");
    // Escreve a struct no arquivo binário
    fwrite(&pedidos, sizeof(Pedidos), 1, arq);
    fclose(arq);

     arq = abrirArquivo("../lanches.bin","wb");
    // Escreve a struct no arquivo binário
    fwrite(&lanches, sizeof(Lanches), 1, arq);
    fclose(arq);
}


Pedidos carregarArquivosPedidos() {
    FILE *arq;
    Pedidos pedidos;
    pedidos.quant = 0; // Inicializa a quantidade com 0, para o caso de o arquivo não existir.

    arq = abrirArquivo("../pedidos.bin", "rb");
    if (arq != NULL) {
        fread(&pedidos, sizeof(Pedidos), 1, arq);
        fclose(arq);
    } else {
        printf("Arquivo de pedidos não encontrado. Continuando com lista vazia.\n");
    }
    
    return pedidos;
}

Lanches carregarArquivosLanches() {
    FILE *arq;
    Lanches lanches;
    lanches.quant = 0; // Inicializa a quantidade com 0, para o caso de o arquivo não existir.

    arq = abrirArquivo("../lanches.bin", "rb");
    if (arq != NULL) {
        fread(&lanches, sizeof(Lanches), 1, arq);
        fclose(arq);
    } else {
        printf("Arquivo de lanches não encontrado. Continuando com lista vazia.\n");
    }
    
    return lanches;
}


// MENU
int menu() {
    int op;
    // system("@cls||clear");  // LIMPA A TELA
    printf("\n\nSISTEMA LANCHONETE\n\n");
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

    Pedidos pedidos = carregarArquivosPedidos();
	Lanches lanches = carregarArquivosLanches();

    int op, num;
    char nome[50];

    do {
        op = menu();
        switch (op) {
            case 0:
                break;
            case 1:
                inserirLanche(&lanches);
                break;
            case 2:
                inserirPedido(&pedidos, &lanches);
                break;
            case 3:
                num = obterNumIntPositivo("\n\nInforme o número do pedido: ");
                imprimirPedido(pedidos, lanches, num);
                break;
            case 4:
                printf("Informe o nome do cliente: ");
                scanf(" %49[^\n]s", nome);
                // retorna a posição do vetor em que está o nome
                num = pesquisarPedidosNome(pedidos, nome);
                if (num != -1){ imprimirPedido(pedidos, lanches, pedidos.vetorPedidos[num].id); }
                break;
            case 5:
                atualizarQuantidade(&pedidos, &lanches);
                break;
            case 6:
                // MAIOR
                if (pedidos.quant > 0) {
                    imprimirPedido(pedidos, lanches, maiorPedido(pedidos));
                } else {
                    printf("\nNenhum pedido encontrado\n");
                }
                break;
            case 7:
				num = obterNumIntPositivo("\nInforme o ID do pedido a ser excluído: ");
				num = pesquisarPedidosID(pedidos, num);
				excluir(&pedidos, num); // Passando como ponteiro
				break;

            case 8:
                listar(pedidos, lanches);
                break;
            default:
                printf("\n\nOpção inválida!\n\n");
        }
        system("PAUSE");  // Windows
    } while (op != 0);

    salvarArquivos(pedidos,lanches);
    return 0;
}
