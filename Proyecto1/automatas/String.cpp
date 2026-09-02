#include "../Automatas.hpp"

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