#include "question_redact.h"
#include "ui_question_redact.h"

question_redact::question_redact(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::question_redact)
{  
     ui->setupUi(this);
     this->setFixedSize(this->size());
}

question_redact::~question_redact()
{
    delete ui;
}
