#include <iostream> // importa libreria estandar de entrada y salida
#include <vector> // libreria de vectores para hacer los arreglos
#include <string> // libreria para poder usar string
using std::cout; using std::cin; using std::vector; using std::string;  // poner cout,cin y vector mas corto

// Constantes para definir las columnas y filas del arreglo
static const int ROWS = 6; // Filas
static const int COLS = 7;// columnas

void printBoard(const vector<vector<char>>& b) { //funcion para imprimir tablero en la linea de comando
    cout << "\n   1 2 3 4 5 6 7\n"; // muestra los numeros de las columnas arriba del tablero

    //recorre cada fila del arreglo
    for ( int r = 0; r < ROWS; ++r) { //bucle 
        cout << " | "; // imprime borde de la fila izquierda
        // recorre cada columna de la fila actual
        for (int c = 0; c < COLS; ++c) { // bucle interno para recorrer las filas de cada columna
            cout << b[r][c] << '.'; // imprime el valor almacenado, pondra "." si esta vacio
        }
        cout << "|\n";  // Cierra la fila con un borde derecho y salto de línea
    }
    cout << "-----------------\n";  // Linea inferior del tablero
}

// verifica colimna llena
bool isColumnFull(const vector<vector<char>>& b, int c) { //funcion
    return b[0][c] != '.'; // si no esta vacio, esta lleno
}

// Coloca la ficha
int dropPiece(vector<vector<char>>& b, int c, char sym) { //funcion
    if (c < 0 || c >= COLS || isColumnFull(b, c)) return -1; // no valido o lleno
    for (int r = ROWS - 1; r >= 0; --r) { // desde abajo a arriba
        if (b[r][c] == '.') { // encuentra un lugar vacio
            b[r][c] = sym; // colocar ficha x o o
            return r; // devuelve la coordenada donde cayo la ficha
        }
    }
    return -1; // error si no encuentra espacio
}

//ver empate
bool isFull(const vector<vector<char>>& b) { //funcion
    for (int c = 0; c < COLS; ++c) //bucle 
        if (b[0][c] == '.') return false; //verifica ubicacion del arreglo columna por columna
    return true; //si estan todas llenas devuelve true si no false
}

// mirar si pasa 4 en ralla
bool checkWinner(const vector<vector<char>>& b, char sym) { //funcion
    //horizontal hacia los lados
    for (int r = 0; r < ROWS; ++r) // bucle  de filas
        for (int c = 0; c <= COLS - 4; ++c) // bucle para mirar filas en la columna actual
            if (b[r][c] == sym && b[r][c+1] == sym && b[r][c+2] == sym && b[r][c+3] == sym) // si encuentra una fila horizontal en 4
                return true; // da true

    //vertica abajo
    for (int r = 0; r <= ROWS - 4; ++r) // bucle  de columnas
        for (int c = 0; c < COLS; ++c) // bucle para mirar filas en la columna actual
            if (b[r][c] == sym && b[r+1][c] == sym && b[r+2][c] == sym && b[r+3][c] == sym) // si encuentra 4 en fila 
                return true; // regresa true

    //diagonal abajo a derecha
    for (int r = 0; r <= ROWS - 4; ++r) //bucle  de filas
        for (int c = 0; c <= COLS - 4; ++c)//  bucle para mirar filas en la columna actual
            if (b[r][c] == sym && b[r+1][c+1] == sym && b[r+2][c+2] == sym && b[r+3][c+3] == sym)// si encuentra una fila diagonal desde abajo a la derecha
                return true; // regresa true

    //diagonal abajo a izquierda
    for (int r = 0; r <= ROWS - 4; ++r) // bucle  de columnas
        for (int c = 3; c < COLS; ++c)// bucle para mirar filas en la columna actual
            if (b[r][c] == sym && b[r+1][c-1] == sym && b[r+2][c-2] == sym && b[r+3][c-3] == sym) // si encuentra una fila diagonal desde abajo a la izquierda
                return true;// regresa true

    return false; //nadie gana
}

int askColumn(const string & playerName){ //funcion para preguntar que columna se coloca el signo
    while (true) { //bucle infinito hasta que el jugador de una entrada valida
        cout << playerName << ", elige una columna (1-7): "; // muestra mensaje para elegir columna
        string line; // variable para guardar texto ingresado
        if (!std::getline(cin,line)) return -1; //  si no puede leer, termine

        // eliminar espacio al inicio y final
        size_t s = line.find_first_not_of(" \t\r\n"); // la neta nose como funciona bien pero funciona
        size_t e = line.find_first_not_of(" \t\r\n");  // la neta nose como funciona bien pero funciona
        if (s == string::npos) { // si la entrada esta vacia
            cout << "entrada vacia. \n"; //imprimit mensaje
            continue; // vuelve a pedir      
        }
        string t = line.substr(s, e - s + 1); //texto limpio
        try { //intenta
            int col = std::stoi(t); // convertir txt a int
            if (col < 1 || col > 7) { // valida rango
                cout << "Rango 1-7.\n"; //imprime
                continue; //termina
            }
            return col - 1; // indice ajustad
        } catch (...) { //verificar si se convierte en numero
            cout << "Ingresa un número 1-7.\n"; //pregunta
        }
        

    }
}


int main() { //bucle principal
    cout << "=== Conecta 4 — Modo consola (6x7) ===\n"; // texto de titulo

    vector<vector<char>> board(ROWS, vector<char>(COLS, '.'));  // crea una variable  tipo char  guardando los parametros
    char current = 'X'; // quien inicia
    printBoard(board); //llama a la funcion printBoard

    while (true) { // bucle
        string name = (current == 'X') ? "Jugador 1 (X)" : "Jugador 2 (O)"; // asigna al primer jugador como X y al 2 como O por default
        int col = askColumn(name); // pide la columna para poner el signo

        if (col == -1) { // si presionan fin de entrada 
            cout << "Salida.\n"; //mensaje de salida
            return 0; //termina
        }

        if (isColumnFull(board, col)) { // verficia que exista espacio
            cout << "Columna llena. Elige otra.\n"; // mensaje para decir que se escoja otra columna para el signo
            continue; //termina y salta al otro cilo
        }

        dropPiece(board, col, current); // animacion para caida de ficha, remplazar espacio por signo de jugador actual
        printBoard(board); // muestra tablero actualizado

        //ganadir?
        if (checkWinner(board, current)) { // funcion para mirar el ganador
            cout << name << " ha ganado\n"; // mensaje
            break; // termina el bucle
        }

        //empate
        if (isFull(board)) { // llama la funcion para ver si esta llena la tabla, arreglo
            cout << "Empate.\n"; //mensaje
            break;//pasa al siguiente bucle
        }
        

        // cambia de jugador
        current = (current == 'X') ? 'O' : 'X'; //cambia el signo a poner 
    }

    return 0; //termina el programa
}
