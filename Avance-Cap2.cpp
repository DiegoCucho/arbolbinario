#include <iostream>
using namespace std;

struct Nodo {
    string nombre;
    string fechaNacimiento;
    char genero;
    Nodo* izquierda;
    Nodo* derecha;
};

// Crear un nuevo nodo
Nodo* nuevoNodo(string nombre, string fecha, char genero) {
    Nodo* nodo = new Nodo();
    nodo->nombre = nombre;
    nodo->fechaNacimiento = fecha;
    nodo->genero = genero;
    nodo->izquierda = NULL;
    nodo->derecha = NULL;
    return nodo;
}

// Insertar en el árbol por orden alfabético del nombre
Nodo* insertar(Nodo* raiz, string nombre, string fecha, char genero) {
    if (raiz == NULL) {
        return nuevoNodo(nombre, fecha, genero);
    }
    if (nombre < raiz->nombre) {
        raiz->izquierda = insertar(raiz->izquierda, nombre, fecha, genero);
    } else if (nombre > raiz->nombre) {
        raiz->derecha = insertar(raiz->derecha, nombre, fecha, genero);
    } else {
        cout << "Ya existe una persona con ese nombre.\n";
    }
    return raiz;
}

// Recorridos
void preorden(Nodo* nodo) {
    if (nodo != NULL) {
        cout << nodo->nombre << " (" << nodo->fechaNacimiento << ", " << nodo->genero << ")\n";
        preorden(nodo->izquierda);
        preorden(nodo->derecha);
    }
}

void inorden(Nodo* nodo) {
    if (nodo != NULL) {
        inorden(nodo->izquierda);
        cout << nodo->nombre << " (" << nodo->fechaNacimiento << ", " << nodo->genero << ")\n";
        inorden(nodo->derecha);
    }
}

void postorden(Nodo* nodo) {
    if (nodo != NULL) {
        postorden(nodo->izquierda);
        postorden(nodo->derecha);
        cout << nodo->nombre << " (" << nodo->fechaNacimiento << ", " << nodo->genero << ")\n";
    }
}

// Buscar por nombre
Nodo* buscar(Nodo* raiz, string nombre) {
    if (raiz == NULL || raiz->nombre == nombre)
        return raiz;
    if (nombre < raiz->nombre)
        return buscar(raiz->izquierda, nombre);
    else
        return buscar(raiz->derecha, nombre);
}

int main() {
	setlocale(LC_CTYPE,"Spanish");
    Nodo* raiz = NULL;
    int n;
    string nombre, fecha;
    char genero;

    cout << "¿Cuántas personas deseas registrar?: ";
    cin >> n;
    cin.ignore(); // Limpiar el buffer

    for (int i = 0; i < n; i++) {
        cout << "Nombre: ";
        getline(cin, nombre);
        cout << "Fecha de nacimiento (dd/mm/aaaa): ";
        getline(cin, fecha);
        cout << "Género (M/F): ";
        cin >> genero;
        cin.ignore(); // Limpiar el buffer

        raiz = insertar(raiz, nombre, fecha, genero);
    }

    cout << "\nRecorrido Preorden:\n";
    preorden(raiz);

    cout << "\nRecorrido Inorden:\n";
    inorden(raiz);

    cout << "\nRecorrido Postorden:\n";
    postorden(raiz);

    // Búsqueda de una persona
    cout << "\n\nBuscar persona por nombre: ";
    getline(cin, nombre);
    Nodo* encontrado = buscar(raiz, nombre);
    if (encontrado != NULL) {
        cout << "Encontrado: " << encontrado->nombre << " - Nacido el " << encontrado->fechaNacimiento << ", Género: " << encontrado->genero << "\n";
    } else {
        cout << "No se encontró a " << nombre << ".\n";
    }

    return 0;
}

