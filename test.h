#ifndef TEST_H
#define TEST_H

#include <QCoreApplication>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QDebug>

class Test
{
private:
    int current_question;
    QJsonDocument questions_doc;
    QJsonArray questions;
    int correct_answ;
    void UpdateStat();

public:
    Test();
    QJsonObject getQuestion();
    void toAnswer(int number);
    bool isValid() const;
    int QuestionCount() const;
    int GetCorrect() const;
};

#endif // TEST_H
