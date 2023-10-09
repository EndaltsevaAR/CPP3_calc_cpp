#include <cmath>
#include "Controller.h"

std::string s21::Controller::startCommonCalculator(const std::string &expression, const std::string &x) {
    return model.commonCalcStart(expression, x);
}

std::vector<double> s21::Controller::startCreditCalculator(int type, double sum_d, double time_d, double rate_d) {
    return model.creditCalcStart(type, sum_d, time_d, rate_d);
}