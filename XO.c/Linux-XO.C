#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>

struct
{
	int x;
	int y;
} typedef p;

typedef struct
{
	int i;
	int j;
} itens;

p pos = {0, 0};
p lpos = {1, 1};

unsigned char cursor = '#';
bool player = 0b0;
bool bot;

static uint16_t wins[2];

static char matriz_char[3][3] = {
	{'$', '$', '$'},
	{'$', '$', '$'},
	{'$', '$', '$'}};

void delay(int32_t ms)
{
	usleep(ms*1000);
}

int getch(void)
{
	struct termios oldattr, newattr;
	int ch;
	tcgetattr(STDIN_FILENO, &oldattr);
	newattr = oldattr;
	newattr.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
	ch = getchar();
	if (ch == 0x1B)
	{
		getchar();
		ch = getchar();
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
	return ch;
}

bool alguemGanhou()
{
	for (int i = 0; i < 3; i++)
	{
		if (matriz_char[i][0] != '$' && matriz_char[i][0] == matriz_char[i][1] && matriz_char[i][1] == matriz_char[i][2])
		{
			if (matriz_char[i][0] == 'X')
				wins[0]++;
			else
				wins[1]++;
			return true;
		}
	}
	for (int i = 0; i < 3; i++)
	{
		if (matriz_char[0][i] != '$' && matriz_char[0][i] == matriz_char[1][i] && matriz_char[1][i] == matriz_char[2][i])
		{
			if (matriz_char[0][i] == 'X')
				wins[0]++;
			else
				wins[1]++;
			return true;
		}
	}
	if (matriz_char[1][1] != '$')
	{
		if (matriz_char[0][0] == matriz_char[1][1] && matriz_char[1][1] == matriz_char[2][2])
		{
			if (matriz_char[0][0] == 'X')
				wins[0]++;
			else
				wins[1]++;
			return true;
		}
		if (matriz_char[0][2] == matriz_char[1][1] && matriz_char[1][1] == matriz_char[2][0])
		{
			if (matriz_char[0][2] == 'X')
				wins[0]++;
			else
				wins[1]++;
			return true;
		}
	}

	int contador = 1;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (matriz_char[i][j] != '$')
				contador++;
			if (contador == 8)
			{
				player = !player;
				return true;
			}
		}
	}
	return false;
}

void desenhaTela()
{
	system("clear");
	printf(" -----------\n");
	printf("| %c | %c | %c |\n", matriz_char[0][0], matriz_char[0][1], matriz_char[0][2]);
	printf("| --|---|-- |\n");
	printf("| %c | %c | %c |\n", matriz_char[1][0], matriz_char[1][1], matriz_char[1][2]);
	printf("| --|---|-- |\n");
	printf("| %c | %c | %c |\n", matriz_char[2][0], matriz_char[2][1], matriz_char[2][2]);
	printf(" -----------\n");
	printf("\nPlayer:%d\n---------------\nVitorias:\nP1:%d\nP2:%d\n---------------\n{x:%d,y:%d}\n", player, wins[0], wins[1], pos.x, pos.y);
}

void resetTabuleiro()
{
	system("clear");
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			matriz_char[i][j] = '$';
}

itens verificaPos()
{
	itens n = {0, 0};
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (matriz_char[i][j] == '$')
			{
				n.i = i;
				n.j = j;
				return n;
			}
	return n;
}

