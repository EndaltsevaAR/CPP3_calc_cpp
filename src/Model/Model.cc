#include <vector>
#include <list>
#include "iostream"
#include "list"

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

    std::string Model::to_posifix(const std::string &infix, const std::string &x) {
        bool flag_error = false;
        std::string posifix;
        std::list<std::string> char_list;


        for (size_t infix_count = 0, postfix_count = 0; infix_count < infix.size() && !flag_error; ++infix_count) {
            if(isdigit(infix[infix_count])) { // digit check
                posifix[postfix_count] = infix[infix_count];
                ++postfix_count;
                if (infix_count + 1 < infix.size() && (!(isdigit(infix[infix_count+1]) || infix[infix_count+1] == '.'))) {
                    posifix[postfix_count] = ' ';
                    ++postfix_count;
                }
            } else if (infix[infix_count] == '.') {
                if (infix_count > 0 && isdigit(infix[infix_count-1]) && isdigit(infix[infix_count+1])) {
                    posifix[postfix_count] = infix[infix_count+1];
                    ++postfix_count;
                } else {
                    std::cout<< "Dote is not correct!" << std::endl;
                    flag_error = true;
                }
            }
        }
        if (flag_error) {
            posifix = ERROR;
        }

        return posifix;
    }


} // s21