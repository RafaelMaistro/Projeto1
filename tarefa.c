#include "tarefa.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Variáveis globais
Usuario usuarios[MAX_USERS];
Transacao transacoes[MAX_USERS][MAX_TRANSACTIONS];
int num_usuarios = 0;
int num_transacoes[MAX_USERS] = {0};
Cotacao cotacao = {25000.0, 1500.0, 0.5};

// Função de login
int login(char *cpf, char *senha) {
  for (int i = 0; i < num_usuarios; i++) {
    if (strcmp(usuarios[i].cpf, cpf) == 0 &&
        strcmp(usuarios[i].senha, senha) == 0) {
      return i;
    }
  }
  return -1;
}

// Função de consultar saldo
void consultar_saldo(Usuario *usuario) {
  printf("\n--- Saldo da Carteira ---\n");
  printf("Reais: R$ %.2f\n", usuario->carteira.reais);
  printf("Bitcoin: %.6f BTC\n", usuario->carteira.bitcoin);
  printf("Ethereum: %.6f ETH\n", usuario->carteira.ethereum);
  printf("Ripple: %.6f XRP\n", usuario->carteira.ripple);
}

// Atualiza as cotações das criptomoedas
void atualizar_cotacoes() {
  srand(time(NULL));
  cotacao.cotacao_bitcoin *= (1 + (rand() % 11 - 5) / 100.0);
  cotacao.cotacao_ethereum *= (1 + (rand() % 11 - 5) / 100.0);
  cotacao.cotacao_ripple *= (1 + (rand() % 11 - 5) / 100.0);
  printf("Cotações atualizadas!\n");
}

// Função de depósito
void depositar_reais(Usuario *usuario, float valor) {
  usuario->carteira.reais += valor;
  printf("Depósito de R$ %.2f realizado com sucesso!\n", valor);
  registrar_transacao(usuario, "deposito", "", valor, 0.0);
}

// Função de saque
void sacar_reais(Usuario *usuario, float valor, char *senha) {
  if (strcmp(usuario->senha, senha) != 0) {
    printf("Senha incorreta!\n");
    return;
  }
  if (valor > usuario->carteira.reais) {
    printf("Saldo insuficiente!\n");
    return;
  }
  usuario->carteira.reais -= valor;
  printf("Saque de R$ %.2f realizado com sucesso!\n", valor);
  registrar_transacao(usuario, "saque", "", -valor, 0.0);
}

// Função para registrar transações
void registrar_transacao(Usuario *usuario, char *tipo, char *cripto,
                         float valor, float taxa) {
  int idx_usuario = -1;
  for (int i = 0; i < num_usuarios; i++) {
    if (strcmp(usuarios[i].cpf, usuario->cpf) == 0) {
      idx_usuario = i;
      break;
    }
  }

  if (idx_usuario != -1 && num_transacoes[idx_usuario] < MAX_TRANSACTIONS) {
    Transacao *transacao =
        &transacoes[idx_usuario][num_transacoes[idx_usuario]];

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(transacao->data, "%02d/%02d/%04d %02d:%02d:%02d", tm.tm_mday,
            tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);

    strcpy(transacao->tipo, tipo);
    strcpy(transacao->cripto, cripto);
    transacao->valor = valor;
    transacao->taxa = taxa;

    num_transacoes[idx_usuario]++;
  }
}

// Função de compra de criptomoeda
void comprar_cripto(Usuario *usuario, char *senha, char tipo[], float valor) {
  if (strcmp(usuario->senha, senha) != 0) {
    printf("Senha incorreta!\n");
    return;
  }

  float taxa, valor_com_taxa;

  if (strcmp(tipo, "bitcoin") == 0) {
    taxa = valor * 0.02;
    valor_com_taxa = valor + taxa;
    if (usuario->carteira.reais < valor_com_taxa) {
      printf("Saldo insuficiente!\n");
      return;
    }
    usuario->carteira.reais -= valor_com_taxa;
    usuario->carteira.bitcoin += valor / cotacao.cotacao_bitcoin;
    registrar_transacao(usuario, "compra", "bitcoin", -valor, taxa);
  } else if (strcmp(tipo, "ethereum") == 0) {
    taxa = valor * 0.01;
    valor_com_taxa = valor + taxa;
    if (usuario->carteira.reais < valor_com_taxa) {
      printf("Saldo insuficiente!\n");
      return;
    }
    usuario->carteira.reais -= valor_com_taxa;
    usuario->carteira.ethereum += valor / cotacao.cotacao_ethereum;
    registrar_transacao(usuario, "compra", "ethereum", -valor, taxa);
  } else if (strcmp(tipo, "ripple") == 0) {
    taxa = valor * 0.01;
    valor_com_taxa = valor + taxa;
    if (usuario->carteira.reais < valor_com_taxa) {
      printf("Saldo insuficiente!\n");
      return;
    }
    usuario->carteira.reais -= valor_com_taxa;
    usuario->carteira.ripple += valor / cotacao.cotacao_ripple;
    registrar_transacao(usuario, "compra", "ripple", -valor, taxa);
  } else {
    printf("Tipo de criptomoeda inválido!\n");
  }
}

