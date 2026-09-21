#include "Lexer.hpp"
#include "Automatas.hpp"

#include <cctype>

Lexer::Lexer(const std::string& codigo) {

    this->codigo = codigo;

    posicion = 0;
    linea = 1;
    columna = 1;
}


char Lexer::actual() {

    if (posicion >= codigo.length()) {
        return '\0';
    }

    return codigo[posicion];
}

void Lexer::avanzar_cadena() {

    if (posicion >= codigo.length()) {
        return;
    }

    if (codigo[posicion] == '\n') {

        linea++;
        columna = 1;

    } else {

        columna++;
    }

    posicion++;
}

void Lexer::agregarToken(TokenType tipo,const std::string& lexema,int lineaInicio,int columnaInicio) {
    Token token;
    token.tipo = tipo;
    token.lexema = lexema;
    token.linea = lineaInicio;
    token.columna = columnaInicio;
    tokens.push_back(token);
}

TokenType Lexer::verificarPalabraReservada(const std::string& palabra) {

    if (palabra == "let")
        return TokenType::LET;

    if (palabra == "fn")
        return TokenType::FN;

    if (palabra == "if")
        return TokenType::IF;

    if (palabra == "else")
        return TokenType::ELSE;

    if (palabra == "while")
        return TokenType::WHILE;

    if (palabra == "for")
        return TokenType::FOR;

    if (palabra == "return")
        return TokenType::RETURN;


    // Tipos de Rust

    if (palabra == "i32")
        return TokenType::TYPE_I32;

    if (palabra == "f64")
        return TokenType::TYPE_F64;

    if (palabra == "bool")
        return TokenType::TYPE_BOOL;

    if (palabra == "char")
        return TokenType::TYPE_CHAR;

    if (palabra == "str")
        return TokenType::TYPE_STR;


    return TokenType::IDENTIFICADOR;
}

void Lexer::Identificador() {

    int inicio = posicion;
    int lineaInicio = linea;
    int columnaInicio = columna;

    while (
        std::isalnum(static_cast<unsigned char>(actual())) ||
        actual() == '_'
    ) {

        avanzar_cadena();
    }

    std::string lexema =
        codigo.substr(inicio, posicion - inicio);

    if (esIdentificador(lexema)) {

        TokenType tipo =
            verificarPalabraReservada(lexema);

        agregarToken(
            tipo,
            lexema,
            lineaInicio,
            columnaInicio
        );

    } else {

        agregarToken(
            TokenType::ERROR,
            lexema,
            lineaInicio,
            columnaInicio
        );
    }
}

void Lexer::Numero() {

    int inicio = posicion;
    int lineaInicio = linea;
    int columnaInicio = columna;

    bool tienePunto = false;

    while (
        std::isalnum(static_cast<unsigned char>(actual())) ||
        actual() == '.' ||
        actual() == '_'
    ) {

        if (actual() == '.') {
            tienePunto = true;
        }

        avanzar_cadena();
    }

    std::string lexema =
        codigo.substr(inicio, posicion - inicio);

    if (!esNumero(lexema)) {

        agregarToken(
            TokenType::ERROR,
            lexema,
            lineaInicio,
            columnaInicio
        );

        return;
    }

    if (tienePunto) {

        agregarToken(
            TokenType::DECIMAL,
            lexema,
            lineaInicio,
            columnaInicio
        );

    } else {

        agregarToken(
            TokenType::ENTERO,
            lexema,
            lineaInicio,
            columnaInicio
        );
    }
}

void Lexer::String() {

    int inicio = posicion;
    int lineaInicio = linea;
    int columnaInicio = columna;

    avanzar_cadena();

    bool escape = false;
    bool cerrado = false;

    while (actual() != '\0') {

        char c = actual();

        if (!escape && c == '"') {

            avanzar_cadena();
            cerrado = true;

            break;
        }

        if (!escape && c == '\\') {

            escape = true;

        } else {

            escape = false;
        }

        avanzar_cadena();
    }

    std::string lexema = codigo.substr(inicio, posicion - inicio);

    if (cerrado && esString(lexema)) {

        agregarToken(
            TokenType::STRING_LITERAL,
            lexema,
            lineaInicio,
            columnaInicio
        );

    } else {

        agregarToken(
            TokenType::ERROR,
            lexema,
            lineaInicio,
            columnaInicio
        );
    }
}

void Lexer::Char() {

    int inicio = posicion;

    int lineaInicio = linea;
    int columnaInicio = columna;


    // Consumir '
    avanzar_cadena();


    bool escape = false;
    bool cerrado = false;


    while (
        actual() != '\0' &&
        actual() != '\n' &&
        actual() != '\r'
    ) {

        char c = actual();


        if (!escape && c == '\'') {

            avanzar_cadena();

            cerrado = true;

            break;
        }


        if (!escape && c == '\\') {

            escape = true;

        } else {

            escape = false;
        }


        avanzar_cadena();
    }


    std::string lexema =
        codigo.substr(
            inicio,
            posicion - inicio
        );


    if (cerrado && esChar(lexema)) {

        agregarToken(
            TokenType::CHAR_LITERAL,
            lexema,
            lineaInicio,
            columnaInicio
        );

    } else {

        agregarToken(
            TokenType::ERROR,
            lexema,
            lineaInicio,
            columnaInicio
        );
    }
}

