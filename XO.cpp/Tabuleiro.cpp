#include "Tabuleiro.h"
#include <iostream>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

Tabuleiro::Tabuleiro() {
    inicializar();
}

void Tabuleiro::inicializar() {
    char valor = '1';
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            tabuleiro[i][j] = valor++;
        }
    }
}

void Tabuleiro::desenhar() {
    limparTela();
    std::cout << " " << tabuleiro[0][0] << " | " << tabuleiro[0][1] << " | " << tabuleiro[0][2] << "\n";
    std::cout << "---|---|---\n";
    std::cout << " " << tabuleiro[1][0] << " | " << tabuleiro[1][1] << " | " << tabuleiro[1][2] << "\n";
    std::cout << "---|---|---\n";
    std::cout << " " << tabuleiro[2][0] << " | " << tabuleiro[2][1] << " | " << tabuleiro[2][2] << "\n";
}

bool Tabuleiro::colocarMarcador(int posicao, char marcador) {
    int linha = (posicao - 1) / 3;
    int coluna = (posicao - 1) % 3;

    if (tabuleiro[linha][coluna] != 'X' && tabuleiro[linha][coluna] != 'O') {
        tabuleiro[linha][coluna] = marcador;
        return true;
    }
    else {
        return false;
    }
}

int Tabuleiro::verificarVencedor() {
    // Linhas
    for (int i = 0; i < 3; i++) {
        if (tabuleiro[i][0] == tabuleiro[i][1] && tabuleiro[i][1] == tabuleiro[i][2]) {
            return 1;
        }
    }
    // Colunas
    for (int i = 0; i < 3; i++) {
        if (tabuleiro[0][i] == tabuleiro[1][i] && tabuleiro[1][i] == tabuleiro[2][i]) {
            return 1;
        }
    }
    // Diagonais
    if (tabuleiro[0][0] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][2]) {
        return 1;
    }
    if (tabuleiro[0][2] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][0]) {
        return 1;
    }
    return 0;
}

void Tabuleiro::limparTela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}