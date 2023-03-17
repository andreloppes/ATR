#include <iostream>
#include <stack>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
// Matriz representnado o labirinto
char **maze;
// Numero de linhas e colunas do labirinto
int num_rows;
int num_cols;

// Posição a ser explorada
struct pos_t {
  int i;
  int j;
};

// Estrutura de dados contendo as próximas
// posicões a serem exploradas no labirinto
std::stack<pos_t> valid_positions;

// Inserir elemento:

pos_t pos;

/*pos.i = 1;
pos.j = 3;
valid_positions.push(pos);*/

// Retornar o numero de elementos: valid_positions.size();
// Retornar o primeiro elemento fo vetor: valid_positions.pop();
// Remover o elemento no topo: valid_positions.front();

pos_t load_maze(const char *file_name) {
  pos_t initial_pos;
  int num[2];
  FILE *pFile;
  // Abre o arquivo para leitura (fopen)
  pFile = fopen("maze.txt", "rw");
  if (pFile == NULL) // Se não conseguiu criar
  {
    cout << "Erro na leitura do arquivo\n" << endl;
    abort();
  }
  // Le o numero de linhas e colunas (fscanf)
  for (int i = 0; i < 1; i++) {
    fscanf(pFile, "%d", &num[i]);
  }
  // e salva em num_rows e num_cols
  num_rows = num[0];
  num_cols = num[1];

  // Aloca a matriz maze (malloc)
  maze = (char **)malloc(num_rows * sizeof(char *));
  for (int i = 0; i < num_rows; ++i) {
    maze[i] = (char *)malloc(num_cols * sizeof(char));
  }
  // alocação de um vetor de tamanho 4 (4 linhas)

  // Aloca cada linha da matriz

  for (int i = 0; i < num_rows; ++i) {
    for (int j = 0; j < num_cols; ++j) {
      char n;
      // Le o valor da linha i+1,j do arquivo e salva na posição maze[i][j]
      fscanf(pFile, "%c", &n);
      maze[i + 1][j] = n;
      // Se o valor for 'i' salvar o valor em initial_pos
      if (n == 'i') {
        initial_pos.i = i;
        initial_pos.j = j;
      }
    }
  }
  return initial_pos;
}

void print_maze() {
  for (int i = 0; i < num_rows; ++i) {
    for (int j = 0; j < num_cols; ++j) {
      printf("%c", maze[i][j]);
    }
    printf("\n");
  }
}

void walk(pos_t pos) {
  // Marcar a posição atual com o símbolo '.'
  maze[pos.i][pos.j] = '.';
  /* Dado a posição atual, verifica quais sao as próximas posições válidas
          Checar se as posições abaixo são validas
 (i>0, i<num_rows, j>0, j<num_cols)
e se são posições ainda não visitadas (ou seja, caracter 'x') e
     inserir cada uma delas no vetor valid_positions
           - pos.i, pos.j+1
           - pos.i, pos.j-1
           - pos.i+1, pos.j
           - pos.i-1, pos.j
           Caso alguma das posiçÕes validas seja igual a 's', terminar o
     programa
   */
  if(pos.i > 0 && pos.i < num_rows && pos.j > 0 && pos.j < num_cols){
    // LEFT
    if(maze[pos.i][pos.j+1] == 'x'){
      pos_t valid_pos;
      valid_pos.i = pos.i;
      valid_pos.j = pos.j+1;
      valid_positions.push(valid_pos);
    }
    if(maze[pos.i][pos.j+1] == 's'){
      return;
    }

    // RIGHT
    if(maze[pos.i][pos.j-1]){
    pos_t valid_pos;
      valid_pos.i = pos.i;
      valid_pos.j = pos.j-1;
      valid_positions.push(valid_pos);
    }
    if(maze[pos.i][pos.j-1] == 's'){
      return;
    }

    // UP
    if(maze[pos.i+1][pos.j]){
    pos_t valid_pos;
      valid_pos.i = pos.i+1;
      valid_pos.j = pos.j;
      valid_positions.push(valid_pos);
    }
    if(maze[pos.i+1][pos.j] == 's'){
      return;
    }

    // DOWN
    if(maze[pos.i-1][pos.j]){
    pos_t valid_pos;
      valid_pos.i = pos.i-1;
      valid_pos.j = pos.j;
      valid_positions.push(valid_pos);
    }
    if(maze[pos.i-1][pos.j] == 's'){
      return;
    }
  }

  // Imprime o labirinto
  print_maze();

      // Verifica se o vetor nao esta vazio.
      // Caso não esteja, pegar o primeiro valor de
      // valid_positions, remove-lo e chamar a funçao walk com esse valor
  if(valid_positions.size() > 0){
      pos_t next_position = valid_positions.top();
      valid_positions.pop();

     walk(next_position);
  }
}

int main(int argc, char *argv[]) {
  // carregar o labirinto com o nome do arquivo recebido como argumento (argv[])
  pos_t initial_pos = load_maze("maze.txt");
  walk(initial_pos);
}
