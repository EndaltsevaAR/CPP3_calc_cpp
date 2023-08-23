#include "iostream"

#include "Model.h"

namespace s21 {

    std::string Model::commonCalcStart(const std::string& expression, const std::string& x) {
        std::string answer;
        if (expression.size() > STACK_SIZE) {
            std::cout<< "Expression is to much long!" << std::endl;
            return ERROR;
        }

        std::string posifix = to_posifix(expression, x);


        return std::string();
    }

    std::string Model::to_posifix(const std::string &expression, const std::string &x) {
        std::string posifix_expression;



        return std::string();
    }


} // s21