#include <stdio.h>
#include <stdlib.h>

struct elemento{
     int valor;
     int linha;
     int coluna;
     struct elemento * dir; // ponteiro para o próximo elemento não nulo da direita
     struct elemento * baixo; // ponteiro para o próximo elemento não nulo abaixo
};

// ASSINATURAS DE FUNÇÕES
void add_valor(struct elemento ** vetor_linhas, struct elemento ** vetor_colunas);
void consulta(struct elemento ** vetor_linhas);
void soma_linha(struct elemento ** vetor_linhas);
void soma_coluna(struct elemento ** vetor_colunas);
void excluir(int m, struct elemento ** vetor_linhas, struct elemento ** vetor_colunas);

void main(){
     int m = 0, n = 0; // Variáveis utilizadas para o tamanho dos vetores de ponteiros (m linhas e n colunas)

     printf("Ola.\nPara criar sua matriz, digite o numero de linhas(m) e colunas(n)\nno seguinte formato 'm n'\n  -");
     scanf("%d %d", &m, &n);
     struct elemento ** vetor_linhas = (struct elemento **) calloc(m, sizeof(struct elemento *)); //Vetor vertical com ponteiros para os primeiros elementos das linhas
     struct elemento ** vetor_colunas = (struct elemento **) calloc(n, sizeof(struct elemento *)); //Vetor vertical com ponteiros para os primeiros elementos das colunas
     
     int opcao = 0;
     do{
          system("cls"); //Limpa tela
          printf("Digite uma opcao\n");
          printf("  1 - Adicionar um valor\n");
          printf("  2 - Consultar um valor\n");
          printf("  3 - Consultar soma de uma linha\n");
          printf("  4 - Consultar soma de uma coluna\n");
          printf("  5 - Excluir a matriz\n");
          printf("      OPCAO: "); scanf("%d", &opcao);
          
          switch(opcao){
                 case 1:
                      add_valor(vetor_linhas, vetor_colunas);
                      break;
                 case 2:
                      consulta(vetor_linhas);
                      break;
                 case 3:
                      soma_linha(vetor_linhas);
                      break;
                 case 4:
                      soma_coluna(vetor_colunas);
                      break;
                 case 5:
                      excluir(m, vetor_linhas, vetor_colunas);
                      break;
                 default:
                      break;
          }
     }while(1);
     getch();
}

void add_valor(struct elemento ** vetor_linhas, struct elemento ** vetor_colunas){
     /*
     Função para adicionar valores na matriz nas posições (i, j) a partir da forma 'v m n'
     Sendo v o valor, m a linha, n a coluna
     */
     system("cls"); //Limpa tela
     printf("Para adicionar um valor(v) em uma linha(m) e uma coluna(n)\ndigite na sequencia 'v m n'\n  -");
     int val = 0 , lin = 0, col = 0;
     scanf("%d %d %d", &val, &lin, &col);
     lin--; col--; // O usuário vai digitar um valor de 1 até N, porém trabalhamos de 0 até N-1 no vetor
     
     
     struct elemento * novo_elemento = (struct elemento *) calloc(1, sizeof(struct elemento));
     novo_elemento -> valor = val;
     novo_elemento -> linha = lin;
     novo_elemento -> coluna = col;      
     
     if(vetor_linhas[lin] == NULL){
           // Primeiro elemento a ser adicionado na linha
           novo_elemento -> dir = NULL;
           vetor_linhas[lin] = novo_elemento;
     }else if(col < vetor_linhas[lin] -> coluna){
           // Quando um elemento vira o novo primeiro da linha
           novo_elemento -> dir = vetor_linhas[lin];
           vetor_linhas[lin] = novo_elemento;
     }else{
           // Quando já há pelo menos um elemento na linha e o novo virá depois do primeiro
           struct elemento * auxiliar = vetor_linhas[lin];
           while(auxiliar -> dir != NULL && col > auxiliar -> dir)
                 auxiliar = auxiliar -> dir;
           novo_elemento -> dir = auxiliar -> dir;
           auxiliar -> dir = novo_elemento;
     }
     
     if(vetor_colunas[col] == NULL){
           // Primeiro elemento a ser adicionado na coluna
           novo_elemento -> baixo = NULL;
           vetor_colunas[col] = novo_elemento;
     }else if(lin < vetor_colunas[col] -> linha){
           // Quando um elemento vira o novo primeiro da coluna
           novo_elemento -> baixo = vetor_colunas[col];
           vetor_colunas[col] = novo_elemento;
     }else{
           // Quando já há pelo menos um elemento na coluna e o novo virá depois do primeiro
           struct elemento * auxiliar = vetor_colunas[col];
           while(auxiliar -> baixo != NULL && lin > auxiliar -> baixo)
                 auxiliar = auxiliar -> baixo;
           novo_elemento -> baixo = auxiliar -> baixo;
           auxiliar -> baixo = novo_elemento;
     }
}


