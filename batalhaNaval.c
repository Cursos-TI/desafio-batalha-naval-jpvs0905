#include <stdio.h>

int main() {
    // ---------- Declaração do tabuleiro ----------
    int tabuleiro[10][10]; // tabuleiro fixo 10x10

    // ---------- Inicializa o tabuleiro com água (0) ----------
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            tabuleiro[i][j] = 0; // 0 significa água
        }
    }

    // ---------- Definição das coordenadas iniciais ----------
    // Navio horizontal começa na linha 2, coluna 4
    int linhaH = 2;
    int colunaH = 4;

    // Navio vertical começa na linha 5, coluna 7
    int linhaV = 5;
    int colunaV = 7;

    // ---------- Posicionamento do navio horizontal ----------
    // navio de tamanho fixo = 3
    if (colunaH + 3 <= 10) { 
        for (int j = 0; j < 3; j++) {
            tabuleiro[linhaH][colunaH + j] = 3; // 3 significa navio
        }
    }

    // ---------- Posicionamento do navio vertical ----------
    if (linhaV + 3 <= 10) {
        for (int i = 0; i < 3; i++) {
            if (tabuleiro[linhaV + i][colunaV] == 0) { 
                tabuleiro[linhaV + i][colunaV] = 3;
            }
        }
    }

    // ---------- Exibição do tabuleiro ----------
    printf("=== TABULEIRO DE BATALHA NAVAL ===\n\n");
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}
