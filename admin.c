#include "tarefas.h"
#include <stdio.h>
#include <string.h>



void menu_principal_admin() {
  int opcao;
  char cpf[MAX_CPF], nome[MAX_NOME], nome_cripto[MAX_NOME];
  float cotacao, taxa_compra, taxa_venda;

  do {
    printf("\n=== Menu Principal de Administração ===\n");
    printf("1. Cadastro de Novo Investidor\n");
    printf("2. Excluir Investidor\n");
    printf("3. Cadastro de Criptomoeda\n");
    printf("4. Excluir Criptomoeda\n");
    printf("5. Consultar Saldo de Investidor\n");
    printf("6. Consultar Extrato de Investidor\n");
    printf("7. Atualizar Cotação de Criptomoeda\n");
    printf("8. Sair\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);
    getchar(); // Limpar buffer

    switch (opcao) {
    case 1:
      // Cadastro de novo investidor
      printf("\n--- Cadastro de Novo Investidor ---\n");
      printf("Nome: ");
      fgets(nome, sizeof(nome), stdin);
      nome[strcspn(nome, "\n")] = '\0';

      printf("CPF: ");
      fgets(cpf, sizeof(cpf), stdin);
      cpf[strcspn(cpf, "\n")] = '\0';

      printf("Senha: ");
      char senha[MAX_SENHA];
      fgets(senha, sizeof(senha), stdin);
      senha[strcspn(senha, "\n")] = '\0';

      if (cadastrar_usuario(nome, cpf, senha)) {
        printf("Investidor cadastrado com sucesso!\n");
      } else {
        printf("Erro: Não foi possível cadastrar o investidor.\n");
      }
      break;

    case 2:
      // Excluir investidor
      printf("\n--- Excluir Investidor ---\n");
      printf("CPF do investidor: ");
      fgets(cpf, sizeof(cpf), stdin);
      cpf[strcspn(cpf, "\n")] = '\0';

      if (excluir_usuario(cpf)) {
        printf("Investidor excluído com sucesso!\n");
      } else {
        printf("Erro: Investidor não encontrado ou não pôde ser excluído.\n");
      }
      break;

    case 3:
      // Cadastro de criptomoeda
      printf("\n--- Cadastro de Criptomoeda ---\n");
      printf("Nome da Criptomoeda: ");
      fgets(nome_cripto, sizeof(nome_cripto), stdin);
      nome_cripto[strcspn(nome_cripto, "\n")] = '\0'; // Remover newline

      printf("Cotação Inicial: ");
      scanf("%f", &cotacao);
      getchar();

      printf("Taxa de Compra: ");
      scanf("%f", &taxa_compra);

      printf("Taxa de Venda: ");
      scanf("%f", &taxa_venda);

      // Passando todos os parâmetros para a função cadastrar_criptomoeda
      if (cadastrar_criptomoeda(nome_cripto, cotacao, taxa_compra,
                                taxa_venda)) {
        printf("Criptomoeda cadastrada com sucesso!\n");
      } else {
        printf("Erro: Não foi possível cadastrar a criptomoeda.\n");
      }
      break;

    case 4:
      // Excluir criptomoeda
      printf("\n--- Excluir Criptomoeda ---\n");
      printf("Nome da Criptomoeda: ");
      fgets(nome_cripto, sizeof(nome_cripto), stdin);
      nome_cripto[strcspn(nome_cripto, "\n")] = '\0';

      if (excluir_criptomoeda(nome_cripto)) {
        printf("Criptomoeda excluída com sucesso!\n");
      } else {
        printf("Erro: Criptomoeda não encontrada.\n");
      }
      break;

    case 5:
      // Consultar saldo de investidor
      printf("\n--- Consultar Saldo de Investidor ---\n");
      printf("CPF do investidor: ");
      fgets(cpf, sizeof(cpf), stdin);
      cpf[strcspn(cpf, "\n")] = '\0';

      consultar_saldo_usuario(cpf);
      break;

    case 6:
      // Consultar extrato de investidor
      printf("\n--- Consultar Extrato de Investidor ---\n");
      printf("CPF do investidor: ");
      fgets(cpf, sizeof(cpf), stdin);
      cpf[strcspn(cpf, "\n")] = '\0';

      consultar_extrato_usuario(cpf);
      break;

    case 7:
      // Atualizar cotação de criptomoeda
      printf("\n--- Atualizar Cotação de Criptomoeda ---\n");
      printf("Nome da Criptomoeda: ");
      fgets(nome_cripto, sizeof(nome_cripto), stdin);
      nome_cripto[strcspn(nome_cripto, "\n")] = '\0';

      printf("Nova Cotação: ");
      scanf("%f", &cotacao);
      getchar();

      atualizar_cotacao(nome_cripto, cotacao);
      break;

    case 8:
      // Sair
      printf("Saindo do sistema...\n");
      break;

    default:
      printf("Opção inválida! Tente novamente.\n");
      break;
    }
  } while (opcao != 8);
}

void menu_admin() {
  int opcao;
  char cpf[MAX_CPF], senha[MAX_SENHA];
  char nome[MAX_NOME];

  do {
    printf("\n=== Sistema de Gerenciamento de Administradores ===\n");
    printf("1. Cadastro de Administrador\n");
    printf("2. Login de Administrador\n");
    printf("3. Sair\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);
    getchar(); // Limpar buffer

    switch (opcao) {
    case 1:
      // Cadastro de administrador
      printf("\n--- Cadastro de Administrador ---\n");
      printf("Nome: ");
      fgets(nome, sizeof(nome), stdin);
      nome[strcspn(nome, "\n")] = '\0';

      printf("CPF: ");
      fgets(cpf, sizeof(cpf), stdin);
      cpf[strcspn(cpf, "\n")] = '\0';

      printf("Senha: ");
      fgets(senha, sizeof(senha), stdin);
      senha[strcspn(senha, "\n")] = '\0';

      if (cadastrar_usuario(nome, cpf, senha)) {
        printf("Administrador cadastrado com sucesso!\n");
      } else {
        printf("Erro: Não foi possível cadastrar o administrador. CPF já "
               "cadastrado ou limite atingido.\n");
      }
      break;
    salvar_dados();
    case 2:
      // Login de administrador
      printf("\n--- Login de Administrador ---\n");
      printf("CPF: ");
      fgets(cpf, sizeof(cpf), stdin);
      cpf[strcspn(cpf, "\n")] = '\0'; // Remover o '\n' do input

      printf("Senha: ");
      fgets(senha, sizeof(senha), stdin);
      senha[strcspn(senha, "\n")] = '\0';

      if (login_admin(cpf, senha) != -1) {
        printf("Login bem-sucedido! Bem-vindo ao sistema.\n");
        menu_principal_admin(); // Chama o menu principal após login
                                // bem-sucedido
      } else {
        printf("Erro: CPF ou senha incorretos.\n");
      }
      break;

    case 3:
      // Sair
      printf("Saindo do sistema...\n");
      break;

    default:
      printf("Opção inválida! Tente novamente.\n");
      break;
    }
  } while (opcao != 3);
}

int main() {
  carregar_dados_admin(); // Carregar dados do arquivo binário

  menu_admin(); // Chamar o menu de administração

  salvar_dados_admin(); // Salvar dados no arquivo binário
  return 0;
}
