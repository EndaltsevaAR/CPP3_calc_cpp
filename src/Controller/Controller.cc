#include "Controller.h"

namespace s21 {

    Controller::Controller() {
        model = new s21::Model();
    }

    Controller::~Controller() = default;

    std::string Controller::startCommonCalculator(const std::string &expression, const std::string &x) {
        return model->commonCalcStart(expression, x);
    }

} // s21