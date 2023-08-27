#include <gtest/gtest.h>

#include <vector>
#include <list>
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

#define X "3.14"

#include "Model.h" // Подключите ваш заголовочный файл Model.h

using namespace s21; // Подставьте правильное пространство имён

class ModelTest : public testing::Test {
protected:
    Model model; // Создание экземпляра Model, который будет использоваться во всех тестах
};

// common operations
// good tests
TEST_F(ModelTest, s21_calc_just_numb_test) {
    std::string expression = "2";
    std::string result = model.commonCalcStart(expression, X);
    EXPECT_EQ(result, "2.0000000");
}

TEST_F(ModelTest, s21_calc_request_test) {
    std::string expression = "(2+2*2+2+2*2+2+2*2)/3";
    std::string result = model.commonCalcStart(expression, X);
    EXPECT_EQ(result, "6.0000000");
}

TEST_F(ModelTest, s21_calc_just_x_test) {
    std::string expression = "x";
    std::string result = model.commonCalcStart(expression, X);
    EXPECT_EQ(result, "3.1400000");
}

TEST_F(ModelTest, s21_calc_simple_add_test) {
    std::string expression = "2+1";
    std::string result = model.commonCalcStart(expression, X);
    EXPECT_EQ(result, "3.0000000");
}

TEST_F(ModelTest, s21_calc_simple_add_minus_numb_test) {
    std::string expression = "-2+1";
    std::string result = model.commonCalcStart(expression, X);
    EXPECT_EQ(result, "-1.0000000");
}

TEST_F(ModelTest, s21_calc_spaces_test) {
    std::string expression = "2 +1";
    std::string result = model.commonCalcStart(expression, X);
    EXPECT_EQ(result, "3.0000000");
}

TEST_F(ModelTest, s21_calc_more_spaces_test) {
    std::string expression = "2 + 1 ";
    std::string result = model.commonCalcStart(expression, X);
    EXPECT_EQ(result, "3.0000000");
}

TEST_F(ModelTest, s21_calc_start_spaces_test) {
    std::string expression = " 2 + 1 ";
    std::string result = model.commonCalcStart(expression, X);
    EXPECT_EQ(result, "3.0000000");
}

TEST_F(ModelTest, s21_calc_simple_add_big_number_test) {
    std::string expression = "12+1";
    std::string result = model.commonCalcStart(expression, X);
    EXPECT_EQ(result, "13.0000000");
}

TEST_F(ModelTest, s21_calc_simple_add_extra_number_test) {
    std::string expression = "12345+12345";
    std::string result = model.commonCalcStart(expression, X);
    EXPECT_EQ(result, "24690.0000000");
}

TEST_F(ModelTest, s21_calc_simple_mult_extra_number_test) {
    std::string expression = "12345*12345";
    std::string result = model.commonCalcStart(expression, X);
    EXPECT_EQ(result, "152399025.0000000");
}

TEST_F(ModelTest, s21_calc_simple_sub_test) {
    std::string expression = "2-1";
    std::string result = model.commonCalcStart(expression, X);
    EXPECT_EQ(result, "1.0000000");
}

TEST_F(ModelTest, s21_calc_simple_sub_minus_numb_test) {
    std::string expression = "-2-1";
    std::string result = model.commonCalcStart(expression, X);
    EXPECT_EQ(result, "-3.0000000");
}

TEST_F(ModelTest, s21_calc_simple_mult_test) {
    std::string expression = "2*3";
    std::string result = model.commonCalcStart(expression, X);
    EXPECT_EQ(result, "6.0000000");
}

TEST_F(ModelTest, s21_calc_simple_mult_minus_numb_test) {
    std::string expression = "-2*3";
    std::string result = model.commonCalcStart(expression, X);
    EXPECT_EQ(result, "-6.0000000");
}

TEST_F(ModelTest, s21_calc_simple_mult_minus_minus_numb_test) {
    std::string expression = "-2*-3";
    std::string result = model.commonCalcStart(expression, X);
    EXPECT_EQ(result, "6.0000000");
}

TEST_F(ModelTest, s21_calc_simple_div_test) {
    std::string expression = "6/3";
    std::string result = model.commonCalcStart(expression, X);
    EXPECT_EQ(result, "2.0000000");
}

TEST_F(ModelTest, s21_calc_simple_div_minus_numb_test) {
    std::string expression = "-6/3";
    std::string result = model.commonCalcStart(expression, X);
    EXPECT_EQ(result, "-2.0000000");
}

TEST_F(ModelTest, s21_calc_x_letter_test) {
    std::string expression = "x+1";
    std::string result = model.commonCalcStart(expression, X);
    EXPECT_EQ(result, "4.1400000");
}

TEST_F(ModelTest, s21_calc_x_2_test) {
    std::string expression = "x+1";
    std::string x = "2";
    std::string result = model.commonCalcStart(expression, x);
    EXPECT_EQ(result, "3.0000000");
}

TEST_F(ModelTest, s21_calc_simple_brackets_test) {
    std::string expression = "(1+2)";
    std::string result = model.commonCalcStart(expression, X);
    EXPECT_EQ(result, "3.0000000");
}

TEST_F(ModelTest, s21_calc_complicated_brackets_test) {
    std::string expression = "(1+2)*3";
    std::string result = model.commonCalcStart(expression, X);
    EXPECT_EQ(result, "9.0000000");
}

