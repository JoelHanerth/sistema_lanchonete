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




int main(){

    return 0;
}