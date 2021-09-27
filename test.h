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


public:
    Test();
    bool isValid();
    int QuestionCount();
    QJsonObject getQuestion();
};

#endif // TEST_H
