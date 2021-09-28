#ifndef QUESTION_REDACT_H
#define QUESTION_REDACT_H

#include <QDialog>
#include <QVector>
#include <QRadioButton>
#include <QLineEdit>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>

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
    QVector<QRadioButton*> radio_vector;
    QVector<QLineEdit*> edit_vector;
private slots:
    void AddQuestion();
};

#endif // QUESTION_REDACT_H
