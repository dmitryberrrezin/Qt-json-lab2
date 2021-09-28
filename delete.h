#ifndef DELETE_H
#define DELETE_H

#include <QDialog>
#include <QIntValidator>
#include <QMessageBox>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

namespace Ui {
class Delete;
}

class Delete : public QDialog
{
    Q_OBJECT

public:
    explicit Delete(QWidget *parent = nullptr);
    ~Delete();
private:
    Ui::Delete *ui;
private slots:
    void DeleteQuestion();
};

#endif // DELETE_H