void Lexer::Operador() {

    int lineaInicio = linea;
    int columnaInicio = columna;

    std::string lexema;


    // Guardamos el primer carácter
    char primero = actual();

    lexema += primero;

    avanzar_cadena();

    // Comprobar operadores de 2 caracteres
  

    if (actual() != '\0') {

        char segundo = actual();


        if (
            (primero == '&' && segundo == '&') ||
            (primero == '|' && segundo == '|') ||
            (primero == '=' && segundo == '=') ||
            (primero == '!' && segundo == '=') ||
            (primero == '<' && segundo == '=') ||
            (primero == '>' && segundo == '=') ||
            (primero == '-' && segundo == '>')
        ) {

            lexema += segundo;

            avanzar_cadena();
        }
    }
      if (!esOperador(lexema)) {

        agregarToken(
            TokenType::ERROR,
            lexema,
            lineaInicio,
            columnaInicio
        );

        return;
    }
      TokenType tipo;


    if (lexema == "+") {

        tipo = TokenType::PLUS;

    } else if (lexema == "-") {

        tipo = TokenType::MINUS;

    } else if (lexema == "*") {

        tipo = TokenType::MULTIPLY;

    } else if (lexema == "/") {

        tipo = TokenType::DIVIDE;

    } else if (lexema == "&&") {

        tipo = TokenType::AND;

    } else if (lexema == "||") {

        tipo = TokenType::OR;

    } else if (lexema == "!") {

        tipo = TokenType::NOT;

    } else if (lexema == "=") {

        tipo = TokenType::ASSIGN;

    } else if (lexema == "==") {

        tipo = TokenType::EQUAL;

    } else if (lexema == "!=") {

        tipo = TokenType::NOT_EQUAL;

    } else if (lexema == "<") {

        tipo = TokenType::LESS;

    } else if (lexema == "<=") {

        tipo = TokenType::LESS_EQUAL;

    } else if (lexema == ">") {

        tipo = TokenType::GREATER;

    } else if (lexema == ">=") {

        tipo = TokenType::GREATER_EQUAL;

    } else if (lexema == "->") {

        tipo = TokenType::ARROW;

    } else {

        tipo = TokenType::ERROR;
    }


    agregarToken(
        tipo,
        lexema,
        lineaInicio,
        columnaInicio
    );
}

void Lexer::Delimitador() {

    int lineaInicio = linea;
    int columnaInicio = columna;


    std::string lexema(
        1,
        actual()
    );


    char c = actual();

    avanzar_cadena();


    // Validar con el automata
    if (!esDelimitador(lexema)) {

        agregarToken(
            TokenType::ERROR,
            lexema,
            lineaInicio,
            columnaInicio
        );

        return;
    }


    TokenType tipo;


    switch (c) {

        case '(':
            tipo = TokenType::LEFT_PAREN;
            break;

        case ')':
            tipo = TokenType::RIGHT_PAREN;
            break;

        case '{':
            tipo = TokenType::LEFT_BRACE;
            break;

        case '}':
            tipo = TokenType::RIGHT_BRACE;
            break;

        case '[':
            tipo = TokenType::LEFT_BRACKET;
            break;

        case ']':
            tipo = TokenType::RIGHT_BRACKET;
            break;

        case ',':
            tipo = TokenType::COMMA;
            break;

        case ';':
            tipo = TokenType::SEMICOLON;
            break;

        case ':':
            tipo = TokenType::COLON;
            break;

        default:
            tipo = TokenType::ERROR;
            break;
    }


    agregarToken(
        tipo,
        lexema,
        lineaInicio,
        columnaInicio
    );
}



std::vector<Token> Lexer::tokenizar() {

    while (actual() != '\0') {

        char c = actual();

        //Espacios

        if (
            c == ' ' ||
            c == '\t' ||
            c == '\r' ||
            c == '\n'
        ) {

            avanzar_cadena();
            continue;
        }

        //Identificadores

        if (
            std::isalpha(static_cast<unsigned char>(c)) ||
            c == '_'
        ) {

            Identificador();
            continue;
        }

        // Numeros

        if (std::isdigit(static_cast<unsigned char>(c))) {

            Numero();
            continue;
        }

        //Strings

        if (c == '"') {

            String();
            continue;
        }

        if (c == '\'') {
            Char();
            continue;
        }

        //Operadores
        if (
            c == '+' ||
            c == '-' ||
            c == '*' ||
            c == '/' ||
            c == '!' ||
            c == '&' ||
            c == '|' ||
            c == '=' ||
            c == '<' ||
            c == '>'
        ) {
            Operador();
            continue;
        }

        //Delimitadores
         if (
            c == '{' ||
            c == '}' ||
            c == '(' ||
            c == ')' ||
            c == '[' ||
            c == ']' ||
            c == ',' ||
            c == ';' ||
            c == ':'
        ) {
            Delimitador();
            continue;
        }

        //Caracter Desconocido

        std::string desconocido(1, c);

        agregarToken(
            TokenType::ERROR,
            desconocido,
            linea,
            columna
        );

        avanzar_cadena();
    }

    // Final del archivo
    agregarToken(
        TokenType::END_OF_FILE,
        "",
        linea,
        columna
    );

    return tokens;
}