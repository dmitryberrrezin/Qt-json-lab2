#include "delete.h"
#include "ui_delete.h"

Delete::Delete(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Delete)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
    ui->lineEdit->setValidator(new QIntValidator(0, 99999, this));
    connect(ui->del, SIGNAL(clicked()), this, SLOT(DeleteQuestion()));
}

void Delete::DeleteQuestion()
{
    if(ui->lineEdit->text().isEmpty())
    {
        QMessageBox::critical(this, "error", "Enter question number");
        return;
    }
    QFile file(QCoreApplication::applicationDirPath() + "/questions.json");
    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(this, "info", "No questions yet");
        return;
    }
    QByteArray data = file.readAll();
    file.close();
    QJsonDocument questions_doc = QJsonDocument::fromJson(data);
    QJsonObject main_obj = questions_doc.toVariant().toJsonObject();
    QJsonArray questions = main_obj["questions"].toArray();

    if(questions.isEmpty())
    {
        QMessageBox::information(this, "info", "No questions yet");
        return;
    }
    int number = ui->lineEdit->text().toInt();
    if(number > questions.size())
    {
        QMessageBox::critical(this, "error", "Question count:"+QString::number(questions.size()));
        return;
    }
    if(number == 0)
    {
        QMessageBox::critical(this, "error", "Question number must be > 0");
        return;
    }

    --number;
    auto it = questions.begin();
    for(int i = 0; i < number; ++i)
    {
        ++it;
    }
    questions.erase(it);
    main_obj["questions"] = questions;
    file.open(QIODevice::WriteOnly | QIODevice::Truncate);
    file.write(QJsonDocument(main_obj).toJson(QJsonDocument::Indented));
    file.close();
    QMessageBox::information(this, "success", "Question deleted");
 }

Delete::~Delete()
{
    delete ui;
}
