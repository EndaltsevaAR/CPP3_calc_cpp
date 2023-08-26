#include <vector>
#include <list>
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

#include "Model.h"

namespace s21 {

    std::string Model::commonCalcStart(const std::string &expression, const std::string &x) {
        setlocale(LC_ALL, "en_US.UTF-8");
        std::string answer;
        if (expression.size() > STACK_SIZE) {
            std::cout << "Expression is to much long!" << std::endl;
            return ERROR;
        }

        answer = to_posifix(expression, x);
        if (answer != ERROR) {
            answer = calculate(answer, x);
        }


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

            if (flag_status) {
                while (!operatorList.empty()) {
                    posifix.insert(postfix_count, operatorList.back());
                    postfix_count += operatorList.back().size();
                    posifix[postfix_count++] = ' ';
                    operatorList.pop_back();
                }
                posifix[postfix_count] = '\0';

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
                if (isEngineeringFunction(operat) || operat == "mod") {
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
        } else if (isEngineeringFunction(operat)) {
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

    bool Model::isEngineeringFunction(const std::string &operat) {
        return operat == "sin" || operat == "cos" || operat == "tan" || operat == "acos" || operat == "asin" ||
               operat == "atan" || operat == "ln" || operat == "lg" || operat == "sqrt";
    }

    std::string Model::calculate(const std::string& posifix, const std::string &x) {
        std::string answer = ERROR;
        int flag_status = true;
        std::list<double> doubleList;

        std::vector<std::string> tokens = tokenizeString(posifix); // вместо стрток



        for (auto it = tokens.begin(); it != tokens.end() && flag_status; ++it) {
            if (*it == "p") {
                doubleList.push_back(M_PI);
            } else if (is_string_number(*it)) {
                doubleList.push_back(std::stod(*it));
            } else if (*it == "x") {
                doubleList.push_back(std::stod(x));
            } else {
                double oper_result = 0.0;
                double operand2;
                if (!doubleList.empty()) {
                    operand2 = doubleList.back();
                    doubleList.pop_back();
                    if (isOperatorTwoParametrs(*it)) {
                        double operand1;
                        if (!doubleList.empty()) {
                            operand1 = doubleList.back();
                            doubleList.pop_back();
                            flag_status = doTwoOperator(*it, operand1, operand2, &oper_result);
                        } else {
                            std::cout << "Stack is empty, there is no operator in" << std::endl;
                            flag_status = false;
                        }
                    } else {
                        flag_status = doOneOperator(*it, operand2, &oper_result);
                    }
                } else {
                    std::cout << "Stack is empty, there is no operator in" << std::endl;
                    flag_status = false;
                }
                if (flag_status) {
                    doubleList.push_back(oper_result);
                }
            }
        }

        if (doubleList.size() != 1) {
            std::cout << "There is not enough operators or functions" << std::endl;
            flag_status = false;
        }

        if (!flag_status) {
            answer = ERROR;
        }

        return answer;
    }

    std::vector<std::string> Model::tokenizeString(const std::string &posifix) {
        std::vector<std::string> tokens;
        std::istringstream iss(posifix);
        std::string token;
        while (iss >> token) {
            tokens.push_back(token);
        }
        return tokens;
    }

    bool Model::isOperatorTwoParametrs(std::string &token) {
        return is_one_letter_operator(token[0]) || token == "mod";
    }

    bool Model::doTwoOperator(std::string &operat, double operand1, double operand2, double *answer) {
        bool flag_status = true;
        if (operat == "+") {
            *answer = operand1 + operand2;
        } else if (operat == "-") {
            *answer = operand1 - operand2;
        } else if (operat == "*") {
            *answer = operand1 * operand2;
        } else if (operat == "^") {
            if (is_correct_pow_arguments(operand1, operand2)) {
                *answer = std::pow(operand1, operand2);
            } else {
                std::cout << "There is not correct pow arguments" << std::endl;
                flag_status = false;
            }
        } else if (operat == "/") {
            if (operand2 == 0) {
                std::cout << "Error: division by zero" << std::endl;
                flag_status = false;
            } else {
                *answer = operand1 / operand2;
            }
        } else if (operat == "mod") {
            if (operand2 == 0) {
                std::cout << "Error: division by zero" << std::endl;
                flag_status = false;
            } else {
                *answer = std::fmod(operand1, operand2);
            }
        }
        return flag_status;
    }

    bool Model::is_correct_pow_arguments(double operand1, double operand2) const {
        bool flag_status = true;
        // 0 в отрицательной степени  возвращает бесконечность
        // возведение в дабловскую степень отрицательное число - -nan
        if ((operand1 == 0.0 && operand2 < 0.0) ||
            (operand1 < 0 && fabs(fmod(operand2, 1.0)) > s21_EPS_TEST)) {
            flag_status = false;
        }
        return flag_status;
    }

    bool Model::doOneOperator(std::string &operat, double operand, double *answer) const {
        bool flag_status = true;
        if (operat == "sin") {
            *answer = std::sin(operand);
        } else if (operat == "cos") {
            *answer = std::cos(operand);
        } else if (operat == "tan") {
            *answer = std::tan(operand);
        } else if (operat == "asin") {
            if (fabs(operand) - 1.0 > s21_EPS_TEST) {  // значения х могут быть только в диапазоне [-1;1]
                std::cout << "For a function x must be [-1;1]" << std::endl;
                flag_status = false;
            } else {
                *answer = std::asin(operand);
            }
        } else if (operat == "acos") {
            if (fabs(operand) - 1.0 > s21_EPS_TEST) {  // значения х могут быть только в диапазоне [-1;1]
                std::cout << "For a function x must be [-1;1]" << std::endl;
                flag_status = false;
            } else {
                *answer = std::acos(operand);
            }
        } else if (operat == "atan") {
            *answer = std::atan(operand);
        } else if (operat == "sqrt") {
            if (operand < 0) {  // аргументы должен быть положительным числом или 0
                std::cout << "X for sqrt must be greater than 0" << std::endl;
                flag_status = false;
            } else {
                *answer = std::sqrt(operand);
            }
        } else if (operat == "log") {
            if (operand < s21_EPS_TEST) {
                std::cout << "X must be greater than 0" << std::endl;
                flag_status = false;
            } else {
                *answer = std::log10(operand);
            }
        } else if (operat == "ln") {
            if (operand < s21_EPS_TEST) {
                std::cout << "X must be greater than 0" << std::endl;
                flag_status = false;
            } else {
                *answer = std::log(operand);
            }
        }
        return flag_status;
    }


} // s21