TEST_F(ModelTest, s21_calc_more_complicated_brackets_test) {
    std::string expression = "(1+2)*3+1";
    std::string result = model.commonCalcStart(expression, X);
    EXPECT_EQ(result, "10.0000000");
}

TEST_F(ModelTest, s21_calc_double_brackets_test) {
    std::string expression = "((x))";
    std::string result = model.commonCalcStart(expression, X);
    EXPECT_EQ(result, "3.1400000");
}

TEST_F(ModelTest, s21_calc_double_add_test) {
    std::string expression = "1.1+1";
    std::string result = model.commonCalcStart(expression, X);
    EXPECT_EQ(result, "2.1000000");
}

TEST_F(ModelTest, s21_calc_two_double_add_test) {
    std::string expression = "1.1+2.2";
    std::string result = model.commonCalcStart(expression, X);
    EXPECT_EQ(result, "3.3000000");
}

TEST_F(ModelTest, s21_calc_simple_unar_plus_test) {
    std::string expression = "2++3";
    std::string result = model.commonCalcStart(expression, X);
    EXPECT_EQ(result, "5.0000000");
}

TEST_F(ModelTest, s21_calc_unar_plus_test) {
    std::string expression = "2+(+3)";
    std::string result = model.commonCalcStart(expression, X);
    EXPECT_EQ(result, "5.0000000");
}

TEST_F(ModelTest, s21_calc_simple_unar_minus_test) {
    std::string expression = "2+-3";
    std::string result = model.commonCalcStart(expression, X);
    EXPECT_EQ(result, "-1.0000000");
}

TEST_F(ModelTest, s21_calc_unar_minus_test) {
    std::string expression = "2+(-3)";
    std::string result = model.commonCalcStart(expression, X);
    EXPECT_EQ(result, "-1.0000000");
}

TEST_F(ModelTest, s21_calc_simple_unar_minus_sub_test) {
    std::string expression = "2--3";
    std::string result = model.commonCalcStart(expression, X);
    EXPECT_EQ(result, "5.0000000");
}

TEST_F(ModelTest, s21_calc_simple_unar_minus_sub_x_test) {
    std::string expression = "2--x";
    std::string result = model.commonCalcStart(expression, X);
    EXPECT_EQ(result, "5.1400000");
}

TEST_F(ModelTest, s21_calc_unar_minus_sub_x_test) {
    std::string expression = "2+(-x)";
    std::string result = model.commonCalcStart(expression, X);
    EXPECT_EQ(result, "-1.1400000");
}

TEST_F(ModelTest, s21_calc_all_oper_test) {
    std::string expression = "1+2*(4+1)/2.5";
    std::string result = model.commonCalcStart(expression, X);
    EXPECT_EQ(result, "5.0000000");
}

TEST_F(ModelTest, s21_calc_div_small_test) {
    std::string expression = "1 / 0.0000000001";
    std::string result = model.commonCalcStart(expression, X);
    EXPECT_EQ(result, "10000000000.0000000");
}

// wrong tests

TEST_F(ModelTest, s21_calc_just_letter_test) {
    std::string expression = "u";
    std::string result = model.commonCalcStart(expression, X);
    EXPECT_EQ(result, s21::Model::ERROR);
}

TEST_F(ModelTest, s21_calc_just_operator_test) {
    std::string expression = "+";
    std::string result = model.commonCalcStart(expression, X);
    EXPECT_EQ(result, s21::Model::ERROR);
}

TEST_F(ModelTest, s21_calc_wrong_letter_test) {
    std::string expression = "2+y";
    std::string result = model.commonCalcStart(expression, X);
    EXPECT_EQ(result, s21::Model::ERROR);
}

TEST_F(ModelTest, s21_calc_div_0_test) {
    std::string expression = "1/0";
    std::string result = model.commonCalcStart(expression, X);
    EXPECT_EQ(result, s21::Model::ERROR);
}

TEST_F(ModelTest, s21_calc_wrong_add_test) {
    std::string expression = "1+";
    std::string result = model.commonCalcStart(expression, X);
    EXPECT_EQ(result, s21::Model::ERROR);
}

TEST_F(ModelTest, s21_calc_wrong_open_bracket_test) {
    std::string expression = "(1+2";
    std::string result = model.commonCalcStart(expression, X);
    EXPECT_EQ(result, s21::Model::ERROR);
}

TEST_F(ModelTest, s21_calc_wrong_close_bracket_test) {
    std::string expression = "1+2)";
    std::string result = model.commonCalcStart(expression, X);
    EXPECT_EQ(result, s21::Model::ERROR);
}

TEST_F(ModelTest, s21_calc_wrong_compl_double_bracket_test) {
    std::string expression = "(())";
    std::string result = model.commonCalcStart(expression, X);
    EXPECT_EQ(result, s21::Model::ERROR);
}

TEST_F(ModelTest, s21_calc_wrong_compl_bracket_test) {
    std::string expression = "((x)))(";
    std::string result = model.commonCalcStart(expression, X);
    EXPECT_EQ(result, s21::Model::ERROR);
}

TEST_F(ModelTest, s21_calc_opposite_bracket_test) {
    std::string expression = ")1+2(";
    std::string result = model.commonCalcStart(expression, X);
    EXPECT_EQ(result, s21::Model::ERROR);
}

TEST_F(ModelTest, s21_calc_opposite_bracket_empty_test) {
    std::string expression = ")(";
    std::string result = model.commonCalcStart(expression, X);
    EXPECT_EQ(result, s21::Model::ERROR);
}

