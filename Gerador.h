#ifndef PROJETO_C2_GERADOR_H
#define PROJETO_C2_GERADOR_H

#endif //PROJETO_C2_GERADOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Função para ordenar os elementos pela ordem usando Bubble Sort
void bubbleSort(struct Element* head) {
    int trocado;
    struct Element *atual;
    struct Element *ultimo = NULL;

    // Lista vazia
    if (head == NULL)
        return;

    do {
        trocado = 0;
        atual = head;

        while (atual->next != ultimo) {
            if (atual->ordem > atual->next->ordem) {
                // Troca dos valores
                int temp = atual->ordem;
                atual->ordem = atual->next->ordem;
                atual->next->ordem = temp;

                char temp_desc[MAX_LINHA];
                strcpy(temp_desc, atual->descricao);
                strcpy(atual->descricao, atual->next->descricao);
                strcpy(atual->next->descricao, temp_desc);

                char temp_quant[MAX_LINHA];
                strcpy(temp_quant, atual->quant_vendido);
                strcpy(atual->quant_vendido, atual->next->quant_vendido);
                strcpy(atual->next->quant_vendido, temp_quant);

                trocado = 1;
            }
            atual = atual->next;
        }
        ultimo = atual;
    } while (trocado);
}

int Gerador(const char *test) {
    int num_elementos = 0;
    char linha[MAX_LINHA];


    //Abre o arquivo de texto
    FILE *arquivo = fopen(test, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo de texto\n");
        exit(1);
    }

    // Cria a cabeça da lista encadeada
    struct Element* head = NULL;
    struct Element* tail = NULL;


    //Roda o programa toda vez que há uma linha nova
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

    //Fecha o arquivo
    fclose(arquivo);

    //Organiza
    bubbleSort(head);

    // Abre o arquivo binário para escrita

    struct Element* current = head;
    FILE* arquivoTeste = fopen("arquivo-bin.bin", "w");

    if (arquivoTeste == NULL) {
        printf("Erro ao abrir o arquivo de texto.\n");
        exit(1);
    }
    while (current != NULL) {
        fprintf(arquivoTeste, "%d %s %s\n", current->ordem, current->descricao, current->quant_vendido);
        current = current->next;
    }

    //Fecha o arquivo binário
    fclose(arquivoTeste);


    // Imprime os elementos no terminal
    current = head;
    while (current != NULL) {
        printf("Ordem: %d, Descrição: %s, Quantidade vendida: %s\n", current->ordem, current->descricao, current->quant_vendido);
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
