#ifndef TAREFA_H
#define TAREFA_H

#define MAX_USERS 10
#define MAX_TRANSACTIONS 100

// Estruturas
typedef struct {
  float reais;
  float bitcoin;
  float ethereum;
  float ripple;
} Carteira;

typedef struct {
  char cpf[12];
  char senha[20];
  Carteira carteira;
} Usuario;

typedef struct {
  char data[20];
  char tipo[10];
  char cripto[20];
  float valor;
  float taxa;
} Transacao;

typedef struct {
  float cotacao_bitcoin;
  float cotacao_ethereum;
  float cotacao_ripple;
} Cotacao;

// Variáveis globais
extern Usuario usuarios[MAX_USERS];
extern int num_usuarios;
extern Transacao transacoes[MAX_USERS][MAX_TRANSACTIONS];
extern int num_transacoes[MAX_USERS];
extern Cotacao cotacao;

// Funções
int login(char *cpf, char *senha);
void consultar_saldo(Usuario *usuario);
void atualizar_cotacoes();
void depositar_reais(Usuario *usuario, float valor);
void sacar_reais(Usuario *usuario, float valor, char *senha);
void registrar_transacao(Usuario *usuario, char *tipo, char *cripto,
                         float valor, float taxa);
void comprar_cripto(Usuario *usuario, char *senha, char tipo[], float valor);
void vender_cripto(Usuario *usuario, char *senha, char tipo[], float valor);

void consultar_extrato(Usuario *usuario);
void salvar_dados();
void carregar_dados();

#endif
