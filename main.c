#include "tarefa.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  int opcao, usuario_logado = -1;
  char senha[20], cpf[12];

  carregar_dados(); // Carregar dados ao iniciar o programa

  while (usuario_logado == -1) {
    printf("\n--- Menu Inicial ---\n");
    printf("1. Cadastrar\n2. Login\nEscolha uma opção: ");
    scanf("%d", &opcao);

    if (opcao == 1) {
      if (num_usuarios < MAX_USERS) {
        printf("CPF: ");
        scanf("%s", cpf);

        // Verificar se o CPF já está cadastrado
        int cpf_duplicado = 0;
        for (int i = 0; i < num_usuarios; i++) {
          if (strcmp(usuarios[i].cpf, cpf) == 0) {
            printf("CPF já cadastrado! Tente novamente.\n");
            cpf_duplicado = 1;
            break;
          }
        }

        if (!cpf_duplicado) {
          strcpy(usuarios[num_usuarios].cpf, cpf);
          printf("Senha: ");
          scanf("%s", usuarios[num_usuarios].senha);
          usuarios[num_usuarios].carteira.reais = 0.0;
          usuarios[num_usuarios].carteira.bitcoin = 0.0;
          usuarios[num_usuarios].carteira.ethereum = 0.0;
          usuarios[num_usuarios].carteira.ripple = 0.0;
          num_usuarios++;
          printf("Usuário cadastrado com sucesso!\n");
        }
      } else {
        printf("Número máximo de usuários atingido!\n");
      }
    } else if (opcao == 2) {
      printf("CPF: ");
      scanf("%s", cpf);
      printf("Senha: ");
      scanf("%s", senha);

      usuario_logado = login(cpf, senha);
      if (usuario_logado == -1) {
        printf("Login inválido!\n");
      }
    } else {
      printf("Opção inválida!\n");
    }
  }

  int escolha;
  Usuario *usuario = &usuarios[usuario_logado];
  do {
    printf("\n--- Menu ---\n");
    printf("1. Consultar saldo\n");
    printf("2. Depositar reais\n");
    printf("3. Sacar reais\n");
    printf("4. Comprar cripto\n");
    printf("5. Vender cripto\n");
    printf("6. Atualizar cotações\n");
    printf("7. Consultar extrato\n");
    printf("8. Sair\n");
    printf("Escolha uma opção: ");
    scanf("%d", &escolha);

    switch (escolha) {
    case 1:
      consultar_saldo(usuario);
      break;
    case 2: {
      float valor;
      printf("Digite o valor a depositar: ");
      scanf("%f", &valor);
      depositar_reais(usuario, valor);
      break;
    }
    case 3: {
      float valor;
      printf("Digite o valor a sacar: ");
      scanf("%f", &valor);
      printf("Digite sua senha: ");
      scanf("%s", senha);
      sacar_reais(usuario, valor, senha);
      break;
    }
    case 4: {
      char cripto[20];
      float valor;
      printf("Digite o tipo de cripto (bitcoin/ethereum/ripple): ");
      scanf("%s", cripto);
      printf("Digite o valor a comprar: ");
      scanf("%f", &valor);
      printf("Digite sua senha: ");
      scanf("%s", senha);
      comprar_cripto(usuario, senha, cripto, valor);
      break;
    }
    case 5: {
      char cripto[20];
      float valor;
      printf("Digite o tipo de cripto (bitcoin/ethereum/ripple): ");
      scanf("%s", cripto);
      printf("Digite o valor a vender: ");
      scanf("%f", &valor);
      printf("Digite sua senha: ");
      scanf("%s", senha);
      vender_cripto(usuario, senha, cripto, valor);
      break;
    }
    case 6:
      atualizar_cotacoes();
      break;
    case 7:
      consultar_extrato(usuario);
      break;
    case 8:
      salvar_dados(); // Salvar os dados ao sair do programa
      printf("Saindo...\n");
      break;
    default:
      printf("Opção inválida!\n");
    }
  } while (escolha != 8);

  return 0;
}