void consulta(struct elemento ** vetor_linhas){
     /*
     Função para consultar o valor de uma posição (i, j) dada na forma 'i j'
     */
     system("cls"); //Limpa tela
     int i, j;
     printf("Digite a linha(i) e a coluna(j) no seguinte formato 'i j'\n  -");
     scanf("%d %d", &i, &j);
     i--, j--;
     
     printf("Valor na posicao: ");
     if(vetor_linhas[i] == NULL)
           printf("0");
     else{
          struct elemento * auxiliar = vetor_linhas[i];
          if(auxiliar -> coluna > j)
               printf("0");
          else if(auxiliar -> coluna == j)
               printf("%d", auxiliar -> valor);
          else{
               if(auxiliar -> dir == NULL){
                     printf("0");
               }else {
                     while(auxiliar -> dir -> coluna <= j)
                          auxiliar = auxiliar -> dir;
                     if(auxiliar -> coluna == j)
                          printf("%d", auxiliar -> valor);
                     else
                          printf("0");
               }
          }
          
     }
     getch();
}

void soma_linha(struct elemento ** vetor_linhas){
     /*
     Função para obter a soma de uma linha inserida pelo usuário
     */
     system("cls");
     printf("Digite a linha que deseja obter a soma: ");
     int lin = 0;
     scanf("%d", &lin);
     printf("A soma da linha %d resulta em: ", lin);
     lin--;
     int somatorio = 0;
     if(vetor_linhas[lin] == NULL)
          printf("0");
     else{
          struct elemento * auxiliar = vetor_linhas[lin];
          somatorio = auxiliar -> valor;
          while(auxiliar -> dir != NULL){
                auxiliar = auxiliar -> dir;
                somatorio += auxiliar -> valor;
          }
          printf("%d", somatorio);
     }
     getch();
}

void soma_coluna(struct elemento ** vetor_colunas){
     /*
     Função para obter a soma de uma coluna inserida pelo usuário
     */
     system("cls");
     printf("Digite a coluna que deseja obter a soma: ");
     int col = 0;
     scanf("%d", &col);
     printf("A soma da coluna %d resulta em: ", col);
     col--;
     int somatorio = 0;
     if(vetor_colunas[col] == NULL)
          printf("0");
     else{
          struct elemento * auxiliar = vetor_colunas[col];
          somatorio = auxiliar -> valor;
          while(auxiliar -> baixo != NULL){
                auxiliar = auxiliar -> baixo;
                somatorio += auxiliar -> valor;
          }
          printf("%d", somatorio);
     }
     getch();
}

void excluir(int m, struct elemento ** vetor_linhas, struct elemento ** vetor_colunas){
     /*
     Função para excluir a matriz
     */
     system("cls");
     int i = 0;
     struct elemento * auxiliar1 = NULL;
     struct elemento * auxiliar2 = NULL;

     for(i = 0; i < m; i ++){
                 if(vetor_linhas[i] != NULL){
                        auxiliar1 = vetor_linhas[i];
                        if(auxiliar1 -> dir == NULL){
                             free(auxiliar1);
                        }else{
                              auxiliar2 = vetor_linhas[i] -> dir;
                              while(auxiliar1 -> dir != NULL){
                                  free(auxiliar1);
                                  auxiliar1 = auxiliar2;
                                  auxiliar2 = auxiliar2 -> dir;
                                  free(auxiliar2);
                                  
                              }
                        }
                 }
     }
     free(auxiliar1);
     free(vetor_linhas);
     free(vetor_colunas);
     printf("EXCLUSAO DA MATRIZ COM SUCESSO");
     getch();
     system("exit");
}
