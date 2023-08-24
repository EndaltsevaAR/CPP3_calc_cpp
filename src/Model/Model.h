//
// Created by joserans_home on 23.08.23.
//

#ifndef CALC_CPP_MODEL_H
#define CALC_CPP_MODEL_H

#include <string>

namespace s21 {

    class Model {
    public:

        std::string commonCalcStart(const std::string &expression, const std::string &x);


    private:
        // static constants
        const int STACK_SIZE = 255;
        const std::string ERROR = "ERROR";

        std::string to_posifix(const std::string &expression, const std::string &x);

        static bool is_string_number(const std::string &expression);

        std::string is_operator(const std::string &infix, size_t i);

        bool is_arithmetic_operator(const char &letter);
    };

} // s21

#endif //CALC_CPP_MODEL_H
