#include "modulo_livro.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LIVROS 5000

struct livro biblioteca[MAX_LIVROS];
int numLivros = 0;

void emprestimo_livro() {
    char cpf[MAX_NOME];
    char isbn[MAX_NOME];

    // Obter CPF e ISBN do usuário
    printf("CPF do cliente ao qual irá retirar o livro: ");
    scanf("%s", cpf);
    printf("ISBN do livro ao qual irá retirar: ");
    scanf("%s", isbn);

    // Verificar se o cliente existe
    FILE *clientes_file = fopen("clientes.txt", "r");
    if (clientes_file == NULL) {
        printf("Erro ao abrir o arquivo de clientes.\n");
        return;
    }

    int cliente_encontrado = 0;
    Cliente cliente;
    while (fscanf(clientes_file, "%s %s %s %s %d %d", cliente.nome, cliente.endereco, cliente.telefone, cliente.cpf, &cliente.id, &cliente.ativ) == 6) {
        if (strcmp(cliente.cpf, cpf) == 0) {
            cliente_encontrado = 1;
            break;
        }
    }

    fclose(clientes_file);

    if (!cliente_encontrado) {
        printf("Cliente com CPF %s não encontrado.\n", cpf);
        return;
    }

    // Verificar se o livro existe
    FILE *biblioteca_file = fopen("biblioteca.txt", "r");
    if (biblioteca_file == NULL) {
        printf("Erro ao abrir o arquivo da biblioteca.\n");
        return;
    }

    int livro_encontrado = 0;
    Livro livro;
    while (fscanf(biblioteca_file, "%s %s %d %d %d %s", livro.titulo, livro.autor, &livro.quant, &livro.quant_disp, &livro.local, livro.isbn) == 6) {
        if (strcmp(livro.isbn, isbn) == 0) {
            livro_encontrado = 1;
            break;
        }
    }

    fclose(biblioteca_file);

    if (!livro_encontrado) {
        printf("Livro com ISBN %s não encontrado.\n", isbn);
        return;
    }

    // Verificar se o livro está disponível
    if (livro.quant_disp <= 0) {
        printf("O livro não está disponível para empréstimo.\n");
        return;
    }

    livro.quant_disp--;

      livro.lista_cpfs = malloc(MAX_CPFS * sizeof(char *));
      for (int i = 0; i < MAX_CPFS; i++) {
        livro.lista_cpfs[i] = malloc((MAX_NOME + 1) * sizeof(char));
      }

    strcpy(livro.lista_cpfs[MAX_CPFS - 1], cliente.cpf);  // Adiciona o CPF à lista_cpfs

    // Atualizar o arquivo da biblioteca com as modificações
    FILE *biblioteca_atualizada = fopen("biblioteca.txt", "w");
    if (biblioteca_atualizada == NULL) {
        printf("Erro ao abrir o arquivo da biblioteca para atualização.\n");
        return;
    }

    fprintf(biblioteca_atualizada, "%s %s %d %d %d %s\n", livro.titulo, livro.autor, livro.quant, livro.quant_disp, livro.local, livro.isbn);

    fclose(biblioteca_atualizada);

    printf("Empréstimo realizado com sucesso.\n");

  if (!encontrado) {
    return 0;
  }

  return encontrado;
}

void editor_livro(char *titulo) {
  int mudar;
  int novo_local;
  printf("\n=====================================\n");
  printf("=== Editor de Livros ===\n");
  printf("=====================================\n\n");
  printf("1 - Mudar Local do livro\n");
  printf("2 - Mudar quantidade de unidades\n");
  printf("0 - Retornar para o menu principal\n");
  printf("=====================================\n");
  printf("Escolha uma opção: ");
  scanf("%d", &mudar);

  switch (mudar) {
  case 1:
    printf("Novo local do livro: ");
    scanf("%d", &novo_local);
    for (int i = 0; i < numLivros; i++) {
      if (strcasecmp(biblioteca[i].titulo, titulo) == 0) {
        biblioteca[i].local = novo_local;
      }
    }
    break;
  case 2:
    printf("Nova quantidade de unidades: ");
    scanf("%d", &novo_local);
    for (int i = 0; i < numLivros; i++) {
      if (strcasecmp(biblioteca[i].titulo, titulo) == 0) {
        biblioteca[i].quant = novo_local;
      }
    }
    break;
  case 0:
    printf("Retornando para o menu principal.\n");
    break;
  default:
    printf("Opção inválida. Tente novamente.\n");
  }
}

int menu_livro() {
  int escolha = 1;
  char titulo[100];

  while (escolha != 0) {
    printf("\n=====================================\n");
    printf("=== Registro de Livros ===\n");
    printf("=====================================\n\n");
    printf("1 - Registrar Livros Novos\n");
    printf("2 - Editar Registro de Livro\n");
    printf("3 - Alugar Livro\n");
    printf("0 - Retornar para o menu principal\n");
    printf("=====================================\n");
    printf("Escolha uma opção: ");
    scanf("%d", &escolha);

    switch (escolha) {
    case 1:
      registrar_livro();
      break;
    case 2:
      printf("Nome do livro: ");
      scanf("%s", titulo);
      if (buscar_livro_por_titulo(titulo)) {
        editor_livro(titulo);
      }
      break;
    case 3:
      emprestimo_livro();
      break;
    case 0:
      printf("Retornando para o menu principal.\n");
      break;
    default:
      printf("Opção inválida. Tente novamente.\n");
    }
  }
  return 0;
}

void registrar_livro() {
    FILE *file;
    file = fopen("biblioteca.txt", "a");  // Open file in append mode

    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    if (numLivros < MAX_LIVROS) {
        printf("\n === Registrar Livro ===\n");

        printf("Nome do livro: ");
        scanf("%s", biblioteca[numLivros].titulo);
        fprintf(file, "Nome do livro: %s\n", biblioteca[numLivros].titulo);

        printf("Autor do livro: ");
        scanf("%s", biblioteca[numLivros].autor);
        fprintf(file, "Autor do livro: %s\n", biblioteca[numLivros].autor);

        printf("Quantidade de cópias do livro: ");
        scanf("%d", &biblioteca[numLivros].quant);
        fprintf(file, "Quantidade de cópias do livro: %d\n", biblioteca[numLivros].quant);

        biblioteca[numLivros].quant_disp = biblioteca[numLivros].quant;

        printf("Número do local (número de quatro dígitos): ");
        scanf("%d", &biblioteca[numLivros].local);
        fprintf(file, "Número do local: %d\n", biblioteca[numLivros].local);

        numLivros++;
    } else {
        printf("A biblioteca está cheia. Não é possível adicionar mais livros.\n");
    }

    fclose(file);  // Close the file
}

bool validar_isbn(const char *isbn) {
  if (isbn == NULL) {
    return false;
  }
  if (strlen(isbn) != 13) {
    return false; 
  }
  for (int i = 0; isbn[i] != '\0'; i++) {
    if (!isdigit(isbn[i]) && !(i == 12 && isbn[i] == 'X')) {
      return false; // ISBN inválido se contiver caracteres não permitidos
    }
  }

  // Calcula o dígito de verificação
  int soma = 0;
  for (int i = 0; i < 12; i++) {
    int digito = isbn[i] - '0';
    soma += (i % 2 == 0) ? digito : digito * 3;
  }
  int digitoVerificador = (10 - (soma % 10)) % 10;

  // Verifica o dígito de verificação
  if (isbn[12] != (digitoVerificador + '0')) {
    return false; // ISBN inválido se o dígito de verificação estiver errado
  }

  return true; // ISBN válido
}
