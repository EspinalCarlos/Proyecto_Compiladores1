#include "Arbol.hpp"

#include <iostream>

void agregarHijo(Nodo* padre, Nodo* hijo) {
    if (padre == nullptr || hijo == nullptr) {
        return;
    }
    if (padre->hijoIzquierdo == nullptr) {

        padre->hijoIzquierdo = hijo;

        return;
    }
    Nodo* actual = padre->hijoIzquierdo;
    while (actual->hermanoDerecho != nullptr) {
        actual = actual->hermanoDerecho;
    }
    actual->hermanoDerecho = hijo;
}

void imprimirArbol(Nodo* nodo,int nivel) {
    if (nodo == nullptr) {
        return;
    }
    for (int i = 0; i < nivel; i++) {
        std::cout << "    ";
    }
    std::cout << nodo->valor << '\n';
    // Bajan al hijo
    imprimirArbol(
        nodo->hijoIzquierdo,
        nivel + 1
    );
    // Se recorren los hermanos del mismo nivel
    imprimirArbol(nodo->hermanoDerecho,nivel);
}
