//
// Created by joserans_home on 23.08.23.
//

#ifndef CALC_CPP_MODEL_H
#define CALC_CPP_MODEL_H

#include <list>
#include <string>
#include <vector>

namespace s21 {

    class Model {
    public:
        // static constants
        static const std::string ERROR;
        static const std::string X;

        std::string commonCalcStart(const std::string &expression, const std::string &x);
        static std::string zeroIsZero(std::string expression);


    private:
        // static constants
        static const size_t STACK_SIZE = 255;
        constexpr static const double s21_EPS_TEST = 1e-7;
        static const int MAX_NUMBER = 1000000;
        static const int WIDTH = 850;
        static const int HEIGHT = 600;
        static std::string convertToPosifix(const std::string &expression, const std::string &x);
        static void handleDigit(std::string& posifix, const std::string& expression, size_t& infix_count);
        static bool handleDote(std::string& posifix, const std::string& expression, size_t& infix_count);
        static bool handleXP(std::string& posifix, const std::string& x,  char inf_letter);
        static bool handleOperator(std::string& posifix, const std::string& expression, size_t& infix_count, std::list<std::string>& operatorList);

        std::string calculateResult(const std::string& posifix, const std::string &x);
        bool calculateMagicWithOperator(std::string &token, std::list<double> &doubleList);

        static bool isStringNumber(const std::string &expression);

        static std::string isOperator(const std::string &infix, size_t i);

        static bool isOneLetterOperator(const char &letter);

        static std::string getFunction(const std::string &infix, size_t i);

        static int getPriority(const std::string& operat);

        static bool isUnarOperator(std::string infix, size_t count);

        static bool isEngineeringFunction(const std::string &operat);

        static std::vector<std::string> tokenizeString(const std::string& posifix);

        static bool isOperatorTwoParametrs(std::string &token);

        bool doTwoOperator(std::string &operat, double operand1, double operand2, double *pDouble);

        bool isCorrectPowArguments(double operand1, double operand2) const;

        bool doOneOperator(std::string &operat, double operand, double *answer) const;

        static bool isNextLetterDigitableOrEmpty(const std::string &infix, size_t infix_count);

        static bool findOpenBracket(std::string &posifix, std::list<std::string> &operatorList, bool isCloseBracket);

        static void popTopOperation(std::string &posifix, std::list<std::string> &operatorList);
    };

} // s21

#endif //CALC_CPP_MODEL_H
