#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>

#include "../Controller/Controller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 protected:
  void keyPressEvent(QKeyEvent *event);

 private:
  Ui::MainWindow *ui;
  s21::Controller *controller;

 private slots:
  void is_restart();
  QString calculation_process(QString input_text, QString x_text);
  void paint_grath(QString input_text);
  void digits_symbols();
  void equal_symbol();
  void into_button();
  void operations();
  void clean_input();
  void clean_x();
  void clean_all();
  void on_actionCredit_Calculator_triggered();
  void on_actionDeposit_Calculator_triggered();
};
#endif  // MAINWINDOW_H