TEST_F(ModelTest, s21_calc_comma_test) {
    std::string expression = "1,1+1";
    std::string result = model.commonCalcStart(expression, X);
    EXPECT_EQ(result, s21::Model::ERROR);
}

TEST_F(ModelTest, s21_calc_comma_one_number_test) {
    std::string expression = "1,1+";
    std::string result = model.commonCalcStart(expression, X);
    EXPECT_EQ(result, s21::Model::ERROR);
}

TEST_F(ModelTest, s21_calc_two_dots_test) {
    std::string expression = "1..1 + 1";
    std::string result = model.commonCalcStart(expression, X);
    EXPECT_EQ(result, s21::Model::ERROR);
}

TEST_F(ModelTest, s21_calc_wrong_dot_start_test) {
    std::string expression = ".1 + 1";
    std::string result = model.commonCalcStart(expression, X);
    EXPECT_EQ(result, s21::Model::ERROR);
}

TEST_F(ModelTest, s21_calc_wrong_letter_a_test) {
    std::string expression = "1a+1";
    std::string result = model.commonCalcStart(expression, X);
    EXPECT_EQ(result, s21::Model::ERROR);
}

TEST_F(ModelTest, s21_calc_wrong_operator_test) {
    std::string expression = "2?3";
    std::string result = model.commonCalcStart(expression, X);
    EXPECT_EQ(result, s21::Model::ERROR);
}

TEST_F(ModelTest, s21_calc_start_operator_test) {
    std::string expression = "/3";
    std::string result = model.commonCalcStart(expression, X);
    EXPECT_EQ(result, s21::Model::ERROR);
}

TEST_F(ModelTest, s21_calc_x_wrong_test) {
    std::string expression = "x+1";
    std::string result = model.commonCalcStart(expression, X);
    EXPECT_EQ(result, s21::Model::ERROR);
}

// sin
TEST_F(ModelTest, s21_calc_sin_cos_1_test) {
    std::string expression1 = "sin(x)";
    std::string expression2 = "cos(x)";
    for (double number = -2 * M_PI; number <= 2 * M_PI; number += M_PI_2) {
        std::string x = std::to_string(number);
        std::string result1 = model.commonCalcStart(expression1, x);
        std::string result2 = model.commonCalcStart(expression2, x);
        EXPECT_EQ(result1, std::to_string(std::sin(number)));
        EXPECT_EQ(result2, std::to_string(std::cos(number)));
    }
}

TEST_F(ModelTest, s21_calc_sin_cos_2_test) {
    std::string expression1 = "sin(x)";
    std::string expression2 = "cos(x)";
    for (double number = -100.0; number <= 100.0; number += 0.5) {
        std::string x = std::to_string(number);
        std::string result1 = model.commonCalcStart(expression1, x);
        std::string result2 = model.commonCalcStart(expression2, x);
        EXPECT_EQ(result1, std::to_string(std::sin(number)));
        EXPECT_EQ(result2, std::to_string(std::cos(number)));
    }
}

TEST_F(ModelTest, s21_calc_sin_cos_3_test) {
    std::string expression1 = "sin(12345.87654321)";
    std::string expression2 = "cos(12345.87654321)";
    std::string result1 = model.commonCalcStart(expression1, X);
    std::string result2 = model.commonCalcStart(expression2, X);
    EXPECT_EQ(result1, std::to_string(sin(12345.87654321)));
    EXPECT_EQ(result2, std::to_string(cos(12345.87654321)));
}

TEST_F(ModelTest, s21_calc_sin_cos_4_test) {
    std::string expression1 = "sin(x)";
    std::string expression2 = "cos(x)";
    std::string x = std::to_string(M_PI * 100);
    std::string result1 = model.commonCalcStart(expression1, x);
    std::string result2 = model.commonCalcStart(expression2, x);
    EXPECT_EQ(result1, std::to_string(sin(M_PI * 100)));
    EXPECT_EQ(result2, std::to_string(cos(M_PI * 100)));
}

TEST_F(ModelTest, s21_calc_sin_cos_5_test) {
    std::string expression1 = "sin(x)";
    std::string expression2 = "cos(x)";
    std::string x = std::to_string(-M_PI * 100);
    std::string result1 = model.commonCalcStart(expression1, x);
    std::string result2 = model.commonCalcStart(expression2, x);
    EXPECT_EQ(result1, std::to_string(sin(-M_PI * 100)));
    EXPECT_EQ(result2, std::to_string(cos(-M_PI * 100)));
}

TEST_F(ModelTest, s21_calc_sin_cos_6_test) {
    std::string expression1 = "sin(1234567891.234567)";
    std::string expression2 = "cos(1234567891.234567)";
    std::string result1 = model.commonCalcStart(expression1, X);
    std::string result2 = model.commonCalcStart(expression2, X);
    EXPECT_EQ(result1, std::to_string(sin(1234567891.234567)));
    EXPECT_EQ(result2, std::to_string(cos(1234567891.234567)));
}

TEST_F(ModelTest, s21_calc_sin_cos_7_test) {
    std::string expression1 = "sin(-1234567891.234567)";
    std::string expression2 = "cos(-1234567891.234567)";
    std::string result1 = model.commonCalcStart(expression1, X);
    std::string result2 = model.commonCalcStart(expression2, X);
    EXPECT_EQ(result1, std::to_string(sin(-1234567891.234567)));
    EXPECT_EQ(result2, std::to_string(cos(-1234567891.234567)));
}

