#include "Jogador.h"

Jogador::Jogador(char marcador) : marcador(marcador) {}

char Jogador::getMarcador() {
    return marcador;
}

void Jogador::jogadaMaquina(Tabuleiro& tabuleiro) {
    srand(time(0));
    int posicao;
    bool jogada_valida = false;

    while (!jogada_valida) {
        posicao = rand() % 9 + 1;
        jogada_valida = tabuleiro.colocarMarcador(posicao, marcador);
    }
}