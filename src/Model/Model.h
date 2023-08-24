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

        static std::string is_operator(const std::string &infix, size_t i);

        static bool is_one_letter_operator(const char &letter);

        static std::string get_function(const std::string &infix, size_t i);

        static int getPriority(const std::string& operat);

        static bool isUnarOperator(std::string infix, size_t count);
    };

} // s21

#endif //CALC_CPP_MODEL_H
