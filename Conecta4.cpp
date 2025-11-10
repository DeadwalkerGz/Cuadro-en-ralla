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


int main() { // bucle principal
    cout << "=== Conecta 4 — Modo consola (6x7) ===\n";  //imprime mensaje, titulo
    
    // Crea un tablero de 6 f x 7 c lleno de puntos 
    vector<vector<char>> board(ROWS, vector<char>(COLS, '.'));

    // llama la funcion para imprimir el tablero
    printBoard(board);

    //pregunta al jugador que elija una columna
    int c = askColumn("Jugador 1 (X)");

    //muestro columna elejida
    cout << "Elegiste columna (0-based): " << c << "\n";

    return 0; // devuelve cero
}
