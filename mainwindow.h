#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "test.h"
#include "delete.h"
#include "question_redact.h"

#include <QMainWindow>
#include <QRadioButton>
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Test *test;
    QVector<QRadioButton*> radio_vector;

signals:
   void submitted();

private slots:
    void StartTest();
    void NextQuestion();
    void NoTest();
    void ShowStat();
    void NewQuestion();
    void DeleteQuestion();
};
#endif // MAINWINDOW_H
