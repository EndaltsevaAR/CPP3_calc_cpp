#ifndef DEPOSITWINDOW_H
#define DEPOSITWINDOW_H

#include <QDate>
#include <QDialog>
#include <QTextStream>
#include <QTime>

#include "../Controller/Controller.h"

namespace Ui {
class DepositWindow;
}

class DepositWindow : public QDialog {
  Q_OBJECT

 public:
  explicit DepositWindow(QWidget *parent = nullptr);
  ~DepositWindow();

 protected:
  int is_string_digitable(const QString &expression);
  void calc_without_capitalization(
      double sum_d, double rate_d, double tax_rate_d, double free_sum_d,
      QDate input_date, QDate output_date, int refill_errors[],
      QDate refill_next_dates[], QString refill_sums[],
      QString refill_periods[], int cut_errors[], QDate cut_next_dates[],
      QString cut_sums[], QString cut_periods[]);
  void calc_with_capitalization(double sum_d, double rate_d, double tax_rate_d,
                                double free_sum_d, QDate input_date,
                                QDate output_date, int refill_errors[],
                                QDate refill_next_dates[],
                                QString refill_sums[], QString refill_periods[],
                                int cut_errors[], QDate cut_next_dates[],
                                QString cut_sums[], QString cut_periods[]);
  double calc_free_sum();
  void print_results(double pay_d, double total_d, double over_d);
  QDate get_periodicity(QString period, QDate input_date);
  QString check_argument(QString sum_text, QString init_string,
                         int is_int_check_need, int *error_flag);
  int is_param_int(double param_d);
  void is_date_over(QDate refill_start_date, int *error, QDate output_date);

 private slots:
  void on_push_deposit_calc_clicked();

 private:
  Ui::DepositWindow *ui;
};

#endif  // DEPOSITWINDOW_H
