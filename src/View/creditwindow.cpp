#include "creditwindow.h"

#include <QKeyEvent>
#include <QLabel>

#include <vector>
#include <list>
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

#include "ui_creditwindow.h"
#include "../Controller/Controller.h"

#define INIT_SUM "1000"
#define INIT_RATE "9.5"
#define INIT_TIME "12"
#define INIT_FREE_SUM "1000000"
#define INIT_CB_TAX "7.5"
#define INIT_TAX_RATE "13"

CreditWindow::CreditWindow(QWidget* parent)
    : QDialog(parent), ui(new Ui::CreditWindow) {
  ui->setupUi(this);
}

CreditWindow::~CreditWindow() { delete ui; }

void CreditWindow::keyPressEvent(QKeyEvent* event) {
  int is_ok = 1;
  QString sum_text = ui->line_sum->text();
  QString time_text = ui->line_time->text();
  QString rate_text = ui->line_rate->text();

  if (is_string_digitable(sum_text) && is_string_digitable(sum_text) &&
      is_string_digitable(sum_text)) {
    if (sum_text == "") {
      sum_text = INIT_SUM;
    }
    if (time_text == "") {
      time_text = INIT_TIME;
    }
    if (rate_text == "") {
      rate_text = INIT_RATE;
    }

    double sum_d = sum_text.toDouble();
    double time_d = time_text.toDouble();
    double rate_d = rate_text.toDouble();

    int is_time_int = (std::floor(time_d) == time_d);  // check time is integer

    if (sum_d > 0 && time_d > 0 && rate_d > 0 && is_time_int) {
      QString key_text = event->text();

      if (ui->radio_type_annuitet->isChecked()) {
        annuitet_type(sum_d, time_d, rate_d);
      } else if (ui->radio_type_diff->isChecked()) {
        differ_type(sum_d, time_d, rate_d);
      }
    } else {  // if input date are negative
      is_ok = 0;
    }
  } else {  // if input date are incorrect
    is_ok = 0;
  }

  if (!is_ok) {
    ui->label_pay_enter->setText("ERROR");
    ui->label_total_pay_enter->setText("ERROR");
    ui->label_overpay_enter->setText("ERROR");
    ui->progress_pay->setValue(100);
  }
}

int CreditWindow::is_string_digitable(const QString& expression) {
    std::cout << expression.size();
    return 0;
    /*
  QByteArray byteArray = expression.toUtf8();
  char* charArray = byteArray.data();
  return is_string_number(charArray);
  */
}
/*
char* CreditWindow::double_to_string(double number) {
  char buffer[STACK_SIZE];
  std::sprintf(buffer, "%.2f", number);
  char* charResult = buffer;
  return charResult;
}
*/
void CreditWindow::print_results(double pay_d, double total_d, double over_d) {
  QString pay_text = QString::number(pay_d, 'f', 2);
  ui->label_pay_enter->setText(pay_text);

  QString total_text = QString::number(total_d, 'f', 2);
  ui->label_total_pay_enter->setText(total_text);

  QString over_text = QString::number(over_d, 'f', 2);
  ui->label_overpay_enter->setText(over_text);

  int progress = (int)(100 - over_d * 100 / total_d);
  ui->progress_pay->setValue(progress);
}

void CreditWindow::annuitet_type(double sum_d, double time_d, double rate_d) {
  double pay_d = sum_d * (rate_d / (100 * 12) /
                          (1 - std::pow(1 + rate_d / (100 * 12), -time_d)));
  double total_d = time_d * pay_d;
  double over_d = total_d - sum_d;
  print_results(pay_d, total_d, over_d);
}

void CreditWindow::differ_type(double sum_d, double time_d, double rate_d) {
  double over_d = 0;
  double month_rate = rate_d / (100 * 12);
  double month_debt_pay = sum_d / time_d;
  double month_perc_pay = 0;
  double pay_d = month_debt_pay + sum_d * month_rate;
  double total_d = sum_d;
  for (int i = 0; i < time_d; i++) {
    month_perc_pay = sum_d * month_rate;
    over_d += month_perc_pay;
    sum_d = sum_d - month_debt_pay;
  }
  total_d += over_d;
  print_results(pay_d, total_d, over_d);
}
