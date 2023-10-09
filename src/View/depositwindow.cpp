#include <vector>
#include <list>
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

#include "depositwindow.h"

#include "ui_depositwindow.h"
#include "../Controller/Controller.h"

#define INIT_SUM "1000"
#define INIT_RATE "9.5"
#define INIT_TIME "12"
#define INIT_FREE_SUM "1000000"
#define INIT_CB_TAX "7.5"
#define INIT_TAX_RATE "13"

DepositWindow::DepositWindow(QWidget *parent)
    : QDialog(parent), ui(new Ui::DepositWindow) {
  ui->setupUi(this);

  ui->date_input->setDate(QDate::currentDate());
  ui->date_output->setDate(QDate::currentDate());

  ui->date_refill_1->setMinimumDate(ui->date_input->date());
  ui->date_refill_2->setMinimumDate(ui->date_input->date());
  ui->date_refill_3->setMinimumDate(ui->date_input->date());

  ui->date_cut_1->setMinimumDate(ui->date_input->date());
  ui->date_cut_2->setMinimumDate(ui->date_input->date());
  ui->date_cut_3->setMinimumDate(ui->date_input->date());
}

DepositWindow::~DepositWindow() { delete ui; }

void DepositWindow::on_push_deposit_calc_clicked() {

  int sum_error = 1, time_error = 1, rate_error = 1, tax_rate_error = 1;
  QString sum_text =
      check_argument(ui->line_sum->text(), INIT_SUM, 0, &sum_error);
  QString time_text =
      check_argument(ui->line_time->text(), INIT_TIME, 1, &time_error);
  QString rate_text =
      check_argument(ui->line_rate->text(), INIT_RATE, 0, &rate_error);
  QString tax_rate_text = check_argument(ui->line_tax_rate->text(),
                                         INIT_TAX_RATE, 0, &tax_rate_error);

  if (sum_error && time_error && rate_error && tax_rate_error) {
    QDate input_date = ui->date_input->date();
    QDate output_date = input_date.addMonths(time_text.toInt());

    double sum_d = sum_text.toDouble();
    double rate_d = rate_text.toDouble();
    double tax_rate_d = tax_rate_text.toDouble();

    double free_sum_d = calc_free_sum();

    // refill prepart
    int refill_errors[3] = {0};
    QDate next_refill_date_1, next_refill_date_2, next_refill_date_3;
    QDate refill_next_dates[] = {
        next_refill_date_1, next_refill_date_2,
        next_refill_date_3};  //  int refill_error_1, refill_error_2,
                              //  refill_error_3;

    QString refill_sum_1 =
        check_argument(ui->line_refill_sum->text(), "", 0, &refill_errors[0]);
    QString refill_sum_2 =
        check_argument(ui->line_refill_sum_2->text(), "", 0, &refill_errors[1]);
    QString refill_sum_3 =
        check_argument(ui->line_refill_sum_3->text(), "", 0, &refill_errors[2]);
    QString refill_sums[] = {refill_sum_1, refill_sum_2, refill_sum_3};

    QDate refill_date_1 = ui->date_refill_1->date();
    QDate refill_date_2 = ui->date_refill_2->date();
    QDate refill_date_3 = ui->date_refill_3->date();
    QDate refill_start_dates[] = {refill_date_1, refill_date_2, refill_date_3};

    QString refill_period = ui->combo_periodicity_refill_1->currentText();
    QString refill_period_2 = ui->combo_periodicity_refill_2->currentText();
    QString refill_period_3 = ui->combo_periodicity_refill_3->currentText();
    QString refill_periods[] = {refill_period, refill_period_2,
                                refill_period_3};

    for (int i = 0; i < 3; i++) {
      if (refill_errors[i]) {
        is_date_over(refill_start_dates[i], &refill_errors[i], output_date);
      }
      if (refill_errors[i]) {
        refill_next_dates[i] = refill_start_dates[i];
      }
    }

    // cut prepart
    int cut_errors[3] = {0};
    QDate next_cut_date_1, next_cut_date_2, next_cut_date_3;
    QDate cut_next_dates[] = {
        next_cut_date_1, next_cut_date_2,
        next_cut_date_3};  //  int refill_error_1, refill_error_2,
                           //  refill_error_3;

    QString cut_sum_1 =
        check_argument(ui->line_cut_sum_1->text(), "", 0, &cut_errors[0]);
    QString cut_sum_2 =
        check_argument(ui->line_cut_sum_2->text(), "", 0, &cut_errors[1]);
    QString cut_sum_3 =
        check_argument(ui->line_cut_sum_3->text(), "", 0, &cut_errors[2]);
    QString cut_sums[] = {cut_sum_1, cut_sum_2, cut_sum_3};

    QDate cut_date_1 = ui->date_cut_1->date();
    QDate cut_date_2 = ui->date_cut_2->date();
    QDate cut_date_3 = ui->date_cut_3->date();
    QDate cut_start_dates[] = {cut_date_1, cut_date_2, cut_date_3};

    QString cut_period = ui->combo_periodicity_cut_1->currentText();
    QString cut_period_2 = ui->combo_periodicity_cut_2->currentText();
    QString cut_period_3 = ui->combo_periodicity_cut_3->currentText();
    QString cut_periods[] = {cut_period, cut_period_2, cut_period_3};

    for (int i = 0; i < 3; i++) {
      if (cut_errors[i]) {
        is_date_over(cut_start_dates[i], &cut_errors[i], output_date);
      }
      if (cut_errors[i]) {
        cut_next_dates[i] = cut_start_dates[i];
      }
    }

    // main part
    if (!ui->check_capitalization->isChecked()) {  // without capitalization
      calc_without_capitalization(
          sum_d, rate_d, tax_rate_d, free_sum_d, input_date, output_date,
          refill_errors, refill_next_dates, refill_sums, refill_periods,
          cut_errors, cut_next_dates, cut_sums, cut_periods);
    } else {
      calc_with_capitalization(
          sum_d, rate_d, tax_rate_d, free_sum_d, input_date, output_date,
          refill_errors, refill_next_dates, refill_sums, refill_periods,
          cut_errors, cut_next_dates, cut_sums, cut_periods);
    }
    ui->date_output->setDate(output_date);
  } else {
    ui->label_calc_perc_enter->setText("ERROR");
    ui->label_calc_sum_tax_enter->setText("ERROR");
    ui->label_calc_total_sum_perc_enter->setText("ERROR");
  }

}

