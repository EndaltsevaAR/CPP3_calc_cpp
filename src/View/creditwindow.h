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
  void print_results(std::vector<double> print_info);

 private:
  Ui::CreditWindow *ui;
};

#endif  // CREDITWINDOW_H
