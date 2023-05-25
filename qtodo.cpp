#include "qtodo.h"
#include "./ui_qtodo.h"
#include "citem.h"
#include "dialog.h"
#include <QMessageBox>
#include <QCheckBox>
#include <qfont.h>
#include <QTimer>
Qtodo::Qtodo(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Qtodo)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(on_checkitem()));
    timer->start(10000);
    pTrayIcon = new QSystemTrayIcon(this);
    //QIcon icon = QIcon(":/tmp.png");//相对路径总是搞不定，暂且搁置
    QIcon icon = QIcon("C:/Users/28104/Documents/Qtodo/tmp.png");//暂时用着这个图标
    this->setWindowIcon(icon);
    pTrayIcon->setIcon(icon);
    pTrayIcon->setToolTip("Qtodo");
    connect(pTrayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason)));
}
Qtodo::~Qtodo()
{
    delete ui;
    delete timer;
    delete pTrayIcon;
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

void Qtodo::on_checkitem(){
    QDateTime now=QDateTime::currentDateTime();
    for(int i=0; i < itemcnt; i++){
        //qDebug()<<now.secsTo(items[i].ddl);
        if(!items[i].is_finish &&  abs(now.msecsTo(items[i].ddl)) <= 5000){
            QMessageBox *box = new QMessageBox(this);
            box->setText(QString("the deadline of ") + items[i].name + QString(" is comming !"));
            box->setModal(false);
            box->show();
        }
    }
}

void Qtodo::on_hideButton_clicked(){
    this->hide();
    pTrayIcon->show();
    pTrayIcon->showMessage(QString("Qtodo"), QString("Qtodo正在后台运行"), QSystemTrayIcon::Information, 5000);
}

void Qtodo::on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason reason){
    switch(reason){
    case QSystemTrayIcon::Trigger:
        this->show();
        break;
    default:
        break;
    }
}