QString DepositWindow::check_argument(QString param_text, QString init_string,
                                      int is_int_check_need, int *error_flag) {
  *error_flag = 1;
  if (param_text == "") {
    param_text = init_string;
  }

  if (!is_string_digitable(param_text) || param_text == "") {
    *error_flag = 0;
  }

  double param_d = param_text.toDouble();

  if (*error_flag &&
      (param_d < 0 || (is_int_check_need && !is_param_int(param_d)))) {
    *error_flag = 0;
  }
  return param_text;
}

int DepositWindow::is_param_int(double param_d) {
  return (std::floor(param_d) == param_d);  // check time is integer
}

int DepositWindow::is_string_digitable(const QString &expression) {
    std::cout << expression.size();
    return 0;
    /*
  QByteArray byteArray = expression.toUtf8();
  char *charArray = byteArray.data();
  return is_string_number(charArray);
  */
}

void DepositWindow::is_date_over(QDate refill_start_date, int *error,
                                 QDate output_date) {
  *error = refill_start_date <= output_date;
}

void DepositWindow::calc_without_capitalization(
    double sum_d, double rate_d, double tax_rate_d, double free_sum_d,
    QDate input_date, QDate output_date, int refill_errors[],
    QDate refill_next_dates[], QString refill_sums[], QString refill_periods[],
    int cut_errors[], QDate cut_next_dates[], QString cut_sums[],
    QString cut_periods[]) {
  double perc = 0;

  while (input_date < output_date) {
    if (QDate::isLeapYear(input_date.year())) {
      perc += sum_d * rate_d / (366 * 100);
    } else {
      perc += sum_d * rate_d / (365 * 100);
    }

    // for refill
    for (int i = 0; i < 3; i++) {
      if (refill_errors[i] && input_date == refill_next_dates[i]) {
        sum_d += refill_sums[i].toDouble();
        if (refill_periods[i] != "Разовое") {
          refill_next_dates[i] =
              get_periodicity(refill_periods[i], refill_next_dates[i]);
        }
      }
    }

    // for cut
    for (int i = 0; i < 3; i++) {
      if (cut_errors[i] && input_date == cut_next_dates[i]) {
        sum_d -= cut_sums[i].toDouble();
        if (cut_periods[i] != "Разовое") {
          cut_next_dates[i] =
              get_periodicity(cut_periods[i], cut_next_dates[i]);
        }
      }
    }

    input_date = input_date.addDays(1);
  }
  double tax = perc - free_sum_d;
  if (tax > 0) {
    tax *= tax_rate_d / 100;
  } else {
    tax = 0;
  }
  double total = perc - tax;
  print_results(perc, tax, total);
}