TEST_F(ModelTest, s21_calc_sin_cos_8_test) {
    std::string expression1 = "sin(x)";
    std::string expression2 = "cos(x)";
    for (double number = 0.1; number < 1.0; number += 0.123456) {
        std::string x = std::to_string(number);
        std::string result1 = model.commonCalcStart(expression1, x);
        std::string result2 = model.commonCalcStart(expression2, x);
        EXPECT_EQ(result1, std::to_string(std::sin(number)));
        EXPECT_EQ(result2, std::to_string(std::cos(number)));
    }
}

TEST_F(ModelTest, s21_calc_sin_9_test) {
    std::string expression1 = "sin(x)";
    std::string expression2 = "cos(x)";
    for (double number = -1.0; number < 0.0; number += 0.123456) {
        std::string x = std::to_string(number);
        std::string result1 = model.commonCalcStart(expression1, x);
        std::string result2 = model.commonCalcStart(expression2, x);
        EXPECT_EQ(result1, std::to_string(std::sin(number)));
        EXPECT_EQ(result2, std::to_string(std::cos(number)));
    }
}

TEST_F(ModelTest, s21_calc_sin_cos_10_test) {
    std::string expression1 = "si(1)";
    std::string expression2 = "co(1)";
    std::string result1 = model.commonCalcStart(expression1, X);
    std::string result2 = model.commonCalcStart(expression2, X);
    EXPECT_EQ(result1, s21::Model::ERROR);
    EXPECT_EQ(result2, s21::Model::ERROR);
}

// asin
TEST_F(ModelTest, s21_calc_asin_acos_1_test) {
    std::string expression1 = "asin(x)";
    std::string expression2 = "acos(x)";
    for (double number = -2 * M_PI; number <= 2 * M_PI; number += M_PI_2) {
        std::string x = std::to_string(number);
        std::string result1 = model.commonCalcStart(expression1, x);
        std::string result2 = model.commonCalcStart(expression2, x);
        std::string answer1 = s21::Model::ERROR;
        std::string answer2 = s21::Model::ERROR;
        if (std::fabs(number) < 1) {
            answer1 = std::to_string(std::asin(number));
            answer2 = std::to_string(std::acos(number));
        }
        EXPECT_EQ(result1, answer1);
        EXPECT_EQ(result2, answer2);
    }
}

TEST_F(ModelTest, s21_calc_asin_acos_2_test) {
    std::string expression1 = "asin(x)";
    std::string expression2 = "acos(x)";
    for (double number = -100.0; number <= 100.0; number += 0.5) {
        std::string x = std::to_string(number);
        std::string result1 = model.commonCalcStart(expression1, x);
        std::string result2 = model.commonCalcStart(expression2, x);
        std::string answer1 = s21::Model::ERROR;
        std::string answer2 = s21::Model::ERROR;
        if (std::fabs(number) < 1) {
            answer1 = std::to_string(std::asin(number));
            answer2 = std::to_string(std::acos(number));
        }
        EXPECT_EQ(result1, answer1);
        EXPECT_EQ(result2, answer2);
    }
}

TEST_F(ModelTest, s21_calc_asin_acos_3_test) {
    std::string expression1 = "asin(12345.87654321)";
    std::string expression2 = "acos(12345.87654321)";
    std::string result1 = model.commonCalcStart(expression1, X);
    std::string result2 = model.commonCalcStart(expression2, X);
    EXPECT_EQ(result1, s21::Model::ERROR);
    EXPECT_EQ(result2, s21::Model::ERROR);
}

TEST_F(ModelTest, s21_calc_asin_acos_4_test) {
    std::string expression1 = "asin(x)";
    std::string expression2 = "acos(x)";
    std::string x = std::to_string(M_PI * 100);
    std::string result1 = model.commonCalcStart(expression1, x);
    std::string result2 = model.commonCalcStart(expression2, x);
    EXPECT_EQ(result1, s21::Model::ERROR);
    EXPECT_EQ(result2, s21::Model::ERROR);
}

TEST_F(ModelTest, s21_calc_asin_acos_5_test) {
    std::string expression1 = "asin(x)";
    std::string expression2 = "acos(x)";
    std::string x = std::to_string(-M_PI * 100);
    std::string result1 = model.commonCalcStart(expression1, x);
    std::string result2 = model.commonCalcStart(expression2, x);
    EXPECT_EQ(result1, s21::Model::ERROR);
    EXPECT_EQ(result2, s21::Model::ERROR);
}

TEST_F(ModelTest, s21_calc_asin_acos_6_test) {
    std::string expression1 = "asin(1234567891.234567)";
    std::string expression2 = "acos(1234567891.234567)";
    std::string result1 = model.commonCalcStart(expression1, X);
    std::string result2 = model.commonCalcStart(expression2, X);
    EXPECT_EQ(result1, s21::Model::ERROR);
    EXPECT_EQ(result2, s21::Model::ERROR);
}

TEST_F(ModelTest, s21_calc_asin_acos_7_test) {
    std::string expression1 = "asin(-1234567891.234567)";
    std::string expression2 = "acos(-1234567891.234567)";
    std::string result1 = model.commonCalcStart(expression1, X);
    std::string result2 = model.commonCalcStart(expression2, X);
    EXPECT_EQ(result1, s21::Model::ERROR);
    EXPECT_EQ(result2, s21::Model::ERROR);
}

