#include "question_redact.h"
#include "ui_question_redact.h"

question_redact::question_redact(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::question_redact)
{  
     ui->setupUi(this);
     this->setFixedSize(this->size());
     connect(ui->add, SIGNAL(clicked()), this, SLOT(AddQuestion()));
     connect(ui->exit, SIGNAL(clicked()), this, SLOT(close()));

     for(auto it: ui->RadioGroup->children())
     {
         radio_vector.append(static_cast<QRadioButton*>(it));
     }
     radio_vector.pop_front();

     for(auto it: ui->EditGroup->children())
     {
         edit_vector.append(static_cast<QLineEdit*>(it));
     }
     edit_vector.pop_front();

}

void question_redact::AddQuestion()
{
    if(ui->textEdit->toPlainText().isEmpty())
    {
       QMessageBox::critical(this, "error", "Enter a question");
       return;
    }
    bool isChecked = false;
    for(int i = 0; i < 4; ++i)
    {
        if(edit_vector[i]->text().isEmpty())
        {
            QMessageBox::critical(this, "error", "Enter an answers");
            return;
        }
        if(radio_vector[i]->isChecked())
        {
            isChecked = true;
        }
    }
    if(isChecked == false)
    {
        QMessageBox::critical(this, "error", "Mark the correct answer");
        return;
    }

    QFile file(QCoreApplication::applicationDirPath() + "/questions.json");
    file.open(QIODevice::ReadWrite);
    QByteArray data = file.readAll();
    file.close();
    QJsonDocument questions_doc = QJsonDocument::fromJson(data);
    QJsonObject main_obj = questions_doc.toVariant().toJsonObject();
    QJsonArray questions = main_obj["questions"].toArray();

    if(questions.isEmpty())
    {
       main_obj.insert("questions", questions);
    }

    QJsonArray answers;

    for(auto &it : edit_vector)
    {
        answers.append(it->text());
    }

    QJsonObject new_quest;
    new_quest.insert("question", ui->textEdit->toPlainText());
    new_quest.insert("answers", answers);
    for(int i = 0; i < 4; ++i)
    {
      if(radio_vector[i]->isChecked())
      {
          new_quest.insert("right", i+1);
          break;
      }
    }
    questions.append(new_quest);
    main_obj["questions"] = questions;

    file.open(QIODevice::WriteOnly | QIODevice::Truncate);
    file.write(QJsonDocument(main_obj).toJson(QJsonDocument::Indented));
    file.close();
    QMessageBox::information(this, "Success", "Question added");

    ui->textEdit->setText("");
    for(int i = 0; i < 4; ++i)
    {
        edit_vector[i]->setText("");
        if(radio_vector[i]->isChecked())
        {
            radio_vector[i]->setAutoExclusive(false);
            radio_vector[i]->setChecked(false);
            radio_vector[i]->setAutoExclusive(true);
        }
    }

}

question_redact::~question_redact()
{
    delete ui;
}
