#include "qtodo.h"
#include "./ui_qtodo.h"
#include "citem.h"
#include "dialog.h"
#include "reminder.h"
#include "item_display.h"
#include <QMessageBox>
#include <QCheckBox>
#include <qfont.h>
#include <QTimer>
#include <QTreeWidget>
#include <QTreeWidgetItem>
Qtodo::Qtodo(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Qtodo)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(on_checkitem()));
    timer->start(10000);
    pTrayIcon = new QSystemTrayIcon(this);
    QIcon icon = QIcon(":/img/todo_icon.png");
    //QIcon icon = QIcon("C:/Users/28104/Documents/Qtodo/tmp.png");
    this->setWindowIcon(icon);
    pTrayIcon->setIcon(icon);
    pTrayIcon->setToolTip("Qtodo");
    connect(pTrayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason)));
    ui->treeWidget->setColumnCount(2);
    QStringList head;
    head<<"事项名称"<<"截止时间";
    ui->treeWidget->setHeaderLabels(head);
    ptable = new timetable(this);
}
Qtodo::~Qtodo()
{
    delete ui;
    delete timer;
    delete pTrayIcon;
    delete ptable;
}


void Qtodo::additem(QTreeWidgetItem* pitem, QTreeWidgetItem* fa, const CItem& input){
    if(pitem==NULL)
        pitem = new QTreeWidgetItem;
    pitem->setText(0,"   "+input.name);
    pitem->setText(1,input.ddl.toString("yyyy-MM-dd hh:mm"));
    QCheckBox *pcheckbox = new QCheckBox;
    pcheckbox->setChecked(input.is_finish);
    if(fa==NULL)
        ui->treeWidget->addTopLevelItem(pitem);
    else
        fa->addChild(pitem);
    ui->treeWidget->setItemWidget(pitem, 0, pcheckbox);
    connect(pcheckbox, SIGNAL(stateChanged(int)), this, SLOT(anyStateChanged()));
}
void Qtodo::on_additemButton_clicked()//增加事项
{
    CItem &input = items[itemcnt + 1];
    Dialog* pDialog = new Dialog(input, this);
    int ret = pDialog->exec();
    pDialog->close();
    if(ret == QDialog::Rejected)
        return;
    itemcnt++;
    additem(NULL, NULL, input);
    childid[0][ui->treeWidget->topLevelItemCount() - 1] = itemcnt;
}
void Qtodo::handlecheck(QTreeWidgetItem* fa, int fid, bool paint){
    for(int i = 0; i< fa->childCount(); i++){
        QTreeWidgetItem *pitem = fa->child(i);
        int idx = childid[fid][i];
        QCheckBox *pcheckbox =static_cast<QCheckBox *>(ui->treeWidget->itemWidget(pitem,0));
        if(paint)
            pcheckbox->setCheckState(Qt::Checked);
        items[idx].is_finish=pcheckbox->isChecked();
        if(items[idx].is_finish){
            QFont font;
            font.setStrikeOut(true);
            pitem->setFont(0, font);
            pitem->setFont(1, font);
            handlecheck(pitem, idx, true);
        }
        else{
            QFont font;
            font.setStrikeOut(false);
            pitem->setFont(0, font);
            pitem->setFont(1, font);
            handlecheck(pitem, idx, false);
        }
    }
}
void Qtodo::anyStateChanged(){//事项被勾选
    for(int i = 0; i < ui->treeWidget->topLevelItemCount(); i++){
        QTreeWidgetItem *pitem = ui->treeWidget->topLevelItem(i);
        int idx = childid[0][i];
        QCheckBox *pcheckbox =static_cast<QCheckBox *>(ui->treeWidget->itemWidget(pitem,0));
        items[idx].is_finish=pcheckbox->isChecked();
        if(items[idx].is_finish){
            QFont font;
            font.setStrikeOut(true);
            pitem->setFont(0, font);
            pitem->setFont(1, font);
            handlecheck(pitem, idx, true);
        }
        else{
            QFont font;
            font.setStrikeOut(false);
            pitem->setFont(0, font);
            pitem->setFont(1, font);
            handlecheck(pitem, idx, false);
        }
    }
}

void Qtodo::on_checkitem(){//检测提醒
    QDateTime now=QDateTime::currentDateTime();
    for(int i=1; i <= itemcnt; i++){
        //qDebug()<<now.msecsTo(items[i].reminder_time);
        if(!items[i].is_finish &&  abs(now.msecsTo(items[i].reminder_time)) <= 5000){
            reminder *prm = new reminder(this, items[i]);
            prm->work();
        }
    }
}

void Qtodo::on_hideButton_clicked(){//最小化到托盘
    this->hide();
    pTrayIcon->show();
    pTrayIcon->showMessage(QString("Qtodo"), QString("Qtodo正在后台运行"), QSystemTrayIcon::Information, 5000);
}

void Qtodo::on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason reason){//托盘中点击
    switch(reason){
    case QSystemTrayIcon::Trigger:
        this->show();
        break;
    default:
        break;
    }
}

int Qtodo::find_id(QTreeWidgetItem *pitem){
    QTreeWidgetItem *fa = pitem->parent();
    if(fa == NULL){
        for(int i = 0; i < ui->treeWidget->topLevelItemCount(); i++){
            QTreeWidgetItem *tmp = ui->treeWidget->topLevelItem(i);
            if(tmp == pitem)
                return childid[0][i];
        }
    }
    int fid=find_id(fa);
    for(int i = 0; i< fa->childCount(); i++){
        QTreeWidgetItem *tmp = fa->child(i);
        if(tmp == pitem)
            return childid[fid][i];
    }
    qDebug()<<"find_id error";
    return 0;
}
void Qtodo::on_treeWidget_itemDoubleClicked(QTreeWidgetItem *pitem, int)
{
    int idx=find_id(pitem);
    CItem input(items[idx]);
    item_display display(this, input, pitem);
    int ret=display.exec();
    display.close();
    if(ret==Dialog::Rejected)
        return ;
    items[idx]=input;
    additem(pitem, pitem->parent(), input);
}


void Qtodo::on_pushButton_clicked()
{
    ptable->exec();
}

