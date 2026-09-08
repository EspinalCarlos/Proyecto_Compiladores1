#include "../Automatas.hpp"
#include <cctype>

bool esIdentificador(const std::string& cadena) {

    enum Estado {
        q0,
        q1,
        error
    };

    Estado estado = q0;

    for (char c : cadena) {

        switch (estado) {

            case q0:
                if (std::isalpha(static_cast<unsigned char>(c)) || c == '_') {
                    estado = q1;
                } else {
                    estado = error;
                }
                break;

            case q1:
                if (std::isalnum(static_cast<unsigned char>(c)) || c == '_') {
                    estado = q1;
                } else {
                    estado = error;
                }
                break;

            case error:
                return false;
        }
    }

    return estado == q1;
}

bool esNumero(const std::string& cadena) {

    enum Estado {
        q0,
        q1,
        q2,
        q3,
        error
    };

    Estado estado = q0;

    for (char c : cadena) {

        switch (estado) {

            case q0:
                if (std::isdigit(static_cast<unsigned char>(c))) {
                    estado = q1;
                } else {
                    estado = error;
                }
                break;

            case q1:
                if (std::isdigit(static_cast<unsigned char>(c))) {
                    estado = q1;
                }
                else if (c == '.') {
                    estado = q2;
                }
                else {
                    estado = error;
                }
                break;

            case q2:
                if (std::isdigit(static_cast<unsigned char>(c))) {
                    estado = q3;
                } else {
                    estado = error;
                }
                break;

            case q3:
                if (std::isdigit(static_cast<unsigned char>(c))) {
                    estado = q3;
                } else {
                    estado = error;
                }
                break;

            case error:
                return false;
        }
    }

    return estado == q1 || estado == q3;
}

bool esOperador(const std::string& cadena) {

    enum Estado {
        q0,
        qSimple,
        qAnd,
        qOr,
        qFinal,
        error
    };

    Estado estado = q0;

    for (char c : cadena) {

        switch (estado) {

            case q0:
                switch (c) {
                    case '+':
                    case '-':
                    case '*':
                    case '/':
                    case '!':
                        estado = qSimple;
                        break;

                    case '&':
                        estado = qAnd;
                        break;

                    case '|':
                        estado = qOr;
                        break;

                    default:
                        estado = error;
                        break;
                }
                break;

            case qSimple:
                estado = error;
                break;

            case qAnd:
                if (c == '&') {
                    estado = qFinal;
                } else {
                    estado = error;
                }
                break;

            case qOr:
                if (c == '|') {
                    estado = qFinal;
                } else {
                    estado = error;
                }
                break;

            case qFinal:
                estado = error;
                break;

            case error:
                return false;
        }
    }

    return estado == qSimple || estado == qFinal;
}

bool escapeValido(char c) {
    return c == 'n' ||
           c == 'r' ||
           c == 't' ||
           c == '0' ||
           c == '\\' ||
           c == '"' ||
           c == '\'';
}

bool esString(const std::string& cadena) {

    enum Estado {
        q0,
        q1,
        qEscape,
        qFinal,
        error
    };

    Estado estado = q0;

    for (char c : cadena) {

        switch (estado) {

            case q0:
                if (c == '"') {
                    estado = q1;
                } else {
                    estado = error;
                }
                break;

            case q1:
                if (c == '"') {
                    estado = qFinal;
                }
                else if (c == '\\') {
                    estado = qEscape;
                }
                else if (c == '\n' || c == '\r') {
                    estado = error;
                }
                else {
                    estado = q1;
                }
                break;

            case qEscape:
                if (escapeValido(c)) {
                    estado = q1;
                } else {
                    estado = error;
                }
                break;

            case qFinal:
                estado = error;
                break;

            case error:
                return false;
        }
    }

    return estado == qFinal;
}

bool esDelimitador(const std::string& cadena) {

    enum Estado {
        q0,
        q1,
        error
    };

    Estado estado = q0;

    for (char c : cadena) {

        switch (estado) {

            case q0:
                switch (c) {
                    case '{':
                    case '}':
                    case '(':
                    case ')':
                    case '[':
                    case ']':
                    case ',':
                    case ';':
                        estado = q1;
                        break;

                    default:
                        estado = error;
                        break;
                }
                break;

            case q1:
                estado = error;
                break;

            case error:
                return false;
        }
    }

    return estado == q1;
}

bool esChar(const std::string& cadena) {

    enum Estado {
        q0,
        q1,
        q2,
        qEscape,
        qFinal,
        error
    };

    Estado estado = q0;

    for (char c : cadena) {

        switch (estado) {

            case q0:
                if (c == '\'') {
                    estado = q1;
                } else {
                    estado = error;
                }
                break;

            case q1:
                if (c == '\\') {
                    estado = qEscape;
                }
                else if (
                    c != '\'' &&
                    c != '\n' &&
                    c != '\r'
                ) {
                    estado = q2;
                }
                else {
                    estado = error;
                }
                break;

            case qEscape:
                switch (c) {
                    case 'n':
                    case 't':
                    case 'r':
                    case '0':
                    case '\\':
                    case '\'':
                    case '"':
                        estado = q2;
                        break;

                    default:
                        estado = error;
                        break;
                }
                break;

            case q2:
                if (c == '\'') {
                    estado = qFinal;
                } else {
                    estado = error;
                }
                break;

            case qFinal:
                estado = error;
                break;

            case error:
                return false;
        }
    }

    return estado == qFinal;
}
