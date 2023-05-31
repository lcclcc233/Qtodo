#include "timetable.h"
#include "ui_timetable.h"
#include <QInputDialog>
#include <QLineEdit>
#include <QColorDialog>
#include <QColor>
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