TEST_F(ModelTest, s21_calc_asin_acos_8_test) {
    std::string expression1 = "asin(x)";
    std::string expression2 = "acos(x)";
    for (double number = 0.1; number < 1.0; number += 0.123456) {
        std::string x = std::to_string(number);
        std::string result1 = model.commonCalcStart(expression1, x);
        std::string result2 = model.commonCalcStart(expression2, x);
        EXPECT_EQ(result1, std::to_string(std::asin(number)));
        EXPECT_EQ(result2, std::to_string(std::acos(number)));
    }
}

TEST_F(ModelTest, s21_calc_asin_acos_9_test) {
    std::string expression1 = "asin(x)";
    std::string expression2 = "acos(x)";
    for (double number = -1.0; number < 0.0; number += 0.123456) {
        std::string x = std::to_string(number);
        std::string result1 = model.commonCalcStart(expression1, x);
        std::string result2 = model.commonCalcStart(expression2, x);
        EXPECT_EQ(result1, std::to_string(std::asin(number)));
        EXPECT_EQ(result2, std::to_string(std::acos(number)));
    }
}

TEST_F(ModelTest, s21_calc_asin_acos_10_test) {
    std::string expression1 = "asi(1)";
    std::string expression2 = "aco(1)";
    std::string result1 = model.commonCalcStart(expression1, X);
    std::string result2 = model.commonCalcStart(expression2, X);
    EXPECT_EQ(result1, s21::Model::ERROR);
    EXPECT_EQ(result2, s21::Model::ERROR);
}

// tan
TEST_F(ModelTest, s21_calc_tan_0_test) {
    std::string expression = "tan(0)";
    std::string result = model.commonCalcStart(expression, X);
    EXPECT_EQ(result, std::to_string(std::tan(0)));
}

TEST_F(ModelTest, s21_calc_tan_atan_1_test) {
    std::string expression1 = "tan(x)";
    std::string expression2 = "atan(x)";
    for (double number = -2 * M_PI; number <= 2 * M_PI; number += M_PI_2) {
        std::string x = std::to_string(number);
        std::string result1 = model.commonCalcStart(expression1, x);
        std::string result2 = model.commonCalcStart(expression2, x);
        EXPECT_EQ(result1, std::to_string(std::tan(number)));
        EXPECT_EQ(result2, std::to_string(std::atan(number)));
    }
}

TEST_F(ModelTest, s21_calc_tan_atan_2_test) {
    std::string expression1 = "tan(x)";
    std::string expression2 = "atan(x)";
    for (double number = -100.0; number <= 100.0; number += 0.5) {
        std::string x = std::to_string(number);
        std::string result1 = model.commonCalcStart(expression1, x);
        std::string result2 = model.commonCalcStart(expression2, x);
        EXPECT_EQ(result1, std::to_string(std::tan(number)));
        EXPECT_EQ(result2, std::to_string(std::atan(number)));
    }
}

TEST_F(ModelTest, s21_calc_tan_atan_3_test) {
    std::string expression1 = "tan(12345.87654321)";
    std::string expression2 = "atan(12345.87654321)";
    std::string result1 = model.commonCalcStart(expression1, X);
    std::string result2 = model.commonCalcStart(expression2, X);
    EXPECT_EQ(result1, std::to_string(std::tan(12345.87654321)));
    EXPECT_EQ(result2, std::to_string(std::atan(12345.87654321)));
}

TEST_F(ModelTest, s21_calc_tan_4_test) {
    std::string expression1 = "tan(x)";
    std::string expression2 = "atan(x)";
    std::string x = std::to_string(M_PI * 100);
    std::string result1 = model.commonCalcStart(expression1, x);
    std::string result2 = model.commonCalcStart(expression2, x);
    EXPECT_EQ(result1, std::to_string(std::tan(M_PI * 100)));
    EXPECT_EQ(result2, std::to_string(std::atan(M_PI * 100)));
}

TEST_F(ModelTest, s21_calc_tan_atan_5_test) {
    std::string expression1 = "tan(x)";
    std::string expression2 = "atan(x)";
    std::string x = std::to_string(-M_PI * 100);
    std::string result1 = model.commonCalcStart(expression1, x);
    std::string result2 = model.commonCalcStart(expression2, x);
    EXPECT_EQ(result1, std::to_string(std::tan(-M_PI * 100)));
    EXPECT_EQ(result2, std::to_string(std::atan(-M_PI * 100)));
}

TEST_F(ModelTest, s21_calc_tan_atan_6_test) {
    std::string expression1 = "tan(1234567891.234567)";
    std::string expression2 = "atan(1234567891.234567)";
    std::string result1 = model.commonCalcStart(expression1, X);
    std::string result2 = model.commonCalcStart(expression2, X);
    EXPECT_EQ(result1, s21::Model::ERROR);
    EXPECT_EQ(result2, s21::Model::ERROR);
}

TEST_F(ModelTest, s21_calc_tan_atan_7_test) {
    std::string expression1 = "tan(-1234567891.234567)";
    std::string expression2 = "atan(-1234567891.234567)";
    std::string result1 = model.commonCalcStart(expression1, X);
    std::string result2 = model.commonCalcStart(expression2, X);
    EXPECT_EQ(result1, s21::Model::ERROR);
    EXPECT_EQ(result2, s21::Model::ERROR);
}

