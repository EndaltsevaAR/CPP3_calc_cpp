#include "mainwindow.h"

#include <QKeyEvent>

#include "../Controller/Controller.h"
#include "creditwindow.h"
#include "depositwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  ui->widget->setInteraction(QCP::iRangeZoom, true);
  ui->widget->setInteraction(QCP::iRangeDrag, true);

  connect(ui->button_0, SIGNAL(clicked()), this, SLOT(digits_symbols()));
  connect(ui->button_1, SIGNAL(clicked()), this, SLOT(digits_symbols()));
  connect(ui->button_2, SIGNAL(clicked()), this, SLOT(digits_symbols()));
  connect(ui->button_3, SIGNAL(clicked()), this, SLOT(digits_symbols()));
  connect(ui->button_4, SIGNAL(clicked()), this, SLOT(digits_symbols()));
  connect(ui->button_5, SIGNAL(clicked()), this, SLOT(digits_symbols()));
  connect(ui->button_6, SIGNAL(clicked()), this, SLOT(digits_symbols()));
  connect(ui->button_7, SIGNAL(clicked()), this, SLOT(digits_symbols()));
  connect(ui->button_8, SIGNAL(clicked()), this, SLOT(digits_symbols()));
  connect(ui->button_9, SIGNAL(clicked()), this, SLOT(digits_symbols()));
  connect(ui->button_acos, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->button_cos, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->button_asin, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->button_sin, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->button_atan, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->button_tan, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->button_pi, SIGNAL(clicked()), this, SLOT(digits_symbols()));
  connect(ui->button_e, SIGNAL(clicked()), this, SLOT(digits_symbols()));
  connect(ui->button_sqrt, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->button_pow, SIGNAL(clicked()), this, SLOT(into_button()));
  connect(ui->button_ln, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->button_log, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->button_mod, SIGNAL(clicked()), this, SLOT(digits_symbols()));
  connect(ui->button_mul, SIGNAL(clicked()), this, SLOT(digits_symbols()));
  connect(ui->button_div, SIGNAL(clicked()), this, SLOT(digits_symbols()));
  connect(ui->button_sub, SIGNAL(clicked()), this, SLOT(digits_symbols()));
  connect(ui->button_add, SIGNAL(clicked()), this, SLOT(digits_symbols()));
  connect(ui->button_open_bracket, SIGNAL(clicked()), this,
          SLOT(digits_symbols()));
  connect(ui->button_close_bracket, SIGNAL(clicked()), this,
          SLOT(digits_symbols()));
  connect(ui->button_dot, SIGNAL(clicked()), this, SLOT(digits_symbols()));
  connect(ui->button_delete_input, SIGNAL(clicked()), this,
          SLOT(clean_input()));
  connect(ui->button_delete_x, SIGNAL(clicked()), this, SLOT(clean_x()));
  connect(ui->button_AC, SIGNAL(clicked()), this, SLOT(clean_all()));
  connect(ui->button_eq, SIGNAL(clicked()), this, SLOT(equal_symbol()));
  connect(ui->button_x, SIGNAL(clicked()), this, SLOT(digits_symbols()));

  ui->widget->xAxis->setLabel("X");
  ui->widget->yAxis->setLabel("Y");
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::paint_grath(QString input_text) {
  //   QString input = ui->label_input_enter->text();
  ui->widget->clearGraphs();
  double XBegin = -5;
  double XEnd = 5;
  double YMin = 0, YMax = 0;

  double X_val = XBegin, Y_val = 0;

  double step_x = 0.04;
  int number_steps = (XEnd - XBegin) / step_x;

  QVector<double> x, y;

  for (int i = 0; i < number_steps; i++) {
    QString y_string = calculation_process(input_text, QString::number(X_val));
    if (y_string != "ERROR") {
      x.push_back(X_val);
      Y_val = y_string.toDouble();
      if (Y_val < YMin) {
        YMin = Y_val;
      } else if (Y_val > YMax) {
        YMax = Y_val;
      }
      y.push_back(Y_val);
    }
    X_val += step_x;
  }

  ui->widget->xAxis->setRange(-5, 5);
  ui->widget->yAxis->setRange(YMin, YMax);
  ui->widget->addGraph();
  ui->widget->graph(0)->addData(x, y);
  ui->widget->replot();
  x.clear();
  y.clear();
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
  is_restart();
  QString input_text = ui->label_input_enter->text();
  QString x_text = ui->label_x_enter->text();
  QString key_touch = event->text();

  if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter ||
      key_touch == "=") {
    QString result = calculation_process(input_text, x_text);
    ui->label_output_enter->setText(result);
    paint_grath(input_text);
  } else {
    if (ui->radio_input->isChecked()) {
      if (event->key() == Qt::Key_Backspace) {
        if (input_text.length() > 0) {
          input_text.chop(1);
          ui->label_input_enter->setText(input_text);
        }
      } else {
        // Передаем событие дальше для обработки других клавиш
        input_text += event->text();
        ui->label_input_enter->setText(input_text);
      }
    } else if (ui->radio_x->isChecked()) {
      if (event->key() == Qt::Key_Backspace) {
        if (x_text.length() > 0) {
          x_text.chop(1);
          ui->label_x_enter->setText(x_text);
        }
      } else {
        // Передаем событие дальше для обработки других клавиш
        x_text += event->text();
        ui->label_x_enter->setText(x_text);
      }
    }
  }
}

