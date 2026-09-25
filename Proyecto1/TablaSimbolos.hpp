#ifndef TABLA_SIMBOLOS_HPP
#define TABLA_SIMBOLOS_HPP

#include <string>
#include <vector>

struct Simbolo {
  int id;
  std::string lexema;
  std::string tipo;
};

class TablaSimbolos {

private:
  std::vector<Simbolo> simbolos;

public:
  int insertar(const std::string &lexema, const std::string &tipo = "");
  void imprimir() const;
  const std::vector<Simbolo> &obtenerSimbolos() const;
};

#endif
