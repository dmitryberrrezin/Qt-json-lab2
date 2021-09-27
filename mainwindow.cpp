#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , test(nullptr)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
    connect(ui->start, SIGNAL(triggered()), this, SLOT(StartTest()));
    connect(ui->submit, SIGNAL(clicked()), this, SLOT(NoTest()));

    for(auto it: ui->groupBox->children())
    {
        radio_vector.append(static_cast<QRadioButton*>(it));
    }

    radio_vector.pop_front();
}

void MainWindow::StartTest()
{
    if(test != nullptr)
    {
        delete test;
    }
    test = new Test;
    disconnect(ui->submit, SIGNAL(clicked()), this, SLOT(NoTest()));
    connect(ui->submit, SIGNAL(clicked()), this, SLOT(NextQuestion()));
    radio_vector[0]->setChecked(true);
    NextQuestion();
}

void MainWindow::NextQuestion()
{
    bool isAnswer = false;
    for(auto &it:radio_vector)
    {
        if(it->isChecked())
        {
            isAnswer = true;
            it->setAutoExclusive(false);
            it->setChecked(false);
            it->setAutoExclusive(true);
        }
    }
    if(!isAnswer)
    {
        QMessageBox::information(this, "error", "give the answer");
        return;
    }

    QJsonObject cur_question = test->getQuestion();
    qDebug() << cur_question;
    if(cur_question.isEmpty())
    {
        disconnect(ui->submit, SIGNAL(clicked()), this, SLOT(NextQuestion()));
        connect(ui->submit, SIGNAL(clicked()), this, SLOT(NoTest()));
        ui->questionEdit->setText("");
        ui->groupBox->setChecked(false);
        for(auto &it:radio_vector)
        {
            it->setText("");
        }
        QMessageBox::information(this, "success", "Test passed");
        return;
    }

    ui->questionEdit->setText(cur_question["question"].toString());
    QJsonArray answers = cur_question["answers"].toArray();

    for(int i = 0; i < radio_vector.size(); ++i)
    {
        radio_vector[i]->setText(answers[i].toString());
    }
}

void MainWindow::NoTest()
{
    QMessageBox::information(this, "warning", "test not started");
}

MainWindow::~MainWindow()
{
    delete ui;
}

