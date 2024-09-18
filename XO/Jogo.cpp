#include "Jogo.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif
#include <string>

namespace {
	std::string string(int n) {
		return std::to_string(n);
	}
}

Jogo::Jogo() : jogador1('0'), jogador2('0'), jogadorAtual(1) {

    if (!setlocale(LC_ALL, "pt_BR"))
        isWindows = false;
	else
		isWindows = true;

	mostrarMensagem("Bem-vindo ao Jogo da Velha!\n");
    mostrarMensagem("Qual jogador você deseja ser? (X, O): ");
	char marcador;
	std::cin >> marcador;
	if (marcador != 'X' && marcador != 'O' && marcador != 'x' && marcador != 'o') {
		mostrarMensagem("Marcador inválido! Escolha X ou O!\n");
		return;
	}
	if (marcador == 'x') marcador = 'X';
	else if (marcador == 'o') marcador = 'O';
    jogador1 = Jogador(marcador);
	jogador2 = Jogador((marcador == 'X') ? 'O' : 'X');


}

void Jogo::iniciar() {
    char jogar_novamente;
    do {
        tabuleiro.inicializar();
        tabuleiro.desenhar();

        int jogador_vencedor = 0;

        for (int i = 0; i < 9; i++) {
            if (jogadorAtual == 1) {
                mostrarMensagem("É a vez do jogador " + string(jogadorAtual) + ". Escolha uma posição: ");
                int posicao;
                std::cin >> posicao;

                if (posicao < 1 || posicao > 9) {
                    mostrarMensagem("Posição inválida! Tente outra posição!\n");
                    i--;
                    continue;
                }

                if (!tabuleiro.colocarMarcador(posicao, jogador1.getMarcador())) {
                    mostrarMensagem("Posição ocupada! Tente outra posição!\n");
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
                mostrarMensagem("Jogador " + string(jogadorAtual) + " venceu! Parabéns!\n");
                break;
            }

            trocarJogador();
        }

        if (jogador_vencedor == 0) {
            mostrarMensagem("O jogo empatou!\n");
        }

        mostrarMensagem("Deseja jogar novamente? (s/n): ");
        std::cin >> jogar_novamente;

    } while (jogar_novamente == 's' || jogar_novamente == 'S');
}

void Jogo::trocarJogador() {
    jogadorAtual = (jogadorAtual == 1) ? 2 : 1;
}

void Jogo::mostrarMensagem(const std::string& mensagem) {
    if (isWindows) {
        std::cout << mensagem;
    }
    else {
        std::string mensagemSemAcentos = mensagem;
        for (char& c : mensagemSemAcentos) {
            switch (c) {
            case 'á': case 'à': case 'ã': case 'â': c = 'a'; break;
            case 'é': case 'ê': c = 'e'; break;
            case 'í': c = 'i'; break;
            case 'ó': case 'ô': case 'õ': c = 'o'; break;
            case 'ú': c = 'u'; break;
            case 'ç': c = 'c'; break;
            case 'Á': case 'À': case 'Ã': case 'Â': c = 'A'; break;
            case 'É': case 'Ê': c = 'E'; break;
            case 'Í': c = 'I'; break;
            case 'Ó': case 'Ô': case 'Õ': c = 'O'; break;
            case 'Ú': c = 'U'; break;
            case 'Ç': c = 'C'; break;
            }
        }
        std::cout << mensagemSemAcentos;
    }
}