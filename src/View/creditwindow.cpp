#include "creditwindow.h"

#include <QKeyEvent>
#include <QLabel>
#include <cmath>
#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <vector>

#include "../Controller/Controller.h"
#include "ui_creditwindow.h"

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
  std::vector<double> print_info;
  int is_ok = 1;
  QString sum_text = ui->line_sum->text();
  QString time_text = ui->line_time->text();
  QString rate_text = ui->line_rate->text();

  if (sum_text == "") {
    sum_text = INIT_SUM;
  }
  if (time_text == "") {
    time_text = INIT_TIME;
  }
  if (rate_text == "") {
    rate_text = INIT_RATE;
  }

  if (is_string_digitable(sum_text) && is_string_digitable(sum_text) &&
      is_string_digitable(sum_text)) {
    double sum_d = sum_text.toDouble();
    double time_d = time_text.toDouble();
    double rate_d = rate_text.toDouble();

    int is_time_int = (std::floor(time_d) == time_d);  // check time is integer

    if (sum_d > 0 && time_d > 0 && rate_d > 0 && is_time_int) {
      s21::Controller controller;

      QString key_text = event->text();

      if (ui->radio_type_annuitet->isChecked()) {
        print_info = controller.startCreditCalculator(1, sum_d, time_d, rate_d);
      } else if (ui->radio_type_diff->isChecked()) {
        print_info = controller.startCreditCalculator(2, sum_d, time_d, rate_d);
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
  } else {
    print_results(print_info);
  }
}

int CreditWindow::is_string_digitable(const QString& expression) {
  bool isDouble;
  expression.toDouble(&isDouble);
  return isDouble;
}

void CreditWindow::print_results(
    std::vector<double> print_info) {  // pay_d - 0, total_d - 1, over_d - 2
  QString pay_text = QString::number(print_info.at(0), 'f', 2);
  ui->label_pay_enter->setText(pay_text);

  QString total_text = QString::number(print_info.at(1), 'f', 2);
  ui->label_total_pay_enter->setText(total_text);

  QString over_text = QString::number(print_info.at(2), 'f', 2);
  ui->label_overpay_enter->setText(over_text);

  int progress = (int)(100 - print_info.at(2) * 100 / print_info.at(1));
  ui->progress_pay->setValue(progress);
}
