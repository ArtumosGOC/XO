## Como Jogar

1. Clone o repositório para o seu ambiente local.
2. Abra o projeto no Visual Studio.
3. Compile e execute o projeto.
4. Siga as instruções no terminal para jogar.

## Funcionalidades

- Dois jogadores podem jogar alternadamente.
- O jogo verifica automaticamente se há um vencedor ou empate.
- O terminal é limpo a cada jogada para uma melhor visualização.
- O jogador pode escolher jogar novamente após o término do jogo.

## Estrutura do Código

- `Tabuleiro.h`: Declaração da classe `Tabuleiro`.
- `Tabuleiro.cpp`: Implementação da classe `Tabuleiro`.
- `Jogador.h`: Declaração da classe `Jogador`.
- `Jogador.cpp`: Implementação da classe `Jogador`.
- `Jogo.h`: Declaração da classe `Jogo`.
- `Jogo.cpp`: Implementação da classe `Jogo`.
- `XO.cpp`: Função principal que inicia o jogo.

## Como Compilar no Linux


1. Abra um terminal e clone o diretório:
   ```sh
   git clone https://github.com/ArtumosGOC/XO.git
   ```
2. Navegue até o diretório do projeto:
   ```sh
   cd ~/XO/XO/
   ```
3. Compile os arquivos:
   ```sh
   g++ -o jogo_da_velha Tabuleiro.cpp Jogador.cpp Jogo.cpp XO.cpp
   ```
   ou
    ```sh
   g++ *.cpp
   ```
4. Por fim Execute!
   ```sh
   ./jogo_da_velha
   ```

## Como Compilar no Windows

1. Abra o navegador e baixe o Visual Studio 2022

2. No Visual Studio Installer, instale qualquer versão do Visual Studio 2022

3. Selecione o pacote `Desenvolvimento para desktop com C++` e instale

4. Abra e clique em `Clonar um repositório`, em `Local do repositório` cole `https://github.com/ArtumosGOC/XO.git`, Por fim clique em clonar e quando o projeto abrir aperter `CTRL+F5`.
