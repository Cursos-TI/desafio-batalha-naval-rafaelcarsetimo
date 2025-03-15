#include <stdio.h>

#define LINHAS 10
#define COLUNAS 10
#define TAM_NAVIO 3

// Valida se um navio horizontal cabe no tabuleiro sem sobreposição
int validaHorizontal(int tabuleiro[LINHAS][COLUNAS], int linha, int coluna) {
    if (coluna + TAM_NAVIO > COLUNAS) {
        return 0;
    }
    for (int i = 0; i < TAM_NAVIO; i++) {
        if (tabuleiro[linha][coluna + i] != 0) {
            return 0;
        }
    }
    return 1;
}

// Valida se um navio vertical cabe no tabuleiro sem sobreposição
int validaVertical(int tabuleiro[LINHAS][COLUNAS], int linha, int coluna) {
    if (linha + TAM_NAVIO > LINHAS) {
        return 0;
    }
    for (int i = 0; i < TAM_NAVIO; i++) {
        if (tabuleiro[linha + i][coluna] != 0) {
            return 0;
        }
    }
    return 1;
}

// Valida se um navio diagonal (crescente) cabe no tabuleiro sem sobreposição
// Aqui, linha e coluna aumentam simultaneamente.
int validaDiagonalCrescente(int tabuleiro[LINHAS][COLUNAS], int linha, int coluna) {
    if (linha + TAM_NAVIO > LINHAS || coluna + TAM_NAVIO > COLUNAS) {
        return 0;
    }
    for (int i = 0; i < TAM_NAVIO; i++) {
        if (tabuleiro[linha + i][coluna + i] != 0) {
            return 0;
        }
    }
    return 1;
}

// Valida se um navio diagonal (decrescente) cabe no tabuleiro sem sobreposição
// Aqui, a linha aumenta enquanto a coluna diminui.
int validaDiagonalDecrescente(int tabuleiro[LINHAS][COLUNAS], int linha, int coluna) {
    if (linha + TAM_NAVIO > LINHAS || coluna - TAM_NAVIO + 1 < 0) {
        return 0;
    }
    for (int i = 0; i < TAM_NAVIO; i++) {
        if (tabuleiro[linha + i][coluna - i] != 0) {
            return 0;
        }
    }
    return 1;
}

// Posiciona o navio na horizontal e imprime as coordenadas de cada parte
void colocaHorizontal(int tabuleiro[LINHAS][COLUNAS], int linha, int coluna, int navio[TAM_NAVIO]) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[linha][coluna + i] = navio[i];
        printf("Navio Horizontal parte %d colocado em (%d, %d)\n", i + 1, linha, coluna + i);
    }
}

// Posiciona o navio na vertical e imprime as coordenadas de cada parte
void colocaVertical(int tabuleiro[LINHAS][COLUNAS], int linha, int coluna, int navio[TAM_NAVIO]) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[linha + i][coluna] = navio[i];
        printf("Navio Vertical parte %d colocado em (%d, %d)\n", i + 1, linha + i, coluna);
    }
}

// Posiciona o navio na diagonal crescente e imprime as coordenadas
void colocaDiagonalCrescente(int tabuleiro[LINHAS][COLUNAS], int linha, int coluna, int navio[TAM_NAVIO]) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[linha + i][coluna + i] = navio[i];
        printf("Navio Diagonal Crescente parte %d colocado em (%d, %d)\n", i + 1, linha + i, coluna + i);
    }
}

// Posiciona o navio na diagonal decrescente e imprime as coordenadas
void colocaDiagonalDecrescente(int tabuleiro[LINHAS][COLUNAS], int linha, int coluna, int navio[TAM_NAVIO]) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[linha + i][coluna - i] = navio[i];
        printf("Navio Diagonal Decrescente parte %d colocado em (%d, %d)\n", i + 1, linha + i, coluna - i);
    }
}

// Exibe o tabuleiro completo no console
void mostraTabuleiro(int tabuleiro[LINHAS][COLUNAS]) {
    printf("\nTabuleiro Completo:\n");
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    // Cria o tabuleiro 10x10 com todas as posicoes iniciadas com 0 (agua)
    int tabuleiro[LINHAS][COLUNAS] = {0};

    // Vetores que representam os navios (cada posicao com valor 3)
    int navioH[TAM_NAVIO]   = {3, 3, 3};  // navio horizontal
    int navioV[TAM_NAVIO]   = {3, 3, 3};  // navio vertical
    int navioDC[TAM_NAVIO]  = {3, 3, 3};  // navio diagonal crescente
    int navioDD[TAM_NAVIO]  = {3, 3, 3};  // navio diagonal decrescente

    // Coordenadas definidas diretamente no código para cada navio:
    // Navio Horizontal: inicia em (2,2) e ocupa (2,2), (2,3) e (2,4)
    int linhaH = 2, colunaH = 2;
    // Navio Vertical: inicia em (5,7) e ocupa (5,7), (6,7) e (7,7)
    int linhaV = 5, colunaV = 7;
    // Navio Diagonal Crescente: inicia em (0,3) e ocupa (0,3), (1,4) e (2,5)
    int linhaDC = 0, colunaDC = 3;
    // Navio Diagonal Decrescente: inicia em (7,2) e ocupa (7,2), (8,1) e (9,0)
    int linhaDD = 7, colunaDD = 2;

    // Valida e posiciona o navio horizontal
    if (validaHorizontal(tabuleiro, linhaH, colunaH)) {
        colocaHorizontal(tabuleiro, linhaH, colunaH, navioH);
    } else {
        printf("Erro: nao foi possivel posicionar o navio horizontal em (%d, %d)\n", linhaH, colunaH);
    }

    // Valida e posiciona o navio vertical
    if (validaVertical(tabuleiro, linhaV, colunaV)) {
        colocaVertical(tabuleiro, linhaV, colunaV, navioV);
    } else {
        printf("Erro: nao foi possivel posicionar o navio vertical em (%d, %d)\n", linhaV, colunaV);
    }

    // Valida e posiciona o navio diagonal crescente
    if (validaDiagonalCrescente(tabuleiro, linhaDC, colunaDC)) {
        colocaDiagonalCrescente(tabuleiro, linhaDC, colunaDC, navioDC);
    } else {
        printf("Erro: nao foi possivel posicionar o navio diagonal crescente em (%d, %d)\n", linhaDC, colunaDC);
    }

    // Valida e posiciona o navio diagonal decrescente
    if (validaDiagonalDecrescente(tabuleiro, linhaDD, colunaDD)) {
        colocaDiagonalDecrescente(tabuleiro, linhaDD, colunaDD, navioDD);
    } else {
        printf("Erro: nao foi possivel posicionar o navio diagonal decrescente em (%d, %d)\n", linhaDD, colunaDD);
    }

    // Exibe o tabuleiro completo com todos os navios posicionados
    mostraTabuleiro(tabuleiro);

    return 0;
}
