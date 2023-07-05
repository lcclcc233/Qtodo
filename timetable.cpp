#include "timetable.h"
#include "ui_timetable.h"
#include <QInputDialog>
#include <QLineEdit>
#include <QColorDialog>
#include <QColor>
#include <qdatetime.h>
#include <qtodo.h>
timetable::timetable(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::timetable)
{
    setWindowModality(Qt::WindowModal);
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(7);
    ui->tableWidget->setRowCount(12);
    QStringList Hhead;
    Hhead<<"一"<<"二"<<"三"<<"四"<<"五"<<"六"<<"日";
    ui->tableWidget->setHorizontalHeaderLabels(Hhead);
    ui->tableWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
    for(int i = 0; i < 12; i++){
        for(int j = 0; j < 7; j++){
            QTableWidgetItem *pitem = new QTableWidgetItem();
            ui->tableWidget->setItem(i, j, pitem);
        }
    }
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    pa = parent;
}

timetable::~timetable()
{
    for(int i = 0; i < 12; i++)
        for(int j = 0; j < 7; j++)
            delete ui->tableWidget->item(i, j);
    delete ui;
}

void timetable::on_addButton_clicked()
{
    QList<QTableWidgetItem*>  itemlist = ui->tableWidget->selectedItems();
    QString string = QInputDialog::getText(this, tr("添加课程"), tr("请输入课程名"), QLineEdit::Normal);
    QColorDialog dialog(QColor(0, 255, 255), this);
    dialog.exec();
    QColor color =dialog.currentColor();
    for(int i = 0; i < itemlist.size(); i++){
        itemlist[i]->setText(itemlist[i]->text()+string);
        if(color.isValid())
            itemlist[i]->setBackground(QBrush(color));
    }
}

void timetable::on_delButton_clicked()
{
    QList<QTableWidgetItem*>  itemlist = ui->tableWidget->selectedItems();
    QColor color(255, 255, 255);
    for(int i = 0; i < itemlist.size(); i++){
        itemlist[i]->setText("");
        if(color.isValid())
            itemlist[i]->setBackground(QBrush(color));
    }
}


void timetable::on_itemButton_clicked()
{
    QList<QTableWidgetItem*>  itemlist = ui->tableWidget->selectedItems();
    for(int i = 0; i < itemlist.size(); i++){
        int r = itemlist[i]->row();
        int c = itemlist[i]->column();
        QDate d;
        QTime t;
        QDateTime ddl;
        d = QDateTime::currentDateTime().date();
        QLocale locale = QLocale::English;
        int idx;
        QString tmp = QString(locale.toString(d,QString("ddd")));
        if(tmp=="Mon")
            idx=0;
        else if(tmp=="Tue")
            idx=1;
        else if(tmp=="Wed")
            idx=2;
        else if(tmp=="Thu")
            idx=3;
        else if(tmp=="Fri")
            idx=4;
        else if(tmp=="Sat")
            idx=5;
        else
            idx=6;
        d=d.addDays((c-idx+7)%7);
        if(r == 0)
            t.setHMS(8,0,0);
        else if(r == 1)
            t.setHMS(9,0,0);
        else if(r == 2)
            t.setHMS(10,10,0);
        else if(r == 3)
            t.setHMS(11,10,0);
        else if(r == 4)
            t.setHMS(13,0,0);
        else if(r == 5)
            t.setHMS(14,00,0);
        else if(r == 6)
            t.setHMS(15,10,0);
        else if(r == 7)
            t.setHMS(16,10,0);
        else if(r == 8)
            t.setHMS(17,10,0);
        else if(r == 9)
            t.setHMS(18,40,0);
        else if(r == 10)
            t.setHMS(19,40,0);
        else if(r == 11)
            t.setHMS(20,40,0);
        ddl.setDate(d);
        ddl.setTime(t);
        if(ddl.secsTo(QDateTime::currentDateTime())>0)
            ddl=ddl.addDays(7);
        ((Qtodo*)pa)->handle_extraadd(ddl);
    }
}

void timetable::gettext(int r,int c, QString& text, int& R, int& G,int& B){
    text=ui->tableWidget->item(r,c)->text();
    R=ui->tableWidget->item(r,c)->background().color().red();
    G=ui->tableWidget->item(r,c)->background().color().green();
    B=ui->tableWidget->item(r,c)->background().color().blue();
}
void timetable::additem(int r,int c, QString text, int R, int G,int B){
    ui->tableWidget->item(r,c)->setText(text);
    QColor color(R,G,B);
    ui->tableWidget->item(r,c)->setBackground(QBrush(color));
}
void timetable::clear(){
    QColor color(255, 255, 255);
    for(int i = 0; i < 12; i++)
        for(int j = 0; j < 7; j++){
            ui->tableWidget->item(i,j)->setText("");
            ui->tableWidget->item(i,j)->setBackground(QBrush(color));
        }
}
