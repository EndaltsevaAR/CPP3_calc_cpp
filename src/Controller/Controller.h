#ifndef CALC_CPP_CONTROLLER_H
#define CALC_CPP_CONTROLLER_H

#include <list>
#include <string>
#include <vector>

#include "../Model/Model.h"

namespace s21 {

class Controller {
 public:
  std::string startCommonCalculator(const std::string &expression,
                                    const std::string &x);

  std::vector<double> startCreditCalculator(int type, double sum_d,
                                            double time_d, double rate_d);

 private:
  s21::Model model;
};
}  // namespace s21

#endif  // CALC_CPP_CONTROLLER_H
