#ifndef PROJETO_C2_EXPORTADOR_H
#define PROJETO_C2_EXPORTADOR_H

#endif //PROJETO_C2_EXPORTADOR_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINHA 100



int Exportador(const char *test){

    int num_elementos = 0;
    char linha[MAX_LINHA];

    FILE *arquivo = fopen("dados_atualizados.bin", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo binário\n");
        exit(1);
    }

    // Cria a cabeça da lista encadeada
    struct Element* head = NULL;
    struct Element* tail = NULL;

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

    fclose(arquivo);

    struct Element *current = head;
    FILE* arquivoTeste = fopen(test, "w");

    if (arquivoTeste == NULL) {
        printf("Erro ao abrir o arquivo de texto.\n");
        exit(1);
    }
    while (current != NULL) {
        fprintf(arquivoTeste, "%d %s %s\n", current->ordem, current->descricao, current->quant_vendido);
        current = current->next;
    }

    fclose(arquivoTeste);


}