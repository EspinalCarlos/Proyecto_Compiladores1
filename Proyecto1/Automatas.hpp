#ifndef AUTOMATAS_HPP
#define AUTOMATAS_HPP

#include <string>

bool esIdentificador(const std::string& cadena);
bool esNumero(const std::string& cadena);
bool esString(const std::string& cadena);
bool esChar(const std::string& cadena);
bool esOperador(const std::string& cadena);
bool esDelimitador(const std::string& cadena);
#endif
