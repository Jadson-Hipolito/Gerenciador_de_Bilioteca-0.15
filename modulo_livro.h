#ifndef MODULO_LIVRO_H
#define MODULO_LIVRO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CPFS 100
#define MAX_DIGITOS_CPF 12

struct livro {
    char titulo[300];
    char autor[150];
    int quant;
    int quant_disp;
    char **lista_cpfs
    int local;
    char isbn;
};

extern struct livro biblioteca[5000];
extern int numLivros;

void editor_livro(char *titulo);
int buscar_livro_por_titulo(char *termo);
void registrar_livro();
int menu_livro();

#endif