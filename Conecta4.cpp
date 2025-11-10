#include <iostream> // importa libreria estandar de entrada y salida
#include <vector> // libreria de vectores para hacer los arreglos
using std::cout; using std::vector; // poner cout,cin y vector mas corto

// Constantes para definir las columnas y filas del arreglo
static const int ROWS = 6; // Filas
static const int COLS = 7;

void printBoard(const vector<vector<char>>& b) {
    cout << "\n   1 2 3 4 5 6 7\n"; // muestra los numeros de las columnas arriba del tablero

    //recorre cada fila del arreglo
    for ( int r = 0; r < ROWS; ++r) {
        cout << " | "; // imprime borde de la fila izquierda
        // recorre cada columna de la fila actual
        for (int c = 0; c < COLS; ++c) {
            cout << b[r][c] << '.'; // imprime el valor almacenado, pondra "." si esta vacio
        }
        cout << "|\n";  // Cierra la fila con un borde derecho y salto de línea
    }
    cout << "-----------------\n";  // Linea inferior del tablero
}

int main() { // bucle principal
    cout << "=== Conecta 4 — Modo consola (6x7) ===\n";  //imprime mensaje, titulo
    
    // Crea un tablero de 6 f x 7 c lleno de puntos 
    vector<vector<char>> board(ROWS, vector<char>(COLS, '.'));

    // llama la funcion para imprimir el tablero
    printBoard(board);

    return 0; // devuelve cero
}
