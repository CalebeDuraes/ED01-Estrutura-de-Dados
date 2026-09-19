#include <stdio.h>
#define MAX_SIZE 100

typedef struct {
    int itens[MAX_SIZE];
    int topo;
} Pilha;

void InicializaPilha(Pilha *pilha){
    pilha->topo = -1;
};


int VazioPilha(Pilha *pilha){
    return(pilha->topo == -1);
}

int CheioPilha(Pilha *pilha){
    return(pilha->topo == MAX_SIZE -1);
}

int PilhaTopo(Pilha *pilha){
    if(VazioPilha(pilha)){
        printf("Erro: A pilha está vazia.");
        return -10;
    }
    return pilha->itens[pilha->topo];
}

void Push(Pilha *pilha, int item){
    if(CheioPilha(pilha)){
        printf("Erro: Pilha está cheia.\n");
        return;
    }
    pilha->topo++;
    pilha->itens[pilha->topo] = item;
}

int Pop(Pilha *pilha){
    if(VazioPilha(pilha)){
        printf("Erro: Pilha está vazia");
        return -10;
    }
    int item = pilha->itens[pilha->topo];
    pilha->topo--;
    return item;
}

void LerPilha(Pilha *pilha){
    for(int i = 0; i <= pilha->topo; i++){
        printf("\n");
        printf("Piha[%d]: %d", i, pilha->itens[i]);
    }
    printf("\n");
}

int main(){
    printf("teste");

    int numero = 0;

    Pilha pilha;
    Pilha pilha_aux;
    InicializaPilha(&pilha);


    /*ADICIONAR NA PILHA - EX1*/
    for(int i = 0; i < 5; i++){
        printf("Digite o %d° número: ", i + 1);
        scanf("%d", &numero);
        getchar();

        Push(&pilha, numero);
    }

    LerPilha(&pilha); //EX3

    //EXERCÍCIO 4
    InicializaPilha(&pilha_aux);

    LerPilha(&pilha_aux);//EX2

    return 0;
}