itens encontraJogada(char simbolo)
{
	itens n = {-1, -1};

	for (int i = 0; i < 3; i++)
	{
		int count = 0, livre_j = -1;
		for (int j = 0; j < 3; j++)
		{
			if (matriz_char[i][j] == simbolo)
				count++;
			else if (matriz_char[i][j] == '$')
				livre_j = j;
		}
		if (count == 2 && livre_j != -1)
		{
			n.i = i;
			n.j = livre_j;
			return n;
		}
	}

	for (int j = 0; j < 3; j++)
	{
		int count = 0, livre_i = -1;
		for (int i = 0; i < 3; i++)
		{
			if (matriz_char[i][j] == simbolo)
				count++;
			else if (matriz_char[i][j] == '$')
				livre_i = i;
		}
		if (count == 2 && livre_i != -1)
		{
			n.i = livre_i;
			n.j = j;
			return n;
		}
	}

	{
		int count = 0, livre = -1;
		for (int i = 0; i < 3; i++)
		{
			if (matriz_char[i][i] == simbolo)
				count++;
			else if (matriz_char[i][i] == '$')
				livre = i;
		}
		if (count == 2 && livre != -1)
		{
			n.i = livre;
			n.j = livre;
			return n;
		}
	}

	{
		int count = 0, livre = -1;
		for (int i = 0; i < 3; i++)
		{
			if (matriz_char[i][2 - i] == simbolo)
				count++;
			else if (matriz_char[i][2 - i] == '$')
				livre = i;
		}
		if (count == 2 && livre != -1)
		{
			n.i = livre;
			n.j = 2 - livre;
			return n;
		}
	}

	return n;
}

itens verificaBot()
{
	itens n;

	n = encontraJogada('O');
	if (n.i != -1)
		return n;

	n = encontraJogada('X');
	if (n.i != -1)
		return n;

	if (matriz_char[1][1] == '$')
	{
		n.i = 1;
		n.j = 1;
		return n;
	}

	int ordem[9][2];
	int k = 0;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			ordem[k][0] = i, ordem[k++][1] = j;

	for (int i = 8; i > 0; i--)
	{
		int j = rand() % (i + 1);
		int ti = ordem[i][0], tj = ordem[i][1];
		ordem[i][0] = ordem[j][0];
		ordem[i][1] = ordem[j][1];
		ordem[j][0] = ti;
		ordem[j][1] = tj;
	}

	for (int k = 0; k < 9; k++)
	{
		if (matriz_char[ordem[k][0]][ordem[k][1]] == '$')
		{
			n.i = ordem[k][0];
			n.j = ordem[k][1];
			return n;
		}
	}

	n.i = 0;
	n.j = 0;
	return n;
}

int main()
{
	srand(42);

	int ch = 0;
	while (ch != 0x73 && ch != 0x6E)
	{
		printf("Vai jogar com alguem? (S/N)");
		ch = getch();
		//printf("%X", ch);
		bot = (0x73 == ch) ? 0b0 : 0b1;
		system("clear");
	}

	itens n;

	matriz_char[pos.y][pos.x] = cursor;
	desenhaTela();

	while (1)
	{
		ch = getch();
		delay(30);
		//printf("%X", ch);

		if (ch == 0xA)
		{
			if (matriz_char[pos.y][pos.x] == cursor)
			{
				matriz_char[pos.y][pos.x] = (player) ? 'O' : 'X';
				player = !player;

				if (alguemGanhou())
				{
					resetTabuleiro();
				}
				else if (player && bot)
				{
					n = verificaBot();
					matriz_char[n.i][n.j] = 'O';
					player = !player;

					if (alguemGanhou())
					{
						resetTabuleiro();
					}
				}

				n = verificaPos();
				pos.y = n.i;
				pos.x = n.j;
			}
		}
		else
		{
			lpos.y = pos.y;
			lpos.x = pos.x;

			if (ch == 0x44)
				pos.x--;
			if (ch == 0x43)
				pos.x++;
			if (ch == 0x41)
				pos.y--;
			if (ch == 0x42)
				pos.y++;

			pos.y = (pos.y > 2) ? 0 : (pos.y < 0) ? 2
												  : pos.y;
			pos.x = (pos.x > 2) ? 0 : (pos.x < 0) ? 2
												  : pos.x;

			if (matriz_char[pos.y][pos.x] == 'X' || matriz_char[pos.y][pos.x] == 'O')
			{
				pos.y = lpos.y;
				pos.x = lpos.x;
			}
			else if (matriz_char[lpos.y][lpos.x] == cursor)
			{
				matriz_char[lpos.y][lpos.x] = '$';
			}
		}

		if (matriz_char[pos.y][pos.x] == '$')
		{
			matriz_char[pos.y][pos.x] = cursor;
		}

		desenhaTela();
	}

	return 0;
}
