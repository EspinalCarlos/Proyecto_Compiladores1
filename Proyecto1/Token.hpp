#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>

enum class TokenType {

    // Identificadores
    IDENTIFICADOR,
    ENTERO,
    DECIMAL,
    STRING_LITERAL,
    CHAR_LITERAL,

    // Palabras reservadas
    LET,
    FN,
    IF,
    ELSE,
    WHILE,
    FOR,
    RETURN,

    // Tipos
    TYPE_I32,
    TYPE_F64,
    TYPE_BOOL,
    TYPE_CHAR,
    TYPE_STR,

    // Operadores
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,

    AND,
    OR,
    NOT,

    ASSIGN,
    EQUAL,
    NOT_EQUAL,

    LESS,
    LESS_EQUAL,
    GREATER,
    GREATER_EQUAL,

    ARROW,

    // Delimitadores
    LEFT_PAREN,
    RIGHT_PAREN,
    LEFT_BRACE,
    RIGHT_BRACE,
    LEFT_BRACKET,
    RIGHT_BRACKET,

    COMMA,
    SEMICOLON,
    COLON,

    // Especiales
    END_OF_FILE,
    ERROR
};

struct Token {
    TokenType tipo;
    std::string lexema;
    int linea;
    int columna;
};

#endif