#include <vector>
#include <list>
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

#include "Model.h"

namespace s21 {
    const std::string Model::ERROR = "ERROR";

    std::string Model::commonCalcStart(const std::string &expression, const std::string &x) {
        setlocale(LC_ALL, "en_US.UTF-8");
        if (expression.size() > STACK_SIZE) {
            std::cout << "Expression is too long!" << std::endl;
            return ERROR;
        }
        std::string  answer = convertToPosifix(expression, x);
        if (answer != ERROR) {
            answer = calculateResult(answer, x);
        }
        return answer;
    }

    std::string Model::convertToPosifix(const std::string &expression, const std::string &x) {
        bool flag_status = true;
        std::string posifix;
        std::list<std::string> operatorList;

        for (size_t infix_count = 0; infix_count < expression.size() && flag_status; ++infix_count) {
            char inf_letter = expression[infix_count];

            if (isdigit(inf_letter)) { // digit check
                posifix.push_back(inf_letter);
                if (isNextLetterDigitableOrEmpty(expression, infix_count)) {
                    posifix.push_back(' ');
                }
            } else if (inf_letter == '.') {
                if (infix_count > 0 && isdigit(expression[infix_count - 1]) && isdigit(expression[infix_count + 1])) {
                    posifix.push_back(inf_letter);
                } else {
                    std::cout << "Dote is not correct!" << std::endl;
                    flag_status = false;
                }
            } else if (inf_letter == 'x' || inf_letter == 'p') {
                if (!isStringNumber(x)) {
                    std::cout << "X is not correct!" << std::endl;
                    flag_status = false;
                } else {
                    posifix.push_back(inf_letter);
                    posifix.push_back(' ');
                }
            } else if (inf_letter == '(') {
                operatorList.emplace_back("(");
            } else if (inf_letter == ')') {
                flag_status = findOpenBracket(posifix, operatorList, true);
            } else if (inf_letter == ' ') {
                continue;
            } else {
                flag_status = handleOperator(posifix, expression, infix_count, operatorList);
                /*
                std::string operat = isOperator(expression, infix_count);
                if (operat != "!") { // операторы
                    if (isUnarOperator(expression, infix_count)) {
                        if (operat == "-") {
                            posifix.push_back(inf_letter);
                        }
                    } else if (operat == "^") {
                        while (!operatorList.empty() && getPriority(operat) < getPriority(operatorList.back())) {
                            popTopOperation(posifix, operatorList);
                        }
                        operatorList.emplace_back(operat);
                    } else {
                        while (!operatorList.empty() && getPriority(operat) <= getPriority(operatorList.back())) {
                            popTopOperation(posifix, operatorList);
                        }
                        operatorList.emplace_back(operat);
                    }
                    infix_count += operat.size() - 1;
                } else { // ничего не подходит
                    std::cout << "Wrong input from user!" << std::endl;
                    flag_status = false;
                }
                 */
            }
        }

        if (flag_status && !operatorList.empty()) {
            flag_status = findOpenBracket(posifix, operatorList, false);
        }

        if (!flag_status) {
            posifix = ERROR;
        }
        return posifix;
    }

