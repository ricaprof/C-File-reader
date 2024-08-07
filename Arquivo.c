#define MAX_LINHA 100


struct Element {
    int ordem;
    char descricao[MAX_LINHA];
    char quant_vendido[MAX_LINHA];
    struct Element* next;
};

#include "Gerador.h"
#include "Editor.h"
#include "Exportador.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Uso: %s <argumento_string> <argumento_inteiro>\n", argv[0]);
        return 1;
    }


    Gerador(argv[1]); // Passa o argumento de string para Gerador
    Editor();
    Exportador(argv[2]); // Chama Exportador com o argumento inteiro

    return 0;
}