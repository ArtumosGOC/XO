#include <iostream>
#include <locale.h>
#include <cstdlib>
#include <ctime>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

char tabuleiro[3][3];
char marcador_atual;
int jogador_atual;

void limparTela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void inicializarTabuleiro() {
    char valor = '1';
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            tabuleiro[i][j] = valor++;
        }
    }
}

void desenharTabuleiro() {
    limparTela();
    std::cout << " " << tabuleiro[0][0] << " | " << tabuleiro[0][1] << " | " << tabuleiro[0][2] << "\n";
    std::cout << "---|---|---\n";
    std::cout << " " << tabuleiro[1][0] << " | " << tabuleiro[1][1] << " | " << tabuleiro[1][2] << "\n";
    std::cout << "---|---|---\n";
    std::cout << " " << tabuleiro[2][0] << " | " << tabuleiro[2][1] << " | " << tabuleiro[2][2] << "\n";
}

bool colocarMarcador(int posicao) {
    int linha = (posicao - 1) / 3;
    int coluna = (posicao - 1) % 3;

    if (tabuleiro[linha][coluna] != 'X' && tabuleiro[linha][coluna] != 'O') {
        tabuleiro[linha][coluna] = marcador_atual;
        return true;
    }
    else {
        return false;
    }
}

int vencedor() {
    // Linhas
    for (int i = 0; i < 3; i++) {
        if (tabuleiro[i][0] == tabuleiro[i][1] && tabuleiro[i][1] == tabuleiro[i][2]) {
            return jogador_atual;
        }
    }
    // Colunas
    for (int i = 0; i < 3; i++) {
        if (tabuleiro[0][i] == tabuleiro[1][i] && tabuleiro[1][i] == tabuleiro[2][i]) {
            return jogador_atual;
        }
    }
    // Diagonais
    if (tabuleiro[0][0] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][2]) {
        return jogador_atual;
    }
    if (tabuleiro[0][2] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][0]) {
        return jogador_atual;
    }
    return 0;
}

void trocarJogadorEMarcador() {
    if (marcador_atual == 'X') {
        marcador_atual = 'O';
    }
    else {
        marcador_atual = 'X';
    }

    if (jogador_atual == 1) {
        jogador_atual = 2;
    }
    else {
        jogador_atual = 1;
    }
}

void jogadaMaquina() {
    srand(time(0));
    int posicao;
    bool jogada_valida = false;

    while (!jogada_valida) {
        posicao = rand() % 9 + 1;
        jogada_valida = colocarMarcador(posicao);
    }
}

void jogo() {
    char jogar_novamente;
    do {
        inicializarTabuleiro();
        std::cout << "Jogador um, escolha seu marcador (X ou O): ";
        char marcador_j1;
        std::cin >> marcador_j1;

        jogador_atual = 1;
        marcador_atual = marcador_j1;

        desenharTabuleiro();

        int jogador_vencedor = 0;

        for (int i = 0; i < 9; i++) {
            if (jogador_atual == 1) {
                std::cout << "É a vez do jogador " << jogador_atual << ". Escolha uma posição: ";
                int posicao;
                std::cin >> posicao;

                if (posicao < 1 || posicao > 9) {
                    std::cout << "Posição inválida! Tente outra posição!\n";
                    i--;
                    continue;
                }

                if (!colocarMarcador(posicao)) {
                    std::cout << "Posição ocupada! Tente outra posição!\n";
                    i--;
                    continue;
                }
            }
            else {
                jogadaMaquina();
            }

            desenharTabuleiro();

            jogador_vencedor = vencedor();

            if (jogador_vencedor == 1) {
                std::cout << "Jogador um venceu! Parabéns!\n";
                break;
            }
            if (jogador_vencedor == 2) {
                std::cout << "A máquina venceu! Parabéns!\n";
                break;
            }

            trocarJogadorEMarcador();
        }

        if (jogador_vencedor == 0) {
            std::cout << "O jogo empatou!\n";
        }

        std::cout << "Deseja jogar novamente? (s/n): ";
        std::cin >> jogar_novamente;

    } while (jogar_novamente == 's' || jogar_novamente == 'S');
}

int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8");
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    jogo();
    return 0;
}