#include "Arbol.hpp"
#include <iostream>

void agregarHijo(Nodo *padre, Nodo *hijo) {

  if (padre == nullptr || hijo == nullptr) {
    return;
  }

  if (padre->hijoIzquierdo == nullptr) {
    padre->hijoIzquierdo = hijo;
    return;
  }

  Nodo *actual = padre->hijoIzquierdo;

  while (actual->hermanoDerecho != nullptr) {
    actual = actual->hermanoDerecho;
  }

  actual->hermanoDerecho = hijo;
}

void imprimirArbolRecursivo(Nodo *nodo, const std::string &prefijo,bool esUltimo) {

  if (nodo == nullptr) {
    return;
  }

  std::cout << prefijo;

  if (esUltimo) {
    std::cout << "└── ";
  } else {
    std::cout << "├── ";
  }

  std::cout << nodo->valor << '\n';

  std::string nuevoPrefijo = prefijo;

  if (esUltimo) {
    nuevoPrefijo += "    ";
  } else {
    nuevoPrefijo += "│   ";
  }

  Nodo *hijo = nodo->hijoIzquierdo;

  while (hijo != nullptr) {

    bool ultimoHijo = (hijo->hermanoDerecho == nullptr);

    imprimirArbolRecursivo(hijo, nuevoPrefijo, ultimoHijo);

    hijo = hijo->hermanoDerecho;
  }
}

void imprimirArbol(Nodo *raiz) {

  if (raiz == nullptr) {
    return;
  }

  std::cout << raiz->valor << '\n';

  Nodo *hijo = raiz->hijoIzquierdo;

  while (hijo != nullptr) {

    bool ultimoHijo = (hijo->hermanoDerecho == nullptr);

    imprimirArbolRecursivo(hijo, "", ultimoHijo);

    hijo = hijo->hermanoDerecho;
  }
}