void DepositWindow::calc_with_capitalization(
    double sum_d, double rate_d, double tax_rate_d, double free_sum_d,
    QDate input_date, QDate output_date, int refill_errors[],
    QDate refill_next_dates[], QString refill_sums[], QString refill_periods[],
    int cut_errors[], QDate cut_next_dates[], QString cut_sums[],
    QString cut_periods[]) {
  double perc = 0;
  double time_perc = 0;
  ;
  QString period = ui->combo_periodicity->currentText();
  QDate next_date;

  next_date = get_periodicity(period, input_date);
  while (input_date < output_date) {
    if (input_date == next_date) {
      sum_d += time_perc;
      next_date = get_periodicity(period, input_date);
      time_perc = 0;
    }

    double today_perc = 0;

    if (QDate::isLeapYear(input_date.year())) {
      today_perc = sum_d * rate_d / (366 * 100);
    } else {
      today_perc = sum_d * rate_d / (365 * 100);
    }
    perc += today_perc;
    time_perc += today_perc;

    // for refill
    for (int i = 0; i < 3; i++) {
      if (refill_errors[i] && input_date == refill_next_dates[i]) {
        sum_d += refill_sums[i].toDouble();
        if (refill_periods[i] != "Разовое") {
          refill_next_dates[i] =
              get_periodicity(refill_periods[i], refill_next_dates[i]);
        }
      }
    }

    // for cut
    for (int i = 0; i < 3; i++) {
      if (cut_errors[i] && input_date == cut_next_dates[i]) {
        sum_d -= cut_sums[i].toDouble();
        if (cut_periods[i] != "Разовое") {
          cut_next_dates[i] =
              get_periodicity(cut_periods[i], cut_next_dates[i]);
        }
      }
    }
    input_date = input_date.addDays(1);
  }

  double tax = perc - free_sum_d;
  if (tax > 0) {
    tax *= tax_rate_d / 100;
  } else {
    tax = 0;
  }
  double total = perc - tax;
  print_results(perc, tax, total);
}

double DepositWindow::calc_free_sum() {
  QString free_sum_text = ui->line_sum_free_tax->text();
  QString cb_rate_text = ui->line_cb_rate->text();

  double sum_d = 0;
  double rate_d = 0;

  if (!is_string_digitable(free_sum_text) || free_sum_text == "" ||
      free_sum_text.toDouble() < 0) {
    free_sum_text = INIT_FREE_SUM;
  }

  if (!is_string_digitable(cb_rate_text) || cb_rate_text == "" ||
      cb_rate_text.toDouble() < 0) {
    cb_rate_text = INIT_CB_TAX;
  }

  QDate input_date = ui->date_input->date();
  QDate output_date = input_date.addMonths(12);
  // ui->date_output->setDate(output_date);
  int start_year = input_date.year();
  int end_year = output_date.year();

  sum_d = free_sum_text.toDouble();
  rate_d = cb_rate_text.toDouble();
  double free_total_sum = sum_d * rate_d / 100;
  ui->line_total_free_sum->setText(QString::number(free_total_sum));

  return (end_year - start_year + 1) * free_total_sum;
}

void DepositWindow::print_results(double perc, double tax, double total) {
  QString perc_text = QString::number(perc, 'f', 2);
  ui->label_calc_perc_enter->setText(perc_text);

  QString tax_text = QString::number(tax, 'f', 2);
  ui->label_calc_sum_tax_enter->setText(tax_text);

  QString total_text = QString::number(total, 'f', 2);
  ui->label_calc_total_sum_perc_enter->setText(total_text);
}

QDate DepositWindow::get_periodicity(QString period, QDate input_date) {
  QDate next_date;
  if (period == "Ежедневно") {
    next_date = input_date.addDays(1);
  } else if (period == "Раз в неделю") {
    next_date = input_date.addDays(7);
  } else if (period == "Раз в месяц") {
    next_date = input_date.addMonths(1);
  } else if (period == "Раз в квартал") {
    next_date = input_date.addMonths(3);
  } else if (period == "Раз в год") {
    next_date = input_date.addYears(1);
  }
  return next_date;
}