TEST_F(ModelTest, s21_calc_tan_atan_8_test) {
    std::string expression1 = "tan(x)";
    std::string expression2 = "atan(x)";
    for (double number = 0.1; number < 1.0; number += 0.123456) {
        std::string x = std::to_string(number);
        std::string result1 = model.commonCalcStart(expression1, x);
        std::string result2 = model.commonCalcStart(expression2, x);
        EXPECT_EQ(result1, std::to_string(std::tan(number)));
        EXPECT_EQ(result2, std::to_string(std::atan(number)));
    }
}

TEST_F(ModelTest, s21_calc_tan_atan_9_test) {
    std::string expression1 = "tan(x)";
    std::string expression2 = "atan(x)";
    for (double number = -1.0; number < 0.0; number += 0.123456) {
        std::string x = std::to_string(number);
        std::string result1 = model.commonCalcStart(expression1, x);
        std::string result2 = model.commonCalcStart(expression2, x);
        EXPECT_EQ(result1, std::to_string(std::tan(number)));
        EXPECT_EQ(result2, std::to_string(std::atan(number)));
    }
}

TEST_F(ModelTest, s21_calc_tan_atan_10_test) {
    std::string expression1 = "ta(x)";
    std::string expression2 = "ata(x)";
    std::string result1 = model.commonCalcStart(expression1, X);
    std::string result2 = model.commonCalcStart(expression2, X);
    EXPECT_EQ(result1, s21::Model::ERROR);
    EXPECT_EQ(result2, s21::Model::ERROR);
}

// log + ln

TEST_F(ModelTest, s21_calc_log_ln_1_test) {
    std::string expression1 = "log(1.0)";
    std::string expression2 = "ln(1.0)";
    std::string result1 = model.commonCalcStart(expression1, X);
    std::string result2 = model.commonCalcStart(expression2, X);
    EXPECT_EQ(result1, std::to_string(std::log10(1.0)));
    EXPECT_EQ(result2, std::to_string(std::log(1.0)));
}

TEST_F(ModelTest, s21_calc_log_ln_2_test) {
    std::string expression1 = "log(-1.0)";
    std::string expression2 = "ln(-1.0)";
    std::string result1 = model.commonCalcStart(expression1, X);
    std::string result2 = model.commonCalcStart(expression2, X);
    EXPECT_EQ(result1, s21::Model::ERROR);
    EXPECT_EQ(result2, s21::Model::ERROR);
}

TEST_F(ModelTest, s21_calc_log_ln3_test) {
    std::string expression1 = "log(2147483646.0)";
    std::string expression2 = "ln(2147483646.0)";
    std::string result1 = model.commonCalcStart(expression1, X);
    std::string result2 = model.commonCalcStart(expression2, X);
    EXPECT_EQ(result1, s21::Model::ERROR);
    EXPECT_EQ(result2, s21::Model::ERROR);
}

TEST_F(ModelTest, s21_calc_log_ln_4_test) {
    std::string expression1 = "log(-2147483646.0)";
    std::string expression2 = "ln(-2147483646.0)";
    std::string result1 = model.commonCalcStart(expression1, X);
    std::string result2 = model.commonCalcStart(expression2, X);
    EXPECT_EQ(result1, s21::Model::ERROR);
    EXPECT_EQ(result2, s21::Model::ERROR);
}

TEST_F(ModelTest, s21_calc_log_ln_5_test) {
    std::string expression1 = "log(0.0)";
    std::string expression2 = "ln(0.0)";
    std::string result1 = model.commonCalcStart(expression1, X);
    std::string result2 = model.commonCalcStart(expression2, X);
    EXPECT_EQ(result1, s21::Model::ERROR);
    EXPECT_EQ(result2, s21::Model::ERROR);
}

TEST_F(ModelTest, s21_calc_log_ln_6_test) {
    std::string expression1 = "log(-1.123456)";
    std::string expression2 = "ln(-1.123456)";
    std::string result1 = model.commonCalcStart(expression1, X);
    std::string result2 = model.commonCalcStart(expression2, X);
    EXPECT_EQ(result1, s21::Model::ERROR);
    EXPECT_EQ(result2, s21::Model::ERROR);
}

TEST_F(ModelTest, s21_calc_log_ln_7_test) {
    std::string expression1 = "log(1.123456)";
    std::string expression2 = "ln(1.123456)";
    std::string result1 = model.commonCalcStart(expression1, X);
    std::string result2 = model.commonCalcStart(expression2, X);
    EXPECT_EQ(result1, std::to_string(std::log10(1.123456)));
    EXPECT_EQ(result2, std::to_string(std::log(1.123456)));
}

TEST_F(ModelTest, s21_calc_log_ln_8_test) {
    std::string expression1 = "log(x)";
    std::string expression2 = "ln(x)";
    for (double number = 0.1; number < 1.0; number += 0.123456) {
        std::string x = std::to_string(number);
        std::string result1 = model.commonCalcStart(expression1, x);
        std::string result2 = model.commonCalcStart(expression2, x);
        EXPECT_EQ(result1, std::to_string(std::log10(number)));
        EXPECT_EQ(result2, std::to_string(std::log(number)));
    }
}

