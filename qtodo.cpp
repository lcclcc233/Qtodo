#include "qtodo.h"
#include "./ui_qtodo.h"
#include "citem.h"
#include "dialog.h"
#include <QMessageBox>
#include <QCheckBox>
#include <qfont.h>
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

CItem items[100];
int itemcnt = 0;
void Qtodo::on_additemButton_clicked()
{
    //CItem input("程设实习大作业",QDateTime::fromString("2023-06-04 00:00:00","yyyy-MM-dd hh:mm:ss"),false);
    CItem &input = items[itemcnt++];
    Dialog* pDialog = new Dialog(input, this);
    int ret = pDialog->exec();
    pDialog->close();
    if(ret == QDialog::Rejected)
        return;
    QListWidgetItem *pitem = new QListWidgetItem;
    QString out=QString("   %1").arg(input.name, -70+input.name.length(), QLatin1Char(' '))+input.ddl.toString();
    pitem->setText(out);
    QCheckBox *pcheckbox = new QCheckBox;
    pcheckbox->setChecked(input.is_finish);//好像没必要？毕竟不会有true
    ui->listWidget->addItem(pitem);
    ui->listWidget->setItemWidget(pitem,pcheckbox);
    connect(pcheckbox, SIGNAL(stateChanged(int)), this, SLOT(anyStateChanged()));
}

void Qtodo::anyStateChanged(){
    for(int i = 0; i < ui->listWidget->count(); i++){
        QListWidgetItem *pitem =ui->listWidget->item(i);
        QCheckBox *pcheckbox =static_cast<QCheckBox *>(ui->listWidget->itemWidget(pitem));
        items[i].is_finish=pcheckbox->isChecked();
        if(items[i].is_finish){
            QFont font;
            font.setStrikeOut(true);
            pitem->setFont(font);
        }
        else{
            QFont font;
            font.setStrikeOut(false);
            pitem->setFont(font);
        }
    }
}
