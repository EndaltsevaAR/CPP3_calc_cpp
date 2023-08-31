#ifndef CREDITWINDOW_H
#define CREDITWINDOW_H

#include <QDialog>
#include <QString>
#include <iostream>

#include "../Controller/Controller.h"

namespace Ui {
class CreditWindow;
}

class CreditWindow : public QDialog {
  Q_OBJECT

 public:
  explicit CreditWindow(QWidget *parent = nullptr);
  ~CreditWindow();

 protected:
  void keyPressEvent(QKeyEvent *event);
  int is_string_digitable(const QString &expression);
  // char *double_to_string(double number);
  void print_results(double pay_d, double total_d, double over_d);
  void annuitet_type(double sum_d, double time_d, double rate_d);
  void differ_type(double sum_d, double time_d, double rate_d);

 private:
  Ui::CreditWindow *ui;
};

#endif  // CREDITWINDOW_H
