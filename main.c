#include <stdio.h>
#include <string.h>

struct Lanche{
    char nome[50], ingredientes [300];
    double preco;

};
typedef struct Lanche Lanche;

struct Pedido{
    Lanche tipoLanche;
    int nPedido, quant;
    char nomeCliente[100];

};
typedef struct Pedido Pedido;

struct Pedidos{
    Pedido pedido;
    int quantPedidos;

};
typedef struct Pedidos Pedidos;




void Inserir(Pedidos *vetorPedidos){
    printf("Informe o número do pedido: ");
    scanf("%d",&(vetorPedidos[0].pedido.nPedido));

    
}


int menu() {
	int op;
	system("@cls||clear");  // LIMPA A TELA
	printf("\n\nSISTEMA XXYYZZ\n\n");
	printf("1 - Inserir\n");
	printf("2 - Pesquisar por número\n");
	printf("3 - Pesquisar por nome\n");
	printf("4 - Atualizar\n");
	printf("5 - Maior\n");
	printf("6 - Excluir\n");
	printf("7 - Listar\n");
	printf("0 - Sair\n");
	do {
		printf("Escolha sua opção: ");
		scanf(" %d", &op);
	} while(op < 0 || op > 7);
	return op;
}


int main() {
    SetConsoleOutputCP(65001);
    Pedidos vetorPedidos[100];
    int op;



	do {
		op = menu();
		switch ( op ) {
			case 0:
				// SAIR. NÃO PRECISA FAZER NADA
				break;
			case 1:
				Inserir(&vetorPedidos);
                printf("%d",(vetorPedidos[0].pedido.nPedido));
				break;
			case 2:
				// PESQUISAR POR CODIGO/MATRICULA
				break;
			case 3:
				// PESQUISAR POR NOME
				break;
			case 4:
				// ATUALIZAR
				break;
			case 5:
				// MAIOR
				break;
			case 6:
				// EXCLUIR
				break;
			case 7:
				// LISTAR
				break;
			default:
				printf ("\n\nOpçãoo inválida!\n\n");
		}

		system("PAUSE");  // Windows
	} while (op != 0);
	
	return 0;
}