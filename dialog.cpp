#include "dialog.h"
#include "ui_dialog.h"


Dialog::Dialog(CItem &_i, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog),
    input(_i)
{
    setWindowModality(Qt::WindowModal);
    ui->setupUi(this);
    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
}
Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_buttonBox_accepted()
{
    input.name = ui->textEdit->toPlainText();
    input.ddl = ui->dateTimeEdit->dateTime();
    input.is_finish = false;
    qDebug()<<tr("input finished");
}

