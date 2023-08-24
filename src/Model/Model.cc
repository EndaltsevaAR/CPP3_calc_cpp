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
        std::list<std::string> operatorList;


        for (size_t infix_count = 0, postfix_count = 0; infix_count < infix.size() && flag_status; ++infix_count) {
            char inf_letter = infix[infix_count];
            std::string operat = is_operator(infix, infix_count);
            if (isdigit(inf_letter)) { // digit check
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
            } else if (inf_letter == '(') {
                operatorList.push_back(infix.substr(infix_count, 1));
            } else if (inf_letter == ')') {
                bool isOpenBracket = false;
                while (!operatorList.empty() && !isOpenBracket) {
                    std::string last_operator = operatorList.back();
                    if (last_operator == "(") {
                        isOpenBracket = true;
                    } else {
                        posifix.insert(postfix_count, last_operator);
                        postfix_count += last_operator.size();
                        posifix[postfix_count++] = ' ';
                    }
                    operatorList.pop_back();
                }
                if (operatorList.empty() && !isOpenBracket) {
                    std::cout << "You have problem with brackets!" << std::endl;
                    flag_status = false;
                }
            } else if (inf_letter == ' ') {
                continue;
            } else if (operat != "!") { // операторы
                if (isUnarOperator(operat, infix_count)) {
                    if (operat == "-") {
                        posifix[postfix_count++] = inf_letter;
                    }
                } else if (operat == "^") {
                    while (!operatorList.empty() && getPriority(operat) < getPriority(operatorList.back())) {
                        posifix.insert(postfix_count, operatorList.back());
                        postfix_count += operatorList.back().size();
                        posifix[postfix_count++] = ' ';
                        operatorList.pop_back();
                    }
                } else {
                    while (!operatorList.empty() && getPriority(operat) <= getPriority(operatorList.back())) {
                        posifix.insert(postfix_count, operatorList.back());
                        postfix_count += operatorList.back().size();
                        posifix[postfix_count++] = ' ';
                        operatorList.pop_back();
                    }
                }
            } else { // ничего не подходит
                std::cout << "Wrong input from user!" << std::endl;
                flag_status = false;
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
        std::string operat = "!";
        if (is_one_letter_operator(infix[i])) {
            operat = infix.substr(i, 1);
        } else {
            operat = get_function(infix, i);
        }
        return operat;
    }

    bool Model::is_one_letter_operator(const char &letter) {
        return (letter == '+' || letter == '-' || letter == '*'
                || letter == '/' || letter == '%' || letter == '^');
    }

    std::string Model::get_function(const std::string &infix, size_t i) {
        std::string operat = "!";
        bool is_find = false;
        for (size_t funcLength = 4; funcLength >= 2 && !is_find; --funcLength) {
            if (infix.size() - i >= funcLength) {
                std::string subInfix = infix.substr(i, funcLength);
                if (subInfix == "sqrt" || subInfix == "asin" || subInfix == "acos" || subInfix == "atan"
                    || subInfix == "cos" || subInfix == "sin" || subInfix == "tan" || subInfix == "log" ||
                    subInfix == "ln") {
                    is_find = true;
                    operat = subInfix;
                }
            }
        }
        return operat;
    }

    int Model::getPriority(const std::string &operat) {
        int priority = -1;
        if (operat == "+" || operat == "-") {
            priority = 1;
        } else if (operat == "*" || operat == "/" || operat == "mod") {
            priority = 2;
        } else if (operat == "^") {
            priority = 3;
        } else if (operat == "sin" || operat == "cos" || operat == "tan" || operat == "acos" || operat == "asin" ||
                   operat == "atan" || operat == "ln" || operat == "lg" || operat == "sqrt") {
            priority = 4;
        }
        return priority;
    }

    bool Model::isUnarOperator(std::string infix, size_t count) {
        bool isUnar = false;
        if (infix[count] == '+' || infix[count] == '-') {
            if (((count > 0 && (is_one_letter_operator(infix[count - 1]) || infix[count - 1] == '(')) ||
                 count == 0) && (count + 1 < infix.size() && (isdigit(infix[count + 1]) || infix[count + 1] == 'x' ||
                 infix[count + 1] == 'p'))) {
                isUnar = true;
            }
        }
        return isUnar;
    }


} // s21