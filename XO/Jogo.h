#ifndef JOGO_H
#define JOGO_H

#include "Tabuleiro.h"
#include "Jogador.h"

#include <iostream>
#include <locale.h>

class Jogo {
private:
    Tabuleiro tabuleiro;
    Jogador jogador1;
    Jogador jogador2;
    int jogadorAtual;
public:
    Jogo();
    void iniciar();
    void trocarJogador();
};

#endif // JOGO_H