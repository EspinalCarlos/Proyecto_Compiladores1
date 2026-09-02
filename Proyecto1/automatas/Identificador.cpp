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