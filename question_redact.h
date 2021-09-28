#ifndef QUESTION_REDACT_H
#define QUESTION_REDACT_H

#include <QDialog>

namespace Ui {
class question_redact;
}

class question_redact : public QDialog
{
    Q_OBJECT

public:
    explicit question_redact(QWidget *parent = nullptr);
    ~question_redact();

private:
    Ui::question_redact *ui;
};

#endif // QUESTION_REDACT_H