void MainWindow::equal_symbol() {
  QString input_text = ui->label_input_enter->text();
  QString x_text = ui->label_x_enter->text();
  QString result = calculation_process(input_text, x_text);
  ui->label_output_enter->setText(result);
  paint_grath(input_text);
}

QString MainWindow::calculation_process(QString input_text, QString x_text) {
  s21::Controller controller;
  if (x_text == "") {
    x_text = "3.14";
  }
  return QString::fromStdString(controller.startCommonCalculator(
      input_text.toStdString(), x_text.toStdString()));
}

void MainWindow::digits_symbols() {
  is_restart();
  QPushButton *button = (QPushButton *)sender();
  QString string_text;
  if (ui->radio_input->isChecked()) {
    string_text = ui->label_input_enter->text() + button->text();
    ui->label_input_enter->setText(string_text);
  } else {
    string_text = ui->label_x_enter->text() + button->text();
    ui->label_x_enter->setText(string_text);
  }
}

void MainWindow::into_button() {
  is_restart();
  QPushButton *button = (QPushButton *)sender();
  QString string_text;
  QString button_text = button->text();
  if (button_text == "x^y") {
    button_text = "^";
  }
  if (ui->radio_input->isChecked()) {
    string_text = ui->label_input_enter->text() + button_text;
    ui->label_input_enter->setText(string_text);
  } else {
    string_text = ui->label_x_enter->text() + button_text;
    ui->label_x_enter->setText(string_text);
  }
}

void MainWindow::operations() {
  is_restart();
  QPushButton *button = (QPushButton *)sender();
  QString string_text;
  if (ui->radio_input->isChecked()) {
    string_text = ui->label_input_enter->text() + button->text() + "(";
    ui->label_input_enter->setText(string_text);
  } else {
    string_text = ui->label_x_enter->text() + button->text() + "(";
    ui->label_x_enter->setText(string_text);
  }
}

void MainWindow::clean_input() { ui->label_input_enter->setText(""); }

void MainWindow::clean_x() { ui->label_x_enter->setText(""); }

void MainWindow::clean_all() {
  clean_input();
  clean_x();
  ui->label_output_enter->setText("");
}

void MainWindow::is_restart() {
  QString output = ui->label_output_enter->text();
  if (output == "ERROR") {
    clean_all();
  } else if (output != "") {
    clean_all();
    ui->label_input_enter->setText(output + " ");
    ui->label_output_enter->setText("");
  }
}

void MainWindow::on_actionCredit_Calculator_triggered() {
  CreditWindow credit_window;
  credit_window.setModal(true);
  // credit_window.setFixedSize(850, 600);
  credit_window.exec();
}

void MainWindow::on_actionDeposit_Calculator_triggered() {
  DepositWindow deposit_window;
  deposit_window.setModal(true);
  // deposit_window.setFixedSize(850, 600);
  deposit_window.exec();
}
