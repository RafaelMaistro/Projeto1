#include "tarefas.h"
#include <stdio.h>
#include <string.h>

Usuario usuarios[MAX_USERS];
int num_usuarios = 0;

Criptomoeda criptomoedas[MAX_CRIPTO];
int num_criptomoedas = 0;

void carregar_dados_admin() {
  FILE *file = fopen("dados_admin.bin", "rb");
  if (file) {
    fread(&num_usuarios, sizeof(int), 1, file);
    fread(usuarios, sizeof(Usuario), num_usuarios, file);
    fread(&num_criptomoedas, sizeof(int), 1, file);
    fread(criptomoedas, sizeof(Criptomoeda), num_criptomoedas, file);
    fclose(file);
  }
}

void salvar_dados_admin() {
  FILE *file = fopen("dados_admin.bin", "wb");
  if (file) {
    fwrite(&num_usuarios, sizeof(int), 1, file);
    fwrite(usuarios, sizeof(Usuario), num_usuarios, file);
    fwrite(&num_criptomoedas, sizeof(int), 1, file);
    fwrite(criptomoedas, sizeof(Criptomoeda), num_criptomoedas, file);
    fclose(file);
  }
}

int login_admin(const char *cpf, const char *senha) {
  for (int i = 0; i < num_usuarios; i++) {
    if (strcmp(usuarios[i].cpf, cpf) == 0 &&
        strcmp(usuarios[i].senha, senha) == 0) {
      return i;
    }
  }
  return -1;
}

int cadastrar_usuario(const char *nome, const char *cpf, const char *senha) {
    FILE *arquivo = fopen("usuarios.dat", "ab"); // Abre o arquivo em modo de adição binária
    if (!arquivo) {
        perror("Erro ao abrir o arquivo");
        return 0;
    }

    Usuario novo_usuario;
    strncpy(novo_usuario.nome, nome, MAX_NOME);
    strncpy(novo_usuario.cpf, cpf, MAX_CPF);
    strncpy(novo_usuario.senha, senha, MAX_SENHA);

    size_t escrito = fwrite(&novo_usuario, sizeof(Usuario), 1, arquivo);
    fclose(arquivo);

    return escrito == 1; // Retorna 1 se o registro foi salvo com sucesso
}
int excluir_usuario(const char *cpf) {
  for (int i = 0; i < num_usuarios; i++) {
    if (strcmp(usuarios[i].cpf, cpf) == 0) {
      for (int j = i; j < num_usuarios - 1; j++) {
        usuarios[j] = usuarios[j + 1];
      }
      num_usuarios--;
      return 1;
    }
  }
  return 0;
}

Usuario *buscar_usuario_por_cpf(const char *cpf) {
  for (int i = 0; i < num_usuarios; i++) {
    if (strcmp(usuarios[i].cpf, cpf) == 0) {
      return &usuarios[i];
    }
  }
  return NULL;
}

int cadastrar_criptomoeda(const char *nome, float cotacao, float taxa_compra,
                          float taxa_venda) {
  if (num_criptomoedas >= MAX_CRIPTO)
    return 0;

  for (int i = 0; i < num_criptomoedas; i++) {
    if (strcmp(criptomoedas[i].nome, nome) == 0)
      return 0;
  }

  strcpy(criptomoedas[num_criptomoedas].nome, nome);
  criptomoedas[num_criptomoedas].cotacao = cotacao;
  criptomoedas[num_criptomoedas].taxa_compra = taxa_compra;
  criptomoedas[num_criptomoedas].taxa_venda = taxa_venda;
  num_criptomoedas++;
  return 1;
}

int excluir_criptomoeda(const char *nome) {
  for (int i = 0; i < num_criptomoedas; i++) {
    if (strcmp(criptomoedas[i].nome, nome) == 0) {
      for (int j = i; j < num_criptomoedas - 1; j++) {
        criptomoedas[j] = criptomoedas[j + 1];
      }
      num_criptomoedas--;
      return 1;
    }
  }
  return 0;
}

void atualizar_cotacao(const char *nome_cripto, float cotacao) {
  for (int i = 0; i < num_criptomoedas; i++) {
    if (strcmp(criptomoedas[i].nome, nome_cripto) == 0) {
      criptomoedas[i].cotacao = cotacao;
      return;
    }
  }
}

void consultar_saldo_usuario(const char *cpf) {
  Usuario *usuario = buscar_usuario_por_cpf(cpf);
  if (usuario) {
    printf("Saldo do usuário %s:\n", usuario->nome);
    printf("Reais: %.2f\n", usuario->carteira.reais);
    printf("Bitcoin: %.6f\n", usuario->carteira.bitcoin);
    printf("Ethereum: %.6f\n", usuario->carteira.ethereum);
    printf("Ripple: %.6f\n", usuario->carteira.ripple);
  } else {
    printf("Usuário não encontrado.\n");
  }
}

void consultar_extrato_usuario(const char *cpf) {
  printf("Exibindo extrato do investidor com CPF: %s\n", cpf);
}
