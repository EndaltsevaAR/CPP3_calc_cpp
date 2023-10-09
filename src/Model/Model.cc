#include <cmath>
#include <list>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "Model.h"

namespace s21 {
    const std::string Model::ERROR = "ERROR";
    const std::string Model::X = "3.14";

    std::vector<double>  Model::creditCalcStart(int type, double sum_d, double time_d, double rate_d) {
        std::vector<double> print_info;
        double pay_d, total_d, over_d;

        if (type == 1) { // annuitet
            pay_d = sum_d * (rate_d / (100 * 12) /
                                    (1 - std::pow(1 + rate_d / (100 * 12), -time_d)));
            total_d = time_d * pay_d;
            over_d = total_d - sum_d;
        } else {  // differ
            over_d = 0;
            double month_rate = rate_d / (100 * 12);
            double month_debt_pay = sum_d / time_d;
            double month_perc_pay = 0;
            pay_d = month_debt_pay + sum_d * month_rate;
            total_d = sum_d;
            for (int i = 0; i < time_d; i++) {
                month_perc_pay = sum_d * month_rate;
                over_d += month_perc_pay;
                sum_d = sum_d - month_debt_pay;
            }
            total_d += over_d;
        }
        print_info.push_back(pay_d);
        print_info.push_back(total_d);
        print_info.push_back(over_d);
        return print_info;
    }

    std::string Model::commonCalcStart(const std::string &expression, const std::string &x) {
        setlocale(LC_ALL, "en_US.UTF-8");

        if (expression.size() > STACK_SIZE) {
            std::cout << "Expression is too long!" << std::endl;
            return ERROR;
        }
        std::string answer = convertToPosifix(expression, x);
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
            char inf_letter = expression.at(infix_count);

            if (isdigit(inf_letter)) {
                handleDigit(posifix, expression, infix_count);
            } else if (inf_letter == '.') {
                flag_status = handleDote(posifix, expression, infix_count);
            } else if (inf_letter == 'x' || inf_letter == 'p') {
                flag_status = handleXP(posifix, x, inf_letter);
            } else if (inf_letter == '(') {
                operatorList.emplace_back("(");
            } else if (inf_letter == ')') {
                flag_status = findOpenBracket(posifix, operatorList, true);
            } else if (inf_letter == ' ') {
                continue;
            } else {
                flag_status = handleOperator(posifix, expression, infix_count, operatorList);
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

    void Model::handleDigit(std::string &posifix, const std::string &expression, size_t &infix_count) {
        posifix.push_back(expression.at(infix_count));
        if (isNextLetterDigitableOrEmpty(expression, infix_count)) {
            posifix.push_back(' ');
        }
    }

    bool Model::handleDote(std::string &posifix, const std::string &expression, size_t &infix_count) {
        bool status = true;
        if (infix_count > 0 && isdigit(expression.at(infix_count - 1)) && isdigit(expression.at(infix_count + 1))) {
            posifix.push_back(expression.at(infix_count));
        } else {
            std::cout << "Dote is not correct!" << std::endl;
            status = false;
        }
        return status;
    }

    bool Model::handleXP(std::string &posifix, const std::string &x, char inf_letter) {
        bool status = true;
        if (!isStringNumber(x)) {
            std::cout << "X is not correct!" << std::endl;
            status = false;
        } else {
            posifix.push_back(inf_letter);
            posifix.push_back(' ');
        }
        return status;
    }

    bool Model::handleOperator(std::string &posifix, const std::string &expression, size_t &infix_count,
                               std::list<std::string> &operatorList) {
        bool flag_status = true;
        std::string operat = isOperator(expression, infix_count);
        char inf_letter = expression.at(infix_count);
        if (operat != "!") {
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
        } else {
            std::cout << "Wrong input from user!" << std::endl;
            flag_status = false;
        }
        return flag_status;
    }

    std::string Model::calculateResult(const std::string &posifix, const std::string &x) {
        std::string answer = ERROR;
        bool flag_status = true;
        std::list<double> doubleList;
        std::vector<std::string> tokens = tokenizeString(posifix); // вместо стрток

        for (const auto &token : tokens) {
            if (flag_status) {
                if (token == "p") {
                    doubleList.push_back(M_PI);
                } else if (token == "x" || (token.size() > 1 && token.at(1) == 'x')) {
                    if (token.at(0) == '-') {
                        doubleList.push_back(-std::stod(x));
                    } else {
                        doubleList.push_back(std::stod(x));
                    }
                } else if (isStringNumber(token)) {
                    doubleList.push_back(std::stod(token));
                } else {
                    flag_status = calculateMagicWithOperator(const_cast<std::string &>(token), doubleList);
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
            answer = zeroIsZero(std::to_string(doubleList.back()));
        }
        return answer;
    }

    bool Model::calculateMagicWithOperator(std::string &token, std::list<double> &doubleList) {
        bool flag_status = true;
        double oper_result = 0.0, operand2 = 0.0;
        if (!doubleList.empty()) {
            operand2 = doubleList.back();
            doubleList.pop_back();
            if (isOperatorTwoParametrs(token)) {
                double operand1;
                if (!doubleList.empty()) {
                    operand1 = doubleList.back();
                    doubleList.pop_back();
                    flag_status = doTwoOperator(token, operand1, operand2, &oper_result);
                } else {
                    std::cout << "Stack is empty, there is no operator in" << std::endl;
                    flag_status = false;
                }
            } else {
                flag_status = doOneOperator(token, operand2, &oper_result);
            }
        } else {
            std::cout << "Stack is empty, there is no operator in" << std::endl;
            flag_status = false;
        }
        if (flag_status) {
            doubleList.push_back(oper_result);
        }
        return flag_status;
    }


    bool Model::isStringNumber(const std::string &expression) {
        bool is_number = true;
        bool has_dot = false;
        if (!(isdigit(expression.front()) || expression.front() == 'x' || (expression.front() == '-' && expression.size() != 1))) {
            is_number = false;
        }
        for (size_t i = 1; i < expression.size() && is_number; ++i) {
            if (expression.at(i) == '.' && !has_dot) {
                has_dot = true;
            } else if (!isdigit(expression.at(i))) {
                is_number = false;
            }
        }
        return is_number;
    }

    std::string Model::isOperator(const std::string &infix, size_t i) {
        std::string operat = "!";
        if (isOneLetterOperator(infix.at(i))) {
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
        if (infix.at(count) == '+' || infix.at(count) == '-') {
            if (((count > 0 && (isOneLetterOperator(infix.at(count - 1)) || infix.at(count - 1) == '(')) ||
                 count == 0) &&
                (count + 1 < infix.size() && (isdigit(infix.at(count + 1)) || infix.at(count + 1) == 'x' ||
                        infix.at(count + 1) == 'p'))) {
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
        return isOneLetterOperator(token.at(0)) || token == "mod";
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

    bool Model::isCorrectPowArguments(double operand1, double operand2) {
        bool flag_status = true;
        // 0 в отрицательной степени  возвращает бесконечность
        // возведение в дабловскую степень отрицательное число - -nan
        if ((operand1 == 0.0 && operand2 < 0.0) ||
            (operand1 < 0 && fabs(fmod(operand2, 1.0)) > s21_EPS_TEST)) {
            flag_status = false;
        }
        return flag_status;
    }

    bool Model::doOneOperator(std::string &operat, double operand, double *answer) {
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
                   (!(isdigit(infix.at(infix_count + 1)) || infix.at(infix_count + 1) == '.'))) {
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
            expression.erase(expression.begin());
        }
        return expression;
    }

} // s21