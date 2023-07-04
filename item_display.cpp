#include "item_display.h"
#include "ui_item_display.h"
#include "qtodo.h"
#include "dialog.h"
#include "citem.h"
item_display::item_display(QWidget *parent, CItem& i, QTreeWidgetItem* p, bool is_son) :
    QDialog(parent),
    ui(new Ui::item_display),
    qtodo((Qtodo*)parent),
    item(i),
    pitem(p)
{
    setWindowModality(Qt::WindowModal);
    ui->setupUi(this);
    ui->textEdit->setText(item.name);
    ui->dateTimeEdit->setCalendarPopup(true);
    ui->dateTimeEdit->setDateTime(item.ddl);
    if(!item.is_whole_day)
      ui->dateTimeEdit->setDisplayFormat("yyyy-MM-dd hh:mm");
    else
      ui->dateTimeEdit->setDisplayFormat("yyyy-MM-dd");
    ui->dateTimeEdit_2->setCalendarPopup(true);
    ui->dateTimeEdit_2->setDateTime(item.reminder_time);
    ui->dateTimeEdit_2->setDisplayFormat("yyyy-MM-dd hh:mm");
    if(item.is_whole_day)
      ui->checkBox->setCheckState(Qt::Checked);
    if(item.is_vital)
      ui->vital_checkBox->setCheckState(Qt::Checked);
    if(item.is_weekly)
      ui->week_checkBox->setCheckState(Qt::Checked);
    if(is_son){
      ui->vital_checkBox->setEnabled(false);
      ui->addsubButton->setEnabled(false);
      ui->comboBox->setEnabled(false);
      ui->week_checkBox->setEnabled(false);
    }
    for(int i=0;i<((Qtodo*)parent)->categorycnt;i++){
      ui->comboBox->addItem(((Qtodo*)parent)->categoryname[i]);
    }
    ui->comboBox->setCurrentText(item.category);
    ui->comboBox->setEditable(true);
}

item_display::~item_display()
{
    delete ui;
}

void item_display::on_buttonBox_accepted()
{
    item.name = ui->textEdit->toPlainText();
    item.ddl = ui->dateTimeEdit->dateTime();
    item.reminder_time = ui->dateTimeEdit_2->dateTime();
    item.is_whole_day = ui->checkBox->checkState();
    item.is_vital = ui->vital_checkBox->checkState();
    item.category = ui->comboBox->currentText();
    item.is_weekly = ui->week_checkBox->checkState();
}


void item_display::on_checkBox_stateChanged(int state)
{
    if(state==Qt::Checked){
      item.is_whole_day=true;
      ui->dateTimeEdit->setDisplayFormat("yyyy-MM-dd");
    }
    else{
      item.is_whole_day=false;
      ui->dateTimeEdit->setDisplayFormat("yyyy-MM-dd hh:mm");
    }
}




void item_display::on_dateTimeEdit_dateTimeChanged(const QDateTime &dateTime)
{
    ui->dateTimeEdit_2->setDateTime(dateTime);
}


void item_display::on_addsubButton_clicked()
{
    CItem &input = qtodo->items[qtodo->itemcnt + 1];
    Dialog* pDialog = new Dialog(input, qtodo, &item);
    int ret = pDialog->exec();
    pDialog->close();
    if(ret == QDialog::Rejected)
      return;
    qtodo->itemcnt++;
    qtodo->additem(NULL, pitem, input);
    int idx=qtodo->find_id(pitem);
    qtodo->childid[idx][pitem->childCount() - 1] = qtodo->itemcnt;
}

