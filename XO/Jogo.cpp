#include "Jogo.h"


Jogo::Jogo() : jogador1('X'), jogador2('O'), jogadorAtual(1) {}

void Jogo::iniciar() {
    #ifdef _WIN32
	setlocale(LC_ALL, "Portuguese");
    #else
	setlocale(LC_ALL, "pt_BR.UTF-8");
    #endif
    char jogar_novamente;
    do {
        tabuleiro.inicializar();
        tabuleiro.desenhar();

        int jogador_vencedor = 0;

        for (int i = 0; i < 9; i++) {
            if (jogadorAtual == 1) {
                std::cout << "É a vez do jogador " << jogadorAtual << ". Escolha uma posição: ";
                int posicao;
                std::cin >> posicao;

                if (posicao < 1 || posicao > 9) {
                    std::cout << "Posição inválida! Tente outra posição!\n";
                    i--;
                    continue;
                }

                if (!tabuleiro.colocarMarcador(posicao, jogador1.getMarcador())) {
                    std::cout << "Posição ocupada! Tente outra posição!\n";
                    i--;
                    continue;
                }
            }
            else {
                jogador2.jogadaMaquina(tabuleiro);
            }

            tabuleiro.desenhar();

            jogador_vencedor = tabuleiro.verificarVencedor();

            if (jogador_vencedor == 1) {
                std::cout << "Jogador " << jogadorAtual << " venceu! Parabéns!\n";
                break;
            }

            trocarJogador();
        }

        if (jogador_vencedor == 0) {
            std::cout << "O jogo empatou!\n";
        }

        std::cout << "Deseja jogar novamente? (s/n): ";
        std::cin >> jogar_novamente;

    } while (jogar_novamente == 's' || jogar_novamente == 'S');
}

void Jogo::trocarJogador() {
    jogadorAtual = (jogadorAtual == 1) ? 2 : 1;
}