#include <iostream>     // Librería para entrada y salida estándar
#include <string>       // Librería para usar objetos string
#include <cstdlib>      // Para funciones como atoi()
#include <ctime>        // Para obtener la fecha actual
using namespace std;    // Evita el uso repetido del prefijo std::

struct Nodo {
    string nombre;          // Nombre del miembro
    string fechaNacimiento; // Fecha de nacimiento en formato dd/mm/aaaa
    char genero;            // Género: 'M' o 'F'
    Nodo* izquierda;        // Hijo izquierdo en el árbol
    Nodo* derecha;          // Hijo derecho en el árbol
};

// Valida que el nombre contenga solo letras y espacios
bool validarNombre(const string& nombre) {
    for (int i = 0; i < nombre.length(); ++i) {
        if (!isalpha(nombre[i]) && nombre[i] != ' ')
            return false;
    }
    return !nombre.empty();
}

// Valida que la fecha tenga formato correcto y valores válidos
bool validarFecha(const string& fecha) {
    if (fecha.length() != 10) return false;
    if (fecha[2] != '/' || fecha[5] != '/') return false;

    string dd = fecha.substr(0, 2);
    string mm = fecha.substr(3, 2);
    string aaaa = fecha.substr(6, 4);

    for (int i = 0; i < dd.length(); ++i)
        if (!isdigit(dd[i])) return false;
    for (int i = 0; i < mm.length(); ++i)
        if (!isdigit(mm[i])) return false;
    for (int i = 0; i < aaaa.length(); ++i)
        if (!isdigit(aaaa[i])) return false;

    int dia = atoi(dd.c_str());
    int mes = atoi(mm.c_str());
    int anio = atoi(aaaa.c_str());

    if (dia < 1 || dia > 31 || mes < 1 || mes > 12 || anio < 1000 || anio > 9999)
        return false;

    return true;
}

// Calcula la edad a partir de la fecha de nacimiento
int calcularEdad(const string& fechaNacimiento) {
    string dd = fechaNacimiento.substr(0, 2);
    string mm = fechaNacimiento.substr(3, 2);
    string aaaa = fechaNacimiento.substr(6, 4);

    int dia = atoi(dd.c_str());
    int mes = atoi(mm.c_str());
    int anio = atoi(aaaa.c_str());

    time_t t = time(NULL);           // Obtener tiempo actual
    tm* tiempoActual = localtime(&t); // Convertir a estructura tm

    int anioActual = tiempoActual->tm_year + 1900;
    int mesActual = tiempoActual->tm_mon + 1;
    int diaActual = tiempoActual->tm_mday;

    int edad = anioActual - anio;
    if (mesActual < mes || (mesActual == mes && diaActual < dia)) {
        edad--;
    }

    return edad;
}

// Crea un nuevo nodo con los datos proporcionados
Nodo* nuevoNodo(string nombre, string fecha, char genero) {
    Nodo* nodo = new Nodo();
    nodo->nombre = nombre;
    nodo->fechaNacimiento = fecha;
    nodo->genero = genero;
    nodo->izquierda = NULL;
    nodo->derecha = NULL;
    return nodo;
}

// Inserta un nuevo nodo en el árbol en la posición correcta
Nodo* insertar(Nodo* raiz, string nombre, string fecha, char genero) {
    if (raiz == NULL) return nuevoNodo(nombre, fecha, genero);
    if (nombre < raiz->nombre)
        raiz->izquierda = insertar(raiz->izquierda, nombre, fecha, genero);
    else if (nombre > raiz->nombre)
        raiz->derecha = insertar(raiz->derecha, nombre, fecha, genero);
    else
        cout << "Ya existe una persona con ese nombre.\n";
    return raiz;
}

// Recorrido Preorden: raíz -> izquierda -> derecha
void preorden(Nodo* nodo) {
    if (nodo != NULL) {
        int edad = calcularEdad(nodo->fechaNacimiento);
        cout << nodo->nombre << " (" << nodo->fechaNacimiento << ", Edad: " << edad << ", " << nodo->genero << ")\n";
        preorden(nodo->izquierda);
        preorden(nodo->derecha);
    }
}

// Recorrido Inorden: izquierda -> raíz -> derecha
void inorden(Nodo* nodo) {
    if (nodo != NULL) {
        inorden(nodo->izquierda);
        int edad = calcularEdad(nodo->fechaNacimiento);
        cout << nodo->nombre << " (" << nodo->fechaNacimiento << ", Edad: " << edad << ", " << nodo->genero << ")\n";
        inorden(nodo->derecha);
    }
}

// Recorrido Postorden: izquierda -> derecha -> raíz
void postorden(Nodo* nodo) {
    if (nodo != NULL) {
        postorden(nodo->izquierda);
        postorden(nodo->derecha);
        int edad = calcularEdad(nodo->fechaNacimiento);
        cout << nodo->nombre << " (" << nodo->fechaNacimiento << ", Edad: " << edad << ", " << nodo->genero << ")\n";
    }
}

