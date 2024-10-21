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
    int quant;

};
typedef struct Pedidos Pedidos;



// PESQUISAR

int pesquisarLancheID (Lanches vetorLanches[], int pesq) {
    int i;
    for (i = 0; i < vetorLanches->quant; i++) {
		
        if (vetorLanches[i].lanche.id == pesq){
            return i;
		}
    }
    return -1;
}


int pesquisarPedidosID (Pedidos vetorPedidos[], int pesq) {
    int i;
    for (i = 0; i < vetorPedidos->quant; i++) {
		
        if (vetorPedidos[i].pedido.id == pesq){
            return i;
		}
    }
    return -1;
}

int pesquisarPedidosNome (Pedidos vetorPedidos[], char *nome) {
    int i;
    for (i = 0; i < vetorPedidos->quant; i++) {

		// Debug: Mostrar o nome que está sendo comparado
        printf("Comparando: %s com %s\n", vetorPedidos[i].pedido.nomeCliente, nome);
		// Usa strcmp para comparar o conteúdo das strings
        if (strcmp(vetorPedidos[i].pedido.nomeCliente, nome) == 0) {
			printf("aqui");
            return i;
        }
    }
    return -1;
}


 void imprimirPedido(Pedidos vetorPedidos[], Lanches vetorLanches[], int id){
	int pesq1, pesq2;
	printf("\n\n");

	pesq1 = pesquisarPedidosID(vetorPedidos, id);
	if (pesq1 != -1){

		// pra achar o endereço do lanche correspondente ao pedido
		pesq2 = pesquisarLancheID(vetorLanches, (vetorPedidos[pesq1].pedido.tipoLanche));

		printf("Número do pedido: %d\n", vetorPedidos[pesq1].pedido.id);
		printf("ID %d: %s\n", vetorLanches[pesq2].lanche.id ,vetorLanches[pesq2].lanche.nome);
		printf("Ingredientes: %s\n", vetorLanches[pesq2].lanche.ingredientes);
		printf("Preço unitário: R$%lf\n", vetorLanches[pesq2].lanche.preco);
		printf("Quantidade: %d\n", vetorPedidos[pesq1].pedido.quant);
		printf("Preço final do pedido: R$%lf\n", vetorPedidos[pesq1].pedido.valorPedido);
		printf("Nome do Cliente: %s\n\n", vetorPedidos[pesq1].pedido.nomeCliente);
	}

	else{ printf("PEDIDO NÃO ENCOTRADO\n\n"); }
 }



void imprimirLanches(Lanches vetorLanches[]){
	int i;
    printf("\nLANCHES DISPONÍVEIS:\n");
    for (i = 0; i < vetorLanches->quant; i++) {
		printf("ID %d - %s ---- R$%lf\n", vetorLanches[i].lanche.id, vetorLanches[i].lanche.nome, vetorLanches[i].lanche.preco);
    }
    printf("\n");
 }



 void listar(Pedidos vetorPedidos[], Lanches vetorLanches[]){
	int i;

    for (i = 0; i < vetorPedidos->quant; i++) {
		imprimirPedido(vetorPedidos, vetorLanches, vetorPedidos[i].pedido.id);
    }
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


int obterNumIntPositivo( char *mensagem){
	int num;
	do{
		printf("%s", mensagem);
    	scanf("%d",&num);
		if (num<=0){
			printf("\nNúmero Inválido\n");
		}
	} while (num<=0);
	return num;
}

// INSERIR DADOS
void inserirLanche(Lanches lista_lanches[]){
	int aux, pesq;

	// numero do pedido
	do
	{
		printf("\nInforme o id do lanche: ");
    	scanf("%d",&aux);
		pesq = pesquisarLancheID(lista_lanches,aux);
		if (pesq!=-1){
			printf("ID JÁ CADASTRADO\n");
		}
	} while (pesq!=-1);

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



void inserirPedido(Pedidos vetorPedidos[], Lanches vetorLanches[]){
	int aux, pesq;
	double preco;

	// numero do pedido
	do
	{
		printf("Informe o número do pedido: ");
    	scanf("%d",&aux);
		pesq = pesquisarPedidosID(vetorPedidos,aux);
		if (pesq!=-1){
			printf("\nPEDIDO JÁ EXISTENTE\n");
		}
	} while (pesq!=-1);

	// salva o numero do pedido
	vetorPedidos[vetorPedidos->quant].pedido.id=aux;



	// pega id de lanche
	do
	{
		imprimirLanches(vetorLanches);

		printf("Informe o id do lanche: ");
    	scanf("%d",&aux);
		pesq = pesquisarLancheID(vetorLanches,aux);
		if (pesq==-1){
			printf("\nID inexistente\n");
		}
	} while (pesq==-1);

	// salva o id
	vetorPedidos[vetorPedidos->quant].pedido.tipoLanche=aux;

	// salva o preco do lanche
	preco = vetorLanches[pesq].lanche.preco;


	// quantidade de lanche
	aux = obterNumIntPositivo("Informe a quantidade de lanche: ");

	// salva a quantidade do pedido
	vetorPedidos[vetorPedidos->quant].pedido.quant=aux;

	// calcula o valor TOTAL do pedido
	vetorPedidos[vetorPedidos->quant].pedido.valorPedido = aux* preco;

	// nome do cliente
	printf("Informe o nome do cliente: ");
    scanf(" %49[^\n]s", vetorPedidos[vetorPedidos->quant].pedido.nomeCliente);


	vetorPedidos->quant+=1;



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
	vetorLanches->quant = 0;
	vetorPedidos->quant = 0;
    int op, num;
	char nome[50];



	do {
		op = menu();
		switch ( op ) {
			case 0:

				// SAIR. NÃO PRECISA FAZER NADA
				break;
			case 1:
				inserirLanche(vetorLanches);
				printf("\n retorno: %d\n",(vetorLanches[0].lanche.id));
				break;
			case 2:
				inserirPedido(vetorPedidos, vetorLanches);
                printf("\n retorno: %d\n",(vetorPedidos[0].pedido.id));
				// PESQUISAR POR CODIGO/MATRICULA
				break;
			case 3:
				num = obterNumIntPositivo("\n\nInforme o número do pedido: ");
				imprimirPedido(vetorPedidos,vetorLanches,num);
				break;
			case 4:
				// PESQUISAR POR NOME
				printf("Informe o nome do cliente: ");
    			scanf(" %49[^\n]s", nome);
				num = pesquisarPedidosNome(vetorPedidos,nome);
				num = vetorPedidos[num].pedido.id;
				imprimirPedido(vetorPedidos,vetorLanches,num);
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
				listar(vetorPedidos,vetorLanches);
				break;
			default:
				printf ("\n\nOpçãoo inválida!\n\n");
		}

		system("PAUSE");  // Windows
	} while (op != 0);
	
	return 0;
}