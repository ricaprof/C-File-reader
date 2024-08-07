#ifndef PROJETO_C2_EDITOR_H
#define PROJETO_C2_EDITOR_H

#endif //PROJETO_C2_EDITOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LINHA 100

// Estrutura para representar um elemento da sequência

void leitura(struct Element *head) {
    struct Element *current = head;
    while (current != NULL) {
        wprintf(L"Ordem: %d, Descrição: %s, Quantidade vendida: %s\n", current->ordem, current->descricao, current->quant_vendido);
        current = current->next;
    }
    printf("mkpfasf");
}



int Editor() {
    int num_elementos = 0;
    char linha[MAX_LINHA];


    //Abre o arquivo binário
    FILE *arquivo = fopen("arquivo-bin.bin", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo de texto\n");
        exit(1);
    }


    // Cria a cabeça da lista encadeada
    struct Element* head = NULL;
    struct Element* tail = NULL;


    //Pega os dados do arquivo binário
    while (fgets(linha, sizeof(linha), arquivo)) {
        int ordem;
        char descricao[MAX_LINHA];
        char quant_vendido[MAX_LINHA];

        // Lê os campos da linha
        if (sscanf(linha, "%d %s %s", &ordem, descricao, quant_vendido) == 3) {
            num_elementos++;

            // Cria um novo elemento para a lista
            struct Element* newElement = (struct Element*)malloc(sizeof(struct Element));
            if (newElement == NULL) {
                printf("Erro de alocação de memória.\n");
                exit(1);
            }

            newElement->ordem = ordem;
            strcpy(newElement->descricao, descricao);
            strcpy(newElement->quant_vendido, quant_vendido);
            newElement->next = NULL;

            if (head == NULL) {
                head = newElement;
                tail = newElement;
            } else {
                tail->next = newElement;
                tail = newElement;
            }
        }
    }

    //Fecha o arquivo binário criado
    fclose(arquivo);
    struct Element *current = head;
    current = head;
    while (current != NULL) {
        wprintf("Ordem: %d, Descrição: %s, Quantidade vendida: %s\n", current->ordem, current->descricao, current->quant_vendido);
        current = current->next;
    }



    //Modifica os itens
    bool boolean = 1;
    if(boolean == 1){
        printf("Digite 0 para alterar algum produto e 1 para não alterar nenhum\n");
        scanf("%d", &boolean);
    }
    while(boolean == 0){
        int ORDEM;
        bool verificarID = 1;
        int addOrRemove = 0;

        //Verifica se deseja adicionar ou remover um nó da lista
        if(addOrRemove == 0){
            puts("Digite 1 para adicionar um elemento, 2 para remover um elemento e 3 para alterar um elemento");
            scanf("%d", &addOrRemove);
            //Adiciona um nó na lista
            if(addOrRemove == 1){
                puts("Adicionar elemento");

                struct Element* newElement = (struct Element*)malloc(sizeof(struct Element));
                if (newElement == NULL) {
                    printf("Erro de alocação de memória.\n");
                    exit(1);
                }
                //Irá pegar o maior id da lista, adicionar um e fazer deste o id do próximo elemento
                int elementoChave = 0;
                while (current != NULL) {
                    if(current->ordem > elementoChave) elementoChave = current->ordem + 1;
                    current = current->next;
                }
                char novaDesc[MAX_LINHA], novaQuant[MAX_LINHA];
                puts("Digite o nome (sem espaço) do novo produto\n");
                scanf("%c", &novaDesc);
                puts("Digite a quantidade de produtos vendidos\n");
                scanf("%c", &novaQuant);
                newElement->ordem = elementoChave;
                strcpy(newElement->descricao, novaDesc);
                strcpy(newElement->quant_vendido, novaQuant);
                newElement->next = NULL;

                if (head == NULL) {
                    head = newElement;
                    tail = newElement;
                } else {
                    tail->next = newElement;
                    tail = newElement;
                }
            }
                //Remove um nó na lista
            else if (addOrRemove == 2) {
                puts("Digite o id do produto que deseja remover:\n");
                int produto = 0;
                scanf("%d", &produto);

                struct Element* temp = head;

                struct Element* current = head;
                struct Element* previous = NULL;

                while (current != NULL) {
                    if (produto == current->ordem) {
                        if (previous == NULL) {
                            head = current->next;
                            free(current);

                        } else {
                            previous->next = current->next;
                            free(current);

                        }
                    }
                    previous = current;
                    current = current->next;
                }
                addOrRemove = 0;
            }



                //Altera um elemento da lista
            else{
                puts("Digite o id do item que você deseja alterar\n");
                scanf("%d", &ORDEM);
                printf("%d\n", ORDEM);
                struct Element* current = head;
                while (current != NULL) {
                    if(current->ordem == ORDEM) {
                        printf("Digite o novo nome do produto:(Produto antigo '%s')\n", current->descricao);
                        scanf("%s", &current->descricao);
                        printf("Digite a nova quantidade de produto vendido:(Quantidade anterior '%s')\n", current->quant_vendido);
                        scanf("%s", &current->quant_vendido);
                        verificarID = 0;
                    }
                    current = current->next;
                }
                if(verificarID == 1){
                    puts("Digite um Id válido");
                    verificarID == 0;
                }
            }
        }

        puts("Digite 0 para continuar editando e 1 para salvar");
        scanf("%d", &boolean);
    }

    FILE* arquivoTeste = fopen("dados_atualizados.bin", "w");

    if (arquivoTeste == NULL) {
        printf("Erro ao abrir o arquivo de texto.\n");
        exit(1);
    }
    current = head;
    while (current != NULL) {
        fprintf(arquivoTeste, "%d %s %s\n", current->ordem, current->descricao, current->quant_vendido);
        current = current->next;
    }

    fclose(arquivoTeste);


    // Imprime os elementos no terminal
    current = head;
    while (current != NULL) {
        wprintf(L"Ordem: %d, Descrição: %s, Quantidade vendida: %s\n", current->ordem, current->descricao, current->quant_vendido);
        current = current->next;
    }
    // Libera a memória alocada para a lista encadeada
    current = head;
    while (current != NULL) {
        struct Element* temp = current;
        current = current->next;
        free(temp);
    }



    return 0;
}
