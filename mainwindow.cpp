#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
    QFile questions(QCoreApplication::applicationDirPath() + "/questions.json");
    if(!questions.open(QIODevice::ReadWrite))
    {
        throw -1;
    }

     QByteArray saveData = questions.readAll();
     QJsonDocument js_doc(QJsonDocument::fromJson(saveData));

     QJsonObject main_obj = js_doc.toVariant().toJsonObject();
     qDebug() << main_obj["questions"].toArray()[0];

    QJsonObject question_node = main_obj["questions"].toArray()[0].toVariant().toJsonObject();
    qDebug() << question_node["question"];

}

MainWindow::~MainWindow()
{
    delete ui;
}

