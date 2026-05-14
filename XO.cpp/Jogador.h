#ifndef JOGADOR_H
#define JOGADOR_H

#include "Jogador.h"
#include "Tabuleiro.h"
#include <cstdlib>
#include <ctime>

class Jogador {
private:
    char marcador;
public:
    Jogador(char marcador);
    char getMarcador();
    void jogadaMaquina(Tabuleiro& tabuleiro);
};

#endif // JOGADOR_H