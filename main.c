#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_SIZE 10

typedef struct {
    char nome_filme[50];
    int sala;
    int horario;
    float valor;
} Ingresso;

typedef struct {
    char nome[50];
    int idade;
    Ingresso ingresso;
} Cliente;

typedef struct {
    Ingresso* ingressos[MAX_SIZE];
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

Ingresso* PilhaTopo(Pilha *pilha){
    if(VazioPilha(pilha)){
        printf("Erro: A pilha está vazia.");
    }else {
        return pilha->ingressos[pilha->topo];
    }
}

void Push(Pilha *pilha, Ingresso* item){
    if(CheioPilha(pilha)){
        printf("Erro: Pilha está cheia.\n");
        return;
    }
    pilha->topo++;
    pilha->ingressos[pilha->topo] = item;
}

Ingresso* Pop(Pilha *pilha) {
    if(VazioPilha(pilha)){
        printf("Erro: Pilha está vazia");
    } else {
        Ingresso* item = pilha->ingressos[pilha->topo];
        pilha->topo--;
        return item;
    }
}

void LerPilha(Pilha *pilha){
    for(int i = 0; i <= pilha->topo; i++){
        printf("\n");
        printf("---------------\n");
        printf("Piha[%d]: \n", i);
        printf("Nome: %s\n", pilha->ingressos[i]->nome_filme);
        printf("Sala: %d\n", pilha->ingressos[i]->sala);
        printf("Horario: %dH\n", pilha->ingressos[i]->horario);
        printf("Valor: R$%.2f", pilha->ingressos[i]->valor);
    }
    printf("\n");
}

int* buscaPorHorario(Pilha *pilha, int horario, int *qtd) {
    int *indices = malloc(MAX_SIZE * sizeof(int));
    *qtd = 0;

    for (int i = 0; i < MAX_SIZE; i++) {
        if (pilha->ingressos[i]->horario == horario) {
            indices[*qtd] = i;
            (*qtd)++;
        }
    }

    if (*qtd == 0) {
        printf("Não há sessões do filme %s no horario das %dH. \n", pilha->ingressos[0]->nome_filme, horario);
    } else {
        printf("Foram encontrados %d ingressos do filme %s no horario das %dH! \n", *qtd, pilha->ingressos[0]->nome_filme, horario);
    }

    return indices;
}

Pilha* cadastrarFilmes(Pilha* pilha, Pilha* pilha2, Pilha* pilha3) {
    InicializaPilha(pilha);
    InicializaPilha(pilha2);
    InicializaPilha(pilha3);

    //Define o nome do filme
    const char *listaFilmes[10] = {
        "O Poderoso Chefão",
        "Jurassic Park",
        "O Senhor dos Anéis: A Sociedade do Anel",
        "La La Land",
        "Os Vingadores",
        "E.T. – O Extraterrestre",
        "Clube da Luta",
        "Titanic",
        "O Exorcista",
        "Parasita"
    };

    for (int j = 0; j < 3; j++) {
        int intFilme = rand() % 10;
        char nomeFilme[50];
        strcpy(nomeFilme, listaFilmes[intFilme]);

        //Define o valor do ingresso
        float aleatorio = (float)rand() / RAND_MAX;
        float valor = 50 + aleatorio * (70 - 50);
        for (int i = 0; i < MAX_SIZE; i++) {
            Ingresso* ingresso = malloc(sizeof(Ingresso));

            //Define o nome
            strcpy(ingresso->nome_filme, nomeFilme);

            //define valor
            ingresso->valor = valor;

            //Define a sala do ingresso
            ingresso->sala = rand() % 10 + 1;
            //Define horário do ingresso
            ingresso->horario = rand() % (24 - 7 + 1) + 7;

            if (j == 0) {
                Push(pilha, ingresso);
            } else if (j == 1) {
                Push(pilha2, ingresso);
            } else {
                Push(pilha3, ingresso);
            }

        }
    }

    return pilha, pilha2, pilha3;
}

int main(){
    Pilha pilha, pilha2, pilha3;
    srand(time(NULL));

    cadastrarFilmes(&pilha, &pilha2, &pilha3);

    printf("\nPILHA 1\n");
    printf("==============");
    LerPilha(&pilha);

    printf("\nPILHA 2\n");
    printf("==============");
    LerPilha(&pilha2);

    printf("\nPILHA 3\n");
    printf("==============");
    LerPilha(&pilha3);

    int horario;
    int escolha;
    int qtd;
    int *indices = malloc(MAX_SIZE * sizeof(int));

    printf("\n Digite o horario que gostaria de buscar: ");
    scanf("%d", &horario);
    getchar();

    printf("\n Agora digite qual filme gostaria de buscar: ");
    scanf("%d", &escolha);
    getchar();
    if (escolha == 1) {
        indices = buscaPorHorario(&pilha, horario, &qtd);
    } else if (escolha == 2) {
        indices = buscaPorHorario(&pilha2, horario, &qtd);
    } else if (escolha == 3) {
        indices = buscaPorHorario(&pilha3, horario, &qtd);
    }
    for (int i = 0; i < qtd; i++) {
        printf("Ingresso encontrado no incide: %d \n", indices[i]);
    }

    printf("Pressione ENTER para continuar...\n");
    getchar();
    free(indices);

    return 0;
}