// Busca un nodo por nombre
Nodo* buscar(Nodo* raiz, string nombre) {
    if (raiz == NULL || raiz->nombre == nombre)
        return raiz;
    if (nombre < raiz->nombre)
        return buscar(raiz->izquierda, nombre);
    else
        return buscar(raiz->derecha, nombre);
}

// Encuentra el nodo con el nombre mínimo (más a la izquierda)
Nodo* encontrarMinimo(Nodo* nodo) {
    while (nodo && nodo->izquierda != NULL)
        nodo = nodo->izquierda;
    return nodo;
}

// Elimina un nodo por nombre
Nodo* eliminar(Nodo* raiz, string nombre) {
    if (raiz == NULL) return NULL;

    if (nombre < raiz->nombre)
        raiz->izquierda = eliminar(raiz->izquierda, nombre);
    else if (nombre > raiz->nombre)
        raiz->derecha = eliminar(raiz->derecha, nombre);
    else {
        // Caso con un solo hijo o sin hijos
        if (raiz->izquierda == NULL) {
            Nodo* temp = raiz->derecha;
            delete raiz;
            return temp;
        } else if (raiz->derecha == NULL) {
            Nodo* temp = raiz->izquierda;
            delete raiz;
            return temp;
        }
        // Nodo con dos hijos
        Nodo* temp = encontrarMinimo(raiz->derecha);
        raiz->nombre = temp->nombre;
        raiz->fechaNacimiento = temp->fechaNacimiento;
        raiz->genero = temp->genero;
        raiz->derecha = eliminar(raiz->derecha, temp->nombre);
    }
    return raiz;
}

// Verifica si el árbol es un Árbol Binario de Búsqueda (ABB)
bool esABB(Nodo* nodo, string min = "", string max = "zzz") {
    if (nodo == NULL) return true;
    if ((min != "" && nodo->nombre <= min) || (max != "" && nodo->nombre >= max))
        return false;
    return esABB(nodo->izquierda, min, nodo->nombre) &&
           esABB(nodo->derecha, nodo->nombre, max);
}

// Muestra todos los recorridos
void mostrarRecorridos(Nodo* raiz) {
    cout << "\nRecorrido Preorden:\n";
    preorden(raiz);

    cout << "\nRecorrido Inorden:\n";
    inorden(raiz);

    cout << "\nRecorrido Postorden:\n";
    postorden(raiz);
}

int main() {
    Nodo* raiz = NULL; // Árbol inicialmente vacío
    int opcion;
    string nombre, fecha;
    char genero;

    // Menú principal
    do {
        cout << "\n===== MENU GENEALOGIA =====\n";
        cout << "1. Insertar miembro\n";
        cout << "2. Recorridos\n";
        cout << "3. Buscar miembro\n";
        cout << "4. Eliminar miembro\n";
        cout << "5. Verificar si es un ABB valido\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore(); // Ignora el salto de línea restante

        switch (opcion) {
            case 1:
                // Insertar miembro
                do {
                    cout << "\nNombre (solo letras y espacios): ";
                    getline(cin, nombre);
                    if (!validarNombre(nombre))
                        cout << "Nombre invalido. Intente de nuevo.\n";
                } while (!validarNombre(nombre));

                do {
                    cout << "Fecha de nacimiento (dd/mm/aaaa): ";
                    getline(cin, fecha);
                    if (!validarFecha(fecha))
                        cout << "Formato de fecha invalido. Intente de nuevo.\n";
                } while (!validarFecha(fecha));

                do {
                    cout << "Genero (M/F): ";
                    cin >> genero;
                    genero = toupper(genero); // convierte a mayúscula
                    if (genero != 'M' && genero != 'F') {
                        cout << "Genero invalido. Ingrese 'M' o 'F'.\n";
                    }
                    cin.ignore();
                } while (genero != 'M' && genero != 'F');

                raiz = insertar(raiz, nombre, fecha, genero);
                break;

            case 2:
                mostrarRecorridos(raiz);
                break;

            case 3:
                // Buscar
                cout << "\nNombre a buscar: ";
                getline(cin, nombre);
                {
                    Nodo* encontrado = buscar(raiz, nombre);
                    if (encontrado) {
                        int edad = calcularEdad(encontrado->fechaNacimiento);
                        cout << "Encontrado: " << encontrado->nombre
                             << " - Nacido el " << encontrado->fechaNacimiento
                             << ", Edad: " << edad
                             << ", Genero: " << encontrado->genero << "\n";
                    } else {
                        cout << "No se encontro a " << nombre << ".\n";
                    }
                }
                break;

            case 4:
                // Eliminar
                cout << "\nNombre a eliminar: ";
                getline(cin, nombre);
                raiz = eliminar(raiz, nombre);
                cout << "Nodo eliminado (si existia).\n";
                break;

            case 5:
                // Verificar ABB
                cout << "\nEl arbol es un ABB valido?: ";
                cout << (esABB(raiz) ? "Si" : "No") << "\n";
                break;

            case 0:
                cout << "Saliendo del programa...\n";
                break;

            default:
                cout << "Opcion invalida.\n";
        }
    } while (opcion != 0);

    return 0;
}
