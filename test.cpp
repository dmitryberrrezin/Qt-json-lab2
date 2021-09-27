#include "test.h"

Test::Test():
    current_question(0),
    correct_answ(0)
{
    QFile file(QCoreApplication::applicationDirPath() + "/questions.json");
    file.open(QIODevice::ReadWrite);
    QByteArray data = file.readAll();
    file.close();
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
        qDebug() << correct_answ << "/" << QuestionCount();
        UpdateStat();
        return QJsonObject();
    }
    return QJsonObject(questions[current_question++].toObject());
}

void Test::toAnswer(int number)
{
    if(current_question == 0)
        return;
    if(number == questions[current_question-1].toObject()["right"].toInt())
    {
        ++correct_answ;
    }
}

void Test::UpdateStat()
{
    QFile file(QCoreApplication::applicationDirPath() + "/statistics.json");
    file.open(QIODevice::ReadWrite);
    QByteArray data = file.readAll();
    QJsonDocument stat_doc = QJsonDocument::fromJson(data);
    QJsonObject main_obj = stat_doc.toVariant().toJsonObject();
    QJsonArray attempts = main_obj["attempts"].toArray();

    if(attempts.isEmpty())
    {
        main_obj.insert("attempts", attempts);
    }
    file.close();
    QJsonObject new_obj;
    new_obj.insert("correct", correct_answ);
    new_obj.insert("total", QuestionCount());
    attempts.append(new_obj);
    main_obj["attempts"] = attempts;

    file.open(QIODevice::WriteOnly);
    file.write(QJsonDocument(main_obj).toJson(QJsonDocument::Indented));
    file.close();
}

int Test::GetCorrect() const
{
    return correct_answ;
}

int Test::QuestionCount() const
{
    return questions.size();
}

bool Test::isValid() const
{
    return !questions.isEmpty();
}
