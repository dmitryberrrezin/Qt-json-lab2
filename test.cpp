#include "test.h"

Test::Test(): current_question(0)
{
    QFile file(QCoreApplication::applicationDirPath() + "/questions.json");
    file.open(QIODevice::ReadWrite);
    QByteArray data = file.readAll();
    questions_doc = QJsonDocument::fromJson(data);
    if(questions_doc.isEmpty() || questions_doc.isNull())
    {
        QMessageBox::information(nullptr, "Error", "Invalid File");
        return;
    }
    questions = questions_doc["questions"].toArray();
}

QJsonObject Test::getQuestion()
{
    if(current_question == QuestionCount())
    {
        return QJsonObject();
    }
    return QJsonObject(questions[current_question++].toObject());
}

int Test::QuestionCount()
{
    return questions.size();
}

bool Test::isValid()
{
    return questions.size() > 0;
}
