#ifndef TAREFAS_H
#define TAREFAS_H

#include <stdio.h>

#define MAX_USERS 100
#define MAX_CRIPTO 10
#define MAX_CPF 12
#define MAX_SENHA 20
#define MAX_NOME 50

typedef struct {
  float reais;
  float bitcoin;
  float ethereum;
  float ripple;
} Carteira;

typedef struct {
  char nome[MAX_NOME];
  char cpf[MAX_CPF];
  char senha[MAX_SENHA];
  Carteira carteira;
} Usuario;

typedef struct {
  char nome[MAX_NOME];
  float cotacao;
  float taxa_compra;
  float taxa_venda;
} Criptomoeda;

typedef struct {
    float bitcoin;
    float ethereum;
    float ripple;
} Cotacoes;

extern Usuario usuarios[MAX_USERS];
extern int num_usuarios;

extern Criptomoeda criptomoedas[MAX_CRIPTO];
extern int num_criptomoedas;

// Funções para gerenciamento de usuários
void carregar_dados_admin();
void salvar_dados_admin();
void salvar_dados();
int login_admin(const char *cpf, const char *senha);
int cadastrar_usuario(const char *nome, const char *cpf, const char *senha);
int excluir_usuario(const char *cpf);
Usuario *buscar_usuario_por_cpf(const char *cpf);

// Funções para gerenciamento de criptomoedas
int cadastrar_criptomoeda(const char *nome, float cotacao, float taxa_compra,
                          float taxa_venda);
int excluir_criptomoeda(const char *nome);
void atualizar_cotacao(const char *nome_cripto, float cotacao);

// Funções para consulta
void consultar_saldo_usuario(const char *cpf);
void consultar_extrato_usuario(const char *cpf);

#endif
