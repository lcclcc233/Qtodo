#include "item_display.h"
#include "ui_item_display.h"

item_display::item_display(QWidget *parent, CItem& i) :
    QDialog(parent),
    ui(new Ui::item_display),
    item(i)
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

