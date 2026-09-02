#include "../Automatas.hpp"
#include <cctype>

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