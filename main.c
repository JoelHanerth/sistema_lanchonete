#include <stdio.h>
#include <string.h>
#include <windows.h>


struct Lanche{
    char nome[50], ingredientes [300];
    double preco;
	int id;

};
typedef struct Lanche Lanche;

struct Lanches{
    Lanche lanche;
	int quant;
};
typedef struct Lanches Lanches;


struct Pedido{
    int id, quant,tipoLanche;
    char nomeCliente[100];
	float valorPedido;

};
typedef struct Pedido Pedido;

struct Pedidos{
    Pedido pedido;
    int quantPedidos;

};
typedef struct Pedidos Pedidos;



// PESQUISAR

int pesquisarLanche (Lanches *vetorLanches, int pesq) {
    int i;
    for (i = 0; i < vetorLanches->quant; i++) {
		// printf("endereco lanche %d",vetorLanches[i].lanche.id);
		
        if (vetorLanches[i].lanche.id == pesq){
            return i;
		}
    }
    return -1;
}

int pesquisarPedidos (Pedidos *vetorPedidos, int pesq) {
    int i;
    for (i = 0; i < vetorPedidos->quantPedidos; i++) {
		
        if (vetorPedidos[i].pedido.id == pesq){
            return i;
		}
    }
    return -1;
}



double verificarPreco(){
	double aux;
	do
	{
		printf("Informe o preço: ");
    	scanf("%lf",&aux);
		if (aux<=0){
			printf("\nValor inválido\n");
		}
	} while (aux<=0);

	return aux;
}



// INSERIR DADOS
void inserirLanche(Lanches *lista_lanches){
	int aux, pesq;

	// numero do pedido
	do
	{
		printf("Informe o id do lanche: ");
    	scanf("%d",&aux);
		pesq = pesquisarLanche(lista_lanches,aux);
		if (pesq!=-1){
			printf("\nID JÁ CADASTRADO\n");
		}
	} while (pesq!=-1);

	// adiciona o id no vetor
	lista_lanches[lista_lanches->quant].lanche.id = aux;
	
	// nome do lanche
	printf("\nInforme o nome do lanche: ");
    scanf(" %49[^\n]s", lista_lanches[lista_lanches->quant].lanche.nome);

	// ingredientes do lanche
	printf("\nInforme os ingredientes do lanche: ");
    scanf(" %299[^\n]s", lista_lanches[lista_lanches->quant].lanche.ingredientes);

	// preco do lanche
	lista_lanches[lista_lanches->quant].lanche.preco = verificarPreco();

	lista_lanches->quant+=1;

}





void inserirPedido(Pedidos *vetorPedidos, Lanches *vetorLanches){
	int aux, pesq;
	double preco;

	// numero do pedido
	do
	{
		printf("Informe o número do pedido: ");
    	scanf("%d",&aux);
		pesq = pesquisarPedidos(vetorPedidos,aux);
		if (pesq!=-1){
			printf("\nPEDIDO JÁ EXISTENTE\n");
		}
	} while (pesq!=-1);

	// salva o numero do pedido
	vetorPedidos[vetorPedidos->quantPedidos].pedido.id=aux;




	// imprimir menu de lanches disponíveis

	// pega id de lanche
	do
	{
		printf("Informe o id do lanche: ");
    	scanf("%d",&aux);
		pesq = pesquisarLanche(vetorLanches,aux);
		if (pesq==-1){
			printf("\nID inexistente\n");
		}
	} while (pesq==-1);

	// salva o id
	vetorPedidos[vetorPedidos->quantPedidos].pedido.tipoLanche=aux;

	// salva o preco do lanche
	preco = vetorLanches[pesq].lanche.preco;


	// quantidade de lanche
	do{
		printf("Informe a quantidade de lanche: ");
    	scanf("%d",&aux);
		if (aux<=0){
			printf("\nValor inválido\n");
		}
	} while (aux<=0);

	// salva a quantidade do pedido
	vetorPedidos[vetorPedidos->quantPedidos].pedido.quant=aux;

	// calcula o valor TOTAL do pedido
	vetorPedidos[vetorPedidos->quantPedidos].pedido.valorPedido = aux* preco;

	// nome do cliente
	printf("\nInforme o nome do cliente: ");
    scanf(" %49[^\n]s", vetorPedidos[vetorPedidos->quantPedidos].pedido.nomeCliente);


	vetorPedidos->quantPedidos+=1;



}

 void imprimirPedido(Pedidos *vetorPedidos, Lanches *vetorLanches){
	int i, pesq;
    printf("\n\n");
    for (i = 0; i < vetorPedidos->quantPedidos; i++) {
		
		printf("Número do pedido: %d\n", vetorPedidos[i].pedido.id);

		pesq = pesquisarLanche(vetorLanches, (vetorPedidos[i].pedido.tipoLanche));
		printf("Produto: %s\n", vetorLanches[pesq].lanche.nome);
		printf("Ingredientes: %s\n", vetorLanches[pesq].lanche.ingredientes);
		printf("Quantidade: %d\n", vetorPedidos[i].pedido.quant);
		printf("Preço final do pedido: %lf\n", vetorPedidos[i].pedido.valorPedido);
		printf("Nome do Cliente: %s\n\n\n", vetorPedidos[i].pedido.nomeCliente);
        
    }
    printf("\n\n");
 }








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
	} while(op < 0 || op > 8);
	return op;
}


int main() {
    SetConsoleOutputCP(65001);
    Pedidos vetorPedidos[100];
	Lanches vetorLanches[100];
    int op;



	do {
		op = menu();
		switch ( op ) {
			case 0:

				// SAIR. NÃO PRECISA FAZER NADA
				break;
			case 1:
				inserirLanche(&vetorLanches);
				printf("\n retorno: %d\n",(vetorLanches[0].lanche.id));
				break;
			case 2:
				inserirPedido(&vetorPedidos, &vetorLanches);
                printf("\n retorno: %d\n",(vetorPedidos[0].pedido.id));
				// PESQUISAR POR CODIGO/MATRICULA
				break;
			case 3:
				imprimirPedido(vetorPedidos, &vetorLanches);
				// PESQUISAR POR CODIGO/MATRICULA
				break;
			case 4:
				// PESQUISAR POR NOME
				break;
			case 5:
				// ATUALIZAR
				break;
			case 6:
				// MAIOR
				break;
			case 7:
				// EXCLUIR
				break;
			case 8:
				// LISTAR
				break;
			default:
				printf ("\n\nOpçãoo inválida!\n\n");
		}

		system("PAUSE");  // Windows
	} while (op != 0);
	
	return 0;
}