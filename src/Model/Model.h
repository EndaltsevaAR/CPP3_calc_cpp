//
// Created by joserans_home on 23.08.23.
//

#ifndef CALC_CPP_MODEL_H
#define CALC_CPP_MODEL_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

namespace s21 {

    class Model {
    public:
        static const std::string ERROR;
        std::string commonCalcStart(const std::string &expression, const std::string &x);
        static std::string zeroIsZero(std::string expression);


    private:
        // static constants
        const size_t STACK_SIZE = 255;
        const double s21_EPS_TEST = 1e-7;
        const int MAX_NUMBER = 1000000;

        static std::string to_posifix(const std::string &expression, const std::string &x);

        static bool is_string_number(const std::string &expression);

        static std::string is_operator(const std::string &infix, size_t i);

        static bool is_one_letter_operator(const char &letter);

        static std::string get_function(const std::string &infix, size_t i);

        static int getPriority(const std::string& operat);

        static bool isUnarOperator(std::string infix, size_t count);

        static bool isEngineeringFunction(const std::string &operat);

        std::string calculate(const std::string& posifix, const std::string &x);

        static std::vector<std::string> tokenizeString(const std::string& posifix);

        static bool isOperatorTwoParametrs(std::string &token);

        bool doTwoOperator(std::string &operat, double operand1, double operand2, double *pDouble);

        bool is_correct_pow_arguments(double operand1, double operand2) const;

        bool doOneOperator(std::string &operat, double operand, double *answer) const;

        static bool isNextLetterDigitableOrEmpty(const std::string &infix, size_t infix_count);

        static bool findOpenBracket(std::string &posifix, std::list<std::string> &operatorList, bool isCloseBracket);
        static void pop_top_operation(std::string &posifix, std::list<std::string> &operatorList);

    };

} // s21

#endif //CALC_CPP_MODEL_H
