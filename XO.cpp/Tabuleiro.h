#ifndef TABULEIRO_H
#define TABULEIRO_H

class Tabuleiro {
private:
    char tabuleiro[3][3];
public:
    Tabuleiro();
    void inicializar();
    void desenhar();
    bool colocarMarcador(int posicao, char marcador);
    int verificarVencedor();
    void limparTela();
};

#endif // TABULEIRO_H