#include "qtodo.h"
#include "./ui_qtodo.h"
#include "citem.h"
#include <QMessageBox>
#include <QCheckBox>
Qtodo::Qtodo(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Qtodo)
{
    ui->setupUi(this);
}

Qtodo::~Qtodo()
{
    delete ui;
}

void Qtodo::on_pushButton_clicked()
{
    int ret=QMessageBox::information(this,tr("你好"),tr("Hello world!"));
    if(ret==QMessageBox::Ok) qDebug()<<tr("你好！");
}

void Qtodo::on_pushButton_2_clicked()
{
    CItem input("程设实习大作业",QDateTime::fromString("2023-06-04 00:00:00","yyyy-MM-dd hh:mm:ss"),false);
    QListWidgetItem *pitem = new QListWidgetItem;
    pitem->setText("     "+input.name+"     "+input.ddl.toString());
    QCheckBox *pcheckbox = new QCheckBox;
    pcheckbox->setChecked(input.is_finish);//好像没必要？毕竟不会有true
    ui->listWidget->addItem(pitem);
    ui->listWidget->setItemWidget(pitem,pcheckbox);
}