// Função de venda de criptomoeda
void vender_cripto(Usuario *usuario, char *senha, char tipo[], float valor) {
  if (strcmp(usuario->senha, senha) != 0) {
    printf("Senha incorreta!\n");
    return;
  }

  float taxa, valor_com_taxa;

  if (strcmp(tipo, "bitcoin") == 0) {
    taxa = valor * 0.03;
    valor_com_taxa = valor + taxa;
    if (usuario->carteira.bitcoin < valor / cotacao.cotacao_bitcoin) {
      printf("Saldo insuficiente em BTC!\n");
      return;
    }
    usuario->carteira.reais += valor - taxa;
    usuario->carteira.bitcoin -= valor / cotacao.cotacao_bitcoin;
    registrar_transacao(usuario, "venda", "bitcoin", valor, taxa);
  } else if (strcmp(tipo, "ethereum") == 0) {
    taxa = valor * 0.02;
    valor_com_taxa = valor + taxa;
    if (usuario->carteira.ethereum < valor / cotacao.cotacao_ethereum) {
      printf("Saldo insuficiente em ETH!\n");
      return;
    }
    usuario->carteira.reais += valor - taxa;
    usuario->carteira.ethereum -= valor / cotacao.cotacao_ethereum;
    registrar_transacao(usuario, "venda", "ethereum", valor, taxa);
  } else if (strcmp(tipo, "ripple") == 0) {
    taxa = valor * 0.01;
    valor_com_taxa = valor + taxa;
    if (usuario->carteira.ripple < valor / cotacao.cotacao_ripple) {
      printf("Saldo insuficiente em XRP!\n");
      return;
    }
    usuario->carteira.reais += valor - taxa;
    usuario->carteira.ripple -= valor / cotacao.cotacao_ripple;
    registrar_transacao(usuario, "venda", "ripple", valor, taxa);
  } else {
    printf("Tipo de criptomoeda inválido!\n");
  }
}

// Função para consultar o extrato
void consultar_extrato(Usuario *usuario) {
  int idx_usuario = -1;
  for (int i = 0; i < num_usuarios; i++) {
    if (strcmp(usuarios[i].cpf, usuario->cpf) == 0) {
      idx_usuario = i;
      break;
    }
  }

  if (idx_usuario != -1) {
    printf("\n--- Extrato de Transações ---\n");
    for (int i = 0; i < num_transacoes[idx_usuario]; i++) {
      Transacao *t = &transacoes[idx_usuario][i];
      printf("Data: %s, Tipo: %s, Criptomoeda: %s, Valor: %.2f, Taxa: %.2f\n",
             t->data, t->tipo, t->cripto, t->valor, t->taxa);
    }
  }
}

// Função para salvar os dados em arquivos binários
void salvar_dados() {
  FILE *file = fopen("usuarios.dat", "wb");
  if (!file) {
    printf("Erro ao abrir o arquivo para salvar os usuários.\n");
    return;
  }

  fwrite(&num_usuarios, sizeof(int), 1, file); // Salva o número de usuários
  fwrite(usuarios, sizeof(Usuario), num_usuarios, file); // Salva os usuários
  fclose(file);

  // Salva as transações
  FILE *file_trans = fopen("transacoes.dat", "wb");
  if (!file_trans) {
    printf("Erro ao abrir o arquivo para salvar as transações.\n");
    return;
  }

  fwrite(num_transacoes, sizeof(int), MAX_USERS,
         file_trans); // Salva o número de transações de cada usuário
  fwrite(transacoes, sizeof(Transacao), MAX_USERS * MAX_TRANSACTIONS,
         file_trans); // Salva todas as transações
  fclose(file_trans);
}

// Função para carregar os dados de arquivos binários
void carregar_dados() {
  FILE *file = fopen("usuarios.dat", "rb");
  if (!file) {
    printf("Arquivo de usuários não encontrado. Iniciando com dados vazios.\n");
    return;
  }

  fread(&num_usuarios, sizeof(int), 1, file); // Carrega o número de usuários
  fread(usuarios, sizeof(Usuario), num_usuarios, file); // Carrega os usuários
  fclose(file);

  // Carrega as transações
  FILE *file_trans = fopen("transacoes.dat", "rb");
  if (!file_trans) {
    printf("Arquivo de transações não encontrado.\n");
    return;
  }

  fread(num_transacoes, sizeof(int), MAX_USERS,
        file_trans); // Carrega o número de transações de cada usuário
  fread(transacoes, sizeof(Transacao), MAX_USERS * MAX_TRANSACTIONS,
        file_trans); // Carrega todas as transações
  fclose(file_trans);
}
