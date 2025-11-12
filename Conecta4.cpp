#include <iostream> // importa libreria estandar de entrada y salida
#include <vector> // libreria de vectores para hacer los arreglos
#include <string> // libreria para poder usar string
using std::cout; using std::cin; using std::vector; using std::string;  // poner cout,cin y vector mas corto

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

// verifica colimna llena
bool isColumnFull(const vector<vector<char>>& b, int c) {
    return b[0][c] != '.'; // si no esta vacio, esta lleno
}

// Coloca la ficha
int dropPiece(vector<vector<char>>& b, int c, char sym) {
    if (c < 0 || c >= COLS || isColumnFull(b, c)) return -1; // no valido o lleno
    for (int r = ROWS - 1; r >= 0; --r) { // desde abajo a arriba
        if (b[r][c] == '.') { // encuentra un lugar vacio
            b[r][c] = sym; // colocar ficha x o o
            return r; // devuelve la coordenada donde cayo la ficha
        }
    }
    return -1; // error si no encuentra espacio
}


int askColumn(const string & playerName){
    while (true) { //bucle infinito hasta que el jugador de una entrada valida
        cout << playerName << ", elige una columna (1-7): "; // muestra mensaje para elegir columna
        string line; // variable para guardar texto ingresado
        if (!std::getline(cin,line)) return -1; //  si no puede leer, termine

        // eliminar espacio al inicio y final
        size_t s = line.find_first_not_of(" \t\r\n");
        size_t e = line.find_first_not_of(" \t\r\n");
        if (s == string::npos) { // si la entrada esta vacia
            cout << "entrada vacia. \n";
            continue; // vuelve a pedir      
        }
        string t = line.substr(s, e - s + 1); // 📍 NUEVO: crea una versión limpia del texto
        try {
            int col = std::stoi(t); // convertir txt a int
            if (col < 1 || col > 7) { // valida rango
                cout << "Rango 1-7.\n";
                continue;
            }
            return col - 1; // indice ajustad
        } catch (...) { // 📍 capturar si no se convierte a int
            cout << "Ingresa un número 1-7.\n"; //pregunta
        }
        

    }
}


int main() {
    cout << "=== Conecta 4 — Modo consola (6x7) ===\n";

    vector<vector<char>> board(ROWS, vector<char>(COLS, '.'));
    char current = 'X'; // quien inicia
    printBoard(board);

    while (true) { // bucle
        string name = (current == 'X') ? "Jugador 1 (X)" : "Jugador 2 (O)";
        int col = askColumn(name); // pide la columna

        if (col == -1) { // si presionan fin de entrada 
            cout << "Salida.\n";
            return 0;
        }

        if (isColumnFull(board, col)) { // verficia que exista espacio
            cout << "Columna llena. Elige otra.\n";
            continue;
        }

        dropPiece(board, col, current); // animacion para caida de ficha
        printBoard(board); // muestra tablero actualizado

        // cambia de jugador
        current = (current == 'X') ? 'O' : 'X';
    }

    return 0;
}
