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






int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}