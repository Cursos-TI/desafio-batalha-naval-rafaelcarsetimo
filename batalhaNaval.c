#include <stdio.h>
#include <stdlib.h> // pra usar a funçao abs

#define LINHAS 10
#define COLUNAS 10
#define TAM_NAVIO 3
#define TAM_HAB 5  // tamanho das matrizes de habilidade (5x5)

// ------------------------
// Funçoes de validaçao dos navios (horizontal, vertical, etc)
// ------------------------

int validaHorizontal(int tabuleiro[LINHAS][COLUNAS], int linha, int coluna) {
    if (coluna + TAM_NAVIO > COLUNAS) { // se passar do limite das colunas
        return 0;
    }
    for (int i = 0; i < TAM_NAVIO; i++) {
        if (tabuleiro[linha][coluna + i] != 0) {
            return 0;
        }
    }
    return 1;
}

int validaVertical(int tabuleiro[LINHAS][COLUNAS], int linha, int coluna) {
    if (linha + TAM_NAVIO > LINHAS) { // se passar do limite das linhas
        return 0;
    }
    for (int i = 0; i < TAM_NAVIO; i++) {
        if (tabuleiro[linha + i][coluna] != 0) {
            return 0;
        }
    }
    return 1;
}

// ------------------------
// Funçoes de posicionamento dos navios
// ------------------------

void colocaHorizontal(int tabuleiro[LINHAS][COLUNAS], int linha, int coluna, int navio[TAM_NAVIO]) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[linha][coluna + i] = navio[i];
        printf("Navio Horizontal parte %d colocado em (%d, %d)\n", i+1, linha, coluna + i);
    }
}

void colocaVertical(int tabuleiro[LINHAS][COLUNAS], int linha, int coluna, int navio[TAM_NAVIO]) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[linha + i][coluna] = navio[i];
        printf("Navio Vertical parte %d colocado em (%d, %d)\n", i+1, linha + i, coluna);
    }
}

// ------------------------
// Funçoes pra gerar as matrizes de habilidade
// ------------------------

// Gera um "cone" apontando pra baixo. 
// O cone tem o ponto de origem no topo e se expande nas 3 primeiras linhas, as demais ficam 0.
void geraHabilidadeCone(int hab[TAM_HAB][TAM_HAB]) {
    int centro = TAM_HAB / 2; // centro = 2 para uma matriz 5x5
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            hab[i][j] = 0; // inicia zerado
            // pra as 3 primeiras linhas, aumenta a area afetada
            if(i < 3 && j >= centro - i && j <= centro + i) {
                hab[i][j] = 1;
            }
        }
    }
}

// Gera uma "cruz" com o centro na posição (2,2)
void geraHabilidadeCruz(int hab[TAM_HAB][TAM_HAB]) {
    int centro = TAM_HAB / 2;
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            // se for a linha do centro ou a coluna do centro, marca 1
            if(i == centro || j == centro) {
                hab[i][j] = 1;
            } else {
                hab[i][j] = 0;
            }
        }
    }
}

// Gera um "octaedro" que na verdade vai ser um losango (diamante)
// Usamos a distancia de Manhattan para definir o losango.
void geraHabilidadeOctaedro(int hab[TAM_HAB][TAM_HAB]) {
    int centro = TAM_HAB / 2;
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (abs(i - centro) + abs(j - centro) <= centro) {
                hab[i][j] = 1;
            } else {
                hab[i][j] = 0;
            }
        }
    }
}

// ------------------------
// Funçao pra sobrepor a matriz de habilidade no tabuleiro
// ------------------------
// O ponto de origem da habilidade sera o centro da matriz de habilidade.
// Ou seja, para cada celula da matriz de habilidade, a posicao no tabuleiro é:
// (origem_linha - centro + i, origem_coluna - centro + j)
void overlayHabilidade(int tabuleiro[LINHAS][COLUNAS], int hab[TAM_HAB][TAM_HAB], int origemLinha, int origemColuna) {
    int centro = TAM_HAB / 2;
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            // Calcula as posicoes correspondentes no tabuleiro
            int linhaTab = origemLinha - centro + i;
            int colunaTab = origemColuna - centro + j;
            // Verifica se ta dentro dos limites do tabuleiro
            if(linhaTab >= 0 && linhaTab < LINHAS && colunaTab >= 0 && colunaTab < COLUNAS) {
                // Se a habilidade afeta essa celula, marca com 5
                if(hab[i][j] == 1) {
                    tabuleiro[linhaTab][colunaTab] = 5;
                }
            }
        }
    }
}

// ------------------------
// Funçao pra mostrar o tabuleiro
// ------------------------
void mostraTabuleiro(int tabuleiro[LINHAS][COLUNAS]) {
    printf("\nTabuleiro Final:\n");
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    // Cria o tabuleiro 10x10, iniciando com 0 (agua)
    int tabuleiro[LINHAS][COLUNAS] = {0};

    // Vetores dos navios (cada posicao com valor 3)
    int navioH[TAM_NAVIO] = {3, 3, 3};
    int navioV[TAM_NAVIO] = {3, 3, 3};
    
    // Posiciona os navios como fizemos antes
    // Navio horizontal em (2,2) -> ocupa (2,2), (2,3), (2,4)
    int linhaH = 2, colunaH = 2;
    if(validaHorizontal(tabuleiro, linhaH, colunaH))
        colocaHorizontal(tabuleiro, linhaH, colunaH, navioH);
    else
        printf("Erro: nao consegui colocar o navio horizontal em (%d, %d)\n", linhaH, colunaH);
    
    // Navio vertical em (5,7) -> ocupa (5,7), (6,7), (7,7)
    int linhaV = 5, colunaV = 7;
    if(validaVertical(tabuleiro, linhaV, colunaV))
        colocaVertical(tabuleiro, linhaV, colunaV, navioV);
    else
        printf("Erro: nao consegui colocar o navio vertical em (%d, %d)\n", linhaV, colunaV);
    
    // ------------------------
    // Gerar as matrizes de habilidade
    // ------------------------
    int habCone[TAM_HAB][TAM_HAB];
    int habCruz[TAM_HAB][TAM_HAB];
    int habOcta[TAM_HAB][TAM_HAB];
    
    geraHabilidadeCone(habCone);
    geraHabilidadeCruz(habCruz);
    geraHabilidadeOctaedro(habOcta);
    
    // ------------------------
    // Definir os pontos de origem pra cada habilidade no tabuleiro
    // Lembrando: a origem tem que estar entre 2 e 7 (pra ficar dentro do tabuleiro com matriz 5x5)
    // ------------------------
    int origemConeLinha = 3, origemConeColuna = 3;
    int origemCruzLinha = 6, origemCruzColuna = 6;
    int origemOctaLinha = 7, origemOctaColuna = 3;
    
    // Sobrepoe a habilidade no tabuleiro
    overlayHabilidade(tabuleiro, habCone, origemConeLinha, origemConeColuna);
    overlayHabilidade(tabuleiro, habCruz, origemCruzLinha, origemCruzColuna);
    overlayHabilidade(tabuleiro, habOcta, origemOctaLinha, origemOctaColuna);
    
    // Exibe o tabuleiro com navios e areas de efeito marcadas com 5
    mostraTabuleiro(tabuleiro);
    
    return 0;
}