    std::string Model::calculateResult(const std::string &posifix, const std::string &x) {
        std::string answer = ERROR;
        int flag_status = true;
        std::list<double> doubleList;

        std::vector<std::string> tokens = tokenizeString(posifix); // вместо стрток

        for (auto it = tokens.begin(); it != tokens.end() && flag_status; ++it) {
            if (*it == "p") {
                doubleList.push_back(M_PI);
            } else if (*it == "x" || (it->size() > 1 && it->at(1) == 'x')) {
                if (it->at(0) == '-') {
                    doubleList.push_back(-std::stod(x));
                } else {
                    doubleList.push_back(std::stod(x));
                }
            } else if (isStringNumber(*it)) {
                doubleList.push_back(std::stod(*it));
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

        if (doubleList.size() != 1 && flag_status) {
            std::cout << "There is not enough operators or functions" << std::endl;
            flag_status = false;
        }

        if (!flag_status) {
            answer = ERROR;
        } else {
            answer = std::to_string(doubleList.back());
            answer = zeroIsZero(answer);
        }

        return answer;
    }

    bool Model::handleOperator(std::string& posifix, const std::string& expression, size_t& infix_count, std::list<std::string>& operatorList) {
        bool flag_status = true;
        std::string operat = isOperator(expression, infix_count);
        char inf_letter = expression[infix_count];
        if (operat != "!") { // операторы
            if (isUnarOperator(expression, infix_count)) {
                if (operat == "-") {
                    posifix.push_back(inf_letter);
                }
            } else if (operat == "^") {
                while (!operatorList.empty() && getPriority(operat) < getPriority(operatorList.back())) {
                    popTopOperation(posifix, operatorList);
                }
                operatorList.emplace_back(operat);
            } else {
                while (!operatorList.empty() && getPriority(operat) <= getPriority(operatorList.back())) {
                    popTopOperation(posifix, operatorList);
                }
                operatorList.emplace_back(operat);
            }
            infix_count += operat.size() - 1;
        } else { // ничего не подходит
            std::cout << "Wrong input from user!" << std::endl;
            flag_status = false;
        }
        return flag_status;
    }

    bool Model::isStringNumber(const std::string &expression) {
        bool is_number = true;
        bool has_dot = false;
        if (!(isdigit(expression[0]) || expression[0] == 'x' || (expression[0] == '-' && expression.size() != 1))) {
            is_number = false;
        }
        for (size_t i = 1; i < expression.size() && is_number; ++i) {
            if (expression[i] == '.' && !has_dot) {
                has_dot = true;
            } else if (!isdigit(expression[i])) {
                is_number = false;
            }
        }
        return is_number;
    }

    std::string Model::isOperator(const std::string &infix, size_t i) {
        std::string operat = "!";
        if (isOneLetterOperator(infix[i])) {
            operat = infix.substr(i, 1);
        } else {
            operat = getFunction(infix, i);
        }
        return operat;
    }

    bool Model::isOneLetterOperator(const char &letter) {
        return (letter == '+' || letter == '-' || letter == '*'
                || letter == '/' || letter == '%' || letter == '^');
    }

    std::string Model::getFunction(const std::string &infix, size_t i) {
        std::string operat = "!";
        bool is_find = false;
        for (size_t funcLength = 4; funcLength >= 2 && !is_find; --funcLength) {
            if (infix.size() - i >= funcLength) {
                std::string subInfix = infix.substr(i, funcLength);
                if (isEngineeringFunction(subInfix) || subInfix == "mod") {
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
            if (((count > 0 && (isOneLetterOperator(infix[count - 1]) || infix[count - 1] == '(')) ||
                 count == 0) &&
                (count + 1 < infix.size() && (isdigit(infix[count + 1]) || infix[count + 1] == 'x' ||
                                              infix[count + 1] == 'p'))) {
                isUnar = true;
            }
        }
        return isUnar;
    }

    bool Model::isEngineeringFunction(const std::string &operat) {
        return operat == "sin" || operat == "cos" || operat == "tan" || operat == "acos" || operat == "asin" ||
               operat == "atan" || operat == "ln" || operat == "log" || operat == "sqrt";
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
        return isOneLetterOperator(token[0]) || token == "mod";
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
            if (isCorrectPowArguments(operand1, operand2)) {
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
                *answer = 1.0 * operand1 / operand2;
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

    bool Model::isCorrectPowArguments(double operand1, double operand2) const {
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
        if (std::fabs(operand) > MAX_NUMBER) {  //  область определения от -1000000 до 1000000
            std::cout << "X for function  is too much small/big" << std::endl;
            flag_status = false;
        } else if (operat == "sin") {
            *answer = std::sin(operand);
        } else if (operat == "cos") {
            *answer = std::cos(operand);
        } else if (operat == "tan") {
            *answer = std::tan(operand);
        } else if (operat == "asin" || operat == "acos") {
            if (fabs(operand) - 1.0 > s21_EPS_TEST) {  // значения х могут быть только в диапазоне [-1;1]
                std::cout << "For a function x must be [-1;1]" << std::endl;
                flag_status = false;
            } else {
                if (operat == "asin") *answer = std::asin(operand);
                else *answer = std::acos(operand);
            }
        } else if (operat == "atan") {
            *answer = std::atan(operand);
        } else if (operat == "sqrt" || operat == "log" || operat == "ln") {
            if (operand < 0) {
                std::cout << "X must be greater than 0" << std::endl;
                flag_status = false;
            } else {
                if (operat == "sqrt") *answer = std::sqrt(operand);
                else if (operat == "log") *answer = std::log10(operand);
                else *answer = std::log(operand);
            }
        }

        if (flag_status && std::fabs(*answer) > MAX_NUMBER) {
            std::cout << "Result of one of function  is too much small/big" << std::endl;
            flag_status = false;
        }
        return flag_status;
    }

    bool Model::isNextLetterDigitableOrEmpty(const std::string &infix, size_t infix_count) {
        bool status = false;
        if (infix_count == infix.size() - 1) {
            status = true;
        } else if (infix_count + 1 < infix.size() &&
                   (!(isdigit(infix[infix_count + 1]) || infix[infix_count + 1] == '.'))) {
            status = true;
        }
        return status;
    }

    bool Model::findOpenBracket(std::string &posifix, std::list<std::string> &operatorList, bool isCloseBracket) {
        bool status = true;
        bool isOpenBracket = false;
        while (!operatorList.empty() && status && !isOpenBracket) {
            std::string last_operator = operatorList.back();
            if (last_operator == "(") {
                if (!isCloseBracket) {
                    std::cout << "You have problem with brackets!" << std::endl;
                    status = false;
                }
                isOpenBracket = true;
            } else {
                posifix.append(last_operator);
                posifix.push_back(' ');
            }
            operatorList.pop_back();
        }
        if (isCloseBracket) {
            if (operatorList.empty() && !isOpenBracket) {
                std::cout << "You have problem with brackets!" << std::endl;
                status = false;
            }
        }
        return status;
    }

    void Model::popTopOperation(std::string &posifix, std::list<std::string> &operatorList) {
        posifix.append(operatorList.back());
        posifix.push_back(' ');
        operatorList.pop_back();
    }

    std::string Model::zeroIsZero(std::string expression) {
        if (expression == "-0.000000") {
            expression = "0.000000";
        }
        return expression;
    }

} // s21