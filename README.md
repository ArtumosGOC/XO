# Jogo da Velha

Duas implementações do clássico jogo da velha para terminal, uma em **C** e outra em **C++**.

---

## Versão C

Implementação procedural em arquivo único, focada em controle direto do terminal e lógica de jogo compacta.

### Compilação

```bash
gcc Linux-XO.c -o velha && ./velha
```

### Estrutura

Tudo está em um único arquivo `velha.c`. As responsabilidades são divididas por funções:

**Tipos e variáveis globais**
- `p` — struct para posição `{x, y}` do cursor no tabuleiro
- `itens` — struct para índices `{i, j}` usados pelo bot
- `pos` / `lpos` — posição atual e anterior do cursor
- `matriz_char[3][3]` — estado do tabuleiro (`$` = vazio, `#` = cursor, `X`/`O` = jogadas)
- `wins[2]` — placar de vitórias

**Funções**

| Função | Responsabilidade |
|---|---|
| `getch()` | Lê um caractere do terminal sem aguardar Enter, capturando teclas de seta via sequência ESC |
| `alguemGanhou()` | Verifica linhas, colunas e diagonais em busca de vitória; também detecta empate ao contar células preenchidas |
| `desenhaTela()` | Limpa o terminal e redesenha o tabuleiro com placar e posição do cursor |
| `resetTabuleiro()` | Reinicia o tabuleiro para `$` após cada partida |
| `verificaPos()` | Encontra a primeira célula vazia após uma jogada para reposicionar o cursor |
| `encontraJogada(simbolo)` | Busca uma jogada vencedora ou de bloqueio para o símbolo dado (linha, coluna ou diagonal com 2 peças e 1 vaga) |
| `verificaBot()` | Decide a jogada do bot com prioridade: ganhar > bloquear > centro > aleatório (Fisher-Yates shuffle) |
| `debounce(estado)` | Evita repetição da mesma tecla consecutivamente, exigindo uma tecla diferente entre pressões iguais |

### Controles

| Tecla | Ação |
|---|---|
| Setas | Move o cursor |
| Enter | Confirma a jogada |

### Modos de jogo

- **Sozinho (S)** — jogador vs bot
- **Com alguém (N)** — dois jogadores no mesmo teclado

---

## Versão C++

Implementação orientada a objetos dividida em três classes, cada uma com responsabilidade bem definida.

### Compilação

```bash
g++ Tabuleiro.cpp Jogador.cpp Jogo.cpp main.cpp -o velha && ./velha
```

### Estrutura

**`Tabuleiro`** — `Tabuleiro.h` / `Tabuleiro.cpp`

Responsável pelo estado e visualização do tabuleiro.

| Membro | Responsabilidade |
|---|---|
| `tabuleiro[3][3]` | Matriz interna com o estado de cada célula |
| `inicializar()` | Reseta todas as células para vazio |
| `desenhar()` | Exibe o tabuleiro formatado no terminal |
| `colocarMarcador(posicao, marcador)` | Valida e insere uma peça na posição escolhida (1–9) |
| `verificarVencedor()` | Retorna `1` (X ganhou), `2` (O ganhou), `0` (empate) ou `-1` (jogo em andamento) |
| `limparTela()` | Limpa o terminal de forma compatível com Windows e Linux |

**`Jogador`** — `Jogador.h` / `Jogador.cpp`

Representa um jogador, humano ou máquina.

| Membro | Responsabilidade |
|---|---|
| `marcador` | Símbolo do jogador (`X` ou `O`) |
| `getMarcador()` | Retorna o símbolo do jogador |
| `jogadaMaquina(tabuleiro)` | Escolhe uma posição aleatória válida para o bot |

**`Jogo`** — `Jogo.h` / `Jogo.cpp`

Orquestra o fluxo completo da partida.

| Membro | Responsabilidade |
|---|---|
| `tabuleiro` | Instância do tabuleiro da partida |
| `jogador1` / `jogador2` | Instâncias dos dois jogadores |
| `jogadorAtual` | Controla de quem é o turno |
| `iniciar()` | Loop principal do jogo: alterna turnos, verifica vitória e reinicia |
| `trocarJogador()` | Alterna entre jogador 1 e 2 |
| `mostrarMensagem(mensagem)` | Exibe mensagens de vitória, empate ou erro |

---

## Diferenças entre as versões

| | C | C++ |
|---|---|---|
| Paradigma | Procedural | Orientado a objetos |
| Arquivos | 1 | 4+ |
| Navegação | Setas do teclado | Número da posição (1–9) |
| Bot | Bloqueia e tenta ganhar | Aleatório |
| Placar | Sim | Não |
| Detecção de empate | Sim | Sim |