TEST_F(ModelTest, s21_calc_log_9_test) {
    std::string expression1 = "log(x)";
    std::string expression2 = "ln(x)";
    for (double number = -1.0; number < 0.0; number += 0.123456) {
        std::string x = std::to_string(number);
        std::string result1 = model.commonCalcStart(expression1, x);
        std::string result2 = model.commonCalcStart(expression2, x);
        EXPECT_EQ(result1, s21::Model::ERROR);
        EXPECT_EQ(result2, s21::Model::ERROR);
    }
}

// sqrt
TEST_F(ModelTest, s21_calc_sqrt_1_test) {
    std::string expression = "sqrt(1.0)";
    std::string result = model.commonCalcStart(expression, X);
    EXPECT_EQ(result, std::to_string(std::sqrt(1.0)));
}

TEST_F(ModelTest, s21_calc_sqrt_2_test) {
    std::string expression = "sqrt(-1.0)";
    std::string result = model.commonCalcStart(expression, X);
    EXPECT_EQ(result, s21::Model::ERROR);
}

TEST_F(ModelTest, s21_calc_sqrt_3_test) {
    std::string expression = "sqrt(2147483646.0)";
    std::string result = model.commonCalcStart(expression, X);
    EXPECT_EQ(result, s21::Model::ERROR);
}

TEST_F(ModelTest, s21_calc_sqrt_4_test) {
    std::string expression = "sqrt(-2147483646.0)";
    std::string result = model.commonCalcStart(expression, X);
    EXPECT_EQ(result, s21::Model::ERROR);
}

TEST_F(ModelTest, s21_calc_sqrt_5_test) {
    std::string expression = "sqrt(0.0)";
    std::string result = model.commonCalcStart(expression, X);
    EXPECT_EQ(result, std::to_string(std::sqrt(0.0)));
}

TEST_F(ModelTest, s21_calc_sqrt_6_test) {
    std::string expression = "sqrt(-1.123456)";
    std::string result = model.commonCalcStart(expression, X);
    EXPECT_EQ(result, s21::Model::ERROR);
}

TEST_F(ModelTest, s21_calc_sqrt_7_test) {
    std::string expression = "sqrt(1.123456)";
    std::string result = model.commonCalcStart(expression, X);
    EXPECT_EQ(result, std::to_string(std::sqrt(1.123456)));
}

TEST_F(ModelTest, s21_calc_sqrt_8_test) {
    std::string expression = "sqrt(x)";
    for (double number = 0.1; number < 1.0; number += 0.123456) {
        std::string x = std::to_string(number);
        std::string result = model.commonCalcStart(expression, x);
        EXPECT_EQ(result, std::to_string(std::sqrt(number)));
    }
}

TEST_F(ModelTest, s21_calc_sqrt_9_test) {
    std::string expression = "sqrt(x)";
    for (double number = -1.0; number < 0.0; number += 0.123456) {
        std::string x = std::to_string(number);
        std::string result = model.commonCalcStart(expression, x);
        EXPECT_EQ(result, s21::Model::ERROR);
    }
}

// mod

TEST_F(ModelTest, s21_calc_mod_1_test) {
    std::string expression = "1 mod x";
    for (double number = 0.1; number < 1.0; number += 0.123456) {
        std::string x = std::to_string(number);
        std::string result = model.commonCalcStart(expression, x);
        EXPECT_EQ(result, std::to_string(std::fmod(1.0, number)));
    }
}

TEST_F(ModelTest, s21_calc_mod_2_test) {
    std::string expression = "0.0mod1.0";
    std::string result = model.commonCalcStart(expression, X);
    EXPECT_EQ(result, std::to_string(std::fmod(0.0, 1.0)));
}

TEST_F(ModelTest, s21_calc_mod_3_test) {
    std::string expression = "0.0 mod 0.0";
    std::string result = model.commonCalcStart(expression, X);
    EXPECT_EQ(result, s21::Model::ERROR);
}

TEST_F(ModelTest, s21_calc_mod_4_test) {
    std::string expression = "1.0 mod 0.0";
    std::string result = model.commonCalcStart(expression, X);
    EXPECT_EQ(result, std::to_string(std::fmod(1.0, 0.0)));
}

TEST_F(ModelTest, s21_calc_mod_5_test) {
    std::string expression = "0 mod x";
    for (double number = 2.0; number < 1000.0; number += 123) {
        std::string x = std::to_string(number);
        std::string result = model.commonCalcStart(expression, x);
        EXPECT_EQ(result, std::to_string(std::fmod(0.0, number)));
    }
}

TEST_F(ModelTest, s21_calc_mod_6_test) {
    std::string expression = "x mod 0";
    for (double number = 2.0; number < 1000.0; number += 123) {
        std::string x = std::to_string(number);
        std::string result = model.commonCalcStart(expression, x);
        EXPECT_EQ(result, s21::Model::ERROR);
    }
}

TEST_F(ModelTest, s21_calc_mod_7_test) {
    std::string expression = "0 mod x";
    for (double number = 2.0; number < 1000.0; number += 123.456789) {
        std::string x = std::to_string(number);
        std::string result = model.commonCalcStart(expression, x);
        EXPECT_EQ(result, std::to_string(std::fmod(0.0, number)));
    }
}

TEST_F(ModelTest, s21_calc_mod_8_test) {
    std::string expression = "x mod 0";
    for (double number = 2.0; number < 1000.0; number += 123.456789) {
        std::string x = std::to_string(number);
        std::string result = model.commonCalcStart(expression, x);
        EXPECT_EQ(result, s21::Model::ERROR);
    }
}

