#include <stdio.h>

#define N 10         // tamanho do tabuleiro
#define NAVIO 3      // valor que representa navio
#define CONE 6       // valor que representa habilidade cone
#define CRUZ 7       // valor que representa habilidade cruz
#define OCTAEDRO 8   // valor que representa habilidade octaedro

// Inicializa o tabuleiro com 0 (água)
void inicializarTabuleiro(int tab[N][N]) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            tab[i][j] = 0;
}

// Imprime o tabuleiro
void imprimirTabuleiro(int tab[N][N]) {
    printf("\n=== TABULEIRO ===\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", tab[i][j]);
        }
        printf("\n");
    }
}

// Posicionar navio horizontal
void posicionarNavioHorizontal(int tab[N][N], int linha, int coluna, int tamanho) {
    if (coluna + tamanho <= N) {
        int livre = 1;
        for (int j = 0; j < tamanho; j++)
            if (tab[linha][coluna + j] != 0) livre = 0;
        if (livre)
            for (int j = 0; j < tamanho; j++)
                tab[linha][coluna + j] = NAVIO;
    }
}

// Posicionar navio vertical
void posicionarNavioVertical(int tab[N][N], int linha, int coluna, int tamanho) {
    if (linha + tamanho <= N) {
        int livre = 1;
        for (int i = 0; i < tamanho; i++)
            if (tab[linha + i][coluna] != 0) livre = 0;
        if (livre)
            for (int i = 0; i < tamanho; i++)
                tab[linha + i][coluna] = NAVIO;
    }
}

// Posicionar navio diagonal ↘
void posicionarNavioDiagonalDesc(int tab[N][N], int linha, int coluna, int tamanho) {
    int livre = 1;
    for (int k = 0; k < tamanho; k++) {
        if (linha + k >= N || coluna + k >= N || tab[linha + k][coluna + k] != 0) livre = 0;
    }
    if (livre)
        for (int k = 0; k < tamanho; k++)
            tab[linha + k][coluna + k] = NAVIO;
}

// Posicionar navio diagonal ↙
void posicionarNavioDiagonalAsc(int tab[N][N], int linha, int coluna, int tamanho) {
    int livre = 1;
    for (int k = 0; k < tamanho; k++) {
        if (linha + k >= N || coluna - k < 0 || tab[linha + k][coluna - k] != 0) livre = 0;
    }
    if (livre)
        for (int k = 0; k < tamanho; k++)
            tab[linha + k][coluna - k] = NAVIO;
}

// Aplicar habilidade (5x5) no tabuleiro, não sobrescreve navios
void aplicarHabilidade(int tab[N][N], int habilidade[5][5], int origemI, int origemJ, int valor) {
    int centro = 2; // centro de matriz 5x5
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (habilidade[i][j] == 1) {
                int x = origemI + (i - centro);
                int y = origemJ + (j - centro);
                if (x >= 0 && x < N && y >= 0 && y < N) {
                    if (tab[x][y] == 0) // não sobrescreve navio
                        tab[x][y] = valor;
                }
            }
        }
    }
}

// Criar matriz cone (5x5)
void criarCone(int mat[5][5]) {
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            mat[i][j] = 0;
    mat[0][2] = 1;
    for (int j = 1; j <= 3; j++) mat[1][j] = 1;
    for (int j = 0; j < 5; j++) mat[2][j] = 1;
}

// Criar matriz cruz (5x5)
void criarCruz(int mat[5][5]) {
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            mat[i][j] = (i == 2 || j == 2) ? 1 : 0;
}

// Criar matriz octaedro (5x5)
void criarOctaedro(int mat[5][5]) {
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            mat[i][j] = 0;
    mat[0][2] = 1;
    mat[1][1] = mat[1][2] = mat[1][3] = 1;
    for (int j = 0; j < 5; j++) mat[2][j] = 1;
    mat[3][1] = mat[3][2] = mat[3][3] = 1;
    mat[4][2] = 1;
}

int main() {
    int tabuleiro[N][N];
    inicializarTabuleiro(tabuleiro);

    // --- Posicionar navios ---
    posicionarNavioHorizontal(tabuleiro, 2, 1, 3); // horizontal
    posicionarNavioVertical(tabuleiro, 5, 7, 3);   // vertical
    posicionarNavioDiagonalDesc(tabuleiro, 3, 3, 3); // diagonal ↘
    posicionarNavioDiagonalAsc(tabuleiro, 0, 9, 3);  // diagonal ↙

    // --- Criar habilidades ---
    int cone[5][5], cruz[5][5], octaedro[5][5];
    criarCone(cone);
    criarCruz(cruz);
    criarOctaedro(octaedro);

    // --- Aplicar habilidades ---
    aplicarHabilidade(tabuleiro, cone, 1, 1, CONE);
    aplicarHabilidade(tabuleiro, cruz, 5, 5, CRUZ);
    aplicarHabilidade(tabuleiro, octaedro, 8, 2, OCTAEDRO);

    // --- Exibir tabuleiro final ---
    imprimirTabuleiro(tabuleiro);

    return 0;
}
