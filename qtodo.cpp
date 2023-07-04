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
#include <QFileDialog>
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

    categorymenu = new QMenu();
    categorychoice[0] = new QAction(QIcon(":/img/check.png"), "全部");
    categorymenu->addAction(categorychoice[0]);
    ui->categoryButton->setMenu(categorymenu);
    categoryname[0] = "无";
    connect(categorymenu, SIGNAL(triggered(QAction*)), this, SLOT(action_triggered(QAction*)));

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
    delete categorymenu;
}


void Qtodo::additem(QTreeWidgetItem* pitem, QTreeWidgetItem* fa, const CItem& input){//增加事项的模板函数
    if(pitem==NULL)
        pitem = new QTreeWidgetItem;
    pitem->setText(0,"   "+input.name);
    if(!input.is_whole_day)
      pitem->setText(1,input.ddl.toString("yyyy-MM-dd hh:mm"));
    else
      pitem->setText(1,input.ddl.toString("yyyy-MM-dd"));
    QCheckBox *pcheckbox = new QCheckBox;
    pcheckbox->setChecked(input.is_finish);
    if(fa==NULL)
        ui->treeWidget->addTopLevelItem(pitem);
    else
        fa->addChild(pitem);
    ui->treeWidget->setItemWidget(pitem, 0, pcheckbox);
    ui->pushButton_3->setCheckable(true);
    connect(pcheckbox, SIGNAL(stateChanged(int)), this, SLOT(anyStateChanged()));
    for(int i=0;i<categorycnt;i++){
        if(categoryname[i]==input.category)
            return ;
    }
    categoryname[categorycnt] = input.category;
    categorychoice[categorycnt] = new QAction(QIcon(":/img/check.png"), input.category);
    categorymenu->addAction(categorychoice[categorycnt]);
    categorychoice[categorycnt]->setIconVisibleInMenu(false);
    categorycnt++;
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
void Qtodo::handlecheck(QTreeWidgetItem* fa, int fid, bool paint){//处理已完成的传递
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
            if(items[i].is_weekly){
                items[i].ddl = items[i].ddl.addDays(7);
                items[i].reminder_time = items[i].reminder_time.addDays(7);
                for(int j = 0; j < ui->treeWidget->topLevelItemCount(); j++){
                    QTreeWidgetItem *tmp = ui->treeWidget->topLevelItem(j);
                    if(childid[0][j] == i)
                        additem(tmp, tmp->parent(), items[i]);
                    for(int k = 0; k < tmp->childCount(); k++){
                        QTreeWidgetItem *tt = tmp->child(k);
                        if(childid[childid[0][j]][k] == i)
                            additem(tt, tt->parent(), items[i]);
                    }
                }

            }
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

int Qtodo::find_id(QTreeWidgetItem *pitem){//寻找pitem对应的items的idx
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
void Qtodo::on_treeWidget_itemDoubleClicked(QTreeWidgetItem *pitem, int)//双击事项显示详细信息
{
    int idx=find_id(pitem);
    CItem input(items[idx]);
    item_display display(this, input, pitem, pitem->parent()!=NULL);
    int ret=display.exec();
    display.close();
    if(ret==Dialog::Rejected)
        return ;
    items[idx]=input;
    additem(pitem, pitem->parent(), input);
}


void Qtodo::on_pushButton_clicked()//开启课表
{
    ptable->exec();
}


void Qtodo::on_pushButton_2_clicked()//全部显示
{
    show_vital = false;
    ui->pushButton_3->setChecked(false);
    categorychoice[categorynow]->setIconVisibleInMenu(false);
    categorychoice[0]->setIconVisibleInMenu(true);
    for(int i = 0; i < ui->treeWidget->topLevelItemCount(); i++){
        QTreeWidgetItem *pitem = ui->treeWidget->topLevelItem(i);
        pitem->setHidden(false);
    }
}


void Qtodo::on_pushButton_3_clicked()//显示重要的
{
    show_vital = ui->pushButton_3->isChecked();
    if(show_vital)
        for(int i = 0; i < ui->treeWidget->topLevelItemCount(); i++){
            QTreeWidgetItem *pitem = ui->treeWidget->topLevelItem(i);
            int idx = childid[0][i];
            if(!pitem->isHidden()&&items[idx].is_vital)
                pitem->setHidden(false);
            else
                pitem->setHidden(true);
        }
    else
        for(int i = 0; i < ui->treeWidget->topLevelItemCount(); i++){
            QTreeWidgetItem *pitem = ui->treeWidget->topLevelItem(i);
            int idx = childid[0][i];
            if(categorynow==0 || items[idx].category==categoryname[categorynow])
                pitem->setHidden(false);
            else
                pitem->setHidden(true);
        }
}
void Qtodo::action_triggered(QAction* action){//分类显示
    for(int j=0; j<categorycnt; j++){
        if(action == categorychoice[j])
            categorychoice[j]->setIconVisibleInMenu(true);
        else
            categorychoice[j]->setIconVisibleInMenu(false);
    }
    if(action == categorychoice[0]){
        for(int i = 0; i < ui->treeWidget->topLevelItemCount(); i++){
            QTreeWidgetItem *pitem = ui->treeWidget->topLevelItem(i);
            int idx = childid[0][i];
            if(show_vital&&!items[idx].is_vital)
                pitem->setHidden(true);
            else
                pitem->setHidden(false);
        }
    }
    else{
        for(int j=1; j<categorycnt; j++){
            if(action == categorychoice[j]){
                for(int i = 0; i < ui->treeWidget->topLevelItemCount(); i++){
                    QTreeWidgetItem *pitem = ui->treeWidget->topLevelItem(i);
                    int idx = childid[0][i];
                    if(items[idx].category == categoryname[j] && (!show_vital || items[idx].is_vital))
                        pitem->setHidden(false);
                    else
                        pitem->setHidden(true);
                }
                categorynow = j;
            }
        }
    }
}

void Qtodo::on_out_pushButton_clicked()//导出数据
{
    QString filepath = QFileDialog::getSaveFileName(this, "Save file", "./", "Txt files(*.txt)");
    QFile file(filepath);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        qDebug()<<"File not found!";
        return ;
    }
    QTextStream out(&file);
    out<<"Qtodo"<<Qt::endl;
    out<<itemcnt<<Qt::endl;
    for(int i=1; i<=itemcnt; i++){
        out<<items[i].name<<Qt::endl;
        out<<items[i].ddl.toString("yyyy-MM-dd hh:mm")<<Qt::endl;
        out<<items[i].reminder_time.toString("yyyy-MM-dd hh:mm")<<Qt::endl;
        out<<items[i].is_finish<<Qt::endl;
        out<<items[i].is_whole_day<<Qt::endl;
        out<<items[i].is_vital<<Qt::endl;
    }
    for(int i = 0; i < ui->treeWidget->topLevelItemCount(); i++){
        QTreeWidgetItem *tmp = ui->treeWidget->topLevelItem(i);
        int idx = find_id(tmp);
        out<<idx<<" ";
    }
    out<<"0"<<Qt::endl;
    for(int i = 0; i < ui->treeWidget->topLevelItemCount(); i++){
        QTreeWidgetItem *tmp = ui->treeWidget->topLevelItem(i);
        int idx = find_id(tmp);
        out<<idx<<" ";
        for(int j=0;childid[idx][j]!=0;j++){
            out<<childid[idx][j]<<" ";
        }
        out<<"0"<<Qt::endl;
    }
}

void Qtodo::on_open_pushButton_clicked()
{
    QString filepath = QFileDialog::getOpenFileName(this, "Open file", "./", "Txt files(*.txt)");
    QFile file(filepath);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug()<<"File not found!";
        return ;
    }
    QTextStream in(&file);
    QString str;
    in>>str;
    if(str!=QString("Qtodo")){
        qDebug()<<"Invalid data!";
        return ;
    }
    in>>itemcnt;
    int tmp;
    for(int i = 1; i <= itemcnt; i++){
        in.readLine();
        str = in.readLine();
        items[i].name = str;
        str = in.readLine();
        items[i].ddl = QDateTime::fromString(str, "yyyy-MM-dd hh:mm");
        str = in.readLine();
        items[i].reminder_time = QDateTime::fromString(str, "yyyy-MM-dd hh:mm");
        in>>tmp;
        items[i].is_finish = tmp;
        in>>tmp;
        items[i].is_whole_day = tmp;
        in>>tmp;
        items[i].is_vital = tmp;
    }
    ui->treeWidget->clear();
    for(int j = 0; ; j++){
        in>>tmp;
        if(!tmp)
            break;
        childid[0][j] = tmp;
        additem(NULL, NULL, items[tmp]);
    }
    for(int i = 0; i < ui->treeWidget->topLevelItemCount(); i++){
        QTreeWidgetItem *fa = ui->treeWidget->topLevelItem(i);
        int idx;
        in>>idx;
        for(int j = 0; ; j++){
            in>>tmp;
            if(!tmp)
                break;
            childid[idx][j] = tmp;
            additem(NULL, fa, items[tmp]);
        }
    }
}

