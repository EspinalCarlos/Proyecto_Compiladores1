#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "Token.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"
#include "Arbol.hpp"
#include "TablaSimbolos.hpp"

std::string leerArchivo(const std::string& ruta) {

    std::ifstream archivo(ruta);

    if (!archivo.is_open()) {

        std::cout
            << "No se pudo abrir el archivo: "
            << ruta
            << '\n';

        return "";
    }

    std::stringstream contenido;

    contenido << archivo.rdbuf();

    return contenido.str();
}

std::string nombreToken(TokenType tipo) {

    switch (tipo) {

        case TokenType::IDENTIFICADOR:
            return "IDENTIFICADOR";

        case TokenType::ENTERO:
            return "ENTERO";

        case TokenType::DECIMAL:
            return "DECIMAL";

        case TokenType::STRING_LITERAL:
            return "STRING_LITERAL";

        case TokenType::CHAR_LITERAL:
            return "CHAR_LITERAL";

        case TokenType::LET:
            return "LET";

        case TokenType::FN:
            return "FN";

        case TokenType::IF:
            return "IF";

        case TokenType::ELSE:
            return "ELSE";

        case TokenType::WHILE:
            return "WHILE";

        case TokenType::FOR:
            return "FOR";

        case TokenType::RETURN:
            return "RETURN";

        case TokenType::TYPE_I32:
            return "TYPE_I32";

        case TokenType::TYPE_F64:
            return "TYPE_F64";

        case TokenType::TYPE_BOOL:
            return "TYPE_BOOL";

        case TokenType::TYPE_CHAR:
            return "TYPE_CHAR";

        case TokenType::TYPE_STR:
            return "TYPE_STR";

        case TokenType::PLUS:
            return "PLUS";

        case TokenType::MINUS:
            return "MINUS";

        case TokenType::MULTIPLY:
            return "MULTIPLY";

        case TokenType::DIVIDE:
            return "DIVIDE";

        case TokenType::AND:
            return "AND";

        case TokenType::OR:
            return "OR";

        case TokenType::NOT:
            return "NOT";

        case TokenType::ASSIGN:
            return "ASSIGN";

        case TokenType::EQUAL:
            return "EQUAL";

        case TokenType::NOT_EQUAL:
            return "NOT_EQUAL";

        case TokenType::LESS:
            return "LESS";

        case TokenType::LESS_EQUAL:
            return "LESS_EQUAL";

        case TokenType::GREATER:
            return "GREATER";

        case TokenType::GREATER_EQUAL:
            return "GREATER_EQUAL";

        case TokenType::ARROW:
            return "ARROW";

        case TokenType::LEFT_PAREN:
            return "LEFT_PAREN";

        case TokenType::RIGHT_PAREN:
            return "RIGHT_PAREN";

        case TokenType::LEFT_BRACE:
            return "LEFT_BRACE";

        case TokenType::RIGHT_BRACE:
            return "RIGHT_BRACE";

        case TokenType::LEFT_BRACKET:
            return "LEFT_BRACKET";

        case TokenType::RIGHT_BRACKET:
            return "RIGHT_BRACKET";

        case TokenType::COMMA:
            return "COMMA";

        case TokenType::SEMICOLON:
            return "SEMICOLON";

        case TokenType::COLON:
            return "COLON";

        case TokenType::END_OF_FILE:
            return "END_OF_FILE";

        case TokenType::ERROR:
            return "ERROR";
    }

    return "DESCONOCIDO";
}


int main(int argc, char* argv[]) {
    // Archivo
    std::string ruta = "Pruebas/PruebaErrores.rs";
    if (argc > 1) {
        ruta = argv[1];
    }
    std::string codigo = leerArchivo(ruta);

    if (codigo.empty()) {
        std::cout
            << "El archivo esta vacio o no se pudo leer.\n";
        return 1;
    }

    std::cout << "Codigo Fuente\n";
    std::cout << codigo << "\n\n";

    // 2. Analisis Lexico
    Lexer lexer(codigo);
    std::vector<Token> tokens = lexer.tokenizar();
    std::cout << "Tokens\n";
    bool ErrorLexico = false;

    for (const Token& token : tokens) {
        std::cout << nombreToken(token.tipo) << "\t"<< token.lexema;
        if (token.tipo != TokenType::END_OF_FILE) {
            std::cout << "\tLinea: " << token.linea << "\tColumna: " << token.columna;
        }
        std::cout << '\n';
        if (token.tipo == TokenType::ERROR) {
            ErrorLexico = true;
        }
    }


    // 3. Errores Lexicos


    if (ErrorLexico) {

        std::cout << "\n";
        std::cout << "Errores Lexicos:\n";
  
        for (const Token& token : tokens) {
            if (token.tipo == TokenType::ERROR) {
                std::cout<< "Error lexico"<< " | Lexema: "<< token.lexema << " | Linea: "<< token.linea<< " | Columna: "<< token.columna<< '\n';
            }
        }
        return 0;
    }

    // 4. Analisis Sintactico
    Parser parser(tokens);
    Nodo* arbol = parser.parsear();


  
    // 5. Arbol
    std::cout << "\nArbol de sintaxis:\n";
    imprimirArbol(arbol);

    // 6. Tabla de Simbolos
    std::cout << "\nTabla de Simbolos:\n";
    parser.obtenerTablaSimbolos().imprimir();

    // 7. Errores Sintacticos
    std::vector<ErrorCompilador> errores = parser.obtenerErrores();
    std::cout << "\nERRORES SINTACTICOS\n";
    if (errores.empty()) {
        std::cout << "No se encontraron errores sintacticos.\n";
    } else {
        for (const ErrorCompilador& error : errores) {
            std::cout<< "Error sintactico" << " | Linea: " << error.linea<< " | Columna: " << error.columna << " | " << error.mensaje << '\n';
        }
    }
    return 0;
}
