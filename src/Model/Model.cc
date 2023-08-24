#include <vector>
#include <list>
#include "iostream"
#include "list"

#include "Model.h"

namespace s21 {

    std::string Model::commonCalcStart(const std::string &expression, const std::string &x) {
        std::string answer;
        if (expression.size() > STACK_SIZE) {
            std::cout << "Expression is to much long!" << std::endl;
            return ERROR;
        }

        std::string posifix = to_posifix(expression, x);


        return answer;
    }

    std::string Model::to_posifix(const std::string &infix, const std::string &x) {
        bool flag_status = true;
        std::string posifix;
        std::list<std::string> char_list;


        for (size_t infix_count = 0, postfix_count = 0; infix_count < infix.size() && flag_status; ++infix_count) {
            char inf_letter = infix[infix_count];
            std::string operat = is_operator(infix, infix_count);
            if (operat != "!") {

            } else if (isdigit(inf_letter)) { // digit check
                posifix[postfix_count++] = inf_letter;
                if (infix_count + 1 < infix.size() &&
                    (!(isdigit(infix[infix_count + 1]) || infix[infix_count + 1] == '.'))) {
                    posifix[postfix_count++] = ' ';
                }
            } else if (inf_letter == '.') {
                if (infix_count > 0 && isdigit(infix[infix_count - 1]) && isdigit(infix[infix_count + 1])) {
                    posifix[postfix_count++] = inf_letter;
                } else {
                    std::cout << "Dote is not correct!" << std::endl;
                    flag_status = false;
                }
            } else if (inf_letter == 'x' || inf_letter == 'p') {
                if (!is_string_number(x)) {
                    std::cout << "Dote is not correct!" << std::endl;
                    flag_status = false;
                } else {
                    posifix[postfix_count++] = inf_letter;
                    posifix[postfix_count++] = ' ';
                }
            }
        }
        if (!flag_status) {
            posifix = ERROR;
        }

        return posifix;
    }

    bool Model::is_string_number(const std::string &expression) {
        bool is_number = true;
        bool has_dot = false;
        for (size_t i = 0; i < expression.size() && is_number; ++i) {
            if (expression[i] == '.' && !has_dot) {
                has_dot = true;
            } else if (!isdigit(expression[i])) {
                is_number = false;
            }
        }
        return is_number;
    }

    std::string Model::is_operator(const std::string &infix, size_t i) {
        return std::string();
    }


} // s21