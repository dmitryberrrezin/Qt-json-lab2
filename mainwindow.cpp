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
    connect(ui->statistic, SIGNAL(triggered()), this, SLOT(ShowStat()));

    for(auto it: ui->groupBox->children())
    {
        radio_vector.append(static_cast<QRadioButton*>(it));
    }

    radio_vector.pop_front();
}

void MainWindow::StartTest()
{
    ui->menu->setEnabled(false);
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
    for(int i = 0; i < radio_vector.size(); ++i)
    {
        if(radio_vector[i]->isChecked())
        {
            isAnswer = true;
            radio_vector[i]->setAutoExclusive(false);
            radio_vector[i]->setChecked(false);
            radio_vector[i]->setAutoExclusive(true);
            test->toAnswer(i+1);
            break;
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
        QString res = "result: " + QString::number(test->GetCorrect()) + "/" + QString::number(test->QuestionCount());
        QMessageBox::information(this, "success", res);
        ui->menu->setEnabled(true);
        return;
    }

    ui->questionEdit->setText(cur_question["question"].toString());
    QJsonArray answers = cur_question["answers"].toArray();
    for(int i = 0; i < radio_vector.size(); ++i)
    {
        radio_vector[i]->setText(answers[i].toString());
    }
}

void MainWindow::ShowStat()
{
   QFile file(QCoreApplication::applicationDirPath() + "/statistics.json");
   if(!file.open(QIODevice::ReadOnly))
   {
       QMessageBox::information(this, "error", "no statistics");
       return;
   }

   QByteArray data = file.readAll();
   file.close();
   QJsonDocument stat_doc = QJsonDocument::fromJson(data);
   QJsonArray attempts = stat_doc["attempts"].toArray();

   QString toEdit;
   for(int i = 0; i < attempts.size(); ++i)
   {
       toEdit += "attempt №" + QString::number(i+1) + ":\n";
       toEdit += QString::number(attempts[i].toObject()["correct"].toInt()) + "/" + QString::number(attempts[i].toObject()["total"].toInt()) + "\n\n";
   }
   ui->questionEdit->setText(toEdit);
}

void MainWindow::NoTest()
{
    QMessageBox::information(this, "warning", "test is not started");
}

MainWindow::~MainWindow()
{
    delete ui;
}

