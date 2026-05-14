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
    bool isWindows;
public:
    Jogo();
    void iniciar();
    void trocarJogador();
    void mostrarMensagem(const std::string& mensagem);
};

#endif // JOGO_H