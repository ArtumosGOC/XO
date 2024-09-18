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
    mostrarMensagem("Qual jogador voc� deseja ser? (X, O): ");
	char marcador;
	std::cin >> marcador;
	if (marcador != 'X' && marcador != 'O' && marcador != 'x' && marcador != 'o') {
		mostrarMensagem("Marcador inv�lido! Escolha X ou O!\n");
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
                mostrarMensagem("� a vez do jogador " + string(jogadorAtual) + ". Escolha uma posi��o: ");
                int posicao;
                std::cin >> posicao;

                if (posicao < 1 || posicao > 9) {
                    mostrarMensagem("Posi��o inv�lida! Tente outra posi��o!\n");
                    i--;
                    continue;
                }

                if (!tabuleiro.colocarMarcador(posicao, jogador1.getMarcador())) {
                    mostrarMensagem("Posi��o ocupada! Tente outra posi��o!\n");
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
                mostrarMensagem("Jogador " + string(jogadorAtual) + " venceu! Parab�ns!\n");
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
            case '�': case '�': case '�': case '�': c = 'a'; break;
            case '�': case '�': c = 'e'; break;
            case '�': c = 'i'; break;
            case '�': case '�': case '�': c = 'o'; break;
            case '�': c = 'u'; break;
            case '�': c = 'c'; break;
            case '�': case '�': case '�': case '�': c = 'A'; break;
            case '�': case '�': c = 'E'; break;
            case '�': c = 'I'; break;
            case '�': case '�': case '�': c = 'O'; break;
            case '�': c = 'U'; break;
            case '�': c = 'C'; break;
            }
        }
        std::cout << mensagemSemAcentos;
    }
}