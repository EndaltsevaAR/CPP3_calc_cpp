#ifndef CALC_CPP_CONTROLLER_H
#define CALC_CPP_CONTROLLER_H

#include <list>
#include <string>
#include <vector>

#include "../Model/Model.h"

namespace s21 {

    class Controller {
    public:
        explicit Controller();

        std::string startCommonCalculator(const std::string &expression, const std::string &x);

        ~Controller();

    private:
        s21::Model *model;
    };


} // s21

#endif //CALC_CPP_CONTROLLER_H
