#include <stdio.h>

#define LINHAS 5
#define COLUNAS 5
#define TAM_NAVIO 3

// Funcao pra verificar se o navio horizontal cabe no tabuleiro
int validaHorizontal(int tabuleiro[LINHAS][COLUNAS], int linha, int coluna) {
    if (coluna + TAM_NAVIO > COLUNAS) { // se ultrapassa o limite do tabuleiro
        return 0;
    }
    // Checa se as posicoes estao livres (valor 0)
    for (int i = 0; i < TAM_NAVIO; i++) {
        if (tabuleiro[linha][coluna + i] != 0) {
            return 0;
        }
    }
    return 1;
}

// Funcao pra verificar se o navio vertical cabe no tabuleiro
int validaVertical(int tabuleiro[LINHAS][COLUNAS], int linha, int coluna) {
    if (linha + TAM_NAVIO > LINHAS) { // se ultrapassa o limite do tabuleiro
        return 0;
    }
    // Checa se as posicoes estao livres (valor 0)
    for (int i = 0; i < TAM_NAVIO; i++) {
        if (tabuleiro[linha + i][coluna] != 0) {
            return 0;
        }
    }
    return 1;
}

// Coloca o navio na horizontal e imprime as coordenadas de cada parte
void colocaHorizontal(int tabuleiro[LINHAS][COLUNAS], int linha, int coluna, int navio[TAM_NAVIO]) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[linha][coluna + i] = navio[i];
        printf("Navio horizontal parte %d colocado em (%d, %d)\n", i + 1, linha, coluna + i);
    }
}

// Coloca o navio na vertical e imprime as coordenadas de cada parte
void colocaVertical(int tabuleiro[LINHAS][COLUNAS], int linha, int coluna, int navio[TAM_NAVIO]) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[linha + i][coluna] = navio[i];
        printf("Navio vertical parte %d colocado em (%d, %d)\n", i + 1, linha + i, coluna);
    }
}

// Mostra o tabuleiro no console
void mostraTabuleiro(int tabuleiro[LINHAS][COLUNAS]) {
    printf("\nTabuleiro:\n");
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    // Inicializa o tabuleiro com 0 (agua)
    int tabuleiro[LINHAS][COLUNAS] = {0};
    
    // Vetores que representam os navios (cada posicao com valor 3)
    int navioH[TAM_NAVIO] = {3, 3, 3};
    int navioV[TAM_NAVIO] = {3, 3, 3};
    
    // Coordenadas definidas direto no codigo
    // Para o navio horizontal, vamos colocar na linha 1, coluna 1 
    // Assim ele ocupa as posicoes (1,1), (1,2) e (1,3)
    int linhaH = 1, colunaH = 1;
    
    // Para o navio vertical, vamos colocar na linha 2, coluna 4 
    // Assim ele ocupa as posicoes (2,4), (3,4) e (4,4)
    int linhaV = 2, colunaV = 4;
    
    // Valida e coloca o navio horizontal
    if (validaHorizontal(tabuleiro, linhaH, colunaH)) {
        colocaHorizontal(tabuleiro, linhaH, colunaH, navioH);
    } else {
        printf("Nao foi possivel colocar o navio horizontal em (%d, %d)\n", linhaH, colunaH);
    }
    
    // Valida e coloca o navio vertical
    if (validaVertical(tabuleiro, linhaV, colunaV)) {
        colocaVertical(tabuleiro, linhaV, colunaV, navioV);
    } else {
        printf("Nao foi possivel colocar o navio vertical em (%d, %d)\n", linhaV, colunaV);
    }
    
    // Exibe o tabuleiro com os navios posicionados
    mostraTabuleiro(tabuleiro);
    
    return 0;
}