TEST_F(ModelTest, s21_calc_mod_9_test) {
    std::string expression = "0 mod x";
    for (double number = -1000.0; number < 0.0; number += 123) {
        std::string x = std::to_string(number);
        std::string result = model.commonCalcStart(expression, x);
        EXPECT_EQ(result, std::to_string(std::fmod(0.0, number)));
    }
}

TEST_F(ModelTest, s21_calc_mod_10_test) {
    std::string expression = "x mod 0";
    for (double number = -1000.0; number < 0.0; number += 123) {
        std::string x = std::to_string(number);
        std::string result = model.commonCalcStart(expression, x);
        EXPECT_EQ(result, s21::Model::ERROR);
    }
}

TEST_F(ModelTest, s21_calc_mod_11_test) {
    std::string expression = "0 mod x";
    for (double number = -1000.0; number < 0.0; number += 123.456789) {
        std::string x = std::to_string(number);
        std::string result = model.commonCalcStart(expression, x);
        EXPECT_EQ(result, std::to_string(std::fmod(0.0, number)));
    }
}

TEST_F(ModelTest, s21_calc_mod_12_test) {
    std::string expression = "x mod 0";
    for (double number = -1000.0; number < 0.0; number += 123.456789) {
        std::string x = std::to_string(number);
        std::string result = model.commonCalcStart(expression, x);
        EXPECT_EQ(result, s21::Model::ERROR);
    }
}

TEST_F(ModelTest, s21_calc_mod_13_test) {
    std::string expression = "0 mod x";
    for (double number = -1.0; number < 0.0; number += 0.123456) {
        std::string x = std::to_string(number);
        std::string result = model.commonCalcStart(expression, x);
        EXPECT_EQ(result, std::to_string(std::fmod(0.0, number)));
    }
}

TEST_F(ModelTest, s21_calc_mod_14_test) {
    std::string expression = "x mod 0";
    for (double number = -1.0; number < 0.0; number += 0.123456) {
        std::string x = std::to_string(number);
        std::string result = model.commonCalcStart(expression, x);
        EXPECT_EQ(result, s21::Model::ERROR);
    }
}

TEST_F(ModelTest, s21_calc_mod_15_test) {
    std::string expression = "0 mod x";
    for (double number = 0.1; number < 1.0; number += 0.123456) {
        std::string x = std::to_string(number);
        std::string result = model.commonCalcStart(expression, x);
        EXPECT_EQ(result, std::to_string(std::fmod(0.0, number)));
    }
}

TEST_F(ModelTest, s21_calc_mod_16_test) {
    std::string expression = "x mod 0";
    for (double number = 0.1; number < 1.0; number += 0.123456) {
        std::string x = std::to_string(number);
        std::string result = model.commonCalcStart(expression, x);
        EXPECT_EQ(result, s21::Model::ERROR);
    }
}

TEST_F(ModelTest, s21_calc_mod_17_test) {
    std::string expression = "0 mod x";
    std::string x = "1234567891.234567";
    std::string result = model.commonCalcStart(expression, x);
    EXPECT_EQ(result, std::to_string(std::fmod(0.0, 1234567891.234567)));
}

TEST_F(ModelTest, s21_calc_mod_18_test) {
    std::string expression = "x mod 0";
    std::string x = "1234567891.234567";
    std::string result = model.commonCalcStart(expression, x);
    EXPECT_EQ(result, s21::Model::ERROR);
}

TEST_F(ModelTest, s21_calc_mod_19_test) {
    std::string expression = "0 mod x";
    std::string x = "-1234567891.234567";
    std::string result = model.commonCalcStart(expression, x);
    EXPECT_EQ(result, std::to_string(std::fmod(0.0, -1234567891.234567)));
}

TEST_F(ModelTest, s21_calc_mod_20_test) {
    std::string expression = "x mod 0";
    std::string x = "-1234567891.234567";
    std::string result = model.commonCalcStart(expression, x);
    EXPECT_EQ(result, s21::Model::ERROR);
}

TEST_F(ModelTest, s21_calc_mod_21_test) {
    std::string expression = "1 mod x";
    std::string x = "1234567891.234567";
    std::string result = model.commonCalcStart(expression, x);
    EXPECT_EQ(result, std::to_string(std::fmod(1.0, 1234567891.234567)));
}

TEST_F(ModelTest, s21_calc_mod_22_test) {
    std::string expression = "x mod 1";
    std::string x = "1234567891.234567";
    std::string result = model.commonCalcStart(expression, x);
    EXPECT_EQ(result, std::to_string(std::fmod(1234567891.234567, 1.0)));
}

TEST_F(ModelTest, s21_calc_mod_23_test) {
    std::string expression = "1 mod x";
    std::string x = "-1234567891.234567";
    std::string result = model.commonCalcStart(expression, x);
    EXPECT_EQ(result, std::to_string(std::fmod(1.0, -1234567891.234567)));
}

TEST_F(ModelTest, s21_calc_mod_24_test) {
    std::string expression = "x mod 1";
    std::string x = "-1234567891.234567";
    std::string result = model.commonCalcStart(expression, x);
    EXPECT_EQ(result, std::to_string(std::fmod(-1234567891.234567, 1.0)));
}

TEST_F(ModelTest, s21_calc_mod_25_test) {
    std::string expression = "md(1)";
    std::string result = model.commonCalcStart(expression, X);
    EXPECT_EQ(result, s21::Model::ERROR);
}